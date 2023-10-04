#include <algorithm>

#include "../doomstat.h"
#include "../g_game.h"
#include "../k_hud.h"
#include "../p_local.h"
#include "../r_fps.h"
#include "../v_draw.hpp"

using srb2::Draw;

namespace
{

constexpr INT32 kHudFlags = V_HUDTRANS | V_SLIDEIN;

tic_t player_timer(const player_t* player)
{
	return K_TranslateTimer(player->realtime, 0, nullptr);
}

}; // namespace

void K_drawKart2PTimestamp(void)
{
	auto get_row = []
	{
		if (R_GetViewNumber() == 0)
		{
			return Draw(287, 33).flags(V_SNAPTOTOP);
		}
		else
		{
			return Draw(287, 156).flags(V_SNAPTOBOTTOM);
		}
	};

	Draw row = get_row().flags(kHudFlags | V_SNAPTORIGHT).font(Draw::Font::kZVote);

	row.patch("K_STTIMS");
	row.xy(12, 2).text("{:03}", player_timer(stplyr) / TICRATE);
}

void K_drawKart4PTimestamp(void)
{
	Draw row = Draw(154, 0).flags(kHudFlags).font(Draw::Font::kZVote).align(Draw::Align::kCenter);

	auto draw = [](const Draw& row, tic_t time)
	{
		row.patch("K_STTIMS");
		row.xy(5, 12).text("{:03}", time / TICRATE);
	};

	auto time_of = [](int k) -> tic_t { return k <= r_splitscreen ? player_timer(&players[displayplayers[k]]) : 0u; };

	draw(row.y(1).flags(V_SNAPTOTOP), std::max(time_of(0), time_of(1)));
	draw(row.y(178).flags(V_SNAPTOBOTTOM), std::max(time_of(2), time_of(3)));
}
