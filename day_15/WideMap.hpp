#pragma once
#include "Map.hpp"

struct WideMap : public Map {
    WideMap(const Map &baseMap);
    void moveRobot() override;
};