################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_library(LightningScript "")

set_target_properties(LightningScript PROPERTIES FOLDER "Systems")

target_sources(LightningScript
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningPlugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningPlugin.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningScript.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningScript.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningScriptStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningScriptStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningPlasma.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LightningPlasma.hpp
)

target_include_directories(LightningScript 
PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(LightningScript
    PUBLIC
    Common
    Geometry
    Editor
) 

plasma_multitarget_output_settings(
    LightningScript
    CONFIGS ${supported_configs}
    BASEPATH ${plasma_build_out}
    PLATFORM ${platform}
    CONFIG ${configuration}
    BITS ${bit}
    TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
    PRECOMPILED_HEADER_NAME "Precompiled.hpp"
    PRECOMPILED_SOURCE_NAME "Precompiled.cpp"
    TARGET_SUBFOLDER
)

plasma_source_group(${CMAKE_CURRENT_LIST_DIR} LightningScript "") 