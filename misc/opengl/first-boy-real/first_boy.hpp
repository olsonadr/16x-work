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
    GLFWwindow *, struct object *);

static void key_callback(
    GLFWwindow *, int,
    int, int, int);

mat4 get_model_mat(
    struct object);


struct object
{
    vec4 position;
    vec4 direction;
};
