#include "main.h"
#include "CodeCave.h"
#include "PatternScan.h"
#include "cfg.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if ( CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)Load, NULL, 0, 0) == NULL ) {
			ExitProcess(GetLastError());
			return FALSE; 
		}

		return TRUE;
	}
	return TRUE;
}

DWORD g_dwSampBaseAddr = NULL;
DWORD g_dwJmpBack[8];
DWORD dwJmpBack = NULL;

unsigned int height = NULL, width = NULL, weight = NULL, miplevels = NULL, italic = NULL, charset = NULL, precision = NULL, quality = NULL, pitch = NULL;
char* Font = "Arial";

__declspec(naked) void placeDialogButtonFontInfo() { // THIS ALSO CHANGES TEXT FONT WHEN YOU PRESS T BUT DONT SEND A MESSAGE

	_asm pushad

	LoadConfig("DialogAndChat", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[0];

	_asm popad

	_asm { 
		push [weight]
		push [height]
		push [Font]
		push [charset]
		mov ecx,esi

		jmp dwJmpBack
	}
}

__declspec(naked) void placeDialogFontInfo() {

	_asm pushad

	LoadConfig("DialogListItems", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[1];

	_asm popad

	_asm { 
		push [weight]
		push [height]
		push [Font]
		push [charset]
		mov ecx,esi

		jmp dwJmpBack
	}
}

__declspec(naked) void placeChatFontInfo() {

	_asm pushad

	LoadConfig("Chat", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack	= g_dwJmpBack[2];

	_asm popad

	_asm { 
		push EAX
		push [Font]
		push [pitch]
		push [quality]
		push [precision]
		push [charset]
		push [italic]
		push [miplevels]
		push [weight]
		push [width]
		push [height]
		push ECX

		jmp dwJmpBack
	}
}

__declspec(naked) void placeChatFontInfoShadow() {

	_asm pushad

	LoadConfig("ChatShadow", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[3];

	_asm popad

	_asm { 
		push [Font]
		push [pitch]
		push [quality]
		push [precision]
		push [charset]
		push [italic]
		push [miplevels]
		push [weight]
		push [width]
		push [height]
		push EAX

		jmp dwJmpBack
	}
}

__declspec(naked) void place3DTextFontInfo() {

	_asm pushad

	LoadConfig("3DTextAndDialogBody", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[4];

	_asm popad

	_asm { 
		push ecx
		push [Font]
		push [pitch]
		push [quality]
		push [precision]
		push [charset]
		push [italic]
		push [miplevels]
		push [weight]
		push [width]
		push [height]
		push EDX

		jmp dwJmpBack
	}
}


__declspec(naked) void place3DTextShadowFontInfo() {

	_asm pushad

	LoadConfig("3DTextAndDialogBodyShadow", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[5];

	_asm popad


	_asm { 
		push eax
		push [Font]
		push [pitch]
		push [quality]
		push [precision]
		push [charset]
		push [italic]
		push [miplevels]
		push [weight]
		push [width]
		push [height]
		push edx

		jmp dwJmpBack
	}
}

__declspec(naked) void placeKillListFontInfo() {

	_asm pushad

	LoadConfig("KillList", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[7];

	_asm popad

	_asm { 
		push [Font]
		push [pitch]
		push [quality]
		push [precision]
		xor eax,eax
		push [charset]
		cmp edx,400h
		push [italic]
		setg al
		push [miplevels]
		push [weight]
		push [width]
		lea eax,[eax+eax+0Ch]
		push [height]
		push ecx

		jmp dwJmpBack
	}
}



__declspec(naked) void placeLicensePlateFontInfo() {

	_asm pushad

	LoadConfig("LicensePlate", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[6];

	_asm popad

	_asm { 
		push ebp
		push [Font]
		push [pitch]
		push [quality]
		push [precision]
		push [charset]
		push [italic]
		push [miplevels]
		push [weight]
		push [width]
		push [height]
		push ecx

		jmp dwJmpBack
	}
}



void WINAPI Load() {
	
	DWORD installaddr[8];
	DWORD oldProt = 0;

	CalculateJumpBackAddresses();

	installaddr[0] = g_dwJmpBack[0] - 0x10; // Chat input + Dialog buttons
	installaddr[1] = g_dwJmpBack[1] - 0x10; // Dialog list items and captions, NOT MAIN BODY!!
	installaddr[2] = g_dwJmpBack[2] - 0x1B; // Chat main font
	installaddr[3] = g_dwJmpBack[3] - 0x1A; // Chat shadow font
	installaddr[4] = g_dwJmpBack[4] - 0x1B; // Dialog body and 3D text label font
	installaddr[5] = g_dwJmpBack[5] - 0x1B; // 3D Text label shadow font
	installaddr[6] = g_dwJmpBack[6] - 0x1C; // ???
	installaddr[7] = g_dwJmpBack[7] - 0x29; // kill list

	VirtualProtect((LPVOID)installaddr[0], 16, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[1], 16, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[2], 27, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[3], 26, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[4], 27, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[5], 27, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[6], 28, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[7], 41, PAGE_EXECUTE_READWRITE, &oldProt);

	HookInstall(installaddr[0], (DWORD)placeDialogButtonFontInfo, 16);
	HookInstall(installaddr[1], (DWORD)placeDialogFontInfo, 16);
	HookInstall(installaddr[2], (DWORD)placeChatFontInfo, 27);
	HookInstall(installaddr[3], (DWORD)placeChatFontInfoShadow, 26);
	HookInstall(installaddr[4], (DWORD)place3DTextFontInfo, 27);
	HookInstall(installaddr[5], (DWORD)place3DTextShadowFontInfo, 27);
	HookInstall(installaddr[6], (DWORD)placeLicensePlateFontInfo, 28);
	HookInstall(installaddr[7], (DWORD)placeKillListFontInfo, 41);

	return;
}

void CalculateJumpBackAddresses() 
{
	g_dwJmpBack[0] = FindPattern("\x68\xBC\x02\x00\x00\x6A\x14\x68\x34\x40\x06\x04\x6A\x00\x8B\xCE", "xxxxxxxx????xxxx") + 0x10; 
	g_dwJmpBack[1] = FindPattern("\x68\xBC\x02\x00\x00\x6A\x12\x68\x34\x40\x06\x04\x6A\x01\x8B\xCE", "xxxxxxxx????xxxx") + 0x10;
	g_dwJmpBack[2] = FindPattern("\x50\x68\x34\x40\x06\x04\x6A\x00\x6A\x04\x6A\x00\x6A\x01\x6A\x00\x6A\x01\x68\xBC\x02\x00\x00\x6A\x00\x57\x51\xE8", "xx????xxxxxxxxxxxxxxxxxxxxxx") + 0x1B;
	g_dwJmpBack[3] = FindPattern("\x68\x34\x40\x06\x04\x6A\x00\x6A\x04\x6A\x00\x6A\x01\x6A\x00\x6A\x01\x68\xBC\x02\x00\x00\x6A\x00\x57\x50\xE8", "x????xxxxxxxxxxxxxxxxxxxxxx") + 0x1A;
	g_dwJmpBack[4] = FindPattern("\x51\x68\x34\x40\x06\x04\x6A\x00\x6A\x04\x6A\x00\x6A\x01\x6A\x00\x6A\x01\x68\xBC\x02\x00\x00\x6A\x00\x53\x52\xE8", "xx????xxxxxxxxxxxxxxxxxxxxxx") + 0x1B;
	g_dwJmpBack[5] = FindPattern("\x50\x68\x34\x40\x06\x04\x6A\x00\x6A\x04\x6A\x00\x6A\x01\x6A\x00\x6A\x01\x68\xBC\x02\x00\x00\x6A\x00\x53\x52\xE8", "xx????xxxxxxxxxxxxxxxxxxxxxx") + 0x1B;
	g_dwJmpBack[6] = FindPattern("\x55\x68\x34\x40\x06\x04\x6A\x00\x6A\x04\x6A\x00\x6A\x01\x6A\x00\x6A\x01\x68\xBC\x02\x00\x00\x6A\x0A\x6A\x26\x51\x89\x46\x1C\xE8", "xx????xxxxxxxxxxxxxxxxxxxxxxxxxx") + 0x1C;
	g_dwJmpBack[7] = FindPattern("\x68\x34\x40\x22\x04\x6A\x00\x6A\x00\x6A\x00\x33\xC0\x6A\x01", "x????xxxxxxxxxx") + 0x29;


}




