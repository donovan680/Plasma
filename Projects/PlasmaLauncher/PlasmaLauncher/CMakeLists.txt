################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_executable(PlasmaLauncher "")

set_target_properties(PlasmaLauncher PROPERTIES FOLDER "Projects")

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

plasma_multitarget_output_settings(
    PlasmaLauncher
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

add_dependencies(PlasmaLauncher
    PlasmaLauncherSharedLibrary
)

plasma_subfolder_source_group_ignore_target_folder(${plasma_core_path} Projects PlasmaLauncher "${plasma_core_path}/Projects")

################################################################################
# Post build steps
################################################################################
copy_multiple_shared_objects(
    PlasmaLauncher
    OUTPUT_DIRECTORY ${plasma_binary_dir}
    SHARED_OBJECT_LOCATIONS
    ## setup all dll locations
    ${AssimpSharedPath}
    ${CEFSharedPath}
    ${FreetypeSharedPath}
    ${GLEWSharedPath}
    ${MemoryDebuggerSharedPath}
    ${MemoryTrackerSharedPath}
    ${NvttSharedPath}
    ${PortAudioSharedPath}
    ${SDLSharedPath}
)

if(use_spirv_shared_library)
  copy_multiple_shared_objects(
      PlasmaLauncher
      OUTPUT_DIRECTORY ${plasma_binary_dir}
      SHARED_OBJECT_LOCATIONS
      ${SpirVToolsSharedPath}
  )
endif()

if("${platform}" STREQUAL "Emscripten")
    message("should be calling zip directory for PlasmaLauncher")
    multitarget_zip_directory(
        PlasmaLauncher 
        FOLDERS_TO_ZIP
        "Resources/Loading"
        "Resources/FragmentCore"
        "Resources/PlasmaCore"
        "Resources/PlasmaLauncherResources"
        "PrebuiltPlasmaContent"
        "Tools/SpriteVersion.txt"
        "Data/ColorSchemes"
        "Data/Fallback"
        "Data/Licenses"
        "Data/LightningFragmentSettings"
        "Data/*.*"
        OUTPUT_FILE
        "BuildOutput/PlasmaLauncherFileSystem.zip"
    )
endif()

launcher_post_build(
    PlasmaLauncher 
    ${plasma_core_path}
    ${CurrentDirectory}
    ${plasma_binary_dir}
)

if (${CEF_exists})
    plasma_multitarget_copy_folders_to_target_output_directories(
        PlasmaLauncher
        OUTPUT_DIRECTORY ${plasma_binary_dir}
        FOLDERS_TO_COPY 
        ${aPlasmaCoreDirectory}/External/CEF/bin
    )
endif()