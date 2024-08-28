#pragma once

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_palette_actions.h"

#include "globals.h"
#include "scene.h"

#include "bn_sprite_items_menu_platforming.h"
#include "bn_sprite_items_menu_selector.h"
// #include "bn_sprite_items_c.h"
// #include "bn_sprite_items_c2.h"
// #include "bn_sprite_items_u.h"

#include "bn_regular_bg_items_menu_bg.h"
#include "bn_sound_items.h"
#include "multiplayer.h"
#include "bn_link.h"
#include "bn_link_state.h"


// Font 
#include "../../common/include/common_fixed_8x16_sprite_font.h"

// Backgrounds
#include "bn_regular_bg_items_character_select_screen.h"

// Sprites
#include "bn_sprite_items_pictogram_selector_you.h"
#include "bn_sprite_items_pictogram_selector_other_player.h"
#include "bn_sprite_items_rein_pictogram.h"

// Characters
#include "./characters/-character.h"
#include "./characters/cate.h"
#include "./characters/christine.h"
#include "./characters/fabian.h"
#include "./characters/fleur.h"
#include "./characters/hunter.h"
#include "./characters/joost.h"
#include "./characters/laury.h"
#include "./characters/mar.h"
#include "./characters/networkninja.h"
#include "./characters/rein.h"
#include "./characters/saskia.h"
#include "./characters/sjef.h"
#include "./characters/werner.h"
#include "./characters/sietse.h"


// Sounds
#include "bn_sound_items.h";


namespace character_select 
{
    struct character_pictogram
    {
        all_characters character_to_choose;
        int x_offset = 0;
        int y_offset = 0;
    };

    const int menu_items_x = 5;
    const int menu_items_y = 5;

    int y_offset = 0;
    int spacing_x = 85;


    character_pictogram character_pictograms[menu_items_y][menu_items_x] = 
    {
        {
            character_pictogram 
            {
                all_characters::cate,
                -33,
                -62
            },
            character_pictogram 
            {
                all_characters::christine,
                -2,
                -62
            },
            character_pictogram 
            {
                all_characters::fabian,
                29,
                -62
            },
        },
        {
            character_pictogram 
            {
                all_characters::fleur,
                -33,
                -31
            },
            character_pictogram 
            {
                all_characters::hunter,
                -2,
                -31,
            },
            character_pictogram 
            {
                all_characters::joost,
                29,
                -31,
            },
        }
        ,{
            character_pictogram 
            {
                all_characters::laury,
                -33,
                -0
            },
            character_pictogram 
            {
                all_characters::mar,
                -2,
                -0
            },
            character_pictogram 
            {
                all_characters::networkninja,
                29,
                -0
            },
        },
        {
            character_pictogram 
            {
                all_characters::rein,
                -33,
                31
            },
            character_pictogram 
            {
                all_characters::saskia,
                -2,
                31
            },
            character_pictogram 
            {
                all_characters::sjef,
                29,
                31
            },
        },
        {
            character_pictogram 
            {
                all_characters::werner,
                -33,
                62
            },
            character_pictogram 
            {
                all_characters::sietse,
                -2,
                62
            },
            character_pictogram 
            {
                all_characters::empty,
                29,
                62
            },
        }
    };

    void create_character(character **ptr,  all_characters c) 
    {
        if (c == all_characters::cate) {
            *ptr = new cate();
        }
        if (c == all_characters::christine) {
            *ptr = new christine();
        }
        if (c == all_characters::fabian) {
            *ptr = new fabian();
        }
        if (c == all_characters::fleur) {
            *ptr = new fleur();
        }
        if (c == all_characters::hunter) {
            *ptr = new hunter();
        }
        if (c == all_characters::joost) {
            *ptr = new joost();
        }
        if (c == all_characters::laury) {
            *ptr = new laury();
        }
        if (c == all_characters::mar) {
            *ptr = new mar();
        }
        if (c == all_characters::networkninja) {
            *ptr = new networkninja();
        }
        if (c == all_characters::rein) {
            *ptr = new rein();
        }
        if (c == all_characters::saskia) {
            *ptr = new saskia();
        }
        if (c == all_characters::sietse) {
            *ptr = new sietse();
        }
        if (c == all_characters::sjef) {
            *ptr = new sjef();
        }
        if (c == all_characters::werner) {
            *ptr = new werner();
        }
    }
    

