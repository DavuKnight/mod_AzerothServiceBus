using static Confluent.Kafka.ConfigPropertyNames;
using System.Threading;
using Confluent.Kafka;
using System.Collections.Generic;
using Microsoft.Extensions.FileSystemGlobbing.Internal;
using AzerothServiceBus.Events;

namespace AzerothServiceBus.Server
{
    public class ConsumerEventService : BackgroundService
    {
        private readonly ILogger<ConsumerEventService> _logger;
        static IProducer<Null, Null> nullProducer;
        public ConsumerEventService(ILogger<ConsumerEventService> logger)
        {
            _logger = logger;
            var producerConfig = new ProducerConfig
            {
                BootstrapServers = "localhost:9092"
            };
            nullProducer = new ProducerBuilder<Null, Null>(producerConfig).Build();
            sendNullEventAsync(ServerEvents.Initializing);
        }
        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            var consumerConfig = new ConsumerConfig
            {
                BootstrapServers = "localhost:9092",
                GroupId = Guid.NewGuid().ToString(),
                AutoOffsetReset = AutoOffsetReset.Earliest
            };
            using (var consumer = new ConsumerBuilder<Ignore, string>(consumerConfig).Build())
            {
                try
                {
                    consumer.Subscribe("^WorldsEventNames.*");

                    while (!stoppingToken.IsCancellationRequested)
                    {
                        var consumeResult = consumer.Consume(stoppingToken);
                        if (consumeResult != null)
                        {
                            await processEvent(consumeResult);
                        }
                    }
                }
                catch(Exception exc)
                {
                    Console.WriteLine(exc.Message);
                }
                finally
                {
                    Console.WriteLine("Bye");
                }
            }
            await Task.CompletedTask;
        }

        private async Task processEvent(ConsumeResult<Ignore, string> consumeResult)
        {
            if (consumeResult.Topic == WorldsEventNames.OnBeforeConfigLoad) 
            {
                await sendNullEventAsync(ServerEvents.Initialized);
            }
            else
            {
                Console.WriteLine(consumeResult.Topic);
            }

        }
        private static async Task sendNullEventAsync(string eventName)
        {
            try
            {
                Console.WriteLine(eventName + " Sending");

                var report = await nullProducer.ProduceAsync(eventName, new Message<Null, Null>());
                Console.WriteLine(report.Value);
                Console.WriteLine(eventName + " Sent");
            }
            catch(Exception exc)
            {
                Console.Write(exc.Message);
            }
        }

    }
}
