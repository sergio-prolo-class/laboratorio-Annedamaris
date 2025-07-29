#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Estruturas
typedef struct {
    char nome[100];
    int idade;
    int matricula;
    int faltas;
    float notas[4];
} Aluno;

typedef struct {
    char nome[100];
    char cargo[50];
    float salario;
} Funcionario;

// Prototipos
void menu();
void cadastrarAluno(Aluno *alunos, int *qtd);
void listarAlunos(Aluno *alunos, int qtd);
void atualizarAluno(Aluno *alunos, int qtd);
void removerAluno(Aluno *alunos, int *qtd);
void salvarAlunos(Aluno *alunos, int qtd);
void carregarAlunos(Aluno *alunos, int *qtd);
float calcularMedia(float *notas);

// Main
int main()
{
    Aluno alunos[MAX];
    int qtdAlunos = 0;
    carregarAlunos(alunos, &qtdAlunos);

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarAluno(alunos, &qtdAlunos); break;
            case 2: listarAlunos(alunos, qtdAlunos); break;
            case 3: atualizarAluno(alunos, qtdAlunos); break;
            case 4: removerAluno(alunos, &qtdAlunos); break;
            case 5: salvarAlunos(alunos, qtdAlunos); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void menu()
{
    printf("\n=== Sistema de Cadastro Escolar ===\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Listar alunos\n");
    printf("3. Atualizar aluno\n");
    printf("4. Remover aluno\n");
    printf("5. Salvar dados\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void cadastrarAluno(Aluno *alunos, int *qtd)
{
    printf("\nNome do aluno: ");
    fgets(alunos[*qtd].nome, 100, stdin);
    strtok(alunos[*qtd].nome, "\n");
    printf("Idade: ");
    scanf("%d", &alunos[*qtd].idade);
    printf("Matricula: ");
    scanf("%d", &alunos[*qtd].matricula);
    printf("Faltas: ");
    scanf("%d", &alunos[*qtd].faltas);
    for (int i = 0; i < 4; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &alunos[*qtd].notas[i]);
    }
    (*qtd)++;
}

void listarAlunos(Aluno *alunos, int qtd)
{
    printf("\n=== Lista de Alunos ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("Aluno %d: %s, Idade: %d, Matricula: %d, Faltas: %d, Media: %.2f\n",
               i + 1, alunos[i].nome, alunos[i].idade, alunos[i].matricula, alunos[i].faltas,
               calcularMedia(alunos[i].notas));
    }
}

void atualizarAluno(Aluno *alunos, int qtd)
{
    int mat;
    printf("\nInforme a matricula do aluno a ser atualizado: ");
    scanf("%d", &mat);
    for (int i = 0; i < qtd; i++) {
        if (alunos[i].matricula == mat) {
            printf("Novo nome: ");
            getchar();
            fgets(alunos[i].nome, 100, stdin);
            strtok(alunos[i].nome, "\n");
            printf("Nova idade: ");
            scanf("%d", &alunos[i].idade);
            printf("Novas faltas: ");
            scanf("%d", &alunos[i].faltas);
            for (int j = 0; j < 4; j++) {
                printf("Nova nota %d: ", j + 1);
                scanf("%f", &alunos[i].notas[j]);
            }
            printf("Aluno atualizado!\n");
            return;
        }
    }
    printf("Aluno nao encontrado.\n");
}

void removerAluno(Aluno *alunos, int *qtd)
{
    int mat;
    printf("\nInforme a matricula do aluno a ser removido: ");
    scanf("%d", &mat);
    for (int i = 0; i < *qtd; i++) {
        if (alunos[i].matricula == mat) {
            for (int j = i; j < *qtd - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*qtd)--;
            printf("Aluno removido!\n");
            return;
        }
    }
    printf("Aluno nao encontrado.\n");
}

float calcularMedia(float *notas)
{
    float soma = 0;
    for (int i = 0; i < 4; i++) {
        soma += notas[i];
    }
    return soma / 4.0;
}

void salvarAlunos(Aluno *alunos, int qtd)
{
    FILE *f = fopen("alunos.txt", "w");
    if (!f) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        fprintf(f, "%s;%d;%d;%d;%.2f;%.2f;%.2f;%.2f\n",
                alunos[i].nome, alunos[i].idade, alunos[i].matricula, alunos[i].faltas,
                alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2], alunos[i].notas[3]);
    }
    fclose(f);
    printf("Dados salvos com sucesso.\n");
}

void carregarAlunos(Aluno *alunos, int *qtd)
{
    f
        FILE *= fopen("alunos.txt", "r");
    if (!f)
        return;
    while (fscanf(f, "%[^;];%d;%d;%d;%f;%f;%f;%f\n",
                  alunos[*qtd].nome, &alunos[*qtd].idade, &alunos[*qtd].matricula, &alunos[*qtd].faltas,
                  &alunos[*qtd].notas[0], &alunos[*qtd].notas[1], &alunos[*qtd].notas[2], &alunos[*qtd].notas[3]) != EOF) {
        (*qtd)++;
    }
    fclose(f);
}