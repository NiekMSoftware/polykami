add_executable(basic_example main.cpp)
target_link_libraries(basic_example PRIVATE polykami)

set_target_properties(basic_example PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
)