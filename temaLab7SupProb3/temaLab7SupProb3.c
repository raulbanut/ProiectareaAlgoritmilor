/*Se da un graf neorientat. Sa se precizeze daca este conex sau nu.
*/
#include <stdio.h>
#include <stdlib.h>

typedef  struct lista
{
    int numar;
    struct lista *urmator;
} Lista;


void adaugare(Lista **prim,Lista **ultim,int numar)
{
    Lista *p;
    p=(Lista *)malloc(sizeof(Lista));
    p->numar=numar;
    if (*prim==0)
    {
        *prim=p;
        *ultim=p;
    }
    else
    {
        (*ultim)->urmator=p;
        *ultim=p;
    }
    p->urmator=0;
}


void stergere(Lista **prim,Lista **ultim)
{
    Lista *p;
    p=*prim;
    *prim=(*prim)->urmator;
    free(p);

}



int explorare_largime(int n,int matrice[20][20])
{
    int vizitate[20];
    Lista *prim,*ultim;
    int i,w,nod1;
    for (nod1=1; nod1<=n; nod1++)
    {
        prim=NULL;
        ultim=NULL;
        for (i=1; i<=n; i++)
            vizitate[i]=0;
        vizitate[nod1]=1;
        adaugare(&prim,&ultim,nod1);
        while( prim!=0 )
        {
            for (w=1; w<=n; w++)
                if ((matrice[prim->numar][w]==1) && (vizitate[w]==0))
                {
                    vizitate[w]=1;
                    adaugare(&prim,&ultim,w);

                }
            stergere(&prim,&ultim);
        }
        for (i=1; i<=n; i++)
            if (vizitate[i]==0)
                return 0;
    }
    return 1;
}


int main()
{
    FILE *f;
    int n,m,matrice[20][20],i,j,c;
    f=fopen("Graf","r");
    fscanf(f,"%d ",&n);
    fscanf(f,"%d ",&m);


    //initializam nul

    for (i=1; i<=n; i++)
    {

        for (j=1; j<=m; j++)
        {
            matrice[i][j]=0;
        }
    }
        //contruim matricea de adiacenta
        for (c=1; c<=m; c++)
        {
            fscanf(f,"%d",&i);
            fscanf(f,"%d",&j);
            matrice[i][j]=1;
            matrice[j][i]=1;
        }


        //afisare matrice de adiacenta
        for (i=1; i<=n; i++)
        {
            for (j=1; j<=m; j++)
                printf("%d ",matrice[i][j]);
            printf("\n");
        }

        if (explorare_largime(n,matrice)==1)
            printf("Este graf conex");
        else
            printf("Nu este graf conex");
        fclose(f);
        return 0;
    
}
