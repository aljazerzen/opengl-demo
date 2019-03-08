#include "cube.hpp"

Cube::Cube() {
  viewMatrix.translate(0, 0, -2);

  const Vertex VERTICES[8] = {
    {{-.5f, -.5f, .5f, 1}, {0.5, 0, 0, 1}},
    {{-.5f, .5f, .5f, 1}, {0, 0, 0, 1}},    
    {{.5f, .5f, .5f, 1}, {0, 0, 0, 1}},
    {{.5f, -.5f, .5f, 1}, {0.5, 0, 0, 1}},
    {{-.5f, -.5f, -.5f, 1}, {1, 0, 0, 1}},
    {{-.5f, .5f, -.5f, 1}, {0, 0, 0, 1}},
    {{.5f, .5f, -.5f, 1}, {0, 0, 0, 1}},
    {{.5f, -.5f, -.5f, 1}, {0, 0, 0, 1}}};

  const GLuint INDICES[36] = {0, 2, 1, 0, 3, 2, 4, 3, 0, 4, 7, 3, 4, 1, 5, 4, 0, 1, 3, 6, 2, 3, 7, 6, 1, 6, 5, 1, 2, 6, 7, 5, 6, 7, 4, 5};

  shaderProgram = new ShaderProgram("simple-shader.vertex.glsl", "simple-shader.fragment.glsl");

  glLinkProgram(shaderProgram->programId);
  exitOnGLError("ERROR: Could not link the shader program");

  modelMatrixUniformLocation = glGetUniformLocation(shaderProgram->programId, "ModelMatrix");
  viewMatrixUniformLocation = glGetUniformLocation(shaderProgram->programId, "ViewMatrix");
  projectionMatrixUniformLocation = glGetUniformLocation(shaderProgram->programId, "ProjectionMatrix");
  exitOnGLError("ERROR: Could not get the shader uniform locations");

  projectionMatrix = createProjectionMatrix(60, (float)640 / 480, 1.0f, 100.0f);
  glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, projectionMatrix.m);

  glGenBuffers(2, bufferIds);
  exitOnGLError("ERROR: Could not generate the buffer objects");

  glGenVertexArrays(1, &vaoId);
  exitOnGLError("ERROR: Could not generate the VAO");
  glBindVertexArray(vaoId);
  exitOnGLError("ERROR: Could not bind the VAO");

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  exitOnGLError("ERROR: Could not enable vertex attributes");

  glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
  exitOnGLError("ERROR: Could not bind the VBO to the VAO");

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)sizeof(VERTICES[0].position));
  exitOnGLError("ERROR: Could not set VAO attributes");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);
  exitOnGLError("ERROR: Could not bind the IBO to the VAO");

  glBindVertexArray(0);
}

Cube::~Cube() {
  delete shaderProgram;

  glDeleteBuffers(2, &bufferIds[0]);
  glDeleteVertexArrays(1, &vaoId);
  exitOnGLError("ERROR: Could not destroy the buffer objects");
}

void Cube::draw(float rotation) {
  Matrix modelMatrix;
  modelMatrix.rotateAboutZ(PI * 0.25);
  modelMatrix.rotateAboutX(atan(1 / sqrt(2)));
  modelMatrix.rotateAboutY(rotation);

  glUseProgram(shaderProgram->programId);
  exitOnGLError("ERROR: Could not use the shader program");

  glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, modelMatrix.m);
  glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, viewMatrix.m);
  exitOnGLError("ERROR: Could not set the shader uniforms");

  glBindVertexArray(vaoId);
  exitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
  exitOnGLError("ERROR: Could not draw the cube");

  glBindVertexArray(0);
  glUseProgram(0);
}