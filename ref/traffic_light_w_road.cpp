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
int tfl2_status = 3;
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

void TFL2 (int mode)
{
    switch (mode)
    {
    case 1:
        tfl2_status = 1;
        break;
    case 2:
        tfl2_status = 2;
        break;
    case 3:
        tfl2_status = 3;    
    default:
        printf ("Error input");
        break;
    }
}

void control ()
{
    // State 1
    printMap();
    timer(5);
    TFL2(2);
    printMap();
    // State 2
    timer(2);
    TFL1(3);
    TFL2(1);
    printMap();
    // State 3
    timer(5);
    TFL1(2);
    printMap();
    // State 4
    timer(2);
    TFL1(1);
    TFL2(3);
    printMap();
}

void printMap ()
{
    int size = 23;
    bool printed = false;
    system("clear");
    for (auto i = 0; i<3; i++)
    {
        for (auto j = 0; j<size; j++)
        {
            printed = false;
            if(i==(size/2))
            {
                printed = true;
                printf("\033[31m\033[100m");
                printf("-");
            }
            if (printed == false) if((i==(size/2)+3||i==(size/2)+4||i==(size/2)+5)&&j==(size/2)+3)
            {
                printed = true;
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
            } 
            if (printed == false) if((j==(size/2)+3||j==(size/2)+4||j==(size/2+5))&&i==(size/2)-3)
            {
                printed = true;
                if(tfl2_status==j-((size/2)+2))
                {
                    switch(tfl2_status) 
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
            } 
            if (printed == false) if(j==(size/2))
            {
                printed = true;
                printf("\033[31m\033[100m");
                printf("|");
            } 
            if (printed == false) if(i==(size/2)-1||i==(size/2)+1)
            {
                printed = true;
                printf("\033[100m");
                printf(" ");
            } 
            if (printed == false) if(j==(size/2)-1||j==(size/2)+1)
            {
                printed = true;
                printf("\033[100m");
                printf(" ");
            }
            if (printed == false)
            {
                printf("\033[0m");
                printf(" ");
            }
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