#include "sdg/input.h"
#include <bn_keypad.h>
#include "bn_sprite_items_sdg_arrow_sheet.h"
#include <bn_log.h>

namespace sdg {

input::input() {
    challenge = { 0, 1, 2, 3, 0 }, // will be made random later
    progress = 0;
};

// Reads the input from the D-Pad each frame
void input::update() {
    
    if(bn::keypad::up_pressed()) { _input = 0; }
    else if(bn::keypad::right_pressed()) { _input = 1; }
    else if(bn::keypad::down_pressed()) { _input = 2; }
    else if(bn::keypad::left_pressed()) { _input = 3; }
    // No input results in a default value
    else {_input = -1;}

    if (_input != -1 && progress < 5) {
        if(_input == input::challenge[progress]) {
            progress += 1;
            BN_LOG("CODE IS CORRECT!");
        }
        // reset if incorrect
        else {
            progress = 0;
            BN_LOG("CODE INCORRECT!");
        }
    }
}

// if code complete, victory is achieved
bool input::code_is_correct() const {
    return progress == challenge.size();
}

}