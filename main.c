
/* 
 * File:   main.c
 * Author: pconroy
 *
 *  Sync's EPEVER Charge Controller clock
 * Created on November 5, 2023, 12:20 PM
 */


#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <log4c.h>
#include <libepsolar.h>
/*
 * 
 */
int main(int argc, char** argv) 
{
    const char *devPort = "/dev/ttyXRUSB0";
    
    Logger_Initialize( "/tmp/epsolar_syncclock.log", 5 );
    Logger_LogWarning( "Version: %s\n", "v1.0"  );

    if (!epsolarModbusConnect( devPort, 1 )) {
        Logger_LogFatal( "Unable to open %s to connect to the solar charge controller\n", devPort );
        return (EXIT_FAILURE);
    }

    eps_setRealtimeClockToNow();
    epsolarModbusDisconnect();
    
    Logger_LogWarning( "Clock sync'd\n");
    Logger_Terminate();
    return (EXIT_SUCCESS);
}

