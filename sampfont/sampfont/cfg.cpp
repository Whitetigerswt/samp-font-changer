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
	
	pitch		= GetPrivateProfileInt(element, "Pitch", 0, fullPath);
	quality		= GetPrivateProfileInt(element, "Quality", 0, fullPath);
	precision	= GetPrivateProfileInt(element, "Precision", 0, fullPath);
	charset		= GetPrivateProfileInt(element, "Charset", 0, fullPath);
	italic		= GetPrivateProfileInt(element, "Italic", 0, fullPath);
	miplevels	= GetPrivateProfileInt(element, "MipLevels", 0, fullPath);
	weight		= GetPrivateProfileInt(element, "Weight", 0, fullPath);
	width		= GetPrivateProfileInt(element, "Width", 0, fullPath);
	height		= GetPrivateProfileInt(element, "Height", 0, fullPath);

	GetPrivateProfileString(element, "Font", "Arial", font, 128, fullPath); // NOTE TO FUTURE SELF: THIS LINE CAUSES A CRASH!!!

	
	/*ofstream ofile("test.txt");

	ofile << "before anything " << element << endl;
	TiXmlDocument doc; 
	if(!doc.LoadFile("sampfont.xml", TIXML_ENCODING_UTF8)) {
		ofile << doc.ErrorDesc() << endl;
		CreateConfig();
	}

	ofile << "before " << fatherelement << endl;
	TiXmlElement* sampfont = doc.FirstChildElement("sampfont");
	ofile << "between " << fatherelement << endl;
	TiXmlElement* textApproachElement = sampfont->FirstChildElement( fatherelement );

	ofile << fatherelement << " " << element << endl;

	ofile << textApproachElement->Attribute("font") << endl;
	font = new char[128];
	memcpy((void*)font, (void*)sampfont->Attribute("font"), 128);

	ofile << "after memcpy2" << endl;

	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("pitch", &pitch);

	ofile << "after pitch " << endl;
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("quality", &quality);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("precision", &precision);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("charset", &charset);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("italic", &italic);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("miplevels", &miplevels);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("weight", &weight);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("width", &width);
	textApproachElement->FirstChildElement( element )->QueryUnsignedAttribute("height", &height);

	ofile << "func done" << endl;*/

	return;

}




