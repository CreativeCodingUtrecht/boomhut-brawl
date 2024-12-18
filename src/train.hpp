#include "globals.hpp"

#include "bn_sprite_items_trein_kop.h"
#include "bn_sprite_items_trein_middel.h"



struct train
{   
    bn::fixed_point position = bn::fixed_point(100,69);
    bn::sprite_ptr head = bn::sprite_items::trein_kop.create_sprite(position.x() - 52.0, position.y());
    bn::sprite_ptr middle = bn::sprite_items::trein_middel.create_sprite(position.x(), position.y());
    bn::sprite_ptr tail = bn::sprite_items::trein_kop.create_sprite(position.x() + 51, position.y());

    train() {
        head.set_camera(camera);
        middle.set_camera(camera);
        tail.set_camera(camera);

        tail.set_horizontal_flip(true);
    }

    void update() {
        position.set_x(position.x() - 4);

        // Back to start 
        if (position.x() < -1200) {
            position.set_x(global_random->get_fixed(1000, 2000));
        }

        head.set_position(position.x() - 52.0, position.y());
        middle.set_position(position.x(), position.y());
        tail.set_position(position.x() + 51.0, position.y());
    }   
};
