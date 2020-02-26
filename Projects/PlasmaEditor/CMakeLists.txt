################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_executable(PlasmaEditor "")

set_target_properties(PlasmaEditor PROPERTIES FOLDER "Projects")

target_sources(PlasmaEditor
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Startup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PlasmaCrashCallbacks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PlasmaCrashCallbacks.hpp
)

set(platformSpecificSource)

# get the rc file so we get icons on windows builds
if (${platform} STREQUAL "Windows")
    set(platformSpecificSource
        ${plasma_platform_data}/PlasmaEditor/PlasmaEditor.rc
        ${plasma_platform_data}/PlasmaEditor/Resource.h
    )
endif()

target_sources(PlasmaEditor
    PRIVATE
    ${platformSpecificSource}
)


target_include_directories(PlasmaEditor
PUBLIC
    ${Source_Root}
    ${CMAKE_CURRENT_LIST_DIR} 
    ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(PlasmaEditor
                      PUBLIC
                      Common
                      Gameplay
                      SpatialPartition
                      CodeTranslator
                      LightningShaders
                      Serialization
                      Support
                      Engine 
                      Geometry 
                      Widget 
                      Editor 
                      LightningScript 
                      Networking 
                      Meta 
                      Physics 
                      Sound 
                      Platform 
                      Content 
                      Dash 
                      UiWidget
                      Startup
                      Lightning
                      Graphics
                      ${OpusStatic}
                      ${FreetypeStatic}
                      ${ZLibStatic}
)

if(NOT use_spirv_shared_library)
  target_link_libraries(PlasmaEditor
                      PUBLIC
                      SPIRV-Tools
                      SPIRV-Tools-opt
                      )
endif()

plasma_multitarget_output_settings(
    PlasmaEditor
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

add_dependencies(PlasmaEditor
    BrowserSubProcess
)

plasma_subfolder_source_group_ignore_target_folder(${plasma_core_path} Projects PlasmaEditor "${plasma_core_path}/Projects")


################################################################################
# Post build steps
################################################################################
copy_multiple_shared_objects(
    PlasmaEditor
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
      PlasmaEditor
      OUTPUT_DIRECTORY ${plasma_binary_dir}
      SHARED_OBJECT_LOCATIONS
      ${SpirVToolsSharedPath}
  )
endif()

if("${platform}" STREQUAL "Emscripten")
    message("should be calling zip directory for PlasmaEditor")
    multitarget_zip_directory(
        PlasmaEditor 
        FOLDERS_TO_ZIP
        "Resources/Loading"
        "Resources/FragmentCore"
        "Resources/PlasmaCore"
        "Resources/Editor"
        "Resources/EditorUi"
        "Resources/UiWidget"
        "PrebuiltPlasmaContent"
        "Tools/SpriteVersion.txt"
        "Data/ColorSchemes"
        "Data/Fallback"
        "Data/Licenses"
        "Data/LightningFragmentSettings"
        "Data/*.*"
        OUTPUT_FILE
        "BuildOutput/PlasmaEditorFileSystem.zip"
    )
endif()

#function(create_build_info aTarget aSourceDir aBuildOutDir aOutputLocation)
create_build_info(
    PlasmaEditor
    ${CMAKE_CURRENT_LIST_DIR}
    ${plasma_core_path}
    ${plasma_binary_dir}
    ${plasma_binary_dir}
)

#function(CreatePluginDirectory aTarget aPlasmaCoreDir aBuildOutputDirectory aOS aplatformShortName)
editor_post_build_step(
    PlasmaEditor
    ${plasma_core_path}
    ${plasma_library_dir}
    ${plasma_binary_dir}
    ${platform}
    ${bit}
)

if (${CEF_exists})
    plasma_multitarget_copy_folders_to_target_output_directories(
        PlasmaEditor
        OUTPUT_DIRECTORY ${plasma_binary_dir}
        FOLDERS_TO_COPY 
        ${aPlasmaCoreDirectory}/External/CEF/bin
    )
endif()