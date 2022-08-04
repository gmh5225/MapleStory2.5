#pragma once

namespace Client
{
#pragma warning (disable : 4244)
	static const unsigned int g_iWinSizeX = 1280;
	static const unsigned int g_iWinSizeY = 720;
	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_HENESYS, LEVEL_ELENYA, LEVEL_END };
}

extern HINSTANCE g_hInst;
extern HWND g_hWnd;
extern bool g_bStaticClone;
extern bool g_bStatic;
extern bool g_bGamePlay;
extern bool g_bHenesys;
extern bool g_bElenya;

using namespace Client;
