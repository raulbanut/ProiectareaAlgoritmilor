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

struct arbore *Creare_Echilibrat(unsigned int Nr_Nod)
{
	struct arbore *Nod = NULL;
	if (Nr_Nod)
	{
		char buf[128];
		scanf("%s", buf);
		Nod = (struct arbore*)malloc(sizeof(struct arbore));
		Nod->data = create_char(buf);
		(Nod)->f_st = Creare_Echilibrat(Nr_Nod / 2);
		(Nod)->f_dr = Creare_Echilibrat(Nr_Nod - Nr_Nod / 2 - 1);
	}
	return Nod;
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
	unsigned int Nr;
	printf("Introduceti numarul de noduri: ");
	scanf("%d ", &Nr);
	struct arbore *arb = Creare_Echilibrat(Nr);
	afisare(arb);
	return 0;
}
