#include "jpb/jpb_missile.h"
#include "bn_sprite_items_jpb_missile.h"

namespace jpb {

    jpb_missile::jpb_missile(bn::fixed_point starting_position, bn::fixed speed, bn::size size) :
        _sprite(bn::sprite_items::jpb_missile.create_sprite(starting_position)),
        _bounding_box(create_bounding_box(_sprite, size))
    {}

    void jpb_missile::update() {
        _bounding_box = create_bounding_box(_sprite, {4, 4});
    }
}