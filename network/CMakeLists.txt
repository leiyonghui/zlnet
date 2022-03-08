
aux_source_directory(./ net_SRCS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/libs)
add_library(net ${net_SRCS})
target_link_libraries(net core)
