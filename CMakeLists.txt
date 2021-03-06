cmake_minimum_required(VERSION 3.14)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} main.cpp glad.c)

include_directories(glm)
include_directories(.)

### USE GLAD?
set(SGL_USE_GLAD 1)

# GL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})


# GLEW
find_package(GLEW)
if (GLEW_FOUND AND NOT SGL_USE_GLAD)
    message(STATUS "FIND GLEW_INCLUDE_DIRS => ${GLEW_INCLUDE_DIRS}")
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
else()
    message(STATUS "Using GLAD.")
    add_definitions("-DSGL_USE_GLAD")
endif ()


# GLUT
find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    message(STATUS "FIND GLUT_INCLUDE_DIRS => ${GLUT_INCLUDE_DIRS}")
    add_compile_options(-Wdeprecated-declarations)
    include_directories(${GLUT_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARY})
endif ()


# GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
message(STATUS "FIND GLFW_INCLUDE_DIRS => ${GLFW_INCLUDE_DIRS}" )

target_link_libraries(${PROJECT_NAME} glfw)

# OpenCV
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})