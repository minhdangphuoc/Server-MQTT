
///////////////////////////  3.3.2022  KN /////////////////////////////
#include <cstdio>
#include <cstring>
#include <string>
#include <functional>     	// c++11
#include <unistd.h>
#include <iostream>        	// due to: cout

#include <fstream>
#include <time.h>



#include "mqtt.h"
#include "traffic_light.h"
#include "mqtt_receiv.h"

using namespace std;

#include <jsoncpp/json/json.h>

traffic_light tf1;

//////////////////////////////////////////////////////////////////////////
//////////
//////////    MQTT
//////////
/////////////////////////////////////////////////////////////////////////

mqtt::mqtt(const char *host, int port)						// costructor
{
	

	int keepalive = 600;

	printf("****   MQTT start connect ****** \n");

	connect(host, port, (int) keepalive);			// connect to mqtt broker

	loop_start();						// stay on mqtt loop
};


////////// ON CONNECT ///////////////////////////////////////////////////

void mqtt::on_connect(int rc)							// on connect callback
{
	printf("****   MQTT Connected with code= %d  *****\n", rc);
	if(rc == 0)
	{
					// Only attempt to subscribe on a successful connect. 

		subscribe(NULL, in_topic);

		printf("****   MQTT subscription to topic = ");printf(in_topic);
		printf("    ****\n");
	}
}

//////////////////////////  ON SUBSCRIBE ///////////////////////////////////////

void mqtt::on_subscribe(int mid, int qos_count, const int *granted_qos)		// on subcribe callback
{
	printf("****   MQTT Topic subscription succeeded.   ****\n");
}


//////////////////////////// Message received //////////////////////////////////

void mqtt::on_message(const struct mosquitto_message *message)			// on message callback

{
	std::string mqtt_message;						// mqtt message string

        printf("\n ===================  Message received  ================================ \n"); 

	mqtt_message = (char*) message->payload;

	printf("Message is = %s\n",mqtt_message.c_str()) ;
	tf1.setSignal((int)mqtt_message.c_str()[5]);
	tf1.print();
}  ////////////////////////////         end message received ////////////////////////





