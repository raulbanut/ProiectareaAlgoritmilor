#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arbore
{
	char *data;
	struct arbore *f_dr, *f_st;
};

char *create_char(char x[128])
{
	unsigned int len = strlen(x);
	char *newchar = (char*)malloc(len + 1);
	strcpy(newchar, x);
	return newchar;
}

struct arbore *Creare()
{
	struct arbore *nod = NULL;
	char *citit,buf[128];
	scanf("%s", buf);
	citit = create_char(buf);
	if (strcmp(citit,"*"))
	{
		nod = (struct arbore*)malloc(sizeof(struct arbore));
		nod->data = citit;
		(nod)->f_st = Creare();
		(nod)->f_dr = Creare();
	}
	return nod;
}


void afisare(struct arbore *arb)
{
	if (arb)
	{
		afisare(arb->f_st);
		afisare(arb->f_dr);
		printf("%s ", arb->data);
		free(arb);
	}
}

int main()
{
	struct arbore *arb = Creare();
	afisare(arb);
	return 0;
}
