#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

GLFWwindow * setup(int, int, const char *, GLuint &);
void cleanup(GLFWwindow *);
static void key_callback(GLFWwindow *, int, int, int, int);
