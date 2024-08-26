#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_sprite_text_generator.h"
#include "bn_point.h"
#include "bn_log.h"
#include "bn_format.h"
#include "bn_math.h"
#include "bn_display.h"
#include "bn_link.h"
#include "bn_link_state.h"
#include "bn_music.h"
#include "bn_audio.h"


// Includes
#include "../../include/utils.h"
#include "globals.h"
#include "./characters/-character.h"
#include "pickups.h"


// scenes
#include "scene.h"
#include "boomhut.h"
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
        platforming_level::run();
        // if (next == next_scene::platforming)
        //     next = platforming_level::run();
        // else if (next == next_scene::main_menu)
        //     next = main_menu::run();
    }
}
