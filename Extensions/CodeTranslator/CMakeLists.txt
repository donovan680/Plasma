################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_library(CodeTranslator "")

set_target_properties(CodeTranslator PROPERTIES FOLDER "Extensions")

PLASMA_setup_library(CodeTranslator ${CMAKE_CURRENT_LIST_DIR} TRUE)
PLASMA_use_precompiled_header(CodeTranslator ${CMAKE_CURRENT_LIST_DIR})

target_sources(CodeTranslator
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/CodeSplitWindow.cpp
  ${CMAKE_CURRENT_LIST_DIR}/CodeSplitWindow.hpp
  ${CMAKE_CURRENT_LIST_DIR}/CodeTranslatorCommands.cpp
  ${CMAKE_CURRENT_LIST_DIR}/CodeTranslatorCommands.hpp
  ${CMAKE_CURRENT_LIST_DIR}/CodeTranslatorStandard.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ShaderTranslationDebugHelper.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ShaderTranslationDebugHelper.hpp
)

target_include_directories(CodeTranslator
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/../
)

plasma_target_includes(CodeTranslator
  PUBLIC
    Engine
    LightningShaders
)