
#pragma once

#pragma warning (disable : 4005)
#pragma warning (disable : 4251)


#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>

#include <process.h>

#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"
#include "Engine_Functor.h"
#include "Engine_Function.h"
#include <io.h>
#include <Vfw.h>

#pragma comment(lib, "vfw32.lib")

#ifdef ENGINE_EXPORTS
#pragma comment(lib, "../Bin/fmod_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

#pragma comment(lib, "msimg32.lib")

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG

using namespace std;
using namespace Engine;


