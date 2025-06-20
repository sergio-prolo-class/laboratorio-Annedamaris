#include <stdio.h>

int main()
{
    float faixa_min, faixa_max, ph;
    int n_medições, n_medicoes_fora = 0;

    printf("Entre com a faixa de PH adequada: ");
    scanf("%f %f", &faixa_min, &faixa_max);

    printf("Entre com o numero de medições:");
    scanf("%d", &n_medições);

    printf("Entre com o numero de ph:");
    for (int i = n_medições; i > 0; i--) {
        scanf("%f", &ph);
        if (ph < faixa_min || ph > faixa_max)
            n_medicoes_fora++;
    }

    printf("Numero de medições fora da faixa: %d\n", n_medicoes_fora);

    return 0;
}
