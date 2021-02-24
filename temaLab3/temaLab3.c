/* temaLab3
 Se va realiza problema de la laboratorul 1 sub forma de lista de tip COADA, suprapusa si cu fisier pentru salvarea datelor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct locomotiva
{
      unsigned int id;
      char *tip;
      float greutate;
      struct locomotiva *urm;
} LOCOMOTIVA;

typedef struct depou
{
    LOCOMOTIVA *prim,*ultim,*curent;
    unsigned int dimensiune;
} DEPOU;


void intrare(DEPOU *d);
void iesire(DEPOU *d);
void iesireLaInceput(DEPOU *d);
void afisare(DEPOU *d);
void populare(DEPOU**d);
void salvare(DEPOU *d);
DEPOU *anterior(DEPOU *d);

int main() {
    unsigned int optiune;
    DEPOU *d;
    populare(&d);
    iesireLaInceput(d);
    while(1)
    {
        printf("1 intrare, 2 iesire, 3 afisare, 4 terminare = ");
        scanf("%d",&optiune);
        switch (optiune) {
            case 1:
            {
                intrare(d);
                break;
            }
            case 2:
            {
                iesire(d);
                break;
            }
            case 3:
            {
                if(d->dimensiune==0){
                    printf("Depoul este gol...\n");
                }
                else {
                    afisare(d);
                    printf("\n");
                }
                break;
            }
            case 4:
            {
                printf("La revedere\n");
                salvare(d);
                return 0;
            }
            default:
            {
                printf("Optiune gresita...\n");
                break;
            }
        }
    }
    return 0;
}
             
void intrare(DEPOU *d)
{
    char buf[100];
    d->curent = (LOCOMOTIVA *)malloc(sizeof(LOCOMOTIVA));
    printf("introduceti id = ");
    scanf("%d", &((d->curent)->id));
    printf("introduceti tip = ");
    scanf("%s", buf);
    (d->curent)->tip = (char*)malloc((strlen(buf) + 1) * sizeof(char));
    strcpy((d->curent)->tip, buf);
    printf("introduceti greutate = ");
    scanf("%f", &((d->curent)->greutate));
    d->dimensiune++;
    if (d->prim == NULL)
    {
        (d->curent)->urm = 0;
        d->prim = d->ultim = d->curent;
    }
    else
    {
        (d->curent)->urm = d->prim;
        d->prim = d->curent;
    }
}

void iesire(DEPOU *d)
{
    if(!d->ultim){
        return;
    }
    if(d->ultim==d->prim)
    {
        printf("locomotiva care iese are urmatoarele detalii:\n id : %d\n tip : %s\ngreutate : %f\n\n", (d->ultim)->id, (d->ultim)->tip, (d->ultim)->greutate);
        free(d->ultim);
        d->prim=NULL;
        d->ultim=NULL;
        d->dimensiune=0;
    }
    else
    {
        d->curent = d->prim;
        while(((d->curent)->urm)->urm){d->curent=(d->curent)->urm;}
        printf("locomotiva care iese are urmatoarele detalii:\n id : %d\n tip : %s\ngreutate : %f\n\n", (d->curent)->urm->id, (d->curent)->urm->tip, (d->curent)->urm->greutate);
        d->ultim=d->curent;
        (d->ultim)->urm=NULL;
        d->dimensiune--;
        free((d->curent)->urm);
    }
}
void iesireLaInceput(DEPOU *d){
    if(!d->ultim){
            return;
        }
        if(d->ultim==d->prim)
        {
            free(d->ultim);
            d->prim=NULL;
            d->ultim=NULL;
            d->dimensiune=0;
        }
        else
        {
            d->curent = d->prim;
            while(((d->curent)->urm)->urm){d->curent=(d->curent)->urm;}
            d->ultim=d->curent;
            (d->ultim)->urm=NULL;
            d->dimensiune--;
            free((d->curent)->urm);
        }
}

void afisare(DEPOU *d)
{
    int i=0;
    d->curent=d->prim;
    while(d->curent)
    {
        i++;
        printf("locomotiva %d are urmatoarele detalii : \n id : %d\n tip : %s \n greutate : %.2f\n\n",i,d->curent->id,d->curent->tip,d->curent->greutate);
        d->curent=d->curent->urm;
    }
}

void populare(DEPOU **d)
{
    *d=(DEPOU *)malloc(sizeof(DEPOU));
    (*d)->prim=(*d)->ultim=NULL;
    (*d)->dimensiune=0;
//    FILE *f=fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator3/temaLab3/temaLab3/Depou","r");
    FILE *f=fopen("Depou","r");
    if (!f) return;
    
    char buf[100];
    while(!feof(f))
    {
        (*d)->curent=(LOCOMOTIVA *)malloc(sizeof(LOCOMOTIVA));
        fscanf(f, "%d",&((*d)->curent->id));
        fscanf(f, "%s",buf);
        (*d)->curent->tip=(char*)malloc((strlen(buf)+1)*sizeof(char));
        strcpy((*d)->curent->tip, buf);
        fscanf(f, "%f",&((*d)->curent->greutate));
        (*d)->dimensiune++;
        
        (*d)->curent->urm=0;
        if((*d)->prim==NULL)
        {
            (*d)->prim=(*d)->ultim=(*d)->curent;
        }
        else
        {
            (*d)->ultim->urm=(*d)->curent;
            (*d)->ultim=(*d)->curent;
        }
    }
    fclose(f);
}

void salvare(DEPOU *d)
{
//    FILE *f=fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator3/temaLab3/temaLab3/Depou", "w");
    FILE *f=fopen("Depou","w");
    if(!f) return;
    
    d->curent=d->prim;
    while(d->curent)
    {
        fprintf(f, "%d %s %.2f\n",d->curent->id,d->curent->tip,d->curent->greutate);
        d->curent=d->curent->urm;
    }
    fclose(f);
}
//void intrare(FILE *f, int numarCitiri)
//{
//    struct locomotiva * p=(struct locomotiva *)malloc(sizeof(struct locomotiva));
//    fscanf(f, "%d %s %f",&p->Id,p->Tip,&p->Greutate);
//    printf(" Locomotiva 1 este cu id: %d de tip %s cu greutatea %.2f\n",p->Id,p->Tip,p->Greutate);
////    for(int i=0;i<numarCitiri;i++)
////    {
////
////    }
//    free(p);
//}


DEPOU *anterior(DEPOU *d)
{
    d->curent = d->prim;
    while ((d->curent)->urm != d->ultim)
        d->curent = (d->curent)->urm;
    return d->curent;
}


