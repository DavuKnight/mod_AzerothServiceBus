using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using static System.Net.WebRequestMethods;

namespace AzerothDotNetCore
{

    internal sealed class ModuleManager
    {
        public IServiceProvider ServiceProvider { get; set; }
        IHost azerothHostedService;
        public ModuleManager()
        {
            azerothHostedService = Host.CreateDefaultBuilder()
                .ConfigureServices((hostedService,services)=> configureServices(hostedService,services))
                .Build();
            ServiceProvider = azerothHostedService.Services;
        }

        private void configureServices(HostBuilderContext hostedService, IServiceCollection services)
        {
            var modules = hostedService.Configuration.GetSection("Modules").GetChildren();
            foreach(var module in modules)
            {
                var moduleAssembly = Assembly.LoadFrom(module.Value);
                foreach(Type modulesType in moduleAssembly.GetTypes())
                {
                    if(modulesType.IsAssignableTo(typeof(IWorldEvents)))
                    {
                        services.AddSingleton<IWorldEvents>((s)=>Activator.CreateInstance(modulesType) as IWorldEvents);
                    }
                    if (modulesType.IsAssignableTo(typeof(IPlayerEvents)))
                    {
                        services.AddSingleton<IPlayerEvents>((s) => Activator.CreateInstance(modulesType) as IPlayerEvents);
                    }

                }

                services.AddSingleton(module);
            }
        }

 

        private static volatile ModuleManager? instance;
        private static readonly object threadLock = new object();

        public static ModuleManager Instance
        {
            get
            {
                if (instance != null) return instance;

                lock (threadLock)
                {
                    if (instance == null)
                    {
                        instance = new ModuleManager();
                    }
                }
                return instance;
            }
        }
    }
}

