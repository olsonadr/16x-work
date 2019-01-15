#include "first_boy.hpp"

GLFWwindow * window;

int main(void)
{
    // Startup
    GLuint VertexArrayID;
    int w_width = 2000, w_height = 1000;
    window = setup(w_width, w_height,
                   "Why are you like this?",
                   VertexArrayID);

    if (window == NULL)
    {
        getchar();
        cleanup(window);
        return -1;
    }

    // Loop
    //double time = glfwGetTime();
    glfwGetFramebufferSize(window, &w_width, &w_height);
    glViewport(0, 0, w_width, w_height);
    glfwSwapInterval(1);

    static const GLfloat g_vertex_buffer_data[] =
    {
        -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };
    GLuint vertexbuffer;
    glGenBuffers(1,
                 &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,
                 vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data,
                 GL_STATIC_DRAW);

    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw stuff!
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (!glfwWindowShouldClose(window));

    // Cleanup
    cleanup(window);
    exit(EXIT_SUCCESS);
}
