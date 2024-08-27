#pragma once

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_palette_actions.h"

#include "globals.h"
#include "scene.h"

#include "bn_sprite_items_menu_platforming.h"
#include "bn_sprite_items_menu_selector.h"
// #include "bn_sprite_items_c.h"
// #include "bn_sprite_items_c2.h"
// #include "bn_sprite_items_u.h"

#include "bn_regular_bg_items_menu_bg.h"
#include "bn_sound_items.h"
#include "multiplayer.h"
#include "bn_link.h"
#include "bn_link_state.h"


// Font 
#include "../../common/include/common_fixed_8x16_sprite_font.h"

// Backgrounds
#include "bn_regular_bg_items_character_select_screen.h"

// Sprites
#include "bn_sprite_items_pictogram_selector_you.h"
#include "bn_sprite_items_pictogram_selector_other_player.h"
#include "bn_sprite_items_rein_pictogram.h"

// Characters
#include "./characters/-character.h"
#include "./characters/cate.h"
#include "./characters/christine.h"
#include "./characters/fabian.h"
#include "./characters/fleur.h"
#include "./characters/hunter.h"
#include "./characters/joost.h"
#include "./characters/laury.h"
#include "./characters/mar.h"
#include "./characters/networkninja.h"
#include "./characters/rein.h"
#include "./characters/saskia.h"
#include "./characters/sjef.h"
#include "./characters/werner.h"
#include "./characters/sietse.h"


// Sounds
#include "bn_sound_items.h";


namespace character_select 
{
    struct character_pictogram
    {
        all_characters character_to_choose;
        int x_offset = 0;
        int y_offset = 0;
        bn::string<20> name;
        // bn::sprite_animate_action<400> anim;
    };

    const int menu_items_x = 5;
    const int menu_items_y = 5;

    int y_offset = 0;
    int spacing_x = 85;


    // bn::sprite_ptr you_spr = bn::sprite_items::fabian.create_sprite(-spacing_x,-45);
    // bn::sprite_ptr other_spr = bn::sprite_items::fabian.create_sprite(spacing_x,-45);

    character_pictogram character_pictograms[menu_items_y][menu_items_x] = 
    {
        {
            character_pictogram 
            {
                all_characters::cate,
                -33,
                -62,
                "Space Bard"
                // , 
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::rein_lario.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
                // )
            },
            character_pictogram 
            {
                all_characters::christine,
                -2,
                -62,
                "Christine"
                
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::rein_lario.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
                // )
            },
            character_pictogram 
            {
                all_characters::fabian,
                29,
                -62,
                "El Chefe",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::fabian.tiles_item(), 
                //     46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163
                // )
            },
        },
        {
            character_pictogram 
            {
                all_characters::fleur,
                -33,
                -31,
                "Fleur",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::fleur.tiles_item(), 
                //     35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
                // )
            },
            character_pictogram 
            {
                all_characters::hunter,
                -2,
                -31,
                "Hunter"
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::hunter.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122
                // )
            },
            character_pictogram 
            {
                all_characters::joost,
                29,
                -31,
                "Joost",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::rein_lario.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
                // )
            },
        }
        ,{
            character_pictogram 
            {
                all_characters::laury,
                -33,
                -0,
                "Laury",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::laury.tiles_item(), 
                //     69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400
                // )
            },
            character_pictogram 
            {
                all_characters::mar,
                -2,
                -0,
                "Mar",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::maryam.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276
                // )
            },
            character_pictogram 
            {
                all_characters::networkninja,
                29,
                -0,
                "Network Ninja",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::timo.tiles_item(), 
                //     38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209
                // )
            },
        },
        {
            character_pictogram 
            {
                all_characters::rein,
                -33,
                31,
                "Rein",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::rein_lario.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, you_spr, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
                // )
            },
            character_pictogram 
            {
                all_characters::saskia,
                -2,
                31,
                "Saskia"
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::rein_lario.tiles_item(), 
                //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
                // )
            },
            character_pictogram 
            {
                all_characters::sjef,
                29,
                31,
                "Sjef",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::sjef.tiles_item(), 
                //     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160
                // )
            },
        },
        {
            character_pictogram 
            {
                all_characters::werner,
                -33,
                62,
                "Werner",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::sjef.tiles_item(), 
                //     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160
                // )
            },
            character_pictogram 
            {
                all_characters::sietse,
                -2,
                62,
                "Sietse",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::sjef.tiles_item(), 
                //     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160
                // )
            },
            character_pictogram 
            {
                all_characters::empty,
                29,
                62,
                "---",
                // ,
                // bn::create_sprite_animate_action_forever(you_spr, 1, bn::sprite_items::sjef.tiles_item(), 
                //     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160
                // )
            },
        }
    };

