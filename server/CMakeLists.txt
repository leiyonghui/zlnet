
aux_source_directory(./ SERVER_SRCS)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(server ${SERVER_SRCS})
target_link_libraries(server core net)



