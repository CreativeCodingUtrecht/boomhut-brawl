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
#include "bn_sprite_items_presents_text.h"

#include "bn_sprite_items_press_to_start.h"
#include "bn_sprite_items_to_start.h"


// 'Boomhut Brawl' title text
#include "bn_sprite_items_titel_1.h"
#include "bn_sprite_items_titel_2.h"
#include "bn_sprite_items_titel_3.h"
#include "bn_sprite_items_titel_4.h"
#include "bn_sprite_items_titel_5.h"
#include "bn_sprite_items_titel_6.h"
#include "bn_sprite_items_titel_7.h"
#include "bn_sprite_items_titel_8.h"
#include "bn_sprite_items_titel_9.h"
#include "bn_sprite_items_titel_10.h"


#include "bn_music_items.h"
#include "bn_sound_items.h"

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
        // sprite_ptr c1 = sprite_items::c.create_sprite(-64,-128);
        // sprite_ptr c2 = sprite_items::c2.create_sprite(0,-128);
        // sprite_ptr u = sprite_items::u.create_sprite(64,-128);

        // Presents text
        // sprite_ptr presents_text = sprite_items::presents_text.create_sprite(0, -128);
        // presents_text.set_camera(*camera);

        // bn::music_items::getready_compat.play();
        // bn::music::set_volume(0.5);

        // Boomhut brawl text
        int title_x = 250;
        int title_y = 10;
        sprite_ptr titel_sprites[] = {
            sprite_items::titel_1.create_sprite(title_x + -95, title_y),
            sprite_items::titel_2.create_sprite(title_x + -80, title_y),
            sprite_items::titel_2.create_sprite(title_x + -65, title_y),
            sprite_items::titel_3.create_sprite(title_x + -48, title_y),
            sprite_items::titel_4.create_sprite(title_x + -28, title_y),
            sprite_items::titel_5.create_sprite(title_x + -13, title_y),
            sprite_items::titel_6.create_sprite(title_x + 0, title_y),

            sprite_items::titel_1.create_sprite(title_x + 24, title_y),
            sprite_items::titel_7.create_sprite(title_x + 40, title_y),
            sprite_items::titel_8.create_sprite(title_x + 58, title_y),
            sprite_items::titel_9.create_sprite(title_x + 76, title_y),
            sprite_items::titel_10.create_sprite(title_x + 90, title_y),
        };
        
        for (auto s : titel_sprites) {
            s.set_camera(*camera);
        }

        // press to start
        bool start_showing_press_to_start = false;
        sprite_ptr press_a = sprite_items::press_to_start.create_sprite(title_x - 24, title_y + 110);
        sprite_ptr to_start = sprite_items::to_start.create_sprite(title_x + 24, title_y + 110);
        press_a.set_camera(*camera);
        to_start.set_camera(*camera);


        // Background
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
                } else {
                    start_showing_press_to_start = true;
                }
            }

            // Boomhut pan upwards

            // Title waviness
            for (size_t i = 0; i < 12; i++) {
                titel_sprites[i].set_y(title_y + sin(bn::fixed(t) / 100 + bn::fixed(i) / 12) * 5.0);
            }

            // Press a to start
            bool show_press_to_start = start_showing_press_to_start && t % 60 < 30;
            press_a.set_visible(show_press_to_start);
            to_start.set_visible(show_press_to_start);
    


            // CCU logo --------------------------------
            // C
            // if (t < exit_base) {
            //     c1.set_y(lerp(0, c1.y(), .9));
            // }
            // if (t > exit_base) {
            //     c1.set_y(lerp(128, c1.y(), .9));
            // }

            // // C
            // if (t > entrance_stagger && t < exit_base) {
            //     c2.set_y(lerp(0, c2.y(), .9));
            // }
            // if (t > exit_base + exit_stagger) {
            //     c2.set_y(lerp(128, c2.y(), .9));
            // }

            // // U
            // if (t > entrance_stagger * 2 && t < exit_base) {
            //     u.set_y(lerp(0, u.y(), .9));
            // }
            // if (t > exit_base + exit_stagger * 2) {
            //     u.set_y(lerp(128, u.y(), .9));
            // }

            // // presents text
            // if (t > 5 * 60 && t < 6 * 60) {
            //     presents_text.set_y(lerp(camera->y(), presents_text.y(), .9));
            // }
            // if (t > 6 * 60 && t < 7 * 60) {
            //     presents_text.set_y(lerp(camera->y() + 128, presents_text.y(), .9));
            // }

            // BN_LOG(the_train.position.x());

            // finished, go to main menu 
            if (t == 16 * 60) {
                
            }

            if (t > 60 && bn::keypad::a_pressed() ||bn::keypad::start_pressed()) {
                music::stop();
                background.reset();
                return next_scene::character_select;
            }

            core::update(); 
        }

    }
}










