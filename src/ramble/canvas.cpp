#include <stdio.h>
#include "ramble.h"
#include "../utils.h"

#define CANVAS_VERT "#version 330 core\nlayout (location = 0) in vec2 pos;\nlayout (location = 1) in vec2 uv;\nout vec2 uv;\nvoid main()\n{\n    gl_Position = vec4(a_pos.x, a_pos.y, 0.0f, 1.0);\n    uv = a_uv;\n}"
#define CANVAS_FRAG "#version 330 core\nin vec2 uv;\nuniform sampler2D main_tex;\nout vec4 FragColor;\nvoid main()\n{\n    FragColor = texture(main_tex, uv);\n}"

Canvas *Canvas::inst = nullptr;

Canvas::Canvas(unsigned int width, unsigned int height)
    : width(width), height(height), shader(new Shader("canvas", DEFAULT_TEXTURED_VERT, DEFAULT_TEXTURED_FRAG))
{
    printf("Initializing canvas...\n");

    /* Create & bind framebuffer */
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    /* Create & configure the render texture */
    glGenTextures(1, &render_texture);
    glBindTexture(GL_TEXTURE_2D, render_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)0);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    /* Attach the render texture */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_texture, 0);

    /* Check for framebuffer errors */
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("%sERROR:%s Canvas framebuffer is incomplete!\n", ANSI_BOLD_RED, ANSI_RESET);
    }

    /* Unbind framebuffer */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* Generate & bind vertex array */
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* Generate & bind vertex buffer */
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /* Upload vertex data to buffer */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Configure vertex attributes */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0); // vertex positions
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)(8 * sizeof(float))); // vertex UVs
    glEnableVertexAttribArray(1);

    /* Unbind vertex buffer & vertex array, to avoid unexpected behavior */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Canvas::~Canvas()
{
    glDeleteVertexArrays(1, &inst->VAO);
    glDeleteBuffers(1, &inst->VBO);

    glDeleteTextures(1, &inst->render_texture);

    glDeleteFramebuffers(1, &inst->FBO);

    delete inst->shader;

    printf("Canvas has been destroyed!\n");
}

void Canvas::init(unsigned int width, unsigned int height)
{
    if (inst != nullptr)
    {
        printf("Replacing canvas...\n");
        delete inst;
        inst = new Canvas(width, height);
    }
    else
    {
        inst = new Canvas(width, height);
    }
}

void Canvas::destroy()
{
    delete inst;
}

Canvas *Canvas::instance()
{
    if (inst == nullptr)
    {
        printf("%sERROR:%s Canvas has not been initialized, or has been destroyed!\n", ANSI_BOLD_RED, ANSI_RESET);
        return nullptr;
    }
    else
    {
        return inst;
    }
}

void Canvas::bind_and_clear()
{
    /* Bind FBO */
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    /* Change viewport to match */
    glViewport(0, 0, width, height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas::render(GLFWwindow *window)
{
    int win_w = 0;
    int win_h = 0;

    glfwGetFramebufferSize(window, &win_w, &win_h);

    /* Bind default framebuffer */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* Change viewport to match */
    glViewport(0, 0, win_w, win_h);

    /* Bind VAO */
    glBindVertexArray(VAO);

    /* Activate shader & texture */
    shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render_texture);

    /* Draw screen */
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Canvas::on_window_resized(int win_width, int win_height)
{
    /* Calculate new vertex positions */
    float self_aspect = aspect();
    float win_aspect = (float)win_width / win_height;

    if (win_aspect > self_aspect)
    {
        vertices[0] = -(1.0f / win_aspect) * self_aspect;
        vertices[1] = -1.0f;

        vertices[2] = -(1.0f / win_aspect) * self_aspect;
        vertices[3] =  1.0f;

        vertices[4] =  (1.0f / win_aspect) * self_aspect;
        vertices[5] =  1.0f;

        vertices[6] =  (1.0f / win_aspect) * self_aspect;
        vertices[7] = -1.0f;
    }
    else if (win_aspect < self_aspect)
    {
        vertices[0] = -1.0f;
        vertices[1] = -1.0f / self_aspect * win_aspect;

        vertices[2] = -1.0f;
        vertices[3] =  1.0f / self_aspect * win_aspect;

        vertices[4] =  1.0f;
        vertices[5] =  1.0f / self_aspect * win_aspect;

        vertices[6] =  1.0f;
        vertices[7] = -1.0f / self_aspect * win_aspect;
    }
    else
    {
        vertices[0] = -1.0f;
        vertices[1] = -1.0f;

        vertices[2] = -1.0f;
        vertices[3] =  1.0f;

        vertices[4] =  1.0f;
        vertices[5] =  1.0f;

        vertices[6] =  1.0f;
        vertices[7] = -1.0f;
    }

    /* Update vertex data buffer */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}