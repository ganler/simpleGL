//
//  sympleGL.hpp
//  LearnOpenGL
//
//  Created by ganler-Mac on 2019/9/2.
//  Copyright © 2019 ganler-Mac. All rights reserved.
//

/* Note: This is just header-only. */

#pragma once

#define SGL_MAKE_UNIFORM_FUNC(type, pack_sz, loc)                  \
    if constexpr (pack_sz == 1)                                    \
        glUniform1##type (loc, std::forward<Args>(args)...);       \
    else if constexpr (pack_sz == 2)                               \
        glUniform2##type (loc, std::forward<Args>(args)...);       \
    else if constexpr (pack_sz == 3)                               \
        glUniform3##type (loc, std::forward<Args>(args)...);       \
    else                                                           \
        glUniform4##type(loc, std::forward<Args>(args)...);


#ifdef SGL_USE_GLAD
#include <glad/glad.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include <array>
#include <tuple>
#include <string>
#include <atomic>
#include <fstream>
#include <utility>
#include <iostream>
#include <type_traits>
#include <string_view>
#include <initializer_list>

/*
 
 !!! OpenGL只是一个渲染API，OpenGL的头文件就是各种宏巴拉巴拉的（其一般用宏做API），其cpp也只是用来在系统上找接口上对应的驱动及其动态库，然后load库里面的函数指针。Hard work都是底层干的。嗯，OpenGL是标准，也是一种API封装。
 
 !!! 核心模式和立即渲染模式：
 - 早期OpenGL(before 3.2) ~ 立即渲染模式(immediate mode) => 简单易用，但功能过于高层
 - 3.2之后OpenGL          ~ 核心模式   (core-profile)   => 更多操控细节，操控可以更加灵活
 
 !!! OpenGL易于拓展
 - 硬件公司可通过扩展来支持新的渲染方法。
 if(GL_ARB_extension_name) // 是否满足这个Extension
 // 使用一些新的特性
 else
 // 老方法
 
 !!! OpenGL ~ 状态机
 - OpenGL的状态: OpenGL上下文
 - OpenGL上下文的更改: 设置选项+操作缓冲
 
 !!! GLFW: 提供了渲染基本接口 = 创建上下文，定义窗口参数，处理用户输入。
 FW ~ FrameWork
 
 !!! GLAD:（用来代替GLEW的，GLAD管理OpenGL指针更加方便）
 OpenGL只是一个标准规范，实现由具体开发商针对特定显卡实现的，OpenGL的驱动过多，导致很多参数得被设置为runtime。
 GLAD是继GL3W，GLEW之后，当前最新的用来`访问OpenGL规范接口`的第三方库。
 
 
 */

/*
 !!! In OpenGL, everything is 3D.
 3D坐标转为2D坐标的处理过程是由OpenGL的图形渲染管线（Graphics Pipeline，大多译为管线，实际上指的是一堆原始图形数据途经一个输送管道，期间经过各种变化处理最终出现在屏幕的过程）管理的。
 - 第一部分把你的3D坐标转换为2D坐标
 - 第二部分是把2D坐标转变为实际的有颜色的像素。
 (渲染管线的小程序就是Shader ~ 着色器 ~ OpenGL中用GLSL写成)
 
 !!! 缩写
 - VAO
 - BO
 - IBO/EBO
 
 !!! 三角形的渲染
 - Vertex Sharder: 3d to 3d
 - Primitive Assembly: Input is the output of vertex shader. Render them according to the primitives.
 - Geometry Shader: primitives 2 primitives. (做一些集合上的work)
 - Rasteration Stage: primitives 2 pixiels.
 - Fragment Shader: 计算一个像素的最终颜色
 - Test and Blending:
 
 !!! Vertex Input:
 - OpenGL仅当3D坐标在3个轴（x、y和z）上都为-1.0到1.0的范围内时才处理它，其他返回相当于被裁剪了。 ~ 标准化设备坐标(Normalized Device Coordinates)
 
 */


