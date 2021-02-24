/*1. Se da un graf orientat cu n noduri, si m muchii, fara costuri citit prin vectorul muchiilor din fisierul GRAF.TXT. Sa se foloseasca algoritmul de explorare in largime pt a afisa (la iesirea standard) drumul cel mai scrut de la nodul s la nodul v. Nodurile s si v se citesc de la intrarea standard.*/


#include <stdio.h>
#include <stdlib.h>

#define infinit 0x7FFFFFFF


int** graf;
int* parinti;
int* costuri;
int* vizitat;

unsigned int noduri;

void citire(void);
void afiseazamatricea(void);
void Dijkstra(int s, int v);
int calculeaza(int nodcurent, int v);
int pozmin(void);
void afiseaza(int nodcurent);

int main()
{
    citire();
    afiseazamatricea();
    int s,v;
    printf("Drumul cel mai scurt de la:");
    scanf("%d",&s);
    printf("Pana la:");
    scanf("%d",&v);
    Dijkstra(s,v);
    return 0;
}


void citire()
{
    int m=0;
    FILE* f = fopen("Graf","r");
    fscanf(f,"%d %d", &noduri,&m);

    //aloca memorie pentru graf
    graf = malloc(sizeof(int)*(noduri+1));
    unsigned int i, j;

    for(i = 0; i <= noduri; i++){
        graf[i] = malloc(sizeof(int)*(noduri+1));
        for(j = 0; j <= noduri; j++)
            graf[i][j] = infinit;
    }

    int a=0, b=0;
    int c=0;
    for(c=0;c<=m;c++)
    {
        fscanf(f, "%d %d", &a, &b);
        graf[a][b] = 1;
    }
    fclose(f);
}

void afiseazamatricea()
{
    unsigned int i, j;
    for(i = 1; i <= noduri; i++){
        for(j = 1; j <= noduri; j++)
            if(graf[i][j] == infinit)
                fprintf(stdout,"INF\t");
            else
                fprintf(stdout,"%d\t", graf[i][j]);
        fprintf(stdout,"\n");
    }
}

void Dijkstra(int s, int v)
{
    if(s == v){
        printf("esti deja aici\n");
        return;
    }

    //daca gaseste drum atunci printam drumul
    if(calculeaza(s, v)){
        afiseaza(v);
    }
    //altfel drum imposibil
    else {
        printf("drum imposibil");
    }

}
int calculeaza(int nodcurent, int goalNode)
{
    //initializari vectori imporatanti
    parinti = malloc(sizeof(int)*(noduri+1));
    vizitat = calloc(sizeof(int),noduri+1);
    costuri = malloc(sizeof(int)*(noduri+1));

    int i;
    //costuri initiale infinit peste tot
    for(i = 0; i <= noduri; i++)
        costuri[i] = infinit;

    //nu ne costa nimic sa ajungem in pozitia initiala
    costuri[nodcurent] = 0;

    //tatal nodului de inceput este 0
    parinti[nodcurent] = 0;
    int min;
    do{
        vizitat[nodcurent] = 1;
        //updatam costurile vecinilor nodului curent
        for(i = 1; i <= noduri; i++)
            //daca costul curent plus costul muchiei este mai mare && daca vecinul nu a fost vizitat
            //&& exista muchie intre nod curent si nod vecin
            if(graf[nodcurent][i]+costuri[nodcurent] < costuri[i]&& vizitat[i]==0 && graf[nodcurent][i]!=infinit)
            {
                costuri[i] = costuri[nodcurent]+graf[nodcurent][i];
                //marcam nodul vecin ca si fiu al nodului curent
                parinti[i]=nodcurent;
            }
        //aflam pozitia minimului pe care nu l-am vizitat
        min = pozmin();

        ///trecem la nodul minim
        nodcurent = min;
    }while(nodcurent > 0 && nodcurent != goalNode);///se opreste daca ajunge la destinatie sau daca nu mai exista drum

    if(nodcurent < 0)
        return 0;
    else return 1;
}

int pozmin()
{
    int i;
    int min = infinit;
    int minPos = -1;
    for(i = 1; i <= noduri; i++){
        if(costuri[i] < min && vizitat[i]==0)
        {
            min = costuri[i];
            minPos = i;
        }
    }
    return minPos;
}
void afiseaza(int nodcurent)
{
    if(nodcurent)
    {
        afiseaza(parinti[nodcurent]);
        printf("%d ", nodcurent);
    }
}
