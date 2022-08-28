

using Confluent.Kafka;
using DotNetCoreAzeroth;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace AzerothServiceBus
{
    public class ServiceBusConsumerService : BackgroundService
    {
        private readonly ILogger<ServiceBusConsumerService> _logger;
        public IServiceProvider Services { get; }
        public ServiceBusConsumerService(IServiceProvider services,
        ILogger<ServiceBusConsumerService> logger)
        {
            Services = services;
            _logger = logger;
        }
        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            await Task.Yield();
            _logger.LogInformation("Consume Scoped Service Hosted Service running.");
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
                    consumer.Subscribe("^ServerEvents.*");
                    Console.WriteLine("starting Async Consumer");
                    while (!stoppingToken.IsCancellationRequested)
                    {
                        await Task.Yield();
                        var consumeResult = await consumer.ConsumeAsync(stoppingToken);

                        if (consumeResult != null)
                        {
                            await processEvent(consumeResult);
                        }
                    }
                }
                catch (Exception exc)
                {
                    _logger.LogError(exc, "Unable to consume Kafka Events");
                }
            }
            await Task.CompletedTask;
        }

        private async Task processEvent(ConsumeResult<Ignore, string> consumeResult)
        {
            Console.WriteLine("Event Received");
        }
    }
}
