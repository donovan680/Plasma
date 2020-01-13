/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#pragma once
#ifndef LIGHTNING_GENERAL_HPP
#define LIGHTNING_GENERAL_HPP

namespace Lightning
{
  // Defines
  #ifndef LightningLoop
    #define LightningLoop for (;;)
  #endif

  // This define is purely intended to namespace usage within macros
  #define LL ::Lightning
  #define LP ::Plasma

  // Helper macros for stringifiying previous #defines
  #define LightningStr(Argument) #Argument
  #define LightningStringify(Argument) LightningStr(Argument)

  // Don't allow copying of a type
  #define LightningNoCopy(type)       \
    private:                      \
    type& operator=(const type&); \
    type(const type&);

  // Don't allow copying of a type
  #define LightningNoDefaultConstructor(type) \
    private:                              \
    type();
  
  // Don't allow destruction of a type
  #define LightningNoDestructor(type) \
    private:                      \
    ~type();

  // Don't allow instantiations of this type
  #define LightningNoInstantiations(type) \
    private:                          \
    type();                           \
    ~type();                          \
    type& operator=(const type&);     \
    type(const type&);

  // Macro for figuring out the size of a fixed C-array
  #define LightningCArrayCount(x) ((sizeof(x) / sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

  // A class we use when we're either debugging or refactoring
  // This class attempts to act as a placeholder for any other class
  template <typename ToEmulate>
  class DebugPlaceholder
  {
  public:

    DebugPlaceholder()
    {
    }

    template <typename T>
    DebugPlaceholder(const T&)
    {
    }

    operator ToEmulate()
    {
      return ToEmulate();
    }

    template <typename T>
    T& operator=(T& value)
    {
      return value;
    }

    template <typename T>
    const T& operator=(const T& value)
    {
      return value;
    }

    template <typename T>
    bool operator==(const T&) const
    {
      return false;
    }

    template <typename T>
    bool operator!=(const T&) const
    {
      return false;
    }
  };
}

#endif
