#pragma once

#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_format.h"
#include "bn_log.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"


#include "globals.hpp"
#include "scene.hpp"

#include "bn_sound_items.h"


namespace win_lose
{

    next_scene run() 
    {
        while(true) 
        {   
            t++;

            bn::core::update();
        }

    }
}










