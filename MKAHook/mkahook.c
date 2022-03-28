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
	BGS_ARMORY,
	BGS_BATTLEARENA,
	BGS_BELLTOWER,
	BGS_EVILTOWER,
	BGS_FALLINGCLIFF,
	BGS_FIREWELL,
	BGS_GOROS_LAIR,
	BGS_HELL,
	BGS_HELLSFOUNDRY,
	BGS_LUMBERMILL,
	BGS_PYRAMIDTOP,
	BGS_METEORSTORM,
	BGS_NETHERBELLY,
	BGS_PRISON,
	BGS_REPTILESLAIR,
	BGS_SKYTEMPLE,
	BGS_SOULCHAMBER,
	BGS_SUBWAY,
	BGS_WASTELANDS,
	BGS_OUTWORLDSPIRE,
	BGS_KON_JUNGLE4_ARENA,
	BGS_KON_ICEPATH_ARENA,
	BGS_KON_ICEPALACE_ARENA,
	BGS_KON_FIREMOUNTAIN_ARENA,
	BGS_KON_INNERSPIRE_ARENA1,
	BGS_KON_THRONEROOM,
	BGS_KON_MAPROOM,
	BGS_KON_SK_THRONEROOM,
	BGS_KON_SK_BALCONY,
	BGS_KON_SCORPION_LAIR,
	BGS_KON_FOREST,
	BGS_KON_CAVE_ARENA,
	BGS_KON_RED_CAVE_ARENA,
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
	int ladder_addr = 0x5E7D20;
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

void MKArmageddon_Init()
{
	randu = (void*)(0x1865A0);
	game_printf = (void*)(0x1DD738);
}
