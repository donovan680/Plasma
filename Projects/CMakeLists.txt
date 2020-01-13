################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################
# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

################################################################################
# define all of the targets that are in this folder
################################################################################
add_executable(PlasmaEditor "")
add_executable(PlasmaLauncher "")
add_executable(BrowserSubProcess "")
add_library(PlasmaLauncherSharedLibrary SHARED "")

################################################################################
# Explicitly define the folders as they are not organized how we want
################################################################################
set_target_properties(PlasmaEditor       PROPERTIES FOLDER "Projects")
set_target_properties(PlasmaLauncher     PROPERTIES FOLDER "Projects")
set_target_properties(PlasmaLauncherSharedLibrary  PROPERTIES FOLDER "Projects")
set_target_properties(BrowserSubProcess  PROPERTIES FOLDER "Projects")

################################################################################
# include filelists for each library
################################################################################
include(PlasmaEditor/CMakeLists.txt)
include(PlasmaLauncher/PlasmaLauncher/CMakeLists.txt)
include(PlasmaLauncher/PlasmaLauncherSharedLibrary/CMakeLists.txt)
include(BrowserSubProcess/CMakeLists.txt)

################################################################################
# define include directories for all of our libraries
################################################################################
target_include_directories(PlasmaEditor 
    PUBLIC 
        ${Source_Root}
        ${CurrentDirectory}/PlasmaEditor 
        ${CurrentDirectory}
)
target_include_directories(PlasmaLauncher 
    PUBLIC 
        ${CurrentDirectory}
        ${CurrentDirectory}/PlasmaLauncher/PlasmaLauncher
        ${CurrentDirectory}/PlasmaLauncher/PlasmaLauncherSharedLibrary
)
target_include_directories(PlasmaLauncherSharedLibrary 
    PUBLIC 
        ${CurrentDirectory}
        ${CurrentDirectory}/PlasmaLauncher/PlasmaLauncherSharedLibrary
        ${Dependencies_Root}
        ${Source_Root}
)
target_include_directories(BrowserSubProcess
    PUBLIC 
        ${CurrentDirectory}/BrowserSubProcess    
        ${CurrentDirectory}
)

################################################################################
# set the linked libraries for all of our targets
################################################################################
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

if(NOT use_spirv_shared_library)
target_link_libraries(PlasmaEditor
                      PUBLIC
                      SPIRV-Tools
                      SPIRV-Tools-opt
                      )
endif()

# the launcher is going to need the chrome subprocess to run correctly
add_dependencies(PlasmaLauncherSharedLibrary
    BrowserSubProcess
)
add_dependencies(PlasmaEditor
    BrowserSubProcess
)
# launcher needs the dll to run
add_dependencies(PlasmaLauncher
    PlasmaLauncherSharedLibrary
)
target_link_libraries(BrowserSubProcess
                      PUBLIC
                      Common
                      Platform
                      ${FreetypeStatic}
                      ${ZLibStatic}
                      ${LibpngStatic}
                      ${CEFStatic}
) 
################################################################################
# set the output directories for all of our targets
################################################################################
plasma_multitarget_output_directories(
                      PlasmaEditor
                      PlasmaLauncher 
                      PlasmaLauncherSharedLibrary
                      BrowserSubProcess
                      LIBRARY_DIRECTORY ${plasma_library_dir}
                      RUNTIME_DIRECTORY ${plasma_binary_dir}
)
# go through and seperate outputs to different folders

#ARCHIVE_OUTPUT_DIRECTORY
#LIBRARY_OUTPUT_DIRECTORY
#RUNTIME_OUTPUT_DIRECTORY

