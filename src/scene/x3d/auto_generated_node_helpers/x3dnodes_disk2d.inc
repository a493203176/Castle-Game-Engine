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
    function GetInnerRadius: Single;
    procedure SetInnerRadius(const Value: Single);
    function GetOuterRadius: Single;
    procedure SetOuterRadius(const Value: Single);
    function GetSlices: Integer;
    procedure SetSlices(const Value: Integer);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdInnerRadius: TSFFloat;
    { Internal wrapper for property @code(InnerRadius). This wrapper API may change, we advise to access simpler @code(InnerRadius) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdInnerRadius: TSFFloat read FFdInnerRadius;
    {  }
    property InnerRadius: Single read GetInnerRadius write SetInnerRadius;

    strict private FFdOuterRadius: TSFFloat;
    { Internal wrapper for property @code(OuterRadius). This wrapper API may change, we advise to access simpler @code(OuterRadius) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdOuterRadius: TSFFloat read FFdOuterRadius;
    {  }
    property OuterRadius: Single read GetOuterRadius write SetOuterRadius;

    strict private FFdSolid: TSFBool;
    { Internal wrapper for property @code(Solid). This wrapper API may change, we advise to access simpler @code(Solid) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdSolid: TSFBool read FFdSolid;

    strict private FFdSlices: TSFInt32;
    { Internal wrapper for property @code(Slices). This wrapper API may change, we advise to access simpler @code(Slices) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdSlices: TSFInt32 read FFdSlices;
    { How much to subdivide the circles (both inner and outer circles of the disk). Larger values result in a polygon that looks smoother, but also mean that we need to render more triangles. The default value, -1 means to use the global @link(DefaultTriangulationSlices) parameter. }
    property Slices: Integer read GetSlices write SetSlices;

{$endif read_interface}

{$ifdef read_implementation}

{ TDisk2DNode ----------------------------------------------- }

function TDisk2DNode.GetInnerRadius: Single;
begin
  Result := FdInnerRadius.Value;
end;

procedure TDisk2DNode.SetInnerRadius(const Value: Single);
begin
  FdInnerRadius.Send(Value);
end;

function TDisk2DNode.GetOuterRadius: Single;
begin
  Result := FdOuterRadius.Value;
end;

procedure TDisk2DNode.SetOuterRadius(const Value: Single);
begin
  FdOuterRadius.Send(Value);
end;

function TDisk2DNode.GetSlices: Integer;
begin
  Result := FdSlices.Value;
end;

procedure TDisk2DNode.SetSlices(const Value: Integer);
begin
  FdSlices.Send(Value);
end;

class function TDisk2DNode.ClassX3DType: String;
begin
  Result := 'Disk2D';
end;

procedure TDisk2DNode.CreateNode;
begin
  inherited;

  FFdInnerRadius := TSFFloat.Create(Self, False, 'innerRadius', 0);
   FdInnerRadius.ChangeAlways := chGeometry;
   FdInnerRadius.MustBeNonnegative := true;
  AddField(FFdInnerRadius);

  FFdOuterRadius := TSFFloat.Create(Self, False, 'outerRadius', 1);
   FdOuterRadius.ChangeAlways := chGeometry;
   FdOuterRadius.MustBeNonnegative := true;
  AddField(FFdOuterRadius);

  FFdSolid := TSFBool.Create(Self, False, 'solid', false);
   FdSolid.ChangeAlways := chGeometry;
  AddField(FFdSolid);

  FFdSlices := TSFInt32.Create(Self, True, 'slices', -1);
   FdSlices.ChangeAlways := chGeometry;
  AddField(FFdSlices);
end;

{$endif read_implementation}