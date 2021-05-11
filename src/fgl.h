/*
FGL - public domain graphics library (and possibly game library...)
made by mrfunkdude v1.0

Funky Graphics Library

-- What can it do?
- Create windows
- Draw shapes
- Draw sprites
- Render text

-- Example application
#include "fgl.h"

int main()
{
    fgl_open_window(1024, 600, "fgl example 01 - basic window");
    fgl_font fnt = fgl_load_font("res/font.ttf");

    while (!fgl_is_window_closed) {
        fgl_start_drawing();
        fgl_set_background(FGL_WHITE);
        fgl_draw_text(fnt, "hello fgl", 1024/2, 600/2, 40, FGL_BLACK);
        fgl_stop_drawing();
    }

    fgl_close_window();
    return 0;
}

-- Licensed under zlib
*/

#ifndef FGL_H
#define FGL_H

#include <stdbool.h>	// boolean type

// ------- Types --------
typedef struct fgl_color {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} fgl_color;

typedef struct fgl_vec2d {
    float x, y;
} fgl_vec2d;

typedef struct fgl_rec {
    float x, y;
    int w, h;
} fgl_rec;

typedef struct fgl_circle {
    int x, y;
    float radius;
} fgl_circle;

typedef struct fgl_sprite {
    unsigned int ID;
    int width, height;
} fgl_sprite;

typedef unsigned char byte;
typedef int fgl_font;

enum {
    KEY_NULL            = 0,
    // Alphanumeric keys
    KEY_APOSTROPHE      = 39,
    KEY_COMMA           = 44,
    KEY_MINUS           = 45,
    KEY_PERIOD          = 46,
    KEY_SLASH           = 47,
    KEY_ZERO            = 48,
    KEY_ONE             = 49,
    KEY_TWO             = 50,
    KEY_THREE           = 51,
    KEY_FOUR            = 52,
    KEY_FIVE            = 53,
    KEY_SIX             = 54,
    KEY_SEVEN           = 55,
    KEY_EIGHT           = 56,
    KEY_NINE            = 57,
    KEY_SEMICOLON       = 59,
    KEY_EQUAL           = 61,
    KEY_A               = 65,
    KEY_B               = 66,
    KEY_C               = 67,
    KEY_D               = 68,
    KEY_E               = 69,
    KEY_F               = 70,
    KEY_G               = 71,
    KEY_H               = 72,
    KEY_I               = 73,
    KEY_J               = 74,
    KEY_K               = 75,
    KEY_L               = 76,
    KEY_M               = 77,
    KEY_N               = 78,
    KEY_O               = 79,
    KEY_P               = 80,
    KEY_Q               = 81,
    KEY_R               = 82,
    KEY_S               = 83,
    KEY_T               = 84,
    KEY_U               = 85,
    KEY_V               = 86,
    KEY_W               = 87,
    KEY_X               = 88,
    KEY_Y               = 89,
    KEY_Z               = 90,

    // Function keys
    KEY_SPACE           = 32,
    KEY_ESCAPE          = 256,
    KEY_ENTER           = 257,
    KEY_TAB             = 258,
    KEY_BACKSPACE       = 259,
    KEY_INSERT          = 260,
    KEY_DELETE          = 261,
    KEY_RIGHT           = 262,
    KEY_LEFT            = 263,
    KEY_DOWN            = 264,
    KEY_UP              = 265,
    KEY_PAGE_UP         = 266,
    KEY_PAGE_DOWN       = 267,
    KEY_HOME            = 268,
    KEY_END             = 269,
    KEY_CAPS_LOCK       = 280,
    KEY_SCROLL_LOCK     = 281,
    KEY_NUM_LOCK        = 282,
    KEY_PRINT_SCREEN    = 283,
    KEY_PAUSE           = 284,
    KEY_F1              = 290,
    KEY_F2              = 291,
    KEY_F3              = 292,
    KEY_F4              = 293,
    KEY_F5              = 294,
    KEY_F6              = 295,
    KEY_F7              = 296,
    KEY_F8              = 297,
    KEY_F9              = 298,
    KEY_F10             = 299,
    KEY_F11             = 300,
    KEY_F12             = 301,
    KEY_LEFT_SHIFT      = 340,
    KEY_LEFT_CONTROL    = 341,
    KEY_LEFT_ALT        = 342,
    KEY_LEFT_SUPER      = 343,
    KEY_RIGHT_SHIFT     = 344,
    KEY_RIGHT_CONTROL   = 345,
    KEY_RIGHT_ALT       = 346,
    KEY_RIGHT_SUPER     = 347,
    KEY_KB_MENU         = 348,
    KEY_LEFT_BRACKET    = 91,
    KEY_BACKSLASH       = 92,
    KEY_RIGHT_BRACKET   = 93,
    KEY_GRAVE           = 96,
};

