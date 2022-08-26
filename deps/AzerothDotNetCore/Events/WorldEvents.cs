using AzerothDotNetCore.Contracts;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace AzerothDotNetCore
{
    public static class WorldEvents
    {
        static IEnumerable<IWorldEvents> eventWrappers;
        static WorldEvents()
        {
            if (eventWrappers == null)
            {
                eventWrappers = ModuleManager.Instance.ServiceProvider.GetServices<IWorldEvents>();
            }

        }
        // Called when the open/closed state of the world changes.
        public static int OnOpenStateChange(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnOpenStateChange");
            return 0;
        }

        // Called after the world configuration is (re)loaded.
        public static int OnAfterConfigLoad(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnAfterConfigLoad");
            return 0;
        }

        // Called when loading custom database tables
        public static int OnLoadCustomDatabaseTable(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnLoadCustomDatabaseTable");
            return 0;
        }

        // Called before the world configuration is (re)loaded.
        public static int OnBeforeConfigLoad(IntPtr arg, int argLength)
        {
            try
            {
                Console.WriteLine($"OnBeforeConfigLoad");
                return 0;
            }
            catch (Exception exc)
            {
                Console.WriteLine(exc.Message);
                return 1;
            }
        }

        // Called before the message of the day is changed.
        public static int OnMotdChange(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnMotdChange");
            return 0;
        }

        // Called when a world shutdown is initiated.
        public static int OnShutdownInitiate(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnShutdownInitiate");
            return 0;
        }

        // Called when a world shutdown is cancelled.
        public static int OnShutdownCancel(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnShutdownCancel");
            return 0;
        }

        // Called on every world tick (don't execute too heavy code here).
        public static int OnUpdate(IntPtr arg, int argLength)
        {
            //Console.WriteLine($"OnUpdate");
            return 0;
        }

        // Called when the world is started.
        public static int OnStartup(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnStartup");
            return 0;
        }

        // Called when the world is actually shut down.
        public static int OnShutdown(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnShutdown");
            return 0;
        }

        /**
         * @brief Called after all maps are unloaded from core
         */
        public static int OnAfterUnloadAllMaps(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnAfterUnloadAllMaps");
            return 0;
        }

        /**
         * @brief This hook runs before finalizing the player world session. Can be also used to mutate the cache version of the Client.
         *
         * @param version The cache version that we will be sending to the Client.
         */
        public static int OnBeforeFinalizePlayerWorldSession(IntPtr arg, int argLength)
        {
            Console.WriteLine($"OnBeforeFinalizePlayerWorldSession");
            return 0;
        }

        /**
         * @brief This hook runs after all scripts loading and before itialized
         */
        public static int OnBeforeWorldInitialized(IntPtr arg, int argLength)
        {
            foreach(var eventwrapper in eventWrappers)
            {
                eventwrapper.OnBeforeWorldInitialized();
            }
            return 0;
        }

    }
}
