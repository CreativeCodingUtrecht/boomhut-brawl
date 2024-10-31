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
#include "bn_regular_bg_items_trein_bg.h"
#include "bn_regular_bg_items_facade.h"

// Sprites
#include "bn_sprite_items_pictogram_frame.h"
#include "bn_sprite_items_healthbar_fill.h"
#include "bn_sprite_items_healthbar_frame.h"
#include "bn_sprite_items_wheel.h"
#include "bn_sprite_items_abilitybar_fill.h"

// Includes
#include "../include/utils.h"
#include "globals.hpp"
#include "pickups.hpp"
#include "splash.hpp"
#include "main_menu.hpp"
#include "zoop.hpp"

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


#include "scene.hpp"


using namespace bn;

struct abilitybars
{
    const bn::fixed_point position_1 = bn::fixed_point(-bn::display::width() / 2 + 20, -bn::display::height() / 2 + 30);
    bn::sprite_ptr abilitybar_fill = bn::sprite_items::abilitybar_fill.create_sprite(position_1.x() + 48, position_1.y()+3);
    bn::sprite_ptr abilitybar_frame = bn::sprite_items::healthbar_frame.create_sprite(position_1.x() + 48, position_1.y());

    const bn::fixed_point position_2 = bn::fixed_point(bn::display::width() / 2 - 20, -bn::display::height() / 2 + 30);
    const bn::fixed_point abilitybar_fill_position_2 = bn::fixed_point(position_2.x() - 48, position_2.y()+3);
    bn::sprite_ptr abilitybar_fill2 = bn::sprite_items::abilitybar_fill.create_sprite(abilitybar_fill_position_2);
    bn::sprite_ptr abilitybar_frame2 = bn::sprite_items::healthbar_frame.create_sprite(position_2.x() - 48, position_2.y());

    abilitybars()
    {
        abilitybar_frame2.set_horizontal_flip(true);
        abilitybar_fill2.set_horizontal_flip(true);

    }

    void set_ability_left(bn::fixed ability)
    {
        abilitybar_fill.set_horizontal_scale(bn::max(ability, bn::fixed(0.01)));
        abilitybar_fill.set_x(position_1.x() + map(ability, 0, 1, 16, 48));
    }

    void set_ability_right(bn::fixed ability)
    {
        abilitybar_fill2.set_horizontal_scale(bn::max(ability, bn::fixed(0.01)));
        abilitybar_fill2.set_position(abilitybar_fill_position_2.x() + 32 - ability * 32, abilitybar_fill_position_2.y());
    }    
};

struct healthbars
{
    bn::optional<bn::sprite_ptr> pictogram;
    bn::optional<bn::sprite_ptr> pictogram2;
    

    const bn::fixed_point position_1 = bn::fixed_point(-bn::display::width() / 2 + 20, -bn::display::height() / 2 + 20);
    bn::sprite_ptr boss_frame = bn::sprite_items::pictogram_frame.create_sprite(position_1);
    bn::sprite_ptr healthbar_fill = bn::sprite_items::healthbar_fill.create_sprite(position_1.x() + 48, position_1.y()+3);
    bn::sprite_ptr healthbar_frame = bn::sprite_items::healthbar_frame.create_sprite(position_1.x() + 48, position_1.y());

    const bn::fixed_point position_2 = bn::fixed_point(bn::display::width() / 2 - 20, -bn::display::height() / 2 + 20);
    const bn::fixed_point healthbar_fill_position_2 = bn::fixed_point(position_2.x() - 48, position_2.y()+3);
    bn::sprite_ptr boss_frame2 = bn::sprite_items::pictogram_frame.create_sprite(position_2);
    bn::sprite_ptr healthbar_fill2 = bn::sprite_items::healthbar_fill.create_sprite(healthbar_fill_position_2);
    bn::sprite_ptr healthbar_frame2 = bn::sprite_items::healthbar_frame.create_sprite(position_2.x() - 48, position_2.y());

    healthbars(bn::sprite_item boss_spr_item, bn::sprite_item boss_spr_item2):
        pictogram(boss_spr_item.create_sprite(-bn::display::width() / 2 + 20, -bn::display::height() / 2 + 20)),
        pictogram2(boss_spr_item2.create_sprite(bn::display::width() / 2 - 20, -bn::display::height() / 2 + 20))
    {
        pictogram->set_z_order(2);
        pictogram2->set_z_order(2);

        boss_frame2.set_horizontal_flip(true);
        healthbar_frame2.set_horizontal_flip(true);
        healthbar_fill2.set_horizontal_flip(true);
    }


