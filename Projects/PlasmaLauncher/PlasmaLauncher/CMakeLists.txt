################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
include(${CMAKE_CURRENT_LIST_DIR}/Generated.cmake)

set(platformSpecificSource)

# get the rc file so we get icons on windows builds
if (${platform} STREQUAL "Windows")
    set(platformSpecificSource
    ${plasma_platform_data}/PlasmaLauncher/PlasmaLauncher.rc
    ${plasma_platform_data}/PlasmaLauncher/Resource.h
    )
endif()

target_sources(PlasmaLauncher
    PRIVATE
    ${platformSpecificSource}
)
