#include "mkamenu.h"
#include <stdio.h>
#include "pcsx2/mips.h"
#include "ps2mem.h"
#include "inf.h"
#define TRUE_FALSE(x) x ? "true" : "false"

CVector camPos;
CVector camRot;

struct Menu TheMenu;
float headOffset = 0.0f;
float headDistance = 0.15f;

float headOffset3 =1.0f;
float headDistance3 = -2.15f;

int m_nCurrentPos = 0;
int m_nCurrentMenuOpen = MENU_DEFAULT;
int hook_timer = 0;

int m_bScaleModifier = 0;
float m_nP1Scale = 1.0;
float m_nP2Scale = 1.0;

int m_bFirstPersonCam = 0;
int m_bThirdPersonCam = 0;
int m_bFreeCamera = 0;
int m_bKonquestFPCam = 0;
int m_bFreezeWorld = 0;

int menuAssoc[MENU_MAX_STRINGS * 2] =
{
	MENU_BAR_0,
	MENU_BAR_1,
	MENU_BAR_2,
	MENU_BAR_3,
	MENU_BAR_4,
	MENU_BAR_5,
	MENU_BAR_6,
	MENU_BAR_7,
	MENU_BAR_8,
	MENU_BAR_9,
};

int menuStrings[MENU_MAX_STRINGS] = {};
int titleBar;

const char* menuNames[MENU_MAX_STRINGS] =
{
	"Player",
	"Camera",
	"Misc.",
};

const char* menuNamesPlayer[MENU_MAX_STRINGS] =
{
	"P1 Scale Modifier",
	"P2 Scale Modifier",
	"Enable Scale Modifier",
	"Reset Scale Values"
};

const char* menuNamesCamera[MENU_MAX_STRINGS] =
{
	"First Person Camera",
	"Third Person Camera",
	"Set FOV to 72 (default)",
	"Set FOV to 80 (ws default)",
	"Set FOV to 95",
	"Set FOV to 110",
	"Set FOV to 120",
	"Free Camera"
};

const char* menuNamesMisc[MENU_MAX_STRINGS] =
{
	"Kill HUD",
	"Freeze World",
	"Slowmotion",
	"Reset Speed"
};

struct Menu GetMenu()
{
	return TheMenu;
}

int Menu_Init(int id, int font, char* text, int x, int y, int unk)
{
	int result = string_left_xy(id, font, text, x, y, unk);
	int offset = 0;
	titleBar = string_left_xy(MENU_BAR_0 - 1, 0, "MKAHook by ermaccer", x, y - 40, 88);
	TheMenu.m_bIsReady = 0;
	for (int i = 0; i < MENU_MAX_STRINGS; i++)
	{
		int offset = i + 1;
		static char tmp[128] = {};
		sprintf(tmp, "", i);
		menuStrings[i] = string_left_xy(menuAssoc[i], 0, tmp, x, y - 60 - (15 * (offset)), 88);
	}
	TheMenu.m_bIsReady = 1;
	TheMenu.m_bActive = 0;
	TheMenu.plrPos.x = 0;
	TheMenu.plrPos.y = 0;
	TheMenu.plrPos.z = 0;
	m_bFirstPersonCam = 0;
	m_bFreeCamera = 0;
	m_bThirdPersonCam = 0;
	hook_timer = get_game_tick();
	m_nCurrentPos = 0;
	m_bScaleModifier = 0;
	return result;
}

