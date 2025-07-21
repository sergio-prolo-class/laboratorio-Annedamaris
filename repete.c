#include <stdio.h>
#include <string.h>

int repete_palavra(char orig[], int n, char dest[])
{
    int len = strlen(orig);
    strcpy(dest, "");
    for (int i = 0; i < n; i++) {
        strcat(dest, orig);
    }
    return n * len;
}

int main()
{
    char str1[11];
    char str2[101];
    int num_rep, len_rep;
    printf("Entre com uma palavra: ");
    scanf("%10s", str1);
    printf("Entre com o número de repetições: ");
    scanf("%d", &num_rep);
    len_rep = repete_palavra(str1, num_rep, str2);
    printf("Resultado: \"%s\"\n", str2);
    printf("Tamanho: %d\n", len_rep);
    return 0;
}