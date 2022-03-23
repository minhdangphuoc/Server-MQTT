all:
	g++ main.cpp mqtt_receiv.cpp traffic_light.cpp -std=c++0x -pthread -lmosquitto -lmosquittopp -ljsoncpp -o go1

run: 
	./go1
