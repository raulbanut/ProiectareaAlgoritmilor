//
//  main.c
//  temaDeCasa
/* Problema din laboratorul 1 in care aveam de rezolvat ca prima locomotiva care
 intra sa fie tot prima care iese. FIFO
 La laborator am avut de rezolvat LIFO
 Mai jos am rezolvat problema utilizand o structura de tip locomotiva.
 */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# define NMAX 100

typedef struct locomotiva
{
    int Id;
    char Tip[21];
    float Greutate;
} LOCOMOTIVA;

int main() {
    int varf=0, optiune;
    LOCOMOTIVA DEPOU[NMAX];
    while (1){
        printf("1 Intrare, 2 Iesire, 3 Afisare, 4 Terminare =    ");
        scanf("%d",&optiune);
        switch(optiune){
            case 1:
            { //modul de intrare
                varf++;
                for(int i=varf;i>0;i--){
                    DEPOU[i].Greutate=DEPOU[i-1].Greutate;
                    DEPOU[i].Id=DEPOU[i-1].Id;
                    strcpy(DEPOU[i].Tip,DEPOU[i-1].Tip);
                }
                printf("Introduceti id = ");
                scanf("%d",&DEPOU[0].Id);
                printf("Introduceti tip = ");
                scanf("%s",DEPOU[0].Tip);
                printf("Introduceti greutatea = ");
                scanf("%f",&DEPOU[0].Greutate);
                break;
            }
            case 2:
            {
                //modul de iesire
                if(varf == 0){
                    printf("Depoul este gol...\n");
                }
                else{
                    printf("Locomotiva care iese are următoarele detalii: \nId = %d   |  Tip = %s  |   Greutate = %.2f\n", DEPOU[varf-1].Id, DEPOU[varf-1].Tip, DEPOU[varf-1].Greutate);
                    varf--;
                }
                break;
            }
            case 3:
            {
                //modul de afisare
                if(varf==0) printf("Depoul este gol..\n");
                else {
                    int i;
                    for(i=0;i<varf;i++){
                        printf("Locomotiva %d are urmatoarele detalii: \n Id = %d  |   Tip = %s  |  Greutate = %.2f\n",i+1,DEPOU[i].Id,DEPOU[i].Tip,DEPOU[i].Greutate);
                    }
                }
                break;
            }
            case 4:
            {
                printf("La revedere...\n");
                return 0;
            }
            default:
            {
                printf("Optiune gresita\n");
                break;
            }
        }
    }
    return 0;
}
    

