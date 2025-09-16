#include <iostream>
#include <ostream>

#include "settings/Settings.h"
#include "controller/Controller.h"
#include "model/tools/Direction.h"

#ifdef DEBUG_VERSION
#define TEST(x) std::cout << x << std::endl;
#endif

int main() {

    TEST("yoooooooooo");
    
    // Controller ctrl(20 * TILE_SIZE, 14 * TILE_SIZE, "RaySnake");
    return 0;
}