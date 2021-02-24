

/* Se da un graf orientat cu n varfuri si m muchii, fara costuri, citit prin vectorul muchiilor din fisier GRAF.TXT . Sa se foloseasca algoritmul de explorare in adancime pentru a preciza componentele conexe ale graficului
Date de intrare: Datele citite din fisier
Date de iesire : Se precizeaza componentele conexe ale grafului
Se va incepe cu functia de citire in care se va citi graful din fisier si se va construi matricea de adiacenta.
Matricea de adiacenta ne ajuta sa vedem daca exista sau nu cicluri in graf.
Functia "afisare", afiseaza matricea de adiacenta a grafului citit din fisier.
Vom avea o functie de explorare in adancime care va preciza componentele conexe ale graficului.
In main am apelat functiile "citire" pentru a citi din fisier graful, "afisare" pentru a afisa matricea de adiacenta. */

#include <stdio.h>
#include <stdlib.h>

int x[20][20],y[20],v[20],ns,comp;
int prim;
int ultim;

void citire(int *n)   // se citeste graful din fisier text si construirea matricei de adiacenta
{
    FILE *f=fopen("Graf","r"); //se deschide fisierul
    int i,j,y,m;
    fscanf(f,"%d",n);
    fscanf(f,"%d",&m);      //se preiau datele din fisier
    for(y=1; y<=m; y++)     //se construieste matricea
    {
        fscanf(f,"%d",&i);
        fscanf(f,"%d",&j);
        x[i][j]=x[j][i]=1;
    }

    fclose(f);
}

void afisare(int n)         // afisarea pe ecran a matricei de adiacenta
{
    int i,j;
    printf("Matricea de adiacenta este: \n");
    for( i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            printf("%d ",x[i][j]);
        printf("\n");
    }
}
int vizitate[100];
void explorare_adancime (int n, int s)
{
    int t;
    printf("%d ",s);
    vizitate[s]=1;
    for(t=1; t<=n; t++)
    {
        if(x[s][t]==1 && !vizitate[t])
        {
            explorare_adancime(n,t);
        }
    }
}

int exista_nod_nevizitat(int v[20], int n)
{
    int i;
    for(i=1; i<=n; i++)
        if(v[i]==0)
            return i; // primul nod nevizitat
    return 0;   // nu mai exista noduri nevizitate

}


int parcurgere_latime(int x[20][20], int n,int ns) // verificarea unei componente conexe, plec‚nd din nodul de start ns
{
    int i;
    comp++;
    v[ns]=1;
    prim=ultim=1;
    y[ultim]=ns;
    while(prim<=ultim)
    {
        for(i=1; i<=n; i++)
        {
            if(x[y[prim]][i]==1)
            {
                if(v[i]==0)
                {
                    ultim++;
                    y[ultim]=i;
                    v[i]=1;
                }
            }
        }
        prim++;
    }
    return 0;
}
int main()
{
    int n;
    citire(&n); //citeste graful din fisier
    afisare(n);//afiseaza matricea de adiacenta
    ns=1;
    parcurgere_latime(x,n,ns);//exploarea in latime
    while(exista_nod_nevizitat(v,n)!=0)
    {
        ns=exista_nod_nevizitat(v,n);
        parcurgere_latime(x,n,ns);  //parcurg o alta componenta conexa
    }
    printf("Graful este alcatuit din %d componente conexe \n", comp);
    return 0;
}

