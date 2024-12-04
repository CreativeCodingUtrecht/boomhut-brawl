#pragma once

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_display.h"

#include "scene.hpp"
#include "globals.hpp"
#include "zoop.hpp"

// Sprites
#include "bn_sprite_items_snowflake.h"
#include "bn_sprite_items_snowflake_smol.h"
#include "bn_regular_bg_items_background.h"


namespace christmas
{
    next_scene run()
    {
        snow s;

        while (true) {
            s.draw_and_update();
            bn::core::update();
        }

        return next_scene::main_menu;
    }
}