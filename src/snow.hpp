#include "bn_sprite_items_snowflake.h"
#include "bn_sprite_items_snowflake_smol.h"


#include "globals.hpp"
#include "characters/-character.hpp"





// Snow particles
struct snowflake
{
    bn::fixed_point pos = bn::fixed_point(0,camera->y() - bn::display::height()/2);
    bn::fixed x_pos = global_random->get_fixed(camera->x() - bn::display::width() / 2, camera->x() + bn::display::width() / 2);
    bn::fixed initial_angle = global_random->get_fixed(0, 360);
    bn::fixed size = global_random->get_fixed(0.5, 1);
    bn::sprite_ptr spr;

    snowflake(bn::sprite_item s): spr(s.create_sprite(pos)) {
        spr.set_camera(camera);
    }


    const int indoor_no_snow_tiles[3] = { indoor_floor_tile, indoor_tile, indoor_no_snow_tile };


    void update_and_draw(bn::fixed time) {
        spr.set_x(x_pos + 40.0 * sin(initial_angle + time));

        bn::fixed y_speed = 2 / size;
        spr.set_y(spr.y() + y_speed);

        // Hide if indoors
        int snowflake_tile_index = get_map_tile_index_at_position(spr.position(), *map_item); 
        bool snowflake_is_indoors = false;

        // check if indoors
        for (int tile_index: indoor_no_snow_tiles) {
            if (snowflake_tile_index == tile_index) {
                snowflake_is_indoors = true;
            }
        }
        
        if (you->is_indoors()) {
            if (snowflake_is_indoors) {
                spr.set_visible(false);
            } else {
                spr.set_visible(true);
            }
        } else {
            spr.set_visible(true);    
        }

        // Reset position
        if (spr.y() > camera->y() + bn::display::height() / 2) {
            spr.set_y(camera->y() - bn::display::height()/2);
            x_pos = global_random->get_fixed(camera->x() - bn::display::width() / 2, camera->x() + bn::display::width() / 2);
        }
    }
};

struct snow {
    bn::vector<snowflake, 40> snowflakes;
    bn::fixed t = 0;

    snow() {
        // Generate snowflakes
        for (int i = 0; i < 40; ++i) {
            bool smol = global_random->get_bool();
            snowflake s = snowflake(smol ? bn::sprite_items::snowflake : bn::sprite_items::snowflake_smol);
            snowflakes.push_back(s);
        }
    }

    void draw_and_update() {
        t += 0.001;
        for (snowflake &s : snowflakes) {
            s.update_and_draw(t);
        }
    }
};


// Global snow 
bn::optional<snow> global_snow;