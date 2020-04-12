add_library(Glew)

set_target_properties(Glew PROPERTIES FOLDER "External")

plasma_setup_library(Glew ${CMAKE_CURRENT_LIST_DIR} FALSE)

target_compile_definitions(Glew
  PUBLIC
    GLEW_STATIC
)

target_sources(Glew
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Repo/src/glew.c
)

target_include_directories(Glew
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Repo/include/
)
