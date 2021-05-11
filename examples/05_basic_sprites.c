#include "fgl.h"

int main()
{
    fgl_open_window(1024, 600, "fgl example 05 - basic sprite loading");
    fgl_font fnt = fgl_load_font("res/font.ttf");
    fgl_sprite spr = fgl_load_sprite("res/image.jpg");
    int speed = 5;
    int x = 20;
    int y = -230;

    while (!fgl_is_window_closed()) {
        // updating
        if (fgl_is_key_down(KEY_UP))
            y -= speed;
        if (fgl_is_key_down(KEY_LEFT))
            x -= speed;
        if (fgl_is_key_down(KEY_DOWN))
            y += speed;
        if (fgl_is_key_down(KEY_RIGHT))
            x += speed;

        // drawing
        fgl_start_drawing();
        fgl_set_background(FGL_WHITE);
        fgl_draw_text(fnt, "hello!", 30, 90, 40, FGL_BLACK);
        fgl_draw_sprite(spr, x, y, FGL_WHITE);
        fgl_draw_text(fnt, "native .jpg support!", 30, 10, 40, FGL_WHITE);
        fgl_draw_text(fnt, "use the arrow keys to move the sprite around", 30, 50, 40, FGL_WHITE);
        fgl_stop_drawing();
    }

    fgl_unload_sprite(spr);
    fgl_close_window();
    return 0;
}