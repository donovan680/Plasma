################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################

if(NOT ${PLASMA_BUILD_Content} AND
   NOT ${PLASMA_BUILD_Engine} AND
   NOT ${PLASMA_BUILD_Graphics} AND
   NOT ${PLASMA_BUILD_Networking} AND
   NOT ${PLASMA_BUILD_Physics} AND
   NOT ${PLASMA_BUILD_Sound} AND
   NOT ${PLASMA_BUILD_Startup} AND
   NOT ${PLASMA_BUILD_LightningScript})
   set(PLASMA_NO_SYSTEMS ON)
else()
    set(PLASMA_NO_SYSTEMS OFF)
endif()

################################################################################
# Content
################################################################################
if(${PLASMA_BUILD_Content})
  add_subdirectory(Content)

  set(Plasma_OptionalTarget_Content Content)
endif()

################################################################################
# Engine
################################################################################
if(${PLASMA_BUILD_Content})
  add_subdirectory(Engine)

  set(Plasma_OptionalTarget_Engine Engine)
endif()

################################################################################
# Graphics
################################################################################

if(${PLASMA_BUILD_Graphics})
  add_subdirectory(Graphics)

  set(Lightning_OptionalTarget_Graphics Graphics)
endif()

################################################################################
# Networking
################################################################################

if(${PLASMA_BUILD_Networking})
  add_subdirectory(Networking)

  set(Plasma_OptionalTarget_Networking Networking)
endif()

################################################################################
# Physics
################################################################################
if(${PLASMA_BUILD_Physics})
  add_subdirectory(Physics)

  set(Plasma_OptionalTarget_Physics Physics)
endif()

################################################################################
# Sound
################################################################################

if(${PLASMA_BUILD_Sound})
  add_subdirectory(Sound)

  set(Plasma_OptionalTarget_Sound Sound)
endif()

################################################################################
# Startup
################################################################################
if(${PLASMA_BUILD_Startup})
  add_subdirectory(Startup)

  set(Plasma_OptionalTarget_Startup Startup)
endif()

################################################################################
# LightningScript
################################################################################
if(${PLASMA_BUILD_LightningScript})
  add_subdirectory(LightningScript)

  set(Plasma_OptionalTarget_LightningScript LightningScript)
endif()

if(NOT ${PLASMA_NO_SYSTEMS})
    ################################################################################
    # set the output directories for all of our targets
    ################################################################################
    plasma_multitarget_output_directories(
        ${Plasma_OptionalTarget_Content}
        ${Plasma_OptionalTarget_Engine}
        ${Plasma_OptionalTarget_Graphics}
        ${Plasma_OptionalTarget_Networking}
        ${Plasma_OptionalTarget_Physics}
        ${Plasma_OptionalTarget_Sound}
        ${Plasma_OptionalTarget_Startup}
        ${Plasma_OptionalTarget_LightningScript}
        LIBRARY_DIRECTORY ${plasma_library_dir}
        RUNTIME_DIRECTORY ${plasma_binary_dir}
    )

    ################################################################################
    # set flags and definitions
    ################################################################################
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))

        plasma_multitarget_compile_options( 
            ${Plasma_OptionalTarget_Content}
            ${Plasma_OptionalTarget_Engine}
            ${Plasma_OptionalTarget_Graphics}
            ${Plasma_OptionalTarget_Networking}
            ${Plasma_OptionalTarget_Physics}
            ${Plasma_OptionalTarget_Sound}
            ${Plasma_OptionalTarget_Startup}
            ${Plasma_OptionalTarget_LightningScript}

            PUBLIC
            -wd"4305"

            PRIVATE
            ${common_flags}
            "-D \"CURL_STATICLIB\"" 
            "-D \"WIN32\"" 
            "-D \"_CRT_SECURE_NO_WARNINGS\"" 
            "-D \"PlasmaExportDll\"" 
            
        )

        plasma_multitarget_compile_options( 
            PUBLIC
            PRIVATE
            "-D \"_UNICODE\"" 
            "-D \"UNICODE\""
        )
        #common_library_flags
        set_target_properties(
            ${Plasma_OptionalTarget_Content}
            ${Plasma_OptionalTarget_Engine}
            ${Plasma_OptionalTarget_Graphics}
            ${Plasma_OptionalTarget_Networking}
            ${Plasma_OptionalTarget_Physics}
            ${Plasma_OptionalTarget_Sound}
            ${Plasma_OptionalTarget_Startup}
            PROPERTIES
            STATIC_LIBRARY_FLAGS ${common_library_flags}
            STATIC_LIBRARY_FLAGS_RELEASE "/LTCG"
        )
    else()
        plasma_multitarget_compile_options(
            ${Plasma_OptionalTarget_Content}
            ${Plasma_OptionalTarget_Engine}
            ${Plasma_OptionalTarget_Graphics}
            ${Plasma_OptionalTarget_Networking}
            ${Plasma_OptionalTarget_Physics}
            ${Plasma_OptionalTarget_Sound}
            ${Plasma_OptionalTarget_Startup}
            ${Plasma_OptionalTarget_LightningScript}
            PRIVATE
            PUBLIC
            PRIVATE
            ${common_flags}
        )
        set_target_properties(
            ${Plasma_OptionalTarget_Content}
            ${Plasma_OptionalTarget_Engine}
            ${Plasma_OptionalTarget_Graphics}
            ${Plasma_OptionalTarget_Networking}
            ${Plasma_OptionalTarget_Physics}
            ${Plasma_OptionalTarget_Sound}
            ${Plasma_OptionalTarget_Startup}
            ${Plasma_OptionalTarget_LightningScript}
            PROPERTIES
            LINK_FLAGS "${common_linker_flags}"
        )
    endif()
  endif()