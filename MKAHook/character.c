#include "character.h"
#include "mkarmageddon.h"
#include <stdio.h>
#include "ps2mem.h"
#include "pcsx2/mips.h"


struct char_info_entry pCharTable[] = {
	{"ASHRAH"	, 0x600C50	, 0x600D70	,"ashrah.mko"	,"load_ashrah.sec"},
	{"BARAKA"	, 0x600F40	, 0x601060	,"baraka.mko"	,"load_baraka.sec"},
	{"BO' RAI CHO"	, 0x601220	, 0x601360	,"boraicho.mko"	,"load_boraicho.sec"},
	{"BLAZE"	, 0x601520	, 0x601520	,"bossblaze.mko"	,"load_blaze.sec"},
	{"CAGE"	, 0x6016B0	, 0x6017A0	,"cage.mko"	,"load_cage.sec"},
	{"CHAMELEON"	, 0x602A70	, 0x602A70	,"chameleon.mko"	,"load_chameleon.sec"},
	{"CYRAX"	, 0x602C20	, 0x602D20	,"cyrax.mko"	,"load_cyrax.sec"},
	{"DAEGON"	, 0x602EE0	, 0x602EE0	,"daegon.mko"	,"load_daegon.sec"},
	{"DAIROU"	, 0x6030A0	, 0x6031C0	,"dairou.mko"	,"load_dairou.sec"},
	{"DARRIUS"	, 0x603380	, 0x6034A0	,"darrius.mko"	,"load_darrius.sec"},
	{"ONAGA"	, 0x603670	, 0x603670	,"dragonking.mko"	,"load_onaga.sec"},
	{"DRAHMIN"	, 0x603810	, 0x603910	,"drahmin.mko"	,"load_drahmin.sec"},
	{"ERMAC"	, 0x603AC0	, 0x603BE0	,"ermac.mko"	,"load_ermac.sec"},
	{"FROST"	, 0x603D90	, 0x603E90	,"frost.mko"	,"load_frost.sec"},
	{"FUJIN"	, 0x604030	, 0x604150	,"fujin.mko"	,"load_fujin.sec"},
	{"GORO"	, 0x604310	, 0x604420	,"goro.mko"	,"load_goro.sec"},
	{"HAVIK"	, 0x6045C0	, 0x6046D0	,"havik.mko"	,"load_havik.sec"},
	{"HOTARU"	, 0x604880	, 0x6049A0	,"hotaru.mko"	,"load_hotaru.sec"},
	{"HSU HAO"	, 0x604B50	, 0x604C50	,"hsuhao.mko"	,"load_hsuhao.sec"},
	{"JADE"	, 0x604E00	, 0x604F10	,"jade.mko"	,"load_jade.sec"},
	{"JAREK"	, 0x6050C0	, 0x6051E0	,"jarek.mko"	,"load_jarek.sec"},
	{"JAX"	, 0x605370	, 0x605480	,"jax.mko"	,"load_jax.sec"},
	{"KABAL"	, 0x605640	, 0x605760	,"kabal.mko"	,"load_kabal.sec"},
	{"KAI"	, 0x6058E0	, 0x6059F0	,"kai.mko"	,"load_kai.sec"},
	{"KANO"	, 0x605BA0	, 0x605C90	,"kano.mko"	,"load_kano.sec"},
	{"KENSHI"	, 0x606010	, 0x606130	,"kenshi.mko"	,"load_kenshi.sec"},
	{"KINTARO"	, 0x6062F0	, 0x606410	,"kintaro.mko"	,"load_kintaro.sec"},
	{"KIRA"	, 0x6065D0	, 0x6066E0	,"kira.mko"	,"load_kira.sec"},
	{"KITANA"	, 0x606890	, 0x606990	,"kitana.mko"	,"load_kitana.sec"},
	{"KOBRA"	, 0x606B40	, 0x606C60	,"kobra.mko"	,"load_kobra.sec"},
	{"KUNG LAO"	, 0x606E30	, 0x606F30	,"kunglao.mko"	,"load_kunglao.sec"},
	{"LI MEI"	, 0x607200	, 0x6070E0	,"limei.mko"	,"load_limei.sec"},
	{"LIU KANG"	, 0x6074E0	, 0x6073C0	,"liukang.mko"	,"load_liukang.sec"},
	{"MAVADO"	, 0x6076A0	, 0x6077A0	,"mavado.mko"	,"load_mavado.sec"},
	{"MEAT"	, 0x607950	, 0x607950	,"meat.mko"	,"load_meat.sec"},
	{"MILEENA"	, 0x607AE0	, 0x607C00	,"mileena.mko"	,"load_mileena.sec"},
	{"MOKAP"	, 0x607DB0	, 0x607DB0	,"mokap.mko"	,"load_mokap.sec"},
	{"MOLOCH"	, 0x607F40	, 0x607F40	,"moloch.mko"	,"load_moloch.sec"},
	{"MOTARO"	, 0x6080B0	, 0x6081B0	,"motaro.mko"	,"load_motaro.sec"},
	{"NIGHTWOLF"	, 0x608380	, 0x6084C0	,"nightwolf.mko"	,"load_nightwolf.sec"},
	{"NITARA"	, 0x608670	, 0x608770	,"nitara.mko"	,"load_nitara.sec"},
	{"NOOB"	, 0x608920	, 0x608A30	,"noob.mko"	,"load_noob.sec"},
	{"QUAN CHI"	, 0x608BF0	, 0x608CF0	,"quanchi.mko"	,"load_quanchi.sec"},
	{"RAIDEN"	, 0x608EA0	, 0x608FC0	,"raiden.mko"	,"load_raiden.sec"},
	{"RAIN"	, 0x609170	, 0x609280	,"rain.mko"	,"load_rain.sec"},
	{"REIKO"	, 0x609430	, 0x609550	,"reiko.mko"	,"load_reiko.sec"},
	{"REPTILE"	, 0x609830	, 0x609710	,"reptile.mko"	,"load_reptile.sec"},
	{"SAREENA"	, 0x6099F0	, 0x609AF0	,"sareena.mko"	,"load_sareena.sec"},
	{"SCORPION"	, 0x609DD0	, 0x609CB0	,"scorpion.mko"	,"load_scorpion.sec"},
	{"SEKTOR"	, 0x609F80	, 0x60A0A0	,"sektor.mko"	,"load_sektor.sec"},
	{"SHANG TSUNG"	, 0x60A280	, 0x60A3C0	,"shangtsung.mko"	,"load_shangtsung.sec"},
	{"SHAO KAHN"	, 0x60A570	, 0x60A6B0	,"shaokahn.mko"	,"load_shaokahn.sec"},
	{"SHEEVA"	, 0x60A880	, 0x60A9A0	,"sheeva.mko"	,"load_sheeva.sec"},
	{"SHINNOK"	, 0x60AB70	, 0x60AC90	,"shinnok.mko"	,"load_shinnok.sec"},
	{"SHUJINKO"	, 0x60AE50	, 0x60AF90	,"shujinko.mko"	,"load_shujinko.sec"},
	{"SINDEL"	, 0x60B150	, 0x60B270	,"sindel.mko"	,"load_sindel.sec"},
	{"SMOKE"	, 0x60B420	, 0x60B540	,"smoke.mko"	,"load_smoke.sec"},
	{"SONYA"	, 0x60B6E0	, 0x60B7E0	,"sonya.mko"	,"load_sonya.sec"},
	{"STRYKER"	, 0x60B9A0	, 0x60BAC0	,"stryker.mko"	,"load_stryker.sec"},
	{"SUB-ZERO"	, 0x60BDA0	, 0x60BC80	,"subzero.mko"	,"load_subzero.sec"},
	{"TANYA"	, 0x60BF30	, 0x60C050	,"tanya.mko"	,"load_tanya.sec"},
	{"TAVEN"	, 0x60C1E0	, 0x60C2F0	,"taven.mko"	,"load_taven.sec"},
	{"CAP"	, 0x602330	, 0x602330	,"cap.mko"	,"load_cap.sec"},
	{"RANDOM"	, 0x609CB0	, 0x609DD0	,"scorpion.mko"	,""},

};

void dump_character_info()
{
	int select_addr = 0x59FE60;
	char msgBuffer[1256];
	for (int i = 0; i < 64; i++)
	{
		struct  char_info_entry chr = *(struct char_info_entry*)(select_addr + (sizeof(struct char_info_entry) * i));
		sprintf(msgBuffer, "{\"%s\"\t, 0x%X\t, 0x%X\t,\"%s\"\t,\"%s\"},\n",
			chr.name,
			chr.file_table,
			chr.alt_file_table,
			chr.scriptName,
			chr.loadName);
		_printf(msgBuffer);
	}
}

void patch_new_table()
{
	int select_addr = 0x59FE60;
	char msgBuffer[1256];
	for (int i = 0; i < 64; i++)
		*(struct char_info_entry*)(select_addr + (sizeof(struct char_info_entry) * i)) = pCharTable[i];

}
