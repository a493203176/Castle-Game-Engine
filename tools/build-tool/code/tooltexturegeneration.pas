{
  Copyright 2016-2022 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Compressing and downscaling textures. }
unit ToolTextureGeneration;

{$I castleconf.inc}

interface

uses CastleUtils, CastleStringUtils,
  ToolProject;

procedure AutoGenerateTextures(const Project: TCastleProject);
procedure AutoGenerateCleanAll(const Project: TCastleProject);
procedure AutoGenerateCleanUnused(const Project: TCastleProject);

implementation

{ FPC has CPU unit only for certain architectures, see
  $ cd fpcsrc/rtl
  $ find -iname cpu.pp
}
{$if defined(CPUi386) or
     defined(CPUx86_64) or
     defined(CPUarm) or
     defined(CPUi8086)}
  {$define HAS_CPU_UNIT}
{$endif}

uses SysUtils, {$ifdef HAS_CPU_UNIT} Cpu, {$endif}
  CastleUriUtils, CastleInternalMaterialProperties, CastleImages, CastleFilesUtils,
  CastleLog, CastleFindFiles, CastleTimeUtils,
  CastleInternalAutoGenerated,
  ToolCommonUtils, ToolUtils, {SHA1,} MD5;

type
  ECannotFindTool = class(Exception)
  strict private
    FToolName: string;
  public
    constructor Create(const AToolName: string; const C: TTextureCompression);
    property ToolName: string read FToolName;
  end;

constructor ECannotFindTool.Create(const AToolName: string;
  const C: TTextureCompression);
begin
  FToolName := AToolName;
  inherited CreateFmt('Cannot find tool "%s" necessary to make compressed texture format %s',
    [ToolName, TextureCompressionToString(C)]);
end;

type
  TStats = record
    Count: Cardinal;
    HashTime: TFloatTime;
    DimensionsCount: Cardinal;
    DimensionsTime: TFloatTime;
    CompressionCount: Cardinal;
    CompressionTime: TFloatTime;
    DownscalingCount: Cardinal;
    DownscalingTime: TFloatTime;
    DxtAutoDetectCount: Cardinal;
    DxtAutoDetectTime: TFloatTime;
  end;

{ Auto-detect best DXTn compression format for this image. }
function AutoDetectDxt(const ImageUrl: String; var Stats: TStats): TTextureCompression;
var
  Image: TCastleImage;
  TimeStart: TProcessTimerResult;
begin
  Inc(Stats.DxtAutoDetectCount);
  TimeStart := ProcessTimer;

  Image := LoadImage(ImageUrl);
  try
    case Image.AlphaChannel of
      acNone    : Result:= tcDxt1_RGB;
      acTest    : Result:= tcDxt1_RGBA;
      acBlending: Result:= tcDxt5;
      {$ifndef COMPILER_CASE_ANALYSIS}
      else raise EInternalError.Create('Unexpected Image.AlphaChannel in AutoDetectDxt');
      {$endif}
    end;
  finally FreeAndNil(Image) end;

  Writeln('Autodetected DXTn type for "' + ImageUrl + '": ' +
    TextureCompressionToString(Result));

  Stats.DxtAutoDetectTime := Stats.DxtAutoDetectTime + TimeStart.ElapsedTime;
end;

{ Calculate file contents hash. }
function CalculateHash(const FileUrl: String; var Stats: TStats): string;
var
  TimeStart: TProcessTimerResult;
begin
  TimeStart := ProcessTimer;
  //Result := SHA1Print(SHA1File(UriToFilenameSafe(FileUrl)));
  { MD5 hash is ~2 times faster in my tests, once files are in OS cache. }
  Result := MDPrint(MDFile(UriToFilenameSafe(FileUrl), MD_VERSION_5));
  Stats.HashTime := Stats.HashTime + TimeStart.ElapsedTime;
end;

