#pragma once




struct mem_ssf_entry {
	char* fileName;
	int   totalFileSize; // padded
	int   fileSize;
};

typedef struct {
	char* fileName;
	int   pad[2];
	struct mem_ssf_entry files[1250];
}mem_ssf_header;



void hook_load_ssf(mem_ssf_header* ptr);