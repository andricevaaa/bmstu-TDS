#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define OK 0
#define ERR_IO 1
#define ERR 3
#define SIZE 100
#define ERROR -1

typedef struct node
{
    int N;
    struct node *next;
} node_t;

void info(void);
int size(int *n, int *m);
void free_matrix(int **data, int n);
int **allocate_matrix(int n, int m);
int get_data(int x, int y, int *A, int *JA, node_t *IA, int **matrix);
void write(int *AB, int *JAB, int *BA, int *JBA, int *d, int *t, int *kol);
int spec_sum(int *A, int *JA, node_t *IA, int *B, int *JB, node_t *IB, int *AB, int *JAB, node_t *IAB);
void normal_sum(int **matrix1, int **matrix2, int p, int q);
void print_csr(int **matrix, int n, int m);
void print_nz(int *A, int n);
void free_all(int *X, int *JX);
void freeList(node_t* head);
float count_percent(int x, int y, int l);
void print_list(node_t *X);

#endif //FUNCTIONS_H