    bn::sprite_animate_action<400> get_animation_for_character(all_characters c, bn::sprite_ptr spr) 
    {
        if (c == all_characters::cate) {
            return cate::idle_anim(spr);
        }
        if (c == all_characters::christine) {
            return christine::idle_anim(spr);
        }

        if (c == all_characters::fabian) {
            return fabian::idle_anim(spr);
        }
        if (c == all_characters::fleur) {
            return fleur::idle_anim(spr);
        }
        if (c == all_characters::hunter) {
            return hunter::idle_anim(spr);
        }
        if (c == all_characters::joost) {
            return joost::idle_anim(spr);
        }
        if (c == all_characters::laury) {
            return laury::idle_anim(spr);
        }
        if (c == all_characters::mar) {
            return mar::idle_anim(spr);
        }
        if (c == all_characters::networkninja) {
            return networkninja::idle_anim(spr);
        }
        if (c == all_characters::rein) {
            return rein::idle_anim(spr);
        }
        if (c == all_characters::saskia) {
            return saskia::idle_anim(spr);
        }
        if (c == all_characters::sietse) {
            return sietse::idle_anim(spr);
        }
        if (c == all_characters::sjef) {
            return sjef::idle_anim(spr);
        }
        if (c == all_characters::werner) {
            return werner::idle_anim(spr);
        }
    }



    bn::sound_item get_sound_for_character(all_characters c)
    {
        if (c == all_characters::cate) {
            return bn::sound_items::cat_naam;
        }
        if (c == all_characters::christine) {
            return bn::sound_items::christine_naam;
        }
        if (c == all_characters::fabian) {
            return bn::sound_items::fabian_naam;
        }
        if (c == all_characters::fleur) {
            return bn::sound_items::fleur_naam;
        }
        if (c == all_characters::hunter) {
            return bn::sound_items::niels_naam;
        }
        if (c == all_characters::joost) {
            return bn::sound_items::joost_naam;
        }
        if (c == all_characters::laury) {
            return bn::sound_items::laura_naam;
        }
        if (c == all_characters::mar) {
            return bn::sound_items::mar_naam;
        }
        if (c == all_characters::networkninja) {
            return bn::sound_items::timo_naam;
        }
        if (c == all_characters::rein) {
            return bn::sound_items::rein_naam;
        }
        if (c == all_characters::saskia) {
            return bn::sound_items::saskia_naam;
        }
        if (c == all_characters::sietse) {
            return bn::sound_items::sietse_naam;
        }
        if (c == all_characters::sjef) {
            return bn::sound_items::sjef_naam;
        }
        if (c == all_characters::werner) {
            return bn::sound_items::werner_naam;
        }
    }

    bn::sound_item get_tagline_sound_for_character(all_characters c)
    {
        if (c == all_characters::cate) {
            return bn::sound_items::cat_tagline;
        }
        if (c == all_characters::christine) {
            return bn::sound_items::christine_tagline;
        }
        if (c == all_characters::fabian) {
            return bn::sound_items::fabian_tagline;
        }
        if (c == all_characters::fleur) {
            return bn::sound_items::fleur_tagline;
        }
        if (c == all_characters::hunter) {
            return bn::sound_items::niels_tagline;
        }
        if (c == all_characters::joost) {
            return bn::sound_items::joost_tagline;
        }
        if (c == all_characters::laury) {
            return bn::sound_items::laura_tagline;
        }
        if (c == all_characters::mar) {
            return bn::sound_items::mar_tagline;
        }
        if (c == all_characters::networkninja) {
            return bn::sound_items::timo_tagline;
        }
        if (c == all_characters::rein) {
            return bn::sound_items::timo_tagline;
        }
        if (c == all_characters::saskia) {
            return bn::sound_items::saskia_tagline;
        }
        if (c == all_characters::sietse) {
            return bn::sound_items::sietse_tagline;
        }
        if (c == all_characters::sjef) {
            return bn::sound_items::sjef_tagline;
        }
        if (c == all_characters::werner) {
            return bn::sound_items::werner_tagline;
        }
    }


