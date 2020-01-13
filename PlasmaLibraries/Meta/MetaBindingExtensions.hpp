///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg, Joshua Claeys
/// Copyright 2016-2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------------------------- Object Attributes
namespace ObjectAttributes
{

/// Object is not visible to default inspection
extern const String cHidden;
/// Object has documentation
extern const String cDocumented;
/// Object should explicitly not be documented
extern const String cDoNotDocument;
/// Object is always expanded in the property grid
extern const String cExpanded;
/// Core objects can not be removed from owner or added to new owner
extern const String cCore;
/// Signifies that this object should store the local property modifications
extern const String cStoreLocalModifications;
/// Object is a Proxy for another class
extern const String cProxy;
/// The proxy was created because we failed to construct an object of this type (likely due to 
/// an exception in the constructor)
extern const String cExceptionProxy;
/// For LightningComponent's, Initialize isn't called in an Editor Space. However, it the Component has
/// this attribute, Initialize will be called.
extern const String cRunInEditor;
/// Used to determine whether a type that 'IsA(Resource)' is an interface, or an actual resource type.
extern const String cResourceInterface;
/// Used for scripts. Allows a component to declare it is an interface for other types (i.e. Collider for BoxCollider)
extern const String cComponentInterface;
/// Used to specify that this component has a gizmo (via the archetype parameter)
extern const String cGizmo;
/// Used to specify that a script component is a Command.
extern const String cCommand;
/// Specify Tags for a script component and its associated Resource.
extern const String cTags;
/// Specify a keyboard shortcut for a script component with the Command attribute.
extern const String cShortcut;
extern const String cTool;

}//namespace ObjectFlags

 //------------------------------------------------------------------------------ Property Attributes
namespace PropertyAttributes
{

/// Implies both [Display] and [Serialize].
extern const String cProperty;
/// Used to hide members from auto-complete.
extern const String cInternal;
/// When this property is modified in the property grid, the property grid
/// will do a full rebuild allowing for custom property filters to be run
extern const String cInvalidatesObject;
/// When a Graphical is rendered, if this property exists on a Component of the same Cog 
/// as the Graphical, it will look for a matching input on the objects material 
/// and set the shader parameter.
extern const String cShaderInput;
/// When reverting an object, properties marked with this flag will not be reverted. This is
/// used for things like 'Transform::Translation'. When we revert an object's modifications,
/// we still want it to stay in the same location.
extern const String cLocalModificationOverride;
/// Should this property be serialized. This is implied by PropertyAttributes::cProperty.
extern const String cSerialize;
/// Deprecated. Same functionality as cSerialize. Kept around for legacy files.
extern const String cDeprecatedSerialized;
/// Mark the property as being a dependency on another component.
extern const String cDependency;
/// Should this property show up in the property grid. This is implied by PropertyAttributes::cProperty.
extern const String cDisplay;
/// Deprecated. Same functionality as cDisplay. Kept around for legacy files.
extern const String cDeprecatedEditable;
/// Used for customizing resource properties in scripts.
extern const String cResourceProperty;
/// Clones the Resource 
extern const String cRuntimeClone;
/// Used for renaming properties. First attribute parameter should be the old name.
extern const String cRenamedFrom;
/// Indicates the property should be replicated over the network.
extern const String cNetProperty;
/// Inside an Event dispatched over the network, this integer will be automatically filled with
/// the sending NetPeer's NetPeerId.
extern const String cNetPeerId;
/// Used to group properties in the property view. Must have a single string attribute parameter
/// which is the name of the group.
extern const String cGroup;
/// Used to specify a range for numbers being edited in the property grid.
extern const String cRange;
/// Used to specify that the value should be modified by a slider in the property grid.
extern const String cSlider;
/// Used to mark attribute parameters as optional. This is an internal attribute (not exposed to user).
extern const String cOptional;

}//namespace PropertyFlags

//------------------------------------------------------------------------------ Function Attributes
namespace FunctionAttributes
{

/// The function shows up in the property grid.
extern const String cProperty;
/// Used to hide the function from auto-complete.
extern const String cInternal;
/// The function shows up in the property grid.
extern const String cDisplay;
/// When this function is called from the property grid, the property grid will do a full rebuild
extern const String cInvalidatesObject;

}//namespace FunctionFlags

//------------------------------------------------------------------------- Serialization Attributes
namespace SerializationAttributes
{

// If it's not a primitive type, serialization will assume it can never be a modified property.
// Only its child properties can be modified.
// This was used to avoid checking if Transform.Translation.X is modified. It can never be
// modified because it's a primitive. Only Transform.Translation can be modified.
extern const String cSerializationPrimitive;

}//namespace SerializationAttributes

 // Uncategorized
extern const String cInvalidTypeName;

#define PlasmaBindDocumented() type->AddAttribute(::Plasma::ObjectAttributes::cDocumented)
#define PlasmaBindExpanded() type->AddAttribute(::Plasma::ObjectAttributes::cExpanded)

