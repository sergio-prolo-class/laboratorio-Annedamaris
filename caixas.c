#include <stdio.h>

int main()
{
    float alt, larg, comp, area, Volume;
    printf("Escreva Altura:");
    scanf("%f", &alt);
    printf("Escreva largura:");
    scanf("%f", &larg);
    printf("Escreva comprimento:");
    scanf("%f", &comp);
    area=(alt*larg*2)+(larg*comp*2)+(alt*larg*2);
    printf("A Área é:%.2f\n",area);
    Volume=(alt*larg*comp);
    printf("O Volume é:%.2f\n",Volume);
    return 0;
}