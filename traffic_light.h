#pragma once
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdio.h>
#include <unistd.h>

class traffic_light
{
private:
    int tfl1_status;
public:
    traffic_light(/* args */);

    void setSignal(int i) 
    {
        tfl1_status = i;
    }
    void print();
};

traffic_light::traffic_light(/* args */)
{
    tfl1_status = 0;
}

void traffic_light::print()
{
    int size = 3;
    for (auto i = 0; i<size; i++)
    {
        if(tfl1_status==i+1)
        {
            switch(tfl1_status) 
            {
                case 1: 
                printf("\033[30;101m");
                break;
                case 2: 
                printf("\033[30;103m");
                break;
                case 3: 
                printf("\033[30;102m");
                break;
            }
            printf(" ");
        }else{
            printf("\033[100m");
            printf(" ");
        }
        printf("\033[0m");
        printf("\n");
    }
}

#endif // TRAFFIC_LIGHT_H