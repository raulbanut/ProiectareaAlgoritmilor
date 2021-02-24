#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** new_matrix(unsigned int size, char initialize_max)
{
    unsigned int i, j;
    int** new_mat = (int**)malloc(size * sizeof(int));
    for (i = 1; i < size; i++)
    {
        new_mat[i] = (int*)malloc(size * sizeof(int));
        if (initialize_max)
            for (j = 1; j < size; j++)
                new_mat[i][j] = 0x7fffffff;
    }
    return new_mat;
}

int** citire(FILE* f, unsigned int* n)
{
    unsigned int i, j, c;
    fscanf(f, "%d", n);
    int** cost = new_matrix(++ * n, 1);
    while (!feof(f))
    {
        fscanf(f, "%d%d%d", &i, &j, &c);
        if (i > 0 && i <= *n && j > 0 && j <= *n)
        {
            cost[i][j] = c;
            //cost[j][i] = c;
        }
    }
    return cost;
}

void afisare(unsigned int n, int** cost)
{
    unsigned int i, j;
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            printf("%11d ", cost[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** FLOYD(unsigned int n, int** cost, int*** P)
{
    unsigned int i, j, k;
    int** floyd = new_matrix(n, 0);
    int** p = new_matrix(n, 0);
    for (i = 1; i < n; i++)
        for (j = 1; j < n; j++) {
            floyd[i][j] = cost[i][j];
            p[i][j] = 0;
        }
    for (i = 1; i < n; i++) floyd[i][i] = 0;
    for (k = 1; k < n; k++) {
        for (i = 1; i < n; i++)
            for (j = 1; j < n; j++)
                if (floyd[i][k] + floyd[k][j] < floyd[i][j] && floyd[i][k] != 0x7fffffff && floyd[k][j] != 0x7fffffff)
                {
                    floyd[i][j] = floyd[i][k] + floyd[k][j];
                    p[i][j] = k;
                }
    }
    *P = p;
    return floyd;
}

void afisare_cale(int** P, unsigned int start, unsigned int stop)
{
    if (P[start][stop] != 0)
    {
        unsigned int k = P[start][stop];
        afisare_cale(P, start, k);
        printf("%d->", k);
        afisare_cale(P, k, stop);
    }
}

void free_matrix(unsigned int n, int** matr)
{
    if (!matr) return;
    unsigned int i;
    for (i = 1; i < n; i++)
        free(*(matr + i));
    free(matr);
}

int main()
{
    FILE* f = fopen("date.in", "r");
    unsigned int n;
    char optiune;
    int** cost = NULL, ** floyd = NULL, ** P = NULL;
    if (!f)
    {
        printf("fisierul nu a fost deschis");
        exit(1);
    }
    cost = citire(f, &n);
    fclose(f);
    afisare(n, cost);
    floyd = FLOYD(n, cost, &P);
    afisare(n, floyd);
    while (1)
    {
        fflush(stdin);
        printf("1- Alegere cale 2- Iesire\n");
    HERE:
        scanf("%c", &optiune);
        switch (optiune)
        {
        case '1': {
            unsigned int start, stop;
            printf("Introduceti nodul de inceput: ");
            scanf("%d", &start);
            printf("Introduceti nodul de final: ");
            scanf("%d", &stop);
            if (floyd[start][stop] == 0x7fffffff) {
                printf("calea nu exosta\n");
                break;
            }
            else
            {
                printf("Calea: %d->", start);
                afisare_cale(P, start, stop);
                printf("%d are costul de %d\n", stop, floyd[start][stop]);
                break;
            }
        }
        case '2':
            free_matrix(n, cost);
            free_matrix(n, floyd);
            free_matrix(n, P);
            return 0;
            break;
        case '\n':
            goto HERE;
            break;
        default:
            printf("optiune gresita\n");
            break;
        }
    }
}
