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


// BGs
#include "bn_regular_bg_items_tilemap.h"
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_foreground.h"
#include "bn_regular_bg_items_trein_bg.h"


// Sprites
#include "bn_sprite_items_pictogram_frame.h"
#include "bn_sprite_items_healthbar_fill.h"
#include "bn_sprite_items_healthbar_frame.h"
#include "bn_sprite_items_rein_pictogram.h"
#include "bn_sprite_items_hunter_pictogram.h"



// Includes
#include "../../include/utils.h"
#include "globals.h"
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
#include "pickups.h"
#include "splash.h"
#include "main_menu.h"
#include "zoop.h"

#include "scene.h"


using namespace bn;


struct healthbars
{
    bn::sprite_ptr pictogram;
    // bn::sprite_ptr pictogram2;

    const bn::fixed_point position_1 = bn::fixed_point(-bn::display::width() / 2 + 12, -bn::display::height() / 2 + 20);
    bn::sprite_ptr boss_frame = bn::sprite_items::pictogram_frame.create_sprite(position_1);
    bn::sprite_ptr healthbar_fill = bn::sprite_items::healthbar_fill.create_sprite(position_1.x() + 48, position_1.y()+3);
    bn::sprite_ptr healthbar_frame = bn::sprite_items::healthbar_frame.create_sprite(position_1.x() + 48, position_1.y());

    bn::fixed_point position_2 = bn::fixed_point(-bn::display::width() / 2 + 24, -bn::display::height() / 2 + 24);;
    bn::sprite_ptr boss_frame2 = bn::sprite_items::pictogram_frame.create_sprite(bn::display::width() / 2 + 24, bn::display::height() / 2 + 24);
    bn::sprite_ptr healthbar_fill2 = bn::sprite_items::healthbar_fill.create_sprite(position_2.x() - 48, position_2.y()+3);
    bn::sprite_ptr healthbar_frame2 = bn::sprite_items::healthbar_frame.create_sprite(position_2.x() - 48, position_2.y());

    healthbars(bn::sprite_item boss_spr_item, bn::sprite_item boss_spr_item2):
        pictogram(boss_spr_item.create_sprite(-bn::display::width() / 2 + 12, -bn::display::height() / 2 + 20))
    {
        pictogram.set_z_order(-1);
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
        healthbar_fill.set_horizontal_scale(bn::max(health, bn::fixed(0.01)));
        // healthbar_fill.set_x(position_2.x() + map(health, 0, 1, 16, 48));
    }
};




namespace platforming_level
{
    
