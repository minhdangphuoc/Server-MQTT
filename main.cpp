


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
	char c;
	int i=0;
	string str="", ch;
	while(1)						// keep mqtt send theread running
	{
		// Refresh
		mqtt_obj.initWindow();
		 // move and print in window
		c = getch();
		switch (c)
		{
		case '\n':
			i=0;
			if (str.size()) mqtt_obj.add_log("\n" + str);
			str.clear();
			wclear(mqtt_obj.cmd_win);
			break;
		case 127:
			mvwprintw(mqtt_obj.cmd_win,1, i," ");
			if(i>0)
			{
				i--;
				str.pop_back();
			}
			break;
		default:
			if(i<18)
			{
			i++;
				ch = c;
				str += ch; 
			}
			mvwprintw(mqtt_obj.cmd_win,1, i,ch.c_str());
			break;
		}
	}							
	return 0;
}
