cmake_minimum_required(VERSION 3.10)

project(file_format_test)

include_directories(include)

set(SOURCES
	src/parser.c
	src/write.c
)

set(HEADERS
	include/macro.h
	include/parser.h
	include/types.h
	include/write.h
)

add_library(file_format ${SOURCES} ${HEADERS})
add_executable(file_format_test src/main.c)

target_link_libraries(file_format_test file_format)

add_custom_command(TARGET file_format_test POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/file ${CMAKE_BINARY_DIR})