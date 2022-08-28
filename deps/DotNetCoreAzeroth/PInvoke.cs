using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DotNetCoreAzeroth
{
    public class PInvoke
    {
        [DllImport("worldserver.exe",
           CallingConvention = CallingConvention.Cdecl,
           CharSet = CharSet.Ansi)]
        public static extern int LogInformation(
            string catagory,
            string message
            );
    }
}
