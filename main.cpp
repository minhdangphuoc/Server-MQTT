


//////////////////////////////////////  3.3.2022 //////////////////////////////
///
///	g++ main.cpp mqtt_receiv.cpp -std=c++0x -pthread -lmosquitto -lmosquittopp -ljsoncpp
///
///////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>


using namespace std;


#include "mqtt_receiv.h"

///////////////////////////////////////// conficuration ///////////////////////

#include "mqtt.h"

//////////////////////////////////// main /////////////////


int main(int argc, char *argv[])
{	
	// printf ("Raspberry Pi MQTT receive demo\n") ;

	// printf ("****   Subscribed to listen MQTT messages \n");

	mqtt mqtt_obj(host_addr, port_number);			// start mqtt 
	mqtt_obj.initWindow();
	
	while(1);						// keep mqtt send theread running
						
	return 0;
}
