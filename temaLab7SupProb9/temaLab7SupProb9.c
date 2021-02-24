/* Se da un graf orientat cu n varfuri si m muchii. Sa se foloseasca algoritmul de parcurgere in largime pentru a se preciza daca contine cicluri*/

#include <stdio.h>
#include <stdlib.h>
#define NMAX 20


int mat[NMAX][NMAX],vizitat[NMAX],t[NMAX],ac=0;



void citire(int *n)
{
    FILE *f=fopen ("Graf","r");
    if(f == NULL)
    {
        printf("\nnu se poate deschide fisierul");
        exit(0);
    }

    int i,j,m,c;
    fscanf(f,"%d",n); //citim nr de noduri
    fscanf(f,"%d",&m);  //citim nr de muchii


    for(i=1;i<=*n;i++) //initializare matrice nula
    {
        for(j=1;j<=*n;j++)
        {
            mat[i][j]=0;
            mat[j][i]=0;
        }
    }

    for(c=1;c<=m;c++)  //pt fiecare pereche de muchii
    {
        fscanf(f,"%d",&i);
        fscanf(f,"%d",&j);
        mat[i][j]=1;
        mat[j][i]=1;  //e neorientat
    }

    fclose(f);

}

void explorare_largime(int NrNoduri, int s)
{
    int k;
    vizitat[s]=1;
    for(k=1;k<=NrNoduri;k++)
        if(mat[s][k])
    {
        mat[k][s]=0;
        if(vizitat[k]==0)
            explorare_largime(NrNoduri,k);
        else
            ac=1;
    }

}



int main()
{
    FILE *f=fopen("Graf","r");

    if(f==NULL)
    {
        printf("Probleme la fisier!");
        exit(0);
    }

    int n;
    citire(&n);
    explorare_largime(n,1);
    if(ac==0)
        printf("Nu avem ciclu\n");
    else
        printf("Avem ciclu\n");

    return 0;
}
