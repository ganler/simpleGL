#pragma once

#include <simpleGL.hpp>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>  // Sorry, for convinience I'd like to use GLUT.
#else
#include <GL/glut.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>

constexpr std::size_t w = 800, h = 600;
SGL::shader program;
GLuint vbo_, cbo_, ibo_;
GLint coord3d, v_color, mvp;

constexpr std::array<GLfloat, 3*8> cube_v = {
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0
};

constexpr std::array<GLfloat, 3*8> cube_c = {
        0.0, 0.0, 1.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 1.0
};

constexpr std::array<GLushort, 3*6*2> index_mapping = {
        0, 1, 2,     0, 2, 3,
        1, 5, 6,     1, 2, 6,
        5, 6, 7,     4, 5, 7,
        0, 3, 4,     3, 4, 7,
        1, 4, 5,     0, 1, 4,
        2, 3, 6,     3, 6, 7
};

void draw_cube(int c, char* v[])
{
    glutInit(&c, v); // Foo.
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow("LiuJiawei\'s rotating CUBE");

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW INIT Failed" << std::endl;
        std::exit(-1);
    }

    program = SGL::make_shader_from_file(
            "../shaders/cube_demo.vertex",
            "../shaders/cube_demo.fragment");

    SGL::BO vvbo, cvbo, ibo;
    vvbo.write(cube_v);
    cvbo.write(cube_c);
    ibo.write<GL_ELEMENT_ARRAY_BUFFER>(index_mapping);

    vbo_ = vvbo.get();
    cbo_ = cvbo.get();
    ibo_ = ibo.get();

    coord3d = program.get_attrib("coord3d");
    v_color = program.get_attrib("v_color");
    mvp = program.get_uniform("mvp");

    glutDisplayFunc([](){ // Loop zone. // 带捕获的lambda不可以转化为ptr
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        program.use();

        glEnableVertexAttribArray(coord3d);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glVertexAttribPointer(coord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(v_color);
        glBindBuffer(GL_ARRAY_BUFFER, cbo_);
        glVertexAttribPointer(v_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        glDrawElements(GL_TRIANGLES, index_mapping.size(), GL_UNSIGNED_SHORT, 0);

        glDisableVertexAttribArray(coord3d);
        glDisableVertexAttribArray(v_color);
        glutSwapBuffers();
    });

    glutIdleFunc([](){
        using namespace std::chrono_literals;
        static int turn = 0;
        static float base = 0, i = 0.;
        base += std::pow(std::sin(i += 0.1), 2) * 10;
        std::this_thread::sleep_for(0.5ms);
        float angle = base;       // Aim angle.

        auto cur = (++turn / 78) % 3;
        glm::vec3 axis_y(cur == 0, cur == 1, cur == 2);

        glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 projection = glm::perspective(45.0f, 1.0f * w / h, 0.1f, 10.0f);
        glm::mat4 mvp_ = projection * view * model * anim;
        program.use();
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
        glutPostRedisplay();
    });

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();

    program.remove();
    vvbo.remove();
    cvbo.remove();
    ibo.remove();
}