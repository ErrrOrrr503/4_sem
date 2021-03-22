#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <cmath>

enum edit_mode {
    sel,
    draw
};

struct wall {
    float a1[4]; // x y zlow zhigh
    float a2[4];
    float color[3];
};

class Level
{
public:
    Level();
    void select_wall (float x, float y);

    std::vector<wall> level;
    wall selected_wall;
    const float level_x = 10000;
    const float level_y = 10000;
    const float cell_size = 50;
private:
};

#endif // LEVEL_H
