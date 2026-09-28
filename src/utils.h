#ifndef __H_UTILS_
#define __H_UTILS_

/*
 * These are NOT all of the ANSI color codes. All high-intensity colors are missing,
 * because I am too lazy to add them.
 */

/* REGULAR COLORS */
#define ANSI_BLACK  "\e[0;30m"
#define ANSI_RED    "\e[0;31m"
#define ANSI_GREEN  "\e[0;32m"
#define ANSI_YELLOW "\e[0;33m"
#define ANSI_BLUE   "\e[0;34m"
#define ANSI_PURPLE "\e[0;35m"
#define ANSI_CYAN   "\e[0;36m"
#define ANSI_WHITE  "\e[0;37m"

/* BOLD COLORS  */
#define ANSI_BOLD_BLACK  "\e[1;30m"
#define ANSI_BOLD_RED    "\e[1;31m"
#define ANSI_BOLD_GREEN  "\e[1;32m"
#define ANSI_BOLD_YELLOW "\e[1;33m"
#define ANSI_BOLD_BLUE   "\e[1;34m"
#define ANSI_BOLD_PURPLE "\e[1;35m"
#define ANSI_BOLD_CYAN   "\e[1;36m"
#define ANSI_BOLD_WHITE  "\e[1;37m"

/* UNDERLINE COLORS */
#define ANSI_UNDERLINE_BLACK  "\e[2;30m"
#define ANSI_UNDERLINE_RED    "\e[2;31m"
#define ANSI_UNDERLINE_GREEN  "\e[2;32m"
#define ANSI_UNDERLINE_YELLOW "\e[2;33m"
#define ANSI_UNDERLINE_BLUE   "\e[2;34m"
#define ANSI_UNDERLINE_PURPLE "\e[2;35m"
#define ANSI_UNDERLINE_CYAN   "\e[2;36m"
#define ANSI_UNDERLINE_WHITE  "\e[2;37m"

/* BACKGROUND COLORS */
#define ANSI_BACKGROUND_BLACK  "\e[40m"
#define ANSI_BACKGROUND_RED    "\e[41m"
#define ANSI_BACKGROUND_GREEN  "\e[42m"
#define ANSI_BACKGROUND_YELLOW "\e[43m"
#define ANSI_BACKGROUND_BLUE   "\e[44m"
#define ANSI_BACKGROUND_PURPLE "\e[45m"
#define ANSI_BACKGROUND_CYAN   "\e[46m"
#define ANSI_BACKGROUND_WHITE  "\e[47m"

#define ANSI_RESET "\e[0m"

#define DEFAULT_VERT "#version 330 core\nlayout (location = 0) in vec2 pos;\nvoid main()\n{\n    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);\n}"
#define DEFAULT_FRAG "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\n    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n}"

#define DEFAULT_TEXTURED_VERT "#version 330 core\nlayout (location = 0) in vec2 pos;\nlayout (location = 1) in vec2 uv;\nout vec2 f_uv;\nvoid main()\n{\n    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0);\n    f_uv = uv;\n}"
#define DEFAULT_TEXTURED_FRAG "#version 330 core\nin vec2 f_uv;\nuniform sampler2D main_tex;\nout vec4 FragColor;\nvoid main()\n{\n    FragColor = texture(main_tex, f_uv);\n}"

#define screen_to_gl_x(x) 2.0f * (x) - 1.0f
#define screen_to_gl_y(y) 1.0f - 2.0f * (y)

#define gl_to_screen_x(x) ((x) + 1.0f) / 2.0f
#define gl_to_screen_y(y) (1.0f - (y)) / 2.0f

#endif