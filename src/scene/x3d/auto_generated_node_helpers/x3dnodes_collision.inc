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
    function GetProxy: TAbstractChildNode;
    procedure SetProxy(const Value: TAbstractChildNode);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdEnabled: TSFBool;
    { Internal wrapper for property @code(Enabled). This wrapper API may change, we advise to access simpler @code(Enabled) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEnabled: TSFBool read FFdEnabled;
    {  }
    property Enabled: Boolean read GetEnabled write SetEnabled;

    strict private FEventCollideTime: TSFTimeEvent;
    {  }
    public property EventCollideTime: TSFTimeEvent read FEventCollideTime;

    strict private FEventIsActive: TSFBoolEvent;
    {  }
    public property EventIsActive: TSFBoolEvent read FEventIsActive;

    strict private FFdProxy: TSFNode;
    { Internal wrapper for property @code(Proxy). This wrapper API may change, we advise to access simpler @code(Proxy) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdProxy: TSFNode read FFdProxy;
    {  }
    property Proxy: TAbstractChildNode read GetProxy write SetProxy;

{$endif read_interface}

{$ifdef read_implementation}

{ TCollisionNode ----------------------------------------------- }

function TCollisionNode.GetEnabled: Boolean;
begin
  Result := FdEnabled.Value;
end;

procedure TCollisionNode.SetEnabled(const Value: Boolean);
begin
  FdEnabled.Send(Value);
end;

function TCollisionNode.GetProxy: TAbstractChildNode;
begin
  if FdProxy.Value is TAbstractChildNode then
    Result := TAbstractChildNode(FdProxy.Value)
  else
    Result := nil;
end;

procedure TCollisionNode.SetProxy(const Value: TAbstractChildNode);
begin
  FdProxy.Send(Value);
end;

class function TCollisionNode.ClassX3DType: String;
begin
  Result := 'Collision';
end;

procedure TCollisionNode.CreateNode;
begin
  inherited;

  FFdEnabled := TSFBool.Create(Self, True, 'enabled', true);
   FdEnabled.ChangeAlways := chEverything;
  AddField(FFdEnabled);

  FEventCollideTime := TSFTimeEvent.Create(Self, 'collideTime', false);
  AddEvent(FEventCollideTime);

  FEventIsActive := TSFBoolEvent.Create(Self, 'isActive', false);
  AddEvent(FEventIsActive);

  FFdProxy := TSFNode.Create(Self, False, 'proxy', [TAbstractChildNode]);
   FdProxy.ChangeAlways := chEverything;
  AddField(FFdProxy);
end;

{$endif read_implementation}