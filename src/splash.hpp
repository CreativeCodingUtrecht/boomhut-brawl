#pragma once

#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_format.h"
#include "bn_log.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_bg_palette_ptr.h"

#include "bn_sprite_items_lipje.h"
#include "bn_sprite_items_c.h"
#include "bn_sprite_items_c2.h"
#include "bn_sprite_items_u.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_sprite_items_presents_text.h"

#include "globals.hpp"
#include "scene.hpp"
#include "zoop.hpp"
#include "snow.hpp"
#include "train.hpp"


namespace splash 
{
    using namespace bn;



    next_scene run() 
    {
        // CCU logo
        sprite_ptr c1 = sprite_items::c.create_sprite(-64,-128);
        sprite_ptr c2 = sprite_items::c2.create_sprite(0,-128);
        sprite_ptr u = sprite_items::u.create_sprite(64,-128);

        // Presents text
        sprite_ptr presents_text = sprite_items::presents_text.create_sprite(0, -128);
        presents_text.set_camera(*camera);

        // Backround
        background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
        background->set_z_order(4);
        background->set_camera(*camera);

        // Palette fade
        bn::color icy = rgb255(133, 168, 253);
        bn::bg_palette_ptr pal = background->palette();
        pal.set_fade_color(icy);
        bn::fixed fade = 1;

        // Train
        train the_train;

        // music_items::splashscreen.play();
        int t = 0;
        
        int entrance_stagger = 10;
        int exit_base = 90;
        int exit_stagger = 10;

        camera->set_x(250);
        camera->set_y(500);

        while(true) 
        {   
            t++;

            global_snow->draw_and_update();
            the_train.update();


            // Fade background in
            fade = lerp(fade, 0, 0.02);
            pal.set_fade_intensity(fade);

            // Cutscene upwards
            if (t > 2 * 60) {
                if (camera->y() > 50) {
                    camera->set_y(camera->y() - 1);
                }
            }

            // Boomhut pan upwards

            // CCU logo --------------------------------
            // C
            if (t < exit_base) {
                c1.set_y(lerp(0, c1.y(), .9));
            }
            if (t > exit_base) {
                c1.set_y(lerp(128, c1.y(), .9));
            }

            // C
            if (t > entrance_stagger && t < exit_base) {
                c2.set_y(lerp(0, c2.y(), .9));
            }
            if (t > exit_base + exit_stagger) {
                c2.set_y(lerp(128, c2.y(), .9));
            }

            // U
            if (t > entrance_stagger * 2 && t < exit_base) {
                u.set_y(lerp(0, u.y(), .9));
            }
            if (t > exit_base + exit_stagger * 2) {
                u.set_y(lerp(128, u.y(), .9));
            }

            // presents text
            if (t > 5 * 60 && t < 6 * 60) {
                presents_text.set_y(lerp(camera->y(), presents_text.y(), .9));
            }
            if (t > 6 * 60 && t < 7 * 60) {
                presents_text.set_y(lerp(camera->y() + 128, presents_text.y(), .9));
            }

            // finished, go to main menu 
            if (t == 12 * 60) {
                // music::stop();
                background.reset();
                return next_scene::character_select;
            }

            core::update(); 
        }

    }
}










