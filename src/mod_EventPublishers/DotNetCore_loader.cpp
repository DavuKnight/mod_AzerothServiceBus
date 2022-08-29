/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
 // Standard headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

//Azeroth Headers
#include "Config.h"

//Microsoft >NetCore Headers
#include "nethost.h"
#include "coreclr_delegates.h"
#include "hostfxr.h"

#include <Windows.h>

//Encourage Linker To include DeclSpecs declared in the Facade
#include "../mod_SDK/SDK.h"
#include <Log.h>

#define STR(s) L ## s
#define CH(c) L ## c
#define DIR_SEPARATOR L'\\'
using string_t = std::basic_string<char_t>;


namespace DotNetCore
{
    // Globals to hold hostfxr exports
    hostfxr_initialize_for_runtime_config_fn init_fptr;
    hostfxr_get_runtime_delegate_fn get_delegate_fptr;
    hostfxr_close_fn close_fptr;

    // Forward declarations
    bool load_hostfxr();
    load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* assembly);
}
namespace DotNetCore
{
    // From SC
    void AddDotNetCoreWorldScripts(load_assembly_and_get_function_pointer_fn fn);
    void AddDotNetCorePlayerScripts(load_assembly_and_get_function_pointer_fn fn);

    load_assembly_and_get_function_pointer_fn initializeDotNetCore()
    {
        // Get the current executable's directory
        // This sample assumes the managed assembly to load and its runtime configuration file are next to the host
        char_t host_path[MAX_PATH];
        std::string dllPath = sConfigMgr->GetOption<std::string>("DotNetCore.DllPath", "");
        string_t dllPath_t(dllPath.length(), L' ');
        std::copy(dllPath.begin(), dllPath.end(), dllPath_t.begin());

        std::string dllruntimeconfig = sConfigMgr->GetOption<std::string>("DotNetCore.runtimeconfig", "");
        string_t dllruntimeconfig_t(dllruntimeconfig.length(), L' ');
        std::copy(dllruntimeconfig.begin(), dllruntimeconfig.end(), dllruntimeconfig_t.begin());


        //
        // STEP 1: Load HostFxr and get exported hosting functions
        //
        load_hostfxr();

        //
        // STEP 2: Initialize and start the .NET Core runtime
        //
        const std::basic_string<char_t> config_path = dllruntimeconfig_t;
        load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer = nullptr;
        load_assembly_and_get_function_pointer = get_dotnet_load_assembly(config_path.c_str());
        return load_assembly_and_get_function_pointer;

    }


    load_assembly_and_get_function_pointer_fn initializeDotNetCore();
}
// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void AddDotNetCoreScripts()
{
    load_assembly_and_get_function_pointer_fn fn = DotNetCore::initializeDotNetCore();
    if (fn != nullptr)
    {
        DotNetCore::AddDotNetCoreWorldScripts(fn);
        //DotNetCore::AddDotNetCorePlayerScripts(fn);
    }
}

/********************************************************************************************
 * Functions used to load and activate .NET Core
 ********************************************************************************************/

namespace DotNetCore
{
    // Forward declarations
    void* load_library(const char_t*);
    void* get_export(void*, const char*);

    void* load_library(const char_t* path)
    {
        HMODULE h = ::LoadLibraryW(path);
        assert(h != nullptr);
        return (void*)h;
    }
    void* get_export(void* h, const char* name)
    {
        void* f = ::GetProcAddress((HMODULE)h, name);
        assert(f != nullptr);
        return f;
    }

    // <SnippetLoadHostFxr>
    // Using the nethost library, discover the location of hostfxr and get the methods that are exported
    bool load_hostfxr()
    {
        // Pre-allocate a large buffer for the path to hostfxr
        char_t buffer[MAX_PATH];
        size_t buffer_size = sizeof(buffer) / sizeof(char_t);
        int rc = get_hostfxr_path(buffer, &buffer_size, nullptr);
        if (rc != 0)
            return false;

        // Load hostfxr and get desired exports
        void* lib = load_library(buffer);
        init_fptr = (hostfxr_initialize_for_runtime_config_fn)get_export(lib, "hostfxr_initialize_for_runtime_config");
        get_delegate_fptr = (hostfxr_get_runtime_delegate_fn)get_export(lib, "hostfxr_get_runtime_delegate");
        close_fptr = (hostfxr_close_fn)get_export(lib, "hostfxr_close");

        return (init_fptr && get_delegate_fptr && close_fptr);
    }
    // </SnippetLoadHostFxr>

    // <SnippetInitialize>
    // Load and initialize .NET Core and get desired function pointer for scenario
    load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path)
    {

        // Load .NET Core
        void* load_assembly_and_get_function_pointer = nullptr;
        hostfxr_handle cxt = nullptr;
        int loadDotNetCoreResult = init_fptr(config_path, nullptr, &cxt);
        if (loadDotNetCoreResult != 0 || cxt == nullptr)
        {
            LOG_WARN("mod_DotNetCore.loading", "mod_DotNetCore Init failed: DotNetCore Config File failed to load" );
            close_fptr(cxt);
            return nullptr;
        }

        // Get the load assembly function pointer
        int rc = get_delegate_fptr(
            cxt,
            hdt_load_assembly_and_get_function_pointer,
            &load_assembly_and_get_function_pointer);
        if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
            LOG_WARN("mod_DotNetCore.loading","Get delegate failed: Could not find the desired function pointer");

        //close_fptr(cxt);
        return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
    }
    // </SnippetInitialize>
}

