#pragma once

#include "-character.h"


#include "bn_sprite_items_fleur.h"
#include "bn_sprite_items_avatar_fleur.h"
#include "bn_sound_items.h"


struct fleur: public character {
    virtual bn::string<20> name() {
        return "Fleur";
    }

    bn::sprite_item avatar() {
        return bn::sprite_items::avatar_fleur;
    }


    bn::sound_item sound_naam() {
        return bn::sound_items::fleur_naam;
    }

    bn::sound_item sound_tagline() {
        return bn::sound_items::fleur_tagline;
    }

    bn::sound_item sound_jump() {
        return bn::sound_items::fleur_jump;
    }

    bn::sound_item sound_hit() {
        return bn::sound_items::fleur_hit;
    }

    bn::optional<weapon_info> get_weapon_info() {}



    bn::fixed health = max_health();

    bn::fixed_point position = spawn_point;
    bn::fixed_point velocity;

    bn::fixed max_health() {
        return 100;
    };

    bn::fixed run_speed() {
        return 4;
    };

    bn::fixed jump_velocity() {
        return -7;
    };

    bool is_jumping;
    bool is_running;
    bool flipped;
    bool is_landing;
    bool is_falling;



    // bn::sprite_item pictogram;
    bn::optional<bn::sprite_ptr>_sprite_ptr = sprite_item().create_sprite(spawn_point);

    bn::optional<bn::sprite_ptr> sprite_ptr() {
        return _sprite_ptr;
    };

    static bn::sprite_item sprite_item()  {
        return bn::sprite_items::fleur;
    }

    bn::sprite_item spr_item() {
        return bn::sprite_items::fleur; 
    }

    // Animations

    virtual character_animations animations() override {
        return {
            character_animations {
                idle: bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, bn::sprite_items::fleur.tiles_item(), 
                    35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
                ),
                run: bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, sprite_item().tiles_item(), 
                    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34
                ),
                jump_up: bn::create_sprite_animate_action_once(*_sprite_ptr, 1, sprite_item().tiles_item(), 
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
                ),
                jump_stay: bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, sprite_item().tiles_item(), 
                10, 10
                ),
                jump_down: bn::create_sprite_animate_action_once(*_sprite_ptr, 1, sprite_item().tiles_item(), 
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22
                )
            }
        };
    }

    bn::optional<character_animations> anims = animations();


    fleur() {}


    void unload() {
        anims.reset();
        _sprite_ptr.reset();
    }

    bool _preview_mode;
    void set_preview_mode(bool on_or_off) {
        _preview_mode = on_or_off;
    }


    void update(multiplayer::keypad_data::keypad_data_struct keypad) {
        if (_preview_mode) {
            anims->idle.update();
            return;
        }
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

        // platform beneath player 
        if (on_ground) {
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
            velocity.set_x(-run_speed());
            _sprite_ptr->set_horizontal_flip(true);
            if (on_ground) {
                is_running = true;
                is_landing = false;
            }
        }

        if (keypad.right_held) {
            velocity.set_x(run_speed());
            if (on_ground) {
                is_running = true;
                is_landing = false;
            }
            _sprite_ptr->set_horizontal_flip(false);
        }
        
        if (!keypad.left_held && !keypad.right_held) {
            velocity.set_x(0);
            if (is_running) {
                is_running = false;
            }
        }


        // Apply velocity to position
        position += velocity;

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


