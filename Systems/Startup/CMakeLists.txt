################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_library(Startup "")

plasma_setup_library(Startup ${CMAKE_CURRENT_LIST_DIR} TRUE)
plasma_use_precompiled_header(Startup ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(Startup PROPERTIES FOLDER "Systems")

target_sources(Startup
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Startup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Startup.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StartupStandard.hpp
)

target_include_directories(Startup
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/../
)

plasma_target_includes(Startup
  PUBLIC
    Common
    Geometry
    Graphics
)