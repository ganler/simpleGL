# <font color="#FF00FF">C</font><font color="#F300FF">S</font><font color="#E700FF">1</font><font color="#DB00FF">0</font><font color="#CF00FF">0</font><font color="#C300FF">4</font><font color="#B700FF">3</font><font color="#AB00FF">3</font><font color="#9F00FF"> </font><font color="#9300FF">A</font><font color="#8700FF">S</font><font color="#7B00FF">S</font><font color="#6F00FF">I</font><font color="#6300FF">G</font><font color="#5700FF">N</font><font color="#4B00FF">M</font><font color="#3F00FF">E</font><font color="#3300FF">N</font><font color="#2700FF">T</font><font color="#1B00FF"> </font><font color="#0F00FF">3</font>

>1753070 Jiawei Liu(刘佳伟)

[TOC]

## <font color="#DB00FF">Question 1-> Phong vs Blinn->Phong</font>

### Phong Reflection Model

Uses 3 kinds of reflection:

- Ambient reflection $\to L_aK_a$.
- Diffuse reflection $\to L_dK_d\max(l*n,0)$.
- Specular reflection $\to L_sK_s\max(r*v, 0)$.

### Blinn-Phong reflection model

<img src="https://i.loli.net/2019/11/19/MYSZIlNsLr98qwJ.png" style="zoom:50%;" />

Before any computation, we know $v, n, l$. Computation of $h$ is easy: $h = \frac{l+v}{||l+v||}$ and computation of $r$ is a little bit complex: $r=2*n*(l*n)-l$ .

- The purpose of the modification is to speed up the computation.
- Blinn-Phong reflection model only modified the **specular reflection** stage $\to L_sK_s\max(\frac{l+v}{||l+v||}*n, 0)$

### comparison

- The 2 models are all approaches to do simplified lighting.
- The 2 models are not equal as $r*v\neq\frac{l+v}{||l+v||}*n$
- The Blinn-Phong reflection is more efficient as computation of $r$ is rather expensive.

## <font color="#DB00FF">Question 2-> Gourand Shading vs Phong Shading</font>

### Gourand Shading

Gourand Shading uses vertex shader and interpolation methods on fragment color. <u>The color of vertexes are given and the color of fragments are computed by interpolation.</u>

There're mainly 3 steps:

1. Normal averaging;
2. Vertex lighting;
3. Interpolation;

### Phong Shading

Phong Shading interpolates surface normals across rasterized polygons and computes pixel colors based on the interpolated normals and a reflection model.

### Comparison

- Gourand Shading is simpler and faster as the number of vertexes is usually less than that of fragments.(For a cube: 8 vertexes and 12 fragments)
- Phong shading is a little bit complex but usually it achieves better lighting effects.

## <font color="#DB00FF">Programming 1-> circle ~ midpoint algorithm</font>

![](https://i.loli.net/2019/11/19/toaMLzwrVsAPmkT.png)

## <font color="#DB00FF">Programming 2-> Rendering: Texture & Lighting</font>

### 1st Demo

- Billiards Green 14;

```c++
/* Parameters */

vec3 light_pos   = vec3(20, 20, 50);
vec3 light_color = vec3(1, 1, 1);
float ambient_fac  = 0.1;
float specular_fac = 0.2;
```

![](https://i.loli.net/2019/11/19/tqgKBPnI35xYarl.png)

### 2nd Demo

- 紫罗兰球

```c++
/* Parameters */

vec3 light_pos   = vec3(20, 20, 50);
vec3 light_color = vec3(/* 忘记保存了... 总之是蓝色 */);
float ambient_fac  = 0.1;
float specular_fac = 0.8;
```

![](https://i.loli.net/2019/11/19/zsnSCDcxToyAH8R.png)

### 3rd Demo

- Ball of red pattern;

```c++
/* Parameters */

vec3 light_pos   = vec3(50*cos(t), 50*sin(t), 20);
vec3 light_color = vec3(1.0, 1.8, 1.5);
float ambient_fac  = 0.15;
float specular_fac = 0.4;
```

![](https://i.loli.net/2019/11/19/ixq3pC4NuVglH7D.png)

## Code

```c++
// Vertex Shader
#version 410 core

layout (location = 0) in vec3 coord3d;
layout (location = 1) in vec2 st_coord;
layout (location = 2) in vec3 norms_;

uniform mat4 mvp;

out vec2 text_coord;
out vec3 norms;
out vec3 frag_pos;

void main(void)
{
   gl_Position = mvp * vec4(coord3d, 1.0);
   frag_pos = coord3d;
   text_coord = st_coord;
   norms = norms_;
}
```

```c++
// Fragment Shader
#version 410 core

in vec2 text_coord;
in vec3 norms;
in vec3 frag_pos;

out vec4 frag_color;

uniform vec3 view_pos;
uniform sampler2D texture_source;

void main(void)
{
    vec3 light_pos = vec3(20, 20, 50);
    vec3 light_color = vec3(1, 1, 1);
    vec4 obj_color = texture(texture_source, text_coord);

    // Ambient
    float ambient_fac = 0.1;
    vec3 ambient = ambient_fac * light_color;

    // Diffuse
    vec3 nnorms = normalize(norms);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(nnorms, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    // Specular
    float specular_fac = 0.2;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, nnorms);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 16); // 反射光别太强了
    vec3 specular = specular_fac * spec * light_color;

    vec3 result = (ambient + diffuse + specular) * obj_color.xyz;
    frag_color = vec4(result, 1.0);
}
```

```c++
// C++
// Using SimpleGL.
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

    constexpr char name[] = "../textures/g14.jpeg";
    auto im = cv::imread(name);
    cv::resize(im, im, {2008, 1200}); // 需要被4整除
    cv::cvtColor(im, im, cv::COLOR_BGR2RGB);
    auto program = SGL::make_shader_from_file(
            "../shaders/tx.vertex",
            "../shaders/tx.fragment"
    );

    auto mvp = program.get_uniform("mvp");
//    auto view_pos = program.get_uniform("view_pos");
    program.set_uniform("texture_source", 0);

    gui.run([&](){
        constexpr std::size_t quant_sz   = 40; // 你每个球想有多少个sector and stack

        const float zpos = 10 * std::cos((float)glfwGetTime()/2);
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

        std::this_thread::sleep_for(10ms);
        // Math Stuff.
        glm::mat4 view = glm::lookAt(eye, tar, up);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.1f, 30.0f);
        glm::mat4 mvp_ = projection * view;
        // OpenGL Stuff.
        program.set_uniform("view_pos", eye[0], eye[1], eye[2]);
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvp_));
        SGL::active_texture(0); // glActiveTexture(GL_TEXTURE0);
        wxball.tex.bind();
        program.use();
        wxball.draw();
    });
}
```

