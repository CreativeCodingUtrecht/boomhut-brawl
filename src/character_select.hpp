#pragma once

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_palette_actions.h"
#include "bn_sprite_items_menu_platforming.h"
#include "bn_sprite_items_menu_selector.h"
#include "bn_bg_palettes.h"
#include "bn_bg_palette_ptr.h"
#include "bn_regular_bg_items_menu_bg.h"
#include "bn_link.h"
#include "bn_link_state.h"
#include "bn_sound_items.h"
#include "bn_music_items.h"
#include "bn_music.h"

// Includes
#include "multiplayer.hpp"
#include "globals.hpp"
#include "scene.hpp"


// Font 
#include "../../common/include/common_fixed_8x16_sprite_font.h"

// Backgrounds
#include "bn_regular_bg_items_character_select_screen.h"

// Sprites
#include "bn_sprite_items_pictogram_selector_you.h"
#include "bn_sprite_items_pictogram_selector_other_player.h"
#include "bn_sprite_items_countdown_3.h"
#include "bn_sprite_items_countdown_2.h"
#include "bn_sprite_items_countdown_1.h"
#include "bn_sprite_items_countdown_fight.h"

// Characters
#include "./characters/-character.hpp"
#include "./characters/cate.hpp"
#include "./characters/christine.hpp"
#include "./characters/fabian.hpp"
#include "./characters/fleur.hpp"
#include "./characters/hunter.hpp"
#include "./characters/joost.hpp"
#include "./characters/laury.hpp"
#include "./characters/mar.hpp"
#include "./characters/networkninja.hpp"
#include "./characters/rein.hpp"
#include "./characters/saskia.hpp"
#include "./characters/sjef.hpp"
#include "./characters/werner.hpp"
#include "./characters/sietse.hpp"


// Sounds
#include "bn_sound_items.h"


namespace character_select 
{
    struct character_pictogram
    {
        all_characters character_to_choose;
        int x_offset = 0;
        int y_offset = 0;
    };

    const int menu_items_y = 5;
    const int menu_items_x = 3;

    character_pictogram character_pictograms[menu_items_y][menu_items_x] = 
    {
        {
            character_pictogram(all_characters::cate, -33, -62),
            character_pictogram(all_characters::christine, -2, -62),
            character_pictogram(all_characters::fabian, 29, -62),
        },
        {
            character_pictogram(all_characters::fleur, -33, -31),
            character_pictogram(all_characters::hunter, -2, -31),
            character_pictogram(all_characters::joost, 29, -31),
        },
        {
            character_pictogram(all_characters::laury, -33, -0),
            character_pictogram(all_characters::mar, -2, -0),
            character_pictogram(all_characters::networkninja, 29, -0)
        },
        {
            character_pictogram(all_characters::rein, -33, 31),
            character_pictogram(all_characters::saskia, -2, 31),
            character_pictogram(all_characters::sjef, 29, 31),
        },
        {
            character_pictogram(all_characters::werner, -33, 62),
            character_pictogram(all_characters::sietse, -2, 62),
            character_pictogram(all_characters::empty, 29, 62),
        }
    };

