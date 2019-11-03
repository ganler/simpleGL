//
//  triangle.hpp
//  LearnOpenGL
//
//  Created by ganler-Mac on 2019/9/2.
//  Copyright © 2019 ganler-Mac. All rights reserved.
//

#pragma once

#include <cmath>
#include <chrono>
#include <thread>
#include <simpleGL.hpp>

void draw_triangle()
{
    using namespace SGL;

    session gui(800, 600, "Draw A triangle");
    std::array<float, 15> basev = {
            0.5f, -0.5f, 1.0f, 0.3f, 0.3f,
            -0.5f, -0.5f, 0.3f, 1.0f, 0.3f,
            0.0f,  0.5f, 0.3f, 0.3f, 1.0f};

    auto v = basev;

    VAO vao; // VAO first.
    BO vbo;

    auto program = make_shader_from_file(
            "../shaders/triangle_demo.vertex",
            "../shaders/triangle_demo.fragment");

    constexpr int raw_quant = 100;
    int times = raw_quant;
    bool flag = true;

    auto func = [raw_quant](int x)
    {   return x <= raw_quant * 0.90f ? std::sqrt(x)/(raw_quant / 50) : std::sqrt(x);    };

    gui.run([&](){
        using namespace std::chrono_literals;
        set_color(0.2f, 0.3f, 0.4f);
        std::this_thread::sleep_for(2ms * func(times));
        program.use();

        if(flag && --times == 0)
            flag = false;
        if(!flag && ++times == raw_quant)
            flag = true;

        auto per = times / static_cast<double>(raw_quant);
        for(int i=0; i<3; ++i)
        {
            v[5*i  ] = per * std::sin(M_PI * per + 2*i/3. * M_PI);
            v[5*i+1] = per * std::cos(M_PI * per + 2*i/3. * M_PI);
            for (int j = 2; j < 5; ++j)
                v[5*i+j] = (per*0.7 + 0.3) * basev[5*i+j];
        }

        vbo.write(v);
        vao.interpret(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        vao.interpret(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        vao.bind();

        glDrawArrays(GL_TRIANGLES, 0, v.size());
    });

    vao.remove();
    vbo.remove();
}