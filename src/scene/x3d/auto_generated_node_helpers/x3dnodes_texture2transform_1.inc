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
    function GetTranslation: TVector2;
    procedure SetTranslation(const Value: TVector2);
    function GetRotation: Single;
    procedure SetRotation(const Value: Single);
    function GetScaleFactor: TVector2;
    procedure SetScaleFactor(const Value: TVector2);
    function GetCenter: TVector2;
    procedure SetCenter(const Value: TVector2);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;
    class function ForVRMLVersion(const Version: TX3DVersion): Boolean; override;

    strict private FFdTranslation: TSFVec2f;
    { Internal wrapper for property @code(Translation). This wrapper API may change, we advise to access simpler @code(Translation) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdTranslation: TSFVec2f read FFdTranslation;
    {  }
    property Translation: TVector2 read GetTranslation write SetTranslation;

    strict private FFdRotation: TSFFloat;
    { Internal wrapper for property @code(Rotation). This wrapper API may change, we advise to access simpler @code(Rotation) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdRotation: TSFFloat read FFdRotation;
    {  }
    property Rotation: Single read GetRotation write SetRotation;

    strict private FFdScaleFactor: TSFVec2f;
    { Internal wrapper for property @code(ScaleFactor). This wrapper API may change, we advise to access simpler @code(ScaleFactor) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdScaleFactor: TSFVec2f read FFdScaleFactor;
    {  }
    property ScaleFactor: TVector2 read GetScaleFactor write SetScaleFactor;

    strict private FFdCenter: TSFVec2f;
    { Internal wrapper for property @code(Center). This wrapper API may change, we advise to access simpler @code(Center) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdCenter: TSFVec2f read FFdCenter;
    {  }
    property Center: TVector2 read GetCenter write SetCenter;

{$endif read_interface}

{$ifdef read_implementation}

{ TTexture2TransformNode_1 ----------------------------------------------- }

function TTexture2TransformNode_1.GetTranslation: TVector2;
begin
  Result := FdTranslation.Value;
end;

procedure TTexture2TransformNode_1.SetTranslation(const Value: TVector2);
begin
  FdTranslation.Send(Value);
end;

function TTexture2TransformNode_1.GetRotation: Single;
begin
  Result := FdRotation.Value;
end;

procedure TTexture2TransformNode_1.SetRotation(const Value: Single);
begin
  FdRotation.Send(Value);
end;

function TTexture2TransformNode_1.GetScaleFactor: TVector2;
begin
  Result := FdScaleFactor.Value;
end;

procedure TTexture2TransformNode_1.SetScaleFactor(const Value: TVector2);
begin
  FdScaleFactor.Send(Value);
end;

function TTexture2TransformNode_1.GetCenter: TVector2;
begin
  Result := FdCenter.Value;
end;

procedure TTexture2TransformNode_1.SetCenter(const Value: TVector2);
begin
  FdCenter.Send(Value);
end;

class function TTexture2TransformNode_1.ForVRMLVersion(const Version: TX3DVersion): Boolean;
begin
  Result := Version.Major <= 1; // parse this node only in VRML 1.0 and Inventor files
end;

class function TTexture2TransformNode_1.ClassX3DType: String;
begin
  Result := 'Texture2Transform';
end;

procedure TTexture2TransformNode_1.CreateNode;
begin
  inherited;

  FFdTranslation := TSFVec2f.Create(Self, True, 'translation', Vector2(0, 0));
   FdTranslation.ChangeAlways := chEverything;
  AddField(FFdTranslation);

  FFdRotation := TSFFloat.Create(Self, True, 'rotation', 0);
   FdRotation.ChangeAlways := chEverything;
  AddField(FFdRotation);

  FFdScaleFactor := TSFVec2f.Create(Self, True, 'scaleFactor', Vector2(1, 1));
   FdScaleFactor.ChangeAlways := chEverything;
  AddField(FFdScaleFactor);

  FFdCenter := TSFVec2f.Create(Self, True, 'center', Vector2(0, 0));
   FdCenter.ChangeAlways := chEverything;
  AddField(FFdCenter);
end;

{$endif read_implementation}