    // 0 - 1
    void set_health_left(bn::fixed health)
    {
        healthbar_fill.set_horizontal_scale(bn::max(health, bn::fixed(0.01)));
        healthbar_fill.set_x(position_1.x() + map(health, 0, 1, 16, 48));
    }

    // 0 - 1
    void set_health_right(bn::fixed health)
    {
        healthbar_fill2.set_horizontal_scale(bn::max(health, bn::fixed(0.01)));
        healthbar_fill2.set_position(healthbar_fill_position_2.x() + 32 - health * 32, healthbar_fill_position_2.y());
        // healthbar_fill.set_x(position_2.x() + map(health, 0, 1, 16, 48));
    }
};




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
        bn::sprite_ptr props[] = {
            bn::sprite_items::wheel.create_sprite(327 - 256 + bn::display::width() / 2 + 32, 689 - 256 + bn::display::height() / 2 + 16)
        };

        for (auto &prop : props) {
            prop.set_camera(*camera);
            prop.set_z_order(-100);
        }

        // Animals
        zoop::bee bee;
        zoop::rat rat;

        BN_LOG("entering battle!!");

        // sky and mountains background
        background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
        background->set_z_order(4);
        background->set_camera(*camera);


        // BG and map
//        bn::regular_bg_item tilemap_item = bn::regular_bg_items::tilemap;
//        bn::fixed_point tilemap_position = bn::fixed_point(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
//        bn::regular_bg_ptr tilemap = tilemap_item.create_bg(tilemap_position);
//        tilemap.set_camera(*camera);


        // Trein
//        regular_bg_ptr trein_bg = regular_bg_items::trein_bg.create_bg(0,-188);
//        trein_bg.set_camera(*camera);
//        trein_bg.set_z_order(5);


        // Window for the train
//        bn::window outside_window = bn::window::outside();
//        outside_window.set_show_bg(trein_bg, false);
//        bn::rect_window internal_window = bn::rect_window::internal();
//        internal_window.set_boundaries(-0, -200, 392, 1024);
//        internal_window.set_camera(camera);

        BN_LOG("test");


        // Facade
//        bn::regular_bg_ptr facade = bn::regular_bg_items::facade.create_bg(0,0);
//        facade.set_camera(*camera);
        

        // Default characters
        if (!you) {
            you = new christine();
        }

        if (!other_player) {
            other_player = new fabian();
        }



        // Health bars
        healthbars bars = healthbars(you->avatar(), other_player->avatar());        
        abilitybars abilitybars;

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

            // Update animals
            bee.update();
            rat.update();


            // log_memory_usage();
            
//            printer->print_map_tiles_at_position(*map_item, you->sprite_ptr()->position());
            // printer->print("{} |nekfenwfjwklgenwnlgewknwe ");
//             printer->print_map_tile_and_position(*map_item, you->sprite_ptr()->position());
//             BN_LOG(props[0].position().x());

            // Update level
            // Lipje pickup items
            // for (size_t i = 0; i < 7; i++) {
            //     lipjes[i].update();
            // }

            // Moving clouds
            // clouds_x -=  0.1;
//            trein_bg.set_x(trein_bg.x() - 2);

            // clouds.set_x(clouds_x + player.position.x() / bn::fixed(40.0));


            // Move clouds/mountains bg parallax
            // sky.set_position(-player.position / bn::fixed(50.0));


            // Update player, send keypad to other players -----------
            multiplayer::keypad_data keypad_data_to_send = multiplayer::read_keys();

            // Always update own player
            you->update(frame, keypad_data_to_send.keypad_data);

            // Indoors and outdoors
            if (you->is_indoors()) {
                background->set_item(bn::regular_bg_items::background_indoors);
            } else {
                background->set_item(bn::regular_bg_items::background);
            }

            if (other_player->is_indoors() && !you->is_indoors()) {
                bn::blending::set_transparency_alpha(0.3);
                other_player->sprite_ptr()->set_blending_enabled(true);
            } else {
                other_player->sprite_ptr()->set_blending_enabled(false);
            }

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

            abilitybars.set_ability_left(you->get_ability() / you->max_ability);
            abilitybars.set_ability_right(other_player->get_ability() / other_player->max_ability);        

            // Back to character select
            if (bn::keypad::select_pressed() || multiplayer::other_player_keypad_data.keypad_data.select_pressed) {
                background.reset();
                bars.pictogram.reset();
                bars.pictogram2.reset();
                return next_scene::character_select;
            }

            // Win / lose
            if (you->get_health() <= 0 || other_player->get_health() <= 0) {
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
