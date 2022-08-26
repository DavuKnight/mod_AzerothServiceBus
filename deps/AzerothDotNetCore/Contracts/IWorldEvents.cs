﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AzerothDotNetCore.Contracts
{
    public interface IWorldEvents : IEvents
    {
        int OnBeforeConfigLoad();
        int OnBeforeWorldInitialized();
    }
}