    void generate_character_names()
    {
        printer->info_text_sprites.clear();
        printer->text_generator->set_left_alignment();
        printer->text_generator->generate(-114, 2, you->name(), printer->info_text_sprites);
        printer->text_generator->generate(53, 2, other_player->name(), printer->info_text_sprites);
    }

    next_scene run() 
    {
        int t = 0;
        bool connected = false;

        int x_offset = 0;
        int y_offset = 0;

        int selected_menu_item_x = 0;
        int selected_menu_item_y = 0;
        int other_selected_menu_item_x = 0;
        int other_selected_menu_item_y = 0;

        // Background
        bn::regular_bg_ptr bg = bn::regular_bg_items::character_select_screen.create_bg(0,0);

        // Selectors
        bn::optional<bn::sprite_ptr> selector_you = bn::sprite_items::pictogram_selector_you.create_sprite(0,0);
        bn::optional<bn::sprite_ptr> selector_other_player = bn::sprite_items::pictogram_selector_other_player.create_sprite(0,0);

        // Mosaic timers
        int mosaic_timer_you = 20;
        int mosaic_timer_other = 20;

        // Characters / players
        if (you) {
            you->unload();
        }

        auto selected = character_pictograms[selected_menu_item_x][selected_menu_item_y];
        create_character(&you, selected.character_to_choose);
        you->set_preview_mode(true);
        you->sprite_ptr()->set_position(-spacing_x, -45);
        you->sprite_ptr()->set_mosaic_enabled(true);

        if (other_player) {
            other_player->unload();
        }

        auto other_selected = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y];
        create_character(&other_player, other_selected.character_to_choose);
        other_player->set_preview_mode(true);
        other_player->sprite_ptr()->set_position(spacing_x, -45);
        you->sprite_ptr()->set_mosaic_enabled(true);

        camera->set_position(0,0);

        // Text generators
        printer->info_text_sprites.clear();
        generate_character_names();


