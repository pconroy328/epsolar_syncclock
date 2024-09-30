
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
    char    *controllerPortName = NULL;
    
    Logger_Initialize( "/tmp/epsolar_syncclock.log", 5 );
    Logger_LogWarning( "Version: %s\n", "v2.0"  );
    
    controllerPortName = findController( "/dev/ttyACM", 10, TRUE );
    if (controllerPortName != NULL) {
        Logger_LogInfo( "find controller worked - setting real time clock and disconnecting\n" );
        eps_setRealtimeClockToNow();
        epsolarModbusDisconnect();
    } else {
        Logger_LogInfo( "find controller DID NOT WORK - trying /dev/ttyACM1\n" );
    
        if (!epsolarModbusConnect( "/dev/ttyACM1", 1 )) {
            Logger_LogFatal( "Unable to open %s to connect to the solar charge controller\n", devPort );
            return (EXIT_FAILURE);
        }

        eps_setRealtimeClockToNow();
        epsolarModbusDisconnect();
    }
    
    Logger_LogWarning( "Clock sync'd\n");
    Logger_Terminate();
    return (EXIT_SUCCESS);
}

