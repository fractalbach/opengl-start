#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

// updates the size of the GL viewport to the current size of the window. Call
// this function whenever the window size changes.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

int main() {
  // instantiate the GLFW window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create GLFW window object
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD. GLAD manages function pointers for OpenGL.
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set Dimensions of the Viewport
  glViewport(0, 0, 800, 600);

  // Tell GLFW to resize the GL viewport whenever we resize the window.
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // The Render Loop.
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate(); // free resources from GLFW
  return 0;
}
