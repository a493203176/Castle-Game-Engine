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
    function GetEnabled: Boolean;
    procedure SetEnabled(const Value: Boolean);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdEnabled: TSFBool;
    { Internal wrapper for property @code(Enabled). This wrapper API may change, we advise to access simpler @code(Enabled) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEnabled: TSFBool read FFdEnabled;
    {  }
    property Enabled: Boolean read GetEnabled write SetEnabled;

    strict private FEventTrigger: TSFBoolEvent;
    {  }
    public property EventTrigger: TSFBoolEvent read FEventTrigger;

{$endif read_interface}

{$ifdef read_implementation}

{ TValueTriggerNode ----------------------------------------------- }

function TValueTriggerNode.GetEnabled: Boolean;
begin
  Result := FdEnabled.Value;
end;

procedure TValueTriggerNode.SetEnabled(const Value: Boolean);
begin
  FdEnabled.Send(Value);
end;

class function TValueTriggerNode.ClassX3DType: String;
begin
  Result := 'ValueTrigger';
end;

procedure TValueTriggerNode.CreateNode;
begin
  inherited;

  FFdEnabled := TSFBool.Create(Self, True, 'enabled', true);
   FdEnabled.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdEnabled);

  FEventTrigger := TSFBoolEvent.Create(Self, 'trigger', true);
  AddEvent(FEventTrigger);
end;

{$endif read_implementation}