#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"
#include "historico.h"

void salvarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data) {
    FILE *f = fopen("historico_hanoi.txt", "a");
    if (f == NULL) {
        perror("Erro ao abrir arquivo de historico");
        return;
    }
    fprintf(f, "%s\n%d\n%d\n%s\n", nome_jogador, movimentos, discos, data);
    fclose(f);
}

void carregarHistorico() {
    FILE *f = fopen("historico_hanoi.txt", "r");
    if (f == NULL) {
        return;
    }
        char nome_jogador[100];
        int movimentos, discos;
        char data[11];

    while (fgets(nome_jogador, sizeof(nome_jogador), f) != NULL) {
        fscanf(f, "%d", &movimentos);
        fscanf(f, "%d", &discos);
        fscanf(f, "%s", data);
        adicionarHistorico(nome_jogador, movimentos, discos, data);
    }
}