#include "settings/Settings.hpp"
#include "controller/Controller.hpp"
#include "model/Direction.hpp"

int main() {
    Controller ctrl(20 * TILE_SIZE, 14 * TILE_SIZE, "RaySnake");
    return 0;
}