    next_scene run()
    {
        int clouds_x = 0.0;


        // pickups
        const bn::fixed x_offset = 120;
        const bn::fixed y_offset = 126;

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


        // Animals
        zoop::bee bee;
        zoop::rat rat;




        // World
        const bn::fixed gravity = 0.3;


        // sky and mountains background
        // bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
        // background.set_z_order(4);
        // background.set_camera(*camera);


        // // BG and map
        bn::regular_bg_item tilemap_item = bn::regular_bg_items::tilemap;
        bn::fixed_point tilemap_position = bn::fixed_point(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
        bn::regular_bg_ptr tilemap = tilemap_item.create_bg(tilemap_position);
        const bn::regular_bg_map_item& map_item = tilemap_item.map_item();
        tilemap.set_camera(*camera);
        // tilemap.set_wrapping_enabled(false);
        // tilemap.set_z_order(-1000);


   
        // bn::rect_window internal_window = bn::rect_window();
        // internal_window.set_boundaries(-48, -96, 48, 96);
        // internal_window.set_visible(true);
        // internal_window.set_camera(camera);
        // tilemap.set_visible_in_window(true, internal_window);


  

        // Trein
        regular_bg_ptr trein_bg = regular_bg_items::trein_bg.create_bg(0,-188);
        trein_bg.set_camera(*camera);
        trein_bg.set_z_order(5);


        // Window for the train
        bn::window outside_window = bn::window::outside();
        outside_window.set_show_bg(trein_bg, false);
        bn::rect_window internal_window = bn::rect_window::internal();
        internal_window.set_boundaries(-0, -200, 392, 1024);
        internal_window.set_camera(camera);

        BN_LOG("test");


        // Foreground 
        // bn::regular_bg_ptr foreground = bn::regular_bg_items::foreground.create_bg(bn::display::width() / 2, bn::display::height() / 2);


        // background.set_camera(*camera);
        // foreground.set_camera(*camera);

        auto fab = fabian();

        character* you;
        // character* other_player = &fab;

        you = &fab;

        // BN_LOG(bn::format<> you->name());

        printer->print(you->name());


        // Create player and other player 
        // if (selected_you == all_characters::cate) {
        //     auto p = cate();
        //     you = &p;
        // }
        // if (selected_you == all_characters::christine) {
        //     auto p = christine();
        //     you = &p;
        // }
        // if (selected_you == all_characters::fabian) {
        //     auto p = fabian();
        //     you = &p;
        // }
        // if (selected_you == all_characters::fleur) {
        //     auto p = fleur();
        //     you = &p;
        // }
        // if (selected_you == all_characters::hunter) {
        //     auto p = hunter();
        //     you = &p;
        // }
        // if (selected_you == all_characters::joost) {
        //     auto p = joost();
        //     you = &p;
        // }
        // if (selected_you == all_characters::laury) {
        //     auto p = laury();
        //     you = &p;
        // }
        // if (selected_you == all_characters::mar) {
        //     auto p = mar();
        //     you = &p;
        // }
        // if (selected_you == all_characters::networkninja) {
        //     auto p = networkninja();
        //     you = &p;
        // }
        // if (selected_you == all_characters::rein) {
        //     auto p = rein();
        //     you = &p;
        // }
        // if (selected_you == all_characters::saskia) {
        //     auto p = saskia();
        //     you = &p;
        // }
        // if (selected_you == all_characters::saskia) {
        //     auto p = sietse();
        //     you = &p;
        // }
        // if (selected_you == all_characters::sjef) {
        //     auto p = sjef();
        //     you = &p;
        // }
        // if (selected_you == all_characters::werner) {
        //     auto p = werner();
        //     you = &p;
        // }


        // selected_other = all_characters::fabian;
        // if (selected_other == all_characters::cate) {
        //     cate o = cate();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::christine) {
        //     auto o = christine();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::fabian) {
        //     auto o = fabian();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::fleur) {
        //     auto o = fleur();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::hunter) {
        //     auto o = hunter();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::joost) {
        //     auto o = joost();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::laury) {
        //     auto o = laury();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::mar) {
        //     auto o = mar();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::networkninja) {
        //     auto o = networkninja();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::rein) {
        //     auto o = rein();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::saskia) {
        //     auto o = saskia();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::saskia) {
        //     auto o = sietse();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::sjef) {
        //     auto o = sjef();
        //     players.push_back(&o);
        // }
        // if (selected_other == all_characters::werner) {
        //     auto o = werner();
        //     players.push_back(&o);
        // }

        // auto you = players.at(0);
        // auto other_player = players.at(1);


        // auto p = fabian();
        // auto o = laury();
        players.push_back(you);
        // players.push_back(other_player);


        // Health
        healthbars bars = healthbars(bn::sprite_items::rein_pictogram, bn::sprite_items::hunter_pictogram);
        // healthbar other_healthbar = healthbar(bn::sprite_items::hunter_pictogram, true);
        



        // Camera
        you->sprite_ptr().set_camera(*camera);
        // other_player->sprite_ptr.set_camera(*camera);
        camera->set_position(you->sprite_ptr().position());

        // Health bars


        while(true)
        {
            // Update animals
            // bee.update();
            // rat.update();
            

    
            // printer->print_map_tiles_at_position(map_item, you.position);
            // printer->print_map_tile_and_position(map_item, you.position);

            // Update level
            // Lipje pickup items
            // for (size_t i = 0; i < 7; i++) {
            //     lipjes[i].update();
            // }

            // Moving clouds
            // clouds_x -=  0.1;
            // trein_bg.set_x(trein_bg.x() - 2);

            // clouds.set_x(clouds_x + player.position.x() / bn::fixed(40.0));


            // Move clouds/mountains bg parallax
            // sky.set_position(-player.position / bn::fixed(50.0));


            // Update player, send keypad to other players -----------
            multiplayer::keypad_data keypad_data_to_send = multiplayer::read_keys();

            // Always update own player
            you->update(keypad_data_to_send.keypad_data);

            // // log_memory_usage();

            // // Send if changed
            // multiplayer::send_if_changed(keypad_data_to_send);


            // // Update other player, receive keypad from other players
            // multiplayer::receive_keypad_data();

            // // always update for animations
            // // other_player->update(multiplayer::other_player_keypad_data.keypad_data);


            // // Smooth cam
            camera_follow_smooth(*camera, you->sprite_ptr().position());
            camera->set_x(constrain(camera->x(), 0, bounds_max_x)); // Constrain camera bounds

            // if (bn::keypad::start_pressed()) {
            //     bn::music::stop();
            //     players.clear();
            //     return next_scene::main_menu;
            // }

            bn::core::update();
        }
    }
}
