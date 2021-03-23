add_executable(ValkyrieEngineCommonTestDriver
	test.cpp)

target_include_directories(ValkyrieEngineCommonTestDriver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
	
add_subdirectory(VMath)
add_subdirectory(Vector)
add_subdirectory(Matrix)
add_subdirectory(Content)
add_subdirectory(Transform)

add_custom_command(TARGET ValkyrieEngineCommonTestDriver POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/Content/content ${CMAKE_BINARY_DIR}/content
)

add_custom_command(TARGET ValkyrieEngineCommonTestDriver POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/Content/other_content ${CMAKE_BINARY_DIR}/other_content
)

target_link_libraries(ValkyrieEngineCommonTestDriver
	PUBLIC
		ValkyrieEngineCore
		ValkyrieEngineCommon
		Catch2::Catch2
)

include(CTest)
include(${CMAKE_SOURCE_DIR}/deps/Catch2/contrib/Catch.cmake)
catch_discover_tests(ValkyrieEngineCommonTestDriver
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
