#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "proc.h"
/*struct player{
    char name[30];
    int id;
    int level;
    int LastGame;
    char lastmapname;
}player;*/
/*void rows_clos(char * filename , int * rows , int * cols);
char ** open_file(char * filename);
void show_matrix(char ** Matrix, int rows ,int cols);
void movep_right(char ** matrix,int rows, int cols);
void movep_left(char ** matrix,int rows, int cols);
void movep_up(char ** matrix,int rows, int cols);
void movep_down(char ** matrix,int rows, int cols);
void change_first_ghost(char ** matrix,int rows,int cols);
void move_G1(char ** matrix, int rows, int cols);
void move_G2(char ** matrix, int rows, int cols);
int GameOver(char ** matrix,int rows,int cols);
int GameWon(char ** matrix, int rows, int cols);
int check_pill_A(char ** matrix,int rows,int cols);
int check_pill_B(char ** matrix,int rows,int cols);
int check_pill_C(char ** matrix,int rows,int cols);
void stor_player_info(struct player * player1);
void load_player_info(struct player * player1);
void show_user_info(struct player player1);
void store_map_A(char ** matrix,int rows,int cols);
void store_map_B(char ** matrix,int rows,int cols);
void store_map_C(char ** matrix,int rows,int cols);
//void lastgamA(struct player * player1 , char ** lastA, int rows_A, int cols_A);
*/
int main()
{
    SetConsoleOutputCP(65001);
    char mapA[10] = "mapA.txt";
    char mapB[10] = "mapB.txt";
    char mapC[10] = "mapC.txt";
    int rows_A, cols_A, rows_B, cols_B, rows_C, cols_C;
    int continue_game ;
    int menu_choice;
    struct player player1;
    char ** lastA;
    rows_clos(mapA,&rows_A,&cols_A);
    rows_clos(mapB,&rows_B,&cols_B);
    rows_clos(mapC,&rows_C,&cols_C);

    printf(BOLD_BLUE "WELCOME TO THE PAC-MAN GAME \U0001F60D" RESET);
    Sleep(2000);
    system("cls");
    while(2)
    {
        int flag_leave = 0;
        printf(BOLD_MAG "\t\t\tSELECT AN OPTION FROM THE LIST BELOW\n1.START A NEW GAME\n2.CONTINUE THE PERVIOUS UNFINISHED GAME\n3.SHOW PLAYER INFO\n4.EXIT\n" RESET);
        scanf("%d", &menu_choice);
        switch(menu_choice)
        {
            load_player_info(&player1);
            case 1:
            {
                while(1)
                {
                    
                    char ** map_A = open_file(mapA);
                    change_first_ghost(map_A,rows_A,cols_A);
                    char ** map_B = open_file(mapB);
                    change_first_ghost(map_B,rows_B,cols_B);
                    char ** map_C = open_file(mapC);
                    change_first_ghost(map_C,rows_C,cols_C);
                    system("cls");
                    show_all_maps(map_A,rows_A,cols_A,map_B,rows_B,cols_B,map_C,rows_C,cols_C);
                    load_player_info(&player1);
                    char map_choice;
                    scanf(" %c",&map_choice);
                    system("cls");
                        
                    char move_pacman;
                    if(map_choice == 'A' || map_choice == 'a')
                    {
                        printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                        show_matrix(map_A,rows_A,cols_A);
                        printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_A(map_A,rows_A,cols_A));
                        while(1)
                        {
                            move_pacman = getch();
                            if( move_pacman == 'w' || move_pacman =='W')
                            {
                                movep_up(map_A,rows_A,cols_A);
                            }
                            else if( move_pacman == 's' || move_pacman =='S')
                            {
                                    movep_down(map_A,rows_A,cols_A);
                            }
                            else if( move_pacman == 'd' || move_pacman =='D')
                            {
                                movep_right(map_A,rows_A,cols_A);
                            }
                            else if( move_pacman == 'a' || move_pacman =='A')
                            {
                                movep_left(map_A,rows_A,cols_A);
                                    
                            }
                            else if( move_pacman == 27)
                            {
                                player1.LastGame = 0;
                                system("cls");
                                player1.lastmapname = 'A';
                                store_map_A(map_A, rows_A, cols_A);
                                printf( BOLD_MAG "you will leave the game in a few seconds...");
                                Sleep(2345);
                                break;
                            }
                            system("cls");
                            move_G1(map_A,rows_A,cols_A);
                            printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                            show_matrix(map_A,rows_A,cols_A);
                            printf( BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_A(map_A,rows_A,cols_A));
                            if(GameOver(map_A,rows_A,cols_A) == 0)
                            {
                                printf( BHRED "GAME OVER!" RESET);
                                player1.level = player1.level - 1;
                                player1.LastGame = 1;
                                player1.lastmapname = 'F';
                                Sleep(500);
                                break;
                            }
                            else if( GameWon(map_A,rows_A,cols_A) == 0)
                            {
                                printf( BOLD_MAG "YOU WON!" RESET);
                                player1.level = player1.level + 3;
                                player1.LastGame = 1;
                                player1.lastmapname = 'F';
                                Sleep(500);
                                break;
                            }
                        }
                    }
                    else if(map_choice == 'B' || map_choice == 'b')
                    {
                        printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                        show_matrix(map_B,rows_B,cols_B);
                        printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/2\n" RESET,player1.level, check_pill_B(map_B,rows_B,cols_B));
                        while(1)
                        {
                            move_pacman = getch();
                            if( move_pacman == 'w' || move_pacman =='W')
                            {
                                movep_up(map_B,rows_B,cols_B);
                            }
                            else if( move_pacman == 's' || move_pacman =='S')
                            {
                                movep_down(map_B,rows_B,cols_B);
                            }
                            else if( move_pacman == 'd' || move_pacman =='D')
                            {
                                movep_right(map_B,rows_B,cols_B);
                            }
                            else if( move_pacman == 'a' || move_pacman =='A')
                            {
                                movep_left(map_B,rows_B,cols_B);
                            }
                            else if( move_pacman == 27)
                            {
                                player1.LastGame = 0;
                                player1.lastmapname = 'B';
                                store_map_B(map_B, rows_B, cols_B);
                                system("cls");
                                printf( BOLD_MAG "you will leave the game in a few seconds...");
                                Sleep(2345);
                                break;
                            }
                            system("cls");
                            move_G2(map_B,rows_B,cols_B);
                            move_G1(map_B,rows_B,cols_B);
                            printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                            show_matrix(map_B,rows_B,cols_B);
                            printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/2\n" RESET,player1.level, check_pill_B(map_B,rows_B,cols_B));
                            if(GameOver(map_B,rows_B,cols_B) == 0)
                            {
                                printf( BHRED "GAME OVER!" RESET);
                                player1.level = player1.level - 1;
                                player1.LastGame = 1;
                                player1.lastmapname = 'F';
                                Sleep(500);
                                break;
                            }
                            else if( GameWon(map_B,rows_B,cols_B) == 0)
                            {
                                printf(BOLD_MAG "YOU WON!" RESET);
                                player1.level = player1.level + 3;
                                player1.LastGame = 1;
                                player1.lastmapname = 'F';
                                Sleep(500);
                                break;
                            }
                        }
                            
                    }
                    else if( map_choice == 'C' || map_choice == 'c')
                    {
                        printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                        show_matrix(map_C,rows_C,cols_C);
                        printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/3\n" RESET,player1.level, check_pill_C(map_C,rows_C,cols_C));
                        while(1)
                        {
                            move_pacman = getch();
                            if( move_pacman == 'w' || move_pacman =='W')
                            {
                                movep_up(map_C,rows_C,cols_C);
                            }
                            else if( move_pacman == 's' || move_pacman =='S')
                            {
                                movep_down(map_C,rows_C,cols_C);
                            }
                            else if( move_pacman == 'd' || move_pacman =='D')
                            {
                                movep_right(map_C,rows_C,cols_C);
                            }
                            else if( move_pacman == 'a' || move_pacman =='A')
                            {
                                movep_left(map_C,rows_C,cols_C);
                            }
                            else if( move_pacman == 27)
                            {
                                player1.LastGame = 0;
                                player1.lastmapname = 'C';
                                store_map_C(map_C, rows_C, cols_C);
                                system("cls");
                                printf( BOLD_MAG "you will leave the game in a few seconds...");
                                Sleep(2345);
                                break;
                            }
                            system("cls");
                            move_G1(map_C,rows_C,cols_C);
                            move_G2(map_C,rows_C,cols_C);
                            printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                            show_matrix(map_C,rows_C,cols_C);
                            printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/3\n" RESET,player1.level, check_pill_C(map_C,rows_C,cols_C));
                            if(GameOver(map_C,rows_C,cols_C) == 0)
                            {
                                printf( BHRED "GAME OVER!" RESET);
                                player1.level = player1.level - 1;
                                player1.LastGame = 1;
                                player1.lastmapname = 'F';
                                Sleep(500);
                                break;
                            }
                            else if( GameWon(map_C,rows_C,cols_C) == 0)
                            {
                                printf(BOLD_MAG "YOU WON!" RESET);
                                player1.level = player1.level + 3;
                                player1.LastGame = 1;
                                player1.lastmapname = 'F';
                                Sleep(500);
                                break;
                            }
                        }

                    }
                    stor_player_info(&player1);

                    Sleep(1500);
                    system("cls");
                    printf(BOLD_MAG "\nDO YOU WANT TO START A NEW GAME?\n1.yes\n2.no\n" RESET);
                        
                    scanf("%d",&continue_game);
                    if(continue_game == 2)
                    {
                        break;
                    }
                    


                }
            }
            break;
            case 2:
            {
                while(3)
                {
                    if(player1.LastGame  == 1)
                    {
                        system("cls");
                        printf(BOLD_MAG "\nThere is no uncoplate game.\n" RESET);
                        Sleep(5000);
                        break;
                    }
                    else if(player1.LastGame == 0)
                    {
                        char last_A[16] = "storedmapA.txt";
                        char last_B[16] = "storedmapB.txt";
                        char last_C[16] = "storedmapC.txt";
                        char move_pacman;
                        char map_condition;
                        map_condition = player1.lastmapname;
                        if(map_condition == 'A')
                        {
                            lastA = open_file(last_A);
                            
                            while(4)
                            {

                                printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                                show_matrix(lastA,rows_A,cols_A);
                                printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_A(lastA,rows_A,cols_A));
                                move_pacman = getch();
                                if( move_pacman == 'w' || move_pacman =='W')
                                {
                                    movep_up(lastA,rows_A,cols_A);
                                }
                                else if( move_pacman == 's' || move_pacman =='S')
                                {
                                        movep_down(lastA,rows_A,cols_A);
                                }
                                else if( move_pacman == 'd' || move_pacman =='D')
                                {
                                    movep_right(lastA,rows_A,cols_A);
                                }
                                else if( move_pacman == 'a' || move_pacman =='A')
                                {
                                    movep_left(lastA,rows_A,cols_A);
                                        
                                }
                                else if( move_pacman == 27)
                                {
                                    player1.LastGame = 0;
                                    system("cls");
                                    player1.lastmapname = 'A';
                                    store_map_A(lastA, rows_A, cols_A);
                                    printf( BOLD_MAG "you will leave the game in a few seconds...");
                                    Sleep(2345);
                                    break;
                                }
                                system("cls");
                                move_G1(lastA,rows_A,cols_A);
                                printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                                show_matrix(lastA,rows_A,cols_A);
                                printf( BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_A(lastA,rows_A,cols_A));
                                if(GameOver(lastA,rows_A,cols_A) == 0)
                                {
                                    printf( BHRED "GAME OVER!" RESET);
                                    player1.level = player1.level - 1;
                                    player1.LastGame = 1;
                                    player1.lastmapname = 0;
                                    Sleep(500);
                                    break;
                                }
                                else if( GameWon(lastA,rows_A,cols_A) == 0)
                                {
                                    printf( BOLD_MAG "YOU WON!" RESET);
                                    player1.level = player1.level + 3;
                                    player1.LastGame = 1;
                                    player1.lastmapname = 0;
                                    Sleep(500);
                                    break;
                                }
                            }
                            
                        }
                        else if(map_condition == 'B')
                        {
                            char ** lastB = open_file(last_B);
                            while(2)
                            {
                                printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                                show_matrix(lastB,rows_B,cols_B);
                                printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_B(lastB,rows_B,cols_B));
                                move_pacman = getch();
                                //system("cls");
                                if( move_pacman == 'w' || move_pacman =='W')
                                {
                                    movep_up(lastB,rows_B,cols_B);
                                }
                                else if( move_pacman == 's' || move_pacman =='S')
                                {
                                        movep_down(lastB,rows_B,cols_B);
                                }
                                else if( move_pacman == 'd' || move_pacman =='D')
                                {
                                    movep_right(lastB,rows_B,cols_B);
                                }
                                else if( move_pacman == 'a' || move_pacman =='A')
                                {
                                    movep_left(lastB,rows_B,cols_B);
                                        
                                }
                                else if( move_pacman == 27)
                                {
                                    player1.LastGame = 0;
                                    system("cls");
                                    player1.lastmapname = 'B';
                                    store_map_A(lastB, rows_B, cols_B);
                                    printf( BOLD_MAG "you will leave the game in a few seconds...");
                                    Sleep(2345);
                                    break;
                                }
                                system("cls");
                                move_G1(lastB,rows_B,cols_B);
                                move_G2(lastB,rows_B,cols_B);
                                printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                                show_matrix(lastB,rows_B,cols_B);
                                printf( BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_B(lastB,rows_B,cols_B));
                                if(GameOver(lastB,rows_B,cols_B) == 0)
                                {
                                    printf( BHRED "GAME OVER!" RESET);
                                    player1.level = player1.level - 1;
                                    player1.LastGame = 1;
                                    player1.lastmapname = 'F';
                                    Sleep(500);
                                    break;
                                }
                                else if( GameWon(lastB,rows_B,cols_B) == 0)
                                {
                                    printf( BOLD_MAG "YOU WON!" RESET);
                                    player1.level = player1.level + 3;
                                    player1.LastGame = 1;
                                    player1.lastmapname = 'F';
                                    Sleep(500);
                                    break;
                                }
                            
                            }
                        }
                        else if(map_condition == 'C')
                        {
                            char ** lastC = open_file(last_C);
                            
                            while(2)
                            {
                                printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                                show_matrix(lastC,rows_C,cols_C);
                                printf(BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_C(lastC,rows_C,cols_C));
                                move_pacman = getch();
                                if( move_pacman == 'w' || move_pacman =='W')
                                {
                                    movep_up(lastC,rows_C,cols_C);
                                }
                                else if( move_pacman == 's' || move_pacman =='S')
                                {
                                    movep_down(lastC,rows_C,cols_C);
                                }
                                else if( move_pacman == 'd' || move_pacman =='D')
                                {
                                    movep_right(lastC,rows_C,cols_C);
                                }
                                else if( move_pacman == 'a' || move_pacman =='A')
                                {
                                    movep_left(lastC,rows_C,cols_C);
                                        
                                }
                                else if( move_pacman == 27)
                                {
                                    player1.LastGame = 0;
                                    system("cls");
                                    player1.lastmapname = 'C';
                                    store_map_A(lastC, rows_C, cols_C);
                                    printf( BOLD_MAG "you will leave the game in a few seconds...");
                                    Sleep(2345);
                                    break;
                                }
                                system("cls");
                                move_G1(lastC,rows_C,cols_C);
                                move_G2(lastC,rows_C,cols_C);
                                printf(BOLD_MAG "\npress \e[1;91mEsc\e[1;95m to leave the current game\n\n" RESET);
                                show_matrix(lastC,rows_C,cols_C);
                                printf( BOLD_MAG "\nLEVEL : %d\t\t PILL : %d/1\n" RESET,player1.level, check_pill_C(lastC,rows_C,cols_C));
                                if(GameOver(lastC,rows_C,cols_C) == 0)
                                {
                                    printf( BHRED "GAME OVER!" RESET);
                                    player1.level = player1.level - 1;
                                    player1.LastGame = 1;
                                    player1.lastmapname = 'F';
                                    Sleep(500);
                                    break;
                                }
                                else if( GameWon(lastC,rows_C,cols_C) == 0)
                                {
                                    printf( BOLD_MAG "YOU WON!" RESET);
                                    player1.level = player1.level + 3;
                                    player1.LastGame = 1;
                                    player1.lastmapname = 'F';
                                    Sleep(500);
                                    break;
                                }
                            
                            }

                        }
                    }
                    stor_player_info(&player1);

                    Sleep(1500);
                    system("cls");
                    printf(BOLD_MAG "\npress 'E' to go back to the main menu:" RESET);
                    char back;
                    back = getch();
                    if(back == 'e' || back == 'E')
                    {
                        break;
                    }
                }
            }
            break;
            case 3:
            {
                while(4)
                {
                system("cls");
                show_user_info(player1);
                printf(BOLD_MAG "\n\npress 'E' to go back to main menu." RESET);
                char back_to_menu;
                back_to_menu = getch();
                if(back_to_menu == 'E' || back_to_menu == 'e')
                {
                    break;
                }
                }
                
                
            }
            break;
            case 4:
            {
                flag_leave = 1;
            }
            break;
            default:
            {
                printf(BOLD_MAG "PLEASE ENTER A VALID OPTION!" RESET);
                break;
            }
            break;
        }
        system("cls");
        if(flag_leave == 1)
        {
            break;
        }
    }
    
   return 0;
   
}
