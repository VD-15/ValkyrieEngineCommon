cmake_minimum_required(VERSION 3.10)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, please conduct builds from within a separate build directory")
endif()

set(CMAKE_DISABLE_IN_SOURCE_BUILD  ON)
set(CMAKE_DISABLE_SOURCE_CHANGES   ON)

project(ValkyrieEngineCommon VERSION 0.1.0)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/ValkyrieEngineCore)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/static_math)

add_library(ValkyrieEngineCommon
	${CMAKE_CURRENT_SOURCE_DIR}/include/ValkyrieEngineCommon/ValkyrieEngineCommon.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/ValkyrieEngineCommon/Vector.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ValkyrieEngineCommon.cpp
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

if (BUILD_TESTING)
	enable_testing()
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/Catch2)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()
