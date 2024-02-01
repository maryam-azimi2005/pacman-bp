#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#define  BOLD_BLUE "\e[1;94m"
#define RESET "\033[0m"
#define BOLD_MAG "\e[1;95m"

typedef struct ghost{
    int ghost_i;
    int ghost_j;
}ghost_dir;
typedef struct pacman{
    int pacman_i;
    int pacman_j;
}pacman_dir;
void yellow (){
  printf("\033[1;33m");
}
void reset () {
  printf("\033[0m");
}
void blue(){
    printf("\e[0;36m");
}
void red()
{
    printf("\e[0;31m");
}
int ghost_counts(char ** map , int rows , int cols)
{
    int counter = 0;
    int i,j;
    for(i = 0 ; i < rows ; ++i)
    {
        for(j = 0 ; j < cols ; ++j)
        {
            if(map[i][j] == 'F')
            {
                counter ++;
            }
        }
    }
    return counter;
}

void rows_clos(char * filename , int * rows , int * cols)
{
    FILE * fptr;
    char **Matrix;
    fptr = fopen(filename,"r");
    if(fptr == NULL)
    {
        printf("the map file can't be opend");
    }
    int a, b;
    fscanf(fptr,"%d %d" , &a , &b);
    *rows = a;
    *cols = b;
}
char ** open_file(char * filename)
{
    FILE * fptr;
    char **Matrix;
    fptr = fopen(filename,"r");
    if(fptr == NULL)
    {
        printf("the map file can't be opend");
    }
    int rows, cols;
    fscanf(fptr,"%d %d" , &rows , &cols);
    fgetc(fptr);
    //printf("%d %d", rows, cols);
    Matrix = (char **)malloc(rows * sizeof(char*)); 
    //pointer to an array of [rows] pointers
    for (int i = 0; i < rows; ++i)
      Matrix[i] = (char *)malloc(cols * sizeof(char)); 
    //pointer to a single array with [columns] chars
    for (int i = 0; i < rows; ++i)
    {
        for ( int j = 0; j < cols ; ++j)
        {
            fscanf(fptr,"%c", &Matrix[i][j]);
            
        }
        fgetc(fptr);
    }
    fclose(fptr);
    return Matrix;
}
void show_matrix(char ** Matrix, int rows ,int cols)
{
    //SetConsoleOutputCP(65001);
    for (int i = 0; i < rows; i++)
    {
        for ( int j = 0; j < cols; j++)
        {
            if(Matrix[i][j] == '|' || Matrix[i][j] == '-')
            {
                blue();
                printf("\u2588");
                printf("\u2588");
                reset();
            }
            else if(Matrix[i][j] == '@')
            {
                yellow();
                printf("\U0001F438");
                reset();

            }
            else if(Matrix[i][j] == '.')
            {
                printf("  ");
            }
            else if(Matrix[i][j] == 'P')
            {
                red();
                printf("\U0001F34E");
                reset();
            }
            else if(Matrix[i][j] == 'F')
            {
                printf("\U0001F47B");
            }
        }
        printf("\n");
    }
}
void movep_right(char ** matrix,int rows, int cols)
{
    int i,j;
    for(i = 0 ; i < rows ; ++i)
    {
        for(j = 0 ; j < cols ; ++j)
        {
            if(matrix[i][j] == '@' && matrix[i][j+1] != '|' && matrix[i][j+1] != '-' && matrix[i][j+1] != 'F' )
            {
                matrix[i][j+1] = matrix[i][j];
                matrix[i][j] = '.';
                return;
            }
        }
    }
}
void movep_left(char ** matrix,int rows, int cols)
{
    int i,j;
    for(i = 0 ; i < rows ; ++i)
    {
        for(j = 0 ; j < cols ; ++j)
        {
            if(matrix[i][j] == '@' && matrix[i][j-1] != '|' && matrix[i][j-1] != '-' && matrix[i][j-1] != 'F' )
            {
                matrix[i][j-1] = matrix[i][j];
                matrix[i][j] = '.';
                return;
            }
        }
    }
}
void movep_up(char ** matrix,int rows, int cols)
{
    int i,j;
    for(i = 0 ; i < rows ; ++i)
    {
        for(j = 0 ; j < cols ; ++j)
        {
            if(matrix[i][j] == '@' && matrix[i-1][j] != '|' && matrix[i-1][j] != '-' && matrix[i-1][j] != 'F' )
            {
                matrix[i-1][j] = matrix[i][j];
                matrix[i][j] = '.';
                return;
            }
        }
    }
}
void movep_down(char ** matrix,int rows, int cols)
{
    int i,j;
    for(i = 0 ; i < rows ; ++i)
    {
        for(j = 0 ; j < cols ; ++j)
        {
            if(matrix[i][j] == '@' && i != rows-2 && matrix[i+1][j] != '|' && matrix[i+1][j] != '-' && matrix[i+1][j] != 'F' )
            {
                matrix[i+1][j] = matrix[i][j];
                matrix[i][j] = '.';
                return;
            }
        }
    }
}
void change_first_ghost(char ** matrix,int rows,int cols)
{
    int i,j;
    for(i = 0 ; i < rows ; ++i )
    {
        for( j = 0 ; j < cols ; j++)
        {
            if(matrix[i][j] == 'F')
            {
                matrix[i][j] = 'G';
                break;
            }
        }
    }
}
int main()
{
   SetConsoleOutputCP(65001);
   char mapA[10] = "mapA.txt";
   char mapB[10] = "mapB.txt";
   char mapC[10] = "mapC.txt";
   int rows_A, cols_A, rows_B, cols_B, rows_C, cols_C;
   printf(BOLD_BLUE "WELCOME TO THE PAC-MAN GAME \U0001F60D" RESET);
   Sleep(2000);
   system("cls");
   printf(BOLD_MAG "How would you like the new game to start for you?\n1.randomly\n2.show all the maps\n" RESET);
   int first_choice;
   scanf("%d",&first_choice);
   system("cls");
   
   char map_choice;

   int flag_for_map_choice = 0;
   char ** map_A = open_file(mapA);
   //change_first_ghost(map_A,rows_A,cols_A);
   char ** map_B = open_file(mapB);
   //change_first_ghost(map_B,rows_B,cols_B);
   char ** map_C = open_file(mapC);
   //change_first_ghost(map_C,rows_C,cols_C);
    if(first_choice == 2)
   {
        printf("map A:\n\n");
        rows_clos(mapA,&rows_A,&cols_A);
        show_matrix(map_A,rows_A,cols_A);
       
        printf("\n-----------------------------------------\n");
        printf("map B:\n\n");
        rows_clos(mapB,&rows_B,&cols_B);
        show_matrix(map_B,rows_B,cols_B);
        printf("\n-----------------------------------------\n");

        printf("map C:\n\n");
        rows_clos(mapC,&rows_C,&cols_C);
        show_matrix(map_C,rows_C,cols_C);
        printf("\n-----------------------------------------\n");
        flag_for_map_choice = 1;
        
   }
    else if(first_choice == 1)
    {
        char move_pacman1;
        int x;
        x = rand() % 3;
        if( x == 0)
        {
        show_matrix(map_A,rows_A,cols_A);
        while(1)
        {
            scanf("%c",&move_pacman1);
            if( move_pacman1 == 'w' || move_pacman1 =='W')
            {
                system("cls");
                movep_up(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
            else if( move_pacman1 == 's' || move_pacman1 =='S')
            {
                system("cls");
                movep_down(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
            else if( move_pacman1 == 'd' || move_pacman1 =='D')
            {
                system("cls");
                movep_right(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
            else if( move_pacman1 == 'a' || move_pacman1 =='A')
            {
                system("cls");
                movep_left(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
        }
        }
        else if( x == 1)
        {
        show_matrix(map_B,rows_B,cols_B);
        while(1)
        {
            scanf("%c",&move_pacman1);
            if( move_pacman1 == 'w' || move_pacman1 =='W')
            {
                system("cls");
                movep_up(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
            else if( move_pacman1 == 's' || move_pacman1 =='S')
            {
                system("cls");
                movep_down(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
            else if( move_pacman1 == 'd' || move_pacman1 =='D')
            {
                system("cls");
                movep_right(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
            else if( move_pacman1 == 'a' || move_pacman1 =='A')
            {
                system("cls");
                movep_left(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
        }
        }
        else if ( x == 2)
        {
        show_matrix(map_C,rows_C,cols_C);
        while(1)
        {
            scanf("%c",&move_pacman1);
            if( move_pacman1 == 'w' || move_pacman1 =='W')
            {
                system("cls");
                movep_up(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
            else if( move_pacman1 == 's' || move_pacman1 =='S')
            {
                system("cls");
                movep_down(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
            else if( move_pacman1 == 'd' || move_pacman1 =='D')
            {
                system("cls");
                movep_right(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
            else if( move_pacman1 == 'a' || move_pacman1 =='A')
            {
                system("cls");
                movep_left(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
        }
        }
    }
   

   if(flag_for_map_choice)
   {
    printf(BOLD_MAG "\nWhich one do you like?\nPlease enter the map name(A,B,C):" RESET);
    scanf(" %c",&map_choice);
    
    char move_pacman;
    if(map_choice == 'A' || map_choice == 'a')
    {
        show_matrix(map_A,rows_A,cols_A);
        while(1)
        {
            scanf("%c",&move_pacman);
            if( move_pacman == 'w' || move_pacman =='W')
            {
                system("cls");
                movep_up(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
            else if( move_pacman == 's' || move_pacman =='S')
            {
                system("cls");
                movep_down(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
            else if( move_pacman == 'd' || move_pacman =='D')
            {
                system("cls");
                movep_right(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
            else if( move_pacman == 'a' || move_pacman =='A')
            {
                system("cls");
                movep_left(map_A,rows_A,cols_A);
                show_matrix(map_A,rows_A,cols_A);
            }
        }
    }
    else if(map_choice == 'B' || map_choice == 'b')
    {
        show_matrix(map_B,rows_B,cols_B);
        while(1)
        {
            scanf("%c",&move_pacman);
            if( move_pacman == 'w' || move_pacman =='W')
            {
                system("cls");
                movep_up(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
            else if( move_pacman == 's' || move_pacman =='S')
            {
                system("cls");
                movep_down(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
            else if( move_pacman == 'd' || move_pacman =='D')
            {
                system("cls");
                movep_right(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
            else if( move_pacman == 'a' || move_pacman =='A')
            {
                system("cls");
                movep_left(map_B,rows_B,cols_B);
                show_matrix(map_B,rows_B,cols_B);
            }
        }
    }
    else if( map_choice == 'C' || map_choice == 'c')
    {
        show_matrix(map_C,rows_C,cols_C);
        while(1)
        {
            scanf("%c",&move_pacman);
            if( move_pacman == 'w' || move_pacman =='W')
            {
                system("cls");
                movep_up(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
            else if( move_pacman == 's' || move_pacman =='S')
            {
                system("cls");
                movep_down(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
            else if( move_pacman == 'd' || move_pacman =='D')
            {
                system("cls");
                movep_right(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
            else if( move_pacman == 'a' || move_pacman =='A')
            {
                system("cls");
                movep_left(map_C,rows_C,cols_C);
                show_matrix(map_C,rows_C,cols_C);
            }
        }
    }

   }
  
   
   
}