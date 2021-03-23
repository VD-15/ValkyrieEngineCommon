target_sources(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Transform2D.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Transform3D.cpp
)

target_include_directories(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)
