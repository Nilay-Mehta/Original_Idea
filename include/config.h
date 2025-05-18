//
// Created by nilay on 15-05-2025.
//
#pragma once

#include <cstdint>

namespace Config {
    namespace Display {
        constexpr uint16_t  SCREEN_WIDTH = 1280;
        constexpr uint16_t  SCREEN_HEIGHT = 720;
        constexpr uint8_t   MAX_FPS = 60;
        constexpr bool      VSYNC_ENABLED = true;
        constexpr bool      FRAMERATE_LIMIT_ENABLED = false;
    }

    namespace Timing {
        constexpr float     MAX_DELTA_TIME = 0.25f;
    }

    namespace Player {
        constexpr float     PLAYER_SPEED = 500.f;
        constexpr float     RADIUS = 50.f;
    }
}