/* TemaDeCasa Laboratorul 4
 In fisierul Medicamente se pastreaza sub forma CSV informatiile pentru o farmacie.
 nume medicament, pret, cantitate, data primirii, data expirarii
 Trebuie sa creezi o lista dublu inlantuita ordonata crescator dupa numele medicamentului
 iar daca este acelasi nume trebuie ordonata descrescator dupa pret*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declararea structurii de medicament
struct medicamente
{
    char *nume;
    float pret;
    unsigned int cantitate;
    char dataPrimire[9], dataExpirare[9];
    struct medicamente *urm,*pre;
};





// declararea functiilor pe care le-am utilizat
void adaugaMedicament(char *nume,float pret,unsigned int cantitate, char dataPrimire[9],char dataExpirare[9], struct medicamente **lista);
char *separate(char sursa[]);
void creeazaMeniu(struct medicamente **lista);
void ordonare(struct medicamente **lista);
struct medicamente *cautare(char cuvant[],float pret,struct medicamente *lista);
void modificare(struct medicamente *pos, char dataPrimirii[], char dataExpirarii[], unsigned int cantitate);
void afisare(struct medicamente *lista);
struct medicamente *stergeMedicament(struct medicamente *lista);
void salveazaIesi(struct medicamente **lista);



/*MAIN**/

int main() {
// lista unde stochez medicamentele
    struct medicamente *farmacie=NULL;
// in urmatoarele instructiuni deschid fisierul si verific daca s-a reusit sau nu deschiderea
//    FILE *f=fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator4/temaLab4/temaLab4/Medicamente", "r");
    FILE *f = fopen("Medicamente", "r");
    if (!f)
    {
        printf("eroare la deschiderea fisierului 'medicamente.txt'.");
        exit(1);
    }
    else
    {
// daca s-a reusit deschiderea se vor apela urmatoarele instructiuni
// voi lua pe rand randurile din fisier si le voi adauga intr-o lista de medicamente declarata farmacie
        char aux[129];
        while(fgets(aux,128,f))
        {
            // am declarat un aux cu care voi prelua datele de pe randuri
            char *auxNume;
            unsigned int auxCantitate;
            float auxPret;
            char auxDataExpirare[9],auxDataPrimire[9];
            auxNume = separate(aux); // apelez la functia creata de separere
            auxPret=(float)atof(separate(aux));
            auxCantitate=(unsigned int)atoi(separate(aux));
            strcpy(auxDataPrimire, separate(aux));
            strcpy(auxDataExpirare, separate(aux));
            adaugaMedicament(auxNume,auxPret,auxCantitate,auxDataPrimire,auxDataExpirare,&farmacie);
        }
        fclose(f);
        ordonare(&farmacie);
        creeazaMeniu(&farmacie);
    }
    return 0;
}




/*FUNCTII*/

char *separate(char sursa[]){
// functia utilizata pentru a separa numele medicamentelor
    unsigned int i;
    for (i=0; i<129 && sursa[i] != ',' && sursa[i] != '\n'; i++);
    char *cuvant=(char *)calloc(i+2, sizeof(char));
    strncpy(cuvant,sursa,i);
    memmove(sursa, sursa+i+1, strlen(sursa) - i);
    return cuvant;
}

struct medicamente *cautare(char cuvant[],float pret,struct medicamente *lista)
{
    struct medicamente *pos=lista;
    while (pos)
    {
        if(!strcmp(cuvant, pos->nume) && pret==pos->pret)
        {
            return pos;
        }
        pos=pos->urm;
    }
    return NULL;
}


void modificare(struct medicamente *pos, char dataPrimirii[], char dataExpirarii[], unsigned int cantitate)
{
    pos->cantitate=cantitate;
    strcpy(pos->dataPrimire, dataPrimirii);
    strcpy(pos->dataExpirare, dataExpirarii);
}