void Menu_Draw()
{
	if (!TheMenu.m_bIsReady)
		return;

	if (TheMenu.m_bActive)
	{
		string_set_alpha(MENU_BAR_0 - 1, 255);

		int str = TOTAL_MENU_DEFAULT;
		if (m_nCurrentMenuOpen == MENU_DEFAULT)
			str = TOTAL_MENU_DEFAULT;
		if (m_nCurrentMenuOpen == MENU_PLAYER)
			str = TOTAL_PLAYER;
		if (m_nCurrentMenuOpen == MENU_MISC)
			str = TOTAL_MISC;
		if (m_nCurrentMenuOpen == MENU_CAMERA)
			str = TOTAL_CAMERA;
		for (int i = 0; i < str; i++)
		{
			if (m_nCurrentMenuOpen == MENU_DEFAULT)
				update_string(menuStrings[i], 0, menuNames[i]);
			if (m_nCurrentMenuOpen == MENU_PLAYER)
			{
				char tmp[256] = {};
				switch (m_nCurrentPos)
				{
				case 0:
					sprintf(tmp, "%s %d", "Value - ", (int)(m_nP1Scale * 100));
					break;
				case 1:
					sprintf(tmp, "%s %d", "Value - ", (int)(m_nP2Scale * 100));
					break;
				case 2:
					sprintf(tmp, "%s %s", "Value - ", TRUE_FALSE(m_bScaleModifier));
					break;
				}
			
				update_string(menuStrings[i], 0, menuNamesPlayer[i]);
				update_string(menuStrings[TOTAL_PLAYER + 1], 0, tmp);
			}
			if (m_nCurrentMenuOpen == MENU_CAMERA)
			{
				char tmp[256] = {};
				switch (m_nCurrentPos)
				{
				case 0:
					sprintf(tmp, "%s %s", "Value - ", TRUE_FALSE(m_bFirstPersonCam));
					break;
				case 1:
					sprintf(tmp, "%s %s", "Value - ", TRUE_FALSE(m_bThirdPersonCam));
					break;
				case FREE_CAMERA:
					sprintf(tmp, "%s %s", "Value - ", TRUE_FALSE(m_bFreeCamera));
					break;
				default:
					sprintf(tmp, "Restart match for FOV changes to apply.");
					break;
				}
				update_string(menuStrings[TOTAL_CAMERA + 1], 0, tmp);
				update_string(menuStrings[i], 0, menuNamesCamera[i]);
			}
			if (m_nCurrentMenuOpen == MENU_MISC)
			{
				char tmp[256] = {};
				update_string(menuStrings[TOTAL_PLAYER + 1], 0, tmp);
				update_string(menuStrings[i], 0, menuNamesMisc[i]);
			}

			if (m_nCurrentPos == i)
				string_set_alpha(menuAssoc[i], 255);
			else
				string_set_alpha(menuAssoc[i], 128);
		
		
		
		}
	}
	else
	{
		string_set_alpha(MENU_BAR_0 - 1, 0);
	
		for (int i = 0; i < MENU_MAX_STRINGS; i++)
		{
			string_set_alpha(menuAssoc[i], 0);
		}
	}

}

void Menu_Process()
{
	if (check_switch(0, PAD_L3))
		Menu_Toggle();

	if (GetAsyncKeyState(72))
		Menu_Toggle_FreezeWorld();

	if (GetAsyncKeyState(71))
		Menu_Toggle_FreeCam();


	if (TheMenu.m_bActive)
	{
		if (check_switch(0, PAD_CROSS))
			Menu_KeyCross();
		
		if (check_switch(0, PAD_TRIANGLE))
			Menu_KeyTriangle();
	
		if (check_switch(0, PAD_CIRCLE))
			Menu_KeyCircle();
	
		if (check_switch(0, PAD_UP))
			Menu_KeyUp();
	
		if (check_switch(0, PAD_DOWN))
			Menu_KeyDown();
	
		int str = TOTAL_MENU_DEFAULT;
	
		if (m_nCurrentMenuOpen == MENU_PLAYER)
			str = TOTAL_PLAYER;
		if (m_nCurrentMenuOpen == MENU_MISC)
			str = TOTAL_MISC;
		if (m_nCurrentMenuOpen == MENU_CAMERA)
			str = TOTAL_CAMERA;
	
		if (m_nCurrentPos < 0) m_nCurrentPos = str - 1;
		if (m_nCurrentPos >= str) m_nCurrentPos = 0;
	}
	Menu_Draw();
	Menu_Process_Toggles();
}

void Menu_Process_Toggles()
{

	if (m_bScaleModifier)
	{
		update_player1_scale();
		update_player2_scale();
	}
	if (m_bFirstPersonCam || m_bThirdPersonCam)
		Menu_ProcessCustomCams();
	else
		Menu_ProcessFreeCamera();
}

void Menu_Toggle()
{
	if (get_game_tick() - hook_timer <= 15) return;
	hook_timer = get_game_tick();
	TheMenu.m_bActive = !TheMenu.m_bActive;

	if (TheMenu.m_bActive)
		pause(1);
	else
		pause(0);
}

void Menu_KeyUp()
{
	if (get_game_tick() - hook_timer <= 10) return;
	hook_timer = get_game_tick();
	m_nCurrentPos -= 1;
}

void Menu_KeyDown()
{
	if (get_game_tick() - hook_timer <= 10) return;
	hook_timer = get_game_tick();
	m_nCurrentPos += 1;
}

void Menu_KeyCross()
{
	if (get_game_tick() - hook_timer <= 10) return;
	hook_timer = get_game_tick();
	Menu_ClearStrings();
	if (m_nCurrentMenuOpen == MENU_DEFAULT)
		m_nCurrentMenuOpen = m_nCurrentPos;
	else
	{
	if (m_nCurrentMenuOpen == MENU_PLAYER)
		Menu_ProcessPlayer();
	if (m_nCurrentMenuOpen == MENU_MISC)
		Menu_ProcessMisc();
	if (m_nCurrentMenuOpen == MENU_CAMERA)
		Menu_ProcessCamera();
	}

}

