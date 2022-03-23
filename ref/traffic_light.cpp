/*
enum Colors {
RESET_COLOR,
BLACK_TXT = 30,
RED_TXT,
GREEN_TXT,
YELLOW_TXT,
BLUE_TXT,
MAGENTA_TXT,
CYAN_TXT,
WHITE_TXT,

BLACK_BKG = 40,
RED_BKG,
GREEN_BKG,
YELLOW_BKG,
BLUE_BKG,
MAGENTA_BKG,
CYAN_BKG,
WHITE_BKG	
};
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int tfl1_status = 1;
long long counter = 0;

void printMap();

void TFL1 (int mode)
{
    switch (mode)
    {
    case 1:
        tfl1_status = 1;
        break;
    case 2:
        tfl1_status = 2;
        break;
    case 3:
        tfl1_status = 3;
        break;    
    default:
        printf ("Error input");
        break;
    }
}

void timer(int time)
{
    for (int i = 0; i< time; i++)
    {
        usleep(1000000);
        counter++;
        printMap(); // add to the counter
    }

}

void control ()
{
    // State 1
    printMap();
    timer(5);
    printMap();
    // State 2
    timer(2);
    TFL1(3);
    printMap();
    // State 3
    timer(5);
    TFL1(2);
    printMap();
    // State 4
    timer(2);
    TFL1(1);
    printMap();
}

void printMap ()
{
    int size = 3;
    system("clear");
    for (auto i = 0; i<size; i++)
    {
        if(tfl1_status==i-((size/2)+2))
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
    printf("%i\n",counter);
}

int main(int argc, char *argv[])
{
    while (true) 
    {
        control();
        counter = 0;
    }
    return 0;
}