# Collect all source files
set(POLYKAMI_SOURCES
        # Core - Window
        core/window/Window.cpp
        core/window/Window_Impl.cpp
)

# Create the library
add_library(polykami STATIC ${POLYKAMI_SOURCES})

# Set library properties
set_target_properties(polykami PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)

# Include directories
target_include_directories(polykami
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
target_link_libraries(polykami
    PUBLIC
        glm
    PRIVATE
        glad
        glfw
        stb_image
        json
)

# Compiler-specific options
if(MSVC)
     target_compile_options(polykami PRIVATE /W4)
else()
     target_compile_options(polykami PRIVATE -Wall -Wextra -pedantic)
endif()

# Platform-specific linking
if(WIN32)
     target_link_libraries(polykami PRIVATE opengl32)
elseif(APPLE)
     target_link_libraries(polykami PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit")
else()
     target_link_libraries(polykami PRIVATE GL X11 pthread dl)
endif()