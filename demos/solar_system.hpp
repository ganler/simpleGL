//
// Created by ganler-Mac on 2019-10-24.
//

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

template <typename Iter, typename ... Args>
    void seq_add(Iter&& it, Args ... args)
        {  ((*it++ = args), ...);   }

template <
        std::size_t StackCnt = 20,
        std::size_t SectorCnt = 20,
        typename IterV,
        typename IterE>
constexpr decltype(auto) add_sphere(
        float cx, float cy, float cz, float r, std::size_t number, IterV vertex_it, IterE elem_it) noexcept
{
//    using RetVertType = std::array<GLfloat, 3 * (StackCnt+1) * (SectorCnt+1)>;
//    using RetElemType = std::array<GLuint, (StackCnt - 1) * SectorCnt * 6>;

    constexpr float stack_step = glm::pi<float >() / StackCnt;        // 0 ~ pi
    constexpr float sector_step = 2 * glm::pi<float >() / SectorCnt;  // 0 ~ 2pi
    for (std::size_t i = 0; i <= StackCnt; ++i)
    {
        float phi = glm::pi<float >() / 2 - i * stack_step;
        float rcosphi = r * std::cos(phi), z = r * std::sin(phi);
        int k1 = (i + number * StackCnt) * (SectorCnt + 1), k2 = k1 + (SectorCnt + 1);
        for (std::size_t j = 0; j <= SectorCnt; ++j, ++k1, ++k2)
        {
            float theta = j * sector_step;
            float x = rcosphi * std::cos(theta), y = rcosphi * std::sin(theta);
            seq_add(vertex_it, cx+x, cy+y, cz+z);
            if(i < StackCnt && j < SectorCnt)
            {
                if(i != 0)
                    seq_add(elem_it, k1, k2, k1+1);
                if(i != StackCnt-1)
                    seq_add(elem_it, k1+1, k2, k2+1);
            }
        }
    }
    return std::make_tuple(vertex_it, elem_it);
}

void solar_system_demo()
{
    constexpr GLint width = 800, height = 600;
    SGL::session gui(width, height, R"( <<< Jiawei Liu's Solar System👽 >>> )");

    constexpr std::size_t quant_sz   = 30;
    constexpr std::size_t sphere_num = 4;

    std::array<GLfloat, 3 * (quant_sz+1)   * (quant_sz+1) * sphere_num> vertex_data{};
    std::array<GLuint,  6 * (quant_sz - 1) * quant_sz     * sphere_num>    ebo_data{};

    auto&& [lv1, le1] = add_sphere<quant_sz, quant_sz>(0  , 0  , -4 , 1.8, 0, vertex_data.begin(), ebo_data.begin());
    auto&& [lv2, le2] = add_sphere<quant_sz, quant_sz>(0  , 3.8, 0.8, 0.4, 1, lv1, le1);
    auto&& [lv3, le3] = add_sphere<quant_sz, quant_sz>(4.0, 0.4, 0  , 0.2, 2, lv2, le2);
    auto&& [lv4, le4] = add_sphere<quant_sz, quant_sz>(2.0, 1.4, -1 , 0.2, 3, lv3, le3);

    glEnable(GL_DEPTH_TEST);
    SGL::BO  vbo, ebo;
    SGL::VAO vao;

    vbo.write(vertex_data);

    vao.interpret(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Shape.
    vao.vertex_attrib_array(0);

    vao.interpret(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Color it.
    vao.vertex_attrib_array(1);

    ebo.write<GL_ELEMENT_ARRAY_BUFFER>(ebo_data);

    auto program = SGL::make_shader_from_file(
            "../shaders/ss.vertex",
            "../shaders/ss.fragment"
    );
    auto mvp = program.get_uniform("mvp");

    SGL::set_color(0.2f, 0.3f, 0.4f);

    gui.run([&](){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100us);
        // Math Stuff.
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.f, 0.f, 5.f));
        model = glm::translate(model, glm::vec3(0.0, 0.0, -4.0));
        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.1f, 20.0f);
        glm::mat4 mvp_ = projection * view * model;
        // OpenGL Stuff.
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
        program.use();
        glDrawElements(GL_TRIANGLES, ebo_data.size(), GL_UNSIGNED_INT, nullptr); // 注意ebo的类型要注意
    });
}