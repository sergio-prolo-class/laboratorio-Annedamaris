#include <stdio.h>

int main()
{
    float peso, altura, imc;

    printf("Entre com o peso (kg): ");
    scanf("%f", &peso);
    printf("Entre com a altura (m): ");
    scanf("%f", &altura);

    imc = peso / (altura * altura);

    printf("IMC: %.2f kg/m²\n", imc);

    printf("Classificação: ");
    if (imc < 18.5) {
        printf("Magreza\n");
    } else if (imc < 25.0) {
        printf("Normal\n");
    } else if (imc < 30.0) {
        printf("Sobrepeso\n");
    } else {
        printf("Obesidade\n");
    }

    return 0;
}