#pragma once

#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "../../include/utils.h"

#include "bn_regular_bg_items_tilemap.h"


// Globals
bn::optional<bn::camera_ptr> camera;
bn::optional<info_printer> printer;
bn::optional<bn::random> global_random;


// The world
bn::optional<bn::regular_bg_map_item> map_item;
int passthrough_tiles[] = { 0, 13, 14, 16, 37, 41, 36, 23, 24, 25, 26 };
int wall_tiles[] = { 6, 9, 10 };
const bn::fixed gravity = 0.3;

const bn::fixed_point spawn_point = bn::fixed_point(256,-100);

const bn::fixed bounds_min_x =  -110;
const bn::fixed bounds_max_x = 740;
const bn::fixed bounds_min_y = -200;
const bn::fixed bounds_max_y = 486;