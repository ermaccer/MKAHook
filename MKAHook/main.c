#include <stdio.h>
#include "ps2mem.h"
#include "mkahook.h"

int CompatibleCRCList[] = { 0x433A82D4 };

void init()
{
    MKArmageddon_Init();
    makeJal(0x3357CC, hook_get_one_tower);
    *(int*)0x18DE08 = 0;
}

int main()
{
    return 0;
}