        while (true) 
        {
            t++;

            if (mosaic_timer_you > 0) {
                mosaic_timer_you -= 1;
            } else {
                you->sprite_ptr()->set_mosaic_enabled(false);
            }

            if (mosaic_timer_other > 0) {
                mosaic_timer_other -= 1;
                other_player->sprite_ptr()->set_mosaic_enabled(false);
            }

            bn::sprites_mosaic::set_stretch(map(bn::max(mosaic_timer_you, mosaic_timer_other), 20, 0, 1, 0));
            

            // multiplayer
            multiplayer::keypad_data keys_data = multiplayer::read_keys();
            multiplayer::send_if_changed(keys_data);
            multiplayer::receive_keypad_data();

            you->update(keys_data.keypad_data);
            other_player->update(multiplayer::other_player_keypad_data.keypad_data);

            you->sprite_ptr()->set_camera(*camera);
            other_player->sprite_ptr()->set_camera(*camera);
            // camera->set_position(you->sprite_ptr()->position();


            if (multiplayer::other_player_keypad_data.keypad_data.start_pressed) {
                BN_LOG("start received");
                you->set_preview_mode(false);
                other_player->set_preview_mode(false);
                selector_you.reset();
                selector_other_player.reset();
                return next_scene::platforming;
            }


            // menu navigation you
            if (keys_data.keypad_data.up_pressed || keys_data.keypad_data.down_pressed || 
                keys_data.keypad_data.left_pressed || keys_data.keypad_data.right_pressed) {
                
                bn::sound_items::cursor.play();
                mosaic_timer_you = 20;

                int last_menu_item_x = selected_menu_item_x;
                int last_menu_item_y = selected_menu_item_y;

                if (keys_data.keypad_data.up_pressed)
                    selected_menu_item_x--;
                if (keys_data.keypad_data.down_pressed)
                    selected_menu_item_x++;
                if (keys_data.keypad_data.left_pressed)
                    selected_menu_item_y--;
                if (keys_data.keypad_data.right_pressed)
                    selected_menu_item_y++;
                

                selected_menu_item_x = mod(selected_menu_item_x, menu_items_x);
                selected_menu_item_y = mod(selected_menu_item_y, menu_items_y);

                auto selected = character_pictograms[selected_menu_item_x][selected_menu_item_y];
                auto c = selected.character_to_choose;
                you->unload(); // unload previous
                create_character(&you, c);
                you->set_preview_mode(true);
                you->sprite_ptr()->set_position(-spacing_x, -45);
                you->sprite_ptr()->set_mosaic_enabled(true);

                generate_character_names();

                if (c == all_characters::empty) {
                    selected_menu_item_x = last_menu_item_x;
                    selected_menu_item_y = last_menu_item_y;
                }

                you->sound_naam().play();
            }


            if (keys_data.keypad_data.a_pressed) {
                you->sound_tagline().play();
            }

            if (keys_data.keypad_data.b_pressed) {
                bn::sound_items::fight_countdown.play();
            }

            // menu navigation other player
            if (multiplayer::other_player_keypad_data.keypad_data.up_pressed || multiplayer::other_player_keypad_data.keypad_data.down_pressed || 
                multiplayer::other_player_keypad_data.keypad_data.left_pressed || multiplayer::other_player_keypad_data.keypad_data.right_pressed) {
                
                // bn::sound_items::cursor.play();
                mosaic_timer_you = 20;


                int last_menu_item_x = other_selected_menu_item_x;
                int last_menu_item_y = other_selected_menu_item_y;

                if (multiplayer::other_player_keypad_data.keypad_data.up_pressed)
                    other_selected_menu_item_x--;
                if (multiplayer::other_player_keypad_data.keypad_data.down_pressed)
                    other_selected_menu_item_x++;
                if (multiplayer::other_player_keypad_data.keypad_data.left_pressed)
                    other_selected_menu_item_y--;
                if (multiplayer::other_player_keypad_data.keypad_data.right_pressed)
                    other_selected_menu_item_y++;
                

                other_selected_menu_item_x = mod(other_selected_menu_item_x, menu_items_x);
                other_selected_menu_item_y = mod(other_selected_menu_item_y, menu_items_y);

                auto selected = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y];
                auto c = selected.character_to_choose;
                other_player->unload(); // unload previous
                create_character(&other_player, c);
                other_player->set_preview_mode(true);
                other_player->sprite_ptr()->set_position(spacing_x, -45);
                other_player->sprite_ptr()->set_mosaic_enabled(true);
                generate_character_names();

                if (c == all_characters::empty) {
                    other_selected_menu_item_x = last_menu_item_x;
                    other_selected_menu_item_y = last_menu_item_y;
                }
            }

            if (multiplayer::other_player_keypad_data.keypad_data.a_pressed) {
                selected_other = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y].character_to_choose;
            }


            for (int x = 0; x < menu_items_x; x++) {
                for (int y = 0; y < menu_items_x; y++) {
                    character_pictogram *item = &character_pictograms[x][y];

                    if (x == selected_menu_item_x && y == selected_menu_item_y) {
                        selector_you->set_x(x_offset + item->x_offset);
                        selector_you->set_y(y_offset + item->y_offset);
                    }

                    if (x == other_selected_menu_item_x && y == other_selected_menu_item_y) {
                        selector_other_player->set_x(x_offset + item->x_offset);
                        selector_other_player->set_y(y_offset + item->y_offset);
                    }
                }
            }


            if (keys_data.keypad_data.start_pressed) {
                printer->info_text_sprites.clear();
                selector_you.reset();
                selector_other_player.reset();

                you->set_preview_mode(false);
                other_player->set_preview_mode(false);

                // you->sprite_ptr()->set_mosaic_enabled(true);
                other_player->sprite_ptr()->set_mosaic_enabled(true);

                // bn::link::send(multiplayer::signal_start_game);
                return next_scene::platforming;
            }

            bn::core::update();
        }

        return next_scene::platforming;
    }


    
}