enum {
    MOUSE_LEFT = 0,
    MOUSE_RIGHT,
    MOUSE_MIDDLE
};

// ------- Defines and macros -
#define FGL_WHITE           (fgl_color){ 255, 255, 255, 255 }
#define FGL_BLACK           (fgl_color){ 0, 0, 0, 255       }
#define FGL_DARKGRAY        (fgl_color){ 68, 68, 68, 255 }
#define FGL_GRAY            (fgl_color){ 128, 128, 128, 255 }
#define FGL_LIGHTGRAY       (fgl_color){ 192, 192, 192, 255 }

#define FGL_RED             (fgl_color){ 255, 50, 100, 255  }
#define FGL_ORANGE          (fgl_color){ 255, 153, 51, 255  }
#define FGL_YELLOW          (fgl_color){ 255, 201, 90, 255  }
#define FGL_GREEN           (fgl_color){ 102, 255, 102, 255 }
#define FGL_BLUE            (fgl_color){ 0, 128, 255, 255   }
#define FGL_PURPLE          (fgl_color){ 178, 102, 255, 255 }
#define FGL_PINK            (fgl_color){ 255, 204, 255, 255 }
#define FGL_MAGENTA         (fgl_color){ 255, 102, 255, 255 }

#define PI 3.14159265358979323846
#define DEG2RAD (PI / 180.0)
#define RAD2DEG (180.0 / PI)

// Functions declarations

// ------ Core -------
// Window functions
int fgl_open_window(int w, int h, const char *title);                                               // Initialize OpenGL context
void fgl_close_window();                                                                            // Close the OpenGL context
bool fgl_is_window_closed();                                                                        // Check if the ESC key or close button is pressed

// Drawing functions
void fgl_start_drawing();                                                                           // Clear buffers
void fgl_stop_drawing();                                                                            // Swap buffers and poll events
void fgl_set_background(fgl_color color);                                                           // Clear the background color to a certain color

// Keyboard functions
bool fgl_is_key_up(int key);                                                                        // Check if a key is up (not held)
bool fgl_is_key_down(int key);                                                                      // Check if a key is held
bool fgl_is_key_pressed(int key);                                                                   // Check if a key is pressed once
bool fgl_is_key_released(int key);                                                                  // Check if a key is released

// Mouse functions
bool fgl_is_mouse_up(int button);                                                                   // Check if a mouse button is not being held
bool fgl_is_mouse_down(int button);                                                                 // Check if a mouse button is being held
bool fgl_is_mouse_pressed(int button);                                                              // Check if a mouse button is pressed once
bool fgl_is_mouse_released(int button);                                                             // Check if a mouse button is released
int fgl_get_mouse_x();                                                                              // Returns mouse x position
int fgl_get_mouse_y();                                                                              // Returns mouse y position
fgl_vec2d fgl_get_mouse_pos();                                                                      // Returns mouse position

// Misc. functions
int fgl_random_int(int min, int max);                                                               // Returns a random integer

// ------ Shapes -------
void fgl_draw_pixel(int x, int y, fgl_color color);                                                 // Draw a single pixel
void fgl_draw_triangle(fgl_vec2d v1, fgl_vec2d v2, fgl_vec2d v3, fgl_color color);                  // Draw a triangle
void fgl_draw_line(int start_x, int start_y, int end_x, int end_y, fgl_color color);                // Draw a line
void fgl_draw_rectangle(int x, int y, int w, int h, fgl_color color);                               // Draw a rectangle
void fgl_draw_rectangle_outline(int x, int y, int width, int height, fgl_color color);              // Draw outline of a rectangle
void fgl_draw_circle(int x, int y, float radius, fgl_color color);                                  // Draw a circle
void fgl_draw_circle_outline(int x, int y, float radius, fgl_color color);                          // Draw outline of a circle

// ------ Sprites -------
fgl_sprite fgl_load_sprite(const char *path);                                                       // Load a sprite into memory
void fgl_unload_sprite(fgl_sprite sprite);                                                          // Unload a sprite
void fgl_draw_sprite(fgl_sprite sprite, int x, int y, fgl_color tint);                              // Draw a sprite

// ------ Text -------
int fgl_load_font(const char *path);                                                                // Load font from path
void fgl_draw_text(fgl_font font, const char *text, int x, int y, float size, fgl_color color);  // Draw a piece of text
const char *fgl_format_text(const char *text, ...);                                                  // Formatting of text with variables to embed


#endif  // FGL_H