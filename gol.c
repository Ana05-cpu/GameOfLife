#include "gol.h"


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



void task2(char** matr, int m, int n, int gen, const char *fisierout) {
    // Matrix for the next generation
    char** genUrm = (char**)malloc(m*sizeof(char*));
    for(int k=0; k<m; k++) {
        genUrm[k] = (char*)calloc(n, sizeof(char));
    }

    Stack* top = NULL;
    Node* head;
    Coord coord;
    for(int g=0; g<gen; g++) {
        head = NULL;
        for(int i=0; i<m; i++) { 
            for(int j=0; j<n; j++) {
                int vii = nr_vecini_vii(matr, i, j, m, n); 
                 if(matr[i][j]=='X') {
                    if(vii<2 || vii>3) { 
                        // The cell dies
                        genUrm[i][j]='+';
                        coord.l = i;
                        coord.c = j;
                        add(&head, coord);
                    } else {
                        // The cell keeps living
                        genUrm[i][j]='X'; 
                    } 
                } else {
                    if(vii==3) {
                        // The cell is reborn 
                        genUrm[i][j]='X';
                        coord.l = i;
                        coord.c = j;
                        add(&head, coord);
                    } else {
                        // The cell stays dead
                        genUrm[i][j]='+'; 
                    }
                }
            }
        }
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                matr[i][j] = genUrm[i][j];
            }
        }
        // Push generation list in stack
        push(&top, head, g+1);
    }

    FILE* output = fopen(fisierout, "w");
    if(output==NULL) {
        printf("Eroare la crearea fisierului");
        exit(1);
    }

    /* Create two inverted copies of the original stack, first for writing in the output file
        and second for bonus task implementation*/

    Stack* aux = NULL;
    while(top != NULL) {
        push(&aux, pop(&top), top->gen);
    }
    printStack(aux, output);
    fclose(output);

    char fisier[50];
    strcpy(fisier, fisierout);
    strcat(fisier, ".bonus.in");

    FILE* bonusInput = fopen(fisier, "w");
    if(bonusInput == NULL) {
        printf("Eroare deschidere fisier bonus input");
    }

    printStack(aux, bonusInput);

    // Free the copies
    while(aux != NULL) {
        pop(&aux);
    }

    fprintf(bonusInput, "\n");

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            fprintf(bonusInput, "%c", genUrm[i][j]);
        }
        fprintf(bonusInput, "\n");
    }

    fclose(bonusInput);

    for(int k=0; k<m; k++) {
        free(genUrm[k]);
    }
    free(genUrm);

    //BONUS
    BONUS(fisier, fisierout);
    //BONUS

}

