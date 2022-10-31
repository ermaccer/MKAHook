#include "mkarmageddon.h"

int(*randu)(int max);
void (*game_printf)(char* format, ...);
void (*load_ssf)(struct mem_ssf_header* ssf);
void MKArmageddon_Init()
{
	randu = (void*)(0x185C30);
	game_printf = (void*)(0x1DCC58);
	load_ssf = (void*)(0x26F070);
}