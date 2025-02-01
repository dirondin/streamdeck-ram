#include "StreamDeckPlugin.h"

#include <StreamDeckSDK/ESDMain.h>

int main(int argc, const char** argv)
{
    return esd_main(argc, argv, new StreamDeckPlugin());
}
