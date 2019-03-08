#include "init.hpp"

void exitOnGLError(const char* error_message) {
  const GLenum ErrorValue = glGetError();

  if (ErrorValue != GL_NO_ERROR) {
    fprintf(stderr, "%s: %s\n", error_message, gluErrorString(ErrorValue));
    exit(EXIT_FAILURE);
  }
}

ShaderProgram::ShaderProgram(const string vertexShader, const string fragmentShader) {
  vertexShaderId = loadShader("shaders/" + vertexShader, GL_VERTEX_SHADER, "vertex shader");
  fragmentShaderId = loadShader("shaders/" + fragmentShader, GL_FRAGMENT_SHADER, "fragment shader");

  programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  glUseProgram(programId);

  exitOnGLError("could not create shaders");
}

ShaderProgram::~ShaderProgram() {
  glUseProgram(0);

  glDetachShader(programId, vertexShaderId);
  glDetachShader(programId, fragmentShaderId);

  glDeleteShader(fragmentShaderId);
  glDeleteShader(vertexShaderId);

  glDeleteProgram(programId);

  exitOnGLError("could not destroy shaders");
}

GLuint ShaderProgram::loadShader(const string filename, GLenum shader_type, const char* shaderName) {
  ifstream file(filename, ifstream::binary | ifstream::ate);
  if (!file.is_open()) {
    cerr << "could not open file " << filename << endl;
    return 0;
  }

  long fileSize = file.tellg();

  file.seekg(0);

  if (fileSize < 0) {
    fprintf(stderr, "ERROR: Could not open file %s\n", filename);
    return 0;
  }

  string glslSource(fileSize, ' ');
  file.read(&glslSource[0], fileSize);

  GLuint shaderId = glCreateShader(shader_type);

  if (shaderId == 0) {
    fprintf(stderr, "ERROR: Could not create a shader.\n");
    return 0;
  }

  const GLchar* files[] = {glslSource.c_str()};
  GLint lengths[] = {(int)glslSource.size()};
  glShaderSource(shaderId, 1, files, lengths);
  glCompileShader(shaderId);
  exitOnError(shaderName, shaderId);
  return shaderId;
}

void ShaderProgram::exitOnError(const char* shaderName, int shaderId) {
  GLint val = GL_FALSE;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &val);

  if (val != GL_TRUE) {
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

    fprintf(stderr, "Could not compile %s: \n", shaderName);
    for (int i = 0; i < maxLength; i++) {
      fprintf(stderr, "%c", errorLog[i]);
    }
    exit(-1);
  }
}