    void create_character(character **ptr,  all_characters c)
    {
        delete *ptr;

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

    bn::optional<bn::sprite_ptr> weapon_you;
    bn::optional<bn::sprite_ptr> weapon_other_player;

    void generate_character_names()
    {
        printer->info_text_sprites.clear();
        printer->text_generator->set_left_alignment();
        printer->text_generator->generate(-114, 2, you->name(), printer->info_text_sprites);
        printer->text_generator->generate(53, 2, other_player->name(), printer->info_text_sprites);

        bn::optional<weapon_info> your_weapon = you->get_weapon_info();
        bn::optional<weapon_info> other_player_weapon = other_player->get_weapon_info();

        if (your_weapon) {
//            printer->text_generator->generate(-114, 18, "weapon: ", printer->info_text_sprites);
//            printer->text_generator->generate(-114, 32, your_weapon->name, printer->info_text_sprites);
//            weapon_you = your_weapon->avatar.create_sprite(-114 + 16, 48);
            weapon_you = your_weapon->avatar.create_sprite(-100, 30);
        } else {
            weapon_you.reset();
        }
        if (other_player_weapon) {
//            printer->text_generator->generate(53, 18, "weapon: ", printer->info_text_sprites);
//            printer->text_generator->generate(53, 32, other_player_weapon->name, printer->info_text_sprites);
        } else {
            weapon_other_player.reset();
        }
    }


    next_scene run() 
    {
        int t = 0;

        int selected_menu_item_x = 0;
        int selected_menu_item_y = 0;
        int other_selected_menu_item_x = 0;
        int other_selected_menu_item_y = 0;

        if (!bn::music::playing()) {
            bn::music_items::backwithavengeance.play();
            bn::music::set_volume(0.25);
        }

        // Background
        bn::optional<bn::regular_bg_ptr> bg = bn::regular_bg_items::character_select_screen.create_bg(0,0);

        // Selectors
        bn::optional<bn::sprite_ptr> selector_you = bn::sprite_items::pictogram_selector_you.create_sprite(0,0);
        bn::optional<bn::sprite_ptr> selector_other_player = bn::sprite_items::pictogram_selector_other_player.create_sprite(0,0);

        // Mosaic timers
        int mosaic_timer_you = 20;
        int mosaic_timer_other = 20;


        // Characters / players
        int y_offset = -45;
        int spacing_x = 85;

        // You
        if (you) you->unload();
        create_character(&you, character_pictograms[selected_menu_item_x][selected_menu_item_y].character_to_choose);
        you->set_preview_mode(true);
        you->sprite_ptr()->set_position(-spacing_x, y_offset);
        you->sprite_ptr()->set_mosaic_enabled(true);

        // Other
        if (other_player) other_player->unload();
        create_character(&other_player, character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y].character_to_choose);
        other_player->set_preview_mode(true);
        other_player->sprite_ptr()->set_position(spacing_x, y_offset);
        you->sprite_ptr()->set_mosaic_enabled(true);

        camera->set_position(0,0);

        // Text generators
        printer->info_text_sprites.clear();
        generate_character_names();

        // Ready state
        bool you_ready = false;
        bool other_player_ready = false;

        // Big countdown
        bool counting_down = false;
        int countdown = 180;

        bn::optional<bn::sprite_ptr> countdown_1, countdown_2, countdown_3;
        bn::optional<bn::sprite_ptr> countdown_fight;

        bn::color icy = bn::color(10, 10, 31);

        bn::bg_palette_ptr pal = bg->palette();
        pal.set_fade_color(icy);


        while (true) 
        {
            t++;

            // log_memory_usage();


            // Snow
            global_snow->draw_and_update();

            // Mosaic timer
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
            

            // Counting down
            if (counting_down) {
                pal.set_fade_intensity(.65);

                countdown--;

                if (countdown <= 180 && countdown > 150) {
                    if (!countdown_3) {
                        countdown_3 = bn::sprite_items::countdown_3.create_sprite(0,0);
                        countdown_3->set_scale(0.01);
                    }
                    countdown_3->set_scale(lerp(countdown_3->horizontal_scale(), 2, .5));
                }
                if (countdown <= 150 && countdown > 120) {
                    countdown_3->set_scale(lerp(countdown_3->horizontal_scale(), 0.01, .5));
                }
                if (countdown <= 120 && countdown > 90) {
                    if (!countdown_2) {
                        countdown_3.reset();
                        countdown_2 = bn::sprite_items::countdown_2.create_sprite(0,0);
                        countdown_2->set_scale(0.01);
                    }
                    countdown_2->set_scale(lerp(countdown_2->horizontal_scale(), 2, .5));

                }
                if (countdown <= 90 && countdown > 60) {
                    countdown_2->set_scale(lerp(countdown_2->horizontal_scale(), 0.01, .5));
                    
                }
                if (countdown <= 60 && countdown > 30) {
                    if (!countdown_1) {
                        countdown_2.reset();
                        countdown_1 = bn::sprite_items::countdown_1.create_sprite(0,0);
                        countdown_1->set_scale(0.01);
                    }
                    countdown_1->set_scale(lerp(countdown_1->horizontal_scale(), 2, .5));
                }
                if (countdown <= 30 && countdown > 0) {
                    countdown_1->set_scale(lerp(countdown_1->horizontal_scale(), 0.01, .5));
                    
                }
                if (countdown <= 0 && countdown > -30) {
                    if (!countdown_fight) {
                        countdown_1.reset();
                        countdown_fight = bn::sprite_items::countdown_fight.create_sprite(0,0);
                        countdown_fight->set_scale(0.01);
                    }
                    countdown_fight->set_scale(lerp(countdown_fight->horizontal_scale(), 2, .5));
                }
                if (countdown <= -30 && countdown > -60) {
                    countdown_fight->set_scale(lerp(countdown_fight->horizontal_scale(), 0.01, .5));
                }
                // countdown done
                if (countdown == -60) {
                    printer->info_text_sprites.clear();
                    selector_you.reset();
                    selector_other_player.reset();

                    weapon_you.reset();
                    weapon_other_player.reset();

                    you->set_preview_mode(false);
                    other_player->set_preview_mode(false);
                    you->sprite_ptr()->set_mosaic_enabled(true);
                    other_player->sprite_ptr()->set_mosaic_enabled(true);

                    countdown_fight.reset();
                    bg.reset();

                    BN_LOG("start battle!!");
                    return next_scene::battle;
                }
            }


            // multiplayer
            multiplayer::keypad_data keys_data = multiplayer::read_keys();
            multiplayer::send_if_changed(keys_data);
            multiplayer::receive_keypad_data();

            you->update(keys_data.keypad_data);
            other_player->update(multiplayer::other_player_keypad_data.keypad_data);

            you->sprite_ptr()->set_camera(*camera);
            other_player->sprite_ptr()->set_camera(*camera);
            
            if (multiplayer::other_player_keypad_data.keypad_data.a_pressed) {
                other_player_ready = true;
            }

            if (keys_data.keypad_data.a_pressed) {
                you->sound_tagline().play();
                you_ready = true;
            }

            if (you_ready && other_player_ready) {
                bn::sound_items::fight_countdown.play();
                counting_down = true;
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
                

                selected_menu_item_x = mod(selected_menu_item_x, menu_items_y);
                selected_menu_item_y = mod(selected_menu_item_y, menu_items_x);

                auto selected = character_pictograms[selected_menu_item_x][selected_menu_item_y];
                auto c = selected.character_to_choose;

                if (c == all_characters::empty) {
                    selected_menu_item_x = last_menu_item_x;
                    selected_menu_item_y = last_menu_item_y;
                } else {
                    you->unload(); // unload previous
                    create_character(&you, c);
                    you->set_preview_mode(true);
                    you->sprite_ptr()->set_position(-spacing_x, -45);
                    you->sprite_ptr()->set_mosaic_enabled(true);
                    generate_character_names();
                    you->sound_naam().play();
                }
            }

            // TODO to be deleted later
            if (keys_data.keypad_data.b_pressed) {
                bn::sound_items::fight_countdown.play();
                countdown = 180;
                counting_down = true;
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
                

                other_selected_menu_item_x = mod(other_selected_menu_item_x, menu_items_y);
                other_selected_menu_item_y = mod(other_selected_menu_item_y, menu_items_x);

                auto selected = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y];
                auto c = selected.character_to_choose;
                
                if (c == all_characters::empty) {
                    other_selected_menu_item_x = last_menu_item_x;
                    other_selected_menu_item_y = last_menu_item_y;
                } else {
                    other_player->unload(); // unload previous
                    create_character(&other_player, c);
                    other_player->set_preview_mode(true);
                    other_player->sprite_ptr()->set_position(spacing_x, -45);
                    other_player->sprite_ptr()->set_mosaic_enabled(true);
                    generate_character_names();
                }
            }

            for (int x = 0; x < menu_items_y; x++) {
                for (int y = 0; y < menu_items_y; y++) {
                    character_pictogram *item = &character_pictograms[x][y];

                    if (x == selected_menu_item_x && y == selected_menu_item_y) {
                        selector_you->set_x(item->x_offset);
                        selector_you->set_y(item->y_offset);
                    }

                    if (x == other_selected_menu_item_x && y == other_selected_menu_item_y) {
                        selector_other_player->set_x(item->x_offset);
                        selector_other_player->set_y(item->y_offset);
                    }
                }
            }


            // Start pressed, immediate start
            if (keys_data.keypad_data.start_pressed || multiplayer::other_player_keypad_data.keypad_data.start_pressed) {
                bg.reset();
                printer->info_text_sprites.clear();
                selector_you.reset();
                selector_other_player.reset();

                weapon_you.reset();
                weapon_other_player.reset();

                you->set_preview_mode(false);
                other_player->set_preview_mode(false);
                you->sprite_ptr()->set_mosaic_enabled(true);
                other_player->sprite_ptr()->set_mosaic_enabled(true);

                return next_scene::battle;
            }

            bn::core::update();
        }

        return next_scene::battle;
    }
}