namespace SGL {
    template <std::size_t N>
        using points = std::array<float, N>;
    template<class T>
        struct always_false : std::false_type {};
    /*
     GLuint index,              ~ where to begin
     GLint size,                ~ how many ${type}s is a pointer
     GLenum type,               ~ Whether to make a transform to make it normalized.
     GLsizei stride,            ~ The bytes between 2 vertexes. => &v[N] - &v[N-1]
     const GLvoid * pointer     ~ Offset of the first vertex.
     */
    template <GLuint T, typename Container> // (buffer_num, BO-ID ~ uint*) /* Wow, BO has a buffer space! */
        inline void bind_data(Container&& c, GLuint draw_t = GL_STATIC_DRAW)
    {   glBufferData(T, sizeof(typename std::remove_reference_t<Container>::value_type) * c.size(), c.data(), draw_t);  }
    
    template <unsigned int T>
        static unsigned int compile_shader(std::string_view source)
    {
        auto id = glCreateShader(T);
        const char* src = source.data();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        
        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            // Cannot compile it.
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            auto info = (char*)alloca(len * sizeof(char));
            glGetShaderInfoLog(id, len * sizeof(char), &len, info);
            std::cerr << (T == GL_VERTEX_SHADER ? "[Vertex]" : "[Fragment]") << " Shader compile failed: "
            << info << '\n';
            std::exit(-1);
        }
        return id;
    }
    
    template<typename Int, typename ... Args>
        static void attach(Int p, Args&& ... args)
    {   // compatible with c++11.
#if __cplusplus < 201703L
        std::initializer_list<nullptr_t>{
            ([&](){  glAttachShader(p, std::forward<Args>(args));  }(), nullptr)...
        };
#else
        (glAttachShader(p, std::forward<Args>(args)), ...);
#endif
    }
    
    template<typename ... Args>
        static void remove_shader(Args&& ... args)
    {   // compatible with c++11.
#if __cplusplus < 201703L
        std::initializer_list<nullptr_t>{
            ([&](){  glDeleteShader(std::forward<Args>(args));  }(), nullptr)...
        };
#else
        (glDeleteShader(std::forward<Args>(args)), ...);
#endif
    }
    
    inline std::string file2str(std::string_view f)
    {
        std::ifstream fs(f.data());
        std::string str;
        
        fs.seekg(0, std::ios::end);
        str.reserve(fs.tellg());
        fs.seekg(0, std::ios::beg);
        
        str.assign(std::istreambuf_iterator<char>(fs),
                   std::istreambuf_iterator<char>());
        return str;
    }
    
    /*
     In OpenGL => vertexShader + fragmentShader.
     */


    // @@@@@@@@@@@@@ GSL::shader
    class shader
    {
    private:
        GLuint m_id;
    public:
        shader(GLuint i = std::numeric_limits<GLuint >::max()) : m_id(i) {}
        void use() const         {  glUseProgram(m_id);  }
        inline GLint get_attrib(std::string_view sv) const
        {
            auto ret = glGetAttribLocation(m_id, sv.data());
            if (ret == -1)
                std::cerr << "Could not bind attribute --> " << sv << std::endl;
            return ret;
        }
        inline GLint get_uniform(std::string_view sv) const
        {
            auto ret = glGetUniformLocation(m_id, sv.data());
            if (ret == -1)
                std::cerr << "Could not bind attribute --> " << sv << std::endl;
            return ret;
        }
        inline void remove()
        {
            glDeleteProgram(m_id);
        }
        template <typename ... Args>
            inline void set(std::string_view sv, Args ... args) const
        {
            using common_t = std::common_type_t<Args...>;
            constexpr std::size_t pack_sz = sizeof...(Args);
            static_assert(pack_sz > 0 && pack_sz <= 4, "Parameter numbers doesn't match!");
            // sfinae
            if constexpr      (GLint loc = glGetUniformLocation(m_id, sv.data()); std::is_floating_point_v<common_t> )
            {   SGL_MAKE_UNIFORM_FUNC(f, pack_sz, loc)     }
            else if constexpr ( std::is_same_v<common_t, GLuint > )
            {   SGL_MAKE_UNIFORM_FUNC(i, pack_sz, loc)     }
            else if constexpr ( std::is_convertible_v<common_t, GLint > )
            {   SGL_MAKE_UNIFORM_FUNC(ui, pack_sz, loc)    }
            else
                static_assert(always_false<common_t >::value, "Parameter's type doesn't match!");
        }
    };

    shader make_shader_from_str(std::string_view vs, std::string_view fs)
    {
        auto program = glCreateProgram();
        auto v_shader = compile_shader<GL_VERTEX_SHADER>(vs);
        auto f_shader = compile_shader<GL_FRAGMENT_SHADER>(fs);
        
        attach(program, v_shader, f_shader);
        glLinkProgram(program);
        glValidateProgram(program);
        remove_shader(v_shader, f_shader);

        return program;
    }

    template <typename ... Args>
    shader make_shader_from_file(Args&& ... args)
    {
        return make_shader_from_str(file2str(std::forward<Args>(args))...);
    }
    
    inline void set_color(float r, float g, float b, float a = 1)
    {
        glClearColor(r, g, b, a);
        // glClearColor + glClear 组合 -> 清屏并设置颜色
    }


    // @@@@@@@@@@@@@ GSL::OO
    class BO
    {
    public:
        BO(GLuint sz = 1) : size(sz) {  glGenBuffers(sz, &m_id);  }
        template<GLuint T = GL_ARRAY_BUFFER, typename ... Args>
            inline void write(Args&& ... args) /* Wow, GL_ARRAY_BUFFER uses BO buffer */
        {
            glBindBuffer(T, m_id);
            bind_data<T>(std::forward<Args>(args)...);
        }
        inline void remove()
        {   glDeleteBuffers(size, &m_id);  }
        GLuint get() const
        {
            return m_id;
        }
    private:
        GLuint m_id  = 0;
        GLuint size = 0;
    }; // class BO


    // @@@@@@@@@@@@@ GSL::VAO
    class VAO
    {
    public:
        VAO(GLuint sz = 1) : size(sz)
        {
            glGenVertexArrays(sz, &vao);
            glBindVertexArray(vao);
            glEnableVertexAttribArray(0);  // 为了性能，顶点属性默认是禁用的，这里我们要打开才能看到东西。
            // VBO对于的所有状态都将存储在VAO中 ~ BO 要和 VAO 搭配好。
            // OpenGL的核心模式要求我们使用VAO，所以它知道该如何处理我们的顶点输入。如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西。
        }

        /*
void glVertexAttribPointer(	GLuint index,
                            GLint size,
                            GLenum type,
                            GLboolean normalized,
                            GLsizei stride,
                            const GLvoid * pointer);
         */
        inline void interpret(GLuint index,
                              GLint  size,
                              GLenum type,
                              GLboolean normalized,
                              GLsizei stride,
                              const GLvoid * pointer) const
        {  glVertexAttribPointer(index, size, type, normalized, stride, pointer);  }
        inline static void vertex_attrib_array(GLint v)
        {  glEnableVertexAttribArray(v); }
        template <GLuint T>
            inline void unbind() const
        {
            /* Unbind Buffer */ glBindBuffer(T, 0); // Bind it to nothing.
            /* Unbind Vertex */ glBindVertexArray(0);
        }
        template<GLuint T = GL_ARRAY_BUFFER, typename ... Args>
            inline void interpret_and_unbind(Args&& ... args) const
        {
            interpret(std::forward<Args>(args)...);
            unbind<T>();
        }
        inline void bind() const
        {  glBindVertexArray(vao);  }
        inline void remove() const
        {  glDeleteVertexArrays(size, &vao);  }
    private:
        GLuint vao = 0;
        GLuint size = 0;
    }; // class VAO

    template<
            int MajorV = 4,
            int MinorV = 1,
            int ProfT = GLFW_OPENGL_CORE_PROFILE>
    struct session_config{
        static constexpr int major_v = MajorV;
        static constexpr int minor_v = 1;
        static constexpr int prof_t = ProfT;
    };
    
    // @@@@@@@@@@@@@ GSL::session
    class session
    {
    public:
        GLFWwindow* window;
    public:
        template <typename T = session_config<>>
            session(int w,
                    int h,
                    const char * str     = "unnamed",
                    GLFWmonitor* monitor = nullptr,
                    GLFWwindow * share   = nullptr,
                    T = T{})
        {
            init(T::major_v, T::minor_v, T::prof_t);
            make_window(w, h, str, monitor, share);
        }

        // Activate : Rule of 5.
        ~session()
        {
            if( --window_cnt == 0)
                glfwTerminate();
        }
        session(const session& s) = delete;
        session(session&& s)      = delete;

        inline void make_window(
                int w,
                int h,
                const char * str     = "unnamed",
                GLFWmonitor* monitor = nullptr,
                GLFWwindow * share   = nullptr)
        {
            // For glfw-Window manipulation Doc: http://www.glfw.org/docs/latest/window.html#window_hints
            window = glfwCreateWindow(w, h, str, monitor, share);
            // Test GLFW initialization.
            if( nullptr == window  )
            {
                std::cerr << "glfwWindows cannot be created\n";
                std::exit(-1);
            }
            glfwMakeContextCurrent(window); // 在当前线程建立win的context // 必须先执行

#ifdef SIM_USE_GLAD
            // GLAD test.
            if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
            {
                std::cerr << "GLAD failed to initialize!\n";
#else
            // GLEW TEST
            glewExperimental = true;
            if (glewInit() != GLEW_OK)
            {
                std::cerr << "GLEW failed to initialize!\n";
#endif
                std::exit(-1);
            }
//                glfwGetFramebufferSize(window, &w, &h); // Compatible for Retina.
//                glViewport(0, 0, w, h);
//                glfwSetFramebufferSizeCallback(win, [](GLFWwindow* win_, int w_, int h_)
            //                                   {
            //                                       glViewport(0, 0, w_, h_);
            //                                   });
        }

        template <typename Func>
            inline void run(Func&& func) const
        {
            while(!glfwWindowShouldClose(window))
            {
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);         // 颜色`COLOR`清屏
                func();
                glfwSwapBuffers(window); // 交换颜色缓冲，这里的Buffer是win的buffer，其存储着win的像素信息
                glfwPollEvents();     // 检查触发事件，并启动回调函数
            }
        }
        
        inline const GLubyte* version() const noexcept
        {// Initialize ur GL first.
            return glGetString(GL_VERSION);
        }

        template <GLint T>
            inline GLint get_info() const noexcept
        {
            int n;
            glGetIntegerv(T, &n);
            return n;
        }

        template <typename Func, typename ... Args>
            inline void call_back(Func&& f, Args&& ... args)
        {
            glfwSetKeyCallback(window, std::forward<Func>(f));
            if constexpr (sizeof...(Args) > 0)
                glfwSetInputMode(window, std::forward<Args>(args)...);
        }
    private:
        inline static std::atomic<std::size_t> window_cnt {0};
        inline void init(int major_v = 4, int minor_v = 1, int prof_type=GLFW_OPENGL_CORE_PROFILE) noexcept
        {   // glfwWindowHint(A, v)是用v值来配置参数A的
            if( window_cnt++ == 0 )
                glfwInit();
            
            if(major_v != -1 && minor_v != -1)
            {   // No need to make this a rule.
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_v);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_v);
                glfwWindowHint(GLFW_OPENGL_PROFILE, prof_type);
#ifdef __APPLE__
                // OSX对于GL2.1以上的版本只支持Core Profile.
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
            }
        }
    };
    
}
