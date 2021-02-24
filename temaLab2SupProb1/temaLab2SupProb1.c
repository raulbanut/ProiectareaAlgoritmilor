//
//  main.c
//  problemePropuse1 laboratorul 2
//  Sa se scrie programul care creeaza doua liste simplu inlantuite, ordonate crescator dupa o cheie numerica si apoi le interclaseaza.
//
//  Created by Banut Raul on 09/10/2019.
//  Copyright © 2019 Banut Raul. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct lista{
    int cheieNumerica;
    struct lista *next_p;
};

struct lista * citire(struct lista *p);
void bubbleSort(struct lista *prim);
void swap(struct lista *a, struct lista *b);
void afisare(struct lista *prim);
void MoveNode(struct lista** destRef, struct lista** sourceRef);
struct lista* SortedMerge(struct lista* a, struct lista* b);


int main() {
    unsigned int numarLista1=0,numarLista2=0;
    struct lista *list1=NULL;
    struct lista *list2=NULL;
    struct lista *list3=NULL;
//    list=citire(list);
//    afisare(list);
    
    /* se citeste prima lista */
    printf("introduceti numarul de elemente pentru prima lista = ");
    scanf("%d",&numarLista1);
    int i=0;
    while (i<numarLista1)
    {
        list1=citire(list1);
        i++;
    }
    printf("\n");
    
    /* se citeste a doua lista */
    printf("introduceti numarul de elemente pentru a doua lista = ");
    scanf("%d",&numarLista2);
    i=0;
    while(i<numarLista2)
    {
        list2=citire(list2);
        i++;
    }
    
    /* se ordoneaza crescator listele */
    bubbleSort(list1);
    bubbleSort(list2);
    
    printf("afisez lista 1\n");
    afisare(list1);
    printf("afisez lista 2\n");
    afisare(list2);
    
    list3 = SortedMerge(list1, list2);
    
    printf("aici trb sa fie interclasate\n");
    afisare(list3);
//    printf("aici se desparte\n");
//    afisare(list);
    return 0;
}


struct lista * citire(struct lista *p){
    int numar;
    printf("introduceti date: ");
    scanf("%d",&numar);
    struct lista *nou=(struct lista *)malloc(sizeof(struct lista));
    if (p==NULL){
        nou->next_p=NULL;
        nou->cheieNumerica=numar;
    }
    else
    {
        nou->next_p=p;
        nou->cheieNumerica=numar;
    }
    return nou;
}

//Asa se afiseaza lista
void afisare(struct lista *prim)
{
    struct lista *p=prim;
    while(p)
    {
        printf("cheia este %d \n",p->cheieNumerica);
        p=p->next_p;
    }
}

void bubbleSort(struct lista *prim)
{
    int swapped, i;
    struct lista *ptr1;
    struct lista *lptr = NULL;
      
    /* Verific lista daca e goala. */
    if (prim == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = prim;
        while (ptr1->next_p != lptr)
            {
                if (ptr1->cheieNumerica > ptr1->next_p->cheieNumerica)
                {
                    swap(ptr1, ptr1->next_p);
                    swapped = 1;
                }
                ptr1 = ptr1->next_p;
            }
            lptr = ptr1;
        }
        while (swapped);
}

//Asa se face schimbul intre doua componente din lista
void swap(struct lista *a, struct lista *b)
{
    int temp = a->cheieNumerica;
    a->cheieNumerica = b->cheieNumerica;
    b->cheieNumerica = temp;
}

struct lista* SortedMerge(struct lista* a, struct lista* b)
{
    /* nou il folosesc pt a crea a treia lista */
    struct lista nou;
  
    /* tail indica ultimul nod din lista  */
    struct lista* tail = &nou;
  
    /* deci tail->next_p este locul unde adaug noi noduri la rezultat */
    nou.next_p = NULL;
    while (1)
    {
        if (a == NULL)
        {
            /* daca o lista se termina, folosim cealalta lista*/
            tail->next_p = b;
            break;
        }
        else if (b == NULL)
        {
            tail->next_p = a;
            break;
        }
        if (a->cheieNumerica <= b->cheieNumerica)
            MoveNode(&(tail->next_p), &a);
        else
            MoveNode(&(tail->next_p), &b);
  
        tail = tail->next_p;
    }
    return(nou.next_p);
}

void MoveNode(struct lista** destRef, struct lista** sourceRef)
{
    /* primul nod din sursa */
    struct lista* newNode = *sourceRef;
    assert(newNode != NULL);
  
    /* avansa pointerul */
    *sourceRef = newNode->next_p;
  
    /* leg ultimul de noul */
    newNode->next_p = *destRef;
  
    /* mut dest catre primul */
    *destRef = newNode;
}
