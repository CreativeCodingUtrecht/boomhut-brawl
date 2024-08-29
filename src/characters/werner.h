#pragma once

#include "-character.h"

#include "bn_sprite_items_avatar_werner.h"
#include "bn_sound_items.h"


struct werner: public character {
    // General ----------------------------------
    bn::string<20> name() {
        return "Werner";
    }

    bn::sprite_item avatar() {
        return bn::sprite_items::avatar_werner;
    }

    bn::optional<weapon_info> get_weapon_info() { return bn::optional<weapon_info>(); }


    // Stats ------------------------------------
    bn::fixed max_health() {
        return 100;
    };

    bn::fixed run_speed() {
        return 4;
    };

    bn::fixed jump_velocity() {
        return -7;
    };

    // Sounds -----------------------------------
    bn::sound_item sound_naam() {
        return bn::sound_items::werner_naam;
    }

    bn::sound_item sound_tagline() {
        return bn::sound_items::werner_tagline;
    }

    bn::sound_item sound_jump() {
        return bn::sound_items::werner_jump;
    }

    bn::sound_item sound_hit() {
        return bn::sound_items::werner_hit;
    }


    // Health -----------------------------------
    bn::fixed health = max_health();
    bn::fixed get_health() {
        return health;
    }

    
    int mosaic_timer = 30;
    void take_damage(bn::fixed amount) {
        mosaic_timer = 30;
        _sprite_ptr->set_mosaic_enabled(true);
        health -= amount;
    }


    void apply_force(bn::fixed_point point) {
        velocity += point;
    }



    bn::fixed_point position = spawn_point;;
    bn::fixed_point velocity;

    bool is_jumping;
    bool is_running;
    bool flipped;
    bool is_landing;
    bool is_falling;


    bn::sprite_item sprite_item()  {
        return bn::sprite_items::rein_lario;
    };


    bn::optional<bn::sprite_ptr>_sprite_ptr = sprite_item().create_sprite(spawn_point);
    bn::optional<bn::sprite_ptr> sprite_ptr() {
        return _sprite_ptr;
    };

    // Animations -------------------------------
    character_animations animations() {
        return {
            character_animations {
                .idle = bn::create_sprite_animate_action_forever(*_sprite_ptr, 1, bn::sprite_items::rein_lario.tiles_item(), 
                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
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
            }
        };
    }

       bn::optional<character_animations> anims = animations();

    werner() {}


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

        if (mosaic_timer > 0) {
            mosaic_timer--;
            bn::sprites_mosaic::set_stretch(map(mosaic_timer, 30, 0, 1, 0));
        } else {
            _sprite_ptr->set_mosaic_enabled(false);
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

