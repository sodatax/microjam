#include "knc/knc_astro_cat.h"
#include "mj/mj_game_list.h"


namespace {
    constexpr bn::string_view code_credits[] = { "knc" };
    constexpr bn::string_view graphics_credits[] = { "knc" };
    constexpr bn::string_view sfx_credits[] = { "" };
    constexpr bn::string_view music_credits[] = { "" };
}

namespace knc {

    // speed changes + added thing based on difficulty
    bn::fixed knc_astro_cat::_recommended_speed(mj::difficulty_level difficulty) {
        if (difficulty == mj::difficulty_level::EASY){
            return 1;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 1.5;
        }
        return 2;
    }


    knc_astro_cat::knc_astro_cat(int completed_games, const mj::game_data& data)
        : mj::game("knc"),
        // start in middle, speed number 1
        _cat(bn::fixed_point(0,40), 2),
        _difficulty(recommended_difficulty_level(completed_games, data)),

        // easy mode
        _planet1(bn::fixed_point(0, -80), _recommended_speed(recommended_difficulty_level(completed_games, data))),
        _planet2(bn::fixed_point(-50, -200), _recommended_speed(recommended_difficulty_level(completed_games, data))),
        _planet3(bn::fixed_point(50, -320), _recommended_speed(recommended_difficulty_level(completed_games, data))),

        // stay waiting - normal + hard mode added these
      _planet4(bn::fixed_point(1000, 1000), _recommended_speed(recommended_difficulty_level(completed_games, data))),
      _star1(bn::fixed_point(1000, 1000), _recommended_speed(recommended_difficulty_level(completed_games, data))),
      _star2(bn::fixed_point(1000, 1000), _recommended_speed(recommended_difficulty_level(completed_games, data))),

      // stay waiting - hard mode added only
      _star3(bn::fixed_point(1000, 1000), _recommended_speed(recommended_difficulty_level(completed_games, data))),
        _hit(false)
    {
        bn::fixed speed = _recommended_speed(_difficulty);

    // normal + hard get planet4 and star1, star2
    if(_difficulty == mj::difficulty_level::NORMAL || _difficulty == mj::difficulty_level::HARD) {
        _planet4 = planet(bn::fixed_point(30, -440), speed);
        _star1 = shooting_star(bn::fixed_point(-120, -30), speed);
        _star2 = shooting_star(bn::fixed_point(-200, 18), speed);
    }

    // hard gets star3
    if(_difficulty == mj::difficulty_level::HARD) {
        _star3 = shooting_star(bn::fixed_point(-280, 0), speed);
    }
}

    bn::string<16> knc_astro_cat::title() const
    {
        return "Dodge Them Fire!";
    }

    int knc_astro_cat::total_frames() const
    {
        return 60 * 5; 
    }

    mj::game_result knc_astro_cat::play(const mj::game_data& data)
    {

        bn::fixed speed = _recommended_speed(_difficulty);
        _cat.update();

        // update planet1
        _planet1.update();
        if(_planet1.off_screen()) {
            bn::fixed x = bn::fixed(data.random.get_int(200)) - 100;
            _planet1 = planet(bn::fixed_point(x, -80), speed);
        }
        //update planet 2
        _planet2.update();
        if(_planet2.off_screen()) {
            bn::fixed x = bn::fixed(data.random.get_int(200)) - 100;
            _planet2 = planet(bn::fixed_point(x, -80), speed);
        }

        // update planet3 — respawn at random x if offscreen
        _planet3.update();
        if(_planet3.off_screen()) {
            bn::fixed x = bn::fixed(data.random.get_int(200)) - 100;
            _planet3 = planet(bn::fixed_point(x, -80), speed);
        }

        // update planet4 — normal + hard only
        _planet4.update();
        if(_planet4.off_screen()) {
        bn::fixed x = bn::fixed(data.random.get_int(200)) - 100;
        _planet4 = planet(bn::fixed_point(x, -80), speed);
        }
        // update all shooting stars — respawn at random y if offscreen - only normal and hard mode have these

        // normal + hard
        _star1.update();
        if(_star1.off_screen()) {
            bn::fixed y = bn::fixed(data.random.get_int(140)) - 70;
            _star1 = shooting_star(bn::fixed_point(-120, y), speed);
        }
        // normal + hard
        _star2.update();
        if(_star2.off_screen()) {
            bn::fixed y = bn::fixed(data.random.get_int(140)) - 70;
            _star2 = shooting_star(bn::fixed_point(-120, y), speed);
        }
        // hard mode only
        _star3.update();
        if(_star3.off_screen()) {
            bn::fixed y = bn::fixed(data.random.get_int(140)) - 70;
            _star3 = shooting_star(bn::fixed_point(-120, y), speed);
        }
        // if planet hit cat, end game 
        // if star hit cat, end game

        // easy
        if (_planet1.collides_with(_cat.position(),             cat::COLLISION_RADIUS) ||
        _planet2.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _planet3.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||

        // normal + hard
        _planet4.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _star1.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _star2.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _star3.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
            _hit = true;
    }
       // end game if cat got hit
        return mj::game_result(_hit, false);
    }
    // win if not get hit till time end
    bool knc_astro_cat::victory() const
    {
        return !_hit;
    }

    void knc_astro_cat::fade_in(const mj::game_data&)
    {
    }

    void knc_astro_cat::fade_out(const mj::game_data&)
    {
    }

} // namespace knc

MJ_GAME_LIST_ADD(knc::knc_astro_cat)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)