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
    function GetAxis: TVector3;
    procedure SetAxis(const Value: TVector3);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdKeyValue: TMFFloat;
    { Internal wrapper for property @code(KeyValue). This wrapper API may change, we advise to access simpler @code(KeyValue) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdKeyValue: TMFFloat read FFdKeyValue;
    {  }
    procedure SetKeyValue(const Value: array of Single); overload;
    {  }
    procedure SetKeyValue(const Value: TSingleList); overload;

    strict private FFdAxis: TSFVec3f;
    { Internal wrapper for property @code(Axis). This wrapper API may change, we advise to access simpler @code(Axis) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAxis: TSFVec3f read FFdAxis;
    {  }
    property Axis: TVector3 read GetAxis write SetAxis;

    strict private FEventValue_changed: TSFRotationEvent;
    {  }
    public property EventValue_changed: TSFRotationEvent read FEventValue_changed;

{$endif read_interface}

{$ifdef read_implementation}

{ TCubicBezier2DOrientationInterpolatorNode ----------------------------------------------- }

procedure TCubicBezier2DOrientationInterpolatorNode.SetKeyValue(const Value: array of Single);
begin
  FdKeyValue.Send(Value);
end;

procedure TCubicBezier2DOrientationInterpolatorNode.SetKeyValue(const Value: TSingleList);
begin
  FdKeyValue.Send(Value);
end;

function TCubicBezier2DOrientationInterpolatorNode.GetAxis: TVector3;
begin
  Result := FdAxis.Value;
end;

procedure TCubicBezier2DOrientationInterpolatorNode.SetAxis(const Value: TVector3);
begin
  FdAxis.Send(Value);
end;

class function TCubicBezier2DOrientationInterpolatorNode.ClassX3DType: String;
begin
  Result := 'CubicBezier2DOrientationInterpolator';
end;

procedure TCubicBezier2DOrientationInterpolatorNode.CreateNode;
begin
  inherited;

  FFdKeyValue := TMFFloat.Create(Self, True, 'keyValue', []);
   FdKeyValue.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdKeyValue);

  FFdAxis := TSFVec3f.Create(Self, True, 'axis', Vector3(0, 0, 1));
   FdAxis.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAxis);

  FEventValue_changed := TSFRotationEvent.Create(Self, 'value_changed', false);
  AddEvent(FEventValue_changed);
end;

{$endif read_implementation}