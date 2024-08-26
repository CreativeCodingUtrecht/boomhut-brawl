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


namespace character_select 
{
    struct character_pictogram
    {
        bn::sprite_item pictogram;
        all_characters character_to_choose;
        int x_offset = 0;
        int y_offset = 0;
        int target_x = 0;
        int target_y = 0;
        bn::optional<bn::sprite_ptr> spr;
    };

    const int menu_items_x = 1;
    const int menu_items_y = 1;

    int y_offset = 0;


    character_pictogram character_pictograms[menu_items_x][menu_items_y] = 
    {
        {
            character_pictogram 
            {
                bn::sprite_items::rein_pictogram,
                all_characters::rein,
                0,
                0
            },
        }
    };


    character create_character(all_characters c) 
    {
        if (c == all_characters::cate) {
            return cate();
        }
        if (c == all_characters::christine) {
            return christine();
        }
        if (c == all_characters::fabian) {
            return fabian();
        }
        if (c == all_characters::fleur) {
            return fleur();
        }
        if (c == all_characters::hunter) {
            return hunter();
        }
        if (c == all_characters::joost) {
            return joost();
        }
        if (c == all_characters::laury) {
            return laury();
        }
        if (c == all_characters::mar) {
            return mar();
        }
        if (c == all_characters::networkninja) {
            return networkninja();
        }
        if (c == all_characters::rein) {
            return rein();
        }
        if (c == all_characters::saskia) {
            return saskia();
        }
        if (c == all_characters::sjef) {
            return sjef();
        }
        if (c == all_characters::werner) {
            return werner();
        }
    }

    next_scene start_game(int selected_menu_item_x, int selected_menu_item_y) 
    {   
        // bn::sound_items::into.play();
        // // bn::sound_items::shield.play();
        
        // for (int x = 0; x < menu_items_x; x++) {
        //     for (int y = 0; y < menu_items_x; y++) {
        //         menu_item *item = &menu_items[x][y];
        //         item->spr.reset();
        //     }
        // }

        // return menu_items[selected_menu_item_x][selected_menu_item_y].scene;
    }
    

    next_scene run() 
    {
        int t = 0;
        bool connected = false;

        int x_offset = 0;
        int y_offset = 0;

        int selected_menu_item_x = 0;
        int selected_menu_item_y = 0;
        int other_selected_menu_item_x = 1;
        int other_selected_menu_item_y = 0;

        // Background
        bn::regular_bg_ptr bg = bn::regular_bg_items::character_select_screen.create_bg(0,0);

        // Selectors
        bn::sprite_ptr selector_you = bn::sprite_items::pictogram_selector_you.create_sprite(0,0);
        bn::sprite_ptr selector_other_player = bn::sprite_items::pictogram_selector_other_player.create_sprite(0,0);

        // Characters / players 
        auto you = fabian();
        auto other_player = laury();
        int spacing_x = 85;
        bn::sprite_ptr you_spr = you.sprite_item().create_sprite(-spacing_x,-45);
        bn::sprite_ptr other_spr = other_player.sprite_item().create_sprite(spacing_x,-45);
        auto you_anim = you.idle_anim(you_spr);
        auto other_anim = other_player.idle_anim(other_spr);
        

        while (true) 
        {
            t++;

            // Animate
            you_anim.update();
            other_anim.update();

            // Receive
            if (bn::optional<bn::link_state> link_state = bn::link::receive()) {
                if (!connected) {
                    printer->print("connected to other player!");
                }

                const bn::link_player& first_other_player = link_state->other_players().front();
                int data = first_other_player.data();
                // Start game when other player also starts
                if (data == multiplayer::signal_start_game) {
                    return start_game(selected_menu_item_x, selected_menu_item_y);
                }
            }

            // logo in the corner
            // anim.update();
            // twinkle_anim.update();


            // menu navigation 
            if (bn::keypad::up_pressed() || bn::keypad::down_pressed() || bn::keypad::right_pressed() || bn::keypad::left_pressed()) {
                bn::sound_items::cursor.play();

                if (bn::keypad::up_pressed())
                    selected_menu_item_x--;
                if (bn::keypad::down_pressed())
                    selected_menu_item_x++;
                if (bn::keypad::left_pressed())
                    selected_menu_item_y--;
                if (bn::keypad::right_pressed())
                    selected_menu_item_y++;
                

                selected_menu_item_x = mod(selected_menu_item_x, menu_items_x);
                selected_menu_item_y = mod(selected_menu_item_y, menu_items_y);
            }

            for (int x = 0; x < menu_items_x; x++) {
                for (int y = 0; y < menu_items_x; y++) {
                    character_pictogram *item = &character_pictograms[x][y];
                    item->target_y = (selected_menu_item_x == x && selected_menu_item_y == y) ? -3 : 0;
                    // item->spr->set_y(lerp(item->target_y + y_offset + item->y_offset, item->spr->y(), 0.2));

                    // grow menu item
                    // item->spr->set_scale(lerp(item->spr->horizontal_scale(), 1.0, 0.15));

                    if (x == selected_menu_item_x && y == selected_menu_item_y) {
                        selector_you.set_x(item->target_x + x_offset + item->x_offset - 12);
                        selector_you.set_y(item->target_y + y_offset + item->y_offset);
                    }

                    if (x == other_selected_menu_item_x && y == other_selected_menu_item_y) {
                        selector_other_player.set_x(item->target_x + x_offset + item->x_offset - 12);
                        selector_other_player.set_y(item->target_y + y_offset + item->y_offset);
                    }
                }
            }
            

            // menu_selector_spr.set_x(lerp(menu_selector_target_x, menu_selector_spr.x(), 0.6));
            // menu_selector_spr.set_y(lerp(menu_selector_target_y, menu_selector_spr.y(), 0.6));
            // menu_selector_spr.set_scale(lerp(menu_selector_spr.horizontal_scale(), 1.1, 0.15));
            


            if (bn::keypad::a_pressed()) {
                bn::link::send(multiplayer::signal_start_game);
                return start_game(selected_menu_item_x, selected_menu_item_y);
            }

            bn::core::update();
        }

        return next_scene::platforming;
    }


    
}