struct medicamente *stergeMedicament(struct medicamente *lista)
{
// eliminam un anumit medicament
    if (!lista->pre&&!lista->urm)
    {
        free(lista);
        return NULL;
    }
    else
    {
        if (!lista->pre)
        {
            lista = lista->urm;
            free(lista->pre);
            lista->pre = NULL;
            return lista;
        }
        else
        {
            if (!lista->urm)
            {
                lista = lista->pre;
                free(lista->urm);
                lista->urm = NULL;
                return NULL;
            }
            else
            {
                (lista->urm)->pre = lista->pre;
                (lista->pre)->urm = lista->urm;
                free(lista);
                return NULL;
            }
        }
    }
}

void salveazaIesi(struct medicamente **lista)
{
// salvam lista in medicamente.txt
    struct medicamente *pozitie= *lista;
//    FILE *f = fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator4/temaLab4/temaLab4/Medicamente", "w");
    FILE *f = fopen("Medicamente", "w");
    while (pozitie)
    {
        fprintf(f,"%s,%f,%d,%s,%s\n", pozitie->nume, pozitie->pret, pozitie->cantitate, pozitie->dataPrimire, pozitie->dataExpirare);
        struct medicamente *aux=pozitie;
        pozitie = pozitie->urm;
        free(aux);
    }
    printf("Medicamentele au fost salvate cu success in fisierul Medicamente");
    fclose(f);
    exit(0);
}
void creeazaMeniu(struct medicamente **lista)
{
// utilizez functia pentru a creea afisarea sub forma de meniu
    for(;;)
    {
        unsigned int optiune;
        fflush(stdin);
        printf("1 Cauta medicament, 2 Afiseaza medicamente, 3 Elimina medicament, 4 Salvare+Iesire =  ");
        scanf("%d",&optiune);
        printf("\n");
        switch (optiune) {
            case 1:
            {
                char med[30];
                float pret;
                printf("Introduceti numele medicamentului dorit: ");
                scanf("%s", med);
                printf("Introduceti pretul: ");
                scanf("%f", &pret);
                struct medicamente *found=cautare(med,pret,*lista);
                // introducem datele pentru medicament, pe urma il cautam in lista utilizand functia de cautare
                if (!found)
                {
                    printf("Medicamentul cu numele dat nu se gaseste in lista\n");
                }
                else
                {
                    char dataPrimirii[9],dataExpirarii[9];
                    unsigned int cantitate;
                    printf("Medicamentul introdus a fost gasit in lista\n");
                    printf("\nIntroduceti cantitatea = ");
                    scanf("%d",&cantitate);
                    printf("\nIntroduceti data primirii = ");
                    scanf("%s",dataPrimirii);
                    printf("\nIntroduceti data expirarii = ");
                    scanf("%s",dataExpirarii);
                    modificare(found,dataPrimirii,dataExpirarii,cantitate);
                }
                break;
            }
            case 2:
            {
                afisare(*lista);
                break;
            }
            case 3:
            {
                char medicament[50];
                float pret;
                printf("\nIntroduceti numele medicamentul pentru eliminat = ");
                scanf("%s",medicament);
                printf("\nIntroduceti pretul = ");
                scanf("%f",&pret);
// aici caut medicamentul dupa numele si pretul dat
                struct medicamente *cautat=cautare(medicament, pret, *lista);
                if(!cautat)
                {
                    printf("nu s-a gasit medicamentul\n");
                }
                else
                {
                    cautat=stergeMedicament(cautat);
                    if(cautat)
                    {
                        *lista=cautat;
                        printf("Medicamentul a fost eliminat\n");
                    }
                }
                break;
            }
            case 4:
            {
                salveazaIesi(lista);
                break;
            }
            default:
            {
                printf("Optiunea nu exista\n");
                break;
            }
        }
    }
}


