#include "bn_display.h"
#include "bn_sprite_ptr.h"

#include "../../../include/utils.h";

#include "bn_sprite_items_pictogram_frame.h"
#include "bn_sprite_items_healthbar_fill.h"
#include "bn_sprite_items_healthbar_frame.h"
#include "bn_sprite_items_abilitybar_frame.h"
#include "bn_sprite_items_abilitybar_fill.h"



struct abilitybars
{
    const int x = 48;
    const int y = 30;

    const bn::fixed_point position_1 = bn::fixed_point(-bn::display::width() / 2 + 20, -bn::display::height() / 2 + y);
    bn::sprite_ptr abilitybar_fill = bn::sprite_items::abilitybar_fill.create_sprite(position_1.x() + x, position_1.y()+3);
    bn::sprite_ptr abilitybar_frame = bn::sprite_items::abilitybar_frame.create_sprite(position_1.x() + x, position_1.y());

    const bn::fixed_point position_2 = bn::fixed_point(bn::display::width() / 2 - 20, -bn::display::height() / 2 + y);
    const bn::fixed_point abilitybar_fill_position_2 = bn::fixed_point(position_2.x() - x, position_2.y()+3);
    bn::sprite_ptr abilitybar_fill2 = bn::sprite_items::abilitybar_fill.create_sprite(abilitybar_fill_position_2);
    bn::sprite_ptr abilitybar_frame2 = bn::sprite_items::abilitybar_frame.create_sprite(position_2.x() - x, position_2.y());

    abilitybars()
    {
        abilitybar_frame2.set_horizontal_flip(true);
        abilitybar_fill2.set_horizontal_flip(true);
    }

    void set_ability_left(bn::fixed ability)
    {
        abilitybar_fill.set_horizontal_scale(bn::max(ability, bn::fixed(0.01)));
        abilitybar_fill.set_x(position_1.x() + map(ability, 0, 1, 16, 48));
    }

    void set_ability_right(bn::fixed ability)
    {
        abilitybar_fill2.set_horizontal_scale(bn::max(ability, bn::fixed(0.01)));
        abilitybar_fill2.set_position(abilitybar_fill_position_2.x() + 32 - ability * 32, abilitybar_fill_position_2.y());
    }    
};

struct healthbars
{
    bn::optional<bn::sprite_ptr> pictogram;
    bn::optional<bn::sprite_ptr> pictogram2;
    

    const bn::fixed_point position_1 = bn::fixed_point(-bn::display::width() / 2 + 20, -bn::display::height() / 2 + 20);
    bn::sprite_ptr boss_frame = bn::sprite_items::pictogram_frame.create_sprite(position_1);
    bn::sprite_ptr healthbar_fill = bn::sprite_items::healthbar_fill.create_sprite(position_1.x() + 48, position_1.y()+3);
    bn::sprite_ptr healthbar_frame = bn::sprite_items::healthbar_frame.create_sprite(position_1.x() + 48, position_1.y());

    const bn::fixed_point position_2 = bn::fixed_point(bn::display::width() / 2 - 20, -bn::display::height() / 2 + 20);
    const bn::fixed_point healthbar_fill_position_2 = bn::fixed_point(position_2.x() - 48, position_2.y()+3);
    bn::sprite_ptr boss_frame2 = bn::sprite_items::pictogram_frame.create_sprite(position_2);
    bn::sprite_ptr healthbar_fill2 = bn::sprite_items::healthbar_fill.create_sprite(healthbar_fill_position_2);
    bn::sprite_ptr healthbar_frame2 = bn::sprite_items::healthbar_frame.create_sprite(position_2.x() - 48, position_2.y());

    healthbars(bn::sprite_item boss_spr_item, bn::sprite_item boss_spr_item2):
        pictogram(boss_spr_item.create_sprite(-bn::display::width() / 2 + 20, -bn::display::height() / 2 + 20)),
        pictogram2(boss_spr_item2.create_sprite(bn::display::width() / 2 - 20, -bn::display::height() / 2 + 20))
    {
        pictogram->set_z_order(2);
        pictogram2->set_z_order(2);

        boss_frame2.set_horizontal_flip(true);
        healthbar_frame2.set_horizontal_flip(true);
        healthbar_fill2.set_horizontal_flip(true);
    }


    // 0 - 1
    void set_health_left(bn::fixed health)
    {
        healthbar_fill.set_horizontal_scale(bn::max(health, bn::fixed(0.01)));
        healthbar_fill.set_x(position_1.x() + map(health, 0, 1, 16, 48));
    }

    // 0 - 1
    void set_health_right(bn::fixed health)
    {
        healthbar_fill2.set_horizontal_scale(bn::max(health, bn::fixed(0.01)));
        healthbar_fill2.set_position(healthbar_fill_position_2.x() + 32 - health * 32, healthbar_fill_position_2.y());
        // healthbar_fill.set_x(position_2.x() + map(health, 0, 1, 16, 48));
    }
};
