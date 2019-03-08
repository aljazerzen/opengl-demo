#ifndef INIT_HPP
#define INIT_HPP

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class ShaderProgram {
 private:
  int vertexShaderId;
  int fragmentShaderId;

  void exitOnError(const char* shaderName, int shaderId);
  GLuint loadShader(const string filename, GLenum shader_type, const char* shaderName);

 public:
  int programId;

  ShaderProgram(const string vertexShader, const string fragmentShader);
  ~ShaderProgram();
};

void exitOnGLError(const char* error_message);
GLuint loadShader(const string filename, GLenum shader_type);

#endif