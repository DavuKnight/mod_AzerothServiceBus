**** Complete rewrite needed *** about half of this is wrong.

This is not your typical Module this module is designed to allow devlopment in the DotNet Development language. This is acomplished using the mod in the src/mod_DotNetCoreEvents module which Launches a hosted copy of DotNetCore from withen the WorldServer and then calls into the DotNetCore layer contained in the deps/AzerothDotNetCore project. AzerothDotNetCore then looks at its Appsettings to find any registered consumers for that event and calls into the dll specified executing whatever code it finds contained therein. 
If the desired result from the event is a change in the worldserver the DotNetCode can call back to the WorldServer by referencing the sdk in deps/DotNetCoreAzeroth. DotNetCoreAzeroth then calls into the WorldServer.exe using the mehods exposed in the src mod_sdk module.

Getting Started
	Open your copy of the azerothCore_wotlk. If you do not yet have a copy it can be retrieved via. 
	Git bash using
	git clone https://github.com/azerothcore/azerothcore-wotlk.git
	However there are more steps to setting up Azerothcore then a simple clone so make sure your authserver and worldserver are working to you expectations before continueing.

	If your WorldServer and AuthServer are working navigate to the modules directory within the azerothcore-wotlk directory. Here create a Submodule of this repository. The command to do this in at gitbash is
	git submodule add https://github.com/DavidStrickland0/mod_DotNetCore.git
	
	Once this is accomplished run CMake and ensure the modules deploy You should see additional entries in your CMake Script stating that mod_SDK was installed, the mod_DotNetCoreEvents was installed and that nethost.lib has been successfully located and referenced.
	
	At this point the Mod is ready but doesnt actually do anything. That is because you need to provide the logic now for what you want to do.  

Solution Structure
	In the deps folder there are four projects. 
	deps-
		AzerothDotNetCore-
			This project contains the logic for event subscription and App settings. The WorldServer will look for this DLL by name in its current folder. After you compile a new version of the DLL it needs to be copied out to the servers root folder while the server is shutdown. The server maintanes a reference to this DLL at all times while its running updating outside of a maintainence window isnt currently possible.
			The AzerothDotNetCore project should only be updated when new Events are made available on the world server. In that case both the mod_DotNetCore and the AzerothDotNetCore source code will need to be updated to  accomplish it.
		DotNetCoreAzeroth-
			The mod_SDK exposes a number of methods using extern "C" __declspec(dllexport) as such these can be consumed by anyone from any number of languages however anyone trying to do so will experience why this wrapper class is necessary. DotNetCoreAzeroth is a simple Wrapper class wrapping the functionality exposed by mod_SDK. The structure of this facade should match to the extent possible the structure of the C++ functionality being called. If a method on the WorldScript is being exposed then it should be mapped in DotNetCoreAzeroth to a similarly named method on a simarly named object. This is likely to be messy and none intuitive but its is perferrable to allow for a common language between C++ and DotNet devs moving forward.
		AzerothDotNetCoreTests-
			Unit tests for AzerothDotNetCore
		DotNetCoreAzerothTests
			Automated Functional and UI Tests of DotNetCoreAzeroth and mod_SDK only works with a live test server to ensure the calls are executing as expected.
	src-
		mod_DotNetCoreEvents
			Included for reference and ease of access these are not compiled with the solution
		mod_WorldServerSDK
			Included for reference and ease of access these are not compiled with the solution

Creating your own Module
	Once this Module is installed. 
	Open the Devenvironment of your choice. 
	Create a new .NetCore 6+ DLL. 
	Reference the Two Nugets 
		If you want to subscribe to events from the world Server add AzerothDotNetCore.Events
		If you want to interact with your server AzerothDotNetCore.WorldServerSDK.
	Create a new Class that implements one of the Event interfaces available in AzerothDotNetCore.Events. Leave any events your not using empty. (IE: remove the NotImplementedExceptions if you have them) 
	to execute something on the worldserver call the desired method on the SDK. 
	Once Done Compile your Code. 
	Stop your world server. 
	Copy the DLL into the same folder as your worldserver.exe. 
	Update appsettings.json to include the dll in the module list.
	Start the server. 
	As the Server Comes up you should see a list of all DotNetCore Module DLL's the server has been able to find and instantiate.
	

				
