#include <stdio.h>
#include <stdlib.h>

unsigned int sol = 0;
void afisare_matr(unsigned int** mat, unsigned int dim)
{
    unsigned int i, j;
    printf("Solutia Nr.%d:\n", ++sol);
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

unsigned int** Alocare(unsigned int dim)
{
    unsigned int i;
    unsigned int** nou = (unsigned int)calloc(dim, sizeof(unsigned int*));
    for (i = 0; i < dim; i++)
        *(nou + i) = (unsigned int)calloc(dim, sizeof(unsigned int));
    return nou;
}

void eliberare(unsigned int dim, unsigned int** mat)
{
    unsigned int i;
    for (i = 0; i < dim; i++)
        free(*(mat + i));
    free(mat);
}

char Matrice_Valida(unsigned int dim, unsigned int** mat)
{
    unsigned int i, j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            if (!mat[i][j]) return 0;
    return 1;
}

void backtracking(int dim, unsigned int** mat, int i, int j, unsigned int pas)
{
    mat[i][j] = pas;
    if (i - 1 >= 0 && j - 2 >= 0)
        if (!mat[i - 1][j - 2])
            backtracking(dim, mat, i - 1, j - 2, ++pas);
    if (i - 2 >= 0 && j - 1 >= 0)
        if (!mat[i - 2][j - 1])
            backtracking(dim, mat, i - 2, j - 1, ++pas);
    if (i - 2 >= 0 && j + 1 < dim)
        if (!mat[i - 2][j + 1])
            backtracking(dim, mat, i - 2, j + 1, ++pas);
    if (i - 1 >= 0 && j + 2 < dim)
        if (!mat[i - 1][j + 2])
            backtracking(dim, mat, i - 1, j + 2, ++pas);
    if (i + 1 < dim && j + 2 < dim)
        if (!mat[i + 1][j + 2])
            backtracking(dim, mat, i + 1, j + 2, ++pas);
    if (i + 2 < dim && j + 1 < dim)
        if (!mat[i + 2][j + 1])
            backtracking(dim, mat, i + 2, j + 1, ++pas);
    if (i + 2 < dim && j - 1 >= 0)
        if (!mat[i + 2][j - 1])
            backtracking(dim, mat, i + 2, j - 1, ++pas);
    if (i + 1 < dim && j - 2 >= 0)
        if (!mat[i + 1][j - 2])
            backtracking(dim, mat, i + 1, j - 2, ++pas);
    //afisare_matr(mat, dim);
    if (Matrice_Valida(dim, mat)) afisare_matr(mat, dim);
    mat[i][j] = 0;
}

int main()
{
    unsigned int dim = 0;
    while (!dim) {
        printf("Introduceti dimensiunea matricei: ");
        scanf(" %d", &dim);
        if (!dim)printf("Dimensiunea matricei nu poate fi mai mica ca 0!\n");
    }
    unsigned int** mat = Alocare(dim);
    backtracking(dim, mat, 0, 0, 1);
    eliberare(dim, mat);
    return 0;
}
