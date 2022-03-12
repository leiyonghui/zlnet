#include <stdio.h>
#include "network/Network.h"
#include "network/Common.h"
#include <iostream>
#include "network/Address.h"

using namespace network;
using namespace std;




#ifdef __linux

#endif // __Linux


int main()
{
    CAddress addr("127.0.0.1", 99);
    core_log_trace(addr.toString());
    return 0;
}