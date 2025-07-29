#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    int id;
    char cliente[10];
    char sabor[10];
    char bebida[10];
    int qtdPizza;
    int qtdBebida;
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
        getchar(); // limpa o \n

        switch (opcao) {
            case 1:
                novo(pedidos, &qtd, &caixa);
                break;
            case 2:
                listar(pedidos, qtd);
                break;
            case 3:
                totalCaixa(caixa);
                break;
            case 4: {
    int subopcao;
    printf("\n--- RELATÓRIO ---\n");
    printf("1 - Salvar (acrescentar) todos os pedidos\n");
    printf("2 - Atualizar (sobrescrever) relatório\n");
    printf("Escolha: ");
    scanf("%d", &subopcao);
    getchar();

    if (subopcao == 1) {
        FILE *arquivo = fopen("relatorio.txt", "a");
        if (arquivo != NULL) {
            for (int i = 0; i < qtd; i++) {
                fprintf(arquivo, "ID: %d | Cliente: %s | Sabor: %s | Qtde Pizza: %d | Bebida: %s | Qtde Bebida: %d | Total: R$ %.2f\n",
                    pedidos[i].id,
                    pedidos[i].cliente,
                    pedidos[i].sabor,
                    pedidos[i].qtdPizza,
                    pedidos[i].bebida,
                    pedidos[i].qtdBebida,
                    pedidos[i].total);
            }
            fclose(arquivo);
            printf("Relatório salvo (modo adicionar).\n");
        } else {
            printf("Erro ao abrir o arquivo!\n");
        }
    } else if (subopcao == 2) {
        FILE *arquivo = fopen("relatorio.txt", "w");
        if (arquivo != NULL) {
            for (int i = 0; i < qtd; i++) {
                fprintf(arquivo, "ID: %d | Cliente: %s | Sabor: %s | Qtde Pizza: %d | Bebida: %s | Qtde Bebida: %d | Total: R$ %.2f\n",
                    pedidos[i].id,
                    pedidos[i].cliente,
                    pedidos[i].sabor,
                    pedidos[i].qtdPizza,
                    pedidos[i].bebida,
                    pedidos[i].qtdBebida,
                    pedidos[i].total);
            }
            fclose(arquivo);
            printf("Relatório atualizado (modo sobrescrever).\n");
        } else {
            printf("Erro ao abrir o arquivo!\n");
        }
    } else {
        printf("Opção inválida.\n");
    }
    break;
}
           case 0:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

void menu()
{
    printf("\n--- MENU ---\n");
    printf("1 - Anotar novo pedido\n");
    printf("2 - Listar pedidos\n");
    printf("3 - Mostrar total em caixa\n");
    printf("4 - Relatório\n");
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
    float precoPizza = 0;
    printf("\n Sabores:\n");
    printf("1 - Queijo (39.90)\n");
    printf("2 - Bacon (45.90)\n");
    printf("3 - Calabresa (45.90)\n");
    printf("Escolha: ");
    scanf("%d", &sabor);
    getchar();

    if (sabor < 1 || sabor > 3) {
        printf("Opção inválida! Digite novamente.\n");
    }
    while (sabor < 1 || sabor > 3);

    switch (sabor) {
        case 1:
            strcpy(pedidos[*qtd].sabor, "Queijo");
            precoPizza = 39.90;
            break;
        case 2:
            strcpy(pedidos[*qtd].sabor, "Bacon");
            precoPizza = 45.90;
            break;
        case 3:
        default:
            strcpy(pedidos[*qtd].sabor, "Calabresa");
            precoPizza = 45.90;
            break;
        }

    do {
        printf("Quantidade de pizzas: ");
        scanf("%d", &pedidos[*qtd].qtdPizza);
        getchar();
        if (pedidos[*qtd].qtdPizza < 0) printf("Valor inválido! Digite novamente.\n");
    } while (pedidos[*qtd].qtdPizza < 0);

    int opcaoBebida, bebida;
    float precoBebida = 0;
    pedidos[*qtd].qtdBebida = 0;
    strcpy(pedidos[*qtd].bebida, "Nenhuma");

    printf("Deseja adicionar bebidas?\n1 - Sim\n2 - Não\nEscolha: ");
    scanf("%d", &opcaoBebida);
    getchar();

    if (opcaoBebida == 1) {
        printf("Bebidas disponíveis:\n");
        printf("1 - Água (5.00)\n");
        printf("2 - Refrigerante (10.00)\n");
        printf("Escolha: ");
        scanf("%d", &bebida);
        getchar();

        switch (bebida) {
            case 1:
                precoBebida = 5.00;
                strcpy(pedidos[*qtd].bebida, "Agua");
                break;
            case 2:
                precoBebida = 10.00;
                strcpy(pedidos[*qtd].bebida, "Refri");
                break;
            default:
                printf("Opção inválida. Nenhuma bebida adicionada.\n");
                precoBebida = 0;
                strcpy(pedidos[*qtd].bebida, "Nenhuma");
                break;
        }

        do {
            printf("Quantidade de bebidas: ");
            scanf("%d", &pedidos[*qtd].qtdBebida);
            getchar();
            if (pedidos[*qtd].qtdBebida < 0) printf("Valor inválido! Digite novamente.\n");
        } while (pedidos[*qtd].qtdBebida < 0);
    }

    // Calcula total do pedido
    float totalPedido = precoPizza * pedidos[*qtd].qtdPizza + precoBebida * pedidos[*qtd].qtdBebida;
    pedidos[*qtd].total = totalPedido;
    pedidos[*qtd].id = *qtd + 1;
    *caixa += totalPedido;

    printf("Total do pedido: R$ %.2f\n", totalPedido);

    // Troco
    char resposta;
    printf("Deseja calcular o troco? (s/n): ");
    scanf(" %c", &resposta);
    
    if (resposta == 's' || resposta == 'S') {
        float valorPago;
        do {
            printf("Valor recebido: R$ ");
            scanf("%f", &valorPago);
            if (valorPago < totalPedido) printf("Valor insuficiente! Digite novamente.\n");
        } while (valorPago < totalPedido);
        printf("Troco: R$ %.2f\n", valorPago - totalPedido);
                      
    }
    

    // Salvar no relatório
    FILE *arquivo = fopen("relatorio.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "ID: %d | Cliente: %s | Sabor: %s | Qtde Pizza: %d | Bebida: %s | Qtde Bebida: %d | Total: R$ %.2f\n",
                pedidos[*qtd].id,
                pedidos[*qtd].cliente,
                pedidos[*qtd].sabor,
                pedidos[*qtd].qtdPizza,
                pedidos[*qtd].bebida,
                pedidos[*qtd].qtdBebida,
                pedidos[*qtd].total);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar relatório!\n");
    }

    printf("Pedido feito com sucesso!\n");
    (*qtd)++;
}

void listar(Pedido pedidos[], int qtd)
{
    printf("\n--- LISTA DE PEDIDOS ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Cliente: %s | Sabor: %s | Qtde Pizza: %d | Bebida: %s | Qtde Bebida: %d | Total: R$ %.2f\n",
               pedidos[i].id,
               pedidos[i].cliente,
               pedidos[i].sabor,
               pedidos[i].qtdPizza,
               pedidos[i].bebida,
               pedidos[i].qtdBebida,
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