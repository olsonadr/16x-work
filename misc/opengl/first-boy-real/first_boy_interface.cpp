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
    int num_objects = 1;
    struct object * object_list = new struct object[num_objects];
    object_list[0] =
    {
        .position = vec4(0.f, 0.f, 2.f, 1.f),
        .direction = vec4(0.f, 0.f, -1.f, 0.f)
    };
    vec3 normal_axis(0.f, 1.f, 0.f);


    // Startup
    GLuint VertexArrayID;
    int w_width = 1920, w_height = 1080;
    window = setup(w_width, w_height,
                   "Why are you like this?",
                   VertexArrayID, &camera,
                   object_list, num_objects);

    if (window == NULL)
    {
        getchar();
        cleanup(window, object_list);
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


    // Setting vertices and buffers
    static const GLfloat g_vertex_buffer_data[] =
    {
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f, -1.0f, // triangle 2 : begin
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f, // triangle 2 : end
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
    static const GLfloat g_color_buffer_data[] =
    {
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f, -1.0f, // triangle 2 : begin
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f, // triangle 2 : end
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
    GLuint vertexbuffer;
    GLuint colorbuffer;
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,
                 vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,
                 colorbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data,
                 GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(g_color_buffer_data),
                 g_color_buffer_data,
                 GL_STATIC_DRAW);


    // Set mvp usage correct tranformations.
    GLuint MatrixID =
        glGetUniformLocation(
            programID,
            "MVP"
        );


    // Loop
    do
    {
        // Clear the screen and use shaders
        glClear(GL_COLOR_BUFFER_BIT
                | GL_DEPTH_BUFFER_BIT);


        // Use the shader
        glUseProgram(programID);


        // Generate mats
        for (int i = 0; i < num_objects; i++)
        {
            mat4 model_mat = mat4(1.f);

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

            mat4 mvp_mat = projection_mat
                           * camera_mat
                           * model_mat;

            glUniformMatrix4fv(
                MatrixID, 1,
                GL_FALSE,
                &mvp_mat[0][0]
            );
        }


        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,
                     vertexbuffer);
        glVertexAttribPointer(0, 3,
                              GL_FLOAT,
                              GL_FALSE,
                              0, (void *)0);

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,
                     colorbuffer);
        glVertexAttribPointer(1, 3,
                              GL_FLOAT,
                              GL_FALSE,
                              0, (void *)0);

        // Draw then close arrays
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);


        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (!glfwWindowShouldClose(window));


    // Cleanup
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    cleanup(window, object_list);
    exit(EXIT_SUCCESS);
}
