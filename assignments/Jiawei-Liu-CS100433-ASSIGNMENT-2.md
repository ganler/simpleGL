# <font color="#FF00FF">C</font><font color="#F300FF">S</font><font color="#E700FF">1</font><font color="#DB00FF">0</font><font color="#CF00FF">0</font><font color="#C300FF">4</font><font color="#B700FF">3</font><font color="#AB00FF">3</font><font color="#9F00FF"> </font><font color="#9300FF">A</font><font color="#8700FF">S</font><font color="#7B00FF">S</font><font color="#6F00FF">I</font><font color="#6300FF">G</font><font color="#5700FF">N</font><font color="#4B00FF">M</font><font color="#3F00FF">E</font><font color="#3300FF">N</font><font color="#2700FF">T</font><font color="#1B00FF"> </font><font color="#0F00FF">2</font>

> 1753070 刘佳伟

[TOC]

## <font color="#C000FF">1</font><font color="#BD00FF">.</font><font color="#BA00FF"> </font><font color="#B700FF">D</font><font color="#B400FF">i</font><font color="#B100FF">f</font><font color="#AE00FF">f</font><font color="#AB00FF">e</font><font color="#A800FF">r</font><font color="#A500FF">e</font><font color="#A200FF">n</font><font color="#9F00FF">c</font><font color="#9C00FF">e</font><font color="#9900FF">s</font><font color="#9600FF"> </font><font color="#9300FF">b</font><font color="#9000FF">e</font><font color="#8D00FF">t</font><font color="#8A00FF">w</font><font color="#8700FF">e</font><font color="#8400FF">e</font><font color="#8100FF">n</font><font color="#7E00FF"> </font><font color="#7B00FF">o</font><font color="#7800FF">r</font><font color="#7500FF">t</font><font color="#7200FF">h</font><font color="#6F00FF">o</font><font color="#6C00FF">g</font><font color="#6900FF">r</font><font color="#6600FF">a</font><font color="#6300FF">p</font><font color="#6000FF">h</font><font color="#5D00FF">i</font><font color="#5A00FF">c</font><font color="#5700FF"> </font><font color="#5400FF">a</font><font color="#5100FF">n</font><font color="#4E00FF">d</font><font color="#4B00FF"> </font><font color="#4800FF">p</font><font color="#4500FF">e</font><font color="#4200FF">r</font><font color="#3F00FF">s</font><font color="#3C00FF">p</font><font color="#3900FF">e</font><font color="#3600FF">c</font><font color="#3300FF">t</font><font color="#3000FF">i</font><font color="#2D00FF">v</font><font color="#2A00FF">e</font><font color="#2700FF"> </font><font color="#2400FF">3</font><font color="#2100FF">D</font><font color="#1E00FF"> </font><font color="#1B00FF">v</font><font color="#1800FF">i</font><font color="#1500FF">e</font><font color="#1200FF">w</font><font color="#0F00FF">i</font><font color="#0C00FF">n</font><font color="#0900FF">g</font><font color="#0600FF"> </font><font color="#0300FF">p</font><font color="#0000FF">r</font><font color="#0000FF">o</font><font color="#0000FF">c</font><font color="#0000FF">e</font><font color="#0000FF">s</font><font color="#0000FF">s</font><font color="#0000FF">e</font><font color="#0000FF">s</font>

#### Orthographic viewing

> Orthographic viewing uses **parallel projection**, in which all the projection lines are orthogonal to the projection plaine, making every plane of the scenen appearing in affine transformation on the viewing surface.
>
> - Orthographic viewing tosses out weight in z axis.
>
> > In practice, we just set `z = 0`.

<img src="https://i.loli.net/2019/10/22/OVFrzbEGD173Xmi.png" style="zoom:50%;" />

#### Perspective viewing

> Different from orthographic viewing, in perspective viewing objects appear smaller when the distance from the observer increases. (The futher, the smaller).
>
> - In perspective viewing, scale diminishes in z axis.
>
> > $$
> > x_p = \frac{x}{z/d}\\
> > y_p = \frac{y}{z/d}\\
> > z_p = d
> > $$

