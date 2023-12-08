#include "mkarmageddon.h"


int randu(int max)
{
	return ((int(*)(int))0x185C30)(max);
}

void _printf(char* format, ...)
{
	((void(*)(const char*, ...))0x1DCC58)(format);
}

void load_ssf(mem_ssf_header* ssf)
{
	((void(*)(mem_ssf_header*))0x26F070)(ssf);
}

void load_font(int id)
{
	((void(*)(int))0x16FC70)(id);
}

void set_cam_pos(CVector* pos)
{
	((void(*)(CVector*))0x17E3A0)(pos);
}

void set_cam_rot(CVector* rot)
{
	((void(*)(CVector*))0x17E360)(rot);
}

void set_cam_target(CVector* target)
{
	((void(*)(CVector*))0x17E060)(target);
}

void render()
{
	((void(*)())0x126940)();
}

void pause(int i)
{
	((void(*)(int))0x182BB0)(i);
}

void get_bone_pos(int obj, int id, CVector* pos)
{
	((void(*)(int, int, CVector*))0x13A710)(obj, id, pos);
}

void setup_fatality_scene()
{
	((void(*)())0x263720)();
}

int string_left_xy(int id, int font, char* text, int y, int x, int unk)
{
	return ((int(*)(int, int, char*, int, int, int))0x16F990)(id, font, text, y, x, unk);
}

void update_string(int string, int font, char* newText)
{
	((void(*)(int, int, char*))0x16EF70)(string, font, newText);
}

void string_set_alpha(int id, int alpha)
{
	((void(*)(int, int))0x183AF0)(id, alpha);
}

int create_mkproc_generic_nostack(int id, int a2, void* pFunc, int unk, int* result)
{
	return ((int(*)(int, int, void*, int, int*))0x12DE80)(id, a2, pFunc, unk, result);
}

int check_switch(int player, int id)
{
	return ((int(*)(int, int))0x1636F0)(player, id);
}

void get_stick_pos(int player, int stick, float* x, float* y)
{
	((void(*)(int, int, float*, float*))0x1632F0)(player, stick, x, y);
}

int get_game_state()
{
	return *(int*)0x69F014;
}

int get_game_mode()
{
	return *(int*)(0x64DEA4);
}

int get_game_tick()
{
	return *(int*)(0x64DEB4);
}

void get_matrix_forward(int obj, CVector* mat)
{
	mat->x = *(float*)(*(int*)(obj + 40) + 32 + 0);
	mat->y = *(float*)(*(int*)(obj + 40) + 32 + 4);
	mat->z = *(float*)(*(int*)(obj + 40) + 32 + 8);
}

void get_matrix_right(int obj, CVector* mat)
{
	mat->x = *(float*)(*(int*)(obj + 40) + 0);
	mat->y = *(float*)(*(int*)(obj + 40) + 4);
	mat->z = *(float*)(*(int*)(obj + 40) + 8);
}

void obj_set_scale(int obj, CVector* scale)
{
	((void(*)(int, CVector*))0x138150)(obj, scale);
}

void set_game_speed(float speed)
{
	*(float*)0x64DE94 = speed;
}

int get_konquest_hero()
{
	int konquest_data = *(int*)(PLAYER1_INFO + 0x30);
	if (!konquest_data)
		return 0;

	return *(int*)(konquest_data + 48);
}

int snd_req(int id)
{
	return ((int(*)(int))0x12BF10)(id);
}

void xfer_proc(int proc, void* xref)
{
	((void(*)(int, void*))0x12ECF0)(proc, xref);
}

void start_plyrs()
{
	((void(*)())0x136360)();
}

void MKArmageddon_Init()
{

}