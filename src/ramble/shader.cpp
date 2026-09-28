#include <stdio.h>
#include "ramble.h"
#include "../utils.h"

Shader::Shader(const char *name, const char *vert_source, const char *frag_source) : name(name)
{
    /* Create & compile vertex shader */
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vert_source, 0);
    glCompileShader(vert);

    int success;
    char log[512];

    /* Check for vertex shader compilation errors */
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vert, 512, 0, log);
        printf("%sERROR:%s Shader compilation failed! (%s, vertex)\n%s\n", ANSI_BOLD_RED, ANSI_RESET, name, log);

        //valid = false;
    }

    /* Create & compile fragment shader */
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &frag_source, 0);
    glCompileShader(frag);

    /* Check for fragment shader compilation errors */
    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag, 512, 0, log);
        printf("%sERROR:%s Shader compilation failed! (%s, fragment)\n%s\n", ANSI_BOLD_RED, ANSI_RESET, name, log);

        //valid = false;
    }

    /* Link shaders */
    handle = glCreateProgram();
    glAttachShader(handle, vert);
    glAttachShader(handle, frag);
    glLinkProgram(handle);

    /* Check for linking errors */
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(handle, 512, 0, log);
        printf("%sERROR:%s Shader linking failed! (%s)\n%s\n", ANSI_BOLD_RED, ANSI_RESET, name, log);

        //valid = false;
    }

    /* Cleanup */
    glDeleteShader(vert);
    glDeleteShader(frag);
}

Shader::~Shader()
{
    printf("Deleting shader... (%s)\n", name);
    glDeleteProgram(handle);
}

void Shader::use()
{
    glUseProgram(handle);
}