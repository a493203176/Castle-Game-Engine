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
    function GetCenter: TVector3;
    procedure SetCenter(const Value: TVector3);
    function GetDescription: String;
    procedure SetDescription(const Value: String);
    function GetDisplayed: Boolean;
    procedure SetDisplayed(const Value: Boolean);
    function GetRetainUserOffsets: Boolean;
    procedure SetRetainUserOffsets(const Value: Boolean);
    function GetSize: TVector3;
    procedure SetSize(const Value: TVector3);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdCenter: TSFVec3f;
    { Internal wrapper for property @code(Center). This wrapper API may change, we advise to access simpler @code(Center) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdCenter: TSFVec3f read FFdCenter;
    {  }
    property Center: TVector3 read GetCenter write SetCenter;

    strict private FFdChildren: TMFNode;
    { Internal wrapper for property @code(Children). This wrapper API may change, we advise to access simpler @code(Children) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdChildren: TMFNode read FFdChildren;
    {  }
    procedure SetChildren(const Value: array of TX3DNode);

    strict private FFdDescription: TSFString;
    { Internal wrapper for property @code(Description). This wrapper API may change, we advise to access simpler @code(Description) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDescription: TSFString read FFdDescription;
    {  }
    property Description: String read GetDescription write SetDescription;

    strict private FFdDisplayed: TSFBool;
    { Internal wrapper for property @code(Displayed). This wrapper API may change, we advise to access simpler @code(Displayed) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDisplayed: TSFBool read FFdDisplayed;
    {  }
    property Displayed: Boolean read GetDisplayed write SetDisplayed;

    strict private FFdRetainUserOffsets: TSFBool;
    { Internal wrapper for property @code(RetainUserOffsets). This wrapper API may change, we advise to access simpler @code(RetainUserOffsets) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdRetainUserOffsets: TSFBool read FFdRetainUserOffsets;
    {  }
    property RetainUserOffsets: Boolean read GetRetainUserOffsets write SetRetainUserOffsets;

    strict private FFdSize: TSFVec3f;
    { Internal wrapper for property @code(Size). This wrapper API may change, we advise to access simpler @code(Size) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdSize: TSFVec3f read FFdSize;
    {  }
    property Size: TVector3 read GetSize write SetSize;

{$endif read_interface}

{$ifdef read_implementation}

{ TViewpointGroupNode ----------------------------------------------- }

function TViewpointGroupNode.GetCenter: TVector3;
begin
  Result := FdCenter.Value;
end;

procedure TViewpointGroupNode.SetCenter(const Value: TVector3);
begin
  FdCenter.Send(Value);
end;

procedure TViewpointGroupNode.SetChildren(const Value: array of TX3DNode);
var
  L: Integer;
  A: array of TX3DNode;
begin
  L := High(Value) + 1;
  SetLength(A, L);
  if L > 0 then
    Move(Value[0], A[0], L * SizeOf(TX3DNode));
  FdChildren.Send(A);
end;

function TViewpointGroupNode.GetDescription: String;
begin
  Result := FdDescription.Value;
end;

procedure TViewpointGroupNode.SetDescription(const Value: String);
begin
  FdDescription.Send(Value);
end;

function TViewpointGroupNode.GetDisplayed: Boolean;
begin
  Result := FdDisplayed.Value;
end;

procedure TViewpointGroupNode.SetDisplayed(const Value: Boolean);
begin
  FdDisplayed.Send(Value);
end;

function TViewpointGroupNode.GetRetainUserOffsets: Boolean;
begin
  Result := FdRetainUserOffsets.Value;
end;

procedure TViewpointGroupNode.SetRetainUserOffsets(const Value: Boolean);
begin
  FdRetainUserOffsets.Send(Value);
end;

function TViewpointGroupNode.GetSize: TVector3;
begin
  Result := FdSize.Value;
end;

procedure TViewpointGroupNode.SetSize(const Value: TVector3);
begin
  FdSize.Send(Value);
end;

class function TViewpointGroupNode.ClassX3DType: String;
begin
  Result := 'ViewpointGroup';
end;

procedure TViewpointGroupNode.CreateNode;
begin
  inherited;

  FFdCenter := TSFVec3f.Create(Self, True, 'center', Vector3(0, 0, 0));
   FdCenter.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdCenter);

  FFdChildren := TMFNode.Create(Self, True, 'children', [TAbstractViewpointNode, TViewpointGroupNode]);
   FdChildren.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdChildren);

  FFdDescription := TSFString.Create(Self, True, 'description', '');
   FdDescription.ChangeAlways := chNone;
  AddField(FFdDescription);

  FFdDisplayed := TSFBool.Create(Self, True, 'displayed', true);
   FdDisplayed.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdDisplayed);

  FFdRetainUserOffsets := TSFBool.Create(Self, True, 'retainUserOffsets', false);
   FdRetainUserOffsets.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdRetainUserOffsets);

  FFdSize := TSFVec3f.Create(Self, True, 'size', Vector3(0, 0, 0));
   FdSize.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdSize);
end;

{$endif read_implementation}