#pragma once

/* STL */
#include <vector>
#include <thread>

/* A modern C++ OpenGL Lib wrapped by Jiawei Liu */
#include <simpleGL.hpp>

/* GLM Lib */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* OpenCV Lib */
#include <opencv2/opencv.hpp>
#include <simpleGL.hpp>

void texture_and_lighting_demo()
{
    constexpr GLint width = 800, height = 600;
    SGL::session gui(width, height, R"( <<< 温金金金球 >>> )");

    constexpr char name[] = "../textures/fire.jpg";
    auto im = cv::imread(name);
    cv::resize(im, im, {2008, 1200}); // 需要被4整除
    cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
    auto program = SGL::make_shader_from_file(
            "../shaders/tx.vertex",
            "../shaders/tx.fragment"
    );

    auto mvp = program.get_uniform("mvp");
    program.set_uniform("texture_source", 0);

    gui.run([&](){
        constexpr std::size_t quant_sz   = 40; // 你每个球想有多少个sector and stack

        const float ran = (float)glfwGetTime();
        const float zpos = 10 * std::cos(ran/2);
        glfwSetWindowTitle(gui.window, (R"( <<< 温金金金球 >>> : Z --> )" + std::to_string(zpos)).c_str());
        SGL::sphere<quant_sz, quant_sz> wxball(0, 0, zpos, 2);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        wxball.prepare(0, 1, 2);

        /* Texture */
        wxball.tex.parami(GL_TEXTURE_WRAP_S, GL_REPEAT);
        wxball.tex.parami(GL_TEXTURE_WRAP_T, GL_REPEAT);

        wxball.tex.parami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        wxball.tex.parami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        wxball.tex.parami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        wxball.tex.parami(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        wxball.tex.load_image(im);
        wxball.tex.mipmap();

        // -----------

        using namespace std::chrono_literals;
        constexpr auto eye = glm::vec3(0.0, 0.0, 15);
        constexpr auto tar = glm::vec3(0, 0, -10);
        constexpr auto up  = glm::vec3(0.0, 1.0, 0.0);

        std::this_thread::sleep_for(5ms);
        // Math Stuff.
        glm::mat4 view = glm::lookAt(eye, tar, up);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.1f, 30.0f);
        glm::mat4 mvp_ = projection * view;
        // OpenGL Stuff.
        program.set_uniform("light_pos", 30*std::cos(ran), 30*std::sin(ran), 20.f);
        program.set_uniform("view_pos", eye[0], eye[1], eye[2]);
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
        SGL::active_texture(0); // glActiveTexture(GL_TEXTURE0);
        wxball.tex.bind();
        program.use();
        wxball.draw();
    });
}