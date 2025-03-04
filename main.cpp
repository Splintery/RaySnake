#include "src/settings/Settings.hpp"
#include "src/controller/Controller.hpp"
#include "src/model/Direction.hpp"

int main() {
    Controller ctrl(20 * TILE_SIZE, 14 * TILE_SIZE, "RaySnake");
    return 0;
}