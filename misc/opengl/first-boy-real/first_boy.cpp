#include "first_boy.hpp"

struct object * camera_ptr;
struct object * objects;
int num_objects;
vec3 normal_axis(0.f, 1.f, 0.f);
float step_size = 1;

/*
** Creates and returns a window, setting it as the context
**	as well, checks for error in window creation.
*/
GLFWwindow * setup(
    int w_width,
    int w_height,
    const char * title,
    GLuint & VertexArrayID,
    struct object * camera_passed,
    struct object * objects_passed,
    int num_objects_passed)
{
    // Global intitializations
    camera_ptr = camera_passed;

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
    glClearColor(0.0f, 0.0f, 0.23f, 0.0f);

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
    GLFWwindow * window,
    struct object * object_list)
{
    if (window != nullptr)
    {
        glfwDestroyWindow(window);
    }

    delete object_list;
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
    if (key != -1)
    {
        mat4 pos_change = mat4(1.f);
        mat4 dir_change = mat4(1.f);
	float degrees;

        if (key == GLFW_KEY_ESCAPE
                && action == GLFW_PRESS)

        {
            glfwSetWindowShouldClose(
                window, GLFW_TRUE
            );
        }
        else if (key == GLFW_KEY_W
                 && (action == GLFW_PRESS
                     || action == GLFW_REPEAT))
        {
            pos_change =
                translate(
                    mat4(1.f),
                    step_size * vec3((*camera_ptr).direction)
                ); //* pos_change;
        }
        else if (key == GLFW_KEY_S
                 && (action == GLFW_PRESS
                     || action == GLFW_REPEAT))
        {
            pos_change =
                translate(
                    mat4(1.f),
                    step_size * vec3((-1.f * (*camera_ptr).direction))
                ); //* pos_change;
        }
	else if (key == GLFW_KEY_A
		&& (action == GLFW_PRESS
		    || action == GLFW_REPEAT))
	{
	    vec3 left = rotate(
		    radians(90.f),
		    normal_axis
		    ) * (*camera_ptr).direction;
            pos_change =
                translate(
                    mat4(1.f),
                    step_size * left
                ); //* pos_change;
	}	
	else if (key == GLFW_KEY_D
		&& (action == GLFW_PRESS
		    || action == GLFW_REPEAT))
	{	
	    vec3 right = rotate(
		    radians(-90.f),
		    normal_axis
		    ) * (*camera_ptr).direction;
            pos_change =
                translate(
                    mat4(1.f),
                    step_size * right
                ); //* pos_change;
	}
        else if (key == GLFW_KEY_R
                 && action == GLFW_PRESS)
        {
            (*camera_ptr)
            .position =
                vec4(0.f, 0.f, -4.f, 1.f);
            (*camera_ptr).direction =
                vec4(0.f, 0.f, 1.f, 0.f);
        }
        else if (key == GLFW_KEY_Q
                 && (action == GLFW_PRESS
                     || action == GLFW_REPEAT))
        {
	    if (mods == GLFW_MOD_SHIFT) {
		degrees = 90.f;
	    } else {
		degrees = 7.f;
	    }
            dir_change =
                rotate(
                    radians(degrees),
                    normal_axis
                );
        }
        else if (key == GLFW_KEY_E
                 && (action == GLFW_PRESS
                     || action == GLFW_REPEAT))
        {
	    if (mods == GLFW_MOD_SHIFT) {
		degrees = -90.f;
	    } else {
		degrees = -7.f;
	    }
            dir_change =
                rotate(
                    radians(degrees),
                    normal_axis
                ); //* dir_change;
        }


        (*camera_ptr).position =
            pos_change * (*camera_ptr).position;
        (*camera_ptr).direction =
            dir_change * (*camera_ptr).direction;
    }
}


/*
** Returns the mat4 model matrix for an object
*/
/*
 *mat4 get_model_mat(
 *        struct object passed_object)
 *{
 *    mat4 translation = translate(
 *            mat4(),
 *            vec3(passed_object.position));
 *}
 */
