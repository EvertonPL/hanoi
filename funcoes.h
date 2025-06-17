#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h>

// struct do nó da pilha
typedef struct Node {
    int discos;
    struct Node *prox;
} Node;

// struct da torre
typedef struct {
    Node *top;
    char nome;
} Torre;

extern Torre torreA, torreB, torreC;
extern int n;

// --- Funções Públicas ---
void inicializar_torres(int quantidade);
void iniciar_jogo(char* nome_jogador, const char* data);
void limpar_torres();

// --- Funções de Menu ---
void mostrar_menu();
void lidar_com_estatisticas();
void mostrar_regras();

#endif