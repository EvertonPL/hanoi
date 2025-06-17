#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"
#include "historico.h"

Historico* inicio;

void adicionarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data) {
    Historico* novo = malloc(sizeof(Historico));
    strcpy(novo->nome_jogador, nome_jogador);
    novo->movimentos = movimentos;
    novo->discos = discos;
    strcpy(novo->data, data);
    novo->prox = inicio;
    inicio = novo;
}

void carregarHistorico() {
    FILE *f = fopen("historico_hanoi.txt", "r");
    if (f == NULL) {
        return;
    }
        char nome_jogador[100];
        int movimentos, discos;
        char data[11];

    while (fscanf(f, " %99[^\n]\n%d\n%d\n%10[^\n]\n", nome_jogador, &movimentos, &discos, data) == 4) {
        adicionarHistorico(nome_jogador, movimentos, discos, data);
    }
    fclose(f);
}

void salvarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data) {
    FILE *f = fopen("historico_hanoi.txt", "a");
    if (f == NULL) {
        perror("Erro ao abrir arquivo de historico");
        return;
    }
    fprintf(f, "%s\n%d\n%d\n%s\n", nome_jogador, movimentos, discos, data);
    fclose(f);
}

void mostrarHistorico() {
    if (inicio == NULL) {
        printf("Nenhum historico para mostrar.\n");
        return;
    }
    printf("\nHistorico de partidas\n");
    Historico* atual = inicio;
    while (atual) {
        printf("Jogador: %s | Movimentos: %d | Discos: %d | Data: %s\n",
               atual->nome_jogador, atual->movimentos, atual->discos, atual->data);
        atual = atual->prox;
    }
    printf("=============================\n");
}

void buscarUsuario(const char* nome_jogador) {
    int achou = 0;
    Historico* atual = inicio;
    char nome_busca[100];
    strcpy(nome_busca, nome_jogador);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    printf("\nHistorico para o jogador '%s'\n", nome_busca);
    while(atual != NULL) {
        if (strcasecmp(atual->nome_jogador, nome_busca) == 0) {
            printf("Jogador: %s | Movimentos: %d | Discos: %d | Data: %s\n",
                   atual->nome_jogador, atual->movimentos, atual->discos, atual->data);
            achou = 1;
        }
        atual = atual->prox;
    }
    if (achou == 0){
        printf("Nenhum registro encontrado para o jogador '%s'.\n", nome_busca);
    }
}

void buscarData(const char* data) {
    int achou = 0;
    Historico* atual = inicio;
    printf("\nHistorico para a data '%s'\n", data);
    
    while (atual != NULL) {
        if (strcmp(atual->data, data) == 0) {
            printf("Jogador: %s | Movimentos: %d | Discos: %d | Data: %s\n",
                   atual->nome_jogador, atual->movimentos, atual->discos, atual->data);
            achou = 1;
        }
        atual = atual->prox;
    }
    
    if (achou == 0) {
        printf("Nenhum registro encontrado para a data '%s'.\n", data);
    }
}