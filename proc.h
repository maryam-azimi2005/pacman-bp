
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#define  BOLD_BLUE "\e[1;94m"
#define RESET "\033[0m"
#define BOLD_MAG "\e[1;95m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BLU "\e[0;36m"
#ifndef MYPACMAN_H
#define MYPACMAN_H
struct player{
    char name[30];
    int id;
    int level;
    int LastGame; //if (LastGame == 0) means the player has no unfinished game and if (LastGame == 1) means that the player has an unfinished game
    char lastmapname; // A for mapA, B for mapB, C for mapC and F means the player has no unfinshed game.
}player; 


void rows_clos(char * filename , int * rows , int * cols);//input: a file name and two pointers to integer
//description: this function opens a map file and stores the number of columns and rows of the matrix.

char ** open_file(char * filename);//input:a filename
//description: it reads from a map file and allocates a 2d char array(matrix) to store the map.
//output: a matrix of character.

void show_all_maps(char **map_A, int rows_A, int cols_A , char **map_B, int rows_B, int cols_B , char **map_C, int rows_C, int cols_C);

void show_matrix(char ** Matrix, int rows ,int cols);//input:a map(matrix) and the value of its columns and rows.
//description: to use unicodes for beautification the map. for each character ( . , | , - , @ , P , F , G) prints a special unicode.

void movep_right(char ** matrix,int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find '@' character, change the locatin of that(increase x).

void movep_left(char ** matrix,int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find '@' character, change the locatin of that(decrease x).

void movep_up(char ** matrix,int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find '@' character, change the locatin of that(decrease y).

void movep_down(char ** matrix,int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find '@' character, change the locatin of that(increase y).

void change_first_ghost(char ** matrix,int rows,int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find 'F' change it to 'G' and return.

void move_G1(char ** matrix, int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find 'G' randomly change its locatin.

void move_G2(char ** matrix, int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix and when it find 'F' randomly change its locatin.

int GameOver(char ** matrix,int rows,int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix looking for '@' (pacman) if it didn't find '@' means that game is over.
//

int GameWon(char ** matrix, int rows, int cols);//input:a map(matrix) and the value of its columns and rows.
//description: It traves in map matrix looking for 'P' (Pill) if it didn't find 'P' means that the player won.

int check_pill_A(char ** matrix,int rows,int cols);//input:a map(matrix) and the value of its columns and rows.

int check_pill_B(char ** matrix,int rows,int cols);//input:a map(matrix) and the value of its columns and rows.

int check_pill_C(char ** matrix,int rows,int cols);//input:a map(matrix) and the value of its columns and rows.

void stor_player_info(struct player * player1);
void load_player_info(struct player * player1);
void show_user_info(struct player player1);
void store_map_A(char ** matrix,int rows,int cols);
void store_map_B(char ** matrix,int rows,int cols);
void store_map_C(char ** matrix,int rows,int cols);
#endif