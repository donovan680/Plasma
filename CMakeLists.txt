################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################
################################################################################
# Set required version of cmake and any version specific policies
################################################################################
cmake_minimum_required(VERSION 3.9.1 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo)

################################################################################
# Declare project(s) and set used languages
################################################################################
project(Plasma CXX)

################################################################################
# Set up options for project depending on verius PlasmaCore features
################################################################################

# Helper for Option sets, this will turn any builds not turned on by the option
# sets off.
function(plasma_turn_remaining_builds_off)
    # ZeroLibraries
    option(PLASMA_BUILD_Common "Build the Common project" OFF)
    option(PLASMA_BUILD_Dash "Build the Dash project" OFF)
    option(PLASMA_BUILD_Geometry "Build the Geometry project" OFF)
    option(PLASMA_BUILD_Meta "Build the Meta project" OFF)
    option(PLASMA_BUILD_Platform "Build the Platform project" OFF)
    option(PLASMA_BUILD_Serialization "Build the Serialization project" OFF)
    option(PLASMA_BUILD_SpatialPartition "Build the SpatialPartition project" OFF)
    option(PLASMA_BUILD_Support "Build the Support project" OFF)
    option(PLASMA_BUILD_Lightning "Build the Lightning project" OFF)

    # Projects
    option(PLASMA_BUILD_PlasmaEditor "Build the PlasmaEditor project" OFF)
    option(PLASMA_BUILD_PlasmaLauncher "Build the PlasmaLauncher project" OFF)
    option(PLASMA_BUILD_PlasmaLauncherSharedLibrary "Build the PlasmaLauncherSharedLibrary project" OFF)
    option(PLASMA_BUILD_BrowserSubProcess "Build the BrowserSubProcess project" OFF)

    # Systems
    option(PLASMA_BUILD_Content "Build the Content project" OFF)
    option(PLASMA_BUILD_Engine "Build the Engine project" OFF)
    option(PLASMA_BUILD_Graphics "Build the Graphics project" OFF)
    option(PLASMA_BUILD_Networking "Build the Networking project" OFF)
    option(PLASMA_BUILD_Physics "Build the Physics project" OFF)
    option(PLASMA_BUILD_Sound "Build the Sound project" OFF)
    option(PLASMA_BUILD_Startup "Build the Startup project" OFF)
    option(PLASMA_BUILD_LightningScript "Build the LightningScript project" OFF)

    # Extensions
    option(PLASMA_BUILD_CodeTranslator "Build the CodeTranslator project" OFF)
    option(PLASMA_BUILD_Editor "Build the Editor project" OFF)
    option(PLASMA_BUILD_Gameplay "Build the Gameplay project" OFF)
    option(PLASMA_BUILD_UiWidget "Build the UiWidget project" OFF)
    option(PLASMA_BUILD_Widget "Build the Widget project" OFF)
    option(PLASMA_BUILD_LightningShaders "Build the LightningShaders project" OFF)
endfunction()

###################################
# Option Sets, these default off.
###################################

# Set up options sets, these will then set base options, these will all default 
# to OFF.

# If you only want to link against Lightning and the LightningShader extension
# this option is for you.
option(PLASMA_OPTIONSET_LightningShader "The LightningShaders option set, will turn on everything required for LightningShaders" OFF)

if(${PLASMA_OPTIONSET_LightningShader})
	option(PLASMA_OPTIONSET_Lightning "Build the Lightning project" ON)
    option(PLASMA_BUILD_Geometry "Build the Geometry project" ON)
	option(PLASMA_BUILD_LightningShaders "Build the LightningShaders project" ON)
endif()

# If you only want to link against Lightning this option is for you.
option(PLASMA_OPTIONSET_Lightning "The Lightning option set, will turn on everything required for Lightning" OFF)

if(${PLASMA_OPTIONSET_Lightning})
    option(PLASMA_BUILD_Common "Build the Common project" ON)
    option(PLASMA_BUILD_Lightning "Build the Lightning project" ON)
endif()

# Options are weird, and the first option set in the cmake hierarchy goes first
# so if any of our optionsets are set, then we want to turn off any extra
# builds/dependencies.
if(${PLASMA_OPTIONSET_Lightning} OR
   ${PLASMA_OPTIONSET_LightningShader})
   plasma_turn_remaining_builds_off()
endif()

###################################
# Base options, these default on.
###################################
#####################
# PlasmaLibraries
#####################
option(PLASMA_BUILD_Common "Build the Common project" ON)
option(PLASMA_BUILD_Dash "Build the Dash project" ON)
option(PLASMA_BUILD_Geometry "Build the Geometry project" ON)
option(PLASMA_BUILD_Meta "Build the Meta project" ON)
option(PLASMA_BUILD_Platform "Build the Platform project" ON)
option(PLASMA_BUILD_Serialization "Build the Serialization project" ON)
option(PLASMA_BUILD_SpatialPartition "Build the SpatialPartition project" ON)
option(PLASMA_BUILD_Support "Build the Support project" ON)
option(PLASMA_BUILD_Lightning "Build the Lightning project" ON)

