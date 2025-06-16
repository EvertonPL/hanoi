#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct Historico {
    char nome_jogador[100];
    int movimentos;
    int discos;
    char data[11]; 
    struct Historico* prox;
} Historico;

void mostrarHistorico();
void adicionarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data);
void salvarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data);
void carregarHistorico();
void buscarUsuario(const char* nome_jogador);
void buscarData(const char* data);

#endif