################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################
# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

################################################################################
# define all of the libraries that are in this folder
################################################################################
add_library(Common "") 
add_library(Dash "")
add_library(Geometry "")
add_library(Meta "")
add_library(Serialization "")
add_library(SpatialPartition  "")
add_library(Support "")
add_library(Lightning "")

################################################################################
# Explicitly define the folders as they are not organized how we want
################################################################################
set_target_properties(Common           PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(Dash             PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(Geometry         PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(Meta             PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(Serialization    PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(SpatialPartition PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(Support          PROPERTIES FOLDER "PlasmaLibraries")
set_target_properties(Lightning            PROPERTIES FOLDER "PlasmaLibraries")

################################################################################
# include filelists for each library
################################################################################
include(Common/CMakeLists.txt)
include(Dash/CMakeLists.txt)
include(Geometry/CMakeLists.txt)
include(Meta/CMakeLists.txt)

include(Serialization/CMakeLists.txt)
include(SpatialPartition/CMakeLists.txt)
include(Support/CMakeLists.txt)
include(Lightning/CMakeLists.txt)

# platform is going to define its own target
add_subdirectory(Platform)
################################################################################
# define include directories for all of our libraries
################################################################################
target_include_directories(Common
    PUBLIC 
        ${CurrentDirectory}/Common
        ${CurrentDirectory}
)
target_include_directories(Dash
    PUBLIC
        ${CurrentDirectory}/Dash 
        ${CurrentDirectory}
)
target_include_directories(Geometry
    PUBLIC
        ${CurrentDirectory}/Geometry 
        ${CurrentDirectory}
)
target_include_directories(Meta
    PUBLIC
        ${CurrentDirectory}/Meta 
        ${CurrentDirectory}
)
target_include_directories(Serialization
    PUBLIC
        ${CurrentDirectory}/Serialization 
        ${CurrentDirectory}
)
target_include_directories(SpatialPartition
    PUBLIC
        ${CurrentDirectory}/SpatialPartition 
        ${CurrentDirectory}
)
target_include_directories(Support
    PUBLIC
        ${CurrentDirectory}/Support
        ${CurrentDirectory}
)
target_include_directories(Lightning
    PUBLIC
        ${CurrentDirectory}/Lightning/Project
        ${CurrentDirectory}/Lightning/Project/Lightning
        ${VLD_INCLUDE_DIRS}
        ${CurrentDirectory}
)

################################################################################
# set the linked libraries for all of our targets
################################################################################
target_link_libraries(Dash
                      PUBLIC
                      Common
                      Lightning                      
                      Geometry
) 
target_link_libraries(Geometry
                      PUBLIC
                      Common
                      Lightning
) 
target_link_libraries(Lightning
                      PUBLIC
                      Common
                      ${VLD_LIBRARIES}
)
target_link_libraries(Meta
                      PUBLIC
                      Lightning
)
target_link_libraries(Serialization
                      PUBLIC
                      Common
                      Geometry
)
target_link_libraries(SpatialPartition
                      PUBLIC
                      Lightning
)
target_link_libraries(Support
                      PUBLIC
                      Common
                      ${ZLibStatic}
                      ${LibpngStatic}
)

################################################################################
# set the output directories for all of our targets
################################################################################
plasma_multitarget_output_directories(
    Common
    Dash
    Geometry
    Meta
    Serialization
    SpatialPartition
    Support
    Lightning
    LIBRARY_DIRECTORY ${plasma_library_dir}
    RUNTIME_DIRECTORY ${plasma_binary_dir}
)

################################################################################
# Specify any additional target options such as pdb locations
################################################################################

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
    plasma_multitarget_output_settings(
        Common 
        Dash 
        Geometry
        Meta 
        Serialization
        SpatialPartition
        Support
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
        Lightning 
        CONFIGS ${supported_configs}
        BASEPATH ${plasma_build_out}
        PLATFORM ${platform}
        CONFIG ${configuration}
        BITS ${bit}
        TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
        PRECOMPILED_HEADER_NAME "Lightning.hpp"
        PRECOMPILED_SOURCE_NAME "Lightning.cpp"
        TARGET_SUBFOLDER "Lightning/Project"
    )
endif()

################################################################################
# set flags and definitions
################################################################################
if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
    plasma_multitarget_compile_options(  
        Common 
        Dash 
        Geometry
        Meta 
        Serialization
        SpatialPartition
        Support
        
        PRIVATE
         
        PUBLIC
            -GS -analyze-  -Zc:wchar_t
            
        PRIVATE
            -W3 -wd"4302"
            ${common_flags}
    )
    if (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014")
        plasma_multitarget_compile_options(  
            Lightning 
            PRIVATE

            PUBLIC
                -GS -analyze-  -Zc:wchar_t

            PRIVATE
            $<$<CONFIG:Debug>:-GS>
            $<$<CONFIG:Release>:-GS->
            $<$<CONFIG:Release>:-GL>
            -analyze-
            -W3 
            -wd"4302"
            -Zc:wchar_t
            $<$<CONFIG:Debug>:-Od>
            $<$<CONFIG:Release>:-O2>
            -Zc:inline 
            -fp:fast 
            -errorReport:prompt 
            -WX 
            -Zc:forScope 
            -GR- 
            -Gd
            $<$<CONFIG:Release>:-arch:SSE2>
            -Oy-
            $<$<CONFIG:Debug>:-MDd>
            $<$<CONFIG:Release>:-Oi>
            $<$<CONFIG:Release>:-MT>
            -EHsc 
            -nologo
            -DDEBUG  
            "-D \"_CRT_SECURE_NO_WARNINGS\"" 
            "-Wno-unused-command-line-argument"
            "-Wno-undefined-inline"
            -FILightning.hpp
        )
    else()
        plasma_multitarget_compile_options(  
            Lightning 
            PRIVATE
             
            PUBLIC
                -GS -analyze-  -Zc:wchar_t
                
            PRIVATE
                -W3 -wd"4302"
                ${common_flags}
        )
    endif()
else()
    plasma_multitarget_compile_options(
        Common 
        Dash 
        Geometry
        Meta 
        Serialization
        SpatialPartition
        Support
        Lightning
        PRIVATE
        PUBLIC
        PRIVATE
        ${common_flags}
    )
    set_target_properties(
        Common 
        Dash 
        Geometry
        Meta 
        Serialization
        SpatialPartition
        Support
        Lightning
        PROPERTIES
        LINK_FLAGS "${common_linker_flags}"
    )
endif()

################################################################################
# Set linker flags
################################################################################
if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
    # set the correct subsystems for executable targets, and set stack size for the editor
    set_target_properties(
        Common
        Dash
        Geometry
        Meta
        Serialization
        SpatialPartition
        Support
        Lightning 
        PROPERTIES 
        STATIC_LIBRARY_FLAGS "${common_library_flags}"
        STATIC_LIBRARY_FLAGS_RELEASE "/LTCG"
    )
endif()
################################################################################
# Group source into folders
################################################################################
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Common "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Dash "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Geometry "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Meta "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Serialization "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries SpatialPartition "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Support "")
plasma_subfolder_source_group(${plasma_core_path} PlasmaLibraries Lightning "")