    // void 

    next_scene start_game(int selected_menu_item_x, int selected_menu_item_y) 
    {   
        // bn::sound_items::into.play();
        // // bn::sound_items::shield.play();
        
        // for (int x = 0; x < menu_items_x; x++) {
        //     for (int y = 0; y < menu_items_x; y++) {
        //         menu_item *item = &menu_items[x][y];
        //         item->spr.reset();
        //     }
        // }

        // return menu_items[selected_menu_item_x][selected_menu_item_y].scene;
    }



    void create_character(bn::unique_ptr<character> &ptr,  all_characters c) 
    {
        if (c == all_characters::cate) {
            ptr.reset(new cate());
        }
        if (c == all_characters::christine) {
            ptr.reset(new christine());
        }
        if (c == all_characters::fabian) {
            ptr.reset(new fabian());
        }
        if (c == all_characters::fleur) {
            ptr.reset(new fleur());
        }
        if (c == all_characters::hunter) {
            ptr.reset(new hunter());
        }
        if (c == all_characters::joost) {
            ptr.reset(new joost());
        }
        if (c == all_characters::laury) {
            ptr.reset(new laury());
        }
        if (c == all_characters::mar) {
            ptr.reset(new mar());
        }
        if (c == all_characters::networkninja) {
            ptr.reset(new networkninja());
        }
        if (c == all_characters::rein) {
            ptr.reset(new rein());
        }
        if (c == all_characters::saskia) {
            ptr.reset(new saskia());
        }
        if (c == all_characters::sietse) {
            ptr.reset(new sietse());
        }
        if (c == all_characters::sjef) {
            ptr.reset(new sjef());
        }
        if (c == all_characters::werner) {
            ptr.reset(new werner());
        }
    }
    

    next_scene run() 
    {
        int t = 0;
        bool connected = false;

        int x_offset = 0;
        int y_offset = 0;

        int selected_menu_item_x = 0;
        int selected_menu_item_y = 0;
        int other_selected_menu_item_x = 0;
        int other_selected_menu_item_y = 0;

        // Background
        bn::regular_bg_ptr bg = bn::regular_bg_items::character_select_screen.create_bg(0,0);

        // Selectors
        bn::sprite_ptr selector_you = bn::sprite_items::pictogram_selector_you.create_sprite(0,0);
        bn::sprite_ptr selector_other_player = bn::sprite_items::pictogram_selector_other_player.create_sprite(0,0);


        // Characters / players
        auto selected = character_pictograms[selected_menu_item_x][selected_menu_item_y];
        create_character(you, selected.character_to_choose);

        auto other_selected = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y];
        create_character(other_player, other_selected.character_to_choose);


        bn::sprite_ptr you_spr = cate::sprite_item().create_sprite(-spacing_x,-45);
        bn::sprite_ptr other_spr = cate::sprite_item().create_sprite(spacing_x,-45);

        bn::optional<bn::sprite_animate_action<400>> you_anim = cate::idle_anim(you_spr);
        bn::optional<bn::sprite_animate_action<400>> other_anim = cate::idle_anim(other_spr);


        // Text generators
        bn::sprite_text_generator text_generator_you(common::variable_8x8_sprite_font);
        text_generator_you.set_left_alignment();
        bn::vector<bn::sprite_ptr, 4> text_sprites;
        text_generator_you.generate(-112, 2, you->name(), text_sprites);

        bn::sprite_text_generator text_generator_other(common::variable_8x8_sprite_font);
        text_generator_other.set_right_alignment();
        bn::vector<bn::sprite_ptr, 4> text_sprites_other;
        text_generator_other.generate(112, 2, other_player->name(), text_sprites_other);


