#include "fgl.h"

int main()
{
    fgl_open_window(1024, 600, "fgl example 06 - basic text");
    fgl_font fnt = fgl_load_font("res/font.ttf");
    fgl_font fnt2 = fgl_load_font("res/font2.ttf");
    int val1 = fgl_random_int(-3, 9);
    int val2 = 0;
    int frames_count = 0;
    fgl_color color = (fgl_color){ fgl_random_int(0, 255), fgl_random_int(0, 255), fgl_random_int(0, 255), 255 };

    while (!fgl_is_window_closed()) {
        // updating contents
        frames_count++;
        if (frames_count >= 90) {
            frames_count = 0;
            val1 = fgl_random_int(-3, 9);
            color = (fgl_color){ fgl_random_int(0, 255), fgl_random_int(0, 255), fgl_random_int(0, 255), 255 };
        }

        val2++;

        // drawing
        fgl_start_drawing();
        fgl_set_background(FGL_WHITE);
        fgl_draw_text(fnt, "dealing with text", 10, 10, 30, FGL_DARKGRAY);
        fgl_draw_text(fnt, "this is a normal text, and it can have any font previously specified (ttf only)", 10, 40, 30, FGL_DARKGRAY);
        fgl_draw_text(fnt2, "quite 8-bit, isn't it?", 10, 70, 30, color);
        fgl_draw_text(fnt, fgl_format_text("you can also have values updating: %d", val2), 10, 110, 30, FGL_DARKGRAY);
        fgl_draw_text(fnt, fgl_format_text("and random values: %d", val1), 10, 140, 30, FGL_DARKGRAY);
        fgl_draw_text(fnt, "with colorful texts as well", 40, 200, 80, color);
        fgl_draw_text(fnt, "and big texts!", 40, 400, 120, FGL_BLACK);
        fgl_stop_drawing();
    }

    fgl_close_window();
    return 0;
}