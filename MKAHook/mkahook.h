#pragma once
//#define BOSS_TOWER
//#define SSF_DUMPER

#define SINGLEFIGHT_ACTIVATE_SND 75037
#define SINGLEFIGHT_DEACTIVATE_SND 75034

void init_variables();
void process_mkahook();
void hook_render();

void hook_menu_create_proc();
void toggle_single_fight();
void hook_set_single_fight();
void process_single_fight();
float p_mkahook_menu_proc();

extern int variable;
extern float headDistance;
extern float headOffset;