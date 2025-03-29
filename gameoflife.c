#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    This method counts the number of alive neighbours taking into consideration 
    if the cell is placed on the edge of the matrix

    Parameters: the matrix, the row of the cell, the column of the cell,
    number of rows, number of columns 
*/
int nr_vecini_vii(char** matr, int i, int j, int m, int n) {
    int vii=0;

    if(i>0 && j>0 && matr[i-1][j-1]=='X') {
        vii++;
    }

    if(i>0 && matr[i-1][j]=='X') {
        vii++;
    }
    
    if(i>0 && j<n-1 && matr[i-1][j+1]=='X') {
        vii++;
    }

    if(j<n-1 && matr[i][j+1]=='X') {
        vii++;
    }

    if(i<m-1 && j<n-1 && matr[i+1][j+1]=='X') {
        vii++;
    }

    if(i<m-1 && matr[i+1][j]=='X') {
        vii++;
    }

    if(i<m-1 && j>0 && matr[i+1][j-1]=='X') {
        vii++;
    }

    if(j>0 && matr[i][j-1]=='X') {
        vii++;
    }

    return vii;
}

/*
    Implementation of task 1: print the first n generations of the game matrix
    which was read from the input file

    Parameters: the matrix, number of rows, number of columns, 
    number of game generations, output file name
*/
void task1(char** matr, int m, int n, int gen, const char *fisierout) {
    // Matrix for the next generation
    char** genUrm = (char**)malloc(m*sizeof(char*));
    for(int k=0; k<m; k++) {
        genUrm[k] = (char*)calloc(n, sizeof(char));
    }

    FILE* output = fopen(fisierout, "w");
    if(output==NULL) {
        printf("Eroare la crearea fisierului");
        exit(1);
    }

    // Print the original matrix in the output file
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            fprintf(output, "%c", matr[i][j]);
        }
        fprintf(output, "\n");
    }
    fprintf(output, "\n");

    // Iterate through the specified number of generations
    for(int g=0; g<gen; g++) { 
        for(int i=0; i<m; i++) { 
            for(int j=0; j<n; j++) {
                int vii = nr_vecini_vii(matr, i, j, m, n); 
                // Update the status of the current cell based on its alive neighbours
                if(matr[i][j]=='X') {
                    if(vii<2 || vii>3) { 
                        // The cell dies
                        genUrm[i][j]='+';
                    } else {
                        // The cell keeps living
                        genUrm[i][j]='X'; 
                    } 
                } else {
                    if(vii==3) {
                        // The cell is reborn 
                        genUrm[i][j]='X';
                    } else {
                        // The cell stays dead
                        genUrm[i][j]='+'; 
                    }
                }
            }  
        }
        // Print the next generation matrix in the output file
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                fprintf(output, "%c", genUrm[i][j]);
            }
            fprintf(output, "\n");
        }
        fprintf(output, "\n");

        // The next generation becomes the current one for the next iteration
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                matr[i][j] = genUrm[i][j];
            }
        }
    }
    fclose(output);

    for(int k=0; k<m; k++) {
        free(genUrm[k]);
    }
    free(genUrm);
}

int main(int argc, char* argv[]) {
    FILE* tema = fopen(argv[1], "rt");

    if(tema==NULL) {
        printf("Fisierul de input nu a putut fi accesat");
        exit(1);
    }

    // Read all input file values
    int task, m, n, gen;
    fscanf(tema, "%d", &task); 
    fscanf(tema, "%d %d", &m, &n);
    fscanf(tema, "%d", &gen);

    char** matr = (char**)malloc(m*sizeof(char*));
    for(int k=0; k<m; k++) {
        matr[k] = (char*)calloc(n, sizeof(char));
    }

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            do {
                fscanf(tema, "%c", &matr[i][j]);
            } while(matr[i][j]=='\n' || matr[i][j]=='\r');
        }
    } 

    fclose(tema);

    // Switch for the task number argument
    switch(task) {
        case 1: 
            task1(matr, m, n, gen,argv[2]);
            break;
    }

    for(int k=0; k<m; k++) {
        free(matr[k]);
    }
    free(matr);

    return 0;
}