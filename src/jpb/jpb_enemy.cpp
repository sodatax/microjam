#include "jpb/jpb_enemy.h"
#include "bn_sprite_items_jpb_ship.h"

namespace jpb {

    jpb_enemy::jpb_enemy(bn::fixed_point starting_position, bn::size _size) :
        enemy_sprite(bn::sprite_items::jpb_ship.create_sprite(starting_position)),
        enemy_box(create_bounding_box(enemy_sprite, _size))
    {}

    void jpb_enemy::update() {
        enemy_box = create_bounding_box(enemy_sprite, {8, 8});
    }
}