/* Sa se implementeze algoritmi prezentati tabelelor de dispersie. Se da un fisier in care este trecut numele, prenumele si media. Cheia este numele si prenumele. Se va crea un meniu pentru adaugare/stergere/modificare ...
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define m 11

typedef struct student
{
    char* nume, * prenume;
    float media;
    struct student* next;
}student;

char* Separator(char buf[])
{
    unsigned int i;
    for (i = 0; i < strlen(buf) && buf[i] != ',' && buf[i + 1] != ' ' && buf[i] != '\n'; i++);
    char* nou = (char*)malloc((sizeof(char) * i) + 1);
    strncpy(nou, buf, i);
    nou[i] = '\0';
    if (i < strlen(buf) - 2)
        strcpy(buf, buf + i + 2);
    return nou;
}

unsigned int f_hash(unsigned int size1, unsigned int size2)
{
    return ((size1 % m) + (size2 % m)) % m;
}

unsigned int char_sum(char* C)
{
    unsigned int i, sum = 0;
    for (i = 0; i < strlen(C); i++)
        sum += C[i];
    return sum;
}

void adauga(char* nume, char* prenume, float media, student** Stud)
{
    unsigned int poz = f_hash(char_sum(nume), char_sum(prenume));
    if (!(*Stud + poz)->nume)
    {
        (*Stud + poz)->nume = nume;
        (*Stud + poz)->prenume = prenume;
        (*Stud)[poz].media = media;
        (*Stud + poz)->next = NULL;
    }
    else
    {
        student* cap = (*Stud + poz);
        student* nou = (student*)malloc(sizeof(student));
        nou->next = NULL;
        nou->nume = nume;
        nou->prenume = prenume;
        nou->media = media;
        while (cap->next) cap = cap->next;
        cap->next = nou;
    }
}

void Citire(FILE* f, student** Stud)
{
    char buf[256];
    while (fgets(buf, 256, f))
    {
        char* N = Separator(buf);
        char* P = Separator(buf);
        float M = (float)atof(Separator(buf));
        adauga(N, P, M, Stud);
    }
}

void free_stud(student* Stud, unsigned int poz, FILE* f)
{
    fprintf(f, "%s, %s, %.2f\n", (Stud + poz)->nume, (Stud + poz)->prenume, (Stud + poz)->media);
    free((Stud + poz)->nume);
    free((Stud + poz)->prenume);
}

void save_and_exit(student* Stud, FILE* f)
{
    unsigned int i;
    for (i = 0; i < m; i++)
    {
        if ((Stud + i)->nume)
        {
            if (!((Stud + i)->next))
                free_stud(Stud, i, f);
            else
            {
                student* cap = Stud + i;
                while (cap)
                {
                    student* aux = cap;
                    cap = cap->next;
                    free_stud(aux, 0, f);
                }
            }
        }
    }
    free(Stud);
}

student* cautare(char* nume, char* prenume, student* Stud, student** for_delete)
{
    unsigned int poz = f_hash(char_sum(nume), char_sum(prenume));
    if (for_delete)*for_delete = NULL;
    if (!(Stud + poz)->nume) return NULL;
    else
    {
        student* cap = Stud + poz;
        while (cap) {
            if (!strcmp(cap->nume, nume) && !strcmp(cap->prenume, prenume))
                return cap;
            else
            {
                if (for_delete)*for_delete = cap;
                cap = cap->next;
            }
        }
        return NULL;
    }
}

void Read_Keyboard(char** N, char** P, float* Media)
{
    char buf[128];
    printf("Introduceti numele studentului: ");
    scanf(" %s", buf);
    *N = Separator(buf);
    printf("Introduceti prenumele studentului: ");
    scanf(" %s", buf);
    *P = Separator(buf);
    if (Media)
    {
        printf("Introduceti media studentului: ");
        scanf(" %f", Media);
    }
}

void main_menu(student* Studenti)
{
    char optiune;
    while (1)
    {
        printf("Introduceti 1-Adaugare; 2-Afisare; 3-Modificare; 4-Stergere; 5-Iesire\n");
        scanf(" %c", &optiune);
        system("cls");
        switch (optiune)
        {
        case '1':
        {
            char* nume, * prenume;
            float media;
            Read_Keyboard(&nume, &prenume, &media);
            adauga(nume, prenume, media, &Studenti);
            printf("Studentul a fost adaugat cu success\n");
            break;
        }
        case '2':
        {
            char* nume, * prenume;
            Read_Keyboard(&nume, &prenume, NULL);
            student* caut = cautare(nume, prenume, Studenti, NULL);
            if (!caut)
                printf("Studentul nu a fost gasit\n");
            else
                printf("%s, %s, %.2f\n", caut->nume, caut->prenume, caut->media);

            break;
        }
        case '3':
        {
            char* nume, * prenume;
            Read_Keyboard(&nume, &prenume, NULL);
            student* caut = cautare(nume, prenume, Studenti, NULL);
            if (!caut)
                printf("Studentul nu a fost gasit\n");
            else
            {
                printf("Studentul a fost gasit\nIntroduceti datele pentru a fi modificate\n");
                float media;
                Read_Keyboard(&nume, &prenume, &media);
                free(caut->nume); caut->nume = nume;
                free(caut->prenume); caut->prenume = prenume;
                caut->media = media;
            }

            break;
        }
        case '4':
        {
            char* nume, * prenume;
            Read_Keyboard(&nume, &prenume, NULL);
            student* precedent, * caut = cautare(nume, prenume, Studenti, &precedent);
            if (!caut)
                printf("Studentul nu a fost gasit\n");
            else
            {
                if (!precedent)
                {

                    free(caut->nume);
                    free(caut->prenume);
                    if (caut->next)
                    {
                        caut = caut->next;
                        unsigned int poz = f_hash(char_sum(nume), char_sum(prenume));
                        while (caut) {
                            (Studenti + poz)->nume = caut->nume;
                            (Studenti + poz)->prenume = caut->prenume;
                            (Studenti + poz)->media = caut->media;
                            (Studenti + poz)->next = caut->next;
                            caut = caut->next;
                        }
                    }
                    else
                    {
                        caut->nume = NULL;
                        caut->prenume = NULL;
                        caut->media = 0;
                    }
                }
                else
                {
                    precedent->next = caut->next;
                    free(caut->nume);
                    free(caut->prenume);
                    free(caut);
                }
            }
        }
        break;
        case '5':
        {
            FILE *f=fopen("date","w");
//            FILE* f = fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator10/temaLab10/temaLab10/date", "w");
            save_and_exit(Studenti, f);
            fclose(f);
            printf("Datele au fost salvate cu success");
            exit(0);
            break;
        }
        default:
            printf("Optiunea nu exista\n");
            break;
        }
    }
}

int main()
{
    student* Studenti = (student*)calloc(m, sizeof(student));
    FILE *f=fopen("date", "r");
//    FILE* f = fopen("/Users/raulbanut/Desktop/Algoritmilor Proiectare/laborator10/temaLab10/temaLab10/date", "r");
    if (!f)
    {
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }
    Citire(f, &Studenti);
    fclose(f);
    printf("Datele au fost incarcate cu success din fisier\n");
    main_menu(Studenti);

    return 0;
}
