#pragma once

namespace Plasma
{

DeclareEnum7(LightningShaderIRBaseType, Op, ConstantLiteral, DataType, Function, Block, Comment, Extension);
DeclareEnum3(BlockType, Direct, Selection, Loop);
DeclareEnum15(ShaderIRTypeBaseType, Bool, Float, Int, Vector, Matrix, Struct, Image, Sampler, SampledImage, FixedArray, RuntimeArray, Void, Function, Pointer, Unknown)

typedef spv::Op OpType;
class LightningShaderIRLibrary;
class LightningShaderIRType;
class LightningShaderIRFunction;
class SpirVExtensionLibrary;

class LightningShaderIRComments
{
public:
  void Add(StringParam comment)
  {
    mComments.PushBack(comment);
  }
  Array<String> mComments;
};

class LightningShaderSourceLocation
{
public:
  Array<Lightning::CodeLocation> mCodeLocations;
};

class LightningShaderDebugInfo
{
public:
  void Clear()
  {
    mLocations.mCodeLocations.Clear();
    mComments.mComments.Clear();
  }
  LightningShaderSourceLocation mLocations;
  LightningShaderIRComments mComments;
};

//-------------------------------------------------------------------ILightningShaderIR
class ILightningShaderIR
{
public:
  ILightningShaderIR(LightningShaderIRBaseType::Enum baseType) : mIRType(baseType) {};
  virtual ~ILightningShaderIR() {};

  template <typename AsType>
  AsType* As()
  {
    if(mIRType == AsType::mStaticBaseType)
      return (AsType*)this;
    return nullptr;
  }
  template <typename AsType>
  AsType* AsAssert()
  {
    ErrorIf(mIRType != AsType::mStaticBaseType, "Invalid type cast");
    return (AsType*)this;
  }

  LightningShaderIRBaseType::Enum mIRType;
  LightningShaderDebugInfo mDebugInfo;
  String mDebugResultName;
};

//-------------------------------------------------------------------LightningShaderIRConstantLiteral
/// Represents a constant value literal such as the number 1.
class LightningShaderIRConstantLiteral : public ILightningShaderIR
{
public:
  const static LightningShaderIRBaseType::Enum mStaticBaseType = LightningShaderIRBaseType::ConstantLiteral;

  LightningShaderIRConstantLiteral(Lightning::Any value) : ILightningShaderIR(mStaticBaseType)
  {
    mValue = value;
  }

  Lightning::Any mValue;
};

//-------------------------------------------------------------------LightningShaderExtensionImport
class LightningShaderExtensionImport : public ILightningShaderIR
{
public:
  const static LightningShaderIRBaseType::Enum mStaticBaseType = LightningShaderIRBaseType::Extension;
  LightningShaderExtensionImport(SpirVExtensionLibrary* library) : ILightningShaderIR(mStaticBaseType)
  {
    mLibrary = library;
  }

  SpirVExtensionLibrary* mLibrary;
};

//-------------------------------------------------------------------LightningShaderIROp
class LightningShaderIROp : public ILightningShaderIR
{
public:
  const static LightningShaderIRBaseType::Enum mStaticBaseType = LightningShaderIRBaseType::Op;

  LightningShaderIROp(OpType opType);

  bool IsTerminator();
  bool IsResultPointerType();

  /// If this is a pointer type then the dereference type is returned, otherwise this type itself is returned.
  LightningShaderIRType* GetValueType();
  /// If this is a value type then the pointer type is returned, otherwise this type itself is returned.
  LightningShaderIRType* GetPointerType();

  OpType mOpType;
  Array<ILightningShaderIR*> mArguments;
  LightningShaderIRType* mResultType;
};

//-------------------------------------------------------------------BasicBlock
class BasicBlock : public ILightningShaderIR
{
public:
  const static LightningShaderIRBaseType::Enum mStaticBaseType = LightningShaderIRBaseType::Block;

  BasicBlock();
  ~BasicBlock();

