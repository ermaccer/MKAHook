#include "ssf.h"
#include "mkarmageddon.h"
#include "ps2mem.h"
#include <stdio.h>
#include <string.h>


char ssfName[256] = {};

char ssfBuffer[256] = {};

void hook_load_ssf(struct mem_ssf_header* ptr)
{
	char newName[120] = {};
	char line[128] = {};

	sprintf(newName, "%s", (char*)*(int*)(ptr->fileName));
	
	newName[strlen(newName) - 4] = 0x00;
	{
		game_printf("===START FILE TABLE===\n");
		sprintf(ssfName, "%s\n", newName);
		game_printf(ssfName);
		for (int i = 0; i < 1250; i++)
		{
			if (ptr->files[i].fileName == 0 && ptr->files[i].fileSize == 0)
				break;
			{
				sprintf(line, "%s\n", (char*)*(int*)(ptr->files[i].fileName));
				game_printf(line);

			}
		}
		game_printf("===END FILE TABLE===\n");
	}	

	load_ssf(ptr);
}