<img src="https://i.loli.net/2019/10/22/qND9OIK6XHPwSBR.png" style="zoom:50%;" />



---

## <font color="#C000FF">2</font><font color="#BC00FF">.</font><font color="#B800FF"> </font><font color="#B400FF">W</font><font color="#B000FF">h</font><font color="#AC00FF">a</font><font color="#A800FF">t</font><font color="#A400FF"> </font><font color="#A000FF">i</font><font color="#9C00FF">s</font><font color="#9800FF"> </font><font color="#9400FF">t</font><font color="#9000FF">h</font><font color="#8C00FF">e</font><font color="#8800FF"> </font><font color="#8400FF">d</font><font color="#8000FF">i</font><font color="#7C00FF">f</font><font color="#7800FF">f</font><font color="#7400FF">e</font><font color="#7000FF">r</font><font color="#6C00FF">e</font><font color="#6800FF">n</font><font color="#6400FF">c</font><font color="#6000FF">e</font><font color="#5C00FF"> </font><font color="#5800FF">b</font><font color="#5400FF">e</font><font color="#5000FF">t</font><font color="#4C00FF">w</font><font color="#4800FF">e</font><font color="#4400FF">e</font><font color="#4000FF">n</font><font color="#3C00FF"> </font><font color="#3800FF">t</font><font color="#3400FF">h</font><font color="#3000FF">e</font><font color="#2C00FF"> </font><font color="#2800FF">c</font><font color="#2400FF">l</font><font color="#2000FF">i</font><font color="#1C00FF">p</font><font color="#1800FF"> </font><font color="#1400FF">s</font><font color="#1000FF">p</font><font color="#0C00FF">a</font><font color="#0800FF">c</font><font color="#0400FF">e</font><font color="#0000FF"> </font><font color="#0000FF">a</font><font color="#0000FF">n</font><font color="#0000FF">d</font><font color="#0000FF"> </font><font color="#0000FF">N</font><font color="#0000FF">D</font><font color="#0000FF">C</font>

> The difference is :
>
> - **Dimension**:
>   - Clip space is a **4D** space
>   - NDC space is a **3D** space(at least in OpenGL)
> - **Relation**:
>   - Clip space is independent of camera and viewport
>   - NDC space is relative to camera and viewport(as the vertexes are the perspective division step)
> - **Range**:
>   - There is no strict numeric rule in clip space.
>   - In NDC space, all vertexes are in the range of `[-1, 1]`.



---

## <font color="#C000FF">3</font><font color="#BB00FF">.</font><font color="#B600FF"> </font><font color="#B100FF">W</font><font color="#AC00FF">h</font><font color="#A700FF">y</font><font color="#A200FF"> </font><font color="#9D00FF">d</font><font color="#9800FF">o</font><font color="#9300FF">e</font><font color="#8E00FF">s</font><font color="#8900FF"> </font><font color="#8400FF">c</font><font color="#7F00FF">l</font><font color="#7A00FF">i</font><font color="#7500FF">p</font><font color="#7000FF"> </font><font color="#6B00FF">p</font><font color="#6600FF">e</font><font color="#6100FF">r</font><font color="#5C00FF">f</font><font color="#5700FF">o</font><font color="#5200FF">r</font><font color="#4D00FF">m</font><font color="#4800FF">e</font><font color="#4300FF">d</font><font color="#3E00FF"> </font><font color="#3900FF">i</font><font color="#3400FF">n</font><font color="#2F00FF"> </font><font color="#2A00FF">t</font><font color="#2500FF">h</font><font color="#2000FF">e</font><font color="#1B00FF"> </font><font color="#1600FF">c</font><font color="#1100FF">l</font><font color="#0C00FF">i</font><font color="#0700FF">p</font><font color="#0200FF"> </font><font color="#0000FF">s</font><font color="#0000FF">p</font><font color="#0000FF">a</font><font color="#0000FF">c</font><font color="#0000FF">e</font>

