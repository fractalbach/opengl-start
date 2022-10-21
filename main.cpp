#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

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
    processInput(window);                 // check and handle user input
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // specify color to fill the screen with
    glClear(GL_COLOR_BUFFER_BIT);         // clears entire framebuffer, fills with desired color
    glfwPollEvents();                     // checks for events and calls handlers
    glfwSwapBuffers(window);              // double buffering
  }

  glfwTerminate(); // free resources from GLFW
  return 0;
}

// updates the size of the GL viewport to the current size of the window. Call
// this function whenever the window size changes.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

// Handle Keypresses, mouseclicks, and other forms of direct input from the user.
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}