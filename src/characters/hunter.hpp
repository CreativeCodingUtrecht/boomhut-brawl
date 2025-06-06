#pragma once

#include "-character.hpp"

#include "bn_sprite_items_hunter.h"
#include "bn_sprite_items_avatar_hunter.h"
#include "bn_sprite_items_hunter_arrow.h"
#include "bn_sprite_items_hunter_arrow_avatar.h"
#include "bn_sound_items.h"


struct hunter: public character {
    // General ----------------------------------
    bn::string<20> name() {
        return "Hunter";
    }

    bn::sprite_item avatar() {
        return bn::sprite_items::avatar_hunter;
    }

    bn::optional<weapon_info> get_weapon_info() {
        return weapon_info {
            .name = "arrow",
            .avatar = bn::sprite_items::hunter_arrow_avatar
        };
    }

    // Health -----------------------------------
    bn::fixed max_health() {
        return 100;
    };

    bn::fixed run_speed() {
        return .65;
    };

    bn::fixed jump_velocity() {
        return -7;
    };

    // Sounds -----------------------------------
    bn::sound_item sound_naam() {
        return bn::sound_items::niels_naam;
    }

    bn::sound_item sound_tagline() {
        return bn::sound_items::niels_tagline;
    }

    bn::sound_item sound_jump() {
        return bn::sound_items::niels_jump;
    }

    bn::sound_item sound_hit() {
        return bn::sound_items::niels_hit;
    }

    bn::sound_item sound_win() {
        return bn::sound_items::niels_wins;
    }


    // Health -----------------------------------
    bn::fixed health = max_health();
    bn::fixed get_health() {
        return health;
    }

    void take_damage(bn::fixed amount) {
        mosaic_timer = 30;
        _sprite_ptr->set_mosaic_enabled(true);
        health -= amount;
    }

    // Ability ----------------------------------

    bn::fixed_point position = spawn_point;
    bn::fixed_point velocity;


    int mosaic_timer = 30;

    void apply_force(bn::fixed_point point) {
        velocity += point;
    }

    bool is_jumping;
    bool is_running;
    bool flipped;
    bool is_landing;
    bool is_falling;


    int spr_y_offset = 2;


    // Sprite -----------------------------------
    bn::sprite_item sprite_item()  {
        return bn::sprite_items::hunter;
    };

    bn::optional<bn::sprite_ptr>_sprite_ptr = sprite_item().create_sprite(spawn_point);
    bn::optional<bn::sprite_ptr> sprite_ptr() {
        return _sprite_ptr;
    };

    
    // Animations -------------------------------
    bn::optional<bn::sprite_animate_action<6>> attack_anim_load = bn::create_sprite_animate_action_once(*_sprite_ptr, 1, bn::sprite_items::hunter.tiles_item(), 
        181, 182, 183, 184, 185, 186
    );

    bn::optional<bn::sprite_animate_action<18>> attack_anim_unload = bn::create_sprite_animate_action_once(*_sprite_ptr, 1, bn::sprite_items::hunter.tiles_item(), 
        187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204
    );
    
