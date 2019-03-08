#include "math.hpp"

float cotangent(float angle) {
  return (float)(1.0 / tan(angle));
}

float degreesToRadians(float degrees) {
  return degrees * (float)(PI / 180);
}

float radiansToDegrees(float radians) {
  return radians * (float)(180 / PI);
}

Matrix Matrix::product(const Matrix* m2) {
  Matrix* m1 = this;
  Matrix out = {};

  for (unsigned int row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
    for (unsigned int column = 0; column < 4; ++column)
      out.m[row_offset + column] = (m1->m[row_offset + 0] * m2->m[column + 0]) + (m1->m[row_offset + 1] * m2->m[column + 4]) +
                                   (m1->m[row_offset + 2] * m2->m[column + 8]) + (m1->m[row_offset + 3] * m2->m[column + 12]);

  return out;
}

void Matrix::scale(float x, float y, float z) {
  Matrix scale;

  scale.m[0] = x;
  scale.m[5] = y;
  scale.m[10] = z;

  memcpy(m, this->product(&scale).m, sizeof(m));
}

void Matrix::translate(float x, float y, float z) {
  Matrix translation;

  translation.m[12] = x;
  translation.m[13] = y;
  translation.m[14] = z;

  memcpy(m, this->product(&translation).m, sizeof(m));
}

void Matrix::rotateAboutX(float angle) {
  Matrix rotation;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[5] = cosine;
  rotation.m[6] = -sine;
  rotation.m[9] = sine;
  rotation.m[10] = cosine;

  memcpy(m, this->product(&rotation).m, sizeof(m));
}

void Matrix::rotateAboutY(float angle) {
  Matrix rotation;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[0] = cosine;
  rotation.m[8] = sine;
  rotation.m[2] = -sine;
  rotation.m[10] = cosine;

  memcpy(m, this->product(&rotation).m, sizeof(m));
}

void Matrix::rotateAboutZ(float angle) {
  Matrix rotation;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[0] = cosine;
  rotation.m[1] = -sine;
  rotation.m[4] = sine;
  rotation.m[5] = cosine;

  memcpy(m, this->product(&rotation).m, sizeof(m));
}

void Matrix::print() {
  printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11],
         m[12], m[13], m[14], m[15]);
}

Matrix createProjectionMatrix(float fovy, float aspect_ratio, float near_plane, float far_plane) {
  Matrix out = {};

  const float y_scale = cotangent(degreesToRadians(fovy / 2)), x_scale = y_scale / aspect_ratio, frustum_length = far_plane - near_plane;

  out.m[0] = x_scale;
  out.m[5] = y_scale;
  out.m[10] = -((far_plane + near_plane) / frustum_length);
  out.m[11] = -1;
  out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

  return out;
}
