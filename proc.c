#include "proc.h"



void rows_clos(char * filename , int * rows , int * cols)
{
    FILE * fptr;
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
}// az fgetc baraye new line ha estefade kardam
void show_all_maps(char **map_A, int rows_A, int cols_A , char **map_B, int rows_B, int cols_B , char **map_C, int rows_C, int cols_C)
{
    printf(BOLD_MAG "select a map for the new game :D\n\n" RESET);
    printf("map A:\n\n");
    show_matrix(map_A,rows_A,cols_A);
    printf("\n-----------------------------------------\n");
    printf("map B:\n\n");
    show_matrix(map_B,rows_B,cols_B);
    printf("\n-----------------------------------------\n");
    printf("map C:\n\n");
    show_matrix(map_C,rows_C,cols_C);
    printf("\n-----------------------------------------\n");
    printf(BOLD_MAG "\nWhich one do you like?\nPlease enter the map name(A,B,C):" RESET);
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
                printf(BLU);
                printf("\u2588");
                printf("\u2588");
                printf(RESET);
            }
            else if(Matrix[i][j] == '@')
            {
                printf("\U0001F438");
            }
            else if(Matrix[i][j] == '.')
            {
                printf("  ");
            }
            else if(Matrix[i][j] == 'P')
            {
                printf("\U0001F34E");
            }
            else if(Matrix[i][j] == 'F' || Matrix[i][j] == 'G')
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
            if(matrix[i][j] == '@' && matrix[i][j+1] != '|' && matrix[i][j+1] != '-' && matrix[i][j+1] != 'F' && matrix[i][j+1] != 'G' )
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
            if(matrix[i][j] == '@' && matrix[i][j-1] != '|' && matrix[i][j-1] != '-' && matrix[i][j-1] != 'F' && matrix[i][j-1] != 'G'  )
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
            if(matrix[i][j] == '@' && matrix[i-1][j] != '|' && matrix[i-1][j] != '-' && matrix[i-1][j] != 'F' && matrix[i-1][j] != 'G' )
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
            if(matrix[i][j] == '@' && i != rows-2 && matrix[i+1][j] != '|' && matrix[i+1][j] != '-' && matrix[i+1][j] != 'F'&& matrix[i+1][j] != 'G' )
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
                return;
            }
        }
    }
}
void move_G1(char ** matrix, int rows, int cols)
{
    int tmp_rows,tmp_cols,z,i,j;
    char ** tmp_matrix;
    tmp_matrix = matrix;
    tmp_rows = rows;
    tmp_cols = cols;

    z = rand()%4;
    if(z == 0)
    {
       for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'G' && matrix[i-1][j] != '|' && matrix[i-1][j] != '-' && matrix[i-1][j] != 'F')
                {
                    if(matrix[i-1][j] == '|' || matrix[i-1][j] == '-' || matrix[i-1][j] == 'F')
                    {
                        move_G1(tmp_matrix,tmp_rows,tmp_cols);
                    }
                    else
                    {
                    matrix[i-1][j] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        } 
    }
    else if(z == 1)
    {     
        for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'G'  && matrix[i+1][j] != '|' && matrix[i+1][j] != '-' && matrix[i+1][j] != 'F' )
                {
                    if(matrix[i+1][j] == '|' || matrix[i+1][j] == '-' || matrix[i+1][j] == 'F')
                    {
                       move_G1(tmp_matrix,tmp_rows,tmp_cols); 
                    }
                    else
                    {
                    matrix[i+1][j] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        }
    }
    else if(z == 2)
    {
        for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'G' && matrix[i][j-1] != '|' && matrix[i][j-1] != '-' && matrix[i][j-1] != 'F' )
                {
                    if(matrix[i][j-1] == '|' || matrix[i][j-1] == '-' || matrix[i][j-1] == 'F')
                    {
                        move_G1(tmp_matrix,tmp_rows,tmp_cols);
                    }
                    else
                    {
                    matrix[i][j-1] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        }
    }
    else if(z == 3)
    {
        for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'G' && matrix[i][j+1] != '|' && matrix[i][j+1] != '-' && matrix[i][j+1] != 'F' )
                {
                    if(matrix[i][j+1] == '|' || matrix[i][j+1] == '-' || matrix[i][j+1] != 'F')
                    {
                        move_G1(tmp_matrix,tmp_rows,tmp_cols);
                    }
                    else{
                    matrix[i][j+1] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        }
    }
}
void move_G2(char ** matrix, int rows, int cols)
{
    int tmp_rows,tmp_cols,z,i,j;
    char ** tmp_matrix;
    tmp_matrix = matrix;
    tmp_rows = rows;
    tmp_cols = cols;

    z = rand()%4;
    if(z == 0)
    {
       for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'F' && matrix[i-1][j] != '|' && matrix[i-1][j] != '-' && matrix[i-1][j] != 'G')
                {
                    if(matrix[i-1][j] == '|' || matrix[i-1][j] == '-' || matrix[i-1][j] == 'G')
                    {
                        move_G1(tmp_matrix,tmp_rows,tmp_cols);
                    }
                    else
                    {
                    matrix[i-1][j] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        } 
    }
    else if(z == 1)
    {     
        for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'F'  && matrix[i+1][j] != '|' && matrix[i+1][j] != '-' && matrix[i+1][j] != 'G' )
                {
                    if(matrix[i+1][j] == '|' || matrix[i+1][j] == '-' || matrix[i+1][j] == 'G')
                    {
                       move_G1(tmp_matrix,tmp_rows,tmp_cols); 
                    }
                    else
                    {
                    matrix[i+1][j] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        }
    }
    else if(z == 2)
    {
        for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'F' && matrix[i][j-1] != '|' && matrix[i][j-1] != '-' && matrix[i][j-1] != 'G' )
                {
                    if(matrix[i][j-1] == '|' || matrix[i][j-1] == '-' || matrix[i][j-1] == 'G')
                    {
                        move_G1(tmp_matrix,tmp_rows,tmp_cols);
                    }
                    else
                    {
                    matrix[i][j-1] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        }
    }
    else if(z == 3)
    {
        for(i = 0 ; i < rows ; ++i)
        {
            for(j = 0 ; j < cols ; ++j)
            {
                if(matrix[i][j] == 'F' && matrix[i][j+1] != '|' && matrix[i][j+1] != '-' && matrix[i][j+1] != 'G' )
                {
                    if(matrix[i][j+1] == '|' || matrix[i][j+1] == '-' || matrix[i][j+1] != 'G')
                    {
                        move_G2(tmp_matrix,tmp_rows,tmp_cols);
                    }
                    else{
                    matrix[i][j+1] = matrix[i][j];
                    matrix[i][j] = '.';
                    return;
                    }
                }
            }
        }
    }
}
int GameOver(char ** matrix,int rows,int cols)
{
    int i,j;
    for( i = 0 ; i < rows ; ++i)
    {
        for( j = 0 ; j < cols ; ++j)
        {
            if (matrix[i][j] == '@')
            {
                return 1;
            }
        }
    }
    return 0;
}
int GameWon(char ** matrix, int rows, int cols)
{
    int i,j;
    for( i = 0 ; i < rows ; ++i)
    {
        for( j = 0 ; j < cols ; ++j)
        {
            if(matrix[i][j] == 'P')
            {
                return 1;
            }
        }
    }
    return 0;
}
int check_pill_A(char ** matrix,int rows,int cols)
{
    int i, j, counter = 0;
    for( i = 0 ; i < rows ; i++)
    {
        for( j = 0 ; j < cols ; j++)
        {
            if(matrix[i][j] == 'P')
            {
                ++counter;
            }
        }
    }
    return 1 - counter;
}
int check_pill_B(char ** matrix,int rows,int cols)
{
    int i, j, counter = 0;
    for( i = 0 ; i < rows ; i++)
    {
        for( j = 0 ; j < cols ; j++)
        {
            if(matrix[i][j] == 'P')
            {
                ++counter;
            }
        }
    }
    return 2 - counter;
}
int check_pill_C(char ** matrix,int rows,int cols)
{
    int i, j, counter = 0;
    for( i = 0 ; i < rows ; i++)
    {
        for( j = 0 ; j < cols ; j++)
        {
            if(matrix[i][j] == 'P')
            {
                ++counter;
            }
        }
    }
    return 3 - counter;
}
void stor_player_info(struct player * player1)
{
    FILE *fptr1;
    fptr1 = fopen("playerinfo.bin","wb");
    if(fptr1 != NULL)
    {
        fwrite(player1,sizeof(struct player),1,fptr1);
    }
    fclose(fptr1);

}
void load_player_info(struct player * player1)
{
    FILE *fptr1;
    fptr1 = fopen("playerinfo.bin","rb");
    if(fptr1 != NULL)
    {
        fread(player1,sizeof(struct player),1,fptr1);
        fclose(fptr1);
    }
    else 
        printf(BOLD_MAG "PLAYER INFO FILE CAN NOT BE OPEND" RESET);

}
void show_user_info(struct player player1)
{
    printf(BOLD_MAG "username : %s\n" RESET,player1.name);
    printf(BOLD_MAG "id : %d\n" RESET, player1.id);
    printf(BOLD_MAG "level : %d\n"RESET,player1.level);
    if(player1.LastGame == 1)
    {
        printf(BOLD_MAG "This user has no uncomplete game.\n" RESET);
    }
}
void store_map_A(char ** matrix,int rows,int cols)
{
    int i, j;
    FILE * fptr;
    fptr = fopen("storedmapA.txt", "w");
    fprintf(fptr,"%d %d\n", rows, cols);
    for( i = 0 ; i < rows ; ++i )
    {
        for ( j = 0 ; j < cols ; ++j)
        {
            fprintf(fptr, "%c", matrix[i][j]);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}
void store_map_B(char ** matrix,int rows,int cols)
{
    int i, j;
    FILE * fptr;
    fptr = fopen("storedmapB.txt", "w");
    fprintf(fptr,"%d %d\n", rows, cols);
    for( i = 0 ; i < rows ; ++i )
    {
        for ( j = 0 ; j < cols ; ++j)
        {
            fprintf(fptr, "%c", matrix[i][j]);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}
void store_map_C(char ** matrix,int rows,int cols)
{
    int i, j;
    FILE * fptr;
    fptr = fopen("storedmapC.txt", "w");
    fprintf(fptr,"%d %d\n", rows, cols);
    for( i = 0 ; i < rows ; ++i )
    {
        for ( j = 0 ; j < cols ; ++j)
        {
            fprintf(fptr, "%c", matrix[i][j]);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}
