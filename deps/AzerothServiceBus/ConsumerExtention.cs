using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AzerothServiceBus
{
    using System;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks;
    using Confluent.Kafka;

    public static class ConsumerExtensions
    {
        public static async ValueTask<ConsumeResult<TKey, TValue>> ConsumeAsync<TKey, TValue>(this IConsumer<TKey, TValue> consumer, CancellationToken ct)
        {
            try
            {
                var res = consumer.Consume(0);
                if (res != null)
                {
                    return res;
                }

                return await Task.Run(() => consumer.Consume(ct), ct);
            }
            catch (OperationCanceledException)
            {
                throw new TaskCanceledException($"Kafka consumer [{consumer.Name}] was canceled.");
            }
            catch (Exception e)
            {
                throw new Exception($"Kafka consumer [{consumer.Name}] has failed.", e);
            }
        }
    }
}
