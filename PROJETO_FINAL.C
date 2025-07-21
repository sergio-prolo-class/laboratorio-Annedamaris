#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    int id;
    char cliente[10];
    char sabor[10];
    char bebida[10];
    int quantidade;
    float total;
} Pedido;

void menu();
void novo(Pedido pedidos[], int *qtd, float *caixa);
void listar(Pedido pedidos[], int qtd);
void totalCaixa(float caixa);

int main()
{
    Pedido pedidos[MAX];
    int qtd = 0;
    float caixa = 0;
    int opcao;

    do {
        menu();
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            novo(pedidos, &qtd, &caixa);
        } else if (opcao == 2) {
            listar(pedidos, qtd);
        } else if (opcao == 3) {
            totalCaixa(caixa);
        } else if (opcao != 0) {
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

void menu()
{
    printf("\n Boa Tarde :) \n");
    printf("\n Bem vindo ao Gerenciador de Pizzaria :v \n");
    printf("\n --- MENU ---\n");
    printf("1 - Anotar novo pedido\n");
    printf("2 - Listar pedidos\n");
    printf("3 - Mostrar total em caixa\n");
    printf("0 - Sair\n");
}

void novo(Pedido pedidos[], int *qtd, float *caixa)
{
    if (*qtd >= MAX) {
        printf("Limite de pedidos atingido!\n");
        return;
    }

    printf("Nome do cliente: ");
    fgets(pedidos[*qtd].cliente, 10, stdin);
    strtok(pedidos[*qtd].cliente, "\n");

    int sabor;
    printf("\n Sabores:\n");
    printf("1 - Queijo (39.90)\n");
    printf("2 - Bacon (45.90)\n");
    printf("3 - Calabresa (45.90)\n");
    printf("Escolha: ");
    scanf("%d", &sabor);
    getchar();

    if (sabor == 1) {
        strcpy(pedidos[*qtd].sabor, "Queijo");
        pedidos[*qtd].total = 39.90;
    } else if (sabor == 2) {
        strcpy(pedidos[*qtd].sabor, "Bacon");
        pedidos[*qtd].total = 45.90;
    } else {
        strcpy(pedidos[*qtd].sabor, "Calabresa");
        pedidos[*qtd].total = 45.90;
    }

    int bebida;
    printf("Bebidas:");
    printf("\n1- Agua (5.00)");
    printf("2- Refri (10.00)");
    printf("Escolha: ");
    scanf("%d", &bebida);
    getchar();

    if (bebida == 1) {
        strcpy(pedidos[*qtd].bebida, "Agua");
        pedidos[*qtd].total += 5.00;
    } else {
        strcpy(pedidos[*qtd].bebida, "Refri");
        pedidos[*qtd].total += 10.00;
    }

    printf("Quantidade: ");
    scanf("%d", &pedidos[*qtd].quantidade);

    getchar();

    pedidos[*qtd].id = *qtd + 1;
    pedidos[*qtd].total *= pedidos[*qtd].quantidade;

    *caixa += pedidos[*qtd].total;
    (*qtd)++;

    printf("Pedido feito com sucesso!");
}

void listar(Pedido pedidos[], int qtd)
{
    printf("\n--- LISTA DE PEDIDOS ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Cliente: %s | Sabor: %s | Bebida: %s | Qtde: %d | Total: R$ %.2f\n",
               pedidos[i].id,
               pedidos[i].cliente,
               pedidos[i].sabor,
               pedidos[i].bebida,
               pedidos[i].quantidade,
               pedidos[i].total);
    }
    if (qtd == 0) {
        printf("Nenhum pedido ainda.\n");
    }
}

void totalCaixa(float caixa)
{
    printf("\nTotal no caixa: R$ %.2f\n", caixa);
}