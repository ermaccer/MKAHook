#pragma once

void makeJal(unsigned int addr, void* func);
void patchInt(unsigned int addr, int data);