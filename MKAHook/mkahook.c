#include "mkahook.h"
#include "mkarmageddon.h"

// 8 - boss
// 7 - sub boss
// 1-6 - fighters


short sub_bosses[] = {
	GORO, KINTARO, SHAOKAHN, MOTARO, ONAGA,MOLOCH
};

short characters[] = {
	ASHRAH,BARAKA,BORAICHO,
	CAGE,CHAMELEON,CYRAX,
	DAEGON,DAIROU,DARRIUS,DRAHMIN,
	ERMAC,FROST,FUJIN,HAVIK,HOTARU,
	HSUHAO,JADE,JAREK,JAX,KABAL,KAI,KANO,KENSHI,
	KIRA,KITANA,KOBRA,KUNGLAO,QUANCHI,
	LIMEI,LIUKANG,MAVADO,MEAT,MILEENA,
	MOKAP,NIGHTWOLF,NITARA,NOOB,RAIDEN,SHINNOK,
	RAIN,REIKO,REPTILE,SAREENA,SCORPION,
	SEKTOR,SHEEVA,SHUJINKO,SINDEL,SMOKE,
	SONYA,STRYKER,SUBZERO,TANYA,TAVEN,
	SHANGTSUNG
};

short backgrounds[] = {
	BGS_SUBWAY,
	BGS_PRISON,
	BGS_ARMORY,
	BGS_BELLTOWER,
	BGS_NIS_BGND,
	BGS_GOROS_LAIR,
	BGS_BATTLEARENA,
	BGS_WASTELANDS,
	BGS_REPTILESLAIR,
	BGS_HELL,
	BGS_LUMBERMILL,
	BGS_PYRAMIDTOP,
	BGS_SKYTEMPLE,
	BGS_FALLINGCLIFFS,
	BGS_HELLSFOUNDRY,
	BGS_NETHERBELLY,
	BGS_METEORSTORM,
	BGS_FIREWELL,
	BGS_SOULCHAMBER,
	BGS_EVILTOWER,
	BGS_OUTWORLDSPIRE,
	BGS_KON_JUNGLE_4,
	BGS_KON_ICEPATH_ARENA_1,
	BGS_KON_ICEPALACE_ARENA_1,
	BGS_KON_OBELISK_2,
	BGS_KON_FIREMOUNTAIN,
	BGS_KON_INNERSPIRE,
	BGS_KON_THRONEROOM,
	BGS_KON_MAPROOM,
	BGS_KON_SK_THRONEROOM,
	BGS_KON_OBELISK_1,
	BGS_KON_PRISON_2,
	BGS_KON_SK_BALCONY,
	BGS_KON_SCORPIONS_LAIR,
	BGS_KON_FINAL_BATTLE,
	BGS_KON_FOREST_FA,
	BGS_KON_RED_CAVE_FA,
};

struct ladder_entry my_ladder[8];


int hook_get_one_tower(int max)
{
	make_custom_tower();
	// return 0 so that first tower always gets picked
	return 0;
}

void make_custom_tower()
{
	int ladder_addr = 0x5E4CB0;
	for (int i = 0; i < 8; i++)
	{
		int fighter_id = -1;
		int background_id = -1;
		int table_size = 0;
		// boss
		if (i == 7)
		{
			fighter_id = BLAZE;
			background_id = BGS_PYRAMIDTOP;
		}
#ifndef BOSS_TOWER
		else if (i == 6) // sub boss
		{
			table_size = sizeof(sub_bosses) / sizeof(sub_bosses[0]);
			fighter_id = sub_bosses[randu(table_size)];
		}
		else
		{
			table_size = sizeof(characters) / sizeof(characters[0]);
			fighter_id = characters[randu(table_size)];


			while (is_in_my_ladder(fighter_id))
				fighter_id = characters[randu(table_size)];
		}
		table_size = sizeof(backgrounds) / sizeof(backgrounds[0]);
		if (!(background_id == BGS_PYRAMIDTOP))
		{
			background_id = backgrounds[randu(table_size)];

			while (is_map_in_my_ladder(background_id))
				background_id = backgrounds[randu(table_size)];
		}
#endif
#ifdef BOSS_TOWER
		//SHANG TSUNG 
		//GORO
		//KINTARO
		//MOTARO
		//MOLOCH
		//SHAO KAHN
		//ONAGA
		switch (i)
		{
		case 6:
			fighter_id = SHAOKAHN; 
			background_id = BGS_KON_SK_THRONEROOM;
			break;
		case 5:
			fighter_id = ONAGA; 
			background_id = BGS_OUTWORLDSPIRE;
			break;
		case 4:
			fighter_id = MOLOCH;
			background_id = BGS_GOROS_LAIR;
			break;
		case 3:
			fighter_id = MOTARO; 
			background_id = BGS_KON_SK_BALCONY;
			break;
		case 2:
			fighter_id = KINTARO; 
			background_id = BGS_BATTLEARENA;
			break;
		case 1:
			fighter_id = GORO; 
			background_id = BGS_GOROS_LAIR;
			break;
		case 0:
			fighter_id = SHANGTSUNG; 
			background_id = BGS_KON_THRONEROOM;
			break;
		default:
			break;
		}
#endif


		game_printf("Setting %d as %d on %d\n", i, fighter_id, background_id);
		my_ladder[i].background = my_ladder[i].backgroundLocked = background_id;
		my_ladder[i].character = my_ladder[i].characterLocked = fighter_id;
	}

	for (int i = 0; i < 8; i++)
	{
		int ladder_entry_addr = (ladder_addr + (sizeof(struct ladder_entry) * i));
		*(struct ladder_entry*)(ladder_entry_addr) = my_ladder[i];
	}
}

int is_in_my_ladder(int id)
{
	int result = 0;
	for (int i = 0; i < 8; i++)
	{
		if (my_ladder[i].character == id)
			result = 1;
	}
	// hack for onaga since he's 10 for some reason
	if (id == ONAGA)
		result = 1;
	return result;
}

int is_map_in_my_ladder(int id)
{
	int result = 0;
	for (int i = 0; i < 8; i++)
	{
		if (my_ladder[i].background == id)
			result = 1;
	}

	return result;
}