// Method for adding a node in the list, which represents an element in the stack
void add(Node** head, Coord val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = NULL;

    if(*head == NULL){
        *head = newNode;
    } else {
        Node* aux = *head;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

void push(Stack** top, Node* v, int gen) {
    Stack* newElem= (Stack*)malloc(sizeof(Stack));
    newElem->val = v;
    newElem->next = *top;
    newElem->gen = gen;
    *top = newElem;
}

// Print the whole stack, iterating over the list elements and their contents
void printStack(Stack* stackTop, FILE* fisierout) {
    Stack* aux = stackTop;

    while(aux) {
        fprintf(fisierout, "%d", aux->gen);
        printList(aux->val, fisierout);      
        aux = aux->next;
    }
}

void printList(Node* head, FILE* fisierout) {
    Node* aux = head;

    while(aux != NULL) {
        fprintf(fisierout, " %d %d",  aux->val.l, aux->val.c);
        aux = aux->next;
    }
    fprintf(fisierout, "\n");
}

Node* pop(Stack** top) {
    Stack *temp = (*top);
    Node* aux = temp->val;
    *top = (*top)->next;
    freeNode(temp->val);
    free(temp);

    return aux;
}

void freeNode(Node* head) {
    while(head!=NULL) {
        Node* aux = head;
        head = head->next;
        free(aux);
    }
}

// Work in progress for bonus task =)

void BONUS(const char* file, const char* fisierout) {
    FILE* inputBonus = fopen(file, "r");
    if(inputBonus == NULL) {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }

    int m = 0, n = 0;
    Stack* top = NULL;
    Coord coord;
    Node* head = NULL;
    char linie[300];
    int endOfStack = 0;
    while(fgets(linie, sizeof(linie), inputBonus) != NULL){
        if(strcmp(linie, "\n") == 0) {
            endOfStack = 1;
            continue;
        } 
        if(endOfStack == 0) {
            char const* token = strtok(linie, " ");
            if(token!=NULL) {
                int gen = atoi(token);
                head = NULL;
                int count = 2;
                token = strtok(NULL, " ");
                while(token != NULL) {
                    if(count == 2) {
                        coord.l = atoi(token);
                        count--;
                    } else if(count == 1) {
                        coord.c = atoi(token);
                        count = 2;
                        add(&head, coord);
                    }
                    token = strtok(NULL, " ");
                }
                push(&top, head, gen);
            }  
        } else {
            while(fgets(linie, sizeof(linie), inputBonus) != NULL) {
                if(m == 0) {
                    for(int i = 0; i<strlen(linie); i++) {
                        if(linie[i] != '\n') n++;
                    }
                }
                m++;
            }
            break;
        }
    }

    fclose(inputBonus);

    char** lastGen = (char**)malloc(m*sizeof(char*));
    for(int k=0; k<m; k++) {
        lastGen[k] = (char*)calloc(n, sizeof(char));
    }

    inputBonus = fopen(file, "r");

    while(fgets(linie, sizeof(linie), inputBonus) != NULL){
        if(strcmp(linie, "\n") == 0) {
            break;
        }
    } 
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            do {
                fscanf(inputBonus, "%c", &lastGen[i][j]);
            } while(lastGen[i][j]=='\n' || lastGen[i][j]=='\r');
        } 
    }
    fclose(inputBonus);
    // remove(file);

    writeBonusFile(top, lastGen, m, n, fisierout);
}

//  Implementing the bonus task, recreating the original matrix, 
//     starting from the last generation matrix and the stack of changes

void writeBonusFile(Stack* top, char** lastGen, int m, int n, const char* fisierout) {
    // Apply changes only to the relevant cells
    while(top != NULL) {
        Node* currCoord = pop(&top);
        Node* temp = currCoord; 
        while(temp!=NULL) {
            Coord coords = temp->val;
            if(lastGen[coords.l][coords.c] == '+') {
                lastGen[coords.l][coords.c] = 'X';
            } else {
                lastGen[coords.l][coords.c] = '+';
            }
            temp = temp->next;
        }
    }

    // Create a new output file with the extension ".out.bonus.out" for each test file, 
    //    which contains the original matrix 
    char fisier[50];
    strcpy(fisier, fisierout);
    strcat(fisier, ".bonus.out");

    FILE* output = fopen(fisier, "w");
    if(output == NULL) {
        printf("Eroare");
        exit(1);
    }

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            fprintf(output, "%c", lastGen[i][j]);
        }
        fprintf(output, "\n");
    }
    fclose(output);
}

Tree* createTreeNode(Node* head) {
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->val = head;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* Implementation of the new rule, that revives dead cells that have exactly
 2 alive neighbours */
Node* newRule(char** matr, int m, int n) {
    Node* head = NULL;
    Coord coord;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            int vii = nr_vecini_vii(matr, i, j, m, n);
            if(matr[i][j] == '+' && vii == 2) {
                coord.l = i;
                coord.c = j;
                add(&head, coord);
            }
        }
    }
    return head;
}

// Standard Game of life rules
Node* oldRule(char** matr, int m, int n) {
    Node* head = NULL;
    Coord coord;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            int vii = nr_vecini_vii(matr, i, j, m, n);
            if(matr[i][j] == 'X') {
                if(vii < 2 || vii > 3) {
                    coord.l = i;
                    coord.c = j;
                    add(&head, coord);
                } 
            } else {
                if(vii == 3) {
                    coord.l = i;
                    coord.c = j;
                    add(&head, coord);
                }
            }
        }
    }
    return head;
}

// Updates the matrix based on the list of coordinates
void nextGenMatr(char** matr, Node* head) {
    Node* curr = head;
    while(curr != NULL) {
        Coord coord = curr->val;
        if(matr[coord.l][coord.c] == '+') {
            matr[coord.l][coord.c] = 'X';
        } else matr[coord.l][coord.c] = '+';
        curr = curr->next;
    }
}

