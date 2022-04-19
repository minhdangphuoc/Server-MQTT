all:
	g++ main.cpp mqtt_receiv.cpp -lncurses -std=c++0x -pthread -lmosquitto -lmosquittopp -ljsoncpp -o go1

run: 
	./go1
