#pragma once

#include "bn_core.h"
#include "bn_point.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"
#include "bn_keypad.h"
#include "bn_regular_bg_map_item.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_builder.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_log.h"
#include "bn_vector.h"
#include "bn_sound_item.h"
#include "bn_sound_items.h"

#include "bn_sprite_items_rein_lario.h"


#include "../globals.h"
#include "../../include/utils.h"
#include "../multiplayer.h"



enum class all_characters {
    empty,
    cate, 
    christine, 
    fabian, 
    fleur,
    hunter,
    joost, 
    laury, 
    mar, 
    networkninja, 
    rein, 
    saskia, 
    sietse, 
    sjef, 
    werner
};




struct character_animations {
    bn::sprite_animate_action<400> idle;
    bn::sprite_animate_action<150> run;

    bn::sprite_animate_action<100> jump_up;
    bn::sprite_animate_action<2> jump_stay;
    bn::sprite_animate_action<100> jump_down;
};



// Abstract character
struct character {
    virtual bn::string<20> name();
    virtual bn::sprite_item avatar();
    virtual bn::fixed max_health();
    virtual bn::fixed run_speed();
    virtual bn::fixed jump_velocity();

    // sounds
    virtual bn::sound_item sound_naam();
    virtual bn::sound_item sound_tagline();
    virtual bn::sound_item sound_jump();
    virtual bn::sound_item sound_hit();

    // sprites and animations
    virtual character_animations animations();
    virtual bn::sprite_item spr_item();
    virtual bn::optional<bn::sprite_ptr> sprite_ptr();
    virtual void unload();

    virtual void update(multiplayer::keypad_data::keypad_data_struct keypad);
};





// Global
// bn::vector<bn::unique_ptr<character>, 2> players;

bn::unique_ptr<character> you;
bn::unique_ptr<character> other_player;

bn::optional<all_characters> selected_you;
bn::optional<all_characters> selected_other;

