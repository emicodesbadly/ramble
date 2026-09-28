#include "ramble.h"
#include "../utils.h"

/* ======== SIMPLE RECT ======== */
Rect::Rect(vec2 position, vec2 size)
{
    this->position = position;
    this->size = size;
}

void Rect::render()
{
    
}

/* ======== TEXTURED RECT ======== */
TexturedRect::TexturedRect(vec2 position, Shader *shader, Texture *texture)
    : Rect(position, vec2(texture->width, texture->height))
{
    /* Vertex Data */
    float vertices[16] =
    {
        screen_to_gl_x(position.x),          screen_to_gl_y(position.y),            // Top Left
        screen_to_gl_x(position.x + size.x), screen_to_gl_y(position.y),            // Top Right
        screen_to_gl_x(position.x + size.x), screen_to_gl_y(position.y + size.y),   // Bottom Right
        screen_to_gl_x(position.x),          screen_to_gl_y(position.y + size.y),   // Bottom Left
        0.0f, 1.0f,    // UV - Top Left
        1.0f, 1.0f,    // UV - Top Right
        1.0f, 0.0f,    // UV - Bottom Right
        0.0f, 0.0f     // UV - Bottom Left
    };

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

void TexturedRect::render()
{
    glBindVertexArray(VAO);

    glLineWidth(1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}