void Menu_KeyCircle()
{
	if (get_game_tick() - hook_timer <= 10) return;
	hook_timer = get_game_tick();
	if (!(m_nCurrentMenuOpen == MENU_DEFAULT))
	m_nCurrentMenuOpen = MENU_DEFAULT;
	Menu_ClearStrings();
}

void Menu_KeyTriangle()
{
	if (get_game_tick() - hook_timer <= 10) return;
	hook_timer = get_game_tick();

	if (m_nCurrentMenuOpen == MENU_PLAYER)
		Menu_ProcessPlayerReverse();
}

void Menu_ProcessPlayer()
{
	switch (m_nCurrentPos)
	{
	case 0:
		m_nP1Scale += 0.1f;
		break;
	case 1:
		m_nP2Scale += 0.1f;
		break;
	case 2:
		m_bScaleModifier= !m_bScaleModifier;
		break;
	case 3:
		m_nP1Scale = 1.0f;
		m_nP2Scale = 1.0f;
		break;
	default:
		break;
	}
}

void Menu_ProcessPlayerReverse()
{
	switch (m_nCurrentPos)
	{
	case 0:
		m_nP1Scale -= 0.1f;
		if (m_nP1Scale < 0)
			m_nP1Scale = 0;
		break;
	case 1:
		m_nP2Scale -= 0.1f;

		if (m_nP2Scale < 0)
			m_nP2Scale = 0;
		break;
	default:
		break;
	}
}

void Menu_ProcessMisc()
{
	switch (m_nCurrentPos)
	{
	case 0:
		setup_fatality_scene();
		break;
	case 1:
		set_game_speed(0.0f);
		break;
	case 2:
		set_game_speed(0.5f);
		break;
	case 3:
		set_game_speed(1.0f);
		break;
	default:
		break;
	}
}

void Menu_ProcessCamera()
{
	switch (m_nCurrentPos)
	{
	case 0:
		m_bFirstPersonCam = !m_bFirstPersonCam;
		break;
	case 1:
		m_bThirdPersonCam = !m_bThirdPersonCam;
		break;
	case FOV_72:
		setFov(72.0f);
		break;
	case FOV_90:
		setFov(80.0f);
		break;
	case FOV_95:
		setFov(95.0f);
		break;
	case FOV_110:
		setFov(110.0f);
		break;
	case FOV_120:
		setFov(120.0f);
		break;
	case FREE_CAMERA:
		m_bFreeCamera = !m_bFreeCamera;
		break;
	default:
		break;
	}
}

void Menu_ClearStrings()
{
	string_set_alpha(MENU_BAR_0 - 1, 0);

	for (int i = 0; i < MENU_MAX_STRINGS; i++)
	{
		string_set_alpha(menuAssoc[i], 0);
	}
}

void Menu_Unset()
{
	TheMenu.m_bIsReady = 0;
}

void Menu_ProcessCustomCams()
{
	player_info plr1 = *(player_info*)PLAYER1_INFO;
	player_info plr2 = *(player_info*)PLAYER2_INFO;
	if (plr1.pObject && plr2.pObject)
	{
		CVector headPos;
		CVector rightMat;
		CVector forwardMat;
		CVector headPosP2;
		static int id = 16;
		if (m_bThirdPersonCam)
			id = 14;
		else
			id = 16;
	
		get_bone_pos(plr1.pObject, id, &headPos);
		get_bone_pos(plr2.pObject, id, &headPosP2);
	
		get_matrix_right(plr1.pObject, &rightMat);
		get_matrix_forward(plr1.pObject, &forwardMat);
	
		if (m_bFirstPersonCam)
		{
			headPos.x += rightMat.x * headOffset;
			headPos.y += rightMat.y * headOffset;
			headPos.z += rightMat.z * headOffset;
	
			headPos.x += forwardMat.x * headDistance;
			headPos.y += forwardMat.y * headDistance;
			headPos.z += forwardMat.z * headDistance;
		}
		else
		{
			headPos.y += headOffset3;
	
			headPos.x += forwardMat.x * headDistance3;
			headPos.y += forwardMat.y * headDistance3;
			headPos.z += forwardMat.z * headDistance3;
		}
	
		set_cam_pos(&headPos);
		set_cam_target(&headPosP2);
	}
}	

