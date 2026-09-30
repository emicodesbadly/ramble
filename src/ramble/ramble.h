#ifndef __H_RAMBLE_
#define __H_RAMBLE_

#include <stdio.h>
#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../utils.h"

using namespace glm;

class Shader final
{
    public:
        const char *name;

        Shader(const char *name, const char *vert_source, const char *frag_source);
        ~Shader();

        void use() const;

    private:
        unsigned int handle;
};

class Texture final
{
    public:
        const char *name;
        const int width, height;

        Texture(const char *name, unsigned char *data, int width, int height, int channel_count);
        ~Texture();

        void use(GLenum unit);

    private:
        unsigned int handle;
};

class Canvas final
{
    public:
        const unsigned int width, height;
        float aspect() { return (float)width / height; }

        Canvas(const Canvas&) = delete;
        Canvas& operator=(const Canvas) = delete;

        static void init(unsigned int width, unsigned int height);
        static void destroy();

        static Canvas *instance();

        void bind_and_clear();
        void render(GLFWwindow *window);

        void on_window_resized(int win_width, int win_height);

    private:
        static Canvas *inst;

        float vertices[16] =
        {
            -1.0f, -1.0f, // Bottom left
            -1.0f,  1.0f, // Top left
             1.0f,  1.0f, // Top right
             1.0f, -1.0f, // Bottom right
             0.0f,  0.0f, // UV - Bottom left
             0.0f,  1.0f, // UV - Top left
             1.0f,  1.0f, // UV - Top right
             1.0f,  0.0f  // UV - Bottom right
        };

        unsigned int VBO;
        unsigned int VAO;
        unsigned int FBO;
        unsigned int render_texture;

        const Shader *shader;

        Canvas(unsigned int width, unsigned int height);
        ~Canvas();
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

        Shader *shader;
        Texture *texture;
};

#endif