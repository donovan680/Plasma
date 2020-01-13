################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
target_sources(Common
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/CommonForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CommonStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CommonStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Guid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Singleton.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Time.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Time.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ThreadableLoop.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ThreadableLoop.hpp
    ${CMAKE_CURRENT_LIST_DIR}/VirtualAny.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/Algorithm.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/Allocator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/Array.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/ArrayMap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/ArraySet.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/BitStream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/BitStream.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/BitStream.inl
    ${CMAKE_CURRENT_LIST_DIR}/Containers/BlockArray.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/ByteBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/ByteBuffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/ContainerCommon.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/CyclicArray.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/HashedContainer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/Hashing.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/HashMap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/HashSet.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/InList.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/OrderedHashMap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/OrderedHashSet.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/OwnedArray.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/SlotMap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/SortedArray.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/TypeTraits.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Containers/UnsortedMap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Diagnostic/Console.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Diagnostic/Console.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Diagnostic/Diagnostic.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Diagnostic/Diagnostic.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Lexer/Lexer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Lexer/Lexer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Lexer/Lexer.inl
    ${CMAKE_CURRENT_LIST_DIR}/Math/BasicNativeTypesMath.inl
    ${CMAKE_CURRENT_LIST_DIR}/Math/BlockVector3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BlockVector3.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BoolVector2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BoolVector2.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BoolVector3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BoolVector3.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BoolVector4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/BoolVector4.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/ByteColor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/ColorDefinitions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/ConjugateGradient.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Curve.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Curve.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/DecomposedMatrix4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/DecomposedMatrix4.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/ErrorCallbacks.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/EulerAngles.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/EulerAngles.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/EulerOrder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/EulerOrder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/ExtendableMath.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/ExtendableMath.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/GaussSeidelSolver.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/GenericVector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/GenericVector.inl
    ${CMAKE_CURRENT_LIST_DIR}/Math/IndexPolicies.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/IntVector2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/IntVector2.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/IntVector3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/IntVector3.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/IntVector4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/IntVector4.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/JacobiSolver.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Math.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Math.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/MathImports.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/MathToString.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/MathToString.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Matrix2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Matrix2.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Matrix3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Matrix3.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Matrix4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Matrix4.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/MatrixStorage.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Numerical.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Numerical.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Quaternion.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Quaternion.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Random.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Random.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Reals.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Reals.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/SharedVectorFunctions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector2.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector3.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector3.inl
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/Vector4.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/VectorHashPolicy.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Math/WeightedProbabilityTable.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Block.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Block.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Graph.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Graph.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Heap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Heap.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/LocalStackAllocator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Memory.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Pool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Pool.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Stack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/Stack.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Memory/PlasmaAllocator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Atomic.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Audio.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Browser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Main.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/MainLoop.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/CallStack.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/ComPort.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/CrashHandler.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Debug.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/DebugSymbolInformation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/DirectoryWatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/DirectoryWatcher.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/ExecutableResource.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/ExternalLibrary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/File.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/File.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FileEvents.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FileEvents.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FilePath.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FilePath.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FileSystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FileSystem.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/FpControl.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Intrinsics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Intrinsics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/IpAddress.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/IpAddress.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Lock.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/OsHandle.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Peripherals.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/PlatformStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/PrivateImplementation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Process.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Process.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Registry.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Renderer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/RendererEnumerations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Resolution.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Shell.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Shell.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Socket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Socket.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/SocketConstants.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/SocketEnums.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Thread.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Thread.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/ThreadSync.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Timer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/TimerBlock.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/UnicodeUtility.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/UnicodeUtility.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Utilities.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/Utilities.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/WebRequest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Platform/WebRequest.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Regex/Regex.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Regex/Regex.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StlBinding/Array.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StlBinding/Associative.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StlBinding/String.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/CharacterTraits.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/CharacterTraits.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/FixedString.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/Rune.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/Rune.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/String.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/String.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringBuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringBuilder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringConversion.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringConversion.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringRange.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringRange.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringUtility.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/StringUtility.hpp
    ${CMAKE_CURRENT_LIST_DIR}/String/ToString.cpp
    ${CMAKE_CURRENT_LIST_DIR}/String/ToString.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/BasicNativeTypes.inl
    ${CMAKE_CURRENT_LIST_DIR}/Utility/BitField.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/BitMath.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/BitTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/ByteEnum.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Callback.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Callback.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/ConditionalRange.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Determinism.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Determinism.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/EnumDeclaration.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/ForEachRange.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/ForEachRange.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Functor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Functor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Guid.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/HalfFloat.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/HalfFloat.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/IdSequence.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/IdStore.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Image.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/ItemCache.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Log2.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/MaxSizeof.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Misc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Misc.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/NativeType.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/NativeType.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/PointerCast.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Rect.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/SpinLock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/SpinLock.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Standard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Status.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Status.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Stream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Stream.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/TextStream.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Typedefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/UintNType.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/UniquePointer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Variant.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Variant.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Variant.inl
    ${CMAKE_CURRENT_LIST_DIR}/Utility/VariantConfig.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Web.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utility/Web.hpp
)
