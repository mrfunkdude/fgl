/*
mrfunkdude (c) 2021
fgl v1.0: core
Core functions implementation

Contents:
- window functions
- basic drawing functions
- input functions
- miscellaneous functions
*/

#if defined(_WIN32)
    #include "include/GLFW/glfw3.h"
#else
    #include <GLFW/glfw3.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fgl.h"

// ---------------------
// Module-specific functions and variables
static GLFWwindow *window;
static int current_key_state[512] = { 0 };
static int previous_key_state[512] = { 0 };
static int current_mouse_state[3] = { 0 };
static int previous_mouse_state[3] = { 0 };

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

static void setup_opengl()
{
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);   // black by default

    glEnable(GL_BLEND);     // enable color blending; required to work with transparencies
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   // reset the projection matrix
    glOrtho(0, fbWidth, fbHeight, 0, 0, 1);     // top left corner is 0,0

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   // reset the modelview matrix

    srand(time(NULL));  // seed the random number generator
}

// -------------------
// External functions
extern int load_text_environment();         // Load fontstash env
extern int unload_text_environment();       // Close fontstash env

// -------------------------
// Implementations

// Initialize OpenGL context
int fgl_open_window(int w, int h, const char *title)
{
    // check for glfw initialization
    if (!glfwInit()) {
        printf("GLFW ERROR: could not initialize GLFW properly\n");
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, false);

    // check for window initialization
    window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!window) {
        printf("GLFW ERROR: could not initialize window properly\n");
        glfwTerminate();
        return -2;
    }

    // callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // set up context
    setup_opengl();
    load_text_environment();
    printf("FGL INFO: created window successfully of %dx%d\n", w, h);

    return 0;
}

// Close the OpenGL context
void fgl_close_window()
{
    unload_text_environment();

    glfwDestroyWindow(window);
    glfwTerminate();
    printf("FGL INFO: closed window successfully\n");
}

// Check if the ESC key or close button is pressed
bool fgl_is_window_closed()
{
    return glfwWindowShouldClose(window);
}

/* Drawing functions */

// Clear appropiate buffers
void fgl_start_drawing()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

// Swap buffers and poll events
void fgl_stop_drawing()
{
    glfwSwapBuffers(window);
    glfwPollEvents();

    glFlush();
}

// Set background to a color
void fgl_set_background(fgl_color color)
{
    // Clamp values from 0.0 to 1.0
    float r = (float)color.r / 255;
    float g = (float)color.g / 255;
    float b = (float)color.b / 255;
    float a = (float)color.a / 255;
    glClearColor(r, g, b, a);
}

/* Input functions: keyboard */

// Check if a key is not being held down
bool fgl_is_key_up(int key)
{
    if (glfwGetKey(window, key) == GLFW_RELEASE) return true;
    else return false;
}

// Check if a key is held down
bool fgl_is_key_down(int key)
{
    if (glfwGetKey(window, key) == GLFW_PRESS) return true;
    else return false;
}

// Check if a key is pressed once
bool fgl_is_key_pressed(int key)
{
    bool res = false;

    current_key_state[key] = fgl_is_key_down(key);
    if (current_key_state[key] != previous_key_state[key]) {
        if (current_key_state[key])
            res = true;
        previous_key_state[key] = current_key_state[key];
    } else {
        res = false;
    }

    return res;
}

// Check if a key was released
bool fgl_is_key_released(int key)
{
    bool res = false;

    current_key_state[key] = fgl_is_key_up(key);
    if (current_key_state[key] != previous_key_state[key]) {
        if (current_key_state[key])
            res = true;
        previous_key_state[key] = current_key_state[key];
    } else {
        res = false;
    }

    return res;
}

/* Input functions: mouse */

// Check if a mouse button is not being held down
bool fgl_is_mouse_up(int button)
{
    if (glfwGetMouseButton(window, button) == GLFW_RELEASE) return true;
    else return false;
}

// Check if a mouse button is held down
bool fgl_is_mouse_down(int button)
{
    if (glfwGetMouseButton(window, button) == GLFW_PRESS) return true;
    else return false;
}

// Check if a mouse button is pressed once
bool fgl_is_mouse_pressed(int button)
{
    bool res = false;

    current_mouse_state[button] = fgl_is_mouse_down(button);
    if (current_mouse_state[button] != previous_mouse_state[button]) {
        if (current_mouse_state[button])
            res = true;
        previous_mouse_state[button] = current_mouse_state[button];
    } else {
        res = false;
    }

    return res;
}

// Check if a mouse button was released
bool fgl_is_mouse_released(int button)
{
    bool res = false;

    current_mouse_state[button] = fgl_is_mouse_up(button);
    if (current_mouse_state[button] != previous_mouse_state[button]) {
        if (current_mouse_state[button])
            res = true;
        previous_mouse_state[button] = current_mouse_state[button];
    } else {
        res = false;
    }

    return res;
}

// Returns mouse X
int fgl_get_mouse_x()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return (int)x;
}

// Returns mouse Y
int fgl_get_mouse_y()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return (int)y;
}

// Returns mouse position
fgl_vec2d fgl_get_mouse_pos()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return (fgl_vec2d){ x, y };
}

/* Miscellaneous functions */

// Return a random integer
int fgl_random_int(int min, int max)
{
    if (min > max) {
        int tmp = max;
        max = min;
        min = tmp;
    }
    
    return (rand()%(abs(max-min)+1) + min);
}