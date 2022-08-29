// Includes list
//#include "SDK.h"
//#include "SDK.cpp"

#include <SDK.h>
void AddDotNetCoreScripts();

void Addmod_AzerothServiceBusScripts(){
    AddDotNetCoreScripts();

    //Got to be an easier way
    //wchar_t category[15] = L"server.loading";
    //wchar_t message[31] = L"Azeroth EnevntHub initializing";

    LogInformation("server.loading", "Azeroth EnevntHub initializing");
}
