#pragma once

#include "bn_vector.h"
#include "bn_fixed_point.h"

#include "./characters/-character.hpp"

#include "bn_sprite_items_snowflake_smol.h"
#include "bn_sprite_items_snowflake.h"
#include "bn_sprite_items_snowball.h"



namespace snowballs {
    struct trail_snowflake {
        bn::sprite_ptr spr;
        int lifetime_left = 30;
        bn::fixed_point velocity;

        trail_snowflake(bn::fixed_point pos, bn::fixed_point vel):
            spr(bn::sprite_items::snowflake.create_sprite(pos)) {
                spr.set_camera(*camera);
                velocity = vel;
        }
    };


    struct snowball {
        character* creator;
        bn::sprite_ptr spr;
        int direction;

        bn::sprite_animate_action<2> anim;

        bn::vector<trail_snowflake, 3> trail;

        snowball(character *player, bn::fixed_point position, int dir): 
            creator(player),  
            spr(bn::sprite_items::snowball.create_sprite(position)),
            direction(dir),
            anim(bn::create_sprite_animate_action_forever(spr, 2, bn::sprite_items::snowball.tiles_item(), 1, 2)) {
                spr.set_camera(*camera);

        }
    };


    bn::vector<snowball, 20> snowballs;


    void spawn(character *creator, bn::fixed_point position, bool horizontal_flip) {
        int dir = horizontal_flip ? -1 : 1;
        if (!snowballs.full()) {
            snowball new_snowball = snowball(creator, position, dir);
            for (int i = 0; i < 3; i++) {
                auto flake = trail_snowflake(position, bn::fixed_point(global_random->get_fixed(0.5, 8) * dir, global_random->get_fixed(-0.5, 0.5)));
                new_snowball.trail.push_back(flake);
            }
            snowballs.push_back(new_snowball);
        }
    }

    void update_all() {
        // BN_LOG(snowballs.size());

        for (int i = 0; i < snowballs.size(); i++) {
            auto s = snowballs.at(i);

            s.anim.update();

            if (s.direction == -1) {
                s.spr.set_x(s.spr.x() - 8);
            } else {
                s.spr.set_x(s.spr.x() + 8);
            }

            for (auto flake : s.trail) {
                flake.spr.set_position(flake.spr.position() + flake.velocity);
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