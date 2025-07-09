add_executable(demo_context main.cpp)
target_link_libraries(demo_context PRIVATE polykami)

set_target_properties(demo_context PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
)