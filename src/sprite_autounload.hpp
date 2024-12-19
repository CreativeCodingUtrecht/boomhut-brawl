#include "bn_sprite_ptr.h"

#include "globals.hpp"


struct sprite_autounload {
    bn::sprite_item spr_item;
    bn::fixed_point position;
    bn::optional<bn::sprite_ptr> spr;

    sprite_autounload(bn::sprite_item spr_item, bn::fixed_point position): spr_item(spr_item), position(position), spr(spr_item.create_sprite(position)) {
        spr->set_camera(*camera);
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
            spr->set_camera(*camera);
        }

        if (!should_be_visible && spr.has_value()) {
            spr.reset();
        }
    }
};