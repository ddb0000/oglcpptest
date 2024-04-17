#include <GLFW/glfw3.h>
#include <iostream>

// Define a camera struct or class (this is a simple placeholder)
struct Camera {
    float x, y, z;
    Camera() : x(0), y(0), z(0) {}
};

int main() {
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

    // this value will control the speed of the movement
    const float movementSpeed = 0.05f;

    while (!glfwWindowShouldClose(window)) {
        // Poll for and process events
        glfwPollEvents();

        // Handle input
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.z -= movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.z += movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.x -= movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.x += movementSpeed;

        // update view matrix with camera's new position
        // and then use that view matrix for rendering

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
