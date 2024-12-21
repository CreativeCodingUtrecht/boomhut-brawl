#pragma once

#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_rect_window.h"
#include "bn_point.h"
#include "bn_log.h"
#include "bn_format.h"
#include "bn_math.h"
#include "bn_display.h"
#include "bn_link.h"
#include "bn_link_state.h"
#include "bn_music.h"
#include "bn_audio.h"
#include "bn_blending_fade_alpha.h"
#include "bn_blending.h"

// BGs
#include "bn_regular_bg_items_tilemap.h"
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_background_indoors.h"
#include "bn_regular_bg_items_background_left.h"
#include "bn_regular_bg_items_background_right.h"
#include "bn_regular_bg_items_trein_bg.h"
#include "bn_regular_bg_items_facade.h"

// Sprites
#include "bn_sprite_items_wheel.h"
#include "bn_sprite_items_wheel_snow.h"
#include "bn_sprite_items_adult_city.h"

// Includes
#include "../include/utils.h"
#include "globals.hpp"
#include "pickups.hpp"
#include "splash.hpp"
#include "main_menu.hpp"
#include "zoop.hpp"
#include "healthbars.hpp"
#include "sprite_autounload.hpp"
#include "train.hpp"
#include "snowball.hpp"

// Characters
#include "./characters/all_characters.hpp"


#include "scene.hpp"


using namespace bn;




namespace battle
{
    
    next_scene run()
    {
        // int clouds_x = 0.0;

        // pickups
        // const bn::fixed x_offset = 120;
        // const bn::fixed y_offset = 126;

        // pickups::lipje lipjes[7] = 
        // {
        //     pickups::lipje(0+x_offset,-y_offset/2),
        //     pickups::lipje(32+x_offset,-y_offset/2),
        //     pickups::lipje(64+x_offset,-y_offset/2),
        //     pickups::lipje(96+x_offset,-y_offset/2),
        //     pickups::lipje(32+x_offset,y_offset),
        //     pickups::lipje(64+x_offset,y_offset),
        //     pickups::lipje(96+x_offset,y_offset)
        // };

//        const bn::fixed x_offset = ;
//        const bn::fixed y_offset = 256 + ;

        // Props        
        // bn::sprite_ptr props[] = {
        //     // bn::sprite_items::adult_city.create_sprite(26 - 256 + bn::display::width() / 2 + 64, 318 - 256 + bn::display::height() / 2 + 48),
        //     // .create_sprite()
        // };

        // adult_city.set_camera(*camera);
        // adult_city.set_z_order(-100);

        // for (auto &prop : props) {
        //     prop.set_camera(*camera);
        //     prop.set_z_order(-100);
        // }

        // Adult city
        sprite_autounload adult_city(bn::sprite_items::adult_city, bn::fixed_point(0 - 256 + bn::display::width() / 2 + 48, 318 - 256 + bn::display::height() / 2 + 48));

        // Snow wheel
        sprite_autounload wheel_snow(bn::sprite_items::wheel_snow, bn::fixed_point(327 - 256 + bn::display::width() / 2 + 32, 689 - 256 + bn::display::height() / 2 + 16));


        // Animals
        zoop::bee bee;
        zoop::rat rat;

        // Birds?


        BN_LOG("entering battle!!");

        // sky and mountains background
        background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
        background->set_z_order(4);
        background->set_camera(*camera);

        // Electric garden


        // Trein
        train the_train;



        // Default characters
        if (!you) {
            you = new networkninja();
        }

        if (!other_player) {
            other_player = new fabian();
        }

        // Health bars
        healthbars bars = healthbars(you->avatar(), other_player->avatar());        
        // abilitybars abilitybars;

        // Camera
        you->sprite_ptr()->set_camera(*camera);
        other_player->sprite_ptr()->set_camera(*camera);
        camera->set_position(you->sprite_ptr()->position());

        // Printer
        printer->text_generator->set_center_alignment();

        int frame = 0;

        while(true)
        {
            frame++;

            // Update snowballs
            snowballs::update_all();


            // Update animals
            bee.update();
            rat.update();

            // Update snow
            global_snow->draw_and_update();

            // Update train
            the_train.update();

            // Props!
            adult_city.update_visibility();
            wheel_snow.update_visibility();

            // Electric garden
//            e_garden_anim.update();

            // log_memory_usage();
            
//            printer->print_map_tiles_at_position(*map_item, you->sprite_ptr()->position());
            // printer->print("{} |nekfenwfjwklgenwnlgewknwe ");
            // printer->print_map_tile_and_position(*map_item, you->sprite_ptr()->position());
//             BN_LOG(props[0].position().x());

            // Update level
            // Lipje pickup items
            // for (size_t i = 0; i < 7; i++) {
            //     lipjes[i].update();
            // }

            // Moving clouds
            // clouds_x -=  0.1;
        //    trein_bg.set_x(trein_bg.x() - 2);

            // clouds.set_x(clouds_x + player.position.x() / bn::fixed(40.0));


            // Move clouds/mountains bg parallax
            // sky.set_position(-player.position / bn::fixed(50.0));


            // Update player, send keypad to other players -----------
            multiplayer::keypad_data keypad_data_to_send = multiplayer::read_keys();

            // Always update own player
            you->update(frame, keypad_data_to_send.keypad_data);


            // Indoors and outdoors ----------------------------
            if (you->is_indoors()) {
                background->set_item(bn::regular_bg_items::background_indoors);
            } else {
                if (camera->x() < 130) {
                    background->set_item(bn::regular_bg_items::background_left);
                } else if (camera->x() > 480) {
                    background->set_item(bn::regular_bg_items::background_right);
                } else {
                    background->set_item(bn::regular_bg_items::background);
                }
            }

            if (other_player->is_indoors() && !you->is_indoors()) {
                bn::blending::set_transparency_alpha(0.3);
                other_player->sprite_ptr()->set_blending_enabled(true);
            } else {
                other_player->sprite_ptr()->set_blending_enabled(false);
            }

            // Maps left and right ----------------------------

            // Send if changed
            multiplayer::send_if_changed(keypad_data_to_send);

            // Update other player, receive keypad from other players
            multiplayer::receive_keypad_data();

            // always update for animations
            other_player->update(frame, multiplayer::other_player_keypad_data.keypad_data);

            // Smooth cam
            camera_follow_smooth(*camera, you->sprite_ptr()->position());
            camera->set_x(constrain(camera->x(), 0, bounds_max_x)); // Constrain camera bounds

            // Health bars
            bars.set_health_left(you->get_health() / you->max_health());
            bars.set_health_right(other_player->get_health() / other_player->max_health());

            // Ability bars, still to determine game balance
            // - increase ability every x frames
            // - reset ability 
            you->increase_ability();
            other_player->increase_ability();

            // abilitybars.set_ability_left(you->get_ability() / you->max_ability);
            // abilitybars.set_ability_right(other_player->get_ability() / other_player->max_ability);        

            // Back to character select
            // if (bn::keypad::select_pressed() || multiplayer::other_player_keypad_data.keypad_data.select_pressed) {
            //     background.reset();
            //     bars.pictogram.reset();
            //     bars.pictogram2.reset();
            //     return next_scene::character_select;
            // }

            // Win / lose
            if (you->get_health() <= 0 || other_player->get_health() <= 0) {
                snowballs::snowballs.clear();
                background.reset();

//                background.reset();
                bars.pictogram.reset();
                bars.pictogram2.reset();

                if (you->get_health() <= 0) {
                    winner = other_player;
                } else {
                    winner = you;
                }

                return next_scene::you_win;
            }

            bn::core::update();
        }
    }
}
