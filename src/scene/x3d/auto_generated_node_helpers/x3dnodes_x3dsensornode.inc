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
    function GetDescription: String;
    procedure SetDescription(const Value: String);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdEnabled: TSFBool;
    { Internal wrapper for property @code(Enabled). This wrapper API may change, we advise to access simpler @code(Enabled) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEnabled: TSFBool read FFdEnabled;
    {  }
    property Enabled: Boolean read GetEnabled write SetEnabled;

    strict private FEventIsActive: TSFBoolEvent;
    {  }
    public property EventIsActive: TSFBoolEvent read FEventIsActive;

    strict private FFdDescription: TSFString;
    { Internal wrapper for property @code(Description). This wrapper API may change, we advise to access simpler @code(Description) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDescription: TSFString read FFdDescription;
    {  }
    property Description: String read GetDescription write SetDescription;

{$endif read_interface}

{$ifdef read_implementation}

{ TAbstractSensorNode ----------------------------------------------- }

function TAbstractSensorNode.GetEnabled: Boolean;
begin
  Result := FdEnabled.Value;
end;

procedure TAbstractSensorNode.SetEnabled(const Value: Boolean);
begin
  FdEnabled.Send(Value);
end;

function TAbstractSensorNode.GetDescription: String;
begin
  Result := FdDescription.Value;
end;

procedure TAbstractSensorNode.SetDescription(const Value: String);
begin
  FdDescription.Send(Value);
end;

class function TAbstractSensorNode.ClassX3DType: String;
begin
  Result := 'X3DSensorNode';
end;

procedure TAbstractSensorNode.CreateNode;
begin
  inherited;

  FFdEnabled := TSFBool.Create(Self, True, 'enabled', true);
   FdEnabled.ChangeAlways := chNone;
  AddField(FFdEnabled);

  FEventIsActive := TSFBoolEvent.Create(Self, 'isActive', false);
  AddEvent(FEventIsActive);

  FFdDescription := TSFString.Create(Self, True, 'description', '');
   FdDescription.ChangeAlways := chNone;
  AddField(FFdDescription);
end;

{$endif read_implementation}