################################################################################
# Specify any additional target options such as pdb locations
################################################################################
if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
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

    plasma_multitarget_output_settings(
        PlasmaLauncher 
        PlasmaLauncherSharedLibrary
        CONFIGS ${supported_configs}
        BASEPATH "${plasma_build_out}"
        PLATFORM ${platform}
        CONFIG ${configuration}
        BITS ${bit}
        TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
        PRECOMPILED_HEADER_NAME "Precompiled.hpp"
        PRECOMPILED_SOURCE_NAME "Precompiled.cpp"
        TARGET_SUBFOLDER PlasmaLauncher
    )

    plasma_multitarget_output_settings(
        BrowserSubProcess
        CONFIGS ${supported_configs}
        BASEPATH ${Plasma_build_out}
        PLATFORM ${platform}
        CONFIG ${configuration}
        BITS ${bit}
        TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
        PRECOMPILED_HEADER_NAME ""
        PRECOMPILED_SOURCE_NAME ""
        TARGET_SUBFOLDER
    )
    
endif()

################################################################################
# set flags and definitions
################################################################################

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))

    plasma_multitarget_compile_options(
        PlasmaEditor
        PlasmaLauncher
        PRIVATE
         
        PUBLIC
        "-D \"_UNICODE\"" 
        "-D \"UNICODE\""
        "-D \"CURL_STATICLIB\" "
        "-D \"WIN32\" "
        "-D \"_CRT_SECURE_NO_WARNINGS\" "
        "-D \"PlasmaExportDll\" "
        PRIVATE
        ${common_flags}

    )

    target_compile_options(
        PlasmaLauncherSharedLibrary
        PRIVATE
         
        PUBLIC
        PRIVATE
        ${common_flags}
        "-D \"_UNICODE\"" 
        "-D \"UNICODE\""
        "-D \"CURL_STATICLIB\"" 
        "-D \"WIN32\"" 
        "-D \"_WINDOWS\"" 
        "-D \"_USRDLL\"" 
        "-D \"PlasmaLauncherSharedLibrary_EXPORTS\"" 
        "-D \"_WINDLL\"" 
        "-D \"_CRT_SECURE_NO_WARNINGS\"" 
        "-D \"PlasmaExportDll\"" 
    )

    # have to set flags for BrowserSubProcess seperatly because it has very different settings
    plasma_multitarget_compile_options(
        BrowserSubProcess
        PRIVATE
        PUBLIC
        PRIVATE
        $<$<CONFIG:Debug>:-GS>
        $<$<CONFIG:Release>:-MP>
        $<$<CONFIG:Release>:-GS->
        $<$<CONFIG:Release>:-GL>

        -analyze-
        -W3 
        -wd"4302"
        -wd"4305"
        -Zc:wchar_t

        $<$<CONFIG:Debug>:-Zi>
        $<$<CONFIG:Release>:-Zi>
        $<$<CONFIG:Debug>:-Gm>
        $<$<CONFIG:Release>:-Gm->
        $<$<CONFIG:Debug>:-Od>
        $<$<CONFIG:Release>:-O2>

        -Zc:inline 
        -fp:precise 
        -errorReport:prompt 
        -Zc:forScope 
        -GR- 
        -Gd
        $<$<CONFIG:Release>:-arch:SSE2>
        -Oy-
        $<$<CONFIG:Debug>:-MDd>
        $<$<CONFIG:Release>:-Oi>
        $<$<CONFIG:Release>:-MT>
        -EHsc 
        $<$<CONFIG:Release>:-Gy>

        -nologo

        $<$<CONFIG:Release>:-"D \"NDEBUG\"">
        $<$<CONFIG:Release>:-"D \"VLD\"">
    )
    
################################################################################
# Set linker flags
################################################################################

    # set the correct subsystems for executable targets, and set stack size for the editor
    set_target_properties(
        PlasmaEditor 
        PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /STACK:8388608 /DEBUG ${common_linker_flags}"
    )

    set_target_properties(
        PlasmaLauncher 
        PlasmaEditor 
        PlasmaLauncherSharedLibrary 
        PROPERTIES 
        LINK_FLAGS_RELEASE "/LTCG"
    )
    
    set_target_properties(
        PlasmaLauncher 
        PlasmaLauncherSharedLibrary 
        BrowserSubProcess
        PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /DEBUG ${common_linker_flags}"
    )

