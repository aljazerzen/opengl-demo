#include "cube.hpp"
#include "init.hpp"
#include "math.hpp"

using namespace std;

unsigned frameCount = 0;

float cubeRotation = 0;
clock_t lastTime = 0;

Cube* cube;

void initialize(int argc, char* argv[]) {
  GLenum glewInitResult;

  glewInitResult = glewInit();

  if (GLEW_OK != glewInitResult) {
    fprintf(stderr, "ERROR: %s\n", glewGetErrorString(glewInitResult));
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

  // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  // glClearColor(0.9f, 0.4f, 0.4f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  exitOnGLError("ERROR: Could not set OpenGL depth testing options");

  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  // glFrontFace(GL_CCW);
  exitOnGLError("ERROR: Could not set OpenGL culling options");

  cube = new Cube();
}

int main(int argc, char* argv[]) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  initialize(argc, argv);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ++frameCount;

    clock_t now = clock();
    if (lastTime == 0)
      lastTime = now;

    cubeRotation += 180.0f * ((float)(now - lastTime) / CLOCKS_PER_SEC);
    lastTime = now;

    cube->draw(cubeRotation);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
}