#include "InitResources.h"

InitResources::InitResources(bool console) :hWnd()
{
	this->console = console;

	// ERROR Message:  "Couldn't load (wstring)"
	InitTextures();
	InitSounds();
	InitFonts();
}


void InitResources::InitTextures()
{
	if (!player.loadFromFile(defenti + "player_actions.png")) ThrowExeption(L"player textures");
	if (!tiles.loadFromFile(defmap + "ground_tilex7.png")) ThrowExeption(L"player map tiles");
	if (!icon.loadFromFile("../res/icon.png")) ThrowExeption(L"game icon lmao");
}

void InitResources::InitSounds()
{

}

void InitResources::InitFonts()
{

}

void InitResources::ThrowExeption(wstring failed_resource)
{
	if (!console)
	{
		wchar_t buff[100];

		wstring error_message = L"Couldn't load ";
		error_message += failed_resource;
		swprintf_s(buff, 100, L"%s", error_message.c_str());

		MessageBox
		(
			hWnd,
			buff,
			L"ERROR",
			MB_OK | MB_ICONERROR
		);
	}

	exit(EXIT_FAILURE);
}

