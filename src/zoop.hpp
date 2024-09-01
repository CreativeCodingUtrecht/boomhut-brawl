#pragma once

#include "bn_core.h"
#include "bn_point.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"
#include "bn_keypad.h"
#include "bn_regular_bg_map_item.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_builder.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_log.h"
#include "bn_vector.h"

#include "bn_sprite_items_bee.h"
#include "bn_sprite_items_rat.h"

#include "globals.hpp"


using namespace bn;




namespace zoop
{
    struct rat
    {
        sprite_ptr sprite = sprite_items::rat.create_sprite(244,186);    
        
        rat() 
        {
            sprite.set_camera(camera);
        }

        void update()
        {

        }
    };


    struct bee
    {
        sprite_ptr sprite = sprite_items::bee.create_sprite(0,20);    
        sprite_animate_action<2> anim = bn::create_sprite_animate_action_forever(sprite, 1, sprite_items::bee.tiles_item(), 0, 1);

        bee() 
        {
            sprite.set_camera(camera);
        }

        void update()
        {
            anim.update();
            sprite.set_x(sprite.x() + global_random->get_fixed(-1.0, 1.0));
            sprite.set_y(sprite.x() + global_random->get_fixed(-1.0, 1.0));
        }
    };

}