void CreateConfig() {
	/*TiXmlDocument doc;  
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "");  
	doc.LinkEndChild( decl );  
 
	TiXmlElement * root = new TiXmlElement( "sampfont" );  
	doc.LinkEndChild( root );  

	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue(" In all of the properties, the default value for HEIGHT DEPENDS ON YOUR RESOLUTION!!!! " );  
	root->LinkEndChild( comment ); 

	comment = new TiXmlComment();
	comment->SetValue(" These changes edits the chat font properties " );  
	root->LinkEndChild( comment );  
 
	TiXmlElement * ChatMain = new TiXmlElement( "Chat" );  
	root->LinkEndChild( ChatMain );  

	comment = new TiXmlComment();
	comment->SetValue(" chat and chatshadow should have almost identical settings for the best look!!! " );  
	ChatMain->LinkEndChild( comment ); 

	TiXmlElement * chat;
	chat = new TiXmlElement( "chat" );  
	ChatMain->LinkEndChild( chat );  
	chat->SetAttribute("font", "Arial");
	chat->SetAttribute("pitch", 0);
	chat->SetAttribute("quality", 4);
	chat->SetAttribute("precision", 0);
	chat->SetAttribute("charset", 1);
	chat->SetAttribute("italic", 0);
	chat->SetAttribute("miplevels", 1);
	chat->SetAttribute("weight", 0x2BC);
	chat->SetAttribute("miplevels", 0);
	chat->SetAttribute("width", 10);
	chat->SetAttribute("height", 10);

	TiXmlElement * chatshadow;
	chatshadow = new TiXmlElement( "chatshadow" );  
	ChatMain->LinkEndChild( chatshadow );  
	chatshadow->SetAttribute("font", "Arial");
	chatshadow->SetAttribute("pitch", 0);
	chatshadow->SetAttribute("quality", 4);
	chatshadow->SetAttribute("precision", 0);
	chatshadow->SetAttribute("charset", 1);
	chatshadow->SetAttribute("italic", 0);
	chatshadow->SetAttribute("miplevels", 1);
	chatshadow->SetAttribute("weight", 0x2BC);
	chatshadow->SetAttribute("miplevels", 0);
	chatshadow->SetAttribute("width", 10);
	chatshadow->SetAttribute("height", 10);

	comment = new TiXmlComment();
	comment->SetValue(" These changes edit the 3DTextLabel and Chat Bubble font properties " );  
	root->LinkEndChild( comment );  

	TiXmlElement * Text3D;
	Text3D = new TiXmlElement( "3DText" );  
	root->LinkEndChild( Text3D );  

	comment = new TiXmlComment();
	comment->SetValue(" 3DText and 3DTextshadow should have almost identical settings for the best look!!! " );  
	Text3D->LinkEndChild( comment ); 

	TiXmlElement * Text3DMain;
	Text3DMain = new TiXmlElement( "3DTextMain" ); 
	Text3D->LinkEndChild( Text3DMain );  
	Text3DMain->SetAttribute("font", "Arial");
	Text3DMain->SetAttribute("pitch", 0);
	Text3DMain->SetAttribute("quality", 4);
	Text3DMain->SetAttribute("precision", 0);
	Text3DMain->SetAttribute("charset", 1);
	Text3DMain->SetAttribute("italic", 0);
	Text3DMain->SetAttribute("miplevels", 1);
	Text3DMain->SetAttribute("weight", 0x2BC);
	Text3DMain->SetAttribute("miplevels", 0);
	Text3DMain->SetAttribute("width", 10);
	Text3DMain->SetAttribute("height", 10);

	TiXmlElement * Text3DShadow;
	Text3DShadow = new TiXmlElement( "3DTextShadow" ); 
	Text3D->LinkEndChild( Text3DShadow );  
	Text3DShadow->SetAttribute("font", "Arial");
	Text3DShadow->SetAttribute("pitch", 0);
	Text3DShadow->SetAttribute("quality", 4);
	Text3DShadow->SetAttribute("precision", 0);
	Text3DShadow->SetAttribute("charset", 1);
	Text3DShadow->SetAttribute("italic", 0);
	Text3DShadow->SetAttribute("miplevels", 1);
	Text3DShadow->SetAttribute("weight", 0x2BC);
	Text3DShadow->SetAttribute("miplevels", 0);
	Text3DShadow->SetAttribute("width", 10);
	Text3DShadow->SetAttribute("height", 10);

	comment = new TiXmlComment();
	comment->SetValue(" These changes edit the dialog font properties " );  
	root->LinkEndChild( comment ); 

	TiXmlElement* MainDialog;
	MainDialog = new TiXmlElement( "Dialog" );  
	root->LinkEndChild( MainDialog );  

	comment = new TiXmlComment();
	comment->SetValue(" This also edits the text when you press T and type in the chat, but haven't sent it yet " );  
	MainDialog->LinkEndChild( comment ); 

	TiXmlElement* buttons_chat;
	buttons_chat = new TiXmlElement("buttons_chat");
	MainDialog->LinkEndChild( buttons_chat ); 
	buttons_chat->SetAttribute("weight", 0x2BC);
	buttons_chat->SetAttribute("font", "Arial");
	buttons_chat->SetAttribute("unknown1", 0x14);
	buttons_chat->SetAttribute("unknown2", 0);

	
	TiXmlElement* body = new TiXmlElement("body");
	MainDialog->LinkEndChild( body ); 
	body->SetAttribute("weight", 0x2BC);
	body->SetAttribute("font", "Arial");
	body->SetAttribute("unknown1", 0x12);
	body->SetAttribute("unknown2", 1);

	comment = new TiXmlComment();
	comment->SetValue(" I have no idea what this changes, but it changes some font in SA-MP " );  
	root->LinkEndChild( comment ); 

	TiXmlElement * Unknown;
	Unknown = new TiXmlElement( "Unknown" );  
	root->LinkEndChild( Unknown );  

	TiXmlElement * unknown;
	unknown = new TiXmlElement( "Unknown" ); 
	Unknown->LinkEndChild(unknown);

	unknown->SetAttribute("font", "Arial");
	unknown->SetAttribute("pitch", 0);
	unknown->SetAttribute("quality", 4);
	unknown->SetAttribute("precision", 0);
	unknown->SetAttribute("charset", 1);
	unknown->SetAttribute("italic", 0);
	unknown->SetAttribute("miplevels", 1);
	unknown->SetAttribute("weight", 0x2BC);
	unknown->SetAttribute("miplevels", 0x0A);
	unknown->SetAttribute("width", 0x26);
	unknown->SetAttribute("height", 10);

	doc.SaveFile( "sampfont.xml" ); */

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
	WritePrivateProfileString("Chat", "Width", "10", fullPath); 
	WritePrivateProfileString("Chat", "Height", "10", fullPath);

	WritePrivateProfileString("ChatShadow", "Font", "Arial", fullPath); 
	WritePrivateProfileString("ChatShadow", "Pitch", "0", fullPath); 
	WritePrivateProfileString("ChatShadow", "Quality", "4", fullPath); 
	WritePrivateProfileString("ChatShadow", "Precision", "0", fullPath); 
	WritePrivateProfileString("ChatShadow", "Charset", "1", fullPath); 
	WritePrivateProfileString("ChatShadow", "Italic", "0", fullPath); 
	WritePrivateProfileString("ChatShadow", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("ChatShadow", "Weight", "700", fullPath); 
	WritePrivateProfileString("ChatShadow", "Width", "10", fullPath); 
	WritePrivateProfileString("ChatShadow", "Height", "10", fullPath);

	WritePrivateProfileString("3DText", "Font", "Arial", fullPath); 
	WritePrivateProfileString("3DText", "Pitch", "0", fullPath); 
	WritePrivateProfileString("3DText", "Quality", "4", fullPath); 
	WritePrivateProfileString("3DText", "Precision", "0", fullPath); 
	WritePrivateProfileString("3DText", "Charset", "1", fullPath); 
	WritePrivateProfileString("3DText", "Italic", "0", fullPath); 
	WritePrivateProfileString("3DText", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("3DText", "Weight", "700", fullPath); 
	WritePrivateProfileString("3DText", "Width", "10", fullPath); 
	WritePrivateProfileString("3DText", "Height", "10", fullPath);

	WritePrivateProfileString("3DTextShadow", "Font", "Arial", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Pitch", "0", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Quality", "4", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Precision", "0", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Charset", "1", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Italic", "0", fullPath); 
	WritePrivateProfileString("3DTextShadow", "MipLevels", "1", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Weight", "700", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Width", "10", fullPath); 
	WritePrivateProfileString("3DTextShadow", "Height", "10", fullPath);

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
	WritePrivateProfileString("Unknown", "Height", "10", fullPath);
}