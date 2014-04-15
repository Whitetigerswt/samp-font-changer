#include "main.h"
#include "CodeCave.h"

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

char* g_szNewFont = "David";
DWORD g_dwSampBaseAddr = NULL;


// arrays are to annoying to deal with in _asm, I still cringe at this.

DWORD g_dwJmpBack;
DWORD g_dwJmpBack2;
DWORD g_dwJmpBack3;
DWORD g_dwJmpBack4;
DWORD g_dwJmpBack5;
DWORD g_dwJmpBack6;
DWORD g_dwJmpBack7;


__declspec(naked) void placeDialogButtonFontInfo() { // THIS ALSO CHANGES TEXT FONT WHEN YOU PRESS T BUT DONT SEND A MESSAGE

	_asm { 
		push 02BCh
		push 14h
		push [g_szNewFont]
		push 0h
		mov ecx,esi

		jmp g_dwJmpBack
	}
}

__declspec(naked) void placeDialogFontInfo() {

	_asm { 
		push 02BCh
		push 12h
		push [g_szNewFont]
		push 1h
		mov ecx,esi

		jmp g_dwJmpBack2
	}
}

__declspec(naked) void placeChatFontInfo() {

	_asm { 
		push EAX
		push [g_szNewFont]
		push 0h
		push 4h
		push 0h
		push 1h
		push 0h
		push 1h
		push 2BCh
		push 0h
		push EDI
		push ECX

		jmp g_dwJmpBack3
	}
}

__declspec(naked) void placeChatFontInfoShadow() {

	_asm { 
		push [g_szNewFont]
		push 0h
		push 4h
		push 0h
		push 1h
		push 0h
		push 1h
		push 2BCh
		push 0h
		push EDI
		push EAX

		jmp g_dwJmpBack4
	}
}

__declspec(naked) void place3DTextFontInfo() {

	_asm { 
		push ecx
		push [g_szNewFont]
		push 0h
		push 4h
		push 0h
		push 1h
		push 0h
		push 1h
		push 2BCh
		push 0h
		push EBX
		push EDX

		jmp g_dwJmpBack5
	}
}


__declspec(naked) void place3DTextShadowFontInfo() {

	_asm { 
		push eax
		push [g_szNewFont]
		push 0h
		push 4h
		push 0h
		push 1h
		push 0h
		push 1h
		push 2BCh
		push 0h
		push ebx
		push edx

		jmp g_dwJmpBack6
	}
}


__declspec(naked) void placeUnknownFontInfo() {

	_asm { 
		push ebp
		push [g_szNewFont]
		push 0h
		push 4h
		push 0h
		push 1h
		push 0h
		push 1h
		push 2BCh
		push 0Ah
		push 26h
		push ecx

		jmp g_dwJmpBack7
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

	g_dwJmpBack  = g_dwSampBaseAddr + 0x9EA15 + 0x10;
	g_dwJmpBack2 = g_dwSampBaseAddr + 0x9EA2A + 0x10;
	g_dwJmpBack3 = g_dwSampBaseAddr + 0x7D35C + 0x1B;
	g_dwJmpBack4 = g_dwSampBaseAddr + 0x7D3A4 + 0x1A;
	g_dwJmpBack5 = g_dwSampBaseAddr + 0x7D3CA + 0x1B;
	g_dwJmpBack6 = g_dwSampBaseAddr + 0x7D412 + 0x1B;
	g_dwJmpBack7 = g_dwSampBaseAddr + 0x7D451 + 0x1C;


}




