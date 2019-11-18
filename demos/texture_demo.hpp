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

void texture_demo()
{
    constexpr GLint width = 800, height = 600;
    SGL::session gui(width, height, R"( <<< 温金金金球 >>> )");

    constexpr char name[] = "../textures/grid.png";
    auto im = cv::imread(name);
    cv::resize(im, im, {2008, 1200}); // 需要被4整除
    cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
    auto program = SGL::make_shader_from_file(
            "../shaders/tx.vertex",
            "../shaders/tx.fragment"
    );

    gui.run([&](){

        constexpr std::size_t quant_sz   = 40; // 你每个球想有多少个sector and stack

        const float zpos = 10 * std::cos((float)glfwGetTime());
        glfwSetWindowTitle(gui.window, (R"( <<< 温金金金球 >>> : Z --> )" + std::to_string(zpos)).c_str());
        SGL::sphere<quant_sz, quant_sz> wxball(0, 0, zpos, 2);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        wxball.prepare(0, 1);

        auto mvp = program.get_uniform("mvp");

        SGL::set_color(0.2f, 0.3f, 0.4f);

        /* Texture */
        wxball.tex.parami(GL_TEXTURE_WRAP_S, GL_REPEAT);
        wxball.tex.parami(GL_TEXTURE_WRAP_T, GL_REPEAT);

        wxball.tex.parami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        wxball.tex.parami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        wxball.tex.parami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        wxball.tex.parami(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        wxball.tex.load_image(im);
        wxball.tex.mipmap();

        program.set_uniform("texture_source", 0);

        // -----------

        using namespace std::chrono_literals;
        const auto eye = glm::vec3(0.0, 0.0, 15);
        const auto tar = glm::vec3(0, 0, 0);
        constexpr auto up  = glm::vec3(0.0, 1.0, 0.0);
        constexpr int  lnum = 100;
        constexpr float aperture = 0.2;

        glm::vec3 right = glm::normalize(glm::cross(tar - eye, up));
        glm::vec3 p_up = glm::normalize(glm::cross(tar - eye, right));

        std::this_thread::sleep_for(1ms);
        glClear(GL_ACCUM_BUFFER_BIT);
        for (int i = 0; i < lnum; ++i) {
            const auto bokeh = right * std::cosf(SGL::pi * 2 * i / lnum) + p_up * std::sinf(SGL::pi * 2 * i / lnum);
            // Math Stuff.
            glm::mat4 view = glm::lookAt(eye + aperture * bokeh, tar, p_up);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.1f, 30.0f);
            glm::mat4 mvp_ = projection * view;
            // OpenGL Stuff.
            glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
            SGL::active_texture(0); // glActiveTexture(GL_TEXTURE0);
            wxball.tex.bind();
            program.use();
            wxball.draw();
            glAccum(i == 0 ? GL_ACCUM : GL_LOAD, 1.0 / lnum);
        }
        glAccum(GL_RETURN, 1);
    });
}