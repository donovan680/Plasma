set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)

# Only done as a hack because we can't find main for some reason (Ubuntu).
if(PLASMA_TARGETOS STREQUAL "Linux")
  add_definitions(-DSDL_MAIN_AVAILABLE)
endif()

add_subdirectory(Repo)

add_library(SDL INTERFACE)

set_target_properties(SDL2-static PROPERTIES FOLDER "External")
set_target_properties(SDL2main PROPERTIES FOLDER "External")

target_link_libraries(SDL
  INTERFACE
    SDL2-static
    SDL2main
)
