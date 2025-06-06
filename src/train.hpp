#pragma once

#include "globals.hpp"

#include "bn_sprite_items_trein_kop_smol.h"
#include "bn_sprite_items_trein_middel_smol.h"

#include "bn_sound_items.h"

struct wagon 
{
    bn::fixed_point position;
    bn::sprite_ptr head, middle, tail;

    wagon(bn::fixed_point pos): 
        position(pos),
        head(bn::sprite_items::trein_kop_smol.create_sprite(pos.x() - 16.0, pos.y())),
        middle(bn::sprite_items::trein_middel_smol.create_sprite(pos.x(), pos.y())),
        tail(bn::sprite_items::trein_kop_smol.create_sprite(pos.x() + 16, pos.y())) {

        head.set_camera(*camera);
        middle.set_camera(*camera);
        tail.set_camera(*camera);

        tail.set_horizontal_flip(true);

        head.set_z_order(100);
        middle.set_z_order(100);
        tail.set_z_order(100);
    }

    void set_x(bn::fixed x) {
        position.set_x(x);
        head.set_x(x - 16.0);
        middle.set_x(x);
        tail.set_x(x + 16.0);
    }
};


struct train
{   
    bool played_sound = true;
    int x_between_wagons = 95;
    bn::fixed_point position = bn::fixed_point(2200,75);
    int speed = 4;
    
    wagon wagons[3] = {
        wagon(bn::fixed_point(position.x() - x_between_wagons, position.y())),
        wagon(bn::fixed_point(position.x(), position.y())),
        wagon(bn::fixed_point(position.x() + x_between_wagons, position.y())),
    };

    train() {
       
    }


    void update() {
        // BN_LOG(position.x());

        // Move position of train and wagons
        position.set_x(position.x() - speed);

        for (wagon &w : wagons) {
            w.set_x(w.position.x()-speed);
        }


        // Play sound when train gets near
        if (abs(position.x() - camera->x()) < 750 && !played_sound) {
            bn::sound_items::train.play();
            played_sound = true;
        }

        // Back to start 
        if (position.x() < -1200) {
            played_sound = false;
            // position.set_x(global_random->get_fixed(1000, 2000)); // Random position
            position.set_x(2000);
            wagons[0].set_x(position.x() - x_between_wagons);
            wagons[1].set_x(position.x());
            wagons[2].set_x(position.x() + x_between_wagons);
        }
    }   
};
