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
    function GetColor: TCastleColor;
    procedure SetColor(const Value: TCastleColor);
    function GetTexture: TAbstractTextureNode;
    procedure SetTexture(const Value: TAbstractTextureNode);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdColor: TSFColorRGBA;
    { Internal wrapper for property @code(Color). This wrapper API may change, we advise to access simpler @code(Color) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdColor: TSFColorRGBA read FFdColor;
    { Color that is multiplied by the texture color. Opaque white by default. Note that the alpha component of this color matters (just like the alpha channel of the texture in @link(Texture)). If the resulting image is partially-transparent, it will be mixed with black underneath. }
    property Color: TCastleColor read GetColor write SetColor;

    strict private FFdTexture: TSFNode;
    { Internal wrapper for property @code(Texture). This wrapper API may change, we advise to access simpler @code(Texture) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdTexture: TSFNode read FFdTexture;
    { Texture displayed in a full-screen quad. Only 2D single-texture nodes are supported now. If you leave this as @nil, the TImageBackgroundNode has no visible effect. }
    property Texture: TAbstractTextureNode read GetTexture write SetTexture;

    strict private FFdTexCoords: TMFVec2f;
    { Internal wrapper for property @code(TexCoords). This wrapper API may change, we advise to access simpler @code(TexCoords) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdTexCoords: TMFVec2f read FFdTexCoords;
    { Texture coordinates of the full-screen quad. By default they use the whole texture area: @orderedList( @item(Vector2(0, 0),) @item(Vector2(1, 0),) @item(Vector2(1, 1),) @item(Vector2(0, 1)) ) It is undefined what happens if there are not exactly 4 items. }
    procedure SetTexCoords(const Value: array of TVector2); overload;
    { Texture coordinates of the full-screen quad. By default they use the whole texture area: @orderedList( @item(Vector2(0, 0),) @item(Vector2(1, 0),) @item(Vector2(1, 1),) @item(Vector2(0, 1)) ) It is undefined what happens if there are not exactly 4 items. }
    procedure SetTexCoords(const Value: TVector2List); overload;

{$endif read_interface}

{$ifdef read_implementation}

{ TImageBackgroundNode ----------------------------------------------- }

function TImageBackgroundNode.GetColor: TCastleColor;
begin
  Result := FdColor.Value;
end;

procedure TImageBackgroundNode.SetColor(const Value: TCastleColor);
begin
  FdColor.Send(Value);
end;

function TImageBackgroundNode.GetTexture: TAbstractTextureNode;
begin
  if FdTexture.Value is TAbstractTextureNode then
    Result := TAbstractTextureNode(FdTexture.Value)
  else
    Result := nil;
end;

procedure TImageBackgroundNode.SetTexture(const Value: TAbstractTextureNode);
begin
  FdTexture.Send(Value);
end;

procedure TImageBackgroundNode.SetTexCoords(const Value: array of TVector2);
begin
  FdTexCoords.Send(Value);
end;

procedure TImageBackgroundNode.SetTexCoords(const Value: TVector2List);
begin
  FdTexCoords.Send(Value);
end;

class function TImageBackgroundNode.ClassX3DType: String;
begin
  Result := 'ImageBackground';
end;

procedure TImageBackgroundNode.CreateNode;
begin
  inherited;

  FFdColor := TSFColorRGBA.Create(Self, True, 'color', Vector4(1, 1, 1, 1));
   FdColor.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdColor);

  FFdTexture := TSFNode.Create(Self, True, 'texture', [TAbstractTextureNode]);
   FdTexture.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdTexture);

  FFdTexCoords := TMFVec2f.Create(Self, True, 'texCoords', [ Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1) ]);
   FdTexCoords.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdTexCoords);
end;

{$endif read_implementation}