#pragma once

#include "bn_vector.h"
#include "bn_fixed_point.h"

#include "./characters/-character.hpp"

#include "bn_sprite_items_snowflake_smol.h"
#include "bn_sprite_items_snowball.h"



namespace snowballs {
    struct snowball {
        character* creator;
        bn::sprite_ptr spr;
        int direction;

        bn::vector<bn::sprite_ptr, 3> trail;

        snowball(character *creator, bn::fixed_point position, int direction): 
            creator(creator),  
            spr(bn::sprite_items::snowball.create_sprite(position)),
            direction(direction) {
                spr.set_camera(*camera);
        }
    };


    bn::vector<snowball, 20> snowballs;


    void spawn(character *creator, bn::fixed_point position, bool horizontal_flip) {
        if (!snowballs.full()) {
            snowball new_snowball = snowball(creator, position, horizontal_flip ? -1 : 1);
            snowballs.push_back(new_snowball);
        }
    }

    void update_all() {
        // BN_LOG(snowballs.size());

        for (int i = 0; i < snowballs.size(); i++) {
            auto s = snowballs.at(i);

            if (s.direction == -1) {
                s.spr.set_x(s.spr.x() - 7);
            } else {
                s.spr.set_x(s.spr.x() + 7);
            }
            
            s.spr.set_rotation_angle(clamp(s.spr.rotation_angle() + 50, 0, 360));

            for (character* c : players()) {
                if (c != s.creator && distance(s.spr.position(), c->sprite_ptr()->position()) < 12) {
                    c->apply_force(bn::fixed_point(5 * s.direction, 0));
                    c->take_damage(10);
                    c->sound_hit().play();
                    snowballs.erase(snowballs.begin() + i);
                }
            }
            
            if (s.spr.x() > bounds_max_x || s.spr.x() < bounds_min_x) {
                snowballs.erase(snowballs.begin() + i);
            }
        }
    }
}








// // STARS
//         if (keypad.b_pressed && !stars.full()) {
//             bn::sprite_ptr star = bn::sprite_items::cat_star.create_sprite(position);
//             star.set_camera(camera);
//             star.set_horizontal_flip(_sprite_ptr->horizontal_flip());
//             star.set_scale(0.1);
//             stars.push_back(star);
//             bn::sound_items::ice_info.play();
//         }

//         for (int i = 0; i < stars.size(); i++) {
//             auto s = stars.at(i);

//             if (s.horizontal_scale() < 1.0) {
//                 s.set_scale(s.horizontal_scale() + 0.1);
//             }

//             if (s.horizontal_flip()) {
//                 s.set_x(s.x() - 5);
//             } else {
//                 s.set_x(s.x() + 5);
//             }
            
//             s.set_rotation_angle(clamp(s.rotation_angle() + 10, 0, 360));
//             // s.set



//             for (character* c : players()) {
//                 if (c != this && distance(s.position(), c->sprite_ptr()->position()) < 16) {
//                     c->apply_force(bn::fixed_point(5, 0));
//                     c->take_damage(25);
//                     stars.erase(stars.begin() + i);
//                 }
//             }
            
//             if (s.x() > bounds_max_x || s.x() < bounds_min_x) {
//                 stars.erase(stars.begin() + i);
//             }
//         }