#pragma once

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_display.h"

#include "scene.hpp"
#include "globals.hpp"

// Sprites
#include "bn_sprite_items_snowflake.h"
#include "bn_sprite_items_snowflake_smol.h"

#include "bn_regular_bg_items_background.h"


namespace christmas
{
    // Snow particles
    struct snowflake
    {
        bn::fixed_point pos = bn::fixed_point(0,0);
        bn::fixed x_pos = global_random->get_fixed(0, bn::display::width());
        bn::fixed initial_angle = global_random->get_fixed(0, 360);
        bn::fixed size = global_random->get_fixed(0.5, 1);
        bn::sprite_ptr spr;

        snowflake(bn::sprite_item s): spr(s.create_sprite(pos)) {
            spr.set_camera(camera);
        }

        void update_and_draw(bn::fixed time) {
            spr.set_x(x_pos + 40.0 * sin(initial_angle + time));

            bn::fixed y_speed = 1 / size;
            spr.set_y(spr.y() + y_speed);

            if (spr.y() > bn::display::height()) {
                spr.set_y(camera->y() - bn::display::height()/2);
                x_pos = global_random->get_fixed(camera->x() - bn::display::width() / 2, camera->x() + bn::display::width() / 2);
            }
        }
    };


    bn::vector<snowflake, 40> snowflakes;


    next_scene run()
    {
        bn::fixed t = 0;

        // Generate 20 snowflakes
        for (int i = 0; i < 40; ++i) {
            bool smol = global_random->get_bool();
            snowflake s = snowflake(smol ? bn::sprite_items::snowflake : bn::sprite_items::snowflake_smol);
            snowflakes.push_back(s);
        }

        bn::sprite_ptr spr = bn::sprite_items::snowflake.create_sprite(camera->position());
        spr.set_camera(camera);

        background = bn::regular_bg_items::background.create_bg(bn::display::width() / 2 + 256, bn::display::height() / 2 + 256);
        background->set_z_order(4);
        background->set_camera(*camera);


        while (true) {
            t += 0.001;


			for (snowflake &s : snowflakes) {
                s.update_and_draw(t);
            }

            bn::core::update();
        }

        return next_scene::main_menu;
    }
}