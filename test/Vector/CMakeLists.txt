target_sources(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Vector3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Vector4.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp
)

target_include_directories(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)
