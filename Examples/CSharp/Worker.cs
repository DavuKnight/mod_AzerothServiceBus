using static Confluent.Kafka.ConfigPropertyNames;
using System.Threading;
using Confluent.Kafka;
using System.Collections.Generic;
using Microsoft.Extensions.FileSystemGlobbing.Internal;

namespace Examples.CSharp
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

            //using (var consumer = new ProducerBuilder<Ignore, string>(config).Build())
            //{
            //    IEnumerable<string> topics = new List<string>()
            //    {
            //        WorldsEventNames.OnStartup,
            //        WorldsEventNames.OnShutdownCancel,
            //        WorldsEventNames.OnMotdChange,
            //        WorldsEventNames.OnOpenStateChange
            //    };
            //    consumer.Subscribe("^W.*");
            //    consumer.Subscribe("^PlayerScript.*");
            //    while (!stoppingToken.IsCancellationRequested)
            //    {
            //        var consumeResult = consumer.Consume(stoppingToken);
            //        if (consumeResult != null)
            //        {
            //            Console.WriteLine(consumeResult.Topic);
            //            Console.WriteLine(consumeResult.Message.Value);

            //        }
            //    }
            //}

            using (var consumer = new ConsumerBuilder<Ignore, string>(config).Build())
            {
                IEnumerable<string> topics = new List<string>() 
                { 
                    WorldsEventNames.OnStartup,
                    WorldsEventNames.OnShutdownCancel,
                    WorldsEventNames.OnMotdChange,
                    WorldsEventNames.OnOpenStateChange
                };
                consumer.Subscribe(new List<string>() { "^WorldScript.*", "^PlayerScript.*" });
                while (!stoppingToken.IsCancellationRequested)
                {
                    var consumeResult = consumer.Consume(stoppingToken);
                    if(consumeResult != null)
                    {
                        Console.WriteLine(consumeResult.Topic);
                        Console.WriteLine(consumeResult.Message.Value);

                    }
                }
            }
            await Task.CompletedTask;
        }
    }
}
