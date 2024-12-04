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
        (*winner)->sound_win().play();
        printer->print(bn::format<20>("{} wins", (*winner)->name()));

        (*winner)->set_preview_mode(true);

        (*winner)->sprite_ptr()->set_scale(2);

        bn::fixed scale = 1;
        bn::fixed fade = 0;
        int frame = 0;
//
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
//            camera_follow_smooth(*camera, (*winner)->sprite_ptr()->position());
            camera_follow_smooth(*camera, (*winner)->sprite_ptr()->position() + bn::fixed_point(0, 10));

            scale = lerp(scale, 2, 0.125);
            (*winner)->sprite_ptr()->set_scale(scale);
//
            fade = lerp(fade, 1, 0.125);
            pal.set_fade_intensity(fade);


            if (bn::keypad::start_pressed() || bn::keypad::select_pressed()) {
                background.reset();
//                pal.set_fade_intensity(0);
//                delete *winner;
                printer->print(bn::string<20>(""));
                return next_scene::splash;
            }

            bn::core::update();
        }

    }
}
