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
    function GetAngularDampingFactor: Single;
    procedure SetAngularDampingFactor(const Value: Single);
    function GetAngularVelocity: TVector3;
    procedure SetAngularVelocity(const Value: TVector3);
    function GetAutoDamp: Boolean;
    procedure SetAutoDamp(const Value: Boolean);
    function GetAutoDisable: Boolean;
    procedure SetAutoDisable(const Value: Boolean);
    function GetCenterOfMass: TVector3;
    procedure SetCenterOfMass(const Value: TVector3);
    function GetDisableAngularSpeed: Single;
    procedure SetDisableAngularSpeed(const Value: Single);
    function GetDisableLinearSpeed: Single;
    procedure SetDisableLinearSpeed(const Value: Single);
    function GetDisableTime: Single;
    procedure SetDisableTime(const Value: Single);
    function GetEnabled: Boolean;
    procedure SetEnabled(const Value: Boolean);
    function GetFiniteRotationAxis: TVector3;
    procedure SetFiniteRotationAxis(const Value: TVector3);
    function GetFixed: Boolean;
    procedure SetFixed(const Value: Boolean);
    function GetInertia: TMatrix3;
    procedure SetInertia(const Value: TMatrix3);
    function GetLinearDampingFactor: Single;
    procedure SetLinearDampingFactor(const Value: Single);
    function GetLinearVelocity: TVector3;
    procedure SetLinearVelocity(const Value: TVector3);
    function GetMass: Single;
    procedure SetMass(const Value: Single);
    function GetMassDensityModel: TX3DNode;
    procedure SetMassDensityModel(const Value: TX3DNode);
    function GetOrientation: TVector4;
    procedure SetOrientation(const Value: TVector4);
    function GetPosition: TVector3;
    procedure SetPosition(const Value: TVector3);
    function GetUseFiniteRotation: Boolean;
    procedure SetUseFiniteRotation(const Value: Boolean);
    function GetUseGlobalGravity: Boolean;
    procedure SetUseGlobalGravity(const Value: Boolean);
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

    strict private FFdAngularDampingFactor: TSFFloat;
    { Internal wrapper for property @code(AngularDampingFactor). This wrapper API may change, we advise to access simpler @code(AngularDampingFactor) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAngularDampingFactor: TSFFloat read FFdAngularDampingFactor;
    {  }
    property AngularDampingFactor: Single read GetAngularDampingFactor write SetAngularDampingFactor;

    strict private FFdAngularVelocity: TSFVec3f;
    { Internal wrapper for property @code(AngularVelocity). This wrapper API may change, we advise to access simpler @code(AngularVelocity) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAngularVelocity: TSFVec3f read FFdAngularVelocity;
    {  }
    property AngularVelocity: TVector3 read GetAngularVelocity write SetAngularVelocity;

    strict private FFdAutoDamp: TSFBool;
    { Internal wrapper for property @code(AutoDamp). This wrapper API may change, we advise to access simpler @code(AutoDamp) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAutoDamp: TSFBool read FFdAutoDamp;
    {  }
    property AutoDamp: Boolean read GetAutoDamp write SetAutoDamp;

    strict private FFdAutoDisable: TSFBool;
    { Internal wrapper for property @code(AutoDisable). This wrapper API may change, we advise to access simpler @code(AutoDisable) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdAutoDisable: TSFBool read FFdAutoDisable;
    {  }
    property AutoDisable: Boolean read GetAutoDisable write SetAutoDisable;

    strict private FFdCenterOfMass: TSFVec3f;
    { Internal wrapper for property @code(CenterOfMass). This wrapper API may change, we advise to access simpler @code(CenterOfMass) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdCenterOfMass: TSFVec3f read FFdCenterOfMass;
    {  }
    property CenterOfMass: TVector3 read GetCenterOfMass write SetCenterOfMass;

    strict private FFdDisableAngularSpeed: TSFFloat;
    { Internal wrapper for property @code(DisableAngularSpeed). This wrapper API may change, we advise to access simpler @code(DisableAngularSpeed) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDisableAngularSpeed: TSFFloat read FFdDisableAngularSpeed;
    {  }
    property DisableAngularSpeed: Single read GetDisableAngularSpeed write SetDisableAngularSpeed;

    strict private FFdDisableLinearSpeed: TSFFloat;
    { Internal wrapper for property @code(DisableLinearSpeed). This wrapper API may change, we advise to access simpler @code(DisableLinearSpeed) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDisableLinearSpeed: TSFFloat read FFdDisableLinearSpeed;
    {  }
    property DisableLinearSpeed: Single read GetDisableLinearSpeed write SetDisableLinearSpeed;

    strict private FFdDisableTime: TSFFloat;
    { Internal wrapper for property @code(DisableTime). This wrapper API may change, we advise to access simpler @code(DisableTime) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdDisableTime: TSFFloat read FFdDisableTime;
    {  }
    property DisableTime: Single read GetDisableTime write SetDisableTime;

    strict private FFdEnabled: TSFBool;
    { Internal wrapper for property @code(Enabled). This wrapper API may change, we advise to access simpler @code(Enabled) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdEnabled: TSFBool read FFdEnabled;
    {  }
    property Enabled: Boolean read GetEnabled write SetEnabled;

    strict private FFdFiniteRotationAxis: TSFVec3f;
    { Internal wrapper for property @code(FiniteRotationAxis). This wrapper API may change, we advise to access simpler @code(FiniteRotationAxis) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdFiniteRotationAxis: TSFVec3f read FFdFiniteRotationAxis;
    {  }
    property FiniteRotationAxis: TVector3 read GetFiniteRotationAxis write SetFiniteRotationAxis;

    strict private FFdFixed: TSFBool;
    { Internal wrapper for property @code(Fixed). This wrapper API may change, we advise to access simpler @code(Fixed) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdFixed: TSFBool read FFdFixed;
    {  }
    property Fixed: Boolean read GetFixed write SetFixed;

    strict private FFdForces: TMFVec3f;
    { Internal wrapper for property @code(Forces). This wrapper API may change, we advise to access simpler @code(Forces) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdForces: TMFVec3f read FFdForces;
    {  }
    procedure SetForces(const Value: array of TVector3); overload;
    {  }
    procedure SetForces(const Value: TVector3List); overload;

    strict private FFdGeometry: TMFNode;
    { Internal wrapper for property @code(Geometry). This wrapper API may change, we advise to access simpler @code(Geometry) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdGeometry: TMFNode read FFdGeometry;
    {  }
    procedure SetGeometry(const Value: array of TAbstractNBodyCollidableNode);

    strict private FFdInertia: TSFMatrix3f;
    { Internal wrapper for property @code(Inertia). This wrapper API may change, we advise to access simpler @code(Inertia) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdInertia: TSFMatrix3f read FFdInertia;
    {  }
    property Inertia: TMatrix3 read GetInertia write SetInertia;

    strict private FFdLinearDampingFactor: TSFFloat;
    { Internal wrapper for property @code(LinearDampingFactor). This wrapper API may change, we advise to access simpler @code(LinearDampingFactor) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdLinearDampingFactor: TSFFloat read FFdLinearDampingFactor;
    {  }
    property LinearDampingFactor: Single read GetLinearDampingFactor write SetLinearDampingFactor;

    strict private FFdLinearVelocity: TSFVec3f;
    { Internal wrapper for property @code(LinearVelocity). This wrapper API may change, we advise to access simpler @code(LinearVelocity) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdLinearVelocity: TSFVec3f read FFdLinearVelocity;
    {  }
    property LinearVelocity: TVector3 read GetLinearVelocity write SetLinearVelocity;

    strict private FFdMass: TSFFloat;
    { Internal wrapper for property @code(Mass). This wrapper API may change, we advise to access simpler @code(Mass) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdMass: TSFFloat read FFdMass;
    {  }
    property Mass: Single read GetMass write SetMass;

    strict private FFdMassDensityModel: TSFNode;
    { Internal wrapper for property @code(MassDensityModel). This wrapper API may change, we advise to access simpler @code(MassDensityModel) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdMassDensityModel: TSFNode read FFdMassDensityModel;
    {  }
    property MassDensityModel: TX3DNode read GetMassDensityModel write SetMassDensityModel;

    strict private FFdOrientation: TSFRotation;
    { Internal wrapper for property @code(Orientation). This wrapper API may change, we advise to access simpler @code(Orientation) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdOrientation: TSFRotation read FFdOrientation;
    {  }
    property Orientation: TVector4 read GetOrientation write SetOrientation;

    strict private FFdPosition: TSFVec3f;
    { Internal wrapper for property @code(Position). This wrapper API may change, we advise to access simpler @code(Position) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdPosition: TSFVec3f read FFdPosition;
    {  }
    property Position: TVector3 read GetPosition write SetPosition;

    strict private FFdTorques: TMFVec3f;
    { Internal wrapper for property @code(Torques). This wrapper API may change, we advise to access simpler @code(Torques) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdTorques: TMFVec3f read FFdTorques;
    {  }
    procedure SetTorques(const Value: array of TVector3); overload;
    {  }
    procedure SetTorques(const Value: TVector3List); overload;

    strict private FFdUseFiniteRotation: TSFBool;
    { Internal wrapper for property @code(UseFiniteRotation). This wrapper API may change, we advise to access simpler @code(UseFiniteRotation) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdUseFiniteRotation: TSFBool read FFdUseFiniteRotation;
    {  }
    property UseFiniteRotation: Boolean read GetUseFiniteRotation write SetUseFiniteRotation;

    strict private FFdUseGlobalGravity: TSFBool;
    { Internal wrapper for property @code(UseGlobalGravity). This wrapper API may change, we advise to access simpler @code(UseGlobalGravity) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdUseGlobalGravity: TSFBool read FFdUseGlobalGravity;
    {  }
    property UseGlobalGravity: Boolean read GetUseGlobalGravity write SetUseGlobalGravity;

{$endif read_interface}

{$ifdef read_implementation}

{ TRigidBodyNode ----------------------------------------------- }

function TRigidBodyNode.GetAngularDampingFactor: Single;
begin
  Result := FdAngularDampingFactor.Value;
end;

procedure TRigidBodyNode.SetAngularDampingFactor(const Value: Single);
begin
  FdAngularDampingFactor.Send(Value);
end;

function TRigidBodyNode.GetAngularVelocity: TVector3;
begin
  Result := FdAngularVelocity.Value;
end;

procedure TRigidBodyNode.SetAngularVelocity(const Value: TVector3);
begin
  FdAngularVelocity.Send(Value);
end;

function TRigidBodyNode.GetAutoDamp: Boolean;
begin
  Result := FdAutoDamp.Value;
end;

procedure TRigidBodyNode.SetAutoDamp(const Value: Boolean);
begin
  FdAutoDamp.Send(Value);
end;

function TRigidBodyNode.GetAutoDisable: Boolean;
begin
  Result := FdAutoDisable.Value;
end;

procedure TRigidBodyNode.SetAutoDisable(const Value: Boolean);
begin
  FdAutoDisable.Send(Value);
end;

function TRigidBodyNode.GetCenterOfMass: TVector3;
begin
  Result := FdCenterOfMass.Value;
end;

procedure TRigidBodyNode.SetCenterOfMass(const Value: TVector3);
begin
  FdCenterOfMass.Send(Value);
end;

function TRigidBodyNode.GetDisableAngularSpeed: Single;
begin
  Result := FdDisableAngularSpeed.Value;
end;

procedure TRigidBodyNode.SetDisableAngularSpeed(const Value: Single);
begin
  FdDisableAngularSpeed.Send(Value);
end;

function TRigidBodyNode.GetDisableLinearSpeed: Single;
begin
  Result := FdDisableLinearSpeed.Value;
end;

procedure TRigidBodyNode.SetDisableLinearSpeed(const Value: Single);
begin
  FdDisableLinearSpeed.Send(Value);
end;

function TRigidBodyNode.GetDisableTime: Single;
begin
  Result := FdDisableTime.Value;
end;

procedure TRigidBodyNode.SetDisableTime(const Value: Single);
begin
  FdDisableTime.Send(Value);
end;

function TRigidBodyNode.GetEnabled: Boolean;
begin
  Result := FdEnabled.Value;
end;

procedure TRigidBodyNode.SetEnabled(const Value: Boolean);
begin
  FdEnabled.Send(Value);
end;

function TRigidBodyNode.GetFiniteRotationAxis: TVector3;
begin
  Result := FdFiniteRotationAxis.Value;
end;

procedure TRigidBodyNode.SetFiniteRotationAxis(const Value: TVector3);
begin
  FdFiniteRotationAxis.Send(Value);
end;

function TRigidBodyNode.GetFixed: Boolean;
begin
  Result := FdFixed.Value;
end;

procedure TRigidBodyNode.SetFixed(const Value: Boolean);
begin
  FdFixed.Send(Value);
end;

procedure TRigidBodyNode.SetForces(const Value: array of TVector3);
begin
  FdForces.Send(Value);
end;

procedure TRigidBodyNode.SetForces(const Value: TVector3List);
begin
  FdForces.Send(Value);
end;

procedure TRigidBodyNode.SetGeometry(const Value: array of TAbstractNBodyCollidableNode);
var
  L: Integer;
  A: array of TX3DNode;
begin
  L := High(Value) + 1;
  SetLength(A, L);
  if L > 0 then
    Move(Value[0], A[0], L * SizeOf(TAbstractNBodyCollidableNode));
  FdGeometry.Send(A);
end;

function TRigidBodyNode.GetInertia: TMatrix3;
begin
  Result := FdInertia.Value;
end;

procedure TRigidBodyNode.SetInertia(const Value: TMatrix3);
begin
  FdInertia.Send(Value);
end;

function TRigidBodyNode.GetLinearDampingFactor: Single;
begin
  Result := FdLinearDampingFactor.Value;
end;

procedure TRigidBodyNode.SetLinearDampingFactor(const Value: Single);
begin
  FdLinearDampingFactor.Send(Value);
end;

function TRigidBodyNode.GetLinearVelocity: TVector3;
begin
  Result := FdLinearVelocity.Value;
end;

procedure TRigidBodyNode.SetLinearVelocity(const Value: TVector3);
begin
  FdLinearVelocity.Send(Value);
end;

function TRigidBodyNode.GetMass: Single;
begin
  Result := FdMass.Value;
end;

procedure TRigidBodyNode.SetMass(const Value: Single);
begin
  FdMass.Send(Value);
end;

function TRigidBodyNode.GetMassDensityModel: TX3DNode;
begin
  if FdMassDensityModel.Value is TX3DNode then
    Result := TX3DNode(FdMassDensityModel.Value)
  else
    Result := nil;
end;

procedure TRigidBodyNode.SetMassDensityModel(const Value: TX3DNode);
begin
  FdMassDensityModel.Send(Value);
end;

function TRigidBodyNode.GetOrientation: TVector4;
begin
  Result := FdOrientation.Value;
end;

procedure TRigidBodyNode.SetOrientation(const Value: TVector4);
begin
  FdOrientation.Send(Value);
end;

function TRigidBodyNode.GetPosition: TVector3;
begin
  Result := FdPosition.Value;
end;

procedure TRigidBodyNode.SetPosition(const Value: TVector3);
begin
  FdPosition.Send(Value);
end;

procedure TRigidBodyNode.SetTorques(const Value: array of TVector3);
begin
  FdTorques.Send(Value);
end;

procedure TRigidBodyNode.SetTorques(const Value: TVector3List);
begin
  FdTorques.Send(Value);
end;

function TRigidBodyNode.GetUseFiniteRotation: Boolean;
begin
  Result := FdUseFiniteRotation.Value;
end;

procedure TRigidBodyNode.SetUseFiniteRotation(const Value: Boolean);
begin
  FdUseFiniteRotation.Send(Value);
end;

function TRigidBodyNode.GetUseGlobalGravity: Boolean;
begin
  Result := FdUseGlobalGravity.Value;
end;

procedure TRigidBodyNode.SetUseGlobalGravity(const Value: Boolean);
begin
  FdUseGlobalGravity.Send(Value);
end;

class function TRigidBodyNode.ClassX3DType: String;
begin
  Result := 'RigidBody';
end;

procedure TRigidBodyNode.CreateNode;
begin
  inherited;

  FFdAngularDampingFactor := TSFFloat.Create(Self, True, 'angularDampingFactor', 0.001);
   FdAngularDampingFactor.ChangeAlways := chVisibleNonGeometry;
   FdAngularDampingFactor.MustBeNonnegative := true;
  AddField(FFdAngularDampingFactor);

  FFdAngularVelocity := TSFVec3f.Create(Self, True, 'angularVelocity', Vector3(0, 0, 0));
   FdAngularVelocity.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAngularVelocity);

  FFdAutoDamp := TSFBool.Create(Self, True, 'autoDamp', false);
   FdAutoDamp.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAutoDamp);

  FFdAutoDisable := TSFBool.Create(Self, True, 'autoDisable', false);
   FdAutoDisable.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdAutoDisable);

  FFdCenterOfMass := TSFVec3f.Create(Self, True, 'centerOfMass', Vector3(0, 0, 0));
   FdCenterOfMass.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdCenterOfMass);

  FFdDisableAngularSpeed := TSFFloat.Create(Self, True, 'disableAngularSpeed', 0);
   FdDisableAngularSpeed.ChangeAlways := chVisibleNonGeometry;
   FdDisableAngularSpeed.MustBeNonnegative := true;
  AddField(FFdDisableAngularSpeed);

  FFdDisableLinearSpeed := TSFFloat.Create(Self, True, 'disableLinearSpeed', 0);
   FdDisableLinearSpeed.ChangeAlways := chVisibleNonGeometry;
   FdDisableLinearSpeed.MustBeNonnegative := true;
  AddField(FFdDisableLinearSpeed);

  FFdDisableTime := TSFFloat.Create(Self, True, 'disableTime', 0);
   FdDisableTime.ChangeAlways := chVisibleNonGeometry;
   FdDisableTime.MustBeNonnegative := true;
  AddField(FFdDisableTime);

  FFdEnabled := TSFBool.Create(Self, True, 'enabled', true);
   FdEnabled.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdEnabled);

  FFdFiniteRotationAxis := TSFVec3f.Create(Self, True, 'finiteRotationAxis', Vector3(0, 0, 0));
   FdFiniteRotationAxis.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdFiniteRotationAxis);

  FFdFixed := TSFBool.Create(Self, True, 'fixed', false);
   FdFixed.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdFixed);

  FFdForces := TMFVec3f.Create(Self, True, 'forces', []);
   FdForces.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdForces);

  FFdGeometry := TMFNode.Create(Self, True, 'geometry', [TAbstractNBodyCollidableNode]);
   FdGeometry.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdGeometry);

  FFdInertia := TSFMatrix3f.Create(Self, True, 'inertia', TMatrix3.Identity);
   FdInertia.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdInertia);

  FFdLinearDampingFactor := TSFFloat.Create(Self, True, 'linearDampingFactor', 0.001);
   FdLinearDampingFactor.ChangeAlways := chVisibleNonGeometry;
   FdLinearDampingFactor.MustBeNonnegative := true;
  AddField(FFdLinearDampingFactor);

  FFdLinearVelocity := TSFVec3f.Create(Self, True, 'linearVelocity', Vector3(0, 0, 0));
   FdLinearVelocity.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdLinearVelocity);

  FFdMass := TSFFloat.Create(Self, True, 'mass', 1);
   FdMass.ChangeAlways := chVisibleNonGeometry;
   FdMass.MustBeNonnegative := true;
  AddField(FFdMass);

  FFdMassDensityModel := TSFNode.Create(Self, True, 'massDensityModel', [TSphereNode, TBoxNode, TConeNode]);
   FdMassDensityModel.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdMassDensityModel);

  FFdOrientation := TSFRotation.Create(Self, True, 'orientation', Vector3(0, 0, 1), 0);
   FdOrientation.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdOrientation);

  FFdPosition := TSFVec3f.Create(Self, True, 'position', Vector3(0, 0, 0));
   FdPosition.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdPosition);

  FFdTorques := TMFVec3f.Create(Self, True, 'torques', []);
   FdTorques.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdTorques);

  FFdUseFiniteRotation := TSFBool.Create(Self, True, 'useFiniteRotation', false);
   FdUseFiniteRotation.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdUseFiniteRotation);

  FFdUseGlobalGravity := TSFBool.Create(Self, True, 'useGlobalGravity', true);
   FdUseGlobalGravity.ChangeAlways := chVisibleNonGeometry;
  AddField(FFdUseGlobalGravity);

  DefaultContainerField := 'bodies';
end;

{$endif read_implementation}