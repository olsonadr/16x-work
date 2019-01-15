#include "first_boy.hpp"


/*
** Creates and returns a window, setting it as the context
**	as well, checks for error in window creation.
*/
GLFWwindow * setup(
    int w_width,
    int w_height,
    const char * title,
    GLuint & VertexArrayID)
{
    // Initialize glfw
    if (!glfwInit())
    {
        std::cout << "glfw did not initialize!" << std::endl;
        return nullptr;
    }

    // Tweakables
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window, set context, and init GLEW
    GLFWwindow * window = glfwCreateWindow(w_width, w_height, title, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Window failed to initialize!" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW!" << std::endl;
        return nullptr;
    }

    // Background color
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Set arrays
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glfwSetKeyCallback(window, key_callback);

    // Return
    return window;
}


/*
** Destroys the window passed and terminates glfw.
*/
void cleanup(
    GLFWwindow * window)
{
    if (window != nullptr)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}


/*
** Defines the key-bindings through GLFW.
*/
static void key_callback(
    GLFWwindow * window,
    int key,
    int scancode,
    int action,
    int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
