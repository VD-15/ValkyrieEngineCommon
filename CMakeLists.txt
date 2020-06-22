cmake_minimum_required(VERSION 3.10)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, please conduct builds from within a separate build directory")
endif()

set(CMAKE_DISABLE_IN_SOURCE_BUILD  ON)
set(CMAKE_DISABLE_SOURCE_CHANGES   ON)

project(ValkyrieEngineCommon VERSION 0.1.0)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/ValkyrieEngineCore)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/static_math)

option(VLK_COMMON_BUILD_TESTS "Build ValkyrieEngineCore test projects" OFF)

add_library(ValkyrieEngineCommon
	include/ValkyrieEngineCommon/ValkyrieEngineCommon.hpp
)

target_include_directories(ValkyrieEngineCommon PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ValkyrieEngineCommon PUBLIC cxx_std_20)

target_link_libraries(ValkyrieEngineCommon
	PUBLIC
		static_math
		ValkyrieEngineCore
)

if (BUILD_TESTING EQUAL ON)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
	add_subdirectory(test)
endif()
