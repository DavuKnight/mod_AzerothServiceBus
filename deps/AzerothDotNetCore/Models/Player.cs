using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace AzerothDotNetCore.Models
{
    internal class MarchelledPlayer
    {
        public string Name { get; }
        public ulong AccountId { get; }

        [StructLayout(LayoutKind.Sequential)]
        struct PlayerArgs
        {
            public UInt64 AccountId;
            public string Name;
        }

        public MarchelledPlayer(IntPtr arg)
        {
            PlayerArgs playerArgs = Marshal.PtrToStructure<PlayerArgs>(arg);
            Name =  playerArgs.Name;
            AccountId = playerArgs.AccountId;
        }
    }
}
