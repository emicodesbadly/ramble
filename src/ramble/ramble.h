#ifndef __H_RAMBLE_
#define __H_RAMBLE_

#include "../glad/glad.h"
#include <glm/glm.hpp>

using namespace glm;

class Shader final
{
    public:
        const char *name;

        Shader(const char *name, const char *vert_source, const char *frag_source);
        ~Shader();

        void use();

    private:
        unsigned int handle;
};

class Texture final
{
    public:
        const char *name;
        const int width, height;

        Texture(const char *name, unsigned char *data, int width, int height);
        ~Texture();

        void use(GLenum unit);

    private:
        unsigned int handle;
};

class Rect
{
    public:
        Rect(vec2 position, vec2 size);

        vec2 position;
        vec2 size;

        virtual void render();
};

class TexturedRect : Rect
{
    public:
        TexturedRect(vec2 position, Shader *shader, Texture *texture);
        ~TexturedRect();

        void render() override;

    private:
        unsigned int VBO;
        unsigned int VAO;
};

#endif