void Menu_ProcessFreeCamera()
{
	int camera = *(int*)0x69EAF4;

	int data = *(int*)0x64DF4C;

	if (m_bFreeCamera)
	{
		static float camSpeed = 0.15f;


		CVector rightMat;
		CVector forwardMat;

		get_matrix_right(camera, &rightMat);
		get_matrix_forward(camera, &forwardMat);

		if (GetAsyncKeyState(90))
			camSpeed = 0.07f;
		else
			camSpeed = 0.15f;

		if (GetAsyncKeyState(87))
		{
			camPos.x += camSpeed * forwardMat.x;
			camPos.y += camSpeed * forwardMat.y;
			camPos.z += camSpeed * forwardMat.z;
		}

		if (GetAsyncKeyState(83))
		{
			camPos.x -= camSpeed * forwardMat.x;
			camPos.y -= camSpeed * forwardMat.y;
			camPos.z -= camSpeed * forwardMat.z;
		}
		if (GetAsyncKeyState(65))
		{
			camPos.x += camSpeed * rightMat.x;
			camPos.y += camSpeed * rightMat.y;
			camPos.z += camSpeed * rightMat.z;
		}
		if (GetAsyncKeyState(68))
		{
			camPos.x -= camSpeed * rightMat.x;
			camPos.y -= camSpeed * rightMat.y;
			camPos.z -= camSpeed * rightMat.z;
		}
		if (GetAsyncKeyState(81))
			camPos.y += camSpeed;
		if (GetAsyncKeyState(69))
			camPos.y -= camSpeed;

		if (GetAsyncKeyState(37))
			camRot.y += camSpeed / 4.0f;
		if (GetAsyncKeyState(39))
			camRot.y -= camSpeed / 4.0f;

		if (GetAsyncKeyState(38))
			camRot.x -= camSpeed / 4.0f;
		if (GetAsyncKeyState(40))
			camRot.x += camSpeed / 4.0f;

		if (GetAsyncKeyState(88))
			camRot.z -= camSpeed / 4.0f;
		if (GetAsyncKeyState(67))
			camRot.z += camSpeed / 4.0f;

		//((void(*)(int, int))0x12ECF0)(0xCA3730, 0x40BD20);

		set_cam_pos(&camPos);
		set_cam_rot(&camRot);
	}
	else
	{
		if (camera)
		{
			camPos = *(CVector*)(camera + 192);
			camRot = *(CVector*)(camera + 240);
		}
	
	}

}

void Misc_ProcessCameras()
{
	if (GetAsyncKeyState(71))
		Menu_Toggle_FreeCam();

	if (GetAsyncKeyState(70))
		Menu_Toggle_KFP();

	if (m_bKonquestFPCam)
		konquest_camera();

	Menu_ProcessFreeCamera();
}

void Menu_Toggle_FreeCam()
{
	if (get_game_tick() - hook_timer <= 15) return;
	hook_timer = get_game_tick();
	m_bFreeCamera = !m_bFreeCamera;
}

void Menu_Toggle_KFP()
{
	if (get_game_tick() - hook_timer <= 15) return;
	hook_timer = get_game_tick();
	m_bKonquestFPCam = !m_bKonquestFPCam;
	setFov(100.0f);
}

void setFov(float value)
{
	*(float*)(0x64C3FC) = value;
}

void Menu_Init_Vars()
{
	m_bFreeCamera = 0;
	m_bKonquestFPCam = 0;
	hook_timer = get_game_tick();
}

void konquest_camera()
{		
	static float camSpeed = 0.15f;
	
	int hero = get_konquest_hero();
	
	if (hero)
	{
		CVector headPos;
		CVector forwardMat;

		get_bone_pos(hero, 16, &headPos);
		get_matrix_forward(hero, &forwardMat);
	
		headPos.x += headDistance * forwardMat.x;
		headPos.y += headDistance * forwardMat.y;
		headPos.z += headDistance * forwardMat.z;
	
		headPos.y += headOffset;

	
		camPos = headPos;
		set_cam_pos(&camPos);
	
		float x, y;
		get_stick_pos(0, 1, &x, &y);
		camRot.y += -x * 0.065f;
		camRot.x += y * 0.065f;
	
		set_cam_rot(&camRot);
	
	}
}

void Menu_Toggle_FreezeWorld()
{
	if (get_game_tick() - hook_timer <= 15) return;
	hook_timer = get_game_tick();
	m_bFreezeWorld = !m_bFreezeWorld;

	if (m_bFreezeWorld)
		set_game_speed(0.0f);
	else
		set_game_speed(1.0f);
}

void update_player1_scale()
{
	player_info plr1 = *(player_info*)PLAYER1_INFO;
	if (plr1.pObject)
	{
		int obj = plr1.pObject;
		float scale = m_nP1Scale;
		CVector s = { scale, scale, scale };
		obj_set_scale(obj, &s);
	}
}

void update_player2_scale()
{
	player_info plr2 = *(player_info*)PLAYER2_INFO;
	if (plr2.pObject)
	{
		int obj = plr2.pObject;
		float scale = m_nP2Scale;
		CVector s = { scale, scale, scale };
		obj_set_scale(obj, &s);
	}
}
