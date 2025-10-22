#include <iostream>
#include <ostream>

#include "settings/Settings.h"
#include "controller/Controller.h"
#include "model/tools/Direction.h"
#include "logger/Logger.h"

int main() {
    Logger::setLogConfigFile("loggerConfig.config");
    LOG_INFO("TestLog", "testmsg!");
    LOG_DEBUG("AnotherTest", "HELLLOOOOOOW");
    // Controller ctrl(20 * TILE_SIZE, 14 * TILE_SIZE, "RaySnake");
    return 0;
}