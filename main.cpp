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

int main()
{
    constexpr GLint width = 800, height = 600;
    SGL::session gui(width, height, R"( <<< 温金金金球 >>> )");

    constexpr std::size_t quant_sz   = 30; // 你每个球想有多少个sector and stack

    SGL::sphere<quant_sz, quant_sz> wxball(-1, -0.4, 2, 2);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    wxball.prepare(0, 1);

    auto program = SGL::make_shader_from_file(
            "../shaders/tx.vertex",
            "../shaders/tx.fragment"
    );

    auto mvp = program.get_uniform("mvp");

    SGL::set_color(0.2f, 0.3f, 0.4f);

    /* Texture */
    constexpr char name[] = "../textures/g14.jpeg";
    auto im = cv::imread(name);
    cv::cvtColor(im, im, cv::COLOR_BGR2RGB);

    wxball.tex.parami(GL_TEXTURE_WRAP_S, GL_REPEAT);
    wxball.tex.parami(GL_TEXTURE_WRAP_T, GL_REPEAT);
    wxball.tex.parami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    wxball.tex.parami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    wxball.tex.parami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    wxball.tex.parami(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    wxball.tex.load_image(im);
    wxball.tex.mipmap();

    program.use();
    program.set_uniform("texture_source", 0);

    gui.run([&](){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100us);
        // Math Stuff.
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.f, -2.f, 4.f));
        model = glm::translate(model, glm::vec3(0.0, 0.0, -4.0));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.f, -1.f, 3.f));
        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.1f, 20.0f);
        glm::mat4 mvp_ = projection * view * model;
        // OpenGL Stuff.
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
        SGL::active_texture(0); // glActiveTexture(GL_TEXTURE0);
        wxball.tex.bind();
        program.use();
        wxball.draw();
    });
}