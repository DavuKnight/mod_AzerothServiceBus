using AzerothDotNetCore;

namespace AzerthDotNetCoreTests
{
    public class Tests
    {
        [SetUp]
        public void Setup()
        {
        }

        [Test]
        public void OnBeforeWorldInitialized()
        {
            IntPtr args = default(IntPtr);
            int arglength = 0;
            WorldEvents.OnBeforeWorldInitialized(args, arglength);
        }
    }
}