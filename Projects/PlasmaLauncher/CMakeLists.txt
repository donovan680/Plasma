################################################################################
# Add any files that need to be manually added in this file.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
if(${PLASMA_BUILD_PlasmaLauncher})
    add_subdirectory(PlasmaLauncher)
    set(Plasma_OptionalTarget_PlasmaLauncher PlasmaLauncher PARENT_SCOPE)
endif()

if(${PLASMA_BUILD_PlasmaLauncherSharedLibrary})
    add_subdirectory(PlasmaLauncherSharedLibrary)
    set(Plasma_OptionalTarget_PlasmaLauncherSharedLibrary PlasmaLauncherSharedLibrary PARENT_SCOPE)
endif()