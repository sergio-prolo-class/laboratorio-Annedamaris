#include <stdio.h>

int main()
{
    float x, y, res;
    char op;

    printf("Entre com a expressão: ");
    scanf("%f %c %f", &x, &op, &y);

    switch (op) {
        case '+':
            res = x + y;
            break;
        case '-' res = x - y;
            break;
            case '*':
            res = x * y;
            break;
        case '/':
            if (y == 0) {
                printf("Erro: Divisão por zero\n");
                return 1;
            }
            res = x / y;
            break;
        default:
            printf("Operador inválido\n");
            return 1;
    }

    printf("O número é %.2f\n", res);
    return 0;
}