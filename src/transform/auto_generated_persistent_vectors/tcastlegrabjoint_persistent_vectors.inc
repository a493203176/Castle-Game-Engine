{ -*- buffer-read-only: t -*-

  Copyright 2018-2022 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Automatically generated wrapper to make vectors/colors persistent.

  Do not edit this file manually!
  Instead
  - edit tools/internal/generate-persistent-vectors/persistent_vectors_input.txt
  - and run generate-persistent-vectors in that directory.
}

{$ifdef read_interface_class}
strict private
  FAnchorPersistent: TCastleVector3Persistent;
  function GetAnchorForPersistent: TVector3;
  procedure SetAnchorForPersistent(const AValue: TVector3);
published
  { @link(Anchor) that can be visually edited in
    Castle Game Engine Editor, Lazarus and Delphi.
    Normal user code does not need to deal with this,
    instead read or write @link(Anchor) directly.

    @seealso Anchor }
  property AnchorPersistent: TCastleVector3Persistent read FAnchorPersistent ;
{$endif read_interface_class}

{$ifdef read_implementation_methods}
function TCastleGrabJoint.GetAnchorForPersistent: TVector3;
begin
  Result := Anchor;
end;

procedure TCastleGrabJoint.SetAnchorForPersistent(const AValue: TVector3);
begin
  Anchor := AValue;
end;
{$endif read_implementation_methods}

{$ifdef read_implementation_constructor}
  FAnchorPersistent := TCastleVector3Persistent.Create(nil);
  { Note that some classes (like TCastleVector3Persistent) call SetSubComponent(true)
    on themselves, for backward compatibility. But we should not depend on it,
    some classes (like TFloatRectanglePersisten) may not call it.
    The responsibility of calling "SetSubComponent(true)" should be on the owner
    in general (this is more functional, and more standard too). }
  FAnchorPersistent.SetSubComponent(true);
  FAnchorPersistent.InternalGetValue := {$ifdef FPC}@{$endif}GetAnchorForPersistent;
  FAnchorPersistent.InternalSetValue := {$ifdef FPC}@{$endif}SetAnchorForPersistent;
  FAnchorPersistent.InternalDefaultValue := Anchor; // current value is default
{$endif read_implementation_constructor}

{$ifdef read_implementation_destructor}
  FreeAndNil(FAnchorPersistent);
{$endif read_implementation_destructor}

{ -*- buffer-read-only: t -*-

  Copyright 2018-2022 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Automatically generated wrapper to make vectors/colors persistent.

  Do not edit this file manually!
  Instead
  - edit tools/internal/generate-persistent-vectors/persistent_vectors_input.txt
  - and run generate-persistent-vectors in that directory.
}

{$ifdef read_interface_class}
strict private
  FTargetWorldPersistent: TCastleVector3Persistent;
  function GetTargetWorldForPersistent: TVector3;
  procedure SetTargetWorldForPersistent(const AValue: TVector3);
published
  { @link(TargetWorld) that can be visually edited in
    Castle Game Engine Editor, Lazarus and Delphi.
    Normal user code does not need to deal with this,
    instead read or write @link(TargetWorld) directly.

    @seealso TargetWorld }
  property TargetWorldPersistent: TCastleVector3Persistent read FTargetWorldPersistent ;
{$endif read_interface_class}

{$ifdef read_implementation_methods}
function TCastleGrabJoint.GetTargetWorldForPersistent: TVector3;
begin
  Result := TargetWorld;
end;

procedure TCastleGrabJoint.SetTargetWorldForPersistent(const AValue: TVector3);
begin
  TargetWorld := AValue;
end;
{$endif read_implementation_methods}

{$ifdef read_implementation_constructor}
  FTargetWorldPersistent := TCastleVector3Persistent.Create(nil);
  { Note that some classes (like TCastleVector3Persistent) call SetSubComponent(true)
    on themselves, for backward compatibility. But we should not depend on it,
    some classes (like TFloatRectanglePersisten) may not call it.
    The responsibility of calling "SetSubComponent(true)" should be on the owner
    in general (this is more functional, and more standard too). }
  FTargetWorldPersistent.SetSubComponent(true);
  FTargetWorldPersistent.InternalGetValue := {$ifdef FPC}@{$endif}GetTargetWorldForPersistent;
  FTargetWorldPersistent.InternalSetValue := {$ifdef FPC}@{$endif}SetTargetWorldForPersistent;
  FTargetWorldPersistent.InternalDefaultValue := TargetWorld; // current value is default
{$endif read_implementation_constructor}

{$ifdef read_implementation_destructor}
  FreeAndNil(FTargetWorldPersistent);
{$endif read_implementation_destructor}
