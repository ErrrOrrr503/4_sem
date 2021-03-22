#include "level.h"

Level::Level()
{

}

void Level::select_wall (float x, float y)
{
    const float delta = 10;
    if (x - round (x / cell_size) * cell_size < delta && x - round (x / cell_size) * cell_size > - delta) {
        selected_wall.a1[0] = selected_wall.a2[0] = round (x / cell_size) * cell_size;
        selected_wall.a1[1] = floor (y / cell_size) * cell_size;
        selected_wall.a2[1] = (floor (y / cell_size) + 1) * cell_size;
    }
    if (y - round (y / cell_size) * cell_size < delta && y - round (y / cell_size) * cell_size > - delta) {
        selected_wall.a1[1] = selected_wall.a2[1] = round (y / cell_size) * cell_size;
        selected_wall.a1[0] = floor (x / cell_size) * cell_size;
        selected_wall.a2[0] = (floor (x / cell_size) + 1) * cell_size;
    }
}
