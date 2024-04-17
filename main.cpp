#include <GLFW/glfw3.h>
#include <iostream>

struct Camera {
    float x, y, z;
    Camera() : x(0), y(0), z(0) {}
};

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5, 0.5, 0.5, 1.0);\n"
    "}\n\0";

int main() {

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    if (!glfwInit()) {
        std::cerr << "failed:glfw\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OGL FPS", nullptr, nullptr);
    if (!window) {
        std::cerr << "failed: create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Camera camera;

    const float movementSpeed = 0.05f;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.z -= movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.z += movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.x -= movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.x += movementSpeed;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
//compile this shit
//g++ -o OpenGLFPS main.cpp -ID:\GLFW\include -LD:\GLFW\build\src -lglfw3 -lopengl32 -lgdi32