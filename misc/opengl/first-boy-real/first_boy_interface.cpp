#include "first_boy.hpp"
#include "common/shader.hpp"

int main(void)
{
    // Window, camera, and objects
    GLFWwindow * window;
    struct object camera =
    {
        .position = vec4(0.f, 0.f, -4.f, 1.f),
        .direction = vec4(0.f, 0.f, 1.f, 0.f)
    };
    int num_objects = 2;
    struct object * object_list = new struct object[num_objects];
    GLfloat ** vertex_list = new GLfloat*[num_objects];
    object_list[0] =
    {
        .name = "Cube",
        .position = vec4(0.f, 0.f, 2.f, 1.f),
        .direction = vec4(0.f, 0.f, -1.f, 0.f),
        .num_vertices = 3 * 36
    };
    GLfloat cube_vertices[3 * 36] =
    {
        -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
        };
    vertex_list[0] = cube_vertices;

    object_list[1] =
    {
        .name = "Triangle",
        .position = vec4(1.f, 0.f, 0.f, 1.f),
        .direction = vec4(0.f, 0.f, -1.f, 0.f),
        .num_vertices = 3 * 12
    };
    GLfloat triangle_vertices[3 * 12] =
    {
        -3.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            -2.0f, 1.0f, 1.0f,
        };
    vertex_list[1] = triangle_vertices;


    // Setting cube and triangle colors (rainbow)
    GLfloat ** color_list = new GLfloat*[num_objects];
    color_list[0] = new GLfloat[object_list[0].num_vertices];
    color_list[1] = new GLfloat[object_list[1].num_vertices];

    for (int i = 0; i < 108; i++)
    {
        color_list[0][i] = vertex_list[0][i];
    }

    for (int i = 0; i < 9; i++)
    {
        color_list[1][i] = vertex_list[1][i];
    }


    // Normal axis
    vec3 normal_axis(0.f, 1.f, 0.f);


    // GLFW Startup
    GLuint VertexArrayID;
    int w_width = 1920, w_height = 1080;
    window = setup(w_width, w_height,
                   "Why are you like this?",
                   VertexArrayID, &camera,
                   object_list, num_objects);

    if (window == NULL)
    {
        glDeleteVertexArrays(1, &VertexArrayID);
        cleanup(
            window, num_objects,
            object_list, vertex_list,
            color_list);
        return -1;
    }


    // Setting loop settings
    //double time = glfwGetTime();
    glfwGetFramebufferSize(window, &w_width, &w_height);
    glViewport(0, 0, w_width, w_height);
    glfwSwapInterval(1);

    // Create and compile shaders
    const char * v_shader =
        "shaders/vertex_shader";
    const char * f_shader =
        "shaders/fragment_shader";
    GLuint programID =
        LoadShaders(v_shader,
                    f_shader);

    // Enable z-buffer and normal culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    // Create buffer arrays
    GLuint vertexbuffer;
    GLuint colorbuffer;
    //GLuint * vertex_buffers = new GLuint[num_objects];
    //GLuint * color_buffers = new GLuint[num_objects];

    // Bind cube and triangle stuff
    glGenBuffers(1, vertexbuffer);
    glGenBuffers(1, colorbuffer);
    //glGenBuffers(num_objects, vertex_buffers);
    //glGenBuffers(num_objects, color_buffers);

    for (int i = 0; i < num_objects; i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER,
                     vertexbuffer);
        //vertex_buffers[i]);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(vertexbuffer),
                     //sizeof(vertex_list[i]),
                     &vertexbuffer,
                     //vertex_list[i],
                     GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,
                     colorbuffer);
        //color_buffers[i]);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(color_list[i]),
                     color_list[i],
                     GL_STATIC_DRAW);
    }

    // Set mvp usage correct tranformations.
    GLuint MatrixID =
        glGetUniformLocation(
            programID,
            "MVP"
        );


    // Loop
    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT
                | GL_DEPTH_BUFFER_BIT);

        // Use the shader
        glUseProgram(programID);

        // Create object non-specific mats
        mat4 camera_mat = lookAt(
                              vec3(camera.position),
                              vec3(camera.position
                                   + camera.direction),
                              normal_axis
                          );

        mat4 projection_mat = perspective(
                                  radians(45.f),
                                  16.f / 9.f,
                                  0.1f,
                                  100.f
                              );

        // Draw per object
        for (int i = 0; i < num_objects; i++)
        {
            mat4 model_mat = translate(
                                 mat4(),
                                 vec3(object_list[i].position)
                             );

            mat4 mvp_mat = projection_mat
                           * camera_mat
                           * model_mat;

            glUniformMatrix4fv(
                MatrixID, 1,
                GL_FALSE,
                &mvp_mat[0][0]
            );

            // 1st attribute buffer: vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,
                         vertexbuffer);
            glVertexAttribPointer(0, 3,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  0, (void *)0);

            // 2nd attribute buffer: colors
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER,
                         colorbuffer);
            glVertexAttribPointer(1, 3,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  0, (void *)0);

            // Draw arrays
            glDrawArrays(GL_TRIANGLES, 0,
                         object_list[i].num_vertices);

        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        /*std::cout << "Position = " << to_string(camera.position) << std::endl << "Direction = " <<
                  to_string(camera.direction) << std::endl << std::endl;*/
    }
    while (!glfwWindowShouldClose(window));


    // Cleanup
    for (int i = 0; i < num_objects; i++)
    {
        glDeleteBuffers(1, &vertex_buffers[i]);
        glDeleteBuffers(1, &color_buffers[i]);
    }

    delete [] vertex_buffers;
    delete [] color_buffers;
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    cleanup(window, num_objects,
            object_list, vertex_list,
            color_list);
    exit(EXIT_SUCCESS);
}