  void AddOp(ILightningShaderIR* op);

  // Local variable must declared before all other lines in the starting block. This separation makes this easier.
  Array<ILightningShaderIR*> mLocalVariables;
  Array<ILightningShaderIR*> mLines;

  /// What kind of a block is this? A basic block with simple
  /// statements? A if block (selection)? A loop?
  BlockType::Enum mBlockType;
  // If this is a loop/selection then these points are used to generate the code needed
  // for declaring structured control flow. Additionally these are used to help generate
  // required branching instructions.
  BasicBlock* mMergePoint;
  BasicBlock* mContinuePoint;

  ILightningShaderIR* mTerminatorOp;
};

//-------------------------------------------------------------------EntryPointInfo
/// Stores information about any found entry point on a type.
/// This is necessary to generate the first few sections of a valid spir-v file.
class EntryPointInfo
{
public:
  EntryPointInfo();

  /// The entry point function
  LightningShaderIRFunction* mEntryPointFn;
  /// What kind of fragment type this entry point is.
  FragmentType::Enum mFragmentType;
  /// The global variable initializer function that the entry point will call.
  /// The back-end translation will replace this with a new function that actually
  /// calls all referenced global variable initializers.
  LightningShaderIRFunction* mGlobalsInitializerFunction;
  /// Any extra capability modes for this entry point (e.g. Geometry)
  Array<spv::Capability> mCapabilities;
  /// Any execution mode instructions for this entry point (e.g. geometry max vertices)
  BasicBlock mExecutionModes;
  /// A block of all of the decorations for variables
  BasicBlock mDecorations;
  /// The declared global variables
  BasicBlock mVariables;
  /// The declared variables that are part of the interface for the
  /// entry point function (required for OpEntryPoint)
  Array<LightningShaderIROp*> mInterface;

  /// The reflection data of all of the resources tied to this entry point.
  ShaderStageInterfaceReflection mStageReflectionData;

  /// Late bound functions are used to replace all instances of function reference with
  /// another during back-end generation. This is needed in particular for the Geometry
  /// shader stage's Append function which needs to be unique to each composite (due to pass-through).
  OrderedHashMap<LightningShaderIRFunction*, LightningShaderIRFunction*> mLateBoundFunctions;
};

//-------------------------------------------------------------------LightningShaderIRFunction
/// Represents a function type for spir-v.
class LightningShaderIRFunction : public ILightningShaderIR
{
public:
  const static LightningShaderIRBaseType::Enum mStaticBaseType = LightningShaderIRBaseType::Function;

  LightningShaderIRFunction();
  ~LightningShaderIRFunction();

  /// Get the shader type that this function returns.
  LightningShaderIRType* GetReturnType();

  String mName;

  /// The type of this function. Arg0 is Return type, remaining args are the parameters
  LightningShaderIRType* mFunctionType;

  // Parameters must be declared before the first block of a function.
  // This block makes it easier to deal with this requirement.
  BasicBlock mParameterBlock;
  Array<BasicBlock*> mBlocks;

  /// Meta information about this functions, such as attributes.
  ShaderIRFunctionMeta* mMeta;
};

//-------------------------------------------------------------------LightningShaderIRType
/// Represents a type, such as Real or a struct.
class LightningShaderIRType : public ILightningShaderIR
{
public:
  const static LightningShaderIRBaseType::Enum mStaticBaseType = LightningShaderIRBaseType::DataType;

  LightningShaderIRType();
  ~LightningShaderIRType();

  LightningShaderIRFunction* CreateFunction(LightningShaderIRLibrary* library);

  /// Adds a member variable to this type.
  void AddMember(LightningShaderIRType* memberType, StringParam memberName);

  /// Gets a sub-type at the given index from this type. Sub types are only valid on structs/functions.
  LightningShaderIRType* GetSubType(int index) const;
  /// Returns the number of sub-types contained. Only valid on structs/functions.
  size_t GetSubTypeCount();
  /// Finds a sub-member's name via the member index. For debug names only now.
  String GetMemberName(size_t memberIndex);