> 1. **Avoid degeneracies**
>    1. We do not need to draw things behind the eye
>    2. Avoid division by `0`
> 2. **Efficiency**
>    1. We do not need to waste time to compute things that won't be drawn
> 3. **CSG boolean operations**
> 4. **Hidden-surface removal**
> 5. **Shadows**



---

## <font color="#C000FF">4</font><font color="#BD00FF">.</font><font color="#BA00FF"> </font><font color="#B700FF">W</font><font color="#B400FF">h</font><font color="#B100FF">a</font><font color="#AE00FF">t</font><font color="#AB00FF"> </font><font color="#A800FF">a</font><font color="#A500FF">r</font><font color="#A200FF">e</font><font color="#9F00FF"> </font><font color="#9C00FF">t</font><font color="#9900FF">h</font><font color="#9600FF">e</font><font color="#9300FF"> </font><font color="#9000FF">d</font><font color="#8D00FF">i</font><font color="#8A00FF">f</font><font color="#8700FF">f</font><font color="#8400FF">e</font><font color="#8100FF">r</font><font color="#7E00FF">e</font><font color="#7B00FF">n</font><font color="#7800FF">c</font><font color="#7500FF">e</font><font color="#7200FF">s</font><font color="#6F00FF"> </font><font color="#6C00FF">b</font><font color="#6900FF">e</font><font color="#6600FF">t</font><font color="#6300FF">w</font><font color="#6000FF">e</font><font color="#5D00FF">e</font><font color="#5A00FF">n</font><font color="#5700FF"> </font><font color="#5400FF">p</font><font color="#5100FF">a</font><font color="#4E00FF">i</font><font color="#4B00FF">n</font><font color="#4800FF">t</font><font color="#4500FF">e</font><font color="#4200FF">r</font><font color="#3F00FF">'</font><font color="#3C00FF">s</font><font color="#3900FF"> </font><font color="#3600FF">a</font><font color="#3300FF">l</font><font color="#3000FF">g</font><font color="#2D00FF">o</font><font color="#2A00FF">r</font><font color="#2700FF">i</font><font color="#2400FF">t</font><font color="#2100FF">h</font><font color="#1E00FF">m</font><font color="#1B00FF">s</font><font color="#1800FF"> </font><font color="#1500FF">a</font><font color="#1200FF">n</font><font color="#0F00FF">d</font><font color="#0C00FF"> </font><font color="#0900FF">Z</font><font color="#0600FF">-</font><font color="#0300FF">b</font><font color="#0000FF">u</font><font color="#0000FF">f</font><font color="#0000FF">f</font><font color="#0000FF">e</font><font color="#0000FF">r</font><font color="#0000FF">?</font>

