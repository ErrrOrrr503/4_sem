#ifndef CURSOR_H
#define CURSOR_H

#include <cmath>

enum cursor_type {
    plain,
    none
    //enum forbids equal enumenators for different enums? strange, errors could be given on type resolving when ambigious
};

class Cursor
{
public:
    Cursor();
    void set (float x_raw, float y_raw, float height, float width , float center_x, float center_y, float angle);
    void antirotate (float angle);
    cursor_type type;
    float cur_x;
    float cur_y;
    float pressed_x;
    float pressed_y;
    float pressed_x_raw;
    float pressed_y_raw;
};

#endif // CURSOR_H
