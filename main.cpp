#include "src/settings/Settings.hpp"
#include "src/controller/Controller.hpp"
#include "src/model/Direction.hpp"

int main() {
    Direction d = Direction::North;
    switch (d)
    {
    case Direction::South:
        printf("S\n");
        break;
    case Direction::North:
        printf("N\n");
        break;
    default:
        printf("E||W\n");
        break;
    }
    if ((int) d + (int) Direction::South == 0) {
        printf("YEAH\n");
    } else if (d == Direction::North) {
        printf("blabla\n");
    }
    Controller ctrl(20 * TILE_SIZE, 14 * TILE_SIZE, "RaySnake");
    return 0;
}