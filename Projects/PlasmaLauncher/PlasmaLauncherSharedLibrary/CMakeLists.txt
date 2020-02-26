################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(PlasmaLauncherSharedLibrary SHARED "")

set_target_properties(PlasmaLauncherSharedLibrary PROPERTIES FOLDER "Projects")

target_sources(PlasmaLauncherSharedLibrary
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/ActiveProjectMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ActiveProjectMenu.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BuildsMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BuildsMenu.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BuildStatus.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BuildStatus.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DeveloperNotes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DeveloperNotes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DiscoverMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DiscoverMenu.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Eula.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Eula.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ExtraModals.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ExtraModals.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Launcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Launcher.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherComponents.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherComponents.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherCrashCallbacks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherCrashCallbacks.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherDllStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherDllStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherStartup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherStartup.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherTasks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherTasks.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherWindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LauncherWindow.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Main.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NewProjectMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NewProjectMenu.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectCache.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectCache.hpp
    ${CMAKE_CURRENT_LIST_DIR}/RecentProjectsMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RecentProjectsMenu.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SettingsMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SettingsMenu.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Standalone.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Standalone.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TagFiltering.hpp
    ${CMAKE_CURRENT_LIST_DIR}/VersionSelector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/VersionSelector.hpp
)

target_include_directories(PlasmaLauncherSharedLibrary 
    PUBLIC 
        ${CurrentDirectory}/../../
        ${CurrentDirectory}
        ${Dependencies_Root}
        ${Source_Root}
)

target_link_libraries(PlasmaLauncherSharedLibrary
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

plasma_multitarget_output_settings(
    PlasmaLauncherSharedLibrary
    CONFIGS ${supported_configs}
    BASEPATH ${plasma_build_out}
    PLATFORM ${platform}
    CONFIG ${configuration}
    BITS ${bit}
    TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
    PRECOMPILED_HEADER_NAME "Precompiled.hpp"
    PRECOMPILED_SOURCE_NAME "Precompiled.cpp"
    TARGET_SUBFOLDER PlasmaLauncher
)

add_dependencies(PlasmaLauncherSharedLibrary
    BrowserSubProcess
)

plasma_subfolder_source_group(${plasma_core_path} Projects/PlasmaLauncher PlasmaLauncherSharedLibrary "${plasma_core_path}/Projects")

launcher_shared_post_build(
    PlasmaLauncherSharedLibrary 
    ${plasma_core_path}
    ${CurrentDirectory}
    ${plasma_binary_dir}
)