        while (true) 
        {
            t++;

            you_anim->update();
            other_anim->update();

            // multiplayer
            multiplayer::keypad_data keys_data = multiplayer::read_keys();
            multiplayer::send_if_changed(keys_data);
            multiplayer::receive_keypad_data();


            if (multiplayer::other_player_keypad_data.keypad_data.start_pressed) {
                BN_LOG("start received");
                return next_scene::platforming;
            }


            // menu navigation you
            if (keys_data.keypad_data.up_pressed || keys_data.keypad_data.down_pressed || 
                keys_data.keypad_data.left_pressed || keys_data.keypad_data.right_pressed) {
                
                bn::sound_items::cursor.play();

                int last_menu_item_x = selected_menu_item_x;
                int last_menu_item_y = selected_menu_item_y;

                if (keys_data.keypad_data.up_pressed)
                    selected_menu_item_x--;
                if (keys_data.keypad_data.down_pressed)
                    selected_menu_item_x++;
                if (keys_data.keypad_data.left_pressed)
                    selected_menu_item_y--;
                if (keys_data.keypad_data.right_pressed)
                    selected_menu_item_y++;
                

                selected_menu_item_x = mod(selected_menu_item_x, menu_items_x);
                selected_menu_item_y = mod(selected_menu_item_y, menu_items_y);

                auto selected = character_pictograms[selected_menu_item_x][selected_menu_item_y];
                auto c = selected.character_to_choose;
                you->unload(); // unload previous
                create_character(you, c);
                text_sprites.clear();
                text_generator_you.generate(-112, 2, you->name(), text_sprites);

                if (c == all_characters::empty) {
                    selected_menu_item_x = last_menu_item_x;
                    selected_menu_item_y = last_menu_item_y;
                }

                you_anim = get_animation_for_character(c, you_spr);

                get_sound_for_character(c).play();
            }


            if (keys_data.keypad_data.a_pressed) {
                selected_you = character_pictograms[selected_menu_item_x][selected_menu_item_y].character_to_choose;
                get_tagline_sound_for_character(*selected_you).play();
            }

            // menu navigation other player
            if (multiplayer::other_player_keypad_data.keypad_data.up_pressed || multiplayer::other_player_keypad_data.keypad_data.down_pressed || 
                multiplayer::other_player_keypad_data.keypad_data.left_pressed || multiplayer::other_player_keypad_data.keypad_data.right_pressed) {
                
                // bn::sound_items::cursor.play();

                int last_menu_item_x = other_selected_menu_item_x;
                int last_menu_item_y = other_selected_menu_item_y;

                if (multiplayer::other_player_keypad_data.keypad_data.up_pressed)
                    other_selected_menu_item_x--;
                if (multiplayer::other_player_keypad_data.keypad_data.down_pressed)
                    other_selected_menu_item_x++;
                if (multiplayer::other_player_keypad_data.keypad_data.left_pressed)
                    other_selected_menu_item_y--;
                if (multiplayer::other_player_keypad_data.keypad_data.right_pressed)
                    other_selected_menu_item_y++;
                

                other_selected_menu_item_x = mod(other_selected_menu_item_x, menu_items_x);
                other_selected_menu_item_y = mod(other_selected_menu_item_y, menu_items_y);

                auto selected = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y];
                auto c = selected.character_to_choose;
                other_player->unload(); // unload previous
                create_character(other_player, c);
                text_sprites_other.clear();
                text_generator_other.generate(112, 2, other_player->name(), text_sprites_other);

                if (c == all_characters::empty) {
                    other_selected_menu_item_x = last_menu_item_x;
                    other_selected_menu_item_y = last_menu_item_y;
                }

                other_anim = get_animation_for_character(c, other_spr);
            }

            if (multiplayer::other_player_keypad_data.keypad_data.a_pressed) {
                selected_other = character_pictograms[other_selected_menu_item_x][other_selected_menu_item_y].character_to_choose;
            }


            for (int x = 0; x < menu_items_x; x++) {
                for (int y = 0; y < menu_items_x; y++) {
                    character_pictogram *item = &character_pictograms[x][y];

                    if (x == selected_menu_item_x && y == selected_menu_item_y) {
                        selector_you.set_x(x_offset + item->x_offset);
                        selector_you.set_y(y_offset + item->y_offset);
                    }

                    if (x == other_selected_menu_item_x && y == other_selected_menu_item_y) {
                        selector_other_player.set_x(x_offset + item->x_offset);
                        selector_other_player.set_y(y_offset + item->y_offset);
                    }
                }
            }


            if (keys_data.keypad_data.start_pressed) {
                // bn::link::send(multiplayer::signal_start_game);
                return next_scene::platforming;
            }

            bn::core::update();
        }

        return next_scene::platforming;
    }


    
}


