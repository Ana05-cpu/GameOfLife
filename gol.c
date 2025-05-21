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

    // Invert the stack to print it in the correct order
    Stack* aux = NULL;
    while(top != NULL) {
        int tempGen = top->gen;
        push(&aux, pop(&top), tempGen);
    }
    printStack(aux, output);
    fclose(output);

    // Bonus input file creation with extension ".out.bonus.in"
    char fisier[50];
    strcpy(fisier, fisierout);
    strcat(fisier, ".bonus.in");

    FILE* bonusInput = fopen(fisier, "w");
    if(bonusInput == NULL) {
        printf("Eroare deschidere fisier bonus input");
    }

    printStack(aux, bonusInput);

    // Free the stack
    while(aux != NULL) {
        Node* temp = pop(&aux);
        freeNode(temp);
    }

    fprintf(bonusInput, "\n");

    // Print final matrix in the bonus input file
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

// Print the list of coordinates
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
    char linie[500];
    // Flag for signaling the end of the stack in the file
    int endOfStack = 0;
    // Iterate over each line (generation) in the stack
    while(fgets(linie, sizeof(linie), inputBonus) != NULL){
        // Check if line is "\n" -> signals the end of the stack/the begining of the matrix
        if(strcmp(linie, "\n") == 0) {
            endOfStack = 1;
            // Jump over the "\n" line
            continue;
        } 
        if(endOfStack == 0) {
            // Split the line into strings (tokens) by space
            char const* token = strtok(linie, " ");
            if(token!=NULL) {
                // First string is the generation so it gets converted to an integer 
                int gen = atoi(token);
                head = NULL;
                int count = 2;
                // Get the next string separated by space
                token = strtok(NULL, " ");
                /*
                    Gets the first coordinate, which is the line, then reduce the count. After storing the second coordinate,
                    which is the column, reset the count and store the coordinates in the list
                */
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
            do {
                // Use the first line to determine the number of columns
                if(m == 0) {
                    for(int i = 0; i<strlen(linie); i++) {
                        if(linie[i] != '\n') n++;
                    }
                }
                // Determine the number of lines
                m++;
            } while(fgets(linie, sizeof(linie), inputBonus) != NULL);
            break;
        }
    }

    fclose(inputBonus);

    char** lastGen = (char**)malloc(m*sizeof(char*));
    for(int k=0; k<m; k++) {
        lastGen[k] = (char*)calloc(n, sizeof(char));
    }

    // Reopen the input file and jump over the stack
    inputBonus = fopen(file, "r");

    while(fgets(linie, sizeof(linie), inputBonus) != NULL){
        if(strcmp(linie, "\n") == 0) {
            break;
        }
    } 
    //  Store the matrix
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            do {
                fscanf(inputBonus, "%c", &lastGen[i][j]);
            } while(lastGen[i][j]=='\n' || lastGen[i][j]=='\r');
        } 
    }
    fclose(inputBonus);

    writeBonusFile(top, lastGen, m, n, fisierout);
}

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
        freeNode(currCoord);
    }

    /*
        Create a new output file with the extension ".out.bonus.out" for each test file, 
        which contains the original matrix 
    */
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

    for(int i=0; i<m; i++) {
        free(lastGen[i]);
    } 
    free(lastGen);

    fclose(output);
}

