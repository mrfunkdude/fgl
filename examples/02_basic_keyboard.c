#include "fgl.h"

int main()
{
    fgl_open_window(1024, 600, "fgl example 02 - basic keyboard input");
    fgl_font fnt = fgl_load_font("res/font.ttf");
    fgl_rec rec = (fgl_rec){ 1024/2, 600/2, 64, 64 };
    int mode = 0;

    while (!fgl_is_window_closed()) {
        // updating square movement
        if (fgl_is_key_down(KEY_W))
            rec.y -= 4;
        if (fgl_is_key_down(KEY_A))
            rec.x -= 4;       
        if (fgl_is_key_down(KEY_S))
            rec.y += 4;
        if (fgl_is_key_down(KEY_D))
            rec.x += 4;
        
        if (fgl_is_key_pressed(KEY_SPACE)) {
            mode++;

            if (mode > 1) {
                mode = 0;
            }
        }

        fgl_start_drawing();
        fgl_set_background(FGL_WHITE);
        mode == 0 ? fgl_draw_rectangle(rec.x, rec.y, rec.w, rec.h, FGL_RED) : fgl_draw_rectangle_outline(rec.x, rec.y, rec.w, rec.h, FGL_RED);
        fgl_draw_text(fnt, "press the wasd keys to move the block around", 10, 10, 30, FGL_DARKGRAY);
        fgl_draw_text(fnt, "press space to see the outline of the block", 10, 50, 30, FGL_DARKGRAY);
        fgl_stop_drawing();
    }

    fgl_close_window();
    return 0;
}