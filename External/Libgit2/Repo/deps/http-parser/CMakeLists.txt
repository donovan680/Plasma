FILE(GLOB SRC_HTTP "*.c" "*.h")

ADD_LIBRARY(http-parser OBJECT ${SRC_HTTP})
set_target_properties(http-parser PROPERTIES FOLDER "External")
ENABLE_WARNINGS(implicit-fallthrough=1)
