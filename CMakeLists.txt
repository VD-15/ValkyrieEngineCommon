cmake_minimum_required(VERSION 3.10)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, please conduct builds from within a separate build directory")
endif()

project(ValkyrieEngineCommon VERSION 0.1.0)

add_library(ValkyrieEngineCommon INTERFACE)

set_target_properties(
	ValkyrieEngineCommon PROPERTIES
		SOVERSION ${ValkyrieEngineCommon_VERSION_MAJOR}
		VERSION ${ValkyrieEngineCommon_VERSION}
		CXX_STANDARD 14
		CXX_STANDARD_REQUIRED FALSE
)

target_include_directories(ValkyrieEngineCommon INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(VLK_COMMON_REQUIRED_VLK_CORE_VERSION 0.0.0)
set(VLK_COMMON_REQUIRED_GCEM_VERSION 1.13.1)

if(NOT TARGET ValkyrieEngineCore)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/ValkyrieEngineCore)
elseif(ValkyrieEngineCore_VERSION VERSION_LESS VLK_COMMON_REQUIRED_VLK_CORE_VERSION)
	message(FATAL_ERROR "Version mismatch: ValkyrieEngineCore. Found: ${ValkyrieEngineCore_VERSION}, must be at least: ${VLK_COMMON_REQUIRED_VLK_CORE_VERSION}")
endif()

if (NOT TARGET gcem)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/gcem)
elseif(gcem_VERSION VERSION_LESS VLK_COMMON_REQUIRED_GCEM_VERSION)
	message(FATAL_ERROR "Version mismatch: gcem. Found: ${gcem_VERSION}, must be at least: ${VLK_COMMON_REQUIRED_gcem_VERSION}")
endif()

target_link_libraries(ValkyrieEngineCommon
	INTERFACE
		gcem
		ValkyrieEngineCore
)

if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
	if (BUILD_TESTING)
		enable_testing()
		add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/Catch2)
		add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
	endif()
endif()