#####################
# External
#####################


#####################
# Systems
#####################
option(PLASMA_BUILD_Content "Build the Content project" ON)
option(PLASMA_BUILD_Engine "Build the Engine project" ON)
option(PLASMA_BUILD_Graphics "Build the Graphics project" ON)
option(PLASMA_BUILD_Networking "Build the Networking project" ON)
option(PLASMA_BUILD_Physics "Build the Physics project" ON)
option(PLASMA_BUILD_Sound "Build the Sound project" ON)
option(PLASMA_BUILD_Startup "Build the Startup project" ON)
option(PLASMA_BUILD_LightningScript "Build the LightningScript project" ON)


#####################
# Extensions
#####################
option(PLASMA_BUILD_CodeTranslator "Build the CodeTranslator project" ON)
option(PLASMA_BUILD_Editor "Build the Editor project" ON)
option(PLASMA_BUILD_Gameplay "Build the Gameplay project" ON)
option(PLASMA_BUILD_UiWidget "Build the UiWidget project" ON)
option(PLASMA_BUILD_Widget "Build the Widget project" ON)
option(PLASMA_BUILD_LightningShaders "Build the LightningShaders project" ON)

#####################
# Projects
#####################
option(PLASMA_BUILD_PlasmaEditor "Build the PlasmaEditor project" ON)
option(PLASMA_BUILD_PlasmaLauncher "Build the PlasmaLauncher project" ON)
option(PLASMA_BUILD_PlasmaLauncherSharedLibrary "Build the PlasmaLauncherSharedLibrary project" ON)
option(PLASMA_BUILD_BrowserSubProcess "Build the BrowserSubProcess project" ON)

################################################################################
# Set up global variables
################################################################################

#paths
set(cmake_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(cmake_utilities_dir ${cmake_include_dir}/Utilities)
set(cmake_os_dir ${cmake_include_dir}/OS)
set(cmake_flags_dir ${cmake_include_dir}/CommonFlags)
set(cmake_config_dir ${cmake_include_dir}/Configuration)
set(cmake_compiler_dir ${cmake_include_dir}/Compiler)


set(plasma_core_path ${CMAKE_CURRENT_SOURCE_DIR})
message("CorePath: ${plasma_core_path}\n")
set(plasma_build_out ${plasma_core_path}/BuildOutput)
set(supported_configs $<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>)
set(plasma_intermediates_dir ${plasma_build_out}/Int/${supported_configs})
set(plasma_unit_test_dir ${plasma_core_path}/UnitTests)


################################################################################
# Define any user options
################################################################################
option(generate_with_unit_tests "If set to 'ON', project will be generated with the unit tests included." OFF)
option(generate_spirv_projects "If set to 'ON', spirv tools projects will be created. Allows static linking or generation of dll for tools." OFF)
option(use_spirv_shared_library "If set to 'ON', project will link against a dll of spirv (allows release dll in debug mode)." ON)

if(NOT generate_spirv_projects AND NOT use_spirv_shared_library)
  message(FATAL_ERROR "spirv project cannot be statically linked without also generating the spirv projects.")
endif()

################################################################################
# Define any platform options
################################################################################
include(${cmake_include_dir}/Platform_Options.cmake)

set(plasma_platform_data ${plasma_core_path}/PlatformData/${platform})

set(plasma_library_dir ${plasma_build_out}/Out/${configuration}/${supported_configs})
set(plasma_binary_dir ${plasma_build_out}/Out/${configuration}/${supported_configs})

################################################################################
# Path for finding external CMake modules
################################################################################
set(CMAKE_MODULE_PATH "${Source_Root}/cmake/modules/")

################################################################################
# Includes
################################################################################
include(${cmake_utilities_dir}/plasma_source_group.cmake)
include(${cmake_utilities_dir}/Plasma_Mulitarget_Functions.cmake)
include(${cmake_utilities_dir}/Plasma_Custom_Commands.cmake)

################################################################################
# Separate Projects into folders for IDEs.
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


################################################################################
# Call CMakeLists.txt in source folders, adding them to the project non-globally
################################################################################
# external libraries
add_subdirectory(External)

# plasma source and related projects
add_subdirectory(PlasmaLibraries)
add_subdirectory(Systems)
add_subdirectory(Extensions)
add_subdirectory(Projects)

if (generate_with_unit_tests)
    if (NOT EXISTS ${plasma_unit_test_dir})
        message(WARNING "option 'generate_with_unit_tests' set but unit test directory: '${plasma_unit_test_dir}' doesn't exist.\n Skipping unit tests.\n")
    else()
        message("\nAdding unit tests to project...\n")
        add_subdirectory(UnitTests)
    endif()
endif()

if (PLASMA_BUILD_PlasmaEditor)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PlasmaEditor)
endif()

