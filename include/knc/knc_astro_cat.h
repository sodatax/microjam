#ifndef KNC_ASTRO_CAT_H
#define KNC_ASTRO_CAT_H

#include "mj/mj_game.h"
#include "knc/knc_cat.h"
#include "knc/knc_planet.h"
#include "mj/mj_difficulty_level.h"
#include "knc/knc_shooting_star.h"

namespace knc {
    class knc_astro_cat : public mj::game {
    public:
        knc_astro_cat(int completed_games, const mj::game_data& data);

        bn::string<16> title() const override;
        int total_frames() const override;
        mj::game_result play(const mj::game_data& data) override;
        bool victory() const override;
        void fade_in(const mj::game_data& data) override;
        void fade_out(const mj::game_data& data) override;

    private:
        // planet and shooting star speed + num
        static bn::fixed _recommended_speed (mj::difficulty_level difficulty);

        cat _cat;
        mj::difficulty_level _difficulty;
        // easy+ normal + hard
        planet _planet1;     
        planet _planet2;
        planet _planet3;
        
        // added only for normal + hard 
        planet _planet4; 
        shooting_star _star1;
        shooting_star _star2;

        // added only for hard
        shooting_star _star3;
        bool _hit;

    };
}

#endif