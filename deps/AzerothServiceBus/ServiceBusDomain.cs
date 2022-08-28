using static Confluent.Kafka.ConfigPropertyNames;
using System.Threading;
using Confluent.Kafka;
using System.Collections.Generic;
using Microsoft.Extensions.FileSystemGlobbing.Internal;
using AzerothServiceBus.Events;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.DependencyInjection;
using DotNetCoreAzeroth;

namespace AzerothServiceBus
{
    internal class ServiceBusDomain
    {
        internal IProducer<Null, Null> NullEventProducer;
        private static ServiceBusDomain instance = new ServiceBusDomain();
        private ServiceBusDomain() {
            initialize();
        }
        public void initialize()
        {
                try
                {
                    var producerConfig = new ProducerConfig
                    {
                        BootstrapServers = "localhost:9092"
                    };
                    NullEventProducer = new ProducerBuilder<Null, Null>(producerConfig).Build();

                    var consumerConfig = new ConsumerConfig
                    {
                        BootstrapServers = "localhost:9092",
                        GroupId = Guid.NewGuid().ToString(),
                        AutoOffsetReset = AutoOffsetReset.Earliest
                    };

                    IHost host = Host.CreateDefaultBuilder()
                        .ConfigureServices(services =>
                        {
                            services.AddHostedService<ServiceBusConsumerService>();
                        })
                                .ConfigureLogging((_, logging) =>
                                {
                                    logging.SetMinimumLevel(LogLevel.Trace);
                                    logging.ClearProviders();
                                    logging.AddSimpleConsole(options => options.IncludeScopes = true);
                                    logging.AddEventLog();
                                })
                        .Build();

                    host.Start();
                }
                catch (Exception exc)
                {
                    Console.WriteLine(exc.Message);
                }
        }
        public static ServiceBusDomain Instance
        {
            get
            {
                return instance;
            }
        }
    }
}
