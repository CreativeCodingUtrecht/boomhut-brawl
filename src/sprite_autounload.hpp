#pragma once


#include "bn_sprite_ptr.h"
#include "globals.hpp"


struct sprite_autounload {
    bn::sprite_item spr_item;
    bn::fixed_point position;
    bool horizontal_flip;
    int z_order = 0;

    bn::optional<bn::sprite_ptr> spr;

    sprite_autounload(bn::sprite_item spr_item, bn::fixed_point position): spr_item(spr_item), position(position), spr(spr_item.create_sprite(position)) {
        set_sprite_properties();
    }

    void set_sprite_properties() {
        spr->set_camera(*camera);
        spr->set_horizontal_flip(horizontal_flip);
        spr->set_z_order(z_order);
    }

    void set_position(bn::fixed_point pos) {
        position = pos;
        if (spr) {
            spr->set_position(pos);
        }
    }
    
    void update_visibility() {
        bool should_be_visible;


        if (abs(camera->x() - position.x()) < 140 && abs(camera->y() - position.y()) < 100) {
            should_be_visible = true;
        } else {
            should_be_visible = false;
        }

        BN_LOG(should_be_visible);

        if (should_be_visible && !spr.has_value()) {
            spr = spr_item.create_sprite(position);
            set_sprite_properties();
        }

        if (!should_be_visible && spr.has_value()) {
            spr.reset();
        }
    }
};