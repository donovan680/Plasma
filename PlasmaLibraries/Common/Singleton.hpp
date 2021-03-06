///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys, Trevor Sundberg
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{
//--------------------------------------------------------------------------------------- Empty Base
class EmptyBase
{
};

//----------------------------------------------------------------------------------- Lazy Singleton
template <typename T, typename Base = EmptyBase>
class LazySingleton : public Base
{
public:
  static T* GetInstance()
  {
    static T instance;
    return &instance;
  }

protected:
  LazySingleton(){}
};

#define PlasmaDeclareExplicitSingletonContents(T) \
public:                                         \
  static T* GetInstance()                       \
  {                                             \
    return mInstance;                           \
  }                                             \
                                                \
  static void Initialize()                      \
  {                                             \
    ReturnIf(mInstance != nullptr,,             \
      "The singleton is being "                 \
      "initialized more than once");            \
    mInstance = new T();                        \
  }                                             \
                                                \
  static void Destroy()                         \
  {                                             \
    delete mInstance;                           \
    mInstance = nullptr;                        \
  }                                             \
private:                                        \
  static T* mInstance;                          \
public:

#define PlasmaDefineExplicitSingletonContents(T)  \
  T* T::mInstance = nullptr;

//------------------------------------------------------------------------------- Explicit Singleton
template <typename T, typename Base = EmptyBase>
class ExplicitSingleton : public Base
{
public:
  PlasmaDeclareExplicitSingletonContents(T);

protected:
  ExplicitSingleton(){}
};

template <typename T, typename Base>
T* ExplicitSingleton<T, Base>::mInstance = nullptr;

}//namespace Plasma
