//
//  window.hpp
//  LearnOpenGL
//
//  Created by ganler-Mac on 2019/9/2.
//  Copyright © 2019 ganler-Mac. All rights reserved.
//

#pragma once

#include <simpleGL.hpp>

void empty_window()
{
    using namespace SGL;
    constexpr GLint width = 800, height = 600;
    
    session gui(width, height, "LearnOpenGL");
    gui.run([&](){
        if(glfwGetKey(gui.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(gui.window, true);
        set_color(0.2, 0.3, 0.4);
    });
}




