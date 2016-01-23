cmake_minimum_required(VERSION 2.8)

project(xsde-cmake)

# include directories to make them reachable by #include commands 
include_directories(
	# include library directory 
	# so #include <xsde/something.h> works everywhere in the project
	${CMAKE_CURRENT_SOURCE_DIR}/libxsde

	# include directory with generated config headers
	# so #include <xsde/config.h> also works
	${CMAKE_CURRENT_BINARY_DIR}/libxsde/xsde/include
)

# adding subdirectories to build nested CMakeLists.txt files
add_subdirectory(libxsde) # library
add_subdirectory(example-hybrid-hello) # example
