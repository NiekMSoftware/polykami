# Collect all source files

# Create the library

# Set library properties

# Include directories

# Link libraries

# Compiler-specific options
if(MSVC)
    # target_compile_options(polykami PRIVATE /W4)
else()
    # target_compile_options(polykami PRIVATE -Wall -Wextra -pedantic)
endif()

# Platform-specific linking
if(WIN32)
    # target_link_libraries(polykami PRIVATE opengl32)
elseif(APPLE)
    # target_link_libraries(polykami PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit")
else()
    # target_link_libraries(polykami PRIVATE GL X11 pthread dl)
endif()