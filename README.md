# mod_AzerothServiceBus
## Introduction
AzerothCore is a great system designed to provide a space for developers to learn to code computer games using a topic they are familiar with. The project has been in development for many years and has taught many the art of C++ programming. The development landscape and runway are changing though and for developers to keep up they need to learn a new set of skills dealing with cloud development using languages other then C++. Applying the right tool for the right time for the right job.

AzerothServiceBus is an attempt to start moving in that direction. Tight itrecate loops will always remain in the realm of C++ where every ml second counts. But some logic and functionality in the game doesnt need to be that responsive. This logic can offloaded to other processes running on other containers, computer or processors. By moving this Latency tolerate logic out of process the remaining logic is better able to deal with what it does best.

This does however comes at a cost. Traditionally in AzerothCore things are written procedurally even to the point that we refer to many things as "Scripts" IE long procedural loops that start at the top and go to the bottum. There is another option though and that is the option that AzerothServiceBus embrasses. Event Driven programming. Instead of long list of instructions Event Based Development deals more with Reactions.


Event: TalkToQuestGiver.
Reaction: Open Quest Review Page

In the example above in procedural programing the worldserver identifies that the user has performed an action that requires it to lookup the data for the quest along with any other information that might apply, then it needs to any modifiers and  load up the information for the loot and then display a screen. All these things tie up reasource for a certain period of time. Granted it happens quickly (<10ms) but its resource intensive for the world server to do this for 1000's of users.

In an event driven system the worldservice publishs a OnQuestGiverTalk(user,questgiver) event and then it goes on about its business. The worldserver assumes that the external process is going to handle it. Eventually (100ms later) the external process has the Quest information ready. It then publishs a OnQuest_x_IsReadyfor(UserY) event. The gameserver sees that event and uses the paylod to display the Quest on the screen.  

These External Systems that service and potentially reacts to these events can be anything. A Docker Container a WebSite a node.js instance or a .Net WorkerClass. They can Live on the local workstation or up in the Cloud in Google, Azure or AWS. Once the event is decoupled from the game loop you can do anything with it.

With all this potential as you might expect that this is not your typical Module.
Though it has many of the same pieces a typical module it has many that are well outside the Boundery of what one would think of as a Mod so lets Get an overview of the Parts and Pieces. 

# Overview
## docker-compose.yml
	This is the Docker compose file to install the currently recommended version of kafta along with its dependencies
## mod_AzerothServiceBus.cmake
	This is simaler to the CMakeList.Txt you might see in other modules. However instead of running as a Spererate project this file gets embedded in the Modules CMakeList.Txt via a bit of magic with its name.
## LICENSE
	MIT
## mod_AzerothServiceBus.sln
	Solution File for the module. Much is writtent in C# however this does not prevent any language or system from subscribing to Kafka and processing Events. C# was just the initial language and the one the first example is in. Hopefull other examples will be forth coming.
## README.md
	This File

## conf
### mod_AzerothServiceBus.conf.dist
		The one configuration file. It's going to take some work but hopefully this will contain the one and only configuration file needed for the module. There are at the time of this writing a number of appsettings and hardcoded values that will eventually find there way here 
## src
### mod_DotNetCore_loader.cpp
	Initialization code for the two C++ parts of the Module
### mod_SDK
	This is were all the functionality we will consume is contained. The logic we referenced about to actually react to the event and pop the Quest Window is here and written/rewritten in a way that it can be consumed via a exported via extern extern "C" __declspec(dllexport).
### mod_EventPublishers
Its not certain at what point or how many Kafka events can be published to without a significant performance impact. For that reason not every event is published also there are many "events" that act more like functions returning a result after process these will be handled on a case by cases basis. 
#### DotNetCore_loader.cpp
Logic to load a hosted instance of the DotNet CLR
#### DotNetCorePlayerScript.cpp
Logic to call into the DotNet CLR when a player event happens
#### DotNetCoreWorldScript.cpp
Logic to call into the DotNet CLR when a world event happens
#### DotNetCore???Script.cpp
One for each Event Source that we want to publish events for.
## deps
### AzerothServiceBus
.NetCore 6 C# project that takes the events from the mod and passes them on to Kafka. This Project could eventually migrate back into the mod and the module may call KAfka directly at some point for increased performanceusing https://docs.confluent.io/kafka-clients/librdkafka/current/overview.html.
### AzerothServiceBus.Contracts
The Constants and structs used to pass data between C++ and Kafka.
### DotNetCoreAzeroth
Facade on top of the sdk.h extern "C" __declspec(dllexport) to make them easier to consume in DotNet. Other languages that can interact with a dllexport may eventuall have thier own. Primarily this is used when Kafka has a message or event intended for the world server. AzerothServiceBus picks up the event in KAfka and uses a method in the Library to pass it into the world server.

### DotNetServiceBus.Server
Example of a DotNetCore Kafka Client that processes events and reacts to them.


# Getting Started
	Open your copy of the azerothCore_wotlk. If you do not yet have a copy it can be retrieved via. 
	Git bash using
	git clone https://github.com/azerothcore/azerothcore-wotlk.git
	However there are more steps to setting up Azerothcore then a simple clone so make sure your authserver and worldserver are working to you expectations before continueing.

	If your WorldServer and AuthServer are working navigate to the modules directory within the azerothcore-wotlk directory. Here get a copy of this repository. The command to do this in at gitbash is
	git clone https://github.com/DavuKnight/mod_AzerothServiceBus
	
	Once downloaded you will see the docker-compose.yml file described above. Docker and docker compose are outside this overview but for this solution to work you will need a version of Kafka installed. This Docker-Copose file is what we setup for development with the config we know works.
	
	Once Kafka is setup run CMake and ensure the modules deploy You should see additional entries in your CMake Script stating that mod_SDK was installed, the mod_DotNetCoreEvents was installed and that nethost.lib has been successfully located and referenced.
	
	At this point the Mod is ready but doesnt actually do anything. That is because you need to provide the logic now for what you want to do.  

	An example of this in C# can be run by compiling the  mod_DotNetCore.sln and running the DotNet Core Server.

