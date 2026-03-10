#include "sdg/input.h"
#include <bn_keypad.h>
#include "bn_sprite_items_sdg_arrow_sheet.h"

namespace sdg {

input::input() {
    challenge = { 0, 3, 1, 2, 0 }, // will be made random later
    progress = 0,
    completed = false;
};

// Reads the input from the D-Pad each frame
void input::update() {
    
    if(bn::keypad::up_held()) { _input = 0; }
    else if(bn::keypad::right_held()) { _input = 1; }
    else if(bn::keypad::down_held()) { _input = 2; }
    else if(bn::keypad::left_held()) { _input = 3; }
    // No input results in a default value
    else {_input = -1;}

    if (_input != -1) {
        if(_input == input::challenge[progress]) { progress += 1; }
        // reset if incorrect
        else { progress = 0; }
    }
}

// if code complete, victory is achieved
bool input::code_is_correct() const {
    return progress == challenge.size();
}

}