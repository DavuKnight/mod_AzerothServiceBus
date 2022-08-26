/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
//#include "Chat.h"
#include "coreclr_delegates.h"
#include <string>

#define ST(s) L ## s
#define CH(c) L ## c
#define DIR_SEPARATOR L'\\'
using string_t = std::basic_string<char_t>;
// Add player scripts


namespace DotNetCore {
    class DotNetCorePlayerScript : public PlayerScript
    {
    public:
        DotNetCorePlayerScript(
            load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer) : PlayerScript("DotNetCoreWorldScript")
        {
            std::string dllPath = sConfigMgr->GetOption<std::string>("DotNetCore.DllPath", "");
            string_t dllPath_t(dllPath.length(), L' ');
            std::copy(dllPath.begin(), dllPath.end(), dllPath_t.begin());

            const char_t* dotnet_type = ST("DotNetLib.PlayerScript, DotNetLib");

            int OnLoginRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnLogin"), nullptr /*delegate_type_name*/, nullptr, (void**)&onLogin);

        }


        component_entry_point_fn onLogin = nullptr;
        // Called when a player logs in.
        void OnLogin(Player* player) override {

            struct playerArgs args(player);

            onLogin(&args, sizeof(args));
        }

        struct playerArgs
        {
            uint64 PlayerGuid;
            const char* Name;
            uint32 AccountId;

            playerArgs(Player* player)
            {
                Name = player->GetName().c_str();
                PlayerGuid = player->GetGUID().GetRawValue();
                AccountId = player->GetSession()->GetAccountId();
            }
        };
    };





    void AddDotNetCorePlayerScripts(load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer)
    {
        new DotNetCorePlayerScript(load_assembly_and_get_function_pointer);
    }
}