  /// How many bytes does this type require? Includes sub-type padding.
  size_t GetByteSize() const;
  /// What starting byte alignment does this type require?
  size_t GetByteAlignment() const;
  /// What is the base primitive type. If this is a vector or matrix it'll return the
  /// underlying component type. If this is a bool, integer, or float then that is returned.
  /// Otherwise the stored type (e.g. struct) will be returned.
  ShaderIRTypeBaseType::Enum GetBasePrimitiveType() const;

  /// Find the first attribute by the given name if it exists.
  ShaderIRAttribute* FindFirstAttribute(StringParam attributeName) const;
  /// Is this type a pointer or value type?
  bool IsPointerType();
  /// Does this type have to be a global? This is determined by the "StorageClass" attribute.
  bool IsGlobalType() const;
  /// If this is a pointer type then the dereference type is returned, otherwise this type itself is returned.
  LightningShaderIRType* GetValueType();
  /// If this is a value type then the pointer type is returned, otherwise this type itself is returned.
  LightningShaderIRType* GetPointerType();

  String mName;
  ShaderIRTypeBaseType::Enum mBaseType;

  /// The functions owned by this type
  Array<LightningShaderIRFunction*> mFunctions;
  /// If this type doesn't have an explicit default constructor then this is the auto-generated one that 
  /// does the same thing as lightning's default constructor (i.e. invoke the pre-constructor)
  LightningShaderIRFunction* mAutoDefaultConstructor;

  /// The lightning type this came from
  Lightning::BoundType* mLightningType;
  /// What library owns this type
  LightningShaderIRLibrary* mShaderLibrary;
  /// Any meta information about this type such as attributes.
  ShaderIRTypeMeta* mMeta;

  /// Only valid on scalar/vector/matrix types
  size_t mComponents;
  LightningShaderIRType* mComponentType;
  // @JoshD: Unify with subtypes later?
  Array<ILightningShaderIR*> mParameters;
  HashMap<String, int> mMemberNamesToIndex;
  HashMap<ShaderFieldKey, int> mMemberKeysToIndex;
  /// If this is a value type then this points to the corresponding pointer type. Otherwise this is null.
  LightningShaderIRType* mPointerType;
  /// If this is a pointer type then this points to the corresponding value type. Otherwise this is null.
  LightningShaderIRType* mDereferenceType;

  spv::StorageClass mStorageClass;
  EntryPointInfo* mEntryPoint;

  // @JoshD: Turn into flags later
  /// Does this type have a main function necessary for compositing?
  bool mHasMainFunction;
};

/// Returns what the component type is (only valid for scalars (null), vectors, and matrices)
LightningShaderIRType* GetComponentType(LightningShaderIRType* compositeType);
bool IsScalarType(LightningShaderIRType* compositeType);
LightningShaderIRType* GetImageTypeFromSampledImage(LightningShaderIRType* samplerType);
/// Returns the required stride of the given type with a base alignment factor (rounds up to nearest multiple of alignment)
int GetStride(LightningShaderIRType* type, float baseAlignment);
size_t GetSizeAfterAlignment(size_t size, size_t baseAlignment);

// Generate a unique identifier for a template type with no filled in arguments.
// Used for finding 'base' template types.
typedef String TemplateTypeKey;
TemplateTypeKey GenerateTemplateTypeKey(Lightning::BoundType* lightningType);

/// Given a field name (after any extra mangling) and the owning class type, generate the property name used to uniquely identify the field.
String GenerateSpirVPropertyName(StringParam fieldName, StringParam ownerType);
/// Given a field name (after any extra mangling) and the owning class type, generate the property name used to uniquely identify the field.
String GenerateSpirVPropertyName(StringParam fieldName, LightningShaderIRType* ownerType);

/// Get all spirv opocode string names. The returned strings don't contain
/// the leading "Op" that the disassembler generates.
Array<String> GetOpcodeNames();

}//namespace Plasma
