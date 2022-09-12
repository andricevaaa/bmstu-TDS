#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "functions.h"

int main()
{ 
    int *A, *JA;
    int *B, *JB;
    node_t *IA;
    node_t *IB;
    int *AB, *JAB;
    node_t *IAB;
    int n, m, rc = OK;
    int elem1, elem2, elem;
    int **matrix1, **matrix2;
    info();
    rc = size(&n, &m);
    if (rc == OK)
    {
        A = (int *)malloc((n*m) * sizeof(int));
        JA = (int *)malloc((n*m) * sizeof(int));
        IA = (node_t *)malloc(sizeof(node_t));
        B = (int *)malloc((n*m) * sizeof(int));
        JB = (int *)malloc((n*m) * sizeof(int));
        IB = (node_t *)malloc(sizeof(node_t));
        matrix1 = allocate_matrix(n, m);
        matrix2 = allocate_matrix(n, m); 
        printf("You're entering the first matrix. \n");
        elem1 = get_data(n, m, A, JA, IA, matrix1);
        if (elem1 == ERROR)
            rc = ERR_IO;
        if (rc == OK)
        {
            printf("You're entering the second matrix. \n");
            elem2 = get_data(n, m, B, JB, IB, matrix2);
            if (elem2 == ERROR)
                rc = ERR_IO;
        };
        if (rc == OK)
        {
            if (n < 10)
            {
                printf("\n");
                print_csr(matrix1, n, m);
                printf("\n");
                print_csr(matrix2, n, m);
            }
            /*printf("\n");
            print_nz(A, elem1);
            printf("\n");
            print_nz(JA, elem1);
            printf("\n");
            print_list(IA);
            printf("\n");
            print_nz(B, elem2);
            printf("\n");
            print_nz(JB, elem2);
            printf("\n");
            print_list(IB);
            printf("\n");*/
            struct timeval start1, start2, end1, end2;
            AB = (int *)malloc((elem1 + elem2) * sizeof(int));
            JAB = (int *)malloc((elem1 + elem2) * sizeof(int));
            IAB = (node_t *)malloc(sizeof(node_t));
            gettimeofday(&start2, NULL);
            elem = spec_sum(A, JA, IA, B, JB, IB, AB, JAB, IAB);
            gettimeofday(&end2, NULL);
            printf("Time taken to do shortened sum: %ld microseconds \n \n", ((end2.tv_sec * 1000000 + end2.tv_usec) - (start2.tv_sec * 1000000 + start2.tv_usec)));
            gettimeofday(&start1, NULL);
            normal_sum(matrix1, matrix2, n, m);
            gettimeofday(&end1, NULL);
            printf("Time taken to do normal sum: %ld microseconds \n \n", ((end1.tv_sec * 1000000 + end1.tv_usec) - (start1.tv_sec * 1000000 + start1.tv_usec)));
            printf("Sparsity of matrix 1: %f%% \n", count_percent(n, m, elem1));
            printf("Sparsity of matrix 2: %f%% \n", count_percent(n, m, elem2));
            printf("Sparsity of resulting matrix: %f%% \n \n", count_percent(n, m, elem));
            printf("Resulting matrix: \n");
            /*if (n < 10)
                print_csr(matrix1, n, m);
            printf("\n");
            print_nz(AB, elem);
            printf("\n");
            print_nz(JAB, elem);
            printf("\n");
            print_list(IAB);
            printf("\n");*/
            free_matrix(matrix1, n);
            free_matrix(matrix2, n);
            free_all(A, JA);
            free_all(B, JB);
            free_all(AB, JAB);
            freeList(IA);
            freeList(IB);
            freeList(IAB);
        }
    };
    return rc;
}