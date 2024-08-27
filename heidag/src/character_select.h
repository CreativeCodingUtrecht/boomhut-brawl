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
        // bn::sprite_animate_action<400> anim;
    };

    const int menu_items_x = 5;
    const int menu_items_y = 5;

    int y_offset = 0;
    int spacing_x = 85;


    // bn::sprite_ptr you_spr = bn::sprite_items::fabian.create_sprite(-spacing_x,-45);
    // bn::sprite_ptr other_spr = bn::sprite_items::fabian.create_sprite(spacing_x,-45);

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

    bn::sprite_animate_action<400> get_animation_for_character(all_characters c, bn::sprite_ptr spr) 
    {
        if (c == all_characters::cate) {
            return cate::idle_anim(spr);
        }
        if (c == all_characters::christine) {
            return christine::idle_anim(spr);
        }

        if (c == all_characters::fabian) {
            return fabian::idle_anim(spr);
        }
        if (c == all_characters::fleur) {
            return fleur::idle_anim(spr);
        }
        if (c == all_characters::hunter) {
            return hunter::idle_anim(spr);
        }
        if (c == all_characters::joost) {
            return joost::idle_anim(spr);
        }
        if (c == all_characters::laury) {
            return laury::idle_anim(spr);
        }
        if (c == all_characters::mar) {
            return mar::idle_anim(spr);
        }
        if (c == all_characters::networkninja) {
            return networkninja::idle_anim(spr);
        }
        if (c == all_characters::rein) {
            return rein::idle_anim(spr);
        }
        if (c == all_characters::saskia) {
            return saskia::idle_anim(spr);
        }
        if (c == all_characters::sietse) {
            return sietse::idle_anim(spr);
        }
        if (c == all_characters::sjef) {
            return sjef::idle_anim(spr);
        }
        if (c == all_characters::werner) {
            return werner::idle_anim(spr);
        }
    }



    bn::sound_item get_sound_for_character(all_characters c)
    {
        if (c == all_characters::cate) {
            return bn::sound_items::cat_naam;
        }
        if (c == all_characters::christine) {
            return bn::sound_items::christine_naam;
        }
        if (c == all_characters::fabian) {
            return bn::sound_items::fabian_naam;
        }
        if (c == all_characters::fleur) {
            return bn::sound_items::fleur_naam;
        }
        if (c == all_characters::hunter) {
            return bn::sound_items::niels_naam;
        }
        if (c == all_characters::joost) {
            return bn::sound_items::joost_naam;
        }
        if (c == all_characters::laury) {
            return bn::sound_items::laura_naam;
        }
        if (c == all_characters::mar) {
            return bn::sound_items::mar_naam;
        }
        if (c == all_characters::networkninja) {
            return bn::sound_items::timo_naam;
        }
        if (c == all_characters::rein) {
            return bn::sound_items::rein_naam;
        }
        if (c == all_characters::saskia) {
            return bn::sound_items::saskia_naam;
        }
        if (c == all_characters::sietse) {
            return bn::sound_items::sietse_naam;
        }
        if (c == all_characters::sjef) {
            return bn::sound_items::sjef_naam;
        }
        if (c == all_characters::werner) {
            return bn::sound_items::werner_naam;
        }
    }

    bn::sound_item get_tagline_sound_for_character(all_characters c)
    {
        if (c == all_characters::cate) {
            return bn::sound_items::cat_tagline;
        }
        if (c == all_characters::christine) {
            return bn::sound_items::christine_tagline;
        }
        if (c == all_characters::fabian) {
            return bn::sound_items::fabian_tagline;
        }
        if (c == all_characters::fleur) {
            return bn::sound_items::fleur_tagline;
        }
        if (c == all_characters::hunter) {
            return bn::sound_items::niels_tagline;
        }
        if (c == all_characters::joost) {
            return bn::sound_items::joost_tagline;
        }
        if (c == all_characters::laury) {
            return bn::sound_items::laura_tagline;
        }
        if (c == all_characters::mar) {
            return bn::sound_items::mar_tagline;
        }
        if (c == all_characters::networkninja) {
            return bn::sound_items::timo_tagline;
        }
        if (c == all_characters::rein) {
            return bn::sound_items::timo_tagline;
        }
        if (c == all_characters::saskia) {
            return bn::sound_items::saskia_tagline;
        }
        if (c == all_characters::sietse) {
            return bn::sound_items::sietse_tagline;
        }
        if (c == all_characters::sjef) {
            return bn::sound_items::sjef_tagline;
        }
        if (c == all_characters::werner) {
            return bn::sound_items::werner_tagline;
        }
    }


    // void 

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



    void create_character(bn::unique_ptr<character> &ptr,  all_characters c) 
    {
        if (c == all_characters::cate) {
            ptr.reset(new cate());
        }
        if (c == all_characters::christine) {
            ptr.reset(new christine());
        }
        if (c == all_characters::fabian) {
            ptr.reset(new fabian());
        }
        if (c == all_characters::fleur) {
            ptr.reset(new fleur());
        }
        if (c == all_characters::hunter) {
            ptr.reset(new hunter());
        }
        if (c == all_characters::joost) {
            ptr.reset(new joost());
        }
        if (c == all_characters::laury) {
            ptr.reset(new laury());
        }
        if (c == all_characters::mar) {
            ptr.reset(new mar());
        }
        if (c == all_characters::networkninja) {
            ptr.reset(new networkninja());
        }
        if (c == all_characters::rein) {
            ptr.reset(new rein());
        }
        if (c == all_characters::saskia) {
            ptr.reset(new saskia());
        }
        if (c == all_characters::sietse) {
            ptr.reset(new sietse());
        }
        if (c == all_characters::sjef) {
            ptr.reset(new sjef());
        }
        if (c == all_characters::werner) {
            ptr.reset(new werner());
        }
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
        bn::sprite_ptr selector_you = bn::sprite_items::pictogram_selector_you.create_sprite(0,0);
        bn::sprite_ptr selector_other_player = bn::sprite_items::pictogram_selector_other_player.create_sprite(0,0);


        // Characters / players
        auto selected = character_pictograms[selected_menu_item_x][selected_menu_item_y];
        create_character(you, selected.character_to_choose);

        auto other_selected = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y];
        create_character(other_player, other_selected.character_to_choose);


        bn::sprite_ptr you_spr = cate::sprite_item().create_sprite(-spacing_x,-45);
        bn::sprite_ptr other_spr = cate::sprite_item().create_sprite(spacing_x,-45);

        bn::optional<bn::sprite_animate_action<400>> you_anim = cate::idle_anim(you_spr);
        bn::optional<bn::sprite_animate_action<400>> other_anim = cate::idle_anim(other_spr);


        // Text generators
        bn::optional<bn::sprite_text_generator> text_generator_you = bn::optional(bn::sprite_text_generator(common::variable_8x8_sprite_font));
        text_generator_you->set_left_alignment();
        bn::vector<bn::sprite_ptr, 4> text_sprites;
        text_generator_you->generate(-112, 2, you->name(), text_sprites);

        bn::optional<bn::sprite_text_generator> text_generator_other = bn::optional(bn::sprite_text_generator(common::variable_8x8_sprite_font));
        text_generator_other->set_right_alignment();
        bn::vector<bn::sprite_ptr, 4> text_sprites_other;
        text_generator_other->generate(112, 2, other_player->name(), text_sprites_other);


        while (true) 
        {
            t++;

            you_anim->update();
            other_anim->update();

            // multiplayer
            multiplayer::keypad_data keys_data = multiplayer::read_keys();
            multiplayer::send_if_changed(keys_data);
            multiplayer::receive_keypad_data();


            if (multiplayer::other_player_keypad_data.keypad_data.start_pressed) {
                BN_LOG("start received");
                text_sprites.clear();
                text_sprites_other.clear();
                text_generator_you.reset();
                text_generator_other.reset();
                return next_scene::platforming;
            }


            // menu navigation you
            if (keys_data.keypad_data.up_pressed || keys_data.keypad_data.down_pressed || 
                keys_data.keypad_data.left_pressed || keys_data.keypad_data.right_pressed) {
                
                bn::sound_items::cursor.play();

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
                create_character(you, c);
                text_sprites.clear();
                text_generator_you->generate(-112, 2, you->name(), text_sprites);

                if (c == all_characters::empty) {
                    selected_menu_item_x = last_menu_item_x;
                    selected_menu_item_y = last_menu_item_y;
                }

                you_anim = get_animation_for_character(c, you_spr);

                get_sound_for_character(c).play();
            }


            if (keys_data.keypad_data.a_pressed) {
                
                selected_you = character_pictograms[selected_menu_item_x][selected_menu_item_y].character_to_choose;
                get_tagline_sound_for_character(*selected_you).play();
            }

            // menu navigation other player
            if (multiplayer::other_player_keypad_data.keypad_data.up_pressed || multiplayer::other_player_keypad_data.keypad_data.down_pressed || 
                multiplayer::other_player_keypad_data.keypad_data.left_pressed || multiplayer::other_player_keypad_data.keypad_data.right_pressed) {
                
                // bn::sound_items::cursor.play();

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
                create_character(other_player, c);
                text_sprites_other.clear();
                text_generator_other->generate(112, 2, other_player->name(), text_sprites_other);

                if (c == all_characters::empty) {
                    other_selected_menu_item_x = last_menu_item_x;
                    other_selected_menu_item_y = last_menu_item_y;
                }

                other_anim = get_animation_for_character(c, other_spr);
            }

            if (multiplayer::other_player_keypad_data.keypad_data.a_pressed) {
                selected_other = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y].character_to_choose;
            }


            for (int x = 0; x < menu_items_x; x++) {
                for (int y = 0; y < menu_items_x; y++) {
                    character_pictogram *item = &character_pictograms[x][y];

                    if (x == selected_menu_item_x && y == selected_menu_item_y) {
                        selector_you.set_x(x_offset + item->x_offset);
                        selector_you.set_y(y_offset + item->y_offset);
                    }

                    if (x == other_selected_menu_item_x && y == other_selected_menu_item_y) {
                        selector_other_player.set_x(x_offset + item->x_offset);
                        selector_other_player.set_y(y_offset + item->y_offset);
                    }
                }
            }


            if (keys_data.keypad_data.start_pressed) {
                text_sprites.clear();
                text_sprites_other.clear();
                text_generator_you.reset();
                text_generator_other.reset();
                // bn::link::send(multiplayer::signal_start_game);
                return next_scene::platforming;
            }

            bn::core::update();
        }

        return next_scene::platforming;
    }


    
}


