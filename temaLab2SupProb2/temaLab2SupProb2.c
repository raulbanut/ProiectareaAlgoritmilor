
//
//  main.c
//  problemePropuse2
// laboratorul 2
//
//  Problema Matricilor rare. Sa se adune/inmulteasca doua matrici rare.
//  Matricile vor fi patratice.
//


#include <stdio.h>
#include <stdlib.h>


struct matrici
{
    unsigned int x,y;
    int valoare;
    struct matrici *urm;
};

struct matrici* citire(struct matrici *list); // citeste matricile
void afisare(struct matrici *list,unsigned int marime); // afiseaza matricile
int returneazaValPoz(struct matrici *M, unsigned int posX, unsigned int posY); // returneaza pozitia de la un X,Y
void afiseazaProdus(struct matrici *M1, struct matrici *M2, unsigned int marime); // realizeaza produsul dintre doua matrici
void afiseazaSuma(struct matrici *M1, struct matrici *M2,unsigned int marime); // realizeaza suma dintre doua matrici

int main() {
    unsigned int nr1,nr2,i;
    printf("introduceti numarul de citiri dorite pentru matricea 1: ");
    scanf("%d",&nr1);
    struct matrici *M1=NULL;
    struct matrici *M2=NULL;
    printf("introduceti perechile de x,y pe care se afla valoarea, apoi valoarea :");
    for(i=0;i<nr1;i++)
    {
        struct matrici *check = NULL;
        check = citire(M1);
        if (!check)
            printf("Ultimua pereche nu a putut fi adaugat in lista.");
        else
            M1 = check;
    }
    
    printf("introduceti numarul de citiri dorite pentru matricea 2: ");
    scanf("%d",&nr2);
    printf("introduceti perechile de x,y pe care se afla valoarea, apoi valoarea :");
    for(i=0;i<nr2;i++)
    {
        struct matrici *check = NULL;
        check = citire(M2);
        if (!check)
            printf("Ultimua pereche nu a putut fi adaugat in lista.");
        else
            M2 = check;
    }
    unsigned int dimensiune;
    printf("introduceti dimensiunea matricilor patratice: ");
    scanf("%d",&dimensiune);
    printf("Matricea 1 este : \n");
    afisare(M1, dimensiune);
    printf("Matricea 2 este : \n");
    afisare(M2, dimensiune);
    printf("Suma matricilor este : \n");
    afiseazaSuma(M1, M2, dimensiune);
    printf("Produsul matricilor este : \n");
    afiseazaProdus(M1, M2, dimensiune);
    return 0;
}


struct matrici* citire(struct matrici *list)
{
    struct matrici *nou = (struct matrici *)malloc(sizeof(struct matrici));
    if (!nou) {
        return NULL;
    }
    else
    {
        unsigned int number1, number2;
        int number3;
        scanf(" %d %d %d", &number1,&number2,&number3);
        if (list == NULL)
        {
            nou->urm = NULL;
            nou->x = number1;
            nou->y = number2;
            nou->valoare = number3;
        }
        else
        {
            nou->urm = list;
            nou->x = number1;
            nou->y = number2;
            nou->valoare= number3;
        }
        return nou;
    }
}


void afisare(struct matrici *list,unsigned int marime)
{
    unsigned int i,j;
    for (i = 1; i <= marime; i++)
    {
        for (j = 1; j <= marime; j++)
        {
            struct matrici *cop=list;
            while (cop)
            {
                if (cop->x == i && cop->y == j) {
                    printf("%d ",cop->valoare);
                    goto HERE;
                }
                else
                cop = cop->urm;
            }
            printf("0 ");
        HERE:;
        }
        printf("\n");
    }
    printf("\n");
}

int returneazaValPoz(struct matrici *M, unsigned int posX, unsigned int posY)
{
    while (M)
    {
        if (posX == M->x&&posY == M->y)
            return M->valoare;
        M = M->urm;
    }
    return 0;
}

void afiseazaProdus(struct matrici *M1, struct matrici *M2,unsigned int marime)
{
    unsigned int i, j,k;
    for (i = 1; i <= marime; i++)
    {
        for (j = 1; j <= marime; j++)
        {
            int val = 0;
            for (k = 1; k <= marime; k++)
            {
                val+= returneazaValPoz(M1, i, k) * returneazaValPoz(M2,k,j);
            }
            printf("%d ", val);
        }
        printf("\n");
    }
    printf("\n");
}


void afiseazaSuma(struct matrici *M1, struct matrici *M2,unsigned int marime)
{
    unsigned int i, j;
    for (i = 1; i <= marime; i++)
    {
        for (j = 1; j <= marime; j++)
        {
            printf("%d ", returneazaValPoz(M1,i,j) + returneazaValPoz(M2,i,j));
        }
        printf("\n");
    }
    printf("\n");
}
