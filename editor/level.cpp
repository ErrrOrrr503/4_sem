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

void Level::add_wall ()
{
    if (!wall_is_present (selected_wall))
        walls.push_back(selected_wall);
}

int Level::wall_is_present (wall wall)
{
    for (size_t i = 0; i < walls.size (); i++) {
        if (walls[i].a1[0] == wall.a1[0] && walls[i].a1[1] == wall.a1[1] &&
            walls[i].a2[0] == wall.a2[0] && walls[i].a2[1] == wall.a2[1])
            return 1;
    }
    return 0;
}

void Level::save_level (std::ofstream &outfile)
{
    level_fileheader fileheader;
    fileheader.walls_addr = sizeof (level_fileheader);
    fileheader.walls_size = sizeof (wall) * walls.size ();
    outfile.write ((char *) &fileheader, sizeof (level_fileheader));
    outfile.write ((char *) &walls[0], fileheader.walls_size);
    outfile.flush ();
    emit print_console ("Level saved. Header: " + std::to_string (sizeof (level_fileheader)) +
                        " bytes. Walls: " + std::to_string (fileheader.walls_size) + " bytes.");
}
