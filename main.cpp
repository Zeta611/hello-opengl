#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(
        1280, 720, "Hello, OpenGL", nullptr, nullptr
    );

    glfwMakeContextCurrent(window);

    // Force GLEW to use a modern OpenGL method to check if a function is
    // available
    glewExperimental = GL_TRUE;
    glewInit();


    // Create a Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    // Create vertices
    float vertices[] = {
         0.0f,  0.5f, // Vertex 1
         0.5f, -0.5f, // Vertex 2
        -0.5f, -0.5f  // Vertex 3
    };

    // Upload the vertices to the graphics card
    GLuint vbo;
    glGenBuffers(1, &vbo);  // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  // Make the buffer active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create a vertex shader
    const char *vertexSource = R"glsl(
        #version 150 core

        in vec2 position;

        void main()
        {
            gl_Position = vec4(position, 0.0, 1.0);
        }
    )glsl";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Create a fragment shader
    const char *fragmentSource = R"glsl(
        #version 150 core

        out vec4 outColor;

        void main()
        {
            outColor = vec4(0.0, 1.0, 1.0, 1.0);
        }
    )glsl";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE) {
        printf("Vertex shader successfully compiled!\n");
    } else {
        printf("Vertex shader failed to compile!\n");

        constexpr int buf_size = 512;
        char buffer[buf_size];
        glGetShaderInfoLog(vertexShader, buf_size, nullptr, buffer);
        printf("Log:\n%s", buffer);

        return 1;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE) {
        printf("Fragment shader successfully compiled!\n");
    } else {
        printf("Fragment shader failed to compile!\n");

        constexpr int buf_size = 512;
        char buffer[buf_size];
        glGetShaderInfoLog(fragmentShader, buf_size, nullptr, buffer);
        printf("Log:\n%s", buffer);

        return 1;
    }


    // Combine shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Specify the output buffer of a fragment shader, which is 0 by default
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap back the back buffer and the front buffer after drawing
        glfwSwapBuffers(window);
        glfwPollEvents();
        // Handle ESC key to return to close the window
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    glfwTerminate();
}
