/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include <iostream>
#include "SDK.h"

extern "C" __declspec(dllexport) char* SDKEntryPoint(wchar_t*  path, wchar_t* action, wchar_t* jsonBody)
{
	if (path == L"Chat")
	{
	}
	else
	{
		std::wcout << path;
		std::wcout << action;
		std::wcout << jsonBody;
	}
	return NULL;
}
