#pragma once

#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_format.h"
#include "bn_log.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"


#include "globals.hpp"
#include "scene.hpp"
#include "./characters/-character.hpp"

#include "bn_sound_items.h"


namespace win_lose
{

    next_scene run() 
    {
        (*winner)->sound_win().play();

        printer->print(bn::format<20>("{} wins", (*winner)->name()));

        while(true) 
        {
            camera_follow_smooth(*camera, (*winner)->sprite_ptr()->position());

            if (bn::keypad::start_pressed() || bn::keypad::select_pressed()) {
                background.reset();
                return next_scene::character_select;
            }

            bn::core::update();
        }

    }
}










