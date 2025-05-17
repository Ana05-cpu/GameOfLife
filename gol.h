#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coordonate {
    int l;
    int c;
};
typedef struct Coordonate Coord;

struct Node {
    Coord val;
    struct Node* next;
};
typedef struct Node Node;

struct Stack {
    int gen;
    Node* val;
    struct Stack* next;
};
typedef struct Stack Stack;

struct N {
    Node* val; 
    struct N *left ,* right ;
};
typedef struct N Tree;

typedef struct {
    int V, E;
    int **a;
} Graph;

int nr_vecini_vii(char** matr, int i, int j, int m, int n);

void task1(char** matr, int m, int n, int gen, const char *fisierout);

void task2(char** matr, int m, int n, int gen, const char *fisierout);

void add(Node** head, Coord val);

void push(Stack** top, Node* v, int gen);

void printStack(Stack* stackTop, FILE* fisierout);

void printList(Node* head, FILE* fisierout);

Node* pop(Stack** top);

void freeNode(Node* head);

//Node* copyNode(Stack** top);

void writeBonusFile(Stack* top, char** lastGen, int m, int n, const char* fisierout);

void BONUS(const char* file, const char* fisierout);

Tree* createTreeNode(Node* head);

Node* newRule(char** matr, int m, int n);

Node* oldRule(char** matr, int m, int n);

void nextGenMatr(char** matr, Node* head);

char** copyMatr(char** matr, int m, int n);

Tree* createTree(char** matr, int m, int n, int g, int gen);

void printMatr(FILE* fisierout, char** matr, int m, int n);

void preorder(FILE* fisierout, Tree* root, char** matr, int m, int n);

void task3(char** matr, int m, int n, int gen, const char *fisierout);

void preorderGraphs(FILE* fisierout, Tree* root, char** matr, int m, int n);

void task4(char** matr, int m, int n, int gen, const char *fisierout);

void processGraph(FILE* fisierout, char** matr, int m, int n);

int* longestChainInComponent(Graph* g, int* components, int vertices, int c);

int DFSChain(Graph* g, int* components, int c, int* currChain, int* visited, int* bestChain,
         int currLength, int vertices);

void DFS_scan(Graph *g, int* components, int comp_conexe, int visited[], int i);

int DFS(Graph *g, int* components);

Graph* createGraph(int V, int E, int** adj);

void freeGraph(Graph* g);