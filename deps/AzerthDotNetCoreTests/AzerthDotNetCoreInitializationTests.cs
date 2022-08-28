

using AzerothServiceBus;

namespace AzerthDotNetCoreTests
{
    public class AzerthDotNetCoreInitializationTests
    {
        [SetUp]
        public void Setup()
        {
        }

        [Test]
        public void OnBeforeWorldInitialized()
        {
            WorldEvents.OnBeforeConfigLoad(default(IntPtr), 0);
        }
    }
}
