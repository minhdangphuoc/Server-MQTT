//  KN 25.2.2021

#pragma once
#ifndef MQTT_H
#define MQTT_H

#include <mosquittopp.h>
#include <math.h>
#include "mqtt.h"

class mqtt : public mosqpp::mosquittopp			// mqtt class
{
	private: 
	initscr();

	// New windows
	WINDOW *info_win_1 = newwin(3, 20, 1, 1); 
	wborder(info_win_1, '#', '#', '#', '#', '#', '#', '#', '#');

	WINDOW *info_win_2 = newwin(3, 20, 1, 25); 
	wborder(info_win_2, '#', '#', '#', '#', '#', '#', '#', '#');

	WINDOW *cmd_win = newwin(3, 20, 5,15);

	// Init refresh
	refresh();
	wrefresh(info_win_1);
	wrefresh(info_win_2);
	wrefresh(cmd_win);
	public:
		mqtt(const char *host, int port);	 // constructor
		~mqtt(){};

				// call back functions
		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		bool send_message(std::string message);
};

#endif // MQTT_H