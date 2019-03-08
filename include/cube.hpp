#ifndef CUBE_HPP
#define CUBE_HPP
#include "math.hpp"
#include "init.hpp"

class Cube {
 private:
  ShaderProgram *shaderProgram;
  GLuint vaoId;
  GLuint bufferIds[2];

  GLuint modelMatrixUniformLocation;
  GLuint viewMatrixUniformLocation;
  GLuint projectionMatrixUniformLocation;

  Matrix viewMatrix;
  Matrix projectionMatrix;

 public:
  Cube();
  ~Cube();

  void draw(float rotation);
};

#endif