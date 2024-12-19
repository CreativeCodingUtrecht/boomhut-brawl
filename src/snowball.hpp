#pragma once

#include "bn_vector.h"
#include "bn_fixed_point.h"


struct snowball {
    bn::fixed_point position;
    bn::fixed direction_x;

    void update() {
        
    }
};


bn::vector<snowball, 20> snowballs;