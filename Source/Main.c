#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


//Youssef Ahmed AbdelHafez  20180337
//Khaled Samir              20180095

#define THREADS 3

int main(int argc, char *argv[])
{

    int i,j;
    int id;
    int rows=0,columns=0;


    printf("Enter the Number of Rows:");
    scanf("%d",&rows);
    printf("Enter the Number of Columns:");
    scanf("%d",&columns);

    char** matrix =(char**) malloc (rows * sizeof (char*));

    for ( i = 0; i < rows; i++ )
    {
        matrix[i] = (char*) malloc (columns * sizeof (char));
    }

    printf("The Matrix:\n");
    for(i =0;i<rows;i++) {
        for (j = 0; j < columns; j++) {
            scanf(" %c",&matrix[i][j]);
        }
    }

    printf("\n");
    
    #pragma omp parallel num_threads(THREADS) shared(matrix,rows,columns) private(i,j)
    {
        id = omp_get_thread_num();
        #pragma omp for schedule(static)
        for (i = 0; i < rows; i++) {
            for (j = 1; j <= columns - 1; j++) {
                if (matrix[i][j - 1] == 'X' && matrix[i][j + 1] == 'X') {
                    matrix[i][j] = 'X';
                }
            }
            printf("Row (%d) computed on thread %d: ",i,id);
            for(j =0;j<columns;j++){
                printf("%c ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    printf("\nSolution: \n");
    for(i =0 ;i<rows;i++){
        for(j =0;j<columns;j++){
          printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }


}
