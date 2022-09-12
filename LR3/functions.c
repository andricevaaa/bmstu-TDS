#include "functions.h"

void info(void)
{
    printf("Programm that sums sparse matrixes \n \n");
    printf("When you enter matrix first you'll have to input \n");
    printf("number of rows and number of collumns. \n");
    printf("Both matrixes have to have same number of rows and collumns \n");
    printf("so you'll only get to enter size once. \n");
    printf("All elements of matrixes are entered row by row. \n");
}

//если вводим данные с клавиятуры
int size(int *n, int *m)
{
    int x, y;
    printf("Enter the number of rows: ");
    if (scanf("%d", &x) != 1)
        return ERR_IO;
    printf("\n");
    while (x > 1000 || x < 1)
    {
        printf("Invalid input. Try again: ");
        if (scanf("%d", &x) != 1)
            return ERR_IO;
        printf("\n");
    }
    printf("Enter the number of columns: ");
    if (scanf("%d", &y) != 1)
        return ERR_IO;
    printf("\n");
    while (y > 1000 || y < 1)
    {
        printf("Invalid input. Try again: ");
        if (scanf("%d", &y) != 1)
            return ERR_IO;
        printf("\n");
    }
    printf("\n");
    *n = x;
    *m = y;
    return OK;
}

void free_matrix(int **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);
    free(data);
}

int **allocate_matrix(int n, int m)
{
    int **data;
    data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int));
        if (!data[i])
        {
            free_matrix(data, n);
            return NULL;
        }
    }
    return data;
}

//если вводим данные с клавиятуры
int get_data(int x, int y, int *A, int *JA, node_t *IA, int **matrix)
{
    int p, l, d, t, s;
    int *X = A;
    int *JX = JA;
    node_t *IX = IA;
    int arr[x];
    for (s = 0; s < x; s++)
        arr[s] = 0;
    IX->N = 0;
    IX->next = (node_t *)malloc(sizeof(node_t));
    for (int j = 0; j < x; j++)
        for (int k = 0; k < y; k++)
            matrix[j][k] = 0;
    printf("Enter the amount of non-zero elements: ");
    if (scanf("%d", &p) != 1)
            return ERROR;
    while (p < 1)
    {
        printf("Invalid input. Try again: ");
        if (scanf("%d", &p) != 1)
            return ERROR;
    }
    for (int i = 0; i < p; i++)
    {
        printf("Enter the non-zero element: ");
        if (scanf("%d", &l) != 1)
            return ERROR;
        while (l == 0)
        {
            printf("Invalid input. Try again: ");
            if (scanf("%d", &l) != 1)
                return ERROR;
        }
        printf("Enter row: ");
        if (scanf("%d", &d) != 1)
            return ERROR;
        while (d < 0 || d >= x)
        {
            printf("Invalid input. Try again: ");
            if (scanf("%d", &d) != 1)
                return ERROR;
        }
        printf("Enter column: ");
        if (scanf("%d", &t) != 1)
            return ERROR;
        while (t < 0 || t >= y)
        {
            printf("Invalid input. Try again: ");
            if (scanf("%d", &t) != 1)
                return ERROR;
        }
        matrix[d][t] = l;
        X[i] = l;
        JX[i] = t;
        arr[d] += 1;
    };
    d = 0;
    for (s = 0; s < x; s++)
    {
        IX = IX->next;
        IX->N = arr[s] + d;
        IX->next = (node_t *)malloc(sizeof(node_t));
        d = IX->N;
    }
    free(IX->next);
    printf("\n");
    IX->next = NULL;
    return p;
}

void write(int *AB, int *JAB, int *BA, int *JBA, int *d, int *t, int *kol)
{
    AB[*d] = BA[*t];
    JAB[*d] = JBA[*t];
    *d += 1;
    *t += 1;
    *kol += 1;
}

//суммируем разреженную матрицу
int spec_sum(int *A, int *JA, node_t *IA, int *B, int *JB, node_t *IB, int *AB, int *JAB, node_t *IAB)
{
    int col1 = IA->N;
    int col2 = IB->N;
    int cnt = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    node_t *IX = IAB;
    node_t *IAX = IA;
    node_t *IBX = IB;
    IAX = IAX->next;
    IBX = IBX->next;
    IX->N = 0;
    IX->next = (node_t *)malloc(sizeof(node_t));
    while (IAX != NULL)
    {
        IX->next->N = IX->N;
        IX = IX->next;
        while ((IAX->N - col1) != 0 && (IBX->N - col2) != 0)
        {
            if (JA[x] < JB[y])
            {
                write(AB, JAB, A, JA, &z, &x, &col1);
                IX->N += 1;
                cnt++;
            }
            else if (JA[x] > JB[y])
            {
                write(AB, JAB, B, JB, &z, &y, &col2);
                IX->N += 1;
                cnt++;
            }
            else
            {
                AB[z]= A[x] + B[y++];
                JAB[z++] = JA[x++];
                col1++;
                col2++;
                IX->N += 1;
                cnt++;
            }
        }
        while (col1 != IAX->N)
        {
            write(AB, JAB, A, JA, &z, &x, &col1);
            IX->N += 1;
            cnt++;
        }
        while (col2 != IBX->N)
        {
            write(AB, JAB, B, JB, &z, &y, &col2);
            IX->N += 1;
            cnt++;
        }
        col1 = IAX->N;
        col2 = IBX->N;
        IX->next = (node_t *)malloc(sizeof(node_t));
        IAX = IAX->next;
        IBX = IBX->next;
    }
    free(IX->next);
    IX->next = NULL;
    return cnt;
}

//суммируем стандартную матрицу
void normal_sum(int **matrix1, int **matrix2, int p, int q)
{
    for (int i = 0; i < p; i++)
        for (int j = 0; j < q; j++)
            matrix1[i][j] += matrix2[i][j];
}

//печатаем разреженную матрицу
void print_csr(int **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    };
}

void print_nz(int *A, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

//освобождаем память
void free_all(int *X, int *JX)
{
    free(X);
    free(JX);
}

void freeList(node_t *head)
{
   node_t *tmp;
   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
    free(head);

}

float count_percent(int x, int y, int l)
{
    float m = x;
    float n = y;
    float d = l;
    float res = (d * 100) / (m * n);
    return res;
}

void print_list(node_t *X)
{
    while (X != NULL)
    {
        printf("%d ", X->N);
        X = X->next;
    }
}