{ Make given URL relative to project's data (fails if not possible). }
function MakeUrlRelativeToData(const Project: TCastleProject; const Url: String): String;
var
  DataUrl: String;
begin
  DataUrl := FilenameToUriSafe(Project.DataPath);
  if not IsPrefix(DataUrl, Url, false) then
    raise Exception.CreateFmt('File (%s) is not within data (%s)', [Url, DataUrl]);
  Result := PrefixRemove(DataUrl, Url, false);
end;

procedure AutoGenerateTextures(const Project: TCastleProject);

  procedure TryToolExe(var ToolExe: string; const ToolExeAbsolutePath: string);
  begin
    if (ToolExe = '') and RegularFileExists(ToolExeAbsolutePath) then
      ToolExe := ToolExeAbsolutePath;
  end;

  procedure TryToolExePath(var ToolExe: string; const ToolExeName: string;
    const C: TTextureCompression);
  begin
    if ToolExe = '' then
    begin
      ToolExe := FindExe(ToolExeName);
      if ToolExe = '' then
        raise ECannotFindTool.Create(ToolExeName, C);
    end;
  end;

  procedure Compressonator(const InputFile, OutputFile: string;
    const C: TTextureCompression; MipmapsLevel: Cardinal;
    const CompressionNameForTool: String;
    const AstcBlockRate: String = '');
  var
    ToolExe, InputFlippedFile, OutputTempFile, TempPrefix: string;
    Image: TCastleImage;
    CommandExe: string;
    CommandOptions: TCastleStringList;
  begin
    ToolExe := FindExeCastleTool('CompressonatorCLI');
    { otherwise, assume it's on $PATH }
    if ToolExe = '' then
      ToolExe := FindExe('CompressonatorCLI');
    if ToolExe = '' then
      // on Linux, new released on https://github.com/GPUOpen-Tools/Compressonator/releases have it lowercase
      ToolExe := FindExe('compressonatorcli');
    if ToolExe = '' then
      raise ECannotFindTool.Create('CompressonatorCLI', C);

    TempPrefix := GetTempFileNamePrefix;

    InputFlippedFile := TempPrefix + '.png';

    { In theory, when DDSFlipped = false, we could just do
      CheckCopyFile(InputFile, InputFlippedFile).
      But then AMDCompressCLI fails to read some png files (like flying in dark_dragon).
      TODO: this comment is possibly no longer true as of
      the new (open-source and cross-platform) Compressonator. }
    Image := LoadImage(FilenameToUriSafe(InputFile));
    try
      if TextureCompressionInfo[C].DDSFlipped then
        Image.FlipVertical;
      SaveImage(Image, FilenameToUriSafe(InputFlippedFile));
    finally FreeAndNil(Image) end;

    { this is worse, as it requires ImageMagick }
    // RunCommandSimple(FindExe('convert'), [InputFile, '-flip', InputFlippedFile]);

    OutputTempFile := TempPrefix + 'output' + ExtractFileExt(OutputFile);

    CommandOptions := TCastleStringList.Create;
    try
      CommandExe := ToolExe;

      if AstcBlockRate <> '' then
      begin
        CommandOptions.Add('-BlockRate');
        CommandOptions.Add(AstcBlockRate);
      end;

      if MipmapsLevel > 1 then
      begin
        if MipmapsLevel > 20 then
        begin
          WritelnWarning('Compressonator only supports mipmap levels up to 20, capping specified %d to 20', [MipmapsLevel]);
          MipmapsLevel := 20;
        end;
        CommandOptions.AddRange([
          '-miplevels',
          IntToStr(MipmapsLevel)
        ]);
      end else
      begin
        CommandOptions.AddRange([
          '-nomipmap'
        ]);
      end;

      CommandOptions.AddRange([
        '-fd',
        CompressionNameForTool,
        InputFlippedFile,
        OutputTempFile
      ]);

      {$ifdef UNIX}
      // CompressonatorCLI is just a bash script on Unix
      CommandOptions.Insert(0, CommandExe);
      CommandExe := '/bin/bash';
      {$endif}

      { TODO: it doesn't seem to help, DXT1_RGBA is still without
        anything useful in alpha value. Seems like AMDCompressCLI bug,
        or I just don't know how to use the DXT1 options?
        TODO: this comment is possibly no longer true as of
        the new (open-source and cross-platform) Compressonator. }
      if C = tcDxt1_RGB then // special options for tcDxt1_RGB
        CommandOptions.AddRange(
          ['-DXT1UseAlpha', '1', '-AlphaThreshold', '0.5']);

      RunCommandSimple(ExtractFilePath(TempPrefix),
        CommandExe, CommandOptions.ToArray);
    finally FreeAndNil(CommandOptions) end;

    CheckRenameFile(OutputTempFile, OutputFile);
    CheckDeleteFile(InputFlippedFile, true);
  end;

  procedure PVRTexTool(const InputFile, OutputFile: string;
    const C: TTextureCompression; const MipmapsLevel: Cardinal;
    const CompressionNameForTool: string);
  var
    ToolExe: string;
  begin
    ToolExe := FindExeCastleTool('PVRTexToolCLI');
    {$ifdef UNIX}
    { Try the standard installation path on Linux.
      On x86_64, try the 64-bit version first, otherwise fallback on 32-bit. }
    {$ifdef CPU64}
    TryToolExe(ToolExe, '/opt/Imagination/PowerVR_Graphics/PowerVR_Tools/PVRTexTool/CLI/Linux_x86_64/PVRTexToolCLI');
    {$endif}
    TryToolExe(ToolExe, '/opt/Imagination/PowerVR_Graphics/PowerVR_Tools/PVRTexTool/CLI/Linux_x86_32/PVRTexToolCLI');
    {$endif}
    { otherwise, assume it's on $PATH }
    TryToolExePath(ToolExe, 'PVRTexToolCLI', C);

    RunCommandSimple(ToolExe, [
      '-f', CompressionNameForTool,
      '-q', 'pvrtcbest',
      '-m', IntToStr(MipmapsLevel),
      { On iOS, it seems that PVRTC textures must be square.
        See
        - https://en.wikipedia.org/wiki/PVRTC
        - https://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/TextureTool/TextureTool.html
        But this is only an Apple implementation limitation, not a limitation
        of PVRTC1 compression.
        More info on this compression on
        - http://cdn.imgtec.com/sdk-documentation/PVRTC+%26+Texture+Compression.User+Guide.pdf
        - http://blog.imgtec.com/powervr/pvrtc2-taking-texture-compression-to-a-new-dimension

        In practice, forcing texture here to be square is very bad:
        - If a texture is addressed from the top, e.g. in Spine atlas file,
          then it's broken now. So using a texture atlases like 1024x512 from Spine
          would be broken.
        - ... and there's no sensible solution to the above problem.
          We could shift the texture, but then what if something addresses
          it from the bottom?
        - What if something (VRML/X3D or Collada texture coords) addresses
          texture in 0...1 range?
        - To fully work with it, we would have to store original texture
          size somewhere, and it's shift with regards to new compressed texture,
          and support it everywhere where we "interpret" texture coordinates
          (like when reading Spine atlas, or in shaders when sampling
          texture coordinates). Absolutely ugly.

        So, don't do this! Allow rectangular PVRTC textures!
      }
      // '-squarecanvas', '+' ,

      { TODO: use "-flip y" only when
        - TextureCompressionInfo[C].DDSFlipped (it is false for DXTn)
        - OutputFile is DDS.

        If OutputFile is KTX, then always use
        '-flip' 'y,flag'
        which means that file should be ordered bottom-to-top (and marked as such
        in the KTX header). This means it can be read in an efficient way.
        Using KTX requires some improvements to CastleAutoGenerated.xml
        first (to mark that we were able to generate KTX).
      }
      '-flip', 'y',

      '-i', InputFile,
      '-o', OutputFile
    ]);
  end;

  procedure AstcEncTool(const InputFile, OutputFile: String;
    const C: TTextureCompression; const MipmapsLevel: Cardinal;
    const CompressionNameForTool: String;
    const ColorspaceOption: String);
  var
    ToolExe: String;
    ToolName: String;
  begin
    if MipmapsLevel > 1 then
      raise Exception.CreateFmt('astcenc tool doesn''t support generating mipmaps, cannot generate %s->%s with mipmaps level %d', [
        InputFile,
        OutputFile,
        MipmapsLevel
      ]);

    ToolName := 'astcenc';
    {$ifdef CPU64}
      ToolName := 'astcenc-sse2'; // https://github.com/ARM-software/astc-encoder says this will always work on a 64-bit processor
      {$ifdef HAS_CPU_UNIT}
        //ToolName := 'astcenc-none'; // I have no idea what is it
        {$if ((FPC_VERSION = 3) and (FPC_RELEASE >= 3)) or (FPC_VERSION > 3)}
        if SSE41Support and POPCNTSupport then
          ToolName := 'astcenc-sse4.1';
        if AVX2Support and SSE42Support and POPCNTSupport and F16CSupport then
          ToolName := 'astcenc-avx2';
        {$endif}
      {$endif}
    {$endif}

    ToolExe := FindExeCastleTool(ToolName);
    TryToolExePath(ToolExe, ToolName, C);

    RunCommandSimple(ToolExe,
      [ColorspaceOption,
       InputFile,
       OutputFile,
       CompressionNameForTool,
       '-exhaustive',
       '-yflip']);
  end;

  procedure NVCompress(const InputFile, OutputFile: string;
    const C: TTextureCompression; const MipmapsLevel: Cardinal;
    const CompressionNameForTool: string);
  var
    ToolExe: string;
    CommandOptions: TCastleStringList;
  begin
    ToolExe := FindExeCastleTool('nvcompress');

    { assume it's on $PATH }
    TryToolExePath(ToolExe, 'nvcompress', C);

    CommandOptions := TCastleStringList.Create;
    try
      CommandOptions.AddRange([
        '-' + CompressionNameForTool,
        InputFile,
        OutputFile
      ]);
      if MipmapsLevel <= 1 then
      begin
        CommandOptions.AddRange(['-nomips']);
      end else
      begin
        WritelnWarning('nvcompress doesn''t allow to select mipmaps level to generate, generating %s->%s with default mipmaps level of nvcompress', [
          InputFile,
          OutputFile
        ]);
      end;
      RunCommandSimple(ToolExe, CommandOptions.ToArray);
    finally FreeAndNil(CommandOptions) end;
  end;

  procedure NVCompress_FallbackCompressonator(
    const InputFile, OutputFile: string;
    const C: TTextureCompression; const MipmapsLevel: Cardinal;
    const CompressionNameForNVCompress,
          CompressionNameForCompressonator: string);
  begin
    try
      NVCompress(InputFile, OutputFile, C, MipmapsLevel, CompressionNameForNVCompress);
      Exit; // if there was no ECannotFindTool exception, then success: exit
    except
      on E: ECannotFindTool do
        Writeln('Cannot find nvcompress executable. Falling back to Compressonator.');
    end;

    Compressonator(InputFile, OutputFile, C, MipmapsLevel, CompressionNameForCompressonator);
  end;

  { Convert both URLs to filenames and check whether output should be updated.
    In any case, makes appropriate message to user.
    If the file needs to be updated, makes sure it's output directory exists. }
  function CheckNeedsUpdate(const InputUrl, OutputUrl: String; out InputFile, OutputFile: string;
    const ContentAlreadyProcessed: boolean): boolean;
  begin
    InputFile := UriToFilenameSafe(InputUrl);
    OutputFile := UriToFilenameSafe(OutputUrl);

    { Previously, instead of checking "not ContentAlreadyProcessed",
      we were checking modification times:
      "(FileAge(OutputFile) < FileAge(InputFile))".
      But this was not working perfectly -- updating files from version control
      makes the modification times not-100%-reliable for this. }

    Result := (not RegularFileExists(OutputFile)) or (not ContentAlreadyProcessed);
    if Result then
    begin
      Writeln(Format('Updating "%s" from input "%s"', [OutputFile, InputFile]));
      CheckForceDirectories(ExtractFilePath(OutputFile));
    end else
    begin
      if Verbose then
        Writeln(Format('No need to update "%s"', [OutputFile]));
    end;
  end;

  procedure UpdateTextureScale(const InputUrl, OutputUrl: String;
    const Scale: Cardinal; var Stats: TStats;
    const ContentAlreadyProcessed: boolean);
  const
    // equivalent of GLTextureMinSize, but for TextureLoadingScale, not for GLTextureScale
    TextureMinSize = 16;
  var
    InputFile, OutputFile: string;
    Image: TCastleImage;
    NewWidth, NewHeight: Integer;
    NewScale: Cardinal;
    TimeStart: TProcessTimerResult;
  begin
    if CheckNeedsUpdate(InputUrl, OutputUrl, InputFile, OutputFile, ContentAlreadyProcessed) then
    begin
      Inc(Stats.DownscalingCount);
      TimeStart := ProcessTimer;

      Image := LoadImage(InputUrl);
      try
        NewWidth := Image.Width;
        NewHeight := Image.Height;
        NewScale := 1;
        while (NewWidth shr 1 >= TextureMinSize) and
              (NewHeight shr 1 >= TextureMinSize) and
              (NewScale < Scale) do
        begin
          NewWidth := NewWidth shr 1;
          NewHeight := NewHeight shr 1;
          Inc(NewScale);
        end;
        if Verbose then
          Writeln(Format('Resizing "%s" from %dx%d to %dx%d',
            [InputUrl, Image.Width, Image.Height, NewWidth, NewHeight]));
        Image.Resize(NewWidth, NewHeight, BestInterpolation);
        SaveImage(Image, OutputUrl);
      finally FreeAndNil(Image) end;

      Stats.DownscalingTime := Stats.DownscalingTime + TimeStart.ElapsedTime;
    end;
  end;

  { Like UpdateTextureScale, and also record the output in AutoGeneratedTex.Generated }
  procedure UpdateTextureScaleWhole(
    const AutoGeneratedTex: TAutoGenerated.TTexture;
    const InputUrl, OutputUrl: String;
    const Scale: TScale; var Stats: TStats;
    const ContentAlreadyProcessed: Boolean);
  var
    Generated: TAutoGenerated.TGeneratedTexture;
  begin
    UpdateTextureScale(InputUrl, OutputUrl, Scale.Value, Stats, ContentAlreadyProcessed);

    { Using Low(TTextureCompression), it should not matter when Compression = false. }
    Generated := AutoGeneratedTex.Generated(false, Low(TTextureCompression), Scale.Value);
    Generated.Url := MakeUrlRelativeToData(Project, OutputUrl);
    Generated.Platforms := Scale.Platforms;
    Generated.Used := true;
  end;

  procedure UpdateTextureCompress(const InputUrl, OutputUrl: String;
    const C: TTextureCompression; const MipmapsLevel: Cardinal;
    var Stats: TStats; const ContentAlreadyProcessed: boolean);
  var
    InputFile, OutputFile: string;
    TimeStart: TProcessTimerResult;
  begin
    if CheckNeedsUpdate(InputUrl, OutputUrl, InputFile, OutputFile, ContentAlreadyProcessed) then
    begin
      Inc(Stats.CompressionCount);
      TimeStart := ProcessTimer;

      case C of
        { For Compressonator DXT1:
          We have special handling for C = tcDxt1_RGB versus tcDxt1_RGBA,
          they will be handled differently, even though they are both called 'DXT1'. }
        tcDxt1_RGB : NVCompress_FallbackCompressonator(InputFile, OutputFile, C, MipmapsLevel, 'bc1' , 'DXT1');
        tcDxt1_RGBA: NVCompress_FallbackCompressonator(InputFile, OutputFile, C, MipmapsLevel, 'bc1a', 'DXT1');
        tcDxt3     : NVCompress_FallbackCompressonator(InputFile, OutputFile, C, MipmapsLevel, 'bc2' , 'DXT3');
        tcDxt5     : NVCompress_FallbackCompressonator(InputFile, OutputFile, C, MipmapsLevel, 'bc3' , 'DXT5');

        tcATITC_RGB                   : Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ATC_RGB'              );
        tcATITC_RGBA_InterpolatedAlpha: Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ATC_RGBA_Interpolated');
        tcATITC_RGBA_ExplicitAlpha    : Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ATC_RGBA_Explicit'    );

        // format names for PVRTexTool from https://docs.imgtec.com/oxy_ex-2/UtilitiesSrc/PVRTexTool/Documentation/PVRTexTool_Manual/topics/PVRTexTool%20CLI/command_line_options.html
        tcPvrtc1_4bpp_RGB:  PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'PVRTCI_4BPP_RGB');
        tcPvrtc1_2bpp_RGB:  PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'PVRTCI_2BPP_RGB');
        tcPvrtc1_4bpp_RGBA: PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'PVRTCI_4BPP_RGBA');
        tcPvrtc1_2bpp_RGBA: PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'PVRTCI_2BPP_RGBA');
        tcPvrtc2_4bpp:      PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'PVRTCII_4BPP');
        tcPvrtc2_2bpp:      PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'PVRTCII_2BPP');

        tcETC1:             PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ETC1');
                      // or Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ETC_RGB');

        {$ifdef USE_ASTCENC}
        tcASTC_4x4_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '4x4', '-cl');
        tcASTC_5x4_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '5x4', '-cl');
        tcASTC_5x5_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '5x5', '-cl');
        tcASTC_6x5_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '6x5', '-cl');
        tcASTC_6x6_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '6x6', '-cl');
        tcASTC_8x5_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '8x5', '-cl');
        tcASTC_8x6_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '8x6', '-cl');
        tcASTC_8x8_RGBA:           AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '8x8', '-cl');
        tcASTC_10x5_RGBA:          AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x5', '-cl');
        tcASTC_10x6_RGBA:          AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x6', '-cl');
        tcASTC_10x8_RGBA:          AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x8', '-cl');
        tcASTC_10x10_RGBA:         AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x10', '-cl');
        tcASTC_12x10_RGBA:         AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '12x10', '-cl');
        tcASTC_12x12_RGBA:         AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '12x12', '-cl');

        tcASTC_4x4_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '4x4', '-ch');
        tcASTC_5x4_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '5x4', '-ch');
        tcASTC_5x5_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '5x5', '-ch');
        tcASTC_6x5_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '6x5', '-ch');
        tcASTC_6x6_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '6x6', '-ch');
        tcASTC_8x5_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '8x5', '-ch');
        tcASTC_8x6_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '8x6', '-ch');
        tcASTC_8x8_SRGB8_ALPHA8:   AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '8x8', '-ch');
        tcASTC_10x5_SRGB8_ALPHA8:  AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x5', '-ch');
        tcASTC_10x6_SRGB8_ALPHA8:  AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x6', '-ch');
        tcASTC_10x8_SRGB8_ALPHA8:  AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x8', '-ch');
        tcASTC_10x10_SRGB8_ALPHA8: AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '10x10', '-ch');
        tcASTC_12x10_SRGB8_ALPHA8: AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '12x10', '-ch');
        tcASTC_12x12_SRGB8_ALPHA8: AstcEncTool(InputFile, OutputFile, C, MipmapsLevel, '12x12', '-ch');

        {$else}
        // tcASTC_4x4_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_4x4');
        // tcASTC_5x4_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_5x4');
        // tcASTC_5x5_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_5x5');
        // tcASTC_6x5_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_6x5');
        // tcASTC_6x6_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_6x6');
        // tcASTC_8x5_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_8x5');
        // tcASTC_8x6_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_8x6');
        // tcASTC_8x8_RGBA:           PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_8x8');
        // tcASTC_10x5_RGBA:          PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x5');
        // tcASTC_10x6_RGBA:          PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x6');
        // tcASTC_10x8_RGBA:          PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x8');
        // tcASTC_10x10_RGBA:         PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x10');
        // tcASTC_12x10_RGBA:         PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_12x10');
        // tcASTC_12x12_RGBA:         PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_12x12');

        // tcASTC_4x4_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_4x4,UBN,sRGB');
        // tcASTC_5x4_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_5x4,UBN,sRGB');
        // tcASTC_5x5_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_5x5,UBN,sRGB');
        // tcASTC_6x5_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_6x5,UBN,sRGB');
        // tcASTC_6x6_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_6x6,UBN,sRGB');
        // tcASTC_8x5_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_8x5,UBN,sRGB');
        // tcASTC_8x6_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_8x6,UBN,sRGB');
        // tcASTC_8x8_SRGB8_ALPHA8:   PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_8x8,UBN,sRGB');
        // tcASTC_10x5_SRGB8_ALPHA8:  PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x5,UBN,sRGB');
        // tcASTC_10x6_SRGB8_ALPHA8:  PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x6,UBN,sRGB');
        // tcASTC_10x8_SRGB8_ALPHA8:  PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x8,UBN,sRGB');
        // tcASTC_10x10_SRGB8_ALPHA8: PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_10x10,UBN,sRGB');
        // tcASTC_12x10_SRGB8_ALPHA8: PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_12x10,UBN,sRGB');
        // tcASTC_12x12_SRGB8_ALPHA8: PVRTexTool(InputFile, OutputFile, C, MipmapsLevel, 'ASTC_12x12,UBN,sRGB');

        tcASTC_4x4_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '4x4');
        tcASTC_5x4_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '5x4');
        tcASTC_5x5_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '5x5');
        tcASTC_6x5_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '6x5');
        tcASTC_6x6_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '6x6');
        tcASTC_8x5_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '8x5');
        tcASTC_8x6_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '8x6');
        tcASTC_8x8_RGBA:           Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '8x8');
        tcASTC_10x5_RGBA:          Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x5');
        tcASTC_10x6_RGBA:          Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x6');
        tcASTC_10x8_RGBA:          Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x8');
        tcASTC_10x10_RGBA:         Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x10');
        tcASTC_12x10_RGBA:         Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '12x10');
        tcASTC_12x12_RGBA:         Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '12x12');

        // TODO: pass here special option for SRGB8_ALPHA8
        tcASTC_4x4_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '4x4');
        tcASTC_5x4_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '5x4');
        tcASTC_5x5_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '5x5');
        tcASTC_6x5_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '6x5');
        tcASTC_6x6_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '6x6');
        tcASTC_8x5_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '8x5');
        tcASTC_8x6_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '8x6');
        tcASTC_8x8_SRGB8_ALPHA8:   Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '8x8');
        tcASTC_10x5_SRGB8_ALPHA8:  Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x5');
        tcASTC_10x6_SRGB8_ALPHA8:  Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x6');
        tcASTC_10x8_SRGB8_ALPHA8:  Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x8');
        tcASTC_10x10_SRGB8_ALPHA8: Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '10x10');
        tcASTC_12x10_SRGB8_ALPHA8: Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '12x10');
        tcASTC_12x12_SRGB8_ALPHA8: Compressonator(InputFile, OutputFile, C, MipmapsLevel, 'ASTC', '12x12');

        {$endif}

        {$ifndef COMPILER_CASE_ANALYSIS}
        else WritelnWarning('GPUCompression', Format('Compressing to GPU format %s not implemented (to update "%s")',
          [TextureCompressionToString(C), OutputFile]));
        {$endif}
      end;

      Stats.CompressionTime := Stats.CompressionTime + TimeStart.ElapsedTime;
    end;
  end;

  { Read texture sizes, place them in TAutoGenerated.TTexture fields. }
  procedure UpdateTextureDimensions(const AutoGeneratedTex: TAutoGenerated.TTexture;
    const TextureUrl: String; var Stats: TStats);
  var
    Image: TCastleImage;
    TimeStart: TProcessTimerResult;
  begin
    Inc(Stats.DimensionsCount);
    TimeStart := ProcessTimer;

    Image := LoadImage(TextureUrl);
    try
      AutoGeneratedTex.Width := Image.Width;
      AutoGeneratedTex.Height := Image.Height;
      AutoGeneratedTex.Depth := Image.Depth;
    finally FreeAndNil(Image) end;

    Stats.DimensionsTime := Stats.DimensionsTime + TimeStart.ElapsedTime;
  end;

  { Like UpdateTextureCompress, and also record the output in AutoGeneratedTex.Generated }
  procedure UpdateTextureCompressWhole(const AutoGeneratedTexInfo: TAutoGeneratedTextures;
    const AutoGeneratedTex: TAutoGenerated.TTexture;
    const C: TTextureCompression;
    const OriginalTextureUrl, UncompressedUrl: String;
    const Scale: Cardinal;
    var Stats: TStats;
    const ContentAlreadyProcessed: Boolean;
    const Platforms: TCastlePlatforms);
  var
    CompressedUrl: String;
    Generated: TAutoGenerated.TGeneratedTexture;
  begin
    if (not TextureCompressionInfo[C].DDSFlipped) and
       (TextureCompressionInfo[C].FileExtension = '.dds') and
       (AutoGeneratedTex.Height > 4) and
       (AutoGeneratedTex.Height mod 4 <> 0) then
      WritelnWarning('Generating DDS from "%s" with size %dx%d with GPU compression "%s". It will not be read correctly, as we cannot flip it back at loading (and it is expected for this compression format), because the height is not a multiple of 4 (or 1,2,3). We advise to exclude this file from compression.', [
        OriginalTextureUrl,
        AutoGeneratedTex.Width,
        AutoGeneratedTex.Height,
        TextureCompressionInfo[C].Name
      ]);

    CompressedUrl := AutoGeneratedTexInfo.GeneratedTextureUrl(OriginalTextureUrl, true, C, Scale);
    { We use the UncompressedUrl that was updated previously.
      This way there's no need to scale the texture here. }
    UpdateTextureCompress(UncompressedUrl, CompressedUrl, C,
      AutoGeneratedTexInfo.MipmapsLevel, Stats, ContentAlreadyProcessed);

    Generated := AutoGeneratedTex.Generated(true, C, Scale);
    Generated.Url := MakeUrlRelativeToData(Project, CompressedUrl);
    Generated.Platforms := Platforms;
    Generated.Used := true;
  end;

  procedure UpdateTexture(
    const OriginalTextureUrl: String;
    { Determines how the texture should be processed (comes from material_properties.xml) }
    const AutoGeneratedTexInfo: TAutoGeneratedTextures;
    var Stats: TStats;
    { Determines how were the textures processed now (comes from CastleAutoGenerated.xml) }
    const AutoGenerated: TAutoGenerated);
  var
    UncompressedUrl: String;
    C: TTextureCompression;
    Scale: TScale;
    ToGenerate: TTextureCompressionsToGenerate;
    Compressions: TCompressionsMap;
    CompressionPair: TCompressionsMap.TDictionaryPair;
    RelativeOriginalTextureUrl, Hash: String;
    ContentAlreadyProcessed: Boolean;
    { Determines how was the texture processed now (comes from CastleAutoGenerated.xml) }
    AutoGeneratedTex: TAutoGenerated.TTexture;
    MipmapsLevel: Cardinal;
  begin
    Inc(Stats.Count);

    Hash := CalculateHash(OriginalTextureUrl, Stats);

    // calculate and compare Hash with AutoGenerated
    RelativeOriginalTextureUrl := MakeUrlRelativeToData(Project, OriginalTextureUrl);
    AutoGeneratedTex := AutoGenerated.Texture(RelativeOriginalTextureUrl,
      AutoGeneratedTexInfo.OriginalPlatforms, true);
    AutoGeneratedTex.Used := true;
    MipmapsLevel := AutoGeneratedTexInfo.MipmapsLevel;
    ContentAlreadyProcessed :=
      (AutoGeneratedTex.Hash = Hash) and
      (AutoGeneratedTex.MipmapsLevel = MipmapsLevel);

    { We could just Exit now if ContentAlreadyProcessed.
      But it's safer to continue, and check do the indicated (generated) files exist.
      If not, we will generate them, even when hash was already OK. }

    if (not ContentAlreadyProcessed) or
       { old filed before we added dimensions }
       ( (AutoGeneratedTex.Width = 0) and
         (AutoGeneratedTex.Height = 0) and
         (AutoGeneratedTex.Depth = 0) ) then
    begin
      // store new Hash in AutoGenerated
      AutoGeneratedTex.Hash := Hash;
      UpdateTextureDimensions(AutoGeneratedTex, OriginalTextureUrl, Stats);
    end;

    for Scale in AutoGeneratedTexInfo.Scales do
    begin
      if (Scale.Value <> 1) or AutoGeneratedTexInfo.TrivialUncompressedConvert then
      begin
        UncompressedUrl := AutoGeneratedTexInfo.GeneratedTextureUrl(OriginalTextureUrl, false, Low(TTextureCompression), Scale.Value);
        UpdateTextureScaleWhole(AutoGeneratedTex, OriginalTextureUrl, UncompressedUrl, Scale, Stats, ContentAlreadyProcessed);
      end else
        UncompressedUrl := OriginalTextureUrl;

      ToGenerate := AutoGeneratedTexInfo.CompressedFormatsToGenerate;
      if ToGenerate <> nil then
      begin
        Compressions := ToGenerate.Compressions;

        { TODO: we perform AutoDetectDxt call every time.
          Instead, information in auto_generated.xml could allow us to avoid it. }
        if ToGenerate.DxtAutoDetect then
          if ToGenerate.DxtAutoDetectPlatforms * Scale.Platforms <> [] then
          begin
            C := AutoDetectDxt(OriginalTextureUrl, Stats);
            UpdateTextureCompressWhole(AutoGeneratedTexInfo, AutoGeneratedTex, C, OriginalTextureUrl, UncompressedUrl, Scale.Value, Stats, ContentAlreadyProcessed,
              ToGenerate.DxtAutoDetectPlatforms * Scale.Platforms);
          end;

        for CompressionPair in Compressions do
          if CompressionPair.Value * Scale.Platforms <> [] then
          begin
            C := CompressionPair.Key;
            UpdateTextureCompressWhole(AutoGeneratedTexInfo, AutoGeneratedTex, C, OriginalTextureUrl, UncompressedUrl, Scale.Value, Stats, ContentAlreadyProcessed,
              CompressionPair.Value * Scale.Platforms);
          end;
      end;
    end;
  end;

var
  Textures: TCastleStringList;
  I: Integer;
  AutoGeneratedUrl, MatPropsUrl: String;
  MatProps: TMaterialProperties;
  Stats: TStats;
  AutoGenerated: TAutoGenerated;
begin
  if not Project.DataExists then
  begin
    WritelnVerbose('Material properties file does not exist in data (because <data exists="false"/> in CastleEngineManifest.xml), so not compressing anything.');
    Exit;
  end;

  MatPropsUrl := FilenameToUriSafe(Project.DataPath + 'material_properties.xml');
  if not URIFileExists(MatPropsUrl) then
  begin
    WritelnVerbose('Material properties file does not exist, so not compressing anything: ' + MatPropsUrl);
    Exit;
  end;

  FillChar(Stats, SizeOf(Stats), 0);

  AutoGeneratedUrl := FilenameToUriSafe(Project.DataPath + TAutoGenerated.FileName);
  AutoGenerated := TAutoGenerated.Create;
  try
    AutoGenerated.LoadFromFile(AutoGeneratedUrl);

    MatProps := TMaterialProperties.Create(false);
    try
      MatProps.Url := MatPropsUrl;
      Textures := MatProps.AutoGeneratedTextures;
      try
        for I := 0 to Textures.Count - 1 do
          UpdateTexture(Textures[I], Textures.Objects[I] as TAutoGeneratedTextures,
            Stats, AutoGenerated);
      finally FreeAndNil(Textures) end;
    finally FreeAndNil(MatProps) end;

    AutoGenerated.CleanUnused(true);
    AutoGenerated.CleanNotExistingFiles(FilenameToUriSafe(Project.DataPath), true);
    AutoGenerated.SaveToFile(AutoGeneratedUrl);
  finally FreeAndNil(AutoGenerated) end;

  Write(Format(
    'Automatic texture generation completed:' + NL +
    '  %d textures considered to be compressed and/or downscaled.' + NL +
    '  Hashes calculation time: %f seconds.' + NL +
    '  Dimensions calculations: %d in %f seconds.' + NL +
    '  Compressions done: %d in %f seconds.' + NL +
    '  Downscaling done: %d in %f seconds.' + NL +
    '  DXTn auto-detection done: %d in %f seconds.' + NL, [
    Stats.Count,
    Stats.HashTime,
    Stats.DimensionsCount,
    Stats.DimensionsTime,
    Stats.CompressionCount,
    Stats.CompressionTime,
    Stats.DownscalingCount,
    Stats.DownscalingTime,
    Stats.DxtAutoDetectCount,
    Stats.DxtAutoDetectTime
  ]));
end;

procedure CleanDir(const FileInfo: TFileInfo; Data: Pointer;
  var StopSearch: boolean);
begin
  Writeln('Deleting ', FileInfo.AbsoluteName);
  RemoveNonEmptyDir(FileInfo.AbsoluteName);
end;

procedure AutoGenerateCleanAll(const Project: TCastleProject);

  procedure TryDeleteFile(const FileName: string);
  begin
    if RegularFileExists(FileName) then
    begin
      Writeln('Deleting ' + FileName);
      CheckDeleteFile(FileName);
    end;
  end;

begin
  if Project.DataExists then
  begin
    FindFiles(Project.DataPath, TAutoGenerated.AutoGeneratedDirName, true,
      @CleanDir, nil, [ffRecursive]);

    TryDeleteFile(Project.DataPath + TAutoGenerated.FileName);
  end;
end;

type
  TAutoGeneratedCleanUnusedHandler = class
    Project: TCastleProject;
    AutoGenerated: TAutoGenerated;
    destructor Destroy; override;
    procedure FindFilesCallback(const FileInfo: TFileInfo; var StopSearch: boolean);
  end;

procedure TAutoGeneratedCleanUnusedHandler.FindFilesCallback(
  const FileInfo: TFileInfo; var StopSearch: boolean);
var
  UrlInData: String;
begin
  UrlInData := ExtractRelativePath(Project.DataPath, FileInfo.AbsoluteName);
  UrlInData := StringReplace(UrlInData, '\', '/', [rfReplaceAll]);

  if (Pos('/' + TAutoGenerated.AutoGeneratedDirName + '/', UrlInData) <> 0) and
     (not AutoGenerated.Used(UrlInData)) then
  begin
    WritelnVerbose('Deleting unused ' + FileInfo.AbsoluteName);
    CheckDeleteFile(FileInfo.AbsoluteName, true);
  end;
end;

destructor TAutoGeneratedCleanUnusedHandler.Destroy;
begin
  FreeAndNil(AutoGenerated);
  inherited;
end;

procedure AutoGenerateCleanUnused(const Project: TCastleProject);
var
  AutoGeneratedUrl: String;
  Handler: TAutoGeneratedCleanUnusedHandler;
begin
  if Project.DataExists then
  begin
    Handler := TAutoGeneratedCleanUnusedHandler.Create;
    try
      Handler.Project := Project;

      AutoGeneratedUrl := FilenameToUriSafe(Project.DataPath + TAutoGenerated.FileName);
      Handler.AutoGenerated := TAutoGenerated.Create;
      Handler.AutoGenerated.LoadFromFile(AutoGeneratedUrl);

      FindFiles(Project.DataPath, '*', false, @Handler.FindFilesCallback, [ffRecursive]);
    finally FreeAndNil(Handler) end;
  end;
end;

end.