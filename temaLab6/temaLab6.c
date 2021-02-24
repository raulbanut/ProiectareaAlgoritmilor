/* temaDeCasa laboratorul6
 informatiile pentru medicamentele unei farmacii sunt:
 nume medicament, pret, cantitate, data primirii, data expirarii
 Evidenta se tine intr-un program care are drept structura de date un arbore de cautare dupa nume. Programul construieste de la inceput arborele prelucrand datele dintr-un fisier csv, datele sunt separate cu , . Datele se salveaza in fisierul listaMedicamente*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Date
{
    unsigned int Day, Month, Year;
}DATE;

struct medicamente
{
    char* Nume;
    float Pret;
    unsigned int Cantitate;
    DATE* Data_Primirii, * Data_Expirarii;
    struct medicamente* dreapta, * stanga;
};

char* separator(char source[])
{
    unsigned int i;
    for (i = 0; i < 128 && source[i] != ',' && source[i + 1] != ' ' && source[i] != '\n'; i++);
    char* cuv = (char*)calloc(i + 1, sizeof(char));
    strncpy(cuv, source, i);
    //strcat(cuv, '\0');
    strcpy(source, source + i + 2);
    return cuv;
}

DATE* Create_DATE(char In[9])
{
    DATE* NEW = (DATE*)malloc(sizeof(DATE));
    NEW->Day = (unsigned int)((In[0] - '0') * 10 + In[1] - '0');
    NEW->Month = (unsigned int)((In[2] - '0') * 10 + In[3] - '0');
    NEW->Year = (unsigned int)((In[4] - '0') * 1000 + (In[5] - '0') * 100 + (In[6] - '0') * 10 + In[7] - '0');
    return NEW;
}

void adaugare(char* Nume, float Pret, unsigned int Cantitate, DATE* DataIn, DATE* DataOut, struct medicamente** Nod)
{
    struct medicamente* NEW = (struct medicamente*)malloc(sizeof(struct medicamente));
    NEW->Cantitate = Cantitate;
    NEW->dreapta = NULL;
    NEW->stanga = NULL;
    NEW->Data_Expirarii = DataOut;
    NEW->Data_Primirii = DataIn;
    NEW->Nume = Nume;
    NEW->Pret = Pret;
    if (!*Nod)
    {
        *Nod = NEW;
        return;
    }
    else
    {
        struct medicamente* Current = *Nod;
        while (1)
        {
            if (strcmp(NEW->Nume, Current->Nume) < 0)
            {
                if (!Current->stanga) {
                    Current->stanga = NEW;
                    return;
                }
                else
                    Current = Current->stanga;
            }
            else
            {
                if (strcmp(NEW->Nume, Current->Nume) > 0)
                {
                    if (!Current->dreapta) {
                        Current->dreapta = NEW;
                        return;
                    }
                    else
                        Current = Current->dreapta;
                }
                else
                {
                    printf("Cheia deja exista\n");
                    free(NEW->Data_Expirarii);
                    free(NEW->Data_Primirii);
                    free(NEW);
                    return;
                }
            }
        }
    }
}

struct medicamente* cautare(struct medicamente* Nod, char Nume[], struct medicamente** Precedent, int* dir)
{
    if (!strcmp(Nod->Nume, Nume))
        return Nod;
    else
    {
        if (Precedent)
            *Precedent = Nod;
        if (strcmp(Nod->Nume, Nume) > 0)
        {
            if (!Nod->stanga) return NULL;
            else {
                if (Precedent)
                *dir = 1;
                return cautare(Nod->stanga, Nume, !Precedent ? NULL : Precedent, !Precedent ? NULL : dir);
            }
        }
        else
        {
            if (!Nod->dreapta) return NULL;
            else {
                if (Precedent)
                *dir = 2;
                return cautare(Nod->dreapta, Nume, !Precedent ? NULL : Precedent, !Precedent ? NULL : dir);
            }
        }
    }
}

void afisare(struct medicamente* Nod)
{
    if (Nod->stanga) afisare(Nod->stanga);
    printf("%s %.2f %d %d/%d/%d %d/%d/%d\n", Nod->Nume, Nod->Pret, Nod->Cantitate, Nod->Data_Primirii->Day, Nod->Data_Primirii->Month, Nod->Data_Primirii->Year, Nod->Data_Expirarii->Day, Nod->Data_Expirarii->Month, Nod->Data_Expirarii->Year);
    if (Nod->dreapta)  afisare(Nod->dreapta);
}

void salvare_iesire(struct medicamente* Nod, FILE* f)
{
    if (Nod->stanga) salvare_iesire(Nod->stanga, f);
    if (Nod->dreapta)  salvare_iesire(Nod->dreapta, f);
    fprintf(f, "%s, %.2f, %d, %d%d%d, %d%d%d\n", Nod->Nume, Nod->Pret, Nod->Cantitate, Nod->Data_Primirii->Day, Nod->Data_Primirii->Month, Nod->Data_Primirii->Year, Nod->Data_Expirarii->Day, Nod->Data_Expirarii->Month, Nod->Data_Expirarii->Year);
    free(Nod->Data_Primirii);
    free(Nod->Data_Expirarii);
    free(Nod);
}

void elimina(struct medicamente** Nod, char Nume[30])
{
    struct medicamente* precedent;
    int dir = 0;
    if (!strcmp((*Nod)->Nume, Nume))
    {
        if (!(*Nod)->stanga && !(*Nod)->dreapta)
        {
            free((*Nod)->Data_Expirarii);
            free((*Nod)->Data_Primirii);
            free(*Nod);
            *Nod = NULL;
        }
        else
            if (!(*Nod)->stanga && (*Nod)->dreapta)
            {
                struct medicamente* aux = *Nod;
                *Nod = (*Nod)->dreapta;
                free(aux->Data_Expirarii);
                free(aux->Data_Primirii);
                free(aux);
            }
            else
                if ((*Nod)->stanga && !(*Nod)->dreapta)
                {
                    struct medicamente* aux = *Nod;
                    *Nod = (*Nod)->stanga;
                    free(aux->Data_Expirarii);
                    free(aux->Data_Primirii);
                    free(aux);
                }
                else
                {
                    struct medicamente* replace, * aux_replace;
                    struct medicamente* aux = *Nod;
                    replace = (*Nod)->dreapta;
                    aux_replace = *Nod;
                    while (replace->stanga)
                    {
                        aux_replace = replace;
                        replace = replace->stanga;
                    }
                    if (aux_replace != *Nod)
                    {
                        aux_replace->stanga = replace->dreapta;
                        replace->dreapta = (*Nod)->dreapta;
                    }
                    replace->stanga = (*Nod)->stanga;
                    (*Nod) = replace;
                    free(aux->Data_Expirarii);
                    free(aux->Data_Primirii);
                    free(aux);
                }
    }
    else
    {
        struct medicamente* found = cautare(*Nod, Nume, &precedent, &dir);
        if (!found) {
            printf("Medicamentul nu a fost gasit\n");
            return;
        }
        else
        {
            if (!found->dreapta && !found->stanga)
            {
                switch (dir)
                {
                case 1:
                    precedent->stanga = NULL;
                    break;
                case 2:
                    precedent->dreapta = NULL;
                    break;
                }
                free(found->Data_Expirarii);
                free(found->Data_Primirii);
                free(found);
            }
            else
            {
                if (!found->dreapta && found->stanga)
                {
                    struct medicamente* aux = found;
                    switch (dir)
                    {
                    case 1:
                        precedent->stanga = found->stanga;
                        break;
                    case 2:
                        precedent->dreapta = found->stanga;
                        break;
                    }
                    free(aux->Data_Expirarii);
                    free(aux->Data_Primirii);
                    free(aux);
                }
                else
                {
                    if (found->dreapta && !found->stanga)
                    {
                        struct medicamente* aux = found;
                        switch (dir)
                        {
                        case 1:
                            precedent->stanga = found->dreapta;
                            break;
                        case 2:
                            precedent->dreapta = found->dreapta;
                            break;
                        }
                        free(aux->Data_Expirarii);
                        free(aux->Data_Primirii);
                        free(aux);
                    }
                    else
                    {
                        struct medicamente* replace, * aux_replace;
                        replace = found->dreapta;
                        aux_replace = found;
                        while (replace->stanga)
                        {
                            aux_replace = replace;
                            replace = replace->stanga;
                        }
                        if (aux_replace != found)
                        {
                            aux_replace->stanga = replace->dreapta;
                            replace->dreapta = found->dreapta;
                        }
                        replace->stanga = found->stanga;
                        switch (dir)
                        {
                        case 1:
                            precedent->stanga = replace;
                            break;
                        case 2:
                            precedent->dreapta = replace;
                            break;
                        }
                        free(found->Data_Expirarii);
                        free(found->Data_Primirii);
                        free(found);
                    }
                }
            }
        }
    }
}

//fctia returneaza -1  daca d1<d2 0 daca sunt egale 1 daca d1>d2
int comparare_data(DATE d1, DATE d2)
{
    if (d1.Year > d2.Year)
        return 1;
    else {
        if (d1.Year < d2.Year)
            return -1;
        else {
            if (d1.Month > d2.Month)
                return 1;
            else {
                if (d1.Month < d2.Month)
                    return -1;
                else {
                    if (d1.Day > d2.Day)
                        return 1;
                    else {
                        if (d2.Day < d2.Day)
                            return -1;
                        else
                            return 0;
                    }
                }
            }
        }
    }
}

void creare_dupa_data(struct medicamente** Arbore_nou, DATE data, struct medicamente* Arborele_initial)
{
    if (!Arborele_initial)
        return;
    else
    {
        creare_dupa_data(Arbore_nou, data, Arborele_initial->stanga);
        creare_dupa_data(Arbore_nou, data, Arborele_initial->dreapta);
        if (comparare_data(*(Arborele_initial->Data_Expirarii), data) > 0)
            adaugare(Arborele_initial->Nume, Arborele_initial->Pret, Arborele_initial->Cantitate, Arborele_initial->Data_Primirii, Arborele_initial->Data_Expirarii, Arbore_nou);
    }
}

void Main_Menu(struct medicamente** Nod)
{
    printf("Medicamentele au fost incarcate cu success!\n");
    for (;;)
    {
        int optiune;
        fflush(stdin);
        printf("1-Cautare medicament 2-Afisare medicamente 3-Elimina medicament 4-Salvare si iesire 5-Arbore cu data mai veche: ");
        scanf("%d", &optiune);
        system("cls");
        switch (optiune)
        {
        case 1:
        {
            char med[30];
            printf("Introduceti numele medicamentului dorit: ");
            scanf("%s", med);
            struct medicamente* found = cautare(*Nod, med, NULL, NULL);
            if (!found)
                printf("Medicamentul nu a fost gasit\n");
            else
            {
                printf("Medicamentul a fost gasit.\nIntroduceti pretul: ");
                scanf("%f", &found->Pret);
            }
            break;
        }
        case 2:
            afisare(*Nod);
            printf("\n");
            break;
        case 3:
        {
            char med[30];
            printf("Introduceti numele medicamentului dorit: ");
            scanf("%s", med);
            elimina(Nod, med);
            break;
        }
        case 4:
        {
            FILE* f = fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator6/temaLab6/temaLab6/listaMedicamente", "w");
            salvare_iesire(*Nod, f);
            printf("Medicamentele au fost salvate cu success in fisierul listaMedicamente.txt");
            fclose(f);
            exit(0);
            break;
        }
        case 5:
        {
            DATE* data_expirare = (DATE*)malloc(sizeof(DATE));
            printf("Introduceti data zz ll aaaa: ");
            scanf("%d %d %d", &data_expirare->Day, &data_expirare->Month, &data_expirare->Year);
            struct medicamente* DupaData = NULL;
            creare_dupa_data(&DupaData, *data_expirare, *Nod);
            afisare(DupaData);
            printf("\n");
            break;
        }
        default:
            printf("Optiunea selectata nu exista!\n");
            break;
        }
    }
}

int main()
{
    struct medicamente* farmacie = NULL;
    FILE* f = fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator6/temaLab6/temaLab6/listaMedicamente", "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului 'listaMedicamente'!");
        exit(1);
    }
    else
    {
        char buff[129];
        while (fgets(buff, 128, f)) {
            char* nume_aux;
            float pret_aux;
            unsigned int cantitate_aux;
            char data1[9], data2[9];
            nume_aux = separator(buff);
            pret_aux = (float)atof(separator(buff));
            cantitate_aux = (unsigned int)atoi(separator(buff));
            strcpy(data1, separator(buff));
            strcpy(data2, separator(buff));
            adaugare(nume_aux, pret_aux, cantitate_aux, Create_DATE(data1), Create_DATE(data2), &farmacie);
        }
        fclose(f);
        Main_Menu(&farmacie);
    }
    return 0;
}
