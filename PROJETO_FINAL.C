#include <stdio.h>
#include <string.h>

#define MAX 5

////// nova estrutura com separação de quantidades para bebidas e pizza.
typedef struct {
    int id;
    char cliente[10];
    char sabor[10];
    char bebida[10];
    int qtdPizza;
    int qtdBebida;
    float total;
} Pedido;

void menu(); ///// declara o menu
void novo(Pedido pedidos[], int *qtd, float *caixa); //// cadastra novo pedido
void listar(Pedido pedidos[], int qtd);  ////lista os pedidos
void totalCaixa(float caixa); ////mostra o total do caixa

int main()
{
    ///// inicia com o Menu
    Pedido pedidos[MAX];
    int qtd = 0;
    float caixa = 0;
    int opcao;

    do {
        menu();
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); 

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
    int subopcao; ///direciona para o relatorio
    printf("\n--- RELATÓRIO ---\n");
    printf("1 - Salvar (acrescentar) todos os pedidos\n");
    printf("2 - Atualizar (sobrescrever) relatório\n");
    printf("Escolha: ");
    scanf("%d", &subopcao);
    getchar();

    if (subopcao == 1) {
        FILE *arquivo = fopen("relatorio.txt", "a"); ///"a"	append (acrescentar) conteúdo antigo é mantido e novos dados são adicionados no fim
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
        FILE *arquivo = fopen("relatorio.txt", "w"); ///"w"	write, abre para escrita, cria o arquivo se não existir. Se existir, apaga o conteúdo (não consegui melhorar daqui para frente, pois com essa opção, está apagando tudo que já estava escrito).
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

void menu() ////Menu interativo
{
    printf("\n***** Pizzaria La Nonna Felice ^.^  ******\n");
    printf("\n === Iniciando Gerenciador de Pizzaria ===\n");
    printf("\n--- Escolha uma das opções abaixo ---\n");
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

    
    float precoPizza = 0;
    char linha[20];   

    int sabor; //// opções de sabores

    do {
    printf("\n Sabores:\n");
    printf("1 - Queijo (39.90)\n");
    printf("2 - Bacon (45.90)\n");
    printf("3 - Calabresa (45.90)\n");
    printf("Escolha: ");

    fgets(linha, sizeof(linha), stdin); //// correção para valores diferentes das opções do Menu.

    if (sscanf(linha, "%d", &sabor) != 1 || sabor < 1 || sabor > 3) {
        printf("Opção inválida! Digite um número entre 1 e 3.\n");
        sabor = -1; // garante que o loop continue, e não aceite valores diferentes das opções do Menu.
    }
} while (sabor < 1 || sabor > 3);
    
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
        printf("Quantidade de pizzas: "); //// nova função, quantidade de Pizza.
        scanf("%d", &pedidos[*qtd].qtdPizza);
        getchar();
        if (pedidos[*qtd].qtdPizza < 0) printf("Valor inválido! Digite novamente.\n");
    } while (pedidos[*qtd].qtdPizza < 0);

    //// nova função, opção de aceitar bebida ou não.
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

    ////// nova função, calculo do total do pedido.
    float totalPedido = precoPizza * pedidos[*qtd].qtdPizza + precoBebida * pedidos[*qtd].qtdBebida;
    pedidos[*qtd].total = totalPedido;
    pedidos[*qtd].id = *qtd + 1;
    *caixa += totalPedido;

    printf("Total do pedido: R$ %.2f\n", totalPedido);

    ////// nova função, calculo do troco.
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
    

    ////// nova função, salvar no relatório
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