using Confluent.Kafka;
using System.Configuration;

namespace AzerothServiceBus
{
    public static class WorldEvents
    {
        static ServiceBusDomain domain = ServiceBusDomain.Instance;

        private static void sendNullEvent(string eventName)
        {

            try
                {
                    Console.WriteLine(eventName + " is Now Sending===============================");

                    domain.NullEventProducer.Produce(eventName, new Message<Null, Null>(), r =>
Console.WriteLine(!r.Error.IsError
    ? $"Delivered message to {r.TopicPartitionOffset}"
    : $"Delivery Error: {r.Error.Reason}"));

                    Console.WriteLine(eventName + " Sent");
                }
                catch (Exception exc)
                {
                    Console.Write(exc.Message);
                }
        }

        // Called when the open/closed state of the world changes.
        public static int OnOpenStateChange(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnOpenStateChange);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called after the world configuration is (re)loaded.
        public static int OnAfterConfigLoad(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnAfterConfigLoad);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called when loading custom database tables
        public static int OnLoadCustomDatabaseTable(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnLoadCustomDatabaseTable);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called before the world configuration is (re)loaded.
        public static int OnBeforeConfigLoad(IntPtr arg, int argLength)
        {
            try
            {
                Console.WriteLine("Trying to Poke It-6;");
                DotNetCoreAzeroth.PInvoke.LogInformation("server.loading","****************AzerothEventHub Loaded.***************************");
                sendNullEvent(WorldsEventNames.OnBeforeConfigLoad);
                return 0;
            }
            catch(Exception exc)
            {
                Console.WriteLine(exc.Message);
                return 1;
            }
        }

        // Called before the message of the day is changed.
        public static int OnMotdChange(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnMotdChange);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called when a world shutdown is initiated.
        public static int OnShutdownInitiate(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnShutdownInitiate);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called when a world shutdown is cancelled.
        public static int OnShutdownCancel(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnShutdownCancel);
                return 0;
            }
            catch
            {
                return 1;
            }
        }
        // Called on every world tick (don't execute too heavy code here).
        public static int OnUpdate(IntPtr arg, int argLength)
        {
            try
            {
                //sendNullEvent("OnUpdate");
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called when the world is started.
        public static int OnStartup(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnStartup);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        // Called when the world is actually shut down.
        public static int OnShutdown(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnShutdown);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        /**
         * @brief Called after all maps are unloaded from core
         */
        public static int OnAfterUnloadAllMaps(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnAfterUnloadAllMaps);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        /**
         * @brief This hook runs before finalizing the player world session. Can be also used to mutate the cache version of the Client.
         *
         * @param version The cache version that we will be sending to the Client.
         */
        public static int OnBeforeFinalizePlayerWorldSession(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnBeforeFinalizePlayerWorldSession);
                return 0;
            }
            catch
            {
                return 1;
            }
        }

        /**
         * @brief This hook runs after all scripts loading and before itialized
         */
        public static int OnBeforeWorldInitialized(IntPtr arg, int argLength)
        {
            try
            {
                sendNullEvent(WorldsEventNames.OnBeforeWorldInitialized);
                return 0;
            }
            catch
            {
                return 1;
            }
        }
    }
}