else()
    plasma_multitarget_compile_options(
        PlasmaEditor
        PlasmaLauncher
        BrowserSubProcess
        PRIVATE
        PUBLIC
        PRIVATE
        ${common_flags}
    )
    set_target_properties(
        PlasmaEditor
        PlasmaLauncher
        BrowserSubProcess
        PROPERTIES
        LINK_FLAGS "${common_linker_flags}"
    )
endif()

if (${platform} STREQUAL "Emscripten")
    set_target_properties(
        PlasmaEditor
        PROPERTIES SUFFIX ".html"
        LINK_FLAGS "--embed-file \"${plasma_build_out}/PlasmaEditorFileSystem.zip\"@/FileSystem.zip"
    )
    set_target_properties(
        PlasmaLauncher
        PROPERTIES SUFFIX ".html"
        LINK_FLAGS "--embed-file \"${plasma_build_out}/PlasmaLauncherFileSystem.zip\"@/FileSystem.zip"
    )
endif()

################################################################################
# Group source into folders
################################################################################
plasma_subfolder_source_group_ignore_target_folder(${plasma_core_path} Projects PlasmaEditor "${plasma_core_path}/Projects")
plasma_subfolder_source_group_ignore_target_folder(${plasma_core_path} Projects PlasmaLauncher "${plasma_core_path}/Projects")
plasma_subfolder_source_group(${plasma_core_path} Projects/PlasmaLauncher PlasmaLauncherSharedLibrary "${plasma_core_path}/Projects")

plasma_subfolder_source_group(${plasma_core_path} Projects BrowserSubProcess "")



################################################################################
# Post build steps
################################################################################
#### PlasmaEditor editor
copy_multiple_shared_objects(
    PlasmaEditor
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
      PlasmaEditor
      PlasmaLauncher
      OUTPUT_DIRECTORY ${plasma_binary_dir}
      SHARED_OBJECT_LOCATIONS
      ${SpirVToolsSharedPath}
  )
endif()

if("${platform}" STREQUAL "Emscripten")
    message("should be calling zip directory")
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


#function(create_build_info aTarget aSourceDir aBuildOutDir aOutputLocation)
create_build_info(
    PlasmaEditor
    ${CurrentDirectory}/PlasmaEditor
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

####

#### PlasmaLauncherSharedLibrary
# launcher_post_build(aTarget aPlasmaCoreDirectory aProjectDirectory aBuildOutputDirectory)
launcher_shared_post_build(
    PlasmaLauncherSharedLibrary 
    ${plasma_core_path}
    ${CurrentDirectory}/PlasmaLauncher/PlasmaLauncherSharedLibrary
    ${plasma_binary_dir}
)

#### BrowserSubProcess
add_custom_command(
    TARGET BrowserSubProcess POST_BUILD
    # executes "cmake -E copy_directory
    COMMAND ${CMAKE_COMMAND} -E copy_directory  
    # input folder
    ${plasma_binary_dir}/BrowserSubProcess                                  
    #output folder
    ${plasma_binary_dir}/PlasmaEditor
)

####

#### PlasmaLauncher
launcher_post_build(
    PlasmaLauncher 
    ${plasma_core_path}
    ${CurrentDirectory}/PlasmaLauncher/PlasmaLauncher
    ${plasma_binary_dir}
)


#### Copy the CEF files for every project that needs them
# first check if we need CEF for this platform, then copy cef files over
if (${CEF_exists})
    plasma_multitarget_copy_folders_to_target_output_directories(
        PlasmaEditor
        PlasmaLauncher
        BrowserSubProcess
        OUTPUT_DIRECTORY ${plasma_binary_dir}
        FOLDERS_TO_COPY 
        ${aPlasmaCoreDirectory}/External/CEF/bin
    )
endif()
####
