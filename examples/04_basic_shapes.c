#include "fgl.h"

int main()
{
    fgl_open_window(640, 480, "fgl example 04 - basic shapes");
    fgl_font fnt = fgl_load_font("res/font.ttf");

    while (!fgl_is_window_closed()) {
        fgl_start_drawing();
        fgl_set_background(FGL_WHITE);
        fgl_draw_text(fnt, "some shapes on fgl", 30, 10, 40, FGL_BLACK);
        fgl_draw_line(30, 50, 310, 50, FGL_BLACK);
        fgl_draw_rectangle(70, 70, 64, 64, FGL_RED);
        fgl_draw_triangle((fgl_vec2d){ 70, 210 }, (fgl_vec2d){ 134, 210 }, (fgl_vec2d){ 102, 150 }, FGL_YELLOW);
        fgl_draw_circle(100, 260, 40, FGL_GREEN);
        fgl_draw_rectangle_outline(210, 100, 128, 64, FGL_ORANGE);
        fgl_draw_circle_outline(260, 260, 70, FGL_BLUE);
        fgl_stop_drawing();
    }

    fgl_close_window();
    return 0;
}