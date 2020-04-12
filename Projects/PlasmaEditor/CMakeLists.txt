################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_executable(PlasmaEditor "")

plasma_setup_library(PlasmaEditor ${CMAKE_CURRENT_LIST_DIR} TRUE)
plasma_use_precompiled_header(PlasmaEditor ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(PlasmaEditor PROPERTIES FOLDER "Projects")

set(platformSpecificSource)

# get the rc file so we get icons on windows builds
if (${PLASMA_PLATFORM} STREQUAL "Windows")
    set(platformSpecificSource
        ${PLASMA_PLATFORM_DATA_DIR}/PlasmaEditor/PlasmaEditor.rc
        ${PLASMA_PLATFORM_DATA_DIR}/PlasmaEditor/Resource.h
    )
endif()

target_sources(PlasmaEditor
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Startup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PlasmaCrashCallbacks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PlasmaCrashCallbacks.hpp
    ${platformSpecificSource}
)

target_link_libraries(PlasmaEditor
  PUBLIC
    Assimp
    CodeTranslator
    Common
    Content
    Editor
    Engine
    FreeType
    Gameplay
    Geometry
    Graphics
    Libpng
    Meta
    Networking
    Nvtt
    Opus
    Physics
    Platform
    Replication
    Scintilla
    Serialization
    Sound
    SpatialPartition
    SpirvCross
    SpirvHeaders
    SpirvTools
    Startup
    Support
    UiWidget
    Widget
    ZLib
    Lightning
    LightningScript
    LightningShaders
)

add_dependencies(PlasmaEditor
  BrowserSubProcess)

plasma_copy_from_linked_libraries(PlasmaEditor)