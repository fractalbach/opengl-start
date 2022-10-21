#include <glad/glad.h> // Must be included before GLFW

#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// =====================================================================================================================

const float vertices[] = {
    -0.5f, -0.5f, 0.0f, // vertex 1
    0.5f,  -0.5f, 0.0f, // vertex 2
    0.0f,  0.5f,  0.0f  // vertex 3
};

const std::string file_to_string(std::string filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

const char *vertexShaderSource = file_to_string("shaders/simple.vert").c_str();

// =====================================================================================================================

// Updates the size of the GL viewport to the current size of the window. Call whenever the window size changes.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

// Handle Keypresses, mouseclicks, and other forms of direct input from the user.
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void process_render_commands(GLFWwindow *window) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // specify color to fill the screen with
  glClear(GL_COLOR_BUFFER_BIT);         // clears entire framebuffer, fills with desired color
}

// Creates and Loads a GL-buffer to hold vertex data for a simple triangle
void load_triangle() {
  unsigned int VBO;                   // id for a Vertex Buffer Object (VBO)
  glGenBuffers(1, &VBO);              // generate a openGL buffer object, and save the ID
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // binds buffer so that it becomes the "current buffer" to modify
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy user data to current buffer
}

// Loads and Compiles a simple Vertex Shader
void load_and_compile_vertex_shader() {
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);            // create an empty shader object and save the ID
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // loads the shader source code
  glCompileShader(vertexShader);                              // dynamically compiles the shader source code

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // check for any errors in our shader compilation
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // provides useful compile-time error information
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  } else {
    std::cout << "Loaded Shader" << std::endl;
  }
}

// =====================================================================================================================

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

  // prepare buffers for vertices, compile and load shaders, and other stuff
  load_triangle();
  load_and_compile_vertex_shader();

  // The Render Loop.
  while (!glfwWindowShouldClose(window)) {
    processInput(window);            // check and handle user input
    process_render_commands(window); // drawing on the screen happens here
    glfwPollEvents();                // checks for events and calls handlers
    glfwSwapBuffers(window);         // double buffering
  }

  glfwTerminate(); // free resources from GLFW
  return 0;
}

// =====================================================================================================================

