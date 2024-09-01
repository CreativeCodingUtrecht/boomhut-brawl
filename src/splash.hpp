#pragma once

#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_format.h"
#include "bn_log.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"


#include "bn_sprite_items_lipje.h"
#include "bn_sprite_items_c.h"
#include "bn_sprite_items_c2.h"
#include "bn_sprite_items_u.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"


#include "globals.hpp"
#include "scene.hpp"



namespace splash 
{
    using namespace bn;


    next_scene run() 
    {
        // CCU logo
        sprite_ptr c1 = sprite_items::c.create_sprite(-64,-128);
        sprite_ptr c2 = sprite_items::c2.create_sprite(0,-128);
        sprite_ptr u = sprite_items::u.create_sprite(64,-128);

        // music_items::splashscreen.play();


        int t = 0;
        
        int entrance_stagger = 10;
        int exit_base = 90;
        int exit_stagger = 10;

        while(true) 
        {   
            t++;


            // c1
            if (t < exit_base) {
                c1.set_y(lerp(0, c1.y(), .9));
            }
            if (t > exit_base) {
                c1.set_y(lerp(128, c1.y(), .9));
            }

            // c2
            if (t > entrance_stagger && t < exit_base) {
                c2.set_y(lerp(0, c2.y(), .9));
            }
            if (t > exit_base + exit_stagger) {
                c2.set_y(lerp(128, c2.y(), .9));
            }

            // c3
            if (t > entrance_stagger * 2 && t < exit_base) {
                u.set_y(lerp(0, u.y(), .9));
            }
            if (t > exit_base + exit_stagger * 2) {
                u.set_y(lerp(128, u.y(), .9));
            }

            // finished, go to main menu 
            if (t == 3 * 60) {
                music::stop();
                return next_scene::main_menu;
            }

            core::update(); 
        }

    }
}










