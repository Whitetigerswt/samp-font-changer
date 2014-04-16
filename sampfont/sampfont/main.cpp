#include "main.h"
#include "CodeCave.h"
#include "cfg.h"
#include <iostream>

using namespace std;

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
		break;
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
		push [width]
		mov ecx,esi

		jmp dwJmpBack
	}
}

__declspec(naked) void placeDialogFontInfo() {

	_asm pushad

	LoadConfig("DialogBody", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
	dwJmpBack = g_dwJmpBack[1];

	_asm popad

	_asm { 
		push [weight]
		push [height]
		push [Font]
		push [width]
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

	LoadConfig("3DText", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
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

	LoadConfig("3DTextShadow", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
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


__declspec(naked) void placeUnknownFontInfo() {

	_asm pushad

	LoadConfig("Unknown", Font, pitch, quality, precision, charset, italic, miplevels, weight, width, height);
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
	g_dwSampBaseAddr = (DWORD)GetModuleHandle("samp.dll");
	
	
	DWORD installaddr[8];
	DWORD oldProt = 0;

	CalculateJumpBackAddresses();

	installaddr[0] = g_dwSampBaseAddr + 0x9EA15; // Chat input + Dialog buttons
	installaddr[1] = g_dwSampBaseAddr + 0x9EA2A; // Dialog list items and captions, NOT MAIN BODY!!
	installaddr[2] = g_dwSampBaseAddr + 0x7D35C; // Chat main font
	installaddr[3] = g_dwSampBaseAddr + 0x7D3A4; // Chat shadow font
	installaddr[4] = g_dwSampBaseAddr + 0x7D3CA; // Dialog body and 3D text label font
	installaddr[5] = g_dwSampBaseAddr + 0x7D412; // 3D Text label shadow font
	installaddr[6] = g_dwSampBaseAddr + 0x7D451; // ???

	VirtualProtect((LPVOID)installaddr[0], 16, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[1], 16, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[2], 27, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[3], 26, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[4], 27, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[5], 27, PAGE_EXECUTE_READWRITE, &oldProt);
	VirtualProtect((LPVOID)installaddr[6], 28, PAGE_EXECUTE_READWRITE, &oldProt);

	HookInstall(installaddr[0], (DWORD)placeDialogButtonFontInfo, 16);
	HookInstall(installaddr[1], (DWORD)placeDialogFontInfo, 16);
	HookInstall(installaddr[2], (DWORD)placeChatFontInfo, 27);
	HookInstall(installaddr[3], (DWORD)placeChatFontInfoShadow, 26);
	HookInstall(installaddr[4], (DWORD)place3DTextFontInfo, 27);
	HookInstall(installaddr[5], (DWORD)place3DTextShadowFontInfo, 27);
	HookInstall(installaddr[6], (DWORD)placeUnknownFontInfo, 28);



}

void CalculateJumpBackAddresses() {
	// FORMAT: g_dwJmpBack = base addr + install addr + install address size

	g_dwJmpBack[0] = g_dwSampBaseAddr + 0x9EA15 + 0x10;
	g_dwJmpBack[1] = g_dwSampBaseAddr + 0x9EA2A + 0x10;
	g_dwJmpBack[2] = g_dwSampBaseAddr + 0x7D35C + 0x1B;
	g_dwJmpBack[3] = g_dwSampBaseAddr + 0x7D3A4 + 0x1A;
	g_dwJmpBack[4] = g_dwSampBaseAddr + 0x7D3CA + 0x1B;
	g_dwJmpBack[5] = g_dwSampBaseAddr + 0x7D412 + 0x1B;
	g_dwJmpBack[6] = g_dwSampBaseAddr + 0x7D451 + 0x1C;


}




