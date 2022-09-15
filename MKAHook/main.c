#include <stdio.h>
#include "ps2mem.h"
#include "mkarmageddon.h"
#include "mkahook.h"
#include "stage.h"
#include "character.h"

int CompatibleCRCList[] = { 0x104F08F4 };

void init()
{
    MKArmageddon_Init();
    makeJal(0x33471C, hook_get_one_tower);
}

int main()
{
    return 0;
}
