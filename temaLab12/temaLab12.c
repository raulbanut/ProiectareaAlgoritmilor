/* Jocul Persico. Sa se aranjeze pietrele in ordine pe o tabla ce contine 15 pietre numerotate de la 1 la 15 */



#include <stdio.h>
#include <stdlib.h>
typedef struct nod{
                  int m[20][20];
                  int cost,n;
                  struct nod *urm;
                  }TIP_NOD;

typedef struct lista{
               TIP_NOD *nod;
               struct lista *urm;
                    }LISTA;




void pop(LISTA **prim, LISTA **ultim,TIP_NOD *p)
{
    LISTA *q;
    q=(LISTA *)malloc(sizeof(LISTA));
    q->nod=p;
    q->urm=0;
    if (*prim==0)
    {
        *prim=q;
        *ultim=q;
    }
    else
    {
        (*ultim)->urm=q;
        *ultim=q;
    }
}

int cost(TIP_NOD *p)
{
    int i,j,k,n;
    n=p->n;
    k=0;
    for (i=1;i<=p->n;i++)
       for (j=1;j<=p->n;j++)
          if (p->m[i][j]!=(i-1)*n+j) k=k+1;
    return k;
}

int main()
{
    TIP_NOD *rad;
    FILE *f;
    int i,j,k,x,y,n,aux,minim;
    TIP_NOD *p,*pp,*q;
    LISTA *prim, *ultim, *cur;

    prim=0;
    ultim=0;
    rad=(TIP_NOD *)malloc(sizeof(TIP_NOD));
    f=fopen("temaLab12date","r");
    fscanf(f,"%d",&rad->n);
    for (i=1;i<=rad->n;i++)
       for (j=1;j<=rad->n;j++)
           fscanf(f,"%d",&rad->m[i][j]);
    rad->cost=cost(rad);
  while (rad->cost!=1) {


      p=rad;
    n=p->n;
    x=0;
    y=0;
    for (i=1;i<=n;i++)
       for (j=1;j<=n;j++)
          if (p->m[i][j]==(-1)) {
              x=i;
              y=j;
                              }
    pp=(TIP_NOD *)malloc(sizeof(TIP_NOD));
    for (i=1;i<=n;i++)
       for (j=1;j<=n;j++)
          pp->m[i][j]=p->m[i][j];
    pp->n=n;
    if (x!=1) {
               pp->m[x][y]=pp->m[x-1][y];
               pp->m[x-1][y]=-1;
               pop(&prim,&ultim,pp);
              }

    pp=(TIP_NOD *)malloc(sizeof(TIP_NOD));
    for (i=1;i<=n;i++)
       for (j=1;j<=n;j++)
          pp->m[i][j]=p->m[i][j];

    pp->n=n;
    if (y!=1){
               pp->m[x][y]=pp->m[x][y-1];
               pp->m[x][y-1]=-1;
               pop(&prim,&ultim,pp);
             }

    pp=(TIP_NOD *)malloc(sizeof(TIP_NOD));
    for (i=1;i<=n;i++)
       for (j=1;j<=n;j++)
          pp->m[i][j]=p->m[i][j];
    pp->n=n;
    if (x!=n) {
               pp->m[x][y]=pp->m[x+1][y];
               pp->m[x+1][y]=-1;
               pop(&prim,&ultim,pp);
              }

    pp=(TIP_NOD *)malloc(sizeof(TIP_NOD));
    for (i=1;i<=n;i++)
       for (j=1;j<=n;j++)
          pp->m[i][j]=p->m[i][j];
    pp->n=n;
    if (y!=1){
               pp->m[x][y]=pp->m[x][y+1];
               pp->m[x][y+1]=-1;
               pop(&prim,&ultim,pp);
             }

    cur=prim;
    minim=n*n+1;
    while (cur!=0)
    {
       k=cost(cur->nod);
       if (k<minim) {
            q=cur->nod;
            minim=k;
            q->cost=k;
                   }
       cur=cur->urm;

    }
     for (i=1;i<=n;i++){
       for (j=1;j<=n;j++)
          printf("%3d ",q->m[i][j]);
       printf("\n");
  }
   rad=q;
   printf("\n");

  }    return 0;

}
