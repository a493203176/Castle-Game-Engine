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
    function GetAutoRefresh: TFloatTime;
    procedure SetAutoRefresh(const Value: TFloatTime);
    function GetAutoRefreshTimeLimit: TFloatTime;
    procedure SetAutoRefreshTimeLimit(const Value: TFloatTime);
    function GetLoad: Boolean;
    procedure SetLoad(const Value: Boolean);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdAutoRefresh: TSFTime;
    { Internal wrapper for property @code(AutoRefresh). This wrapper API may change, we advise to access simpler @code(AutoRefresh) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAutoRefresh: TSFTime read FFdAutoRefresh;
    {  }
    property AutoRefresh: TFloatTime read GetAutoRefresh write SetAutoRefresh;

    strict private FFdAutoRefreshTimeLimit: TSFTime;
    { Internal wrapper for property @code(AutoRefreshTimeLimit). This wrapper API may change, we advise to access simpler @code(AutoRefreshTimeLimit) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAutoRefreshTimeLimit: TSFTime read FFdAutoRefreshTimeLimit;
    {  }
    property AutoRefreshTimeLimit: TFloatTime read GetAutoRefreshTimeLimit write SetAutoRefreshTimeLimit;

    strict private FFdLoad: TSFBool;
    { Internal wrapper for property @code(Load). This wrapper API may change, we advise to access simpler @code(Load) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdLoad: TSFBool read FFdLoad;
    {  }
    property Load: Boolean read GetLoad write SetLoad;

    strict private FFdUrl: TMFString;
    { Internal wrapper for property @code(Url). This wrapper API may change, we advise to access simpler @code(Url) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdUrl: TMFString read FFdUrl;
    {  }
    procedure SetUrl(const Value: array of string); overload;
    {  }
    procedure SetUrl(const Value: TCastleStringList); overload;

{$endif read_interface}

{$ifdef read_implementation}

{ TAudioClipNode ----------------------------------------------- }

function TAudioClipNode.GetAutoRefresh: TFloatTime;
begin
  Result := FdAutoRefresh.Value;
end;

procedure TAudioClipNode.SetAutoRefresh(const Value: TFloatTime);
begin
  FdAutoRefresh.Send(Value);
end;

function TAudioClipNode.GetAutoRefreshTimeLimit: TFloatTime;
begin
  Result := FdAutoRefreshTimeLimit.Value;
end;

procedure TAudioClipNode.SetAutoRefreshTimeLimit(const Value: TFloatTime);
begin
  FdAutoRefreshTimeLimit.Send(Value);
end;

function TAudioClipNode.GetLoad: Boolean;
begin
  Result := FdLoad.Value;
end;

procedure TAudioClipNode.SetLoad(const Value: Boolean);
begin
  FdLoad.Send(Value);
end;

procedure TAudioClipNode.SetUrl(const Value: array of string);
begin
  FdUrl.Send(Value);
end;

procedure TAudioClipNode.SetUrl(const Value: TCastleStringList);
begin
  FdUrl.Send(Value);
end;

class function TAudioClipNode.ClassX3DType: String;
begin
  Result := 'AudioClip';
end;

procedure TAudioClipNode.CreateNode;
begin
  inherited;

  FFdAutoRefresh := TSFTime.Create(Self, True, 'autoRefresh', 0.0);
   FdAutoRefresh.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAutoRefresh);

  FFdAutoRefreshTimeLimit := TSFTime.Create(Self, True, 'autoRefreshTimeLimit', 3600.0);
   FdAutoRefreshTimeLimit.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAutoRefreshTimeLimit);

  FFdLoad := TSFBool.Create(Self, True, 'load', true);
   FdLoad.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdLoad);

  FFdUrl := TMFString.Create(Self, True, 'url', []);
   FdUrl.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdUrl);

  DefaultContainerField := 'source';
end;

{$endif read_implementation}