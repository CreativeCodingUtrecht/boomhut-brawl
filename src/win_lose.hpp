#pragma once

#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_format.h"
#include "bn_log.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_bg_palettes.h"
#include "bn_bg_palette_ptr.h"

#include "globals.hpp"
#include "scene.hpp"
#include "./characters/-character.hpp"

#include "bn_sound_items.h"


namespace win_lose
{
    next_scene run() 
    {
        // Play winner's sound
        (*winner)->sound_win().play();
        printer->print(bn::format<20>("{} wins", (*winner)->name()));

        // TODO Print "press a to restart"

        // Make the player animate but don't respond to input 
        (*winner)->set_preview_mode(true);

        bn::fixed scale = 1;
        bn::fixed fade = 0;
        int frame = 0;

        // Get the background palette
        if (!background.has_value()) {
            background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
            background->set_z_order(4);
            background->set_camera(*camera);
        }

        bn::color icy = rgb255(133, 168, 253);
        bn::bg_palette_ptr pal = background->palette();
        pal.set_fade_color(icy);


        while(true)
        {
            frame++;

            if (frame == 120) {
                (*winner)->sound_tagline().play();
            }

            global_snow->draw_and_update();
            
            camera_follow_smooth(*camera, (*winner)->sprite_ptr()->position());
            multiplayer::keypad_data keypad_data_to_send = multiplayer::read_keys();

            // Always update own player
            (*winner)->update(frame, keypad_data_to_send.keypad_data);

            // Move the camera to the player
            camera_follow_smooth(*camera, (*winner)->sprite_ptr()->position() + bn::fixed_point(0, 10));

            // Make the player bigger
            scale = lerp(scale, 2, 0.125);
            (*winner)->sprite_ptr()->set_scale(scale);

            // Fade the background
            fade = lerp(fade, 1, 0.125);
            pal.set_fade_intensity(fade);


            if (frame > 2*60 && bn::keypad::a_pressed()) {
                background.reset();
                // you->sprite_ptr().reset();
                // other_player->sprite_ptr().reset();
                you->unload();
                other_player->unload();
                
                // other_player->sprite_ptr()->set_visible(false);
                printer->clear();
                
                return next_scene::splash;
            }

            bn::core::update();
        }

    }
}