#define PlasmaBindSetup(SetupMode) type->HasOrAdd<::Plasma::CogComponentMeta>(type)->mSetupMode = (SetupMode)
#define PlasmaBindDependency(Type) type->HasOrAdd<::Plasma::CogComponentMeta>(type)->mDependencies.Insert(LightningTypeId(Type))
#define PlasmaBindInterface(Type)  type->HasOrAdd<::Plasma::CogComponentMeta>(type)->AddInterface(LightningTypeId(Type))
#define PlasmaBindTag(Tag)         type->HasOrAdd<::Plasma::CogComponentMeta>(type)->mTags.Insert(Tag)
#define PlasmaBindPropertyRename(oldName)  Add(new ::Plasma::MetaPropertyRename(oldName))
#define PlasmaSetPropertyGroup(groupName) Add(new ::Plasma::MetaGroup(groupName))
#define PlasmaLocalModificationOverride() AddAttribute(::Plasma::PropertyAttributes::cLocalModificationOverride)

void BindEventSent(LibraryBuilder& builder, BoundType* boundType, StringParam eventName, BoundType* eventType);
#define PlasmaBindEvent(EventName, EventType)  BindEventSent(builder, type, (EventName), LightningTypeId(EventType))
#define PlasmaBindExternalEvent(EventName, EventType, SenderType)  BindEventSent(builder, LightningTypeId(SenderType), (EventName), LightningTypeId(EventType))

//------------------------------------------------------------------------------------------- Events
namespace Events
{
DeclareEvent(PropertyModified);
DeclareEvent(PropertyModifiedIntermediate);

// The objects Components were changed
DeclareEvent(ComponentsModified);

// Used to signal to the property grid that it should rebuild. Will be sent when Components are modified
DeclareEvent(ObjectStructureModified);

// The object was changed in any way (will be sent when PropertyChanged, ComponentsChanged, and
// ObjectStructureModified are sent)
DeclareEvent(ObjectModified);
}

//---------------------------------------------------------------------------------- Meta Operations
// If the object supports undo/redo, this component should be added
class MetaOperations : public ReferenceCountedEventObject
{
public:
  LightningDeclareType(MetaOperations, TypeCopyMode::ReferenceType);

  // When a property is changed in the editor, this should be called to properly send events or
  // run any special functionality per object type.
  static void NotifyPropertyModified(HandleParam object, PropertyPathParam property,
                                    AnyParam oldValue, AnyParam newValue, bool intermediateChange);
  static void NotifyComponentsModified(HandleParam object);
  // Called when an object is modified in any way.
  static void NotifyObjectModified(HandleParam object, bool intermediateChange = false);

  // Id used in the UndoMap for the operation system. Currently, this id needs to be globally
  // unique between everything that implements this function. This could be made better by 
  // having an undo map per type, instead of a global one.
  virtual u64 GetUndoHandleId(HandleParam object);

  // Before all meta operations, this will be called and stored. When Undo is called,
  // RestoreUndoData will be called with the previously stored data.
  virtual Any GetUndoData(HandleParam object);

  // The given property was modified. This will be called on parents when a child property
  // is modified, as well as the child.
  //
  // e.g. When Cog.CameraViewport.CameraPath.Path is changed, you will get the events on
  // 1. Cog instance with "CameraViewport/CameraPath/Path" as the PropertyPath
  // 2. CameraViewport instance with "CameraPath/Path" as the PropertyPath
  // 3. Path instance with "Path" as the PropertyPath
  virtual void PropertyModified(HandleParam object, PropertyPathParam property, AnyParam oldValue,
                                AnyParam newValue, bool intermediateChange);

  // Called when any Component is added / moved / removed.
  virtual void ComponentsModified(HandleParam object);

  // The object was modified in any way (property modified, component added/moved/removed, property
  // marked as modified, property reverted, child restored, child order restored, etc...)
  virtual void ObjectModified(HandleParam object, bool intermediateChange);

  // When an operation is undone, the data returned from 'GetUndoData' will be given back to us here.
  virtual void RestoreUndoData(HandleParam object, AnyParam undoData) { }

  // Some editor operations require storing the state of and rebuilding of objects. Look at
  // ObjectRestoreState for more detail.
  virtual ObjectRestoreState* GetRestoreState(HandleParam object) { return nullptr; }
};

//----------------------------------------------------------------------------------- Property Event
class PropertyEvent : public Event
{
public:
  LightningDeclareType(PropertyEvent, TypeCopyMode::ReferenceType);

  PropertyEvent(HandleParam object, PropertyPathParam property,
                AnyParam oldValue, AnyParam newValue);

  Handle mObject;
  const PropertyPath& mProperty;
  Any mOldValue;
  Any mNewValue;
};

//--------------------------------------------------------------------------------------- Type Event
class TypeEvent : public Event
{
public:
  LightningDeclareType(TypeEvent, TypeCopyMode::ReferenceType);
  TypeEvent(BoundType* type) : mType(type) {}

