#include "ramble.h"

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
    this->shader = shader;
    this->texture = texture;

    float offset_x = remap(0, Canvas::instance()->width, -1.0f, 1.0f, position.x);
    float offset_y = remap(0, Canvas::instance()->height, 1.0f, -1.0f, position.y);

    float x = (size.x) / (Canvas::instance()->width);
    float y = (size.y) / (Canvas::instance()->height);

    /* Vertex Data */
    float vertices[16] =
    {
        offset_x,     offset_y,    // Top Left
        offset_x + x, offset_y,    // Top Right
        offset_x + x, offset_y - y,    // Bottom Right
        offset_x,     offset_y - y,    // Bottom Left
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
    shader->use();
    texture->use(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}