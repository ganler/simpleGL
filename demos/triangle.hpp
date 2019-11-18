//
//  triangle.hpp
//  LearnOpenGL
//
//  Created by ganler-Mac on 2019/9/2.
//  Copyright © 2019 ganler-Mac. All rights reserved.
//

#pragma once

#include <simpleGL.hpp>

void draw_triangle()
{
    using namespace SGL;
    session gui(800, 600, "Draw A triangle");
    std::array<float, 15> basev = {
            0.5f, -0.5f, 1.0f, 0.3f, 0.3f,
            -0.5f, -0.5f, 0.3f, 1.0f, 0.3f,
            0.0f,  0.5f, 0.3f, 0.3f, 1.0f}, v = basev;;

    VAO vao; // VAO first.
    BO vbo;

    auto program = make_shader_from_file(
            "../shaders/triangle_demo.vertex",
            "../shaders/triangle_demo.fragment");

    constexpr int raw_quant = 1000;
    int times = raw_quant;
    bool flag = true;

    gui.run([&](){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2ms * std::cos(times));
        program.use();

        flag = (flag) ? --times != 0 : ++times == raw_quant;
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
        glDrawArrays(GL_TRIANGLES, 0, v.size());
    });
}