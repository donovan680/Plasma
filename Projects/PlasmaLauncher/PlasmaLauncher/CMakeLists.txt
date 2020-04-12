################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_executable(PlasmaLauncher "")

set_target_properties(PlasmaLauncher PROPERTIES FOLDER "Projects")
plasma_setup_library(PlasmaLauncher ${CMAKE_CURRENT_LIST_DIR} TRUE)
plasma_use_precompiled_header(PlasmaLauncher ${CMAKE_CURRENT_LIST_DIR})


set(platformSpecificSource)

# get the rc file so we get icons on windows builds
if (${PLASMA_PLATFORM} STREQUAL "Windows")
    set(platformSpecificSource
    ${PLASMA_PLATFORM_DATA_DIR}/PlasmaLauncher/PlasmaLauncher.rc
    ${PLASMA_PLATFORM_DATA_DIR}/PlasmaLauncher/Resource.h
    )
endif()

target_sources(PlasmaLauncher
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${platformSpecificSource}
)

target_include_directories(PlasmaLauncher 
    PUBLIC 
        ${CurrentDirectory}/../..
        ${CurrentDirectory}
        ${CurrentDirectory}/../PlasmaLauncherSharedLibrary
)

target_link_libraries(PlasmaLauncher
                      PUBLIC
                      Common
                      Gameplay
                      SpatialPartition 
                      LightningShaders
                      Serialization 
                      Support 
                      Geometry 
                      Widget 
                      Editor 
                      LightningScript 
                      Graphics 
                      Networking 
                      Meta 
                      Engine 
                      Physics 
                      Sound 
                      Startup 
                      Platform 
                      Content 
                      Dash 
                      Lightning 
                      UiWidget 
                      CodeTranslator
) 

plasma_copy_from_linked_libraries(PlasmaLauncher)