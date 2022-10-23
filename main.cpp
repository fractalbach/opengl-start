#include <glad/glad.h> // Must be included before GLFW

#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// =====================================================================================================================

#include "build/shaders/simple.frag.hex"  
#include "build/shaders/simple.vert.hex"

const char *SHADER_SOURCE_FRAG = (const char*)shaders_simple_frag;
const char *SHADER_SOURCE_VERT = (const char*)shaders_simple_vert;

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

// Updates the size of the GL viewport to the current size of the window. Call whenever the window size changes.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

// Handle Keypresses, mouseclicks, and other forms of direct input from the user.
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void check_for_shader_errors(unsigned int shader_id) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success); // check for any errors in our shader compilation
  if (!success) {
    glGetShaderInfoLog(shader_id, 512, NULL, infoLog); // provides useful compile-time error information
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void check_for_shader_program_errors(unsigned int shader_program_id) {
  int success;
  char infoLog[512];
  glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program_id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER_PROGRAM::\n" << infoLog << std::endl;
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

  // Load Vertex Shader
  unsigned int vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);              // create an empty shader object and save the ID
  glShaderSource(vertex_shader, 1, &SHADER_SOURCE_VERT, NULL); // loads the shader source code
  glCompileShader(vertex_shader);                                // dynamically compiles the shader source code
  check_for_shader_errors(vertex_shader);

  // Load Fragment Shader
  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &SHADER_SOURCE_FRAG, NULL);
  glCompileShader(fragment_shader);
  check_for_shader_errors(fragment_shader);

  // Combine the vertex and fragment shaders into a "shader program"
  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  check_for_shader_program_errors(shader_program);
  glDeleteShader(vertex_shader); // we can free these objects since we have finished linking to "shader program
  glDeleteShader(fragment_shader);

  // Handle Vertices
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);              // generate a openGL buffer object, and save the ID
  glBindVertexArray(VAO);             // 1. bind Vertex Array Object
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2. copy vert array into a buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 3. set vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // The Render Loop.
  while (!glfwWindowShouldClose(window)) {
    processInput(window); // check and handle user input

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // specify color to fill the screen with
    glClear(GL_COLOR_BUFFER_BIT);         // clears entire framebuffer, fills with desired color

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();        // checks for events and calls handlers
    glfwSwapBuffers(window); // double buffering
  }

  glfwTerminate(); // free resources from GLFW
  return 0;
}

// =====================================================================================================================