void ordonare(struct medicamente **lista)
{
// in functia asta ordonez lista
    if (!(*lista)->urm)
        return;
    struct medicamente *pozitia1, *pozitia2;
    char ok = 0;
    while (!ok)
    {
        ok = 1;
        pozitia1 = *lista;
        pozitia2 = pozitia1->urm;
        while (pozitia2)
        {
            if (strcmp(pozitia1->nume, pozitia2->nume) > 0 || (strcmp(pozitia1->nume, pozitia2->nume) == 0 && pozitia1->pret < pozitia2->pret))
            {
                if (!pozitia1->pre && !pozitia2->urm)
                {
                    pozitia2->pre = NULL;
                    pozitia2->urm = pozitia1;
                    pozitia1->urm = NULL;
                    pozitia1->pre = pozitia2;
                    ok = 0;
                }
                else
                {
                    if (!pozitia1->pre)
                    {
                        struct medicamente *aux;
                        aux = pozitia2->urm;
                        pozitia2->urm = pozitia1;
                        pozitia1->urm = aux;
                        pozitia2->pre = NULL;
                        pozitia1->pre = pozitia2;
                        (pozitia1->urm)->pre = pozitia1;
                        ok = 0;
                    }
                    else
                        if (!pozitia2->urm)
                        {
                            struct medicamente *aux;
                            aux = pozitia1->pre;
                            pozitia1->urm = NULL;
                            pozitia1->pre = pozitia2;
                            pozitia2->urm = pozitia1;
                            pozitia2->pre = aux;
                            (pozitia2->pre)->urm = pozitia2;
                            ok = 0;
                        }
                        else
                        {
                            struct medicamente *aux = pozitia2->urm;
                            (pozitia1->pre)->urm = pozitia2;
                            pozitia2->pre = pozitia1->pre;
                            pozitia2->urm = pozitia1;
                            pozitia1->pre = pozitia2;
                            pozitia1->urm = aux;
                            (pozitia1->urm)->pre = pozitia1;
                            ok = 0;
                        }
                }
                if ((*lista)->pre)
                    *lista = (*lista)->pre;
                struct medicamente *aux = pozitia1;
                pozitia1 = pozitia2;
                pozitia2 = aux;
            }
            pozitia1 = pozitia1->urm;
            pozitia2 = pozitia2->urm;
        }
    }
}

void afisare(struct medicamente *lista)
{
// in functia asta afisez lista
    struct medicamente *pos=lista;
    while(pos)
    {
        printf("%s:\n ->costa %.2f\n ->cantitatea %d\n ->data primirii %s\n ->data expirarii %s\n",pos->nume,pos->pret,pos->cantitate,pos->dataPrimire,pos->dataExpirare);
        pos=pos->urm;
    }
}

void adaugaMedicament(char *nume,float pret,unsigned int cantitate, char dataPrimire[9],char dataExpirare[9], struct medicamente **lista)
{
// functia utilizata pentru a adauga medicamente in lista farmacie
    if (!*lista)
    {
// daca lista e goala o umplem asa
        struct medicamente *nouaLista=(struct medicamente*)malloc(sizeof(struct medicamente));
        nouaLista->nume=nume;
        nouaLista->pret=pret;
        nouaLista->cantitate=cantitate;
        strcpy(nouaLista->dataPrimire, dataPrimire);
        strcpy(nouaLista->dataExpirare, dataExpirare);
        nouaLista->pre=NULL;
        nouaLista->urm=NULL;
        *lista = nouaLista;
    }
    else
    {
// daca nu e goala adaugam medicamentele asa, se adauga in fata
        struct medicamente *nouaLista=(struct medicamente*)malloc(sizeof(struct medicamente));
        nouaLista->nume=nume;
        nouaLista->pret=pret;
        nouaLista->cantitate=cantitate;
        strcpy(nouaLista->dataPrimire, dataPrimire);
        strcpy(nouaLista->dataExpirare, dataExpirare);
        nouaLista->urm=*lista;
        (*lista)->pre=nouaLista;
        nouaLista->pre=NULL;
        *lista=nouaLista;
    }
}

