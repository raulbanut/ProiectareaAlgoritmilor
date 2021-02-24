#include <stdio.h>
#include <stdlib.h>

typedef struct objects
{
    unsigned int greutatea, pret;
}Obiecte;

void sort(Obiecte* O, unsigned int n)
{
    unsigned int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (O[i].pret < O[j].pret)
            {
                Obiecte aux;
                aux.pret= O[i].pret;
                aux.greutatea = O[i].greutatea;
                O[i].pret = O[j].pret;
                O[i].greutatea = O[j].greutatea;
                O[j].pret = aux.pret;
                O[j].greutatea = aux.greutatea;
            }
        }
    }
}

void Ghiozdan_Greedy(unsigned int GMax, unsigned int Nr, Obiecte* O)
{
    unsigned int i = 0, G_Included = 0, Total_Cost = 0,G_In=0;
    char Not_Full = 1, Is_Separated = 0;
    while (Not_Full)
    {
        if (O[i].greutatea + G_Included < GMax)
        {
            G_Included += O[i].greutatea;
            Total_Cost += O[i].pret * O[i].greutatea;
            i++;
        }
        else
        {
            G_In = GMax - G_Included;
            Total_Cost += G_In * O[i].pret;
            Is_Separated = 1;
            G_Included = GMax;
        }
        if (G_Included == GMax || i == Nr - 1)
            Not_Full = 0;
    }
    printf("Costul total este de %d\n", Total_Cost);
    if (!Is_Separated)
    {
        unsigned int j;
        for (j = 0; j <= i; j++)
        {
            printf("In ghiozdan se afla obiectul cu greutatea %d si pretul %d in totalitate\n", O[j].greutatea, O[j].pret);
        }
    }
    else
    {
        unsigned int j;
        for (j = 0; j < i; j++)
        {
            printf("In ghiozdan se afla obiectul cu greutatea %d si pretul %d in totalitate\n", O[j].greutatea, O[j].pret);
        }
        printf("In ghiozdan se afla %d din obiectul cu greutatea %d si pretul %d \n", G_In , O[j].greutatea, O[j].pret);
    }
}

int main()
{
    unsigned int GMax, Nr_Objects,i;
    printf("Introduceti greutatea ghiozdanului: ");
    scanf(" %d", &GMax);
    printf("Introduceti numarul de materiale: ");
    scanf(" %d", &Nr_Objects);
    printf("Introduceti materialele in pereche (greutate cost): ");
    Obiecte *O = (Obiecte *)malloc(sizeof(Obiecte) * Nr_Objects);
    for (i = 0; i < Nr_Objects; i++)
        scanf(" %d%d", &O[i].greutatea, &O[i].pret);
    sort(O,Nr_Objects);
    Ghiozdan_Greedy(GMax, Nr_Objects, O);
    free(O);
    return 0;
}