Tree* createTreeNode(Node* head) {
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->val = head;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* 
    Implementation of the new rule, that revives dead cells that have exactly
    2 alive neighbours 
 */
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

    /* 
        Make a copy of the current matrix; 
        Creates the coordinates list based on the new rule;
        Uses the list to generate the next generation matrix;
        Asigns the list to the left child of the current node
        Calls the recursive method over the left child to continue the process, then it asigns
        its children accordingly 
        Frees the matrix used by the left child
    */
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
    // Left child is not needed anymore because of whole subtree is already calculated
    free(leftChild); 

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

/* 
    Traverse the created tree in preorder and write to a file, for each node in the tree it 
    traverses, the corresponding matrix 
*/
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

    /* 
        Initialising a matrix with dead cells and modifying it using the list in the tree
        while traversing in preorder 
    */
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

void processGraph(FILE* fisierout, char** matr, int m, int n) {
    /* 
        Create a matrix that will assign a number starting from 1 for each cell that 
        is alive. The dead cells will have 0 assigned 
    */
    int** matrComp = (int**)malloc(m*sizeof(int*));
    for(int k=0; k<m; k++) {
        matrComp[k] = (int*)calloc(n, sizeof(int));
    }
    // Count the number of vertices that will compose the graph
    int nodeNo = 0;
    for(int i=0;i<m;i++) {
        for(int j =0;j<n;j++) {
            if(matr[i][j] == 'X') {
                matrComp[i][j] = ++nodeNo;
            } else {
                matrComp[i][j] = 0;
            }
        }
    }

    // Array of coordinates for each vertex
    Coord* coords = (Coord*)malloc((nodeNo+1)*sizeof(Coord));
    int count = 0;
    for(int i=0;i<m;i++) {
        for(int j =0;j<n;j++) {
            if(matr[i][j] == 'X') {
               coords[++count].l = i;
               coords[count].c = j;
            }
        }
    } 

    // Create the adjacency matrix for the graph
    int** adj = (int**)malloc((nodeNo+2)*sizeof(int*));
    for(int k=0; k<=nodeNo+1; k++) {
        adj[k] = (int*)calloc((nodeNo+2), sizeof(int));
    }
    for(int i=0;i<nodeNo+1;i++) {
        for(int j =0;j<nodeNo+1;j++) {
            adj[i][j] = 0;  
        }
    }
    /*
        Go through each vertex in the created matrix and check all its neighbours.
        If they are also vertices in the graph, fill the adjacency matrix accordingly.
        Also calculate the number of edges.
    */
    int E = 0;
    for(int i=0;i<m;i++) {
        for(int j =0;j<n;j++) {
            if(matrComp[i][j] > 0) {
                int currN = matrComp[i][j];
                for(int v = -1; v <= 1; v++) {
                    for(int w = -1; w <= 1; w++) {
                        if(!(v == 0 && w == 0)) {
                            if(i + v >= 0 && i + v < m && j + w >= 0 && j + w < n) {
                                int neighbN = matrComp[i+v][j+w];
                                if(neighbN > 0) {
                                    adj[currN][neighbN] = 1;
                                    adj[neighbN][currN] = 1;
                                    if(currN < neighbN) E++;
                                } 
                            }
                        }
                    }
                }
            }
        }
    }
    Graph* g = createGraph(nodeNo, E, adj);

    /* 
        Calculate the number of conected components and assign a number to them starting from 1
        Create an array to make a correlation between vertex and component: the position in the array
            represents the vertex and the value represents the component which contains it
    */
    int* components = (int*)malloc((g->V+1)*sizeof(int));
    for(int i=1; i<=g->V; i++) {
        components[i] = 0;
    }
    int compNo = DFS(g, components);

    // Array for solution -> the first element is the length of the chain and the rest show the vertices in order
    int* sol = (int*)malloc((g->V+2)*sizeof(int));
    sol[0] = -1;
    // Iterate through all the components
    for(int c = 1; c <= compNo; c++) {
        int vertices = 0;
        for(int i=1; i<=g->V;i++) {
            // Count the number of vertices in the component 
            if(components[i] == c) {
                vertices++;
            }
        }
        int* tempChain = longestChainInComponent(g, components, vertices, c);
        if(tempChain[0] > sol[0]) {
            for(int j = 0; j <= tempChain[0] + 1; j++) {
                sol[j] = tempChain[j];
            }
        }
        free(tempChain);
    }
    free(components);
    for(int k=0; k<m; k++) {
        free(matrComp[k]);
    }
    free(matrComp);      

    int l = sol[0];
    fprintf(fisierout, "%d\n", l);
    if(sol[0] != -1) {
        // Prints the pairs of coordinates for each vertex 
        fprintf(fisierout, "(%d,%d)", coords[sol[1]].l, coords[sol[1]].c);
        for(int i = 2; i <= l + 1; i++) {
            fprintf(fisierout, " (%d,%d)", coords[sol[i]].l, coords[sol[i]].c);
        }
        fprintf(fisierout, "\n");
    }
    free(sol);
    free(coords);
    freeGraph(g);
}

void freeGraph(Graph* g) {
    for(int k=0; k<=g->V+1; k++) {
        free(g->a[k]);
    }
    free(g->a);   

    free(g);
}

int* longestChainInComponent(Graph* g, int* components, int vertices, int c) {
    int* bestChain = (int*)malloc((g->V+1)*sizeof(int));
    bestChain[0] = 0;

    // If there is a single vertex in the component, set size to 0 and store the coordinates of the single vertex
    if(vertices == 1) {
        for(int i=1; i<g->V;i++) {
            if(components[i] == c) {
                bestChain[0] = 0;
                bestChain[1] = components[i];
                return bestChain;
            }
        }
    }

    int* visited = (int*)malloc((g->V+1)*sizeof(int));
    int* currChain = (int*)malloc((g->V+1)*sizeof(int));
    for(int i=1; i<=g->V; i++) {
        // Only work with vertices from the current component
        if(components[i] == c) {
            for(int j=1; j<=g->V; j++) {
                visited[j] = 0;
            }
            currChain[0] = i; 
            visited[i] = 1;
            int longestChain = DFSChain(g, components, c, currChain, visited, bestChain, 1, vertices);
            // If there are 2 or more vertices in the components, but it cannot find a hamiltonian chain, set size to -1
            if (longestChain == 0) {
                bestChain[0] = -1;
                continue;
            }
            if (bestChain[0] == vertices - 1) {
                break;
            }
        } 
    }
    free(visited);
    free(currChain);
    return bestChain;
}

// Recursive method to find the hamiltonian chain in the component
int DFSChain(Graph* g, int* components, int c, int* currChain, int* visited, int* bestChain,
         int currLength, int vertices) {
    if(currLength > bestChain[0]) {
        bestChain[0] = currLength;
        for(int i=0; i<currLength; i++) {
            // Current chain doesn't store the length in the first element
            bestChain[i+1] = currChain[i];
        }
    }

    // bestChain[0] was counting vertices, so it's decreased by 1 to show the number of edges
    if(currLength == vertices) {
        bestChain[0]--;
        return 1;
    }

    int lastVert = currChain[currLength - 1];
    for(int i = 0; i <= g->V; i++) {
        // Only checks unvisited vertices from the current component that are adjacent to the last visited vertex
        if(components[i] == c && g->a[lastVert][i] == 1 && visited[i] == 0) {
            currChain[currLength] = i;
            visited[i] = 1;
            int longestChain = DFSChain(g, components, c, currChain, visited, bestChain, currLength+1, vertices);
            // Set visited back to 0 to check the other possible chains continuing from the last vertex
            visited[i] = 0;
            // Exit the recursive method after the first hamiltonian chain has been found
            if (longestChain == 1) {
                return 1;
            }
        }
    }

    return 0;
}

void DFS_scan(Graph *g, int* components, int comp_conexe, int visited[], int i) {
    components[i] = comp_conexe + 1;
    int j;
    visited[i] = 1;
    for (j = 1; j <= g->V; j++)
        if (g->a[i][j] == 1 && visited[j] == 0)
            DFS_scan(g, components, comp_conexe, visited, j);
}

int DFS(Graph *g, int* components) {
    int i, comp_conexe = 0, visited[g->V+1];
    for (i = 1; i <= g->V; i++)
        visited[i] = 0;
    for (i = 1; i <= g->V; i++)
        if (visited[i] == 0) {
            DFS_scan(g, components, comp_conexe, visited, i);
            comp_conexe++;
        }
    return comp_conexe;
}

// Adapted the flow from task 3 for printing the matrices to printing the longest hamiltonian chain in each generation
void preorderGraphs(FILE* fisierout, Tree* root, char** matr, int m, int n) {
    if (root) {
        nextGenMatr(matr, root->val);
        char** leftGen = copyMatr(matr, m, n);
        char** rightGen = copyMatr(matr, m, n);
        processGraph(fisierout, matr, m, n);
        preorderGraphs(fisierout, root->left, leftGen, m, n);         
        preorderGraphs(fisierout, root->right, rightGen, m, n);

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

Graph* createGraph(int V, int E, int** adj) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = E;
    g->a = adj;
    return g;
}

void task4(char** matr, int m, int n, int gen, const char *fisierout) {
    Tree* root = createTree(matr, m, n, 0, gen);

    FILE* writeFile = fopen(fisierout, "w");
    if(writeFile == NULL) {
        printf("Eroare la deschidere fisier task 3");
        exit(1);
    }

    for(int i=0;i<m;i++) {
        for(int j =0;j<n;j++) {
            matr[i][j] = '+';
        }
    }
    preorderGraphs(writeFile, root, matr, m, n);

    freeTree(root);
    for(int k=0; k<m; k++) {
        free(matr[k]);
    }
    free(matr);

    fclose(writeFile);
}