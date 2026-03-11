#include <bn_keypad.h>

#include "aaa_planetoid.h"
#include "mj/mj_game_list.h"
#include "bn_display.h"
#include <bn_core.h>
namespace
{
    constexpr bn::string_view code_credits[] = {"KJ, Adam Kurfurst"};
    constexpr bn::string_view graphics_credits[] = {"KJ, Adam Kurfurst"};
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(aaa::aaa_planetoids) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace aaa
{
    bn::random random;

    aaa_planetoids::aaa_planetoids([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("aaa"),
                                                                                                                       _player(bn::fixed_point(0, 0))
    {

        for (int i = 0; i < enemies.max_size(); i++)
        {
            bn::fixed_point pos(random.get_int(-300, 300), random.get_int(-150, 150)); // added extra so some enemies spawn off-screen
            bn::fixed speed = random.get_fixed(.2, .4);                                // nice slow moving enemies

            enemies.push_back(aaa_enemy({pos}, speed));
        }
    }

    bn::string<16> aaa_planetoids::title() const
    {
        return "Planetoids";
    }

    int aaa_planetoids::total_frames() const
    {
        return 480;
    }

    mj::game_result aaa_planetoids::play([[maybe_unused]] const mj::game_data &data)
    {
        _player.update();

        if (bn::keypad::a_pressed())
        {
            if (bullets.size() != bullets.max_size()) // this makes it so that only the max amount of bullets can be on screen at a time, i tried to resize rthe bullets vector but could not so i did this bandaid fix
            {
                bullets.push_back(aaa_Bullet(bn::fixed_point(0, 0), 5, _player.getAngle()));
            }
        }

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].update();
        }

        // I am aware that this is a nested for loop, but trying to make this operate inside the classes would have required passing in the information for the enemy vector
        // I am not at this time able to dedicate that much mental power to solve this, so i instead have a nested loop to check each bullet to each enemy
        for (int i = bullets.size() - 1; i >= 0; i--)
        {
            bullets[i].update();

            bn::fixed bX = bullets[i].BulletPos().x();
            bn::fixed bY = bullets[i].BulletPos().y();

            for (int j = 0; j < enemies.size(); j++)
            {
                if (bullets[i].getRect().intersects(enemies[j].getRect()))
                {
                    enemies.erase(enemies.begin() + j);
                }
            }
            if (bX > bn::display::width() / 2 || bY > bn::display::height() / 2 || bX < -bn::display::width() / 2 || bY < -bn::display::height() / 2)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        return mj::game_result();
    }

    bool aaa_planetoids::victory() const
    {
        // kind of jank but it works if we are hardcoding the inital amount of enemies
        if (enemies.max_size() - enemies.size() > 1)
        {
            return true;
        }
        return false;
    }

    void aaa_planetoids::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    void aaa_planetoids::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }
}