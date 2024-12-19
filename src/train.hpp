#include "globals.hpp"

#include "bn_sprite_items_trein_kop_smol.h"
#include "bn_sprite_items_trein_middel_smol.h"


struct wagon 
{
    bn::fixed_point position;
    bn::sprite_ptr head, middle, tail;

    wagon(bn::fixed_point position): 
        head(bn::sprite_items::trein_kop_smol.create_sprite(position.x() - 16.0, position.y())),
        middle(bn::sprite_items::trein_middel_smol.create_sprite(position.x(), position.y())),
        tail(bn::sprite_items::trein_kop_smol.create_sprite(position.x() + 16, position.y())) {

        head.set_camera(camera);
        middle.set_camera(camera);
        tail.set_camera(camera);

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
    int x_between_wagons = 95;
    bn::fixed_point position = bn::fixed_point(100,75);
    
    wagon wagons[3] = {
        wagon(bn::fixed_point(position.x() - x_between_wagons, position.y())),
        wagon(bn::fixed_point(position.x(), position.y())),
        wagon(bn::fixed_point(position.x() + x_between_wagons, position.y())),
    };

    train() {
       
    }

    void update() {
        for (wagon &w : wagons) {
            w.set_x(w.position.x()-4);
        }

        position.set_x(position.x() - 4);

        // Back to start 
        if (position.x() < -1200) {
            position.set_x(global_random->get_fixed(1000, 2000));
            wagons[0].set_x(position.x() - x_between_wagons);
            wagons[1].set_x(position.x());
            wagons[2].set_x(position.x() + x_between_wagons);
        }
    }   
};
