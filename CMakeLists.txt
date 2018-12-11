cmake_minimum_required(VERSION 3.5)
project(custommath C)

add_subdirectory(ext)

include_directories(include)
add_library(${PROJECT_NAME} SHARED include/custommath.h src/custommath.c)
target_link_libraries(${PROJECT_NAME} lib_lua)
target_link_libraries(${PROJECT_NAME} lib_lualib)
target_link_libraries(${PROJECT_NAME} lib_lauxlib)

#add post build to copy the lua script to the output directory
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/scripts
			${CMAKE_CURRENT_BINARY_DIR}
)

#create lua exe
add_executable(lua ext/lua/lua.c)
target_link_libraries(lua lib_lua)
target_link_libraries(lua lib_lualib)
target_link_libraries(lua lib_lauxlib)

#add post build command to execute test.lua script with lua.exe
add_custom_command(
	TARGET lua POST_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/lua test.lua
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)