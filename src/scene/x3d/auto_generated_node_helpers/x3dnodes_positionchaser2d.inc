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
    function GetInitialDestination: TVector2;
    procedure SetInitialDestination(const Value: TVector2);
    function GetInitialValue: TVector2;
    procedure SetInitialValue(const Value: TVector2);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FEventSet_destination: TSFVec2fEvent;
    {  }
    public property EventSet_destination: TSFVec2fEvent read FEventSet_destination;

    strict private FEventSet_value: TSFVec2fEvent;
    {  }
    public property EventSet_value: TSFVec2fEvent read FEventSet_value;

    strict private FEventValue_changed: TSFVec2fEvent;
    {  }
    public property EventValue_changed: TSFVec2fEvent read FEventValue_changed;

    strict private FFdInitialDestination: TSFVec2f;
    { Internal wrapper for property @code(InitialDestination). This wrapper API may change, we advise to access simpler @code(InitialDestination) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdInitialDestination: TSFVec2f read FFdInitialDestination;
    {  }
    property InitialDestination: TVector2 read GetInitialDestination write SetInitialDestination;

    strict private FFdInitialValue: TSFVec2f;
    { Internal wrapper for property @code(InitialValue). This wrapper API may change, we advise to access simpler @code(InitialValue) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdInitialValue: TSFVec2f read FFdInitialValue;
    {  }
    property InitialValue: TVector2 read GetInitialValue write SetInitialValue;

{$endif read_interface}

{$ifdef read_implementation}

{ TPositionChaser2DNode ----------------------------------------------- }

function TPositionChaser2DNode.GetInitialDestination: TVector2;
begin
  Result := FdInitialDestination.Value;
end;

procedure TPositionChaser2DNode.SetInitialDestination(const Value: TVector2);
begin
  FdInitialDestination.Send(Value);
end;

function TPositionChaser2DNode.GetInitialValue: TVector2;
begin
  Result := FdInitialValue.Value;
end;

procedure TPositionChaser2DNode.SetInitialValue(const Value: TVector2);
begin
  FdInitialValue.Send(Value);
end;

class function TPositionChaser2DNode.ClassX3DType: String;
begin
  Result := 'PositionChaser2D';
end;

procedure TPositionChaser2DNode.CreateNode;
begin
  inherited;

  FEventSet_destination := TSFVec2fEvent.Create(Self, 'set_destination', true);
  AddEvent(FEventSet_destination);

  FEventSet_value := TSFVec2fEvent.Create(Self, 'set_value', true);
  AddEvent(FEventSet_value);

  FEventValue_changed := TSFVec2fEvent.Create(Self, 'value_changed', false);
  AddEvent(FEventValue_changed);

  FFdInitialDestination := TSFVec2f.Create(Self, False, 'initialDestination', Vector2(0, 0));
   FdInitialDestination.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdInitialDestination);

  FFdInitialValue := TSFVec2f.Create(Self, False, 'initialValue', Vector2(0, 0));
   FdInitialValue.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdInitialValue);
end;

{$endif read_implementation}