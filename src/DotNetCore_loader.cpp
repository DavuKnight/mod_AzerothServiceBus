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

#define STR(s) L ## s
#define CH(c) L ## c
#define DIR_SEPARATOR L'\\'
using string_t = std::basic_string<char_t>;


namespace
{
    // Globals to hold hostfxr exports
    hostfxr_initialize_for_runtime_config_fn init_fptr;
    hostfxr_get_runtime_delegate_fn get_delegate_fptr;
    hostfxr_close_fn close_fptr;

    // Forward declarations
    bool load_hostfxr();
    load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* assembly);
}

// From SC
void AddDotNetCoreWorldScripts(load_assembly_and_get_function_pointer_fn fn);
load_assembly_and_get_function_pointer_fn initializeDotNetCore();

// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void AddDotNetCoreScripts()
{
    load_assembly_and_get_function_pointer_fn fn = initializeDotNetCore();
    AddDotNetCoreWorldScripts(fn);
}

load_assembly_and_get_function_pointer_fn initializeDotNetCore()
{
    // Get the current executable's directory
    // This sample assumes the managed assembly to load and its runtime configuration file are next to the host
    char_t host_path[MAX_PATH];
    std::string dllPath = sConfigMgr->GetOption<std::string>("DotNetCore.DllPath", "");
    string_t dllPath_t(dllPath.length(), L' ');
    std::copy(dllPath.begin(), dllPath.end(), dllPath_t.begin());

    auto pos = dllPath_t.find_last_of(DIR_SEPARATOR);
    string_t root_path = dllPath_t.substr(0, pos + 1);

    //
    // STEP 1: Load HostFxr and get exported hosting functions
    //
    load_hostfxr();

    //
    // STEP 2: Initialize and start the .NET Core runtime
    //
    const std::basic_string<char_t> config_path = root_path + STR("DotNetLib.runtimeconfig.json");
    load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer = nullptr;
    load_assembly_and_get_function_pointer = get_dotnet_load_assembly(config_path.c_str());
    assert(load_assembly_and_get_function_pointer != nullptr && "Failure: get_dotnet_load_assembly()");
    return load_assembly_and_get_function_pointer;
//    //
//    // STEP 3: Load managed assembly and get function pointer to a managed method
//    //
//
//    const char_t* dotnet_type = STR("DotNetLib.Lib, DotNetLib");
//    const char_t* dotnet_type_method = STR("Hello");
//    // <SnippetLoadAndGet>
//    // Function pointer to managed delegate
//    component_entry_point_fn hello = nullptr;
//    int rc = load_assembly_and_get_function_pointer(
//        dllPath_t.c_str(),
//        dotnet_type,
//        dotnet_type_method,
//        nullptr /*delegate_type_name*/,
//        nullptr,
//        (void**)&hello);
//    // </SnippetLoadAndGet>
//    assert(rc == 0 && hello != nullptr && "Failure: load_assembly_and_get_function_pointer()");
//
//    //
//// STEP 4: Run managed code
////
//    struct lib_args
//    {
//        const char_t* message;
//        int number;
//    };
//    for (int i = 0; i < 3; ++i)
//    {
//        // <SnippetCallManaged>
//        lib_args args
//        {
//            STR("from host!"),
//            i
//        };
//
//        hello(&args, sizeof(args));
//        // </SnippetCallManaged>
//    }
}


/********************************************************************************************
 * Functions used to load and activate .NET Core
 ********************************************************************************************/

namespace
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
    // Using the nethost library, discover the location of hostfxr and get exports
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
            std::cerr << "Init failed: " << std::hex << std::showbase << loadDotNetCoreResult << std::endl;
            close_fptr(cxt);
            return nullptr;
        }

        // Get the load assembly function pointer
        int rc = get_delegate_fptr(
            cxt,
            hdt_load_assembly_and_get_function_pointer,
            &load_assembly_and_get_function_pointer);
        if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
            std::cerr << "Get delegate failed: " << std::hex << std::showbase << rc << std::endl;

        close_fptr(cxt);
        return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
    }
    // </SnippetInitialize>
}
