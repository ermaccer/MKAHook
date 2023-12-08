#include <stdio.h>
#include "ps2mem.h"
#include "mkarmageddon.h"
#include "mkamenu.h"
#include "mkahook.h"
#include "stage.h"
#include "character.h"
#include "ladder.h"
#include "toc.h"

int CompatibleCRCList[] = { 0x104F08F4 };
void null() {}

void dummy() {}
void init()
{
   hook_timer = 0;
   init_ladder_hook();
   init_variables();
   Menu_Init_Vars();
   makeJal(0x122A9C, hook_render);
   makeJal(0x198B84, Menu_Init);

   _printf("MKAHook init!\n");

  // makeJal(0x1554CC, hook_menu_create_proc);
  // makeJal(0x16A848, hook_set_single_fight);


#ifdef SSF_DUMPER
    makeJal(0x133348, hook_load_ssf);
    makeJal(0x1333D0, hook_load_ssf);
    makeJal(0x135608, hook_load_ssf);
    makeJal(0x1357EC, hook_load_ssf);
    makeJal(0x135814, hook_load_ssf);
    makeJal(0x13FED8, hook_load_ssf);
    makeJal(0x151D38, hook_load_ssf);
    makeJal(0x151EEC, hook_load_ssf);
    makeJal(0x151FEC, hook_load_ssf);
    makeJal(0x168C9C, hook_load_ssf);
    makeJal(0x169770, hook_load_ssf);
    makeJal(0x169BC0, hook_load_ssf);
    makeJal(0x16A778, hook_load_ssf);
    makeJal(0x16AB1C, hook_load_ssf);
    makeJal(0x16ABBC, hook_load_ssf);

    makeJal(0x18D258, hook_load_ssf);
    makeJal(0x18DEC4, hook_load_ssf);
    makeJal(0x19A5EC, hook_load_ssf);
    makeJal(0x19A63C, hook_load_ssf);
    makeJal(0x293FA0, hook_load_ssf);
    makeJal(0x2F1A30, hook_load_ssf);
    makeJal(0x2F7FAC, hook_load_ssf);
    makeJal(0x334BF4, hook_load_ssf);
    makeJal(0x339BFC, hook_load_ssf);
    makeJal(0x33A6A0, hook_load_ssf);
    makeJal(0x33B5E4, hook_load_ssf);
    makeJal(0x33DFA8, hook_load_ssf);
    makeJal(0x33E0F8, hook_load_ssf);
    makeJal(0x3DC29C, hook_load_ssf);
    makeJal(0x3DD4DC, hook_load_ssf);
    makeJal(0x3DD504, hook_load_ssf);
    makeJal(0x3DE464, hook_load_ssf);
    makeJal(0x3DE49C, hook_load_ssf);
    makeJal(0x3F1AEC, hook_load_ssf);
    makeJal(0x3F1B10, hook_load_ssf);
    makeJal(0x417F04, hook_load_ssf);
    makeJal(0x418B9C, hook_load_ssf);
    makeJal(0x418FDC, hook_load_ssf);
    makeJal(0x41D31C, hook_load_ssf);
    makeJal(0x41D34C, hook_load_ssf);
    makeJal(0x427A24, hook_load_ssf);
    makeJal(0x436518, hook_load_ssf);
    makeJal(0x4365B0, hook_load_ssf);
    makeJal(0x436684, hook_load_ssf);
    makeJal(0x4366E0, hook_load_ssf);
    makeJal(0x436754, hook_load_ssf);
    makeJal(0x43677C, hook_load_ssf);
    makeJal(0x436824, hook_load_ssf);
    makeJal(0x4393A0, hook_load_ssf);
    makeJal(0x4393E4, hook_load_ssf);
    makeJal(0x439414, hook_load_ssf);
    makeJal(0x43C410, hook_load_ssf);
    makeJal(0x43CA14, hook_load_ssf);
    makeJal(0x43CF88, hook_load_ssf);
    makeJal(0x43D0E0, hook_load_ssf);
    makeJal(0x43E2EC, hook_load_ssf);
    makeJal(0x43E368, hook_load_ssf);
    makeJal(0x4408B8, hook_load_ssf);
    makeJal(0x441ACC, hook_load_ssf);
    makeJal(0x441D8C, hook_load_ssf);
    makeJal(0x4474CC, hook_load_ssf);
    makeJal(0x4476F0, hook_load_ssf);
    makeJal(0x44E8F4, hook_load_ssf);
    makeJal(0x44E918, hook_load_ssf);
    makeJal(0x44EA48, hook_load_ssf);
    makeJal(0x44EC84, hook_load_ssf);
    makeJal(0x44ECCC, hook_load_ssf);
    makeJal(0x44ED08, hook_load_ssf);
    makeJal(0x44EEBC, hook_load_ssf);
    makeJal(0x44FD20, hook_load_ssf);
    makeJal(0x44FE30, hook_load_ssf);
    makeJal(0x44FE98, hook_load_ssf);
    makeJal(0x44FEF8, hook_load_ssf);
    makeJal(0x44FF40, hook_load_ssf);
    makeJal(0x450010, hook_load_ssf);
    makeJal(0x4500C8, hook_load_ssf);
    makeJal(0x450BF8, hook_load_ssf);
    makeJal(0x450D5C, hook_load_ssf);
    makeJal(0x450E6C, hook_load_ssf);
    makeJal(0x450EC4, hook_load_ssf);
    makeJal(0x450F04, hook_load_ssf);
    makeJal(0x450FF0, hook_load_ssf);
    makeJal(0x452944, hook_load_ssf);
    makeJal(0x4529E8, hook_load_ssf);
    makeJal(0x452B24, hook_load_ssf);
    makeJal(0x452BE4, hook_load_ssf);
    makeJal(0x452C5C, hook_load_ssf);
    makeJal(0x452CB0, hook_load_ssf);
    makeJal(0x45305C, hook_load_ssf);
    makeJal(0x4530D4, hook_load_ssf);
    makeJal(0x453164, hook_load_ssf);
    makeJal(0x453728, hook_load_ssf);
    makeJal(0x453764, hook_load_ssf);
    makeJal(0x453984, hook_load_ssf);
    makeJal(0x453A00, hook_load_ssf);
    makeJal(0x45599C, hook_load_ssf);
    makeJal(0x455DCC, hook_load_ssf);
    makeJal(0x455E48, hook_load_ssf);
    makeJal(0x455E88, hook_load_ssf);
    makeJal(0x455F14, hook_load_ssf);
    makeJal(0x455F3C, hook_load_ssf);
    makeJal(0x455FD4, hook_load_ssf);
    makeJal(0x4560C4, hook_load_ssf);
    makeJal(0x456124, hook_load_ssf);
    makeJal(0x456248, hook_load_ssf);
    makeJal(0x456784, hook_load_ssf);
    makeJal(0x49FA58, hook_load_ssf);
    makeJal(0x49FAC8, hook_load_ssf);
    makeJal(0x49FB2C, hook_load_ssf);
    makeJal(0x4F2A5C, hook_load_ssf);
    makeJal(0x4F4730, hook_load_ssf);
    makeJal(0x4F5188, hook_load_ssf);
    makeJal(0x4F68B8, hook_load_ssf);
    makeJal(0x4F6C30, hook_load_ssf);
    makeJal(0x502A4C, hook_load_ssf);
    makeJal(0x512830, hook_load_ssf);
    makeJal(0x514AD8, hook_load_ssf);
    makeJal(0x527684, hook_load_ssf);
    makeJal(0x5276B0, hook_load_ssf);
    makeJal(0x5277D4, hook_load_ssf);
    makeJal(0x527818, hook_load_ssf);
    makeJal(0x527928, hook_load_ssf);
    makeJal(0x52C6BC, hook_load_ssf);
#endif // SSF_DUMPER
}

int main()
{
    return 0;
}
