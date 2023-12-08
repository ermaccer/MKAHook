#include "mkahook.h"
#include "mkarmageddon.h"
#include "inf.h"
#include "mkamenu.h"
#include "ps2mem.h"

int single_fight_text = -1;
int single_fight_active = 0;
int frontend_timer = 0;
int variable = 0;
int originalSelected = 0;
void init_variables()
{
	single_fight_text = -1;
	single_fight_active = 0;
	frontend_timer = get_game_tick();
	variable = 75068;
	originalSelected = 0;
}

void process_mkahook()
{
	if (get_game_state() == STATE_GAME)
		process_single_fight();
	
	if (get_game_state() == STATE_GAME)
		Menu_Process();
	else if (get_game_state() == STATE_KONQUEST || get_game_state() == STATE_KRYPT || get_game_state() == STATE_MOTOR_KOMBAT)
		Misc_ProcessCameras();
	else
	{
		Menu_Unset();
	}

}

void hook_render()
{
	process_mkahook();
	render();
}

void hook_menu_create_proc()
{
	int procResult = 0;
	single_fight_text = -1;
	if (create_mkproc_generic_nostack(12001, 32, &p_mkahook_menu_proc, 12, &procResult))
		*(int*)(procResult + 8) = 0;


	((void(*)())0x181AD0)();
}

void toggle_single_fight()
{
	if (get_game_tick() - frontend_timer <= 15) return;
	frontend_timer = get_game_tick();
	single_fight_active = !single_fight_active;
	if (single_fight_active)
		snd_req(SINGLEFIGHT_ACTIVATE_SND);
	else
		snd_req(SINGLEFIGHT_DEACTIVATE_SND);
}

void hook_set_single_fight()
{
	player_info* plr2_info = (player_info*)PLAYER2_INFO;

	if (single_fight_active)
	plr2_info->selected = 0;
	start_plyrs();
	//plr2_info->selected = originalSelected;
}

void process_single_fight()
{
	if (single_fight_active && get_game_mode() == MODE_VERSUS)
	{
		player_info* plr2_info = (player_info*)PLAYER2_INFO;
		int winner = *(int*)0x64E124;
		if (winner == 1)
		{
			plr2_info->selected = 2;
		}
		else
			plr2_info->selected = 0;

	}
}

float p_mkahook_menu_proc()
{
	int apdata = *(int*)PROC_DATA;
	float result = 0.0f;
	static int alpha = 254;
	static int go_up = 0;
	if (single_fight_text == -1)
	{
		load_font(8);
		single_fight_text = string_left_xy(0, 0, "SINGLE FIGHT ACTIVE", 50, 400, 1);
	}

	if (check_switch(0, PAD_L3))
		toggle_single_fight();

	if (single_fight_active)
	{
		if (go_up)
			alpha += 1;
		else
			alpha -= 1;


		if (alpha < 123)
		{
			go_up = 1;
			alpha = 124;
		}
		if (alpha > 254)
		{
			alpha = 253;
			go_up = 0;
		}




		string_set_alpha(0, alpha);
	}
	else
	{
		alpha = 254;
		string_set_alpha(0, 0);
	}


	result = 1.0f;

	return result;
}

