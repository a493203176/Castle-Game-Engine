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
    function GetHorizontal: Boolean;
    procedure SetHorizontal(const Value: Boolean);
    function GetLanguage: String;
    procedure SetLanguage(const Value: String);
    function GetLeftToRight: Boolean;
    procedure SetLeftToRight(const Value: Boolean);
    function GetPointSize: Single;
    procedure SetPointSize(const Value: Single);
    function GetSpacing: Single;
    procedure SetSpacing(const Value: Single);
    function GetStyle: TX3DFontStyle;
    procedure SetStyle(const Value: TX3DFontStyle);
    function GetTopToBottom: Boolean;
    procedure SetTopToBottom(const Value: Boolean);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdFamily: TMFString;
    { Internal wrapper for property @code(Family). This wrapper API may change, we advise to access simpler @code(Family) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdFamily: TMFString read FFdFamily;

    strict private FFdHorizontal: TSFBool;
    { Internal wrapper for property @code(Horizontal). This wrapper API may change, we advise to access simpler @code(Horizontal) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdHorizontal: TSFBool read FFdHorizontal;
    {  }
    property Horizontal: Boolean read GetHorizontal write SetHorizontal;

    strict private FFdJustify: TMFString;
    { Internal wrapper for property @code(Justify). This wrapper API may change, we advise to access simpler @code(Justify) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdJustify: TMFString read FFdJustify;

    strict private FFdLanguage: TSFString;
    { Internal wrapper for property @code(Language). This wrapper API may change, we advise to access simpler @code(Language) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdLanguage: TSFString read FFdLanguage;
    {  }
    property Language: String read GetLanguage write SetLanguage;

    strict private FFdLeftToRight: TSFBool;
    { Internal wrapper for property @code(LeftToRight). This wrapper API may change, we advise to access simpler @code(LeftToRight) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdLeftToRight: TSFBool read FFdLeftToRight;
    {  }
    property LeftToRight: Boolean read GetLeftToRight write SetLeftToRight;

    strict private FFdPointSize: TSFFloat;
    { Internal wrapper for property @code(PointSize). This wrapper API may change, we advise to access simpler @code(PointSize) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdPointSize: TSFFloat read FFdPointSize;
    {  }
    property PointSize: Single read GetPointSize write SetPointSize;

    strict private FFdSpacing: TSFFloat;
    { Internal wrapper for property @code(Spacing). This wrapper API may change, we advise to access simpler @code(Spacing) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdSpacing: TSFFloat read FFdSpacing;
    {  }
    property Spacing: Single read GetSpacing write SetSpacing;

    strict private FFdStyle: TSFStringEnum;
    { Internal wrapper for property @code(Style). This wrapper API may change, we advise to access simpler @code(Style) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdStyle: TSFStringEnum read FFdStyle;
    {  }
    property Style: TX3DFontStyle read GetStyle write SetStyle;

    strict private FFdTopToBottom: TSFBool;
    { Internal wrapper for property @code(TopToBottom). This wrapper API may change, we advise to access simpler @code(TopToBottom) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdTopToBottom: TSFBool read FFdTopToBottom;
    {  }
    property TopToBottom: Boolean read GetTopToBottom write SetTopToBottom;

{$endif read_interface}

{$ifdef read_implementation}

{ TScreenFontStyleNode ----------------------------------------------- }

function TScreenFontStyleNode.GetHorizontal: Boolean;
begin
  Result := FdHorizontal.Value;
end;

procedure TScreenFontStyleNode.SetHorizontal(const Value: Boolean);
begin
  FdHorizontal.Send(Value);
end;

function TScreenFontStyleNode.GetLanguage: String;
begin
  Result := FdLanguage.Value;
end;

procedure TScreenFontStyleNode.SetLanguage(const Value: String);
begin
  FdLanguage.Send(Value);
end;

function TScreenFontStyleNode.GetLeftToRight: Boolean;
begin
  Result := FdLeftToRight.Value;
end;

procedure TScreenFontStyleNode.SetLeftToRight(const Value: Boolean);
begin
  FdLeftToRight.Send(Value);
end;

function TScreenFontStyleNode.GetPointSize: Single;
begin
  Result := FdPointSize.Value;
end;

procedure TScreenFontStyleNode.SetPointSize(const Value: Single);
begin
  FdPointSize.Send(Value);
end;

function TScreenFontStyleNode.GetSpacing: Single;
begin
  Result := FdSpacing.Value;
end;

procedure TScreenFontStyleNode.SetSpacing(const Value: Single);
begin
  FdSpacing.Send(Value);
end;

function TScreenFontStyleNode.GetStyle: TX3DFontStyle;
begin
  Result := TX3DFontStyle(FdStyle.EnumValue);
end;

procedure TScreenFontStyleNode.SetStyle(const Value: TX3DFontStyle);
begin
  FdStyle.SendEnumValue(Ord(Value));
end;

function TScreenFontStyleNode.GetTopToBottom: Boolean;
begin
  Result := FdTopToBottom.Value;
end;

procedure TScreenFontStyleNode.SetTopToBottom(const Value: Boolean);
begin
  FdTopToBottom.Send(Value);
end;

class function TScreenFontStyleNode.ClassX3DType: String;
begin
  Result := 'ScreenFontStyle';
end;

procedure TScreenFontStyleNode.CreateNode;
begin
  inherited;

  FFdFamily := TMFString.Create(Self, False, 'family', ['SERIF']);
   FdFamily.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdFamily);

  FFdHorizontal := TSFBool.Create(Self, False, 'horizontal', true);
   FdHorizontal.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdHorizontal);

  FFdJustify := TMFString.Create(Self, False, 'justify', ['BEGIN']);
   FdJustify.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdJustify);

  FFdLanguage := TSFString.Create(Self, False, 'language', '');
   FdLanguage.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdLanguage);

  FFdLeftToRight := TSFBool.Create(Self, False, 'leftToRight', true);
   FdLeftToRight.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdLeftToRight);

  FFdPointSize := TSFFloat.Create(Self, False, 'pointSize', 12.0);
   FdPointSize.ChangeAlways := chVisibleNonGeometry;
   FdPointSize.MustBeNonnegative := true;
  AddField(FFdPointSize);

  FFdSpacing := TSFFloat.Create(Self, False, 'spacing', 1.0);
   FdSpacing.ChangeAlways := chVisibleNonGeometry;
   FdSpacing.MustBeNonnegative := true;
  AddField(FFdSpacing);

  FFdStyle := TSFStringEnum.Create(Self, False, 'style', @FontStyleNames, Ord(High(FontStyleNames)) + 1, Ord(fsPlain));
   FdStyle.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdStyle);

  FFdTopToBottom := TSFBool.Create(Self, False, 'topToBottom', true);
   FdTopToBottom.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdTopToBottom);
end;

{$endif read_implementation}