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
{$ifndef CASTLE_SLIM_NODES}
    function GetMetadata: TAbstractMetadataNode;
    procedure SetMetadata(const Value: TAbstractMetadataNode);
{$endif not CASTLE_SLIM_NODES}
  public
    { Create node fields and events. }
    procedure CreateNode; override;
    class function ClassX3DType: String; override;

{$ifndef CASTLE_SLIM_NODES}
    strict private FFdMetadata: TSFNode;
    { Internal wrapper for property @code(Metadata). This wrapper API may change, we advise to access simpler @code(Metadata) instead, if it is defined (TODO: for now, some field types do not have a simpler counterpart). }
    public property FdMetadata: TSFNode read FFdMetadata;
{$endif not CASTLE_SLIM_NODES}
{$ifndef CASTLE_SLIM_NODES}
    {  }
    property Metadata: TAbstractMetadataNode read GetMetadata write SetMetadata;
{$endif not CASTLE_SLIM_NODES}

{$endif read_interface}

{$ifdef read_implementation}

{ TAbstractNode ----------------------------------------------- }

{$ifndef CASTLE_SLIM_NODES}
function TAbstractNode.GetMetadata: TAbstractMetadataNode;
begin
  if FdMetadata.Value is TAbstractMetadataNode then
    Result := TAbstractMetadataNode(FdMetadata.Value)
  else
    Result := nil;
end;

procedure TAbstractNode.SetMetadata(const Value: TAbstractMetadataNode);
begin
  FdMetadata.Send(Value);
end;

{$endif not CASTLE_SLIM_NODES}
class function TAbstractNode.ClassX3DType: String;
begin
  Result := 'X3DNode';
end;

procedure TAbstractNode.CreateNode;
begin
  inherited;

{$ifndef CASTLE_SLIM_NODES}
  FFdMetadata := TSFNode.Create(Self, True, 'metadata', [TAbstractMetadataNode]);
   FdMetadata.ChangeAlways := chNone;
  AddField(FFdMetadata);
{$endif not CASTLE_SLIM_NODES}
end;

{$endif read_implementation}