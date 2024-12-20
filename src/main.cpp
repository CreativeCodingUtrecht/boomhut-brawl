#include "bn_core.h"
#include "bn_bg_palettes.h"
#include "bn_keypad.h"

// Includes
#include "../include/utils.h"
#include "globals.hpp"
// #include "snow.hpp"

// scenes
#include "scene.hpp"
#include "battle.hpp"
#include "splash.hpp"
#include "main_menu.hpp"
#include "character_select.hpp"
#include "win_lose.hpp"
#include "christmas.hpp"




int main()
{
    bn::core::init();

    // Background
    bn::color background_color = rgb255(140, 165, 247);
    bn::bg_palettes::set_transparent_color(background_color);
    map_item = bn::regular_bg_items::tilemap.map_item();

    // The global camera and printer
    camera = bn::camera_ptr::create(0, 0);
    printer = info_printer();
    global_random = bn::random();

    // Snow
    global_snow = snow();

    // Splash
    // battle::run();
    // next_scene next = battle::run();

    // Main menu
    next_scene next = splash::run();

    while (true)
    {
        if (next == next_scene::character_select) 
            next = character_select::run();
        if (next == next_scene::battle)
            next = battle::run();
        if (next == next_scene::you_win)
            next = win_lose::run();
        else if (next == next_scene::main_menu)
            next = main_menu::run();
        else if (next == next_scene::splash)
            next = splash::run();
    }
}