  BoundType* mType;
};

//------------------------------------------------------------------------------------- Meta Display
class MetaDisplay : public ReferenceCountedEventObject
{
public:
  LightningDeclareType(MetaDisplay, TypeCopyMode::ReferenceType);

  virtual String GetName(HandleParam object) = 0;
  virtual String GetDebugText(HandleParam object) = 0;
};

//-------------------------------------------------------------------------------- Type Name Display
class TypeNameDisplay : public MetaDisplay
{
public:
  LightningDeclareType(TypeNameDisplay, TypeCopyMode::ReferenceType);

  String GetName(HandleParam object) override;
  String GetDebugText(HandleParam object) override;
};

//------------------------------------------------------------------------------ String Name Display
class StringNameDisplay : public MetaDisplay
{
public:
  LightningDeclareType(StringNameDisplay, TypeCopyMode::ReferenceType);
  StringNameDisplay(StringParam string);

  String GetName(HandleParam object) override;
  String GetDebugText(HandleParam object) override;

  String mString;
};

//-------------------------------------------------------------------------- Meta Transform Instance
class MetaTransformInstance
{
public:
  MetaTransformInstance(HandleParam instance = Handle())
    : mInstance(instance),
    mLocalTranslation(nullptr),
    mLocalRotation(nullptr),
    mLocalScale(nullptr),
    mWorldTranslation(nullptr),
    mWorldRotation(nullptr),
    mWorldScale(nullptr),
    mParentWorldMatrix(nullptr),
    mParentLocalMatrix(nullptr)
  {
    // Initialize the aabb to an invalid one so that we can take any other aabb
    // and combine with this without anything being affected.
    mAabb.SetInvalid();
  }

  // Returns whether or not the instance is null.
  bool IsNull();
  bool IsNotNull();

  // Local Transform
  Vec3 GetLocalTranslation();
  Quat GetLocalRotation();
  Vec3 GetLocalScale();

  void SetLocalTranslation(Vec3Param value);
  void SetLocalRotation(QuatParam value);
  void SetLocalScale(Vec3Param value);

  // World Transform
  Vec3 GetWorldTranslation();
  Quat GetWorldRotation();
  Vec3 GetWorldScale();

  // World Matrix
  Mat4 GetParentWorldMatrix();
  // Local Matrix
  Mat4 GetParentLocalMatrix();

  // Transform a local space point to parent space.
  Vec3 ToParent(Vec3Param local);

  // Transform for Cog, object instance for GeoElement, etc...
  Handle mInstance;

  // Consider removing this. It was added to mark the space as modified in Gizmos, but
  // that should be handle in the operation queue.
  Handle mSpace;

  // Local Transform Properties
  Property* mLocalTranslation;
  Property* mLocalRotation;
  Property* mLocalScale;

  // World Transform Properties
  Property* mWorldTranslation;
  Property* mWorldRotation;
  Property* mWorldScale;

  // Used to get the parents world matrix (your local space)
  Handle mParentInstance;
  Property* mParentWorldMatrix;
  Property* mParentLocalMatrix;

  // Used to get a size for focusing. Potentially remove and refactor later.
  Aabb mAabb;
};

typedef MetaTransformInstance& MetaTransformParam;

//----------------------------------------------------------------------------------- Meta Transform
// Allows objects to have transform type properties without the limitation of
// the object type being a Cog
class MetaTransform : public ReferenceCountedEventObject
{
public:
  LightningDeclareType(MetaTransform, TypeCopyMode::ReferenceType);
  virtual MetaTransformInstance GetInstance(HandleParam object) = 0;
};

//The "has" macro
#define has(type) Has<type>()

//An extension to the "has" macro
#define hasAll(type) HasRange<type>()

//------------------------------------------------------------------------------------ Array Binding
#define PlasmaDefineArrayType(arrayType)                                                                    \
  LightningDefineTemplateType(PlasmaMetaArray<arrayType>, builder, type)                                        \
  {                                                                                                       \
                                                                                                          \
  }                                                                                                       \
                                                                                                          \
  LightningDefineExternalBaseType(arrayType, TypeCopyMode::ReferenceType, builder, type)                      \
  {                                                                                                       \
    type->HandleManager = LightningManagerId(PointerManager);                                                 \
    type->Add(new PlasmaMetaArray<arrayType>());                                                            \
  }

#define PlasmaInitializeArrayTypeAs(arrayType, name)                          \
  LightningInitializeTypeAs(PlasmaMetaArray<arrayType>, "PlasmaMetaArray" name);    \
  LightningInitializeExternalTypeAs(arrayType, name);

//----------------------------------------------------------------------------------- Meta Attribute
class MetaAttribute : public ReferenceCountedEventObject
{
public:
  LightningDeclareType(MetaAttribute, TypeCopyMode::ReferenceType);
  virtual void PostProcess(Status& status, ReflectionObject* owner){}
};

} // namespace Plasma
