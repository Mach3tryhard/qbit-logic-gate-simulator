#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "manager.h"


int main() {
    manager::getInstance().Run();
    return 0;
}
