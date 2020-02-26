################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################
if(use_spirv_shared_library)
  set(SpirVToolsCompileOptions -DSPIRV_TOOLS_SHAREDLIB)
endif()

add_subdirectory(SpirV)

if (NOT ${PLASMA_BUILD_CodeTranslator} AND
    NOT ${PLASMA_BUILD_Editor} AND
    NOT ${PLASMA_BUILD_Gameplay} AND
    NOT ${PLASMA_BUILD_UiWidget} AND
    NOT ${PLASMA_BUILD_Widget} AND
    NOT ${PLASMA_BUILD_LightningShaders})
    set(PLASMA_NO_EXTENSIONS ON)
else()
    set(PLASMA_NO_EXTENSIONS OFF)
endif()

################################################################################
# CodeTranslator
################################################################################

if(${PLASMA_BUILD_CodeTranslator})

    add_subdirectory(CodeTranslator)

    set(Plasma_OptionalTarget_CodeTranslator CodeTranslator)
endif()

################################################################################
# Editor
################################################################################
if(${PLASMA_BUILD_Editor})
    
    add_subdirectory(Editor)

    set(Plasma_OptionalTarget_Editor Editor)
endif()

################################################################################
# Gameplay
################################################################################
if(${PLASMA_BUILD_Gameplay})
    
    add_subdirectory(Gameplay)

    set(Plasma_OptionalTarget_Gameplay Gameplay)
endif()


################################################################################
# UiWidget
################################################################################
if(${PLASMA_BUILD_UiWidget})
    
    add_subdirectory(UiWidget)

    set(Plasma_OptionalTarget_UiWidget UiWidget)
endif()

################################################################################
# Widget
################################################################################
if(${PLASMA_BUILD_Widget})
    
    add_subdirectory(Widget)

    set(Plasma_OptionalTarget_Widget Widget)
endif()

################################################################################
# LightningShaders
################################################################################
if(${PLASMA_BUILD_LightningShaders})
    
    add_subdirectory(LightningShaders)

    set(Plasma_OptionalTarget_LightningShaders LightningShaders)
endif()

# We might have no extensions on, so don't try setting any of this.
if (NOT ${ZERO_NO_EXTENSIONS})
    
    ################################################################################
    # set the output directories for all of our targets
    ################################################################################
    plasma_multitarget_output_directories(${Plasma_OptionalTarget_CodeTranslator}
                        ${Plasma_OptionalTarget_Editor}
                        ${Plasma_OptionalTarget_Gameplay} 
                        ${Plasma_OptionalTarget_UiWidget} 
                        ${Plasma_OptionalTarget_Widget}
                        ${Plasma_OptionalTarget_LightningShaders}
                        LIBRARY_DIRECTORY ${plasma_library_dir}
                        RUNTIME_DIRECTORY ${plasma_binary_dir}
    )

    ################################################################################
    # set flags and definitions
    ################################################################################
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
        plasma_multitarget_compile_options(  
            ${Plasma_OptionalTarget_CodeTranslator}
            ${Plasma_OptionalTarget_Editor}
            ${Plasma_OptionalTarget_Gameplay}
            ${Plasma_OptionalTarget_UiWidget}
            ${Plasma_OptionalTarget_Widget}
            ${Plasma_OptionalTarget_LightningShaders}
            PRIVATE 
            PUBLIC
                -GS -analyze-  -Zc:wchar_t
            PRIVATE
                -W3
                -wd"4302" 
                -wd"4305"
                -Gd
                -EHsc
                -GR-
                -fp:fast 
                -Zc:forScope 
                -Oy-
                -Od
                -Zc:inline
                -MDd
                -nologo
                -WX
                ${SpirVToolsCompileOptions}
                ${common_flags}
        )
    else()

        plasma_multitarget_compile_options(
            ${Plasma_OptionalTarget_CodeTranslator}
            ${Plasma_OptionalTarget_Editor}
            ${Plasma_OptionalTarget_Gameplay}
            ${Plasma_OptionalTarget_UiWidget}
            ${Plasma_OptionalTarget_Widget}
            ${Plasma_OptionalTarget_LightningShaders}
            PRIVATE
            PUBLIC
            PRIVATE
            ${common_flags}
        )

        set_target_properties(
            ${Plasma_OptionalTarget_CodeTranslator}
            ${Plasma_OptionalTarget_Editor}
            ${Plasma_OptionalTarget_Gameplay}
            ${Plasma_OptionalTarget_UiWidget}
            ${Plasma_OptionalTarget_Widget}
            ${Plasma_OptionalTarget_LightningShaders}
            PROPERTIES
            LINK_FLAGS ${common_linker_flags}
        )
    endif()

    ################################################################################
    # Set linker flags
    ################################################################################
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
      
        # set the correct subsystems for executable targets, and set stack size for the editor
        set_target_properties(
            ${Plasma_OptionalTarget_CodeTranslator}
            ${Plasma_OptionalTarget_Editor}
            ${Plasma_OptionalTarget_Gameplay}
            ${Plasma_OptionalTarget_UiWidget}
            ${Plasma_OptionalTarget_Widget}
            ${Plasma_OptionalTarget_LightningShaders}
            PROPERTIES 
            STATIC_LIBRARY_FLAGS "${common_library_flags}"
            STATIC_LIBRARY_FLAGS_RELEASE "/LTCG"
        )
    endif()
endif()