#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

#include "defs.h"
#include "logger.h"
#include "entity.h"
#include "scene.h"
#include "scenemanager.h"
#include "components.h"
#include "app.h"
#include <random>

#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <concepts>

class Random {
private:
    inline static std::random_device rd;
    inline static std::mt19937 gen{rd()};

public:
    Random() = delete;
    template <typename T>
    static T Range(T min, T max) {
        std::uniform_real_distribution<T> distrib(min, max);
        return distrib(gen);
    }
};