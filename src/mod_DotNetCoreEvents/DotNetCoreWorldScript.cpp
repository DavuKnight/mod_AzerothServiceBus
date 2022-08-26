/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "coreclr_delegates.h"

#define ST(s) L ## s
#define CH(c) L ## c
#define DIR_SEPARATOR L'\\'
using string_t = std::basic_string<char_t>;
// Add player scripts
namespace DotNetCore {
    class DotNetCoreWorldScript : public WorldScript
    {

    public:
        DotNetCoreWorldScript(
            load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer) : WorldScript("DotNetCoreWorldScript")
        {
            std::string dllPath = sConfigMgr->GetOption<std::string>("DotNetCore.DllPath", "");
            string_t dllPath_t(dllPath.length(), L' ');
            std::copy(dllPath.begin(), dllPath.end(), dllPath_t.begin());

            const char_t* dotnet_type = ST("DotNetLib.WorldScript, DotNetLib");

            int OnOpenStateChangeRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnOpenStateChange"), nullptr /*delegate_type_name*/, nullptr, (void**)&onOpenStateChange);
            int OnAfterConfigLoadRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnAfterConfigLoad"), nullptr /*delegate_type_name*/, nullptr, (void**)&onAfterConfigLoad);
            int OnLoadCustomDatabaseTableRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnLoadCustomDatabaseTable"), nullptr /*delegate_type_name*/, nullptr, (void**)&onLoadCustomDatabaseTable);
            int OnBeforeConfigLoadRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnBeforeConfigLoad"), nullptr /*delegate_type_name*/, nullptr, (void**)&onBeforeConfigLoad);
            int OnMotdChangeRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnMotdChange"), nullptr /*delegate_type_name*/, nullptr, (void**)&onMotdChange);
            int OnShutdownInitiateRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnShutdownInitiate"), nullptr /*delegate_type_name*/, nullptr, (void**)&onShutdownInitiate);
            int OnShutdownCancelRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnShutdownCancel"), nullptr /*delegate_type_name*/, nullptr, (void**)&onShutdownCancel);
            int OnUpdateRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnUpdate"), nullptr /*delegate_type_name*/, nullptr, (void**)&onUpdate);
            int OnStartupRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnStartup"), nullptr /*delegate_type_name*/, nullptr, (void**)&onStartup);
            int OnShutdownRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnShutdown"), nullptr /*delegate_type_name*/, nullptr, (void**)&onShutdown);
            int OnAfterUnloadAllMapsRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnAfterUnloadAllMaps"), nullptr /*delegate_type_name*/, nullptr, (void**)&onAfterUnloadAllMaps);
            int OnBeforeFinalizePlayerWorldSessionRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnBeforeFinalizePlayerWorldSession"), nullptr /*delegate_type_name*/, nullptr, (void**)&onBeforeFinalizePlayerWorldSession);
            int OnBeforeWorldInitializedRC = load_assembly_and_get_function_pointer(dllPath_t.c_str(), dotnet_type, ST("OnBeforeWorldInitialized"), nullptr /*delegate_type_name*/, nullptr, (void**)&onBeforeWorldInitialized);
        }

        component_entry_point_fn onOpenStateChange = nullptr;
        // Called when the open/closed state of the world changes.
        virtual void OnOpenStateChange(bool open) override {
            struct lib_args
            {
                const bool open;
            };
            lib_args args
            {
                open
            };
            onOpenStateChange(&args, sizeof(args));
        }

        component_entry_point_fn onAfterConfigLoad = nullptr;
        // Called after the world configuration is (re)loaded.
        virtual void OnAfterConfigLoad(bool reload) override {
            struct lib_args
            {
                const bool reload;
            };
            lib_args args
            {
                reload
            };
            onAfterConfigLoad(&args, sizeof(args));
        }

        component_entry_point_fn onLoadCustomDatabaseTable = nullptr;
        // Called when loading custom database tables
        virtual void OnLoadCustomDatabaseTable() override {
            onLoadCustomDatabaseTable(nullptr, 0);
        }

        component_entry_point_fn onBeforeConfigLoad = nullptr;
        // Called before the world configuration is (re)loaded.
        virtual void OnBeforeConfigLoad(bool reload) override {
            struct lib_args
            {
                const bool reload;
            };
            lib_args args
            {
                reload
            };
            onBeforeConfigLoad(&args, sizeof(args));
        }

        component_entry_point_fn onMotdChange = nullptr;
        // Called before the message of the day is changed.
        virtual void OnMotdChange(std::string& newMotd) override {
            struct lib_args
            {
                std::string& newMotd;
            };
            lib_args args
            {
                newMotd
            };
            onMotdChange(&args, sizeof(args));
        }

        component_entry_point_fn onShutdownInitiate = nullptr;
        // Called when a world shutdown is initiated.
        virtual void OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask) override {
            struct lib_args
            {
                ShutdownExitCode code;
                ShutdownMask mask;
            };
            lib_args args
            {
                code,
                mask
            };
            onShutdownInitiate(&args, sizeof(args));
        }

        component_entry_point_fn onShutdownCancel = nullptr;
        // Called when a world shutdown is cancelled.
        virtual void OnShutdownCancel() override {
            onShutdownCancel(nullptr, 0);
        }

        component_entry_point_fn onUpdate = nullptr;
        // Called on every world tick (don't execute too heavy code here).
        virtual void OnUpdate(uint32 i) override {
            struct lib_args
            {
                const uint32 i;
            };
            lib_args args
            {
                i
            };
            onUpdate(&args, sizeof(args));
        }

        component_entry_point_fn onStartup = nullptr;
        // Called when the world is started.
        virtual void OnStartup() override {
            onStartup(nullptr, 0);
        }

        component_entry_point_fn onShutdown = nullptr;
        // Called when the world is actually shut down.
        virtual void OnShutdown() override {
            onShutdown(nullptr, 0);
        }

        component_entry_point_fn onAfterUnloadAllMaps = nullptr;
        /**
         * @brief Called after all maps are unloaded from core
         */
        virtual void OnAfterUnloadAllMaps() override {
            onAfterUnloadAllMaps(nullptr, 0);
        }

        component_entry_point_fn onBeforeFinalizePlayerWorldSession = nullptr;
        /**
         * @brief This hook runs before finalizing the player world session. Can be also used to mutate the cache version of the Client.
         *
         * @param version The cache version that we will be sending to the Client.
         */
        virtual void OnBeforeFinalizePlayerWorldSession(uint32& cacheVersion) override {
            struct lib_args
            {
                const uint32& cacheVersion;
            };
            lib_args args
            {
                cacheVersion
            };
            onBeforeFinalizePlayerWorldSession(&args, sizeof(args));
        }

        component_entry_point_fn onBeforeWorldInitialized = nullptr;
        /**
         * @brief This hook runs after all scripts loading and before itialized
         */
        virtual void OnBeforeWorldInitialized() override {
            onBeforeWorldInitialized(nullptr, 0);
        }



    };

    // Add all scripts in one
    void AddDotNetCoreWorldScripts(load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer)
    {
        new DotNetCoreWorldScript(load_assembly_and_get_function_pointer);
    }

}
