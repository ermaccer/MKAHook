#include "stage.h"

#include "toc.h"



struct mk_file_entry nexus_entry_table[] = {
	{"nexus_arena.ssf"	,0, 4},
	{"nexus_arena.sec"	,0, 1},
	{"nexus_arena.mko"	,0, 3},
	{"nexus_arena_fx.mko"	,0, 3},
};

struct mk_toc_entry nexus_file_table[] = {
		{&nexus_entry_table[0]	,0,0 },
		{&nexus_entry_table[1]	,0,1831936},
		{&nexus_entry_table[2]	,0,34656},
		{&nexus_entry_table[3]	,0,4064},
		{0,0,0}
};


char* script_name = "nexus_arena.mko";


void init_stage_hook()
{
	// from toceditor

	for (int i = 0; i < 4; i++)
	{
		nexus_entry_table[i].belong = &nexus_file_table[0];
	}

	int baseSize = 2048;
	for (int i = 1; i < 4; i++)
	{
		nexus_file_table[i].previousSize = baseSize;
		baseSize += (nexus_file_table[i].size + 2048 - 1) & -2048;
	}

	*(int*)(0x05A0B08) = (int)&nexus_file_table[0];
	*(int*)(0x05A0B08 + 4) = (int)&script_name[0];
}