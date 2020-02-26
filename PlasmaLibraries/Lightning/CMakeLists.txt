################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_library(Lightning "")

set_target_properties(Lightning PROPERTIES FOLDER "PlasmaLibraries")
target_sources(Lightning
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Any.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Any.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ArrayClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ArrayClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Base64.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Base64.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Binding.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Binding.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/CodeGenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/CodeGenerator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/CodeLocation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/CodeLocation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Color.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Color.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/CompilationErrors.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/CompilationErrors.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Composition.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Composition.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ConsoleClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ConsoleClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ConstructorBinding.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Core.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/DataDrivenLexer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/DataDrivenLexer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/DataDrivenLexer.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Debugging.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Debugging.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Delegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Delegate.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/DestructibleBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/DestructibleBuffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Documentation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Documentation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ErrorDatabase.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ErrorDatabase.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Events.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Events.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ExecutableState.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ExecutableState.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/FilePathClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/FilePathClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/FileStreamClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/FileStreamClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Formatter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Formatter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Function.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Function.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/General.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/GrammarConstants.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/GrammarConstants.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Handle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Handle.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/HandleManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/HandleManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/HashContainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/HashContainer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/InstructionsEnum.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Json.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Library.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Library.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/LocalBuild.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Matrix.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Matrix.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Members.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Members.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/MethodBinding.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/MultiPrimitive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/MultiPrimitive.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Opcode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Opcode.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/OverloadResolver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/OverloadResolver.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Parser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Plugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Plugin.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ProcessClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/ProcessClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Project.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Project.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/RandomClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/RandomClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Range.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/RangeBinding.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Setup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Setup.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Sha1.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Sha1.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Shared.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Shared.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/SharedReference.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StaticLibrary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StaticLibrary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StreamInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StreamInterface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StringBuilderClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StringBuilderClass.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StringConstants.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StringConstants.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StubCode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/StubCode.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Syntaxer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Syntaxer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/SyntaxTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/SyntaxTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/SyntaxTreeHelpers.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/SyntaxTreeHelpers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/TemplateBinding.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/TemplateBinding.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Timer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Token.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Tokenizer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Tokenizer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/TokenReader.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Traits.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Traits.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Type.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Type.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/UntypedBlockArray.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/VirtualMachine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/VirtualMachine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/VirtualMethodBinding.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/VirtualTableBinding.inl
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/WebSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/WebSocket.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Wrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Wrapper.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Lightning.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Project/Lightning/Lightning.hpp
)

target_include_directories(Lightning
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../Lightning/Project
    ${CMAKE_CURRENT_LIST_DIR}/../Lightning/Project/Lightning
    ${VLD_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(Lightning
                    PUBLIC
                    Common
                    ${VLD_LIBRARIES}
)

plasma_multitarget_output_settings(
    Lightning
    CONFIGS ${supported_configs}
    BASEPATH ${plasma_build_out}
    PLATFORM ${platform}
    CONFIG ${configuration}
    BITS ${bit}
    TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
    PRECOMPILED_HEADER_NAME "Lightning.hpp"
    PRECOMPILED_SOURCE_NAME "Lightning.cpp"
    TARGET_SUBFOLDER
)

plasma_source_group(${CMAKE_CURRENT_LIST_DIR} Lightning "")