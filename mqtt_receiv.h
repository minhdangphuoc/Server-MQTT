//  KN 25.2.2021

#pragma once
#ifndef MQTT_H
#define MQTT_H

#include <mosquittopp.h>
#include <math.h>
#include <ncurses.h>


class mqtt : public mosqpp::mosquittopp			// mqtt class
{
	private:
	std::string log;

	public:
		// New windows
		WINDOW *info_win_1; 
		WINDOW *info_win_2; 
		WINDOW *cmd_win;
		
		mqtt(const char *host, int port);	 // constructor
		~mqtt(){
			endwin();
		}

				// call back functions
		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		bool send_message(std::string message);
		void initWindow();
		void add_log(std::string);
	
};

#endif // MQTT_H