set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw/glfw-3.4)

# glad
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# stb_image
add_library(stb_image STATIC stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC stb_image)

# JSON
add_library(json INTERFACE)
target_include_directories(json INTERFACE json)

# glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)