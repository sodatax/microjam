#include "kgg/kgg_game_name.h"

namespace kgg {

kgg_game_name::kgg_game_name(int completed_games, const mj::game_data& data)
: mj::game("kgg")
{
}

bn::string<16> kgg_game_name::title() const
{
    return "KGG Game";
}

int kgg_game_name::total_frames() const
{
    return 180;
}

mj::game_result kgg_game_name::play(const mj::game_data& data)
{
    return mj::game_result();
}

bool kgg_game_name::victory() const
{
    return false;
}

void kgg_game_name::fade_in(const mj::game_data& data)
{
}

void kgg_game_name::fade_out(const mj::game_data& data)
{
}

}