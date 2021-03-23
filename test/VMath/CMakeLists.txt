target_sources(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/VMath.cpp
)

target_include_directories(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)
