#include <stdio.h>
#include <stdlib.h>
//dist maxima - distanta la care se afla mod dist ridicare = numarul de mere care pot fi luate inainte ca acesta sa devina inaccesibil
typedef struct Mar
{
    unsigned int dist, greutate, nr_mere;
}Mere;

/*void sortare2(unsigned int n, Mere* M)
{
    unsigned int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (M[i].nr_mere == M[j].nr_mere&& M[i].greutate < M[j].greutate)
            {
                Mere aux;
                aux.dist = M[i].dist;
                aux.greutate = M[i].greutate;
                aux.nr_mere = M[i].nr_mere;
                M[i].dist = M[j].dist;
                M[i].greutate = M[j].greutate;
                M[i].nr_mere = M[j].nr_mere;
                M[j].dist = aux.dist;
                M[j].greutate = aux.greutate;
                M[j].nr_mere = aux.nr_mere;
            }
        
}*/

void sortare(unsigned int n, unsigned int i_max, unsigned int i_ridic, Mere* M)
{
    unsigned int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (M[i].nr_mere > M[j].nr_mere|| M[i].nr_mere == M[j].nr_mere && M[i].greutate < M[j].greutate)
            {
                Mere aux;
                aux.dist = M[i].dist;
                aux.greutate = M[i].greutate;
                aux.nr_mere = M[i].nr_mere;
                M[i].dist = M[j].dist;
                M[i].greutate = M[j].greutate;
                M[i].nr_mere = M[j].nr_mere;
                M[j].dist = aux.dist;
                M[j].greutate = aux.greutate;
                M[j].nr_mere = aux.nr_mere;
            }
    //sortare2(n, M);
}
//6 10 4 1 4 2 6 5 2 7 1 8 9 9 10
unsigned int G_max(unsigned int n, unsigned int i_max, unsigned int i_ridic, Mere* M)
{
    unsigned int i, Gr = 0, Mere_culese = 0;
    for (i = 0; i < n; i++)
    {
        if (i_ridic * Mere_culese + M[i].dist <= i_max)
        {
            Gr += M[i].greutate;
            Mere_culese++;
        }
    }
    return Gr;
}
int main()
{
    unsigned int n,i,inal_max,inal_ridicare;
    printf("Introduceti numarul de mere: ");
    scanf(" %d", &n);
    printf("Introduceti inaltimea maxima pentru a cuege: ");
    scanf(" %d", &inal_max);
    printf("Introduceti inaltimea cu care se ridica creanga: ");
    scanf(" %d", &inal_ridicare);
    printf("Introduceti merele (distanta pana la pamant, geutatea)\n");
    Mere* M = (Mere*)malloc(n * sizeof(Mere));
    for (i = 0; i < n; i++) {
        scanf(" %d%d", &M[i].dist, &M[i].greutate);
        M[i].nr_mere = (inal_max - M[i].dist) / inal_ridicare;
    }
    sortare(n,inal_max,inal_ridicare, M);
    printf("Greutatea maxima care poate fi cuelasa este %d\n", G_max(n, inal_max, inal_ridicare, M));
    free(M);
    return 0;
}
