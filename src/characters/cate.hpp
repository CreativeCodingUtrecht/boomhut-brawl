#pragma once

#include "-character.hpp"

#include "bn_sprite_items_cate.h"
#include "bn_sprite_items_avatar_cate.h"
#include "bn_sound_items.h"

#include "bn_sprites_mosaic_actions.h"

#include "bn_sprite_items_cat_star.h"



struct cate: public character {
    // General ----------------------------------
    bn::string<20> name() {
        return "Space Bard";
    }

    bn::sprite_item avatar() {
        return bn::sprite_items::avatar_cate;
    }

    bn::optional<weapon_info> get_weapon_info() { return bn::optional<weapon_info>(); }
    

    // Stats ------------------------------------
    bn::fixed max_health() {
        return 100;
    };

    bn::fixed run_speed() {
        return .75;
    };

    bn::fixed jump_velocity() {
        return -7;
    };



    // Sounds -----------------------------------
    bn::sound_item sound_naam() {
        return bn::sound_items::cat_naam;
    }

    bn::sound_item sound_tagline() {
        return bn::sound_items::cat_tagline;
    }

    bn::sound_item sound_jump() {
        return bn::sound_items::cat_jump;
    }

    bn::sound_item sound_hit() {
        return bn::sound_items::cat_hit;
    }

    bn::sound_item sound_win() {
        return bn::sound_items::cat_wins;
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


    bn::fixed_point position = spawn_point;;
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


    // Sprite -----------------------------------
    bn::sprite_item sprite_item()  {
        return bn::sprite_items::cate;
    };

    bn::optional<bn::sprite_ptr>_sprite_ptr = sprite_item().create_sprite(spawn_point);
    bn::optional<bn::sprite_ptr> sprite_ptr() {
        return _sprite_ptr;
    };


    // Animations -------------------------------
    virtual character_animations animations() override {
        return character_animations {
            .idle = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, bn::sprite_items::cate.tiles_item(),
                59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458
            ),
            .run = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, sprite_item().tiles_item(),
                38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55
            ),
            .jump_up = bn::create_sprite_animate_action_once(*_sprite_ptr, 1, sprite_item().tiles_item(),
                56, 57, 58, 59, 60
            ),
            .jump_stay = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, sprite_item().tiles_item(),
                61, 61
            ),
            .jump_down = bn::create_sprite_animate_action_once(*_sprite_ptr, 1, sprite_item().tiles_item(),
                62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83
            )
        };
    }

    bn::optional<character_animations> anims = animations();

    cate() {
        _sprite_ptr->set_mosaic_enabled(true);
    }

    void unload() {
        anims.reset();
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


    // Stars!
    bn::vector<bn::sprite_ptr, 2> stars;

    void update(multiplayer::keypad_data::keypad_data_struct keypad) {
        if (_preview_mode) {
            anims->idle.update();
            return;

        }

        // Snowballs!
        if (keypad.b_pressed) {
            snowballs::spawn(this, position, _sprite_ptr->horizontal_flip());
        }


        // // STARS
        // if (keypad.b_pressed && !stars.full()) {
        //     bn::sprite_ptr star = bn::sprite_items::cat_star.create_sprite(position);
        //     star.set_camera(camera);
        //     star.set_horizontal_flip(_sprite_ptr->horizontal_flip());
        //     star.set_scale(0.1);
        //     stars.push_back(star);
        //     bn::sound_items::ice_info.play();
        // }

        // for (int i = 0; i < stars.size(); i++) {
        //     auto s = stars.at(i);

        //     if (s.horizontal_scale() < 1.0) {
        //         s.set_scale(s.horizontal_scale() + 0.1);
        //     }

        //     if (s.horizontal_flip()) {
        //         s.set_x(s.x() - 5);
        //     } else {
        //         s.set_x(s.x() + 5);
        //     }
            
        //     s.set_rotation_angle(clamp(s.rotation_angle() + 10, 0, 360));
        //     // s.set



        //     for (character* c : players()) {
        //         if (c != this && distance(s.position(), c->sprite_ptr()->position()) < 16) {
        //             c->apply_force(bn::fixed_point(5, 0));
        //             c->take_damage(25);
        //             stars.erase(stars.begin() + i);
        //         }
        //     }
            
        //     if (s.x() > bounds_max_x || s.x() < bounds_min_x) {
        //         stars.erase(stars.begin() + i);
        //     }
        // }

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
        bn::fixed drg = .85;
        velocity.set_x(velocity.x() * drg);

        // Map bounds
        position.set_x(constrain(position.x(), bounds_min_x, bounds_max_x));
        position.set_y(constrain(position.y(), bounds_min_y, bounds_max_y));

        _sprite_ptr->set_position(position);

        // Update the right animation
        if (is_falling && !is_jumping && !is_landing) {
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

