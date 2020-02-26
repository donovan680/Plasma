################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################

if (NOT ${PLASMA_BUILD_PlasmaEditor} AND
    NOT ${PLASMA_BUILD_PlasmaLauncher} AND
    NOT ${PLASMA_BUILD_PlasmaLauncherSharedLibrary} AND
    NOT ${PLASMA_BUILD_BrowserSubProcess})
    set(PLASMA_NO_PROJECTS ON)
else()
    set(PLASMA_NO_PROJECTS OFF)
endif()

################################################################################
# PlasmaEditor
################################################################################
if(${PLASMA_BUILD_PlasmaEditor})
  
  add_subdirectory(PlasmaEditor)

  set(Plasma_OptionalTarget_PlasmaEditor PlasmaEditor)
endif()

################################################################################
# PlasmaLauncher
################################################################################
# actually deal wth the options inside that folder since there are two projects
add_subdirectory(PlasmaLauncher)

################################################################################
# BrowserSubProcess
################################################################################
if(${PLASMA_BUILD_BrowserSubProcess})
  
  add_subdirectory(BrowserSubProcess)

  set(Plasma_OptionalTarget_BrowserSubProcess BrowserSubProcess)
endif()

################################################################################
# set the output directories for all of our targets
################################################################################
plasma_multitarget_output_directories(
                      ${Plasma_OptionalTarget_PlasmaEditor}
                      ${Plasma_OptionalTarget_PlasmaLauncher} 
                      ${Plasma_OptionalTarget_PlasmaLauncherSharedLibrary}
                      ${Plasma_OptionalTarget_BrowserSubProcess}
                      LIBRARY_DIRECTORY ${plasma_library_dir}
                      RUNTIME_DIRECTORY ${plasma_binary_dir}
)

################################################################################
# set flags and definitions
################################################################################

if (NOT ${PLASMA_NO_PROJECTS})
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC OR (CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM-vs2014"))
        plasma_multitarget_compile_options(
            ${Plasma_OptionalTarget_PlasmaEditor}
            ${Plasma_OptionalTarget_PlasmaLauncher}
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
            ${Plasma_OptionalTarget_PlasmaLauncherSharedLibrary}
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
            ${Plasma_OptionalTarget_BrowserSubProcess}
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
        
        # set the correct subsystems for executable targets, and set stack size for the editor
        set_target_properties(
            ${Plasma_OptionalTarget_PlasmaEditor} 
            PROPERTIES 
            LINK_FLAGS "/SUBSYSTEM:WINDOWS /STACK:8388608 /DEBUG ${common_linker_flags}"
        )

        set_target_properties(
            ${Plasma_OptionalTarget_PlasmaLauncher} 
            ${Plasma_OptionalTarget_PlasmaEditor} 
            ${Plasma_OptionalTarget_PlasmaLauncherSharedLibrary} 
            PROPERTIES 
            LINK_FLAGS_RELEASE "/LTCG"
        )
        
        set_target_properties(
            ${Plasma_OptionalTarget_PlasmaLauncher} 
            ${Plasma_OptionalTarget_PlasmaLauncherSharedLibrary} 
            ${Plasma_OptionalTarget_BrowserSubProcess}
            PROPERTIES 
            LINK_FLAGS "/SUBSYSTEM:WINDOWS /DEBUG ${common_linker_flags}"
        )
    else()
        plasma_multitarget_compile_options(
            ${Plasma_OptionalTarget_PlasmaEditor}
            ${Plasma_OptionalTarget_PlasmaLauncher}
            ${Plasma_OptionalTarget_BrowserSubProcess}
            PRIVATE
            PUBLIC
            PRIVATE
            ${common_flags}
        )
        set_target_properties(
            ${Plasma_OptionalTarget_PlasmaEditor}
            ${Plasma_OptionalTarget_PlasmaLauncher}
            ${Plasma_OptionalTarget_BrowserSubProcess}
            PROPERTIES
            LINK_FLAGS "${common_linker_flags}"
        )
    endif()

    if (${platform} STREQUAL "Emscripten")
        set_target_properties(
            ${Plasma_OptionalTarget_PlasmaEditor}
            PROPERTIES SUFFIX ".html"
            LINK_FLAGS "--embed-file \"${plasma_build_out}/PlasmaEditorFileSystem.zip\"@/FileSystem.zip"
        )
        set_target_properties(
            ${Plasma_OptionalTarget_PlasmaLauncher}
            PROPERTIES SUFFIX ".html"
            LINK_FLAGS "--embed-file \"${plasma_build_out}/PlasmaLauncherFileSystem.zip\"@/FileSystem.zip"
        )
    endif()
endif() 