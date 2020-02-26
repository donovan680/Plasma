################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################

# get our current directory
set(PlasmaLibrariesDirectory ${CMAKE_CURRENT_LIST_DIR})

if (NOT ${PLASMA_BUILD_Common} AND
    NOT ${PLASMA_BUILD_Dash} AND
    NOT ${PLASMA_BUILD_Geometry} AND
    NOT ${PLASMA_BUILD_Meta} AND
    NOT ${PLASMA_BUILD_Platform} AND
    NOT ${PLASMA_BUILD_Serialization} AND
    NOT ${PLASMA_BUILD_SpatialPartition} AND
    NOT ${PLASMA_BUILD_Support} AND
    NOT ${PLASMA_BUILD_Lightning})
    set(PLASMA_NO_CORE_LIBRARIES ON)
else()
    set(PLASMA_NO_CORE_LIBRARIES OFF)
endif()

################################################################################
# Common
################################################################################
if (${PLASMA_BUILD_Common})
    add_subdirectory(Common)

    set(Plasma_OptionalTarget_Common Common)
endif()

################################################################################
# Platform
################################################################################
# platform is going to define its own target
if (${PLASMA_BUILD_Platform})
    add_subdirectory(Platform)
endif()

################################################################################
# Dash
################################################################################
if (${PLASMA_BUILD_Dash})
    add_subdirectory(Dash)

    set(Plasma_OptionalTarget_Dash Dash)
endif()

################################################################################
# Geometry
################################################################################
if (${PLASMA_BUILD_Geometry})
    add_subdirectory(Geometry)

    set(Plasma_OptionalTarget_Geometry Geometry)
endif()

################################################################################
# Lightning
################################################################################
if (${PLASMA_BUILD_Lightning})
    add_subdirectory(Lightning)

    set(Plasma_OptionalTarget_Lightning Lightning)
endif()

################################################################################
# Meta
################################################################################

if (${PLASMA_BUILD_Meta})
    add_subdirectory(Meta)

    set(Plasma_OptionalTarget_Meta Meta)
endif()

################################################################################
# Serialization
################################################################################
if (${PLASMA_BUILD_Serialization})
    add_subdirectory(Serialization)

    set(Plasma_OptionalTarget_Serialization Serialization)
endif()

################################################################################
# SpatialPartition
################################################################################

if (${PLASMA_BUILD_Common})
    add_subdirectory(SpatialPartition)

    set(Plasma_OptionalTarget_SpatialPartition SpatialPartition)

endif()

################################################################################
# set flags and definitions
################################################################################

if (${PLASMA_BUILD_Support})
    add_subdirectory(Support)

    set(Plasma_OptionalTarget_Support Support)
endif()

if (NOT ${PLASMA_NO_CORE_LIBRARIES})
    ################################################################################
    # set the output directories for all of our targets
    ################################################################################
    plasma_multitarget_output_directories(
        ${plasma_OptionalTarget_Common}
        ${plasma_OptionalTarget_Dash}
        ${plasma_OptionalTarget_Geometry}
        ${plasma_OptionalTarget_Meta}
        ${plasma_OptionalTarget_Serialization}
        ${plasma_OptionalTarget_SpatialPartition}
        ${plasma_OptionalTarget_Support}
        ${plasma_OptionalTarget_Lightning}
        LIBRARY_DIRECTORY ${plasma_library_dir}
        RUNTIME_DIRECTORY ${plasma_binary_dir}
    )

    ################################################################################
    # set flags and definitions
    ################################################################################
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
        plasma_multitarget_compile_options(  
            ${Plasma_OptionalTarget_Common} 
            ${Plasma_OptionalTarget_Dash} 
            ${Plasma_OptionalTarget_Geometry}
            ${Plasma_OptionalTarget_Meta} 
            ${Plasma_OptionalTarget_Serialization}
            ${Plasma_OptionalTarget_SpatialPartition}
            ${Plasma_OptionalTarget_Support}
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
            ${Plasma_OptionalTarget_Common} 
            ${Plasma_OptionalTarget_Dash} 
            ${Plasma_OptionalTarget_Geometry}
            ${Plasma_OptionalTarget_Meta} 
            ${Plasma_OptionalTarget_Serialization}
            ${Plasma_OptionalTarget_SpatialPartition}
            ${Plasma_OptionalTarget_Support}
            ${Plasma_OptionalTarget_Lightning}
            PRIVATE
            PUBLIC
            PRIVATE
            ${common_flags}
        )
        set_target_properties(
            ${Plasma_OptionalTarget_Common}
            ${Plasma_OptionalTarget_Dash}
            ${Plasma_OptionalTarget_Geometry}
            ${Plasma_OptionalTarget_Meta}
            ${Plasma_OptionalTarget_Serialization}
            ${Plasma_OptionalTarget_SpatialPartition}
            ${Plasma_OptionalTarget_Support}
            ${Plasma_OptionalTarget_Lightning}
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
            ${Plasma_OptionalTarget_Common}
            ${Plasma_OptionalTarget_Dash}
            ${Plasma_OptionalTarget_Geometry}
            ${Plasma_OptionalTarget_Meta}
            ${Plasma_OptionalTarget_Serialization}
            ${Plasma_OptionalTarget_SpatialPartition}
            ${Plasma_OptionalTarget_Support}
            ${Plasma_OptionalTarget_Lightning}
            PROPERTIES 
            STATIC_LIBRARY_FLAGS "${common_library_flags}"
            STATIC_LIBRARY_FLAGS_RELEASE "/LTCG"
        )
    endif()
endif()