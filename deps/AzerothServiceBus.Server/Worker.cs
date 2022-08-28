using static Confluent.Kafka.ConfigPropertyNames;
using System.Threading;
using Confluent.Kafka;
using System.Collections.Generic;
using Microsoft.Extensions.FileSystemGlobbing.Internal;

namespace AzerothServiceBus.Server
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;

        public Worker(ILogger<Worker> logger)
        {
            _logger = logger;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            var config = new ConsumerConfig
            {
                BootstrapServers = "localhost:9092",
                GroupId = Guid.NewGuid().ToString(),
                AutoOffsetReset = AutoOffsetReset.Earliest
            };

            using (var consumer = new ConsumerBuilder<Ignore, string>(config).Build())
            {
                IEnumerable<string> topics = new List<string>() 
                { 
                    WorldsEventNames.OnStartup,
                    WorldsEventNames.OnShutdownCancel,
                    WorldsEventNames.OnMotdChange,
                    WorldsEventNames.OnOpenStateChange
                };
                consumer.Subscribe("^WorldsEventNames.*");
                while (!stoppingToken.IsCancellationRequested)
                {
                    var consumeResult = consumer.Consume(stoppingToken);
                    if(consumeResult != null)
                    {
                        Console.WriteLine(consumeResult.Topic);
                    }
                }
            }
            await Task.CompletedTask;
        }
    }
}