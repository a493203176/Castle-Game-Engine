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
    function GetRepeatS: Boolean;
    procedure SetRepeatS(const Value: Boolean);
    function GetRepeatT: Boolean;
    procedure SetRepeatT(const Value: Boolean);
    function GetRepeatR: Boolean;
    procedure SetRepeatR(const Value: Boolean);
    function GetTextureProperties: TTexturePropertiesNode;
    procedure SetTextureProperties(const Value: TTexturePropertiesNode);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdRepeatS: TSFBool;
    { Internal wrapper for property @code(RepeatS). This wrapper API may change, we advise to access simpler @code(RepeatS) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdRepeatS: TSFBool read FFdRepeatS;
    {  }
    property RepeatS: Boolean read GetRepeatS write SetRepeatS;

    strict private FFdRepeatT: TSFBool;
    { Internal wrapper for property @code(RepeatT). This wrapper API may change, we advise to access simpler @code(RepeatT) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdRepeatT: TSFBool read FFdRepeatT;
    {  }
    property RepeatT: Boolean read GetRepeatT write SetRepeatT;

    strict private FFdRepeatR: TSFBool;
    { Internal wrapper for property @code(RepeatR). This wrapper API may change, we advise to access simpler @code(RepeatR) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdRepeatR: TSFBool read FFdRepeatR;
    {  }
    property RepeatR: Boolean read GetRepeatR write SetRepeatR;

    strict private FFdTextureProperties: TSFNode;
    { Internal wrapper for property @code(TextureProperties). This wrapper API may change, we advise to access simpler @code(TextureProperties) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdTextureProperties: TSFNode read FFdTextureProperties;
    {  }
    property TextureProperties: TTexturePropertiesNode read GetTextureProperties write SetTextureProperties;

{$endif read_interface}

{$ifdef read_implementation}

{ TAbstractTexture3DNode ----------------------------------------------- }

function TAbstractTexture3DNode.GetRepeatS: Boolean;
begin
  Result := FdRepeatS.Value;
end;

procedure TAbstractTexture3DNode.SetRepeatS(const Value: Boolean);
begin
  FdRepeatS.Send(Value);
end;

function TAbstractTexture3DNode.GetRepeatT: Boolean;
begin
  Result := FdRepeatT.Value;
end;

procedure TAbstractTexture3DNode.SetRepeatT(const Value: Boolean);
begin
  FdRepeatT.Send(Value);
end;

function TAbstractTexture3DNode.GetRepeatR: Boolean;
begin
  Result := FdRepeatR.Value;
end;

procedure TAbstractTexture3DNode.SetRepeatR(const Value: Boolean);
begin
  FdRepeatR.Send(Value);
end;

function TAbstractTexture3DNode.GetTextureProperties: TTexturePropertiesNode;
begin
  if FdTextureProperties.Value is TTexturePropertiesNode then
    Result := TTexturePropertiesNode(FdTextureProperties.Value)
  else
    Result := nil;
end;

procedure TAbstractTexture3DNode.SetTextureProperties(const Value: TTexturePropertiesNode);
begin
  FdTextureProperties.Send(Value);
end;

class function TAbstractTexture3DNode.ClassX3DType: String;
begin
  Result := 'X3DTexture3DNode';
end;

procedure TAbstractTexture3DNode.CreateNode;
begin
  inherited;

  FFdRepeatS := TSFBool.Create(Self, False, 'repeatS', false);
   FdRepeatS.ChangeAlways := chTextureRendererProperties;
  AddField(FFdRepeatS);

  FFdRepeatT := TSFBool.Create(Self, False, 'repeatT', false);
   FdRepeatT.ChangeAlways := chTextureRendererProperties;
  AddField(FFdRepeatT);

  FFdRepeatR := TSFBool.Create(Self, False, 'repeatR', false);
   FdRepeatR.ChangeAlways := chTextureRendererProperties;
  AddField(FFdRepeatR);

  FFdTextureProperties := TSFNode.Create(Self, False, 'textureProperties', [TTexturePropertiesNode]);
   FdTextureProperties.ChangeAlways := chTextureRendererProperties;
  AddField(FFdTextureProperties);
end;

{$endif read_implementation}