#include <stdio.h>
#include "../stb_image/stb_image.h"
#include "ramble.h"
#include "../utils.h"

Texture::Texture(const char *name, unsigned char *data, int width, int height)
    : name(name), width(width), height(height)
{
    /* Generate & bind texture */
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    /* Configure texture wrapping & filtering */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* Upload texture data */
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("%sERROR:%s Texture data is invalid! (%s)\n", ANSI_BOLD_RED, ANSI_RESET, name);
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    printf("Deleting texture... (%s)\n", name);
    glDeleteTextures(1, &handle);
}

void Texture::use(GLenum unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, handle);
}