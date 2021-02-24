//
//  main.c
//  temaDeCasa
/*  Se doreste rezolvarea problemei de la primul laborator sub forma unei liste de tip Coada.
 */

#include <stdio.h>
#include <stdlib.h>

struct locomotiva
{
      int Id;
      char Tip[21];
      float Greutate;
      struct locomotiva *urm;
};


void intrare(struct locomotiva **prim,struct locomotiva **ultim);
unsigned int iesire(struct locomotiva *prim,struct locomotiva *ultim);
void afisare(struct locomotiva *prim);

int main() {
    int optiune;
    struct locomotiva *primul = 0;
    struct locomotiva *ultimul = 0;
    while (1)
    {
        printf("1 intrare, 2 iesire, 3 afisare, 4 oprire = ");
        scanf("%d",&optiune);
        switch (optiune) {
            case 1:
            {
                intrare(&primul, &ultimul);
                break;
            }
            case 2:
            {
                if (!iesire(primul, ultimul))
                {
                    primul=NULL;
                };
                break;
            }
            case 3:
            {
                if (primul==0){printf("Depoul este gol\n");}
                else afisare(primul);
                break;
            }
            case 4:
            {
                printf("La revedere... \n");
                return 0;
            }
            default:
            {
                printf("Optiune gresita ... \n");
                break;
            }
        }
    }
    return 0;
}

void intrare(struct locomotiva **prim, struct locomotiva **ultim){
    struct locomotiva * p=(struct locomotiva *)malloc(sizeof(struct locomotiva));
    printf("Introduceți Id = ");
    scanf("%d",&p->Id);
    printf("Introduceți Tip = ");
    scanf("%s", p->Tip);
    printf("Introduceți Greutate = ");
    scanf("%f", &p->Greutate);
    if (*prim==NULL){
        p->urm=NULL;
        *prim=*ultim=p;
    }
    else
    {
        p->urm=*prim;
        *prim=p;
    }
}


unsigned int iesire(struct locomotiva *prim,struct locomotiva *ultim){
    if(!prim){
        printf("Depoul este gol\n");
        return 1;
    }
    if (!prim->urm)
    {
        printf("Locomotiva cu ID: %d, Tip %s, Greutate %.2f, a iesit!\n",prim->Id,prim->Tip,prim->Greutate);
        free(prim);
        return 0;
    }
    else
    {
        while((prim->urm)->urm) prim=prim->urm;
        printf("Locomotica cu ID: %d, Tip %s, Greutate %.2f, a iesit!\n",(prim->urm)->Id,(prim->urm)->Tip,(prim->urm)->Greutate);
        free(prim->urm);
        prim->urm=NULL;
        return 1;
    }
}

void afisare(struct locomotiva *prim){
    while(prim)
    {
        printf("In depou se afla locomotiva cu \nid: %d  |  tip:  %s  |   greutatea: %.2f\n",prim->Id,prim->Tip,prim->Greutate);
        prim=prim->urm;
    }
}
