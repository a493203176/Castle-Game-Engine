{ -*- buffer-read-only: t -*-

  Copyright 2015-2024 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Automatically generated node properties.

  Do not edit this file manually!
  To add new properties:
  - add them to the text files in tools/internal/x3d-nodes-to-pascal/nodes-specification/ ,
  - and regenerate include files by running x3d-nodes-to-pascal }

{$ifdef read_interface}

  strict private
    function GetEmissiveColor: TCastleColorRGB;
    procedure SetEmissiveColor(const Value: TCastleColorRGB);
    function GetEmissiveTexture: TAbstractSingleTextureNode;
    procedure SetEmissiveTexture(const Value: TAbstractSingleTextureNode);
    function GetEmissiveTextureMapping: String;
    procedure SetEmissiveTextureMapping(const Value: String);
    function GetNormalTexture: TAbstractTexture2DNode;
    procedure SetNormalTexture(const Value: TAbstractTexture2DNode);
    function GetNormalTextureMapping: String;
    procedure SetNormalTextureMapping(const Value: String);
    function GetNormalScale: Single;
    procedure SetNormalScale(const Value: Single);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdEmissiveColor: TSFColor;
    { Internal wrapper for property @code(EmissiveColor). This wrapper API may change, we advise to access simpler @code(EmissiveColor) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEmissiveColor: TSFColor read FFdEmissiveColor;
    {  }
    property EmissiveColor: TCastleColorRGB read GetEmissiveColor write SetEmissiveColor;

    strict private FFdEmissiveTexture: TSFNode;
    { Internal wrapper for property @code(EmissiveTexture). This wrapper API may change, we advise to access simpler @code(EmissiveTexture) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEmissiveTexture: TSFNode read FFdEmissiveTexture;
    {  }
    property EmissiveTexture: TAbstractSingleTextureNode read GetEmissiveTexture write SetEmissiveTexture;

    strict private FFdEmissiveTextureMapping: TSFString;
    { Internal wrapper for property @code(EmissiveTextureMapping). This wrapper API may change, we advise to access simpler @code(EmissiveTextureMapping) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEmissiveTextureMapping: TSFString read FFdEmissiveTextureMapping;
    {  }
    property EmissiveTextureMapping: String read GetEmissiveTextureMapping write SetEmissiveTextureMapping;

    strict private FFdNormalTexture: TSFNode;
    { Internal wrapper for property @code(NormalTexture). This wrapper API may change, we advise to access simpler @code(NormalTexture) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdNormalTexture: TSFNode read FFdNormalTexture;
    { Normalmap texture to perform bump mapping. See https://castle-engine.io/bump_mapping . }
    property NormalTexture: TAbstractTexture2DNode read GetNormalTexture write SetNormalTexture;

    strict private FFdNormalTextureMapping: TSFString;
    { Internal wrapper for property @code(NormalTextureMapping). This wrapper API may change, we advise to access simpler @code(NormalTextureMapping) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdNormalTextureMapping: TSFString read FFdNormalTextureMapping;
    { Determines texture coordinates used by @link(NormalTexture). }
    property NormalTextureMapping: String read GetNormalTextureMapping write SetNormalTextureMapping;

    strict private FFdNormalScale: TSFFloat;
    { Internal wrapper for property @code(NormalScale). This wrapper API may change, we advise to access simpler @code(NormalScale) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdNormalScale: TSFFloat read FFdNormalScale;
    { Emphasize (when > 1) or deemphasize (< 1) the effect of @link(NormalTexture) on the model. }
    property NormalScale: Single read GetNormalScale write SetNormalScale;

{$endif read_interface}

{$ifdef read_implementation}

{ TAbstractOneSidedMaterialNode ----------------------------------------------- }

function TAbstractOneSidedMaterialNode.GetEmissiveColor: TCastleColorRGB;
begin
  Result := FdEmissiveColor.Value;
end;

procedure TAbstractOneSidedMaterialNode.SetEmissiveColor(const Value: TCastleColorRGB);
begin
  FdEmissiveColor.Send(Value);
end;

function TAbstractOneSidedMaterialNode.GetEmissiveTexture: TAbstractSingleTextureNode;
begin
  if FdEmissiveTexture.Value is TAbstractSingleTextureNode then
    Result := TAbstractSingleTextureNode(FdEmissiveTexture.Value)
  else
    Result := nil;
end;

procedure TAbstractOneSidedMaterialNode.SetEmissiveTexture(const Value: TAbstractSingleTextureNode);
begin
  FdEmissiveTexture.Send(Value);
end;

function TAbstractOneSidedMaterialNode.GetEmissiveTextureMapping: String;
begin
  Result := FdEmissiveTextureMapping.Value;
end;

procedure TAbstractOneSidedMaterialNode.SetEmissiveTextureMapping(const Value: String);
begin
  FdEmissiveTextureMapping.Send(Value);
end;

function TAbstractOneSidedMaterialNode.GetNormalTexture: TAbstractTexture2DNode;
begin
  if FdNormalTexture.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdNormalTexture.Value)
  else
    Result := nil;
end;

procedure TAbstractOneSidedMaterialNode.SetNormalTexture(const Value: TAbstractTexture2DNode);
begin
  FdNormalTexture.Send(Value);
end;

function TAbstractOneSidedMaterialNode.GetNormalTextureMapping: String;
begin
  Result := FdNormalTextureMapping.Value;
end;

procedure TAbstractOneSidedMaterialNode.SetNormalTextureMapping(const Value: String);
begin
  FdNormalTextureMapping.Send(Value);
end;

function TAbstractOneSidedMaterialNode.GetNormalScale: Single;
begin
  Result := FdNormalScale.Value;
end;

procedure TAbstractOneSidedMaterialNode.SetNormalScale(const Value: Single);
begin
  FdNormalScale.Send(Value);
end;

class function TAbstractOneSidedMaterialNode.ClassX3DType: String;
begin
  Result := 'X3DOneSidedMaterialNode';
end;

procedure TAbstractOneSidedMaterialNode.CreateNode;
begin
  inherited;

  FFdEmissiveColor := TSFColor.Create(Self, True, 'emissiveColor', Vector3(0, 0, 0));
   FdEmissiveColor.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdEmissiveColor);

  FFdEmissiveTexture := TSFNode.Create(Self, True, 'emissiveTexture', [TAbstractSingleTextureNode]);
   FdEmissiveTexture.ChangeAlways := chEverything;
  AddField(FFdEmissiveTexture);

  FFdEmissiveTextureMapping := TSFString.Create(Self, True, 'emissiveTextureMapping', '');
   FdEmissiveTextureMapping.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdEmissiveTextureMapping);

  FFdNormalTexture := TSFNode.Create(Self, True, 'normalTexture', [TAbstractTexture2DNode]);
   FdNormalTexture.ChangeAlways := chEverything;
  AddField(FFdNormalTexture);

  FFdNormalTextureMapping := TSFString.Create(Self, True, 'normalTextureMapping', '');
   FdNormalTextureMapping.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdNormalTextureMapping);

  FFdNormalScale := TSFFloat.Create(Self, True, 'normalScale', 1);
   FdNormalScale.ChangeAlways := chEverything;
   FdNormalScale.MustBeNonnegative := true;
  AddField(FFdNormalScale);

  DefaultContainerField := 'material';
end;

{$endif read_implementation}