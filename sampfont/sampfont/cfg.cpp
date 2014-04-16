#include "CFG.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void LoadConfig(char* element, char* &font, unsigned int &pitch, unsigned int &quality, unsigned int &precision, unsigned int &charset, unsigned int &italic, unsigned int &miplevels, unsigned int &weight, unsigned int &width, unsigned int &height) {
	
	
	char currentDirectory[250];
	char fullPath[256];

	GetCurrentDirectory(250, currentDirectory);
	sprintf_s(fullPath, 256, "%s\\sampfont.cfg", currentDirectory);

	if(!fexists(fullPath)) CreateConfig();
	
	pitch		= GetPrivateProfileInt(element, "Pitch", 0, fullPath);
	quality		= GetPrivateProfileInt(element, "Quality", 4, fullPath);
	precision	= GetPrivateProfileInt(element, "Precision", 0, fullPath);
	charset		= GetPrivateProfileInt(element, "Charset", 1, fullPath);
	italic		= GetPrivateProfileInt(element, "Italic", 0, fullPath);
	miplevels	= GetPrivateProfileInt(element, "MipLevels", 1, fullPath);
	weight		= GetPrivateProfileInt(element, "Weight", 0x2BC, fullPath);
	width		= GetPrivateProfileInt(element, "Width", 10, fullPath);
	height		= GetPrivateProfileInt(element, "Height", 14, fullPath);

	GetPrivateProfileString(element, "Font", "Arial", currentDirectory, 128, fullPath); // NOTE TO FUTURE SELF: THIS LINE CAUSES A CRASH!!!

	font = currentDirectory;

	return;

}




void CreateConfig() {

	char currentDirectory[250];
	char fullPath[256];

	GetCurrentDirectory(250, currentDirectory);
	sprintf_s(fullPath, 256, "%s\\sampfont.cfg", currentDirectory);

	WritePrivateProfileString("Chat", "Font", "Arial", fullPath); 
	WritePrivateProfileString("Chat", "Pitch", "0", fullPath); 
	WritePrivateProfileString("Chat", "Quality", "4", fullPath); 
	WritePrivateProfileString("Chat", "Precision", "0", fullPath); 
	WritePrivateProfileString("Chat", "Charset", "1", fullPath); 
	WritePrivateProfileString("Chat", "Italic", "0", fullPath); 
	WritePrivateProfileString("Chat", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("Chat", "Weight", "700", fullPath); 
	WritePrivateProfileString("Chat", "Width", "0", fullPath); 
	//WritePrivateProfileString("Chat", "Height", "14", fullPath);

	WritePrivateProfileString("ChatShadow", "Font", "Arial", fullPath); 
	WritePrivateProfileString("ChatShadow", "Pitch", "0", fullPath); 
	WritePrivateProfileString("ChatShadow", "Quality", "4", fullPath); 
	WritePrivateProfileString("ChatShadow", "Precision", "0", fullPath); 
	WritePrivateProfileString("ChatShadow", "Charset", "1", fullPath); 
	WritePrivateProfileString("ChatShadow", "Italic", "0", fullPath); 
	WritePrivateProfileString("ChatShadow", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("ChatShadow", "Weight", "700", fullPath); 
	WritePrivateProfileString("ChatShadow", "Width", "0", fullPath); 
	//WritePrivateProfileString("ChatShadow", "Height", "14", fullPath);

	WritePrivateProfileString("3DText", "Font", "Arial", fullPath); 
	WritePrivateProfileString("3DText", "Pitch", "0", fullPath); 
	WritePrivateProfileString("3DText", "Quality", "4", fullPath); 
	WritePrivateProfileString("3DText", "Precision", "0", fullPath); 
	WritePrivateProfileString("3DText", "Charset", "1", fullPath); 
	WritePrivateProfileString("3DText", "Italic", "0", fullPath); 
	WritePrivateProfileString("3DText", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("3DText", "Weight", "700", fullPath); 
	WritePrivateProfileString("3DText", "Width", "0", fullPath); 
	//WritePrivateProfileString("3DText", "Height", "14", fullPath);

	WritePrivateProfileString("3DTextShadow", "Font", "Arial", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Pitch", "0", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Quality", "4", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Precision", "0", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Charset", "1", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Italic", "0", fullPath); 
	WritePrivateProfileString("3DTextShadow", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Weight", "700", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Width", "0", fullPath); 
	//WritePrivateProfileString("3DTextShadow", "Height", "12", fullPath);

	WritePrivateProfileString("DialogAndChat", "Font", "Arial", fullPath); 
	WritePrivateProfileString("DialogAndChat", "Weight", "700", fullPath); 
	WritePrivateProfileString("DialogAndChat", "Height", "20", fullPath); 
	WritePrivateProfileString("DialogAndChat", "Width", "0", fullPath);

	WritePrivateProfileString("DialogBody", "Font", "Arial", fullPath); 
	WritePrivateProfileString("DialogBody", "Weight", "700", fullPath); 
	WritePrivateProfileString("DialogBody", "Height", "18", fullPath); 
	WritePrivateProfileString("DialogBody", "Width", "1", fullPath);

	WritePrivateProfileString("Unknown", "Font", "Arial", fullPath); 
	WritePrivateProfileString("Unknown", "Pitch", "0", fullPath); 
	WritePrivateProfileString("Unknown", "Quality", "4", fullPath); 
	WritePrivateProfileString("Unknown", "Precision", "0", fullPath); 
	WritePrivateProfileString("Unknown", "Charset", "1", fullPath); 
	WritePrivateProfileString("Unknown", "Italic", "0", fullPath); 
	WritePrivateProfileString("Unknown", "MipLevels", "26", fullPath); 
	WritePrivateProfileString("Unknown", "Weight", "700", fullPath); 
	WritePrivateProfileString("Unknown", "Width", "38", fullPath); 
	WritePrivateProfileString("Unknown", "Height", "12", fullPath);

	WriteResolutionDefaultValues();
}

void WriteResolutionDefaultValues() {
	int x = *(int*)0x0C17044;

	int ebx = 0;
	int edi = 0;

	if(x > 1024) {
		if(x > 1400) {
			if(x > 1600) {
				ebx = 0x12;
				edi = 0x14;
			} else {
				ebx = 0x10;
				edi = 0x12;
			}
		} else {
			ebx = 0xE;
			edi = 0x10;
		}
	} else {
		ebx = 0xC;
		edi = 0xE;
	}
	char ebx_str[20];
	char edi_str[20];

	sprintf_s(ebx_str, sizeof(ebx_str), "%d", ebx);
	sprintf_s(edi_str, sizeof(edi_str), "%d", edi);

	char currentDirectory[250];
	char fullPath[256];

	GetCurrentDirectory(250, currentDirectory);
	sprintf_s(fullPath, 256, "%s\\sampfont.cfg", currentDirectory);

	WritePrivateProfileString("Chat", "Height", edi_str, fullPath);
	WritePrivateProfileString("ChatShadow", "Height", edi_str, fullPath);
	WritePrivateProfileString("3DText", "Height", ebx_str, fullPath);
	WritePrivateProfileString("3DTextShadow", "Height", ebx_str, fullPath);
}

bool fexists(const char* filename) {
  ifstream ifile(filename);
  if(ifile) return true;
  else return false;
}