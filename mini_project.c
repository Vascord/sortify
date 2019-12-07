#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
 
/* Use puts() to print constant strings */
 
#define MSG_WELCOME "WELCOME TO SORTIFY!"
#define MSG_SORT "Sort the following numbers:"
#define MSG_SORT2 "Please sort the numbers"
#define MSG_WELL "Well done!"
#define MSG_WIN "Congratulations, you win!"
#define MSG_OVER "Game Over."
#define MSG_WRONG "Wrong answer."
#define MSG_MAX "You have reached the maximum number of moves."
#define MSG_BYE "Bye."
#define MSG_UNKNOWN "Unknown option."
 
/* Will check in which level the player is and put it up t date*/
 
int level_check(int level, int points)
{
    if(points >= 50)
    {
        level = 6;
    }
    else if(points >= 40)
    {
        level = 5;
    }
    else if(points >= 30)
    {
        level = 4;
    }
    else if(points >= 20)
    {
        level = 3;
    }
    else if(points >= 10)
    {
        level = 2;
    }
    else if(points < 9)
    {
        level = 1;
    }
    return level;
}

 
/* generate a random integer between min and max */
 
int rand_number(const int min, const int max, int random_list[4])
{
    int r, x;
    for(x = 0; x < 4; x++)
    {
        r = (rand() % (max - min + 1)) + min;
        random_list[x] = r;
    }
    return random_list[4];
   
}
 
/* Create random robot_list depending of the level*/
 
int rand_list(int level, int random_list[4])
{
    if(level == 1)
    {
        random_list[4] = rand_number(0, 10, random_list);
    }
    else if(level == 2)
    {
        random_list[4] = rand_number(0, 30, random_list);
    }
    else if(level == 3)
    {
        random_list[4] = rand_number(-50, 30, random_list);
    }
    else if(level == 4)
    {
        random_list[4] = rand_number(-100, 0, random_list);
    }
    else if(level == 5)
    {
        random_list[4] = rand_number(-200, -100, random_list);
    }
    printf("%d, %d, %d, %d\n", random_list[0], random_list[1], random_list[2], random_list[3]);
    return random_list[4];
}
 
/* This will check if the player succeded in doing the list in the nice order */
 
int game_conditions(int player_nums[4], int robot_nums[4],int points)
{
 
    int cont = 0;
    int x,y,retry;

    fflush(stdin);

    /*This while will repeat over and over until the player put the same number as in the robot list*/        
    for (retry = 0; retry != 1;)
    {
        scanf("%d %d %d %d", &player_nums[0], &player_nums[1], &player_nums[2], &player_nums[3]);

        for (x = 0; x < 4; x++)
        {
            for (y = 0; y < 4; y++)
            {
                if (robot_nums[x] == player_nums[y])
                {
                    cont++;
                    break;
                }
            }
        }
        if (cont == 4)
        {
            retry = 1;
        }
        else 
        {
            puts(MSG_SORT2);
        }
        fflush(stdin);
    }
    /*This will see if the player succeded in his duty*/
    if (cont < 4)
    {
        puts(MSG_WRONG);
    }

    if (cont == 4)
    {
        cont = 0;
        for (x = 1; x < 4; x++)
        {
            if (player_nums[x-1] > player_nums[x])
            {
                puts(MSG_WRONG);
                return points;

            }
            else if (player_nums[x-1] <= player_nums[x])
            {
                cont += 1;
            }
        }
 
        if (cont == 3)
        {
            points += 5;
            puts(MSG_WELL);
            return points;
        }
    }

    fflush(stdin);

    return 0;
}
 
/* print the game status */
 
void print_status(const int level, const int points, const int plays)
{
    puts("+-----------------------------+");
    printf("| level:  %02d                  |\n", level);
    printf("| points: %02d                  |\n", points);
    printf("| plays:  %02d                  |\n", plays);
    puts("+-----------------------------+");
}
 
/* print the option menu */
 
void print_menu(void)
{
    puts("+-----------------------------+");
    puts("| SORTIFY                     |");
    puts("| p - next chalenge           |");
    puts("| q - quit                    |");
    puts("| m - print this information  |");
    puts("| s - show your status        |");
    puts("+-----------------------------+");
}
 
int main(int argc, char * argv[])
{
    
    puts(MSG_WELCOME);
    print_menu();
    
    /*Start the programm while verifing if there's a seed or not*/

    if(argc == 1)
    {
        srand(time(0));
    }
    else if(argc == 2)
    {
        srand(atoi(argv[1]));
    }

    /*Those are the valors that we will use*/

    char command = 'r';
    int points = 0;
    int level = 1;
    int plays = 0;
    
    /*This while will cause the game to continue until you quit/lose/win*/

    while(command != 'q' && level != 6 && plays != 30)
    {
        scanf("%c", &command);

        switch(command)
        {
 
            case 'p':
            {
                /*This part is where the game starts, putting player and robot list blank*/

                int player_nums[4] = {0, 0, 0, 0};
                int robot_nums[4] = {0, 0, 0, 0};
                puts(MSG_SORT);
                robot_nums[4] = rand_list(level, robot_nums);
                points = game_conditions(player_nums,robot_nums,points);
                level = level_check(level, points);
                plays += 1;

                /*The lose condition*/
                
                if(plays == 30)
                {
                    puts(MSG_MAX);
                    print_status(level, points, plays);
                    puts(MSG_OVER);
                }

                /*The win condition*/

                else if(level == 6)
                {
                    puts(MSG_WIN);
                    print_status(level, points, plays);
                    puts(MSG_OVER);
                }
                break;
            }
            case 'm':
            {
                print_menu();
                break;
            }    
            case 's':
            {
                print_status(level, points, plays);
                break;
            }
            case 'q':
            {
                print_status(level, points, plays);
                puts(MSG_BYE);
                break;
            }
            case 10:
            case 13:
            case 32:
                break;
            default :
            {
                puts(MSG_UNKNOWN);
                break;
            }
       
        }
       
    }

    return 0;
 
}