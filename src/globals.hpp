#pragma once

#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "../include/utils.h"

#include "bn_regular_bg_items_tilemap.h"
#include "bn_regular_bg_ptr.h"

// Globals
bn::fixed screen_shake = 0;
bn::optional<bn::camera_ptr> camera;
bn::optional<info_printer> printer;
bn::optional<bn::random> global_random;


// The world
bn::optional<bn::regular_bg_map_item> map_item;
bn::optional<bn::regular_bg_ptr> indoor_background;
bn::optional<bn::regular_bg_ptr> background;

int ground_tile = 1;
int wall_tile = 2;
int indoor_floor_tile = 4;
int indoor_tile = 3;
int passthrough_tiles[] = { 0, indoor_tile };
int wall_tiles[] = { wall_tile };
int indoor_tiles[] = {indoor_floor_tile, indoor_tile };

const bn::fixed gravity = 0.3;

const bn::fixed_point spawn_point = bn::fixed_point(256,-100);

const bn::fixed bounds_min_x =  -110;
const bn::fixed bounds_max_x = 740;
const bn::fixed bounds_min_y = -200;
const bn::fixed bounds_max_y = 502;