#pragma once

struct char_info_entry
{
	char* name;
	int file_table;
	int alt_file_table;
	char* scriptName;
	char* loadName;
};


void dump_character_info();
void patch_new_table();