#pragma once
#include "ssf.h"

#define PLAYER1_INFO   0x66012C
#define PLAYER2_INFO   0x660174
#define PLAYER_DATA    0x5D63A4 
#define PROC_DATA	   0x64DF4C
#define KONQUEST_DATA  0x64F250


typedef struct
{
	float x, y, z;
}CVector;


int randu(int max);
void _printf(char* format, ...);
void load_ssf(mem_ssf_header* ssf);
void load_font(int id);
void set_cam_pos(CVector* pos);
void set_cam_rot(CVector* rot);
void set_cam_target(CVector* target);
void render();
void pause(int i);
void get_bone_pos(int obj, int id, CVector* pos);
void setup_fatality_scene();

int string_left_xy(int id, int font, char* text, int y, int x, int unk);
void update_string(int string, int font, char* newText);
void string_set_alpha(int id, int alpha);
int create_mkproc_generic_nostack(int id, int a2, void* pFunc, int unk, int* result);
int check_switch(int player, int id);
void get_stick_pos(int player, int stick, float* x, float* y);

int get_game_state();
int get_game_mode();
int get_game_tick();
void get_matrix_forward(int obj, CVector* mat);
void get_matrix_right(int obj, CVector* mat);
void obj_set_scale(int obj, CVector* scale);
void set_game_speed(float speed);

int get_konquest_hero();

int snd_req(int id);

void xfer_proc(int proc, void* xref);

void start_plyrs();

enum characters
{
		ASHRAH,
		BARAKA,
		BORAICHO,
		BLAZE,
		CAGE,
		CHAMELEON,
		CYRAX,
		DAEGON,
		DAIROU,
		DARRIUS,
		ONAGA,
		DRAHMIN,
		ERMAC,
		FROST,
		FUJIN,
		GORO,
		HAVIK,
		HOTARU,
		HSUHAO,
		JADE,
		JAREK,
		JAX,
		KABAL,
		KAI,
		KANO,
		KENSHI,
		KINTARO,
		KIRA,
		KITANA,
		KOBRA,
		KUNGLAO,
		LIMEI,
		LIUKANG,
		MAVADO,
		MEAT,
		MILEENA,
		MOKAP,
		MOLOCH,
		MOTARO,
		NIGHTWOLF,
		NITARA,
		NOOB,
		QUANCHI,
		RAIDEN,
		RAIN,
		REIKO,
		REPTILE,
		SAREENA,
		SCORPION,
		SEKTOR,
		SHANGTSUNG,
		SHAOKAHN,
		SHEEVA,
		SHINNOK,
		SHUJINKO,
		SINDEL,
		SMOKE,
		SONYA,
		STRYKER,
		SUBZERO,
		TANYA,
		TAVEN,
		KAF,
		RANDOM,
};
enum backgrounds {
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
	BGS_LADDER,
	BGS_KRYPT,
	BGS_PSELECT,
	BGS_CAP_PYRAMID,
	BGS_KREDITS,
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
	BGS_KART_TRACK_LINKUEI,
	BGS_KART_TRACK_VOLCANO,
	BGS_KART_TRACK_JUNGLE,
	BGS_KART_TRACK_DESERT,
	BGS_KART_TRACK_MOTORTOWN
};
enum game_state {
	STATE_0,
	STATE_1,
	STATE_2,
	STATE_ATTRACT,
	STATE_SELECT,
	STATE_5,
	STATE_GAME,
	STATE_8,
	STATE_MENU,
	STATE_9,
	STATE_KRYPT,
	STATE_MOTOR_KOMBAT = 18,
	STATE_KONQUEST = 24

};

enum game_mode {
	MODE_ARCADE,
	MODE_VERSUS,
	MODE_2,
	MODE_PRACTICE,
};

enum pad_button {
	PAD_L2,
	PAD_R2,
	PAD_L1,
	PAD_R1,
	PAD_TRIANGLE,
	PAD_CIRCLE,
	PAD_CROSS,
	PAD_SQUARE,
	PAD_SELECT,
	PAD_L3,
	PAD_R3,
	PAD_START,
	PAD_UP,
	PAD_RIGHT,
	PAD_DOWN,
	PAD_LEFT,
	PAD_ANY,
	PAD_L2R2,

};

typedef struct
{
	int field_0;
	int field_4;
	int selected;
	float field_C;
	char field_10;
	char field_11;
	char field_12;
	char field_13;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	char field_24;
	char field_25;
	char field_26;
	char field_27;
	char field_28;
	char field_29;
	char field_2A;
	char field_2B;
	int characterID;
	int field_30;
	int pObject;
	int field_38;
	int field_3C;
	int field_40;
	int numWins;
}player_info;


void MKArmageddon_Init();