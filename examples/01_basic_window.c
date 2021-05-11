#include "fgl.h"

int main()
{
    fgl_open_window(1024, 600, "fgl example 01 - basic window");
    fgl_font fnt = fgl_load_font("res/font.ttf");

    while (!fgl_is_window_closed()) {
        fgl_start_drawing();
        fgl_set_background(FGL_WHITE);
        fgl_draw_text(fnt, "hello fgl!", 40, 40, 30, FGL_DARKGRAY);
        fgl_stop_drawing();
    }

    fgl_close_window();
    return 0;
}