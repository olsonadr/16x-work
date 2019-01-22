#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "common/shader.hpp"
using namespace glm;

GLFWwindow * setup(
    int, int, const char *,
    GLuint &, struct object *,
    struct object *, int);
void cleanup(
    GLFWwindow *, int,
    struct object *,
    GLfloat ** = nullptr,
    GLfloat ** = nullptr);
static void key_callback(
    GLFWwindow *, int,
    int, int, int);

struct object
{
    std::string name;
    vec4 position;
    vec4 direction;
    int num_vertices;
};
