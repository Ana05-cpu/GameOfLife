#include "gol.h"


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
        case 2:
            task2(matr, m, n, gen, argv[2]);
            break;
        case 3:
            task3(matr, m, n, gen, argv[2]);
            break;
        case 4:
            task4(matr, m, n, gen, argv[2]);
            break;
    }

    for(int k=0; k<m; k++) {
        free(matr[k]);
    }
    free(matr);

    return 0;

    // Final update before submission, looked for memory leaks, not found
}