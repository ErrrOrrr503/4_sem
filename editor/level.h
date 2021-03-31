#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <cmath>
#include <QObject>
#include <fstream>
#include "level_common.h"

enum edit_mode {
    sel,
    draw
};

struct wall {
    float a1[4]; // x y zlow zhigh
    float a2[4];
    float color[3];
};

class Level : public QObject
{
    Q_OBJECT //just for using signal to access console
public:
    Level();
    void select_wall (float x, float y);
    void add_wall ();
    void delete_wall (wall wall);
    int save_level (std::ofstream &outfile);
    int load_level (std::ifstream &infile);

    std::vector<wall> walls;
    wall selected_wall;
    const float level_x = 1000;
    const float level_y = 1000;
    const float cell_size = 50;
private:
    int wall_is_present (wall wall);
signals:
    void print_console (const std::string &s);
};

#endif // LEVEL_H