> **Painter's Algorithm**:
>
> - Sort all elements first then fully paint them **one by one**(near to far).
> - It's **memory-saving** but not time-saving.
>
> **Z-buffer**:
>
> - Store current depth of all pixels, then paint them **pixel by pixel**.
> - It's **time-saving** but not memory-saving.
>
> **Example:**
>
> If we draw 2 elements: `\` and `/`:
>
> - Painter's algorithm: `X`
> - Z-buffer: `>`(right part of `X` will not be drawn)

---

## <font color="#C000FF">5</font><font color="#B900FF">.</font><font color="#B200FF"> </font><font color="#AB00FF">W</font><font color="#A400FF">h</font><font color="#9D00FF">a</font><font color="#9600FF">t</font><font color="#8F00FF"> </font><font color="#8800FF">i</font><font color="#8100FF">s</font><font color="#7A00FF"> </font><font color="#7300FF">t</font><font color="#6C00FF">h</font><font color="#6500FF">e</font><font color="#5E00FF"> </font><font color="#5700FF">c</font><font color="#5000FF">a</font><font color="#4900FF">u</font><font color="#4200FF">s</font><font color="#3B00FF">e</font><font color="#3400FF"> </font><font color="#2D00FF">o</font><font color="#2600FF">f</font><font color="#1F00FF"> </font><font color="#1800FF">Z</font><font color="#1100FF">-</font><font color="#0A00FF">f</font><font color="#0300FF">i</font><font color="#0000FF">g</font><font color="#0000FF">h</font><font color="#0000FF">t</font><font color="#0000FF">i</font><font color="#0000FF">n</font><font color="#0000FF">g</font><font color="#0000FF">?</font>

> **Z-fighting** is a phenomenon which occurs when two or more primitives have similar or identical values in the Z buffer. 
>
> > Solutions:
> >
> > - Higher presicion Z-buffer;(use 64-bit float point number rather than 32-bit one)
> > - Switch to other rendering algorithm, e.g. ray tracing.
> > - Remove the overlapped part.

---

## <font color="#D0FF00">P</font><font color="#B9E800">r</font><font color="#A2D100">o</font><font color="#8BBA00">g</font><font color="#74A300">r</font><font color="#5D8C00">a</font><font color="#468000">m</font><font color="#2F8000">m</font><font color="#188000">i</font><font color="#018000">n</font><font color="#008000">g</font>

### Well, to build a solar system, we should make a sphere first

> I chose the most naive to draw a sphere.
>
> <img src="http://www.songho.ca/opengl/files/gl_sphere01.png" alt="Parametric equation of a sphere" style="zoom:33%;" /> <img src="http://www.songho.ca/opengl/files/gl_sphere02.png" alt="Sectors and stacks of a sphere" style="zoom:33%;" />
> $$
> x = r * \cos(\phi) * \cos(\theta)\\
>      y = r * \cos(\phi) * \sin(\theta)\\
>      z = r * \sin(\phi)
> $$
> That's how I arrange the points.
>
> As points have been arranged, we need to define the painting order to calculate the EBO.
>
> <img src="http://www.songho.ca/opengl/files/gl_sphere03.png" alt="vertex indices of sphere" style="zoom:50%;" />
>
> Note that, both top and bottom are triangles, while other places are trapezoids.

Here's the implementation of one sphere. (To compile this code, you may need a compiler that supports C++17, e.g. gcc7.4+. Yes, I am a modern C++ programmer!)

<img src="https://i.loli.net/2019/10/25/FeIrx47ijPuURC5.png" style="zoom: 33%;" />

> 心得：
>
> 一定要注意ebo的data的类型要和drawElement的类型一样。不然就会发生我这种“一杯茶，一包烟，OpenGL画一天”的惨剧。

### Let's move

![](https://i.loli.net/2019/10/26/keRy1WzlBMDGCuS.png)

![](https://i.loli.net/2019/10/25/42BAMayzWQiDbpo.jpg)



---

## Ref

http://www.songho.ca/opengl/gl_sphere.html



---

## Source Code

You can view it on my [GitHub](https://github.com/ganler/simpleGL).

```c++
//
// Created by ganler-Mac on 2019-10-24.
//

#pragma once

/* STL */
#include <vector>
#include <thread>

/* A modern C++ OpenGL Lib wrapped by Jiawei Liu(ganler is my nickname) */
// https://github.com/ganler/simpleGL
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
        glm::mat4 model = glm::rotate(
          	glm::mat4(1.0f), 
          	(float)glfwGetTime(), 
          	glm::vec3(0.f, 0.f, 5.f)
        );
        model = glm::translate(model, glm::vec3(0.0, 0.0, -4.0));
        glm::mat4 view = glm::lookAt(
          	glm::vec3(0.0, 0.0, 10.0), 
          	glm::vec3(0.0, 0.0, -1.0), 
          	glm::vec3(0.0, 1.0, 0.0)
        );
        glm::mat4 projection = glm::perspective(
          	glm::radians(45.0f), 
          	1.0f * width / height, 
          	0.1f, 
          	20.0f
        );
        glm::mat4 mvp_ = projection * view * model;
        // OpenGL Stuff.
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
        program.use();
        glDrawElements(GL_TRIANGLES, ebo_data.size(), GL_UNSIGNED_INT, nullptr); 
      	// 注意ebo的类型要注意
    });
}
```

