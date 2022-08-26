using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DotNetCoreAzeroth
{
    internal class JsonApi
    {
        [DllImport("worldserver.exe",
           CallingConvention = CallingConvention.Cdecl,
           CharSet = CharSet.Ansi)]
        internal static extern void JsonAPIEntryPoint(
            string path,
            string verb,
            string jsonbody
            );
    }
}
