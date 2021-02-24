//
//  main.c
//  Laboratorul1
//  problemePropuse1
//  De la tastatura se citesc cuvinte. Sa se creeze o lista ordonata alfabetic. Fiecare element al listei contine un cuvant si frecventa lui de aparitie (de cate ori se repeta cuvantul in datele de intrare). Cuvintele din lista sunt distincte. Se va afisa continutul listei in ordine alfabetica. De exemplu daca se citeste:
//  beta gama alfa beta gama delta se va afisa:
//  alfa 1, beta 2, gama 2, delta 1
/* Voi folosi o structura de tip element*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 30

typedef struct element
{
    int nrAparitii;
    char nume[21];
} ELEMENT;

int main() {
    ELEMENT lista[NMAX];
    int optiune,nrCuvinte=0;
    for(int i=0;i<=NMAX;i++){
        lista[i].nrAparitii=0;
    }
    while(1){
        printf("1 Introducere cuvant nou, 2 Afisare lista ordonata alfabetic, 3 Terminare  =    ");
        scanf("%d",&optiune);
        switch (optiune) {
            case 1:
            {
                //se retine cuvantul nou, se parcurge vectorul, daca nu apare cuvantul se adauga in lista, daca apare se incrementeaza nr de aparitii
                //modul de intrare
                char cuvantNou[21];
                printf("Introduceti cuvant nou = ");
                scanf("%s",cuvantNou);
                int semafor=0;
                for(int i=0;i<nrCuvinte;i++){
                    if(!strcmp(lista[i].nume,cuvantNou)){
                        semafor=1;
                        lista[i].nrAparitii++;
                    }

                }
                if(semafor==0){
                    
                    lista[nrCuvinte].nrAparitii=1;
                    strcpy(lista[nrCuvinte].nume,cuvantNou);
                    nrCuvinte++;
                }
                for (int i=0; i<nrCuvinte; i++) {
                    printf("cuv %s apare de %d\n",lista[i].nume,lista[i].nrAparitii);
                }
                break;
            }
            case 2:
            {
                //se ordoneaza si se parcurge vectorul
//                for(int i=0;i<nrCuvinte;i++){
//                    printf("%s %d\n",lista[i].nume,lista[i].nrAparitii);
//                }
                for(int i=0;i<nrCuvinte-1;i++)
                    for(int j=i+1;j<nrCuvinte;j++){
                        if(strcmp(lista[i].nume,lista[j].nume)>0){
                            int aux;
                            char auxiliar[21];
                            aux=lista[i].nrAparitii;
                            lista[i].nrAparitii=lista[j].nrAparitii;
                            lista[j].nrAparitii=aux;
                            strcpy(auxiliar, lista[j].nume);
                            strcpy(lista[j].nume, lista[i].nume);
                            strcpy(lista[i].nume, auxiliar);
                        }
                    }
                for(int i=0;i<nrCuvinte;i++){
                    printf("%s %d\n",lista[i].nume,lista[i].nrAparitii);
                }
                break;
            }
            case 3:
            {
                printf("la revederee...\n");
                exit(1);
                return 0;
            }
        }
    }
}