    virtual character_animations animations() override {
        return character_animations {
            .idle = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, bn::sprite_items::hunter.tiles_item(),
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122
            ),
            .run = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, sprite_item().tiles_item(),
                123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135
            ),
            .jump_up = bn::create_sprite_animate_action_once(*_sprite_ptr, 1, sprite_item().tiles_item(),
                136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157
            ),
            .jump_stay = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, sprite_item().tiles_item(),
                158, 158 
            ),
            .jump_down = bn::create_sprite_animate_action_once(*_sprite_ptr, 1, sprite_item().tiles_item(),
                159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180
            )
        };
    }

    bn::optional<character_animations> anims = animations();

    hunter() {
        set_ability_frame_delay(16);
    }

    void unload() {
        anims.reset();
        attack_anim_load.reset();
        attack_anim_unload.reset();
        _sprite_ptr.reset();
    }
    
    bool _preview_mode;
    void set_preview_mode(bool on_or_off) {
        _preview_mode = on_or_off;
    }

    bool _is_indoors = false;
    bool is_indoors() {
        return _is_indoors;
    }


    // weapon
    bool is_aiming;
    bool is_unloading;
    int max_aiming_countdown = 60;
    int aiming_countdown = 60;

   struct arrow {
        bn::sprite_ptr spr;
        int direction;
    };

    bn::vector<arrow, 10> arrows;



    void update(multiplayer::keypad_data::keypad_data_struct keypad) {
        if (_preview_mode) {
            anims->idle.update();
            return;
        }

        // Snowballs!
        if (keypad.b_pressed) {
            snowballs::spawn(this, position, _sprite_ptr->horizontal_flip());
        }

        if (mosaic_timer > 0) {
            mosaic_timer--;
            bn::sprites_mosaic::set_stretch(map(mosaic_timer, 30, 0, 1, 0));
        } else {
            _sprite_ptr->set_mosaic_enabled(false);
        }

        _is_indoors = false;


        // Watch for gravity
        int player_tile_index = get_map_tile_index_at_position(position, *map_item); 

        bool on_ground = true;
        bool on_wall = false;

        // BN_LOG(bn::format<20>("tile: {}", player_tile_index));

        // check if fallthrough tile
        for (int tile_index: passthrough_tiles) {
            if (player_tile_index == tile_index) {
                on_ground = false;
            }
        }
        
        // check if wall tile
        for (int tile_index: wall_tiles) {
            if (player_tile_index == tile_index) {
                on_wall = true;
            }
        }

        // check if indoors
        for (int tile_index: indoor_tiles) {
            if (player_tile_index == tile_index) {
                _is_indoors = true;
            }
        }


        // platform beneath player 
        if (on_ground && !on_wall) {
            if ((is_jumping) && velocity.y() > 0) {
                is_jumping = false;
                is_landing = true;
            }

            if (is_falling) {
                is_falling = false;
                is_landing = true;
            }

            velocity.set_y(bn::min(bn::fixed(0.0), velocity.y()));
        }
        // can fall
        else {
            velocity.set_y(velocity.y() + gravity);
            is_falling = true;
        }

        // BN_LOG(on_wall);

        // jumping and gravity
        if (keypad.a_pressed && !is_jumping && on_ground && !on_wall) {
            sound_jump().play();
            is_jumping = true;
            is_landing = false;
            velocity.set_y(jump_velocity());
            anims->jump_down.reset();
            anims->jump_up.reset();
        }
        // running
        if (keypad.left_held) {
            is_landing = false;
            velocity.set_x(velocity.x() - run_speed());
            _sprite_ptr->set_horizontal_flip(true);
            if (on_ground) {
                is_running = true;
                is_landing = false;
            }
        }

        //ability
        if (keypad.l_pressed) {
            if (ability >= 100) {
                ability = 0;
                // Do ability
            }
        }

        if (keypad.right_held) {
            velocity.set_x(velocity.x() + run_speed());
            if (on_ground) {
                is_running = true;
                is_landing = false;
            }
            _sprite_ptr->set_horizontal_flip(false);
        }
        
        if (!keypad.left_held && !keypad.right_held) {
            if (is_running) {
                is_running = false;
            }
        }


        // Apply velocity to position
        position += velocity;
        // BN_LOG(velocity.x());
        bn::fixed drg = .85;
        velocity.set_x(velocity.x() * drg);

        // Map bounds
        position.set_x(constrain(position.x(), bounds_min_x, bounds_max_x));
        position.set_y(constrain(position.y(), bounds_min_y, bounds_max_y));

        _sprite_ptr->set_x(position.x());
        _sprite_ptr->set_y(position.y() + spr_y_offset);



        // Aiming!
        // if (keypad.b_pressed) {
        // }
        // if (keypad.b_held) {
        //     is_aiming = true;
        //     // Shoot!
        //     if (aiming_countdown == 0) {
                
        //     } else {
        //         aiming_countdown--;
        //     }
        // }
        // if (!keypad.b_held && is_aiming) {
        //     is_aiming = false;
        //     bn::sound_items::hunter_bow.play_with_priority(3000);
        //     attack_anim_load->reset();
        //     aiming_countdown = 60;
        //     arrow new_arrow = arrow {
        //         .spr = bn::sprite_items::hunter_arrow.create_sprite(position.x(), position.y() - 8),
        //         .direction = _sprite_ptr->horizontal_flip() ? -1 : 1
        //     };

        //     new_arrow.spr.set_camera(camera);
        //     arrows.push_back(new_arrow);
        // }

        // // Animate arrow
        // for (int i = 0; i < arrows.size(); i++) {
        //     arrow a = arrows.at(i);
        //     a.spr.set_x(a.spr.x() + 10 * a.direction);
        //     a.spr.set_horizontal_flip(a.direction == -1);

        //     BN_LOG(you == this);
            
        //     // hitting people
        //     for (character* p : players()) {
        //         if (p != this && distance(a.spr.position(), p->sprite_ptr()->position()) < 32) {
        //             p->sound_hit().play();
        //             arrows.erase(arrows.begin() + i);
        //             p->take_damage(10);
        //             bn::fixed f = 10;
        //             p->apply_force(bn::fixed_point(f * a.direction, 0));
        //         }
        //     }

        //     if (a.spr.x() > bounds_max_x || a.spr.x() < bounds_min_x) {
        //         arrows.erase(arrows.begin() + i);
        //     }
        // }
        
        // Update the right animation
        if (is_aiming) {
            if (!attack_anim_load->done()) {
                attack_anim_load->update();
            } else {
                is_unloading = true;
            }
        } 
        else if (is_unloading) {
            if (!attack_anim_unload->done()) {
                attack_anim_unload->update();
            } else {
                is_unloading = false;
                attack_anim_unload->reset();
            }
        }
        else if (is_falling && !is_jumping && !is_landing) {
            anims->jump_stay.update();
        }
        else if (is_running && !is_jumping) {
            anims->run.update();
        }
        else if (is_jumping) {
            if (anims->jump_up.done()) {
                anims->jump_stay.update();
            } else {
                anims->jump_up.update();
            }
        } else if (is_landing && !anims->jump_down.done()) {
            anims->jump_down.update();
        }
        else {
            anims->idle.update();
        }
    } 
};

