################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_executable(BrowserSubProcess "")


plasma_setup_library(BrowserSubProcess ${CMAKE_CURRENT_LIST_DIR} TRUE)
set_target_properties(BrowserSubProcess PROPERTIES FOLDER "Projects")

target_sources(BrowserSubProcess
     PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(BrowserSubProcess
                      PUBLIC
                      Common
                      Platform
                      FreeType
                      ZLib
                      Libpng
)

add_custom_command(
    TARGET BrowserSubProcess POST_BUILD
    # executes "cmake -E copy_directory
    COMMAND ${CMAKE_COMMAND} -E copy_directory  
    # input folder
    ${plasma_binary_dir}/BrowserSubProcess                                  
    #output folder
    ${plasma_binary_dir}/PlasmaEditor
)