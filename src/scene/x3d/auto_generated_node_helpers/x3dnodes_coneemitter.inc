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
    function GetAngle: Single;
    procedure SetAngle(const Value: Single);
    function GetDirection: TVector3;
    procedure SetDirection(const Value: TVector3);
    function GetPosition: TVector3;
    procedure SetPosition(const Value: TVector3);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdAngle: TSFFloat;
    { Internal wrapper for property @code(Angle). This wrapper API may change, we advise to access simpler @code(Angle) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAngle: TSFFloat read FFdAngle;
    {  }
    property Angle: Single read GetAngle write SetAngle;

    strict private FFdDirection: TSFVec3f;
    { Internal wrapper for property @code(Direction). This wrapper API may change, we advise to access simpler @code(Direction) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDirection: TSFVec3f read FFdDirection;
    {  }
    property Direction: TVector3 read GetDirection write SetDirection;

    strict private FFdPosition: TSFVec3f;
    { Internal wrapper for property @code(Position). This wrapper API may change, we advise to access simpler @code(Position) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdPosition: TSFVec3f read FFdPosition;
    {  }
    property Position: TVector3 read GetPosition write SetPosition;

{$endif read_interface}

{$ifdef read_implementation}

{ TConeEmitterNode ----------------------------------------------- }

function TConeEmitterNode.GetAngle: Single;
begin
  Result := FdAngle.Value;
end;

procedure TConeEmitterNode.SetAngle(const Value: Single);
begin
  FdAngle.Send(Value);
end;

function TConeEmitterNode.GetDirection: TVector3;
begin
  Result := FdDirection.Value;
end;

procedure TConeEmitterNode.SetDirection(const Value: TVector3);
begin
  FdDirection.Send(Value);
end;

function TConeEmitterNode.GetPosition: TVector3;
begin
  Result := FdPosition.Value;
end;

procedure TConeEmitterNode.SetPosition(const Value: TVector3);
begin
  FdPosition.Send(Value);
end;

class function TConeEmitterNode.ClassX3DType: String;
begin
  Result := 'ConeEmitter';
end;

procedure TConeEmitterNode.CreateNode;
begin
  inherited;

  FFdAngle := TSFFloat.Create(Self, True, 'angle', Pi/4);
   FdAngle.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAngle);

  FFdDirection := TSFVec3f.Create(Self, True, 'direction', Vector3(0, 1, 0));
   FdDirection.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdDirection);

  FFdPosition := TSFVec3f.Create(Self, True, 'position', Vector3(0, 0, 0));
   FdPosition.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdPosition);
end;

{$endif read_implementation}