char** copyMatr(char** matr, int m, int n) {
    char** copy = (char**)malloc(m*sizeof(char*));
    for(int i=0; i<m; i++) {
        copy[i] = (char*)calloc(n, sizeof(char));
    }

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            copy[i][j] = matr[i][j];
        }
    }
    return copy;
}

Tree* createTree(char** matr, int m, int n, int g, int gen) {
    Tree* root = createTreeNode(NULL);

    if(g == gen) return root; 

    Node* head = NULL;
    if(g == 0) {
        // For the first gen, creates the list with all the cells that are alive
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {  
                if(matr[i][j] == 'X') {
                    Coord coord;  
                    coord.l = i;
                    coord.c = j;
                    add(&head, coord);
                }
            }
        }
        root->val = head;
    }

    /* Make a copy of the current matrix; 
       Creates the coordinates list based on the new rule;
       Uses the list to generate the next generation matrix;
       Asigns the list to the left child of the current node
       Calls the recursive method over the left child to continue the process, then it asigns
         its children accordingly 
       Frees the matrix used by the left child */
    char** leftGen = copyMatr(matr, m, n);
    Node* leftHead = newRule(leftGen, m, n);
    nextGenMatr(leftGen, leftHead);
    root->left = createTreeNode(leftHead);
    Tree* leftChild = createTree(leftGen, m, n, g+1, gen);
    root->left->left = leftChild->left;
    root->left->right = leftChild->right;
    for(int k=0; k<m; k++) {
        free(leftGen[k]);
    }
    free(leftGen);
    free(leftChild); // not needed anymore left child because of whole subtree is already calculated

    // Same as the left child
    char** rightGen = copyMatr(matr, m, n);
    Node* rightHead = oldRule(rightGen, m, n);
    nextGenMatr(rightGen, rightHead);
    root->right = createTreeNode(rightHead);
    Tree* rightChild = createTree(rightGen, m, n, g+1, gen);
    root->right->left = rightChild->left;
    root->right->right = rightChild->right;
    for(int k=0; k<m; k++) {
        free(rightGen[k]);
    }
    free(rightGen);
    free(rightChild);

    return root;    
}

void printMatr(FILE* fisierout, char** matr, int m, int n) {
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) { 
            fprintf(fisierout, "%c", matr[i][j]);
        }
        fprintf(fisierout, "\n");
    }
    fprintf(fisierout, "\n");

}

/* Traverse the created tree in preorder and write to a file, for each node in the tree it 
 traverses, the corresponding matrix */
void preorder(FILE* fisierout, Tree* root, char** matr, int m, int n) {
    if (root) {
        nextGenMatr(matr, root->val);
        char** leftGen = copyMatr(matr, m, n);
        char** rightGen = copyMatr(matr, m, n);
        printMatr(fisierout, matr, m, n);
        preorder(fisierout, root->left, leftGen, m, n);         
        preorder(fisierout, root->right, rightGen, m, n);

        for(int k=0; k<m; k++) {
            free(leftGen[k]);
        }
        free(leftGen);

        for(int k=0; k<m; k++) {
            free(rightGen[k]);
        }
        free(rightGen);      
    }

}

void freeTree(Tree* root) {
    if(root==NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    freeNode(root->val);

    free(root);
}

void task3(char** matr, int m, int n, int gen, const char *fisierout) {
    Tree* root = createTree(matr, m, n, 0, gen);

    FILE* writeFile = fopen(fisierout, "w");
    if(writeFile == NULL) {
        printf("Eroare la deschidere fisier task 3");
        exit(1);
    }

    /* Initialising a matrix with dead cells and modifying it using the list in the tree
       while traversing in preorder */
    for(int i=0;i<m;i++) {
        for(int j =0;j<n;j++) {
            matr[i][j] = '+';
        }
    }
    preorder(writeFile, root, matr, m, n);

    freeTree(root);

    for(int k=0; k<m; k++) {
        free(matr[k]);
    }
    free(matr);

    fclose(writeFile);
}
