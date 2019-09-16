cmake_minimum_required(VERSION 3.14)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} main.cpp)


include_directories(.)


# GL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})


# GLEW
find_package(GLEW)
if (GLEW_FOUND)
    message(STATUS "FIND GLEW_INCLUDE_DIRS => ${GLEW_INCLUDE_DIRS}")
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
else()
    message(STATUS "GLEW not FOUND... Try to use GLAD.")
    add_definitions("DSGL_USE_GLAD")
endif ()

# GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
message(STATUS "FIND GLFW_INCLUDE_DIRS => " ${GLFW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} glfw)