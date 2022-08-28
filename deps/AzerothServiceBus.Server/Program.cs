using AzerothServiceBus.Server;

IHost host = Host.CreateDefaultBuilder(args)
    .ConfigureServices(services =>
    {
        services.AddHostedService<ConsumerEventService>();
    })
    .Build();

await host.RunAsync();
