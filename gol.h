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

//void writeBonusFile(Stack* top, char** genUrm, int m, int n, const char* fisierout);

//void BONUS(const char* file, const char* fisierout);
