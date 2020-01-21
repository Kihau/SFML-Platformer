#pragma once

#include "all_headers.h"

class InitResources
{
private:
	HWND hWnd;

	// Textures default paths
	const string
		defenti = "../res/",
		defmap = "../res/",
		defback = "../res/";

	bool console{};

public:
	Texture player;
	Texture tiles;
	//Sound testbuff;
	//Font testfont;

public:
	InitResources(bool console);

private:
	void InitTextures();
	void InitSounds();
	void InitFonts();

	void ThrowExeption(wstring failed_resource);
};

