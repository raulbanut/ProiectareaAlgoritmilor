/*17. Se da un graf neorientat cu n noduri si m muchii, fara costuri citit prin vectorul
muchiilor din fisierul GRAF.TXT. Sa se foloseasca algoritmul de explorare in adancime pt
a afisa arborele de acoperire avand radacina nodul s la iesirea standard. s este dat la intrarea standard.*/


#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int adiacenta[NMAX][NMAX];
typedef struct vector
{
    int a,b;
}Vector;

void explorare_adancime(int n, int s)
{
    int i,w,stiva[NMAX],g;
    int vizitat[NMAX],prim,ultim;
    for(i=1; i<=n; i++)
        vizitat[i]=0;
    vizitat[s]=1;
    prim=1;
    ultim=1; //primul si ultimul sunt 1
    stiva[prim]=s;
    while(prim>=ultim)
    {
        g=0;
        w=stiva[prim];
        for(i=1; i<=n; i++)
            if(adiacenta[w][i]==1 && vizitat[i]==0)  // cat timp nu e vizitat si exista legatura
            {
                g=1;
                vizitat[i]=1;
                prim++; // incremantam primul
                stiva[prim]=i;
            }
        if(g==0)
            prim--;

    }
    for(i=1; i<=n; i++)
        printf("%d ",stiva[i]);
}

int main()
{
    Vector v[NMAX];
    int n,m,i,s,j,vi,vf;
    FILE *f;
//    f=fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator7/temaLab7SupProb19/temaLab7SupProb19/Graf","r");
    f=fopen("Graf", "r");
    fscanf(f,"%d",&n);
    fscanf(f,"%d",&m);
    for (i=1;i<=n;i++)
      for(j=1;j<=n;j++)
        adiacenta[i][j]=0;
    for (i=1;i<=m;i++)
    {
        fscanf(f,"%d %d",&vi,&vf);
        v[i].a=vi;
        v[i].b=vf;
        adiacenta[vi][vf]=1;
    }
    fclose(f);
    printf("Nodul radacina:");
    scanf("%d",&s);
    explorare_adancime(n,s);
    return 0;
}
