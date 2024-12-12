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
        // Make the player animate but don't respond to
        (*winner)->set_preview_mode(true);

        bn::fixed scale = 1;
        bn::fixed fade = 0;
        int frame = 0;

        // Get the background palette
        bn::color icy = rgb255(133, 168, 253);
        bn::bg_palette_ptr pal = background->palette();
        pal.set_fade_color(icy);


        while(true)
        {
            frame++;
            
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


            if (bn::keypad::start_pressed() || bn::keypad::select_pressed()) {
                background.reset();
                printer->print(bn::string<20>(""));
                return next_scene::splash;
            }

            bn::core::update();
        }

    }
}
