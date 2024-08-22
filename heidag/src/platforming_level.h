#pragma once

#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_sprite_text_generator.h"
#include "bn_point.h"
#include "bn_log.h"
#include "bn_format.h"
#include "bn_math.h"
#include "bn_display.h"
#include "bn_link.h"
#include "bn_link_state.h"
#include "bn_music.h"
#include "bn_audio.h"


// BGs
#include "bn_regular_bg_items_tilemap.h"
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_foreground.h"


// Includes
#include "../include/utils.h"
#include "globals.h"
#include "player.h"
#include "pickups.h"
#include "splash.h"
#include "main_menu.h"

#include "scene.h"





namespace platforming_level
{
    
    next_scene run()
    {
        bn::color background_color = bn::color(16, 24, 29);
        bn::regular_bg_item tilemap_item = bn::regular_bg_items::tilemap;
        bn::fixed_point tilemap_position = bn::fixed_point(bn::display::width() / 2, bn::display::height() / 2);

        // sky and mountains background
        bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2, bn::display::height() / 2);
        
        int clouds_x = 0.0;


        // pickups
        const bn::fixed x_offset = 120;
        const bn::fixed y_offset = 126;

        pickups::lipje lipjes[7] = 
        {
            pickups::lipje(0+x_offset,-y_offset/2),
            pickups::lipje(32+x_offset,-y_offset/2),
            pickups::lipje(64+x_offset,-y_offset/2),
            pickups::lipje(96+x_offset,-y_offset/2),
            pickups::lipje(32+x_offset,y_offset),
            pickups::lipje(64+x_offset,y_offset),
            pickups::lipje(96+x_offset,y_offset)
        };



        // Background
        bn::bg_palettes::set_transparent_color(background_color);
        

        // World
        const bn::fixed gravity = 0.3;

        // BG and map
        bn::regular_bg_ptr tilemap = tilemap_item.create_bg(tilemap_position);
        const bn::regular_bg_map_item& map_item = tilemap_item.map_item();


        // Foreground 
        // bn::regular_bg_ptr foreground = bn::regular_bg_items::foreground.create_bg(bn::display::width() / 2, bn::display::height() / 2);


        tilemap.set_camera(*camera);
        background.set_camera(*camera);
        // foreground.set_camera(*camera);



        // Player and other player, soon to be max. 4
        player you(*camera, gravity);
        player other_player(*camera, gravity);

        players.push_back(you);
        players.push_back(other_player);
        
        bn::fixed_point last_position;

        // Multiplayer
        int players_counter;
        int current_player_id;
        multiplayer::keypad_data last_keypad_data_to_send;


        while(true)
        {
            // Update level
            // Lipje pickup items
    
            printer->print_map_tiles_at_position(map_item, you.position);


            for (size_t i = 0; i < 7; i++)
            {
                lipjes[i].update();
            }

            // Moving clouds
            clouds_x -=  0.1;
            // clouds.set_x(clouds_x + player.position.x() / bn::fixed(40.0));


            // Move clouds/mountains bg parallax
            // sky.set_position(-player.position / bn::fixed(50.0));


            // Update player, send keypad to other players
            multiplayer::keypad_data keypad_data_to_send {
                keypad_data: multiplayer::keypad_data::keypad_data_struct {
                    l_pressed: bn::keypad::l_pressed(),
                    r_pressed: bn::keypad::r_pressed(),
                    a_pressed: bn::keypad::a_pressed(),
                    left_held: bn::keypad::left_held(),
                    right_held: bn::keypad::right_held()
                }
            };

            // Always update own player
            you.update(map_item , keypad_data_to_send.keypad_data);


            // Print map info when singleplayer
            if (players_counter == 0) {
                // map_info_printer.print_map_tiles_at_position(map_item, player.position);
                if (you.position != last_position) {
                    last_position = you.position;
                    // printer->print_map_tile_and_position(map_item, you.position);
                }
            }

            log_memory_usage();

            // Send if changed
            if (last_keypad_data_to_send.data != keypad_data_to_send.data) {
                bn::link::send(keypad_data_to_send.data);   
                last_keypad_data_to_send.data = keypad_data_to_send.data;
            }


            // Update other player, receive keypad from other players
            multiplayer::keypad_data other_player_keypad_data;

            if(bn::optional<bn::link_state> link_state = bn::link::receive())
            {
                const bn::link_player& first_other_player = link_state->other_players().front();
                other_player_keypad_data.data = first_other_player.data();

                BN_LOG(bn::format<40>("received: {}", other_player_keypad_data.data));                

                // Update multiplayer info text
                if (players_counter != link_state->player_count()) {
                    players_counter = link_state->player_count();
                    current_player_id = link_state->current_player_id();

                    // Immediately refresh the other player as well
                    bn::link::send(keypad_data_to_send.data);   
                    BN_LOG("change in link");                
                    bn::string<40> info_text = bn::format<40>("players: {}, player id: {}", players_counter, current_player_id);
                    printer->print(info_text);
                }
            }
            
            // always update for animations
            other_player.update(map_item, other_player_keypad_data.keypad_data);


            // Smooth cam
            camera_follow_smooth(*camera, you.sprite_ptr.position());

            if (bn::keypad::start_pressed()) {
                bn::music::stop();
                players.clear();
                return next_scene::main_menu;
            }

            bn::core::update();
        }
    }
}
