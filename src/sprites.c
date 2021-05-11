/*
mrfunkdude (c) 2021
fgl v1.0: sprites
Sprites functions implementation

Contents:
- loading/unloading functions
- drawing functions
*/

#include "fgl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"     // image loading
#include <stdio.h>                  // printf()
#include <GL/gl.h>

// -------------------
// Implementations

// Load a sprite into memory
fgl_sprite fgl_load_sprite(const char *path)
{
    fgl_sprite sprite;
    int width, height, bpp;

    // Loading image
    unsigned char *data = stbi_load(path, &width, &height, &bpp, 4);

    if (data == NULL) {
        printf("FGL ERROR: failed to load sprite. Maybe check path?\n");
    }

    // Convert loaded data into OpenGL texture
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // Set texture to repeat on the x-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // Set texture to repeat on the y-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Filter for pixel-perfect drawing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // Filter for pixel-perfect drawing

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Once loaded into VRAM, we can unload the loaded data
    stbi_image_free(data);
    sprite.ID = id;
    sprite.width = width;
    sprite.height = height;

    printf("FGL INFO: generated sprite of ID %d, Size %dx%d\n", sprite.ID, sprite.width, sprite.height);
    return sprite;
}

// Unload a sprite
void fgl_unload_sprite(fgl_sprite sprite)
{
    glDeleteTextures(1, &sprite.ID);
    printf("FGL INFO: unloaded sprite of ID %d\n", sprite.ID);
}

// Draw a sprite
void fgl_draw_sprite(fgl_sprite sprite, int x, int y, fgl_color tint)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sprite.ID);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(1.0, 1.0, 1.0f);
        glRotatef(0.0, 0, 0, 1.0f);

        // Define texture coordinates in a rectangle
        glBegin(GL_QUADS);
            glColor4ub(tint.r, tint.g, tint.b, tint.a);
            glNormal3f(0.0f, 0.0f, 1.0f);                                           // Pointing towards viewer
            glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);                       // Bottom-left corner of texture and quad
            glTexCoord2f(1.0f, 0.0f); glVertex2f(sprite.width, 0.0f);               // Bottom-right corner of texture and quad
            glTexCoord2f(1.0f, 1.0f); glVertex2f(sprite.width, sprite.height);      // Top-right corner of texture and quad
            glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, sprite.height);              // Top-left corner of texture and quad
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);   // disable textures usage
}
