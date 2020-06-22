add_executable(ValkyrieEngineCommonTestDriver
	test.cpp	
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vector)

target_link_libraries(ValkyrieEngineTestDriver
	PRIVATE
		ValkyrieEngineCommon
		Catch2::Catch2
)

include(CTest)
include(Catch)
catch_discover_tests(ValkyrieEngineTestDriver)
