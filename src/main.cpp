#include "bn_core.h"
#include "bn_bg_palettes.h"
#include "bn_keypad.h"

// Includes
#include "../include/utils.h"
#include "globals.h"


// scenes
#include "scene.h"
#include "battle.h"
#include "splash.h"
#include "main_menu.h"
#include "character_select.h"


int main()
{
    bn::core::init();

    // All characters


    // Background
    bn::color background_color = rgb255(140, 165, 247);
    bn::bg_palettes::set_transparent_color(background_color);
    map_item = bn::regular_bg_items::tilemap.map_item();

    
    // The global camera and printer
    camera = bn::camera_ptr::create(0, 0);
    printer = info_printer();
    global_random = bn::random();

    // Splash
    // splash::run();

    // Main menu
    next_scene next = character_select::run();

    while (true)
    {
        if (next == next_scene::character_select) 
            next = character_select::run();
        if (next == next_scene::battle)
            next = battle::run();
        else if (next == next_scene::main_menu)
            next = main_menu::run();
    }
}
