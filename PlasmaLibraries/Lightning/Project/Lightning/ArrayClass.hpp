/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#pragma once
#ifndef LIGHTNING_ARRAY_HPP
#define LIGHTNING_ARRAY_HPP

namespace Lightning
{
  // Instantiates an array template when requested
  PlasmaShared BoundType* InstantiateArray
  (
    LibraryBuilder& builder,
    StringParam baseName,
    StringParam fullyQualifiedName,
    const Array<Constant>& templateTypes,
    const void* userData
  );
  
  // For every instantiated array, it may want to look up information about what it Contains
  class PlasmaShared ArrayUserData
  {
  public:
    ArrayUserData();

    Type* ContainedType;
    BoundType* RangeType;
    BoundType* SelfType;
  };

  // This is the base definition of our array class
  // It is not technically the leaf level class, but it is binary compatible with the Lightning Array template
  // We add no members or virtuals in the derived class, and static assert that the sizes are the same
  template <typename T>
  class PlasmaSharedTemplate ArrayClass
  {
  public:
    // Constructor
    ArrayClass() :
      ModifyId(0)
    {
    }

    // Invalidates all active ranges via incrementing a modification id
    void Modified()
    {
      ++this->ModifyId;
    }

    // Our array is actually just an array of Any types
    // but for arrays of primitive/built in types, it will be optimized
    Array<T> NativeArray;

    // A special counter that we use to denote whenever the container has been modified
    Integer ModifyId;
  };

  static_assert(offsetof(ArrayClass<int>, NativeArray) == 0,
    "The native array must be at offset 0 so that we can binary reinterpret a Lightning ArrayClass as just a normal native Array (unsafe, but performant)");

  // These are all the specializations that are optimized to store exactly that data type
  // All values that are unknown will be stored as the 'Any' type
  #define LightningDeclareDefineArray(ElementType, Linkage)           \
    LightningDeclareCustomType(ArrayClass<ElementType>, LL::Core::GetInstance().GetBuilder()->InstantiateTemplate("Array", LightningConstants(LightningTypeId(ElementType)), LibraryArray(PlasmaInit, Core::GetInstance().GetBuilder()->BuiltLibrary)).Type, Linkage);

  #define LightningDeclareDefineValueArray(ElementType, Linkage)      \
    LightningDeclareDefineArray(ElementType, Linkage)                 \
    typedef ArrayClass<ElementType> Array##ElementType;

  #define LightningDeclareDefineHandleArray(ElementType, Linkage)     \
    LightningDeclareDefineArray(HandleOf<ElementType>, Linkage)       \
    typedef ArrayClass<HandleOf<ElementType>> Array##ElementType;

  // Pre-existing useful declarations
  typedef HandleOf<String> HandleOfString;
  LightningDeclareDefineValueArray (Handle        , PlasmaShared);
  LightningDeclareDefineValueArray (Delegate      , PlasmaShared);
  LightningDeclareDefineValueArray (Boolean       , PlasmaShared);
  LightningDeclareDefineValueArray (Boolean2      , PlasmaShared);
  LightningDeclareDefineValueArray (Boolean3      , PlasmaShared);
  LightningDeclareDefineValueArray (Boolean4      , PlasmaShared);
  LightningDeclareDefineValueArray (Byte          , PlasmaShared);
  LightningDeclareDefineValueArray (Integer       , PlasmaShared);
  LightningDeclareDefineValueArray (Integer2      , PlasmaShared);
  LightningDeclareDefineValueArray (Integer3      , PlasmaShared);
  LightningDeclareDefineValueArray (Integer4      , PlasmaShared);
  LightningDeclareDefineValueArray (Real          , PlasmaShared);
  LightningDeclareDefineValueArray (Real2         , PlasmaShared);
  LightningDeclareDefineValueArray (Real3         , PlasmaShared);
  LightningDeclareDefineValueArray (Real4         , PlasmaShared);
  LightningDeclareDefineValueArray (Quaternion    , PlasmaShared);
  LightningDeclareDefineValueArray (DoubleInteger , PlasmaShared);
  LightningDeclareDefineValueArray (DoubleReal    , PlasmaShared);
  LightningDeclareDefineValueArray (Any           , PlasmaShared);
  LightningDeclareDefineHandleArray(String        , PlasmaShared);
}

#endif
