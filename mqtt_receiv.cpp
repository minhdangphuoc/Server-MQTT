
///////////////////////////  3.3.2022  KN /////////////////////////////
#include <cstdio>
#include <cstring>
#include <string>
#include <functional>     	// c++11
#include <unistd.h>
#include <iostream>        	// due to: cout

#include <fstream>
#include <time.h>



#include "traffic_light.h"
#include "mqtt_receiv.h"
#include "mqtt.h"

using namespace std;

#include <jsoncpp/json/json.h>


traffic_light tf1;
Json::Reader reader; 
Json::Value root; 

//////////////////////////////////////////////////////////////////////////
//////////
//////////    MQTT
//////////
/////////////////////////////////////////////////////////////////////////

mqtt::mqtt(const char *host, int port)						// costructor
{
	// Ncurse Init
	initscr();

	// add window
	info_win_1 = newwin(3, 20, 1, 1); 
	info_win_2 = newwin(3, 20, 1, 25); 
	cmd_win = newwin(3, 20, 5,15);
	
	//init
	initWindow();


	int keepalive = 600;

	add_log("****   MQTT start connect ****** \n");

	connect(host, port, (int) keepalive);			// connect to mqtt broker
	
	loop_start();						// stay on mqtt loop
};

/// Send message
bool mqtt::send_message(std::string message)

 {
 		// Send message - depending on QoS, mosquitto lib managed re-submission this the thread
 		//
 		// * NULL : Message Id (int *) this allow to latter get status of each message
 		// * topic : topic to be used
 		// * lenght of the message
 		// * message
 		// * qos (0,1,2)
 		// * retain (boolean) - indicates if message is retained on broker or not
 		// Should return MOSQ_ERR_SUCCESS
 
	int ret = publish(NULL,out_topic,message.length(),message.c_str(),1,false);

	add_log("Message published ");
	add_log(message);
	add_log("\n");
	
	if (reader.parse(message, root) == true)   
	{
		add_log("Command: ");
		if (!root["Move"].isNull())
		{
			add_log("Move - Value: " + root["Move"].asString());
		}

		if (!root["Turn"].isNull())
		{
			add_log("Turn - Value: " + root["Turn"].asString());
		}
		// tf1.print();
	} else {
		add_log("\n Cannot parse JSON or unvalid command \n"); 
	}

	initWindow();

 	return ( ret == MOSQ_ERR_SUCCESS );
 }


////////// ON CONNECT ///////////////////////////////////////////////////

void mqtt::on_connect(int rc)							// on connect callback
{
	add_log("\n****   MQTT Connected with code= " + to_string(rc) +"  *****");
	if(rc == 0)
	{
					// Only attempt to subscribe on a successful connect. 

		subscribe(NULL, in_topic);

		add_log("\n****   MQTT subscription to topic = ");
		add_log(in_topic);
		add_log("****\n");
	}
}

//////////////////////////  ON SUBSCRIBE ///////////////////////////////////////

void mqtt::on_subscribe(int mid, int qos_count, const int *granted_qos)		// on subcribe callback
{
	add_log("****   MQTT Topic subscription succeeded.   ****\n");
	initWindow();
}


//////////////////////////// Message received //////////////////////////////////

void mqtt::on_message(const struct mosquitto_message *message)			// on message callback

{

	std::string mqtt_message;						// mqtt message string

	
    // add_log("\nMessage received: \n"); 

	mqtt_message = (char*) message->payload;
	// add_log("Message is = "+ mqtt_message +"\n") ;
	
	if (reader.parse(mqtt_message, root) == true)   
	{
		if (!root["analog"].isNull())
		{
			int analogValue = stoi(root["analog"].asString());
			std::cout << analogValue << std::endl;
			tf1.setSignal(1 + (analogValue>300) + (analogValue>600) + (analogValue>1024)); 
			if(!send_message("{\"TFL\":" + to_string(1 + (analogValue>300) + (analogValue>600) + (analogValue>1024)) + "}")) add_log("Message did not send\n") ;
		}

		if (root["TFL"].isInt())
		{
			int state = root["TFL"].asInt(); 
			tf1.setSignal(state);
			// mvprintw(9,0,to_string(state).c_str());
			// mvwprintw(info_win_1, 1, 1, to_string(state).c_str());
		}

		if (!root["Distance"].isNull())
		{
			int dist = root["Distance"].asInt(); 
			// mvprintw(9,0,to_string(state).c_str());
			wclear(info_win_1);
			mvwprintw(info_win_1, 1, 1, (to_string(dist) + " cm").c_str());
		}

		if (!root["Compass"].isNull())
		{
			int comp = root["Compass"].asInt(); 
			// mvprintw(9,0,to_string(state).c_str());
			wclear(info_win_2);
			mvwprintw(info_win_2, 1, 1, (to_string(comp) + " deg").c_str());
		}
		// tf1.print();
	} else {
		// add_log("\n Cannot parse JSON \n"); 
	}
	
	initWindow();
}  ////////////////////////////         end message received ////////////////////////

void mqtt::add_log(std::string str)
{
	log += str;
}

void mqtt::initWindow()
{
	noecho();
	
	// border
	wborder(info_win_1, '#', '#', '#', '#', '#', '#', '#', '#');
	wborder(info_win_2, '#', '#', '#', '#', '#', '#', '#', '#');
	wborder(cmd_win, '#', '#', '#', '#', '#', '#', '#', '#');

	// Add Window Title
	mvwprintw(info_win_1, 0, 1, "Distance");
	mvwprintw(info_win_2, 0, 1, "Compass");
	mvwprintw(cmd_win, 0, 1, "Command");

	// print log - test
	mvprintw(10,0,log.c_str());

	// Refresh
	wrefresh(info_win_1);
	wrefresh(info_win_2);
	wrefresh(cmd_win);
	refresh();
}



