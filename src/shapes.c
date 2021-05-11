/*
mrfunkdude (c) 2021
fgl v1.0: shapes
Shapes functions implementation

Contents:
- pixel functions
- line functions
- triangle functions
- rectangle functions
- circle functions
*/

#include "fgl.h"

#include <GL/gl.h>      // shapes rendering
#include <math.h>       // sin(), cos()

// -------------------
// Implementations

// Draw a pixel
void fgl_draw_pixel(int x, int y, fgl_color color)
{
    glBegin(GL_POINTS);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2i(x, y);
    glEnd();
}

// Draw a line
void fgl_draw_line(int start_x, int start_y, int end_x, int end_y, fgl_color color)
{
    glBegin(GL_LINES);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2i(start_x, start_y);
        glVertex2i(end_x, end_y);
    glEnd();
}

// Draw a triangle
void fgl_draw_triangle(fgl_vec2d v1, fgl_vec2d v2, fgl_vec2d v3, fgl_color color)
{
    glBegin(GL_TRIANGLES);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2f(v1.x, v1.y);
        glVertex2f(v2.x, v2.y);
        glVertex2f(v3.x, v3.y);
    glEnd();
}

// Draw a rectangle
void fgl_draw_rectangle(int x, int y, int width, int height, fgl_color color)
{
    glBegin(GL_QUADS);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2i(x, y);                       // Top left vertex
        glVertex2i(x + width, y);               // Top right vertex
        glVertex2i(x + width, y + height);      // Bottom right vertex
        glVertex2i(x, y + height);              // Bottom left vertex
    glEnd();
}

// Draw outline of a rectangle
void fgl_draw_rectangle_outline(int x, int y, int width, int height, fgl_color color)
{
    glBegin(GL_LINE_LOOP);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2i(x, y);
        glVertex2i(x + width - 1, y);
        glVertex2i(x + width - 1, y + height - 1);
        glVertex2i(x, y + height - 1);
    glEnd();
}

// Draw a circle
void fgl_draw_circle(int x, int y, float radius, fgl_color color)
{
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    glBegin(GL_TRIANGLE_FAN);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2i(x, y);

        for (int i = 0; i <= 360; i++) {
            glVertex2f(x + sin(DEG2RAD*i) * radius, y + cos(DEG2RAD*i) * radius);
        }
    glEnd();
    
    glDisable(GL_POLYGON_SMOOTH);
}

// Draw outline of a circle
void fgl_draw_circle_outline(int x, int y, float radius, fgl_color color)
{
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glBegin(GL_LINE_LOOP);
        glColor4ub(color.r, color.g, color.b, color.a);
        glVertex2i(x, y);

        for (int i = 0; i <= 360; i++) {
            glVertex2f(x + sin(DEG2RAD*i) * radius, y + cos(DEG2RAD*i) * radius);
        }
    glEnd();
    
    glDisable(GL_LINE_SMOOTH);
}
