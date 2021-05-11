/*
mrfunkdude (c) 2021
fgl v1.0: text
Text functions implementation

Contents:
- loading fonts
- drawing text
- embedding variables to a renderable text
*/

#include "fgl.h"
#include <stdio.h>
#include <stdarg.h>     // va_list, va_start(), vsprintf(), va_end()
#include <GL/gl.h>

#define FONTSTASH_IMPLEMENTATION
#include "external/fontstash.h"

#define GLFONTSTASH_IMPLEMENTATION
#include "external/glfontstash.h"

#define MAX_BUFFERS         4
#define BUFFER_LEN       1024

// -------------------
// Module-specific functions and variables
extern int load_text_environment();         // Load fontstash env
extern int unload_text_environment();       // Close fontstash env
static FONScontext *fs = NULL;

// -------------------
// Implementations

// Load a font into memory
int fgl_load_font(const char *path)
{
    int fn = FONS_INVALID;
    fn = fonsAddFont(fs, "font", path);
    if (fn == FONS_INVALID) {
        printf("FGL ERROR: could not load font. Maybe check path?\n");
    }

    printf("FGL INFO: loaded font from %s properly\n", path);

    return fn;
}

// Draw a piece of text
void fgl_draw_text(fgl_font font, const char *text, int x, int y, float size, fgl_color color)
{
    unsigned int c = glfonsRGBA(color.r, color.g, color.b, color.a);

    fonsClearState(fs);
    fonsSetFont(fs, font);

    fonsSetSize(fs, size);
    fonsSetColor(fs, c);
    fonsDrawText(fs, x, y+size-6, text, NULL);
}

// Embed variables to a text
const char *fgl_format_text(const char *text, ...)
{
    char buffers[MAX_BUFFERS][BUFFER_LEN] = { 0 };
    int index = 0;

    char *current_buffer = buffers[index];
    memset(current_buffer, 0, MAX_BUFFERS); // clear buffers before

    va_list args;
    va_start(args, text);
    vsnprintf(current_buffer, BUFFER_LEN, text, args);
    va_end(args);

    index++;
    if (index >= MAX_BUFFERS) {
        index = 0;
    }

    return current_buffer;
}

// -------------------
// Load fontstash env
extern int load_text_environment()
{
    fs = glfonsCreate(512, 512, FONS_ZERO_TOPLEFT);
    if (fs == NULL) {
        printf("FGL ERROR: could not create fontstash.\n");
        return -1;
    }

    printf("FGL INFO: loaded text environment properly\n");
}

// Close fontstash env
extern int unload_text_environment()
{
    glfonsDelete(fs);
    printf("FGL INFO: unloaded text environment properly\n");
}