
aux_source_directory(./ test_SRCS)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(test ${test_SRCS})
target_link_libraries(test core net)



