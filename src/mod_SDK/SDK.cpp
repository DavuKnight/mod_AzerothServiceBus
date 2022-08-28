/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include <iostream>
#include "SDK.h"
#include <Log.h>

extern "C" __declspec(dllexport) int LogInformation(const char* catagory_t, const char* message_t)
{
    LOG_INFO(catagory_t, message_t);
    return 1;
}
