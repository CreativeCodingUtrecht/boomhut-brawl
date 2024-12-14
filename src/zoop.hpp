#pragma once

#include "bn_core.h"
#include "bn_point.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"
#include "bn_keypad.h"
#include "bn_regular_bg_map_item.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_builder.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_log.h"
#include "bn_vector.h"

#include "bn_sprite_items_bee.h"
#include "bn_sprite_items_rat.h"
#include "bn_sprite_items_snowflake.h"
#include "bn_sprite_items_snowflake_smol.h"

#include "globals.hpp"


using namespace bn;




namespace zoop
{
    struct rat
    {
        sprite_ptr sprite = sprite_items::rat.create_sprite(244,186);    
        
        rat() {
            sprite.set_camera(camera);
        }

        void update() {

        }
    };


    struct bee
    {
        sprite_ptr sprite = sprite_items::bee.create_sprite(0,20);    
        sprite_animate_action<2> anim = bn::create_sprite_animate_action_forever(sprite, 1, sprite_items::bee.tiles_item(), 0, 1);

        bee() {
            sprite.set_camera(camera);
        }

        void update() {
            anim.update();
            sprite.set_x(sprite.x() + global_random->get_fixed(-1.0, 1.0));
            sprite.set_y(sprite.x() + global_random->get_fixed(-1.0, 1.0));
        }
    };



}


// Snow particles
struct snowflake
{
    bn::fixed_point pos = bn::fixed_point(0,camera->y() - bn::display::height()/2);
    bn::fixed x_pos = global_random->get_fixed(camera->x() - bn::display::width() / 2, camera->x() + bn::display::width() / 2);
    bn::fixed initial_angle = global_random->get_fixed(0, 360);
    bn::fixed size = global_random->get_fixed(0.5, 1);
    bn::sprite_ptr spr;

    snowflake(bn::sprite_item s): spr(s.create_sprite(pos)) {
        spr.set_camera(camera);
    }

    void update_and_draw(bn::fixed time) {
        spr.set_x(x_pos + 40.0 * sin(initial_angle + time));

        bn::fixed y_speed = 2 / size;
        spr.set_y(spr.y() + y_speed);

        if (spr.y() > camera->y() + bn::display::height() / 2) {
            spr.set_y(camera->y() - bn::display::height()/2);
            x_pos = global_random->get_fixed(camera->x() - bn::display::width() / 2, camera->x() + bn::display::width() / 2);
        }
    }
};

struct snow {
    bn::vector<snowflake, 40> snowflakes;
    bn::fixed t = 0;

    snow() {
        // Generate snowflakes
        for (int i = 0; i < 40; ++i) {
            bool smol = global_random->get_bool();
            snowflake s = snowflake(smol ? bn::sprite_items::snowflake : bn::sprite_items::snowflake_smol);
            snowflakes.push_back(s);
        }
    }

    void draw_and_update() {
        t += 0.001;
        for (snowflake &s : snowflakes) {
            s.update_and_draw(t);
        }
    }
};


// Global snow 
bn::optional<snow> global_snow;