#ifndef MATH_HPP
#define MATH_HPP
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

static const double PI = 3.14159265358979323846;

struct Vertex {
  float position[4];
  float color[4];
};

class Matrix {
 public:
  float m[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  Matrix product(const Matrix* m2);
  void rotateAboutX(float angle);
  void rotateAboutY(float angle);
  void rotateAboutZ(float angle);
  void scale(float x, float y, float z);
  void translate(float x, float y, float z);

  void print();
};

float cotangent(float angle);
float degreesToRadians(float degrees);
float radiansToDegrees(float radians);

Matrix createProjectionMatrix(float fovy, float aspect_ratio, float near_plane, float far_plane);

#endif