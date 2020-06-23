add_library(Base INTERFACE)

target_link_libraries(Base
	INTERFACE
		ValkyrieEngineCommon
		Catch2::Catch2
)

add_executable(Vector2 Vector2.cpp)
add_executable(Vector3 Vector3.cpp)


target_link_libraries(Vector2 PRIVATE Base)
target_link_libraries(Vector3 PRIVATE Base)

add_test(NAME Vector2 COMMAND Vector2)
add_test(NAME Vector3 COMMAND Vector3)
