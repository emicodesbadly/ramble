#ifndef __H_RAMBLE_
#define __H_RAMBLE_

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

class Rect
{
    public:
        Rect(vec2 position, vec2 size);

        vec2 position;
        vec2 size;

        virtual void render();

    private:
        unsigned int VBO;
        unsigned int VAO;
};

#endif