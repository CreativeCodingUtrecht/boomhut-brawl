#pragma once

#include "-character.h"



struct saskia: public character {
    bn::string<20> name = "Saskia";

    bn::fixed max_health = 100.0;
    bn::fixed health = max_health;

    bn::fixed_point position;
    bn::fixed_point velocity;
    bn::fixed jump_velocity = -7.0;
    bn::fixed run_speed = 4;

    bool is_jumping;
    bool is_running;
    bool flipped;
    bool is_landing;
    bool is_falling;

    static bn::sprite_item sprite_item()  {
        return bn::sprite_items::rein_lario;
    };

    // bn::sprite_item pictogram;
    bn::sprite_ptr sprite_ptr = sprite_item().create_sprite(spawn_point);


    // Animations
    static bn::sprite_animate_action<400> idle_anim(bn::sprite_ptr spr)  {
        return bn::create_sprite_animate_action_forever(spr, 1, bn::sprite_items::rein_lario.tiles_item(), 
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
        );
    }

    character_animations animations = character_animations {
        idle: idle_anim(sprite_ptr),
        run: bn::create_sprite_animate_action_forever(sprite_ptr, 1, sprite_item().tiles_item(), 
            38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55
        ),
        jump_up: bn::create_sprite_animate_action_once(sprite_ptr, 1, sprite_item().tiles_item(), 
            56, 57, 58, 59, 60
        ),
        jump_stay: bn::create_sprite_animate_action_forever(sprite_ptr, 1, sprite_item().tiles_item(), 
            61, 61
        ),
        jump_down: bn::create_sprite_animate_action_once(sprite_ptr, 1, sprite_item().tiles_item(), 
            62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83
        )
    };

    saskia() {}

    void update(multiplayer::keypad_data::keypad_data_struct keypad) {
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
            is_jumping = true;
            is_landing = false;
            velocity.set_y(jump_velocity);
            animations.jump_down.reset();
            animations.jump_up.reset();
        }
        // running
        if (keypad.left_held) {
            is_landing = false;
            velocity.set_x(-run_speed);
            sprite_ptr.set_horizontal_flip(true);
            if (on_ground) {
                is_running = true;
                is_landing = false;
            }
        }

        if (keypad.right_held) {
            velocity.set_x(run_speed);
            if (on_ground) {
                is_running = true;
                is_landing = false;
            }
            sprite_ptr.set_horizontal_flip(false);
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

        sprite_ptr.set_position(position);

        // Update the right animation
        if (is_falling && !is_jumping && !is_landing) {
            animations.jump_stay.update();
        }
        else if (is_running && !is_jumping) {
            animations.run.update();
        }
        else if (is_jumping) {
            if (animations.jump_up.done()) {
                animations.jump_stay.update();
            } else {
                animations.jump_up.update();
            }
        } else if (is_landing && !animations.jump_down.done()) {
            animations.jump_down.update();
        }
        else {
            animations.idle.update();
        }
    } 
};

