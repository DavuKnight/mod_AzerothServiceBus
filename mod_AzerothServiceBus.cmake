
find_path(
NETHOST_INCLUDE_DIR 
NAMES nethost.h
PATHS C:/Program\ Files/dotnet/packs/Microsoft.NETCore.App.Host.win-x64/6.0.8/runtimes/win-x64/native
)

find_library(
NETHOST_LIBRARY 
nethost 
PATHS C:/Program\ Files/dotnet/packs/Microsoft.NETCore.App.Host.win-x64/6.0.8/runtimes/win-x64/native
)

message(STATUS "Include dir is: ${NETHOST_INCLUDE_DIR}")
message(STATUS "Found NETHOST_LIBRARY library: ${NETHOST_LIBRARY}")

if (NOT NETHOST_INCLUDE_DIR OR NOT NETHOST_LIBRARY)
message(FATAL_ERROR "** NETHOST_LIBRARY library not found!")
endif ()



add_library(nethost STATIC IMPORTED GLOBAL)
set_target_properties(nethost
  PROPERTIES
    IMPORTED_LOCATION
      "${NETHOST_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES
      "${NETHOST_INCLUDE_DIR}")

target_link_libraries(modules PUBLIC  nethost)
target_include_directories(modules
 PRIVATE
  "${NETHOST_INCLUDE_DIR}/bin")
  
 message(STATUS "Copying ${NETHOST_INCLUDE_DIR}/bin/nethost.dll to  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  
 add_custom_command(TARGET modules POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${NETHOST_INCLUDE_DIR}/nethost.dll"      # <--this is in-file
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(ConfigurationName)")                 # <--this is out-file path