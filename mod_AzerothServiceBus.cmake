set(RDKAFKA_BUILD_STATIC ON CACHE BOOL "")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/mod_AzerothServiceBus/deps/librdkafka-1.8.2")
target_link_libraries(modules PUBLIC rdkafka++)
