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

#include "../globals.hpp"
#include "../include/utils.h"
#include "../multiplayer.hpp"


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


// Will be shown in the character select screen
struct weapon_info {
    bn::string<20> name;
    bn::sprite_item avatar;
};

// Abstract character
struct character {
    int frame = 0;

    // Ability stats
    bn::fixed ability = 100;
    bn::fixed max_ability = 100;
    int ability_power = 50; // Standard frame delay for ability increase
    int ability_frame_delay = 0.16f * ability_power; // Standard frame delay for ability increase
    int ability_frame_duration = 180 * (ability_power / 100); // Max 3s duration for ability bason on 60fps 
    
    // Inflicted ability states
    bool isStunned = false;
    int stun_frame_start;
    int stun_frame_duration; 

    virtual void stun(int frame_duration) {
        isStunned = true;
        // ability = 0;
        stun_frame_start = frame;
        stun_frame_duration = frame_duration;
    }

    virtual void release_stun() {
        if (stun_frame_start + stun_frame_duration <= frame) {
            isStunned = false;
        }
    };

    virtual bn::string<20> name() = 0;
    virtual bn::sprite_item avatar() = 0;
    virtual bn::fixed max_health() = 0;

    virtual bn::fixed run_speed() = 0;
    virtual bn::fixed jump_velocity() = 0;

    virtual bn::fixed get_health() = 0;
    virtual bn::fixed get_ability() {
        return ability;
    };    

    virtual void increase_ability() {
        if (frame % ability_frame_delay == 0) {           
            ability = bn::min(ability + 1, max_ability);
        }
    };

    virtual void set_ability_power(int power) {
        ability_power = power;
        ability_frame_delay = 0.078f * power; // 0.16f * power; // Standard frame delay for ability increase
        ability_frame_duration = 180 * (power / 100); // Max 3s duration for ability bason on 60fps 
    };

    virtual void set_ability_frame_delay(int delay) {
        ability_frame_delay = delay;
    };

    virtual void reset_ability() {
        ability = 0;
    };    

    virtual void take_damage(bn::fixed) = 0;
    virtual void apply_force(bn::fixed_point) = 0;

    // state
    virtual bool is_indoors() {
        return false;
    };

    // sounds
    virtual bn::sound_item sound_naam() = 0;
    virtual bn::sound_item sound_tagline() = 0;
    virtual bn::sound_item sound_jump() = 0;
    virtual bn::sound_item sound_hit() = 0;
    virtual bn::sound_item sound_win() = 0;

    // sprites and animations
    virtual character_animations animations() = 0;
    virtual bn::sprite_item sprite_item() = 0;
    virtual bn::optional<bn::sprite_ptr> sprite_ptr() = 0;
    virtual void unload() = 0;

    // weapons
    virtual bn::optional<weapon_info> get_weapon_info() = 0;

    // behaviour
    virtual void set_preview_mode(bool) = 0; 
    virtual void update(int frame, multiplayer::keypad_data::keypad_data_struct keypad) 
    {
        this->frame = frame;
        update(keypad);
    };
    virtual void update(multiplayer::keypad_data::keypad_data_struct keypad) = 0;

    virtual ~character() {};
};

// Global
character* you;
character* other_player;

bn::optional<character*> winner;
bn::optional<character*> loser;

bn::vector<character*, 2> players() {
    bn::vector<character*, 2> vec;
    vec.push_back(you);
    vec.push_back(other_player);
    return vec;
}
