target_sources(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Matrix3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Matrix4.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Quaternion.cpp
)

target_include_directories(ValkyrieEngineCommonTestDriver PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)
