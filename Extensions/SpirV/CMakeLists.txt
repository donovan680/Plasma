################################################################################
# Author: Joshua Davis
# Copyright 2018, DigiPen Institute of Technology
################################################################################
add_subdirectory(SPIRV-Cross/PlasmaCMake)
if(generate_spirv_projects)
  add_subdirectory(SpirVFiles/PlasmaCMake)
endif()
