#include "mkarmageddon.h"

int(*randu)(int max);
void (*game_printf)(char* format, ...);
void (*load_ssf)(struct mem_ssf_header* ssf);
void(*set_cam_pos)(struct CVector* pos);
void(*set_cam_rot)(struct CVector* rot);
void(*set_cam_target)(struct CVector* rot);
void(*render)();

void MKArmageddon_Init()
{
	randu = (void*)(0x185C30);
	game_printf = (void*)(0x1DCC58);
	load_ssf = (void*)(0x26F070);

	render = (void*)0x126940;
	set_cam_pos = (void*)0x17E3A0;
	set_cam_rot = (void*)0x17E360;
	set_cam_target = (void*)0x17E060;
}