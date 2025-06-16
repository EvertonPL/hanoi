#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "funcoes.h"
#include "historico.h"

// ... (varáveis globais e protóipos estáticos permanecem os mesmos) ...
Torre torreA, torreB, torreC;
int n;
static void mostrar_torres();
static int altura_torre(const Torre* torre);
static int disco_no_nivel(const Torre* torre, int nivel);
static int validar_movimento(Torre *origem, Torre *destino);
static void executar_movimento(Torre *origem, Torre *destino);
static Torre* torre_por_nome(char nome);
static void push(Torre *torre, int discos);
static int pop(Torre *torre);
static void liberar_pilha(Torre *torre);
static void imprimir_torre(const Torre* t, int level, int n_max);


// --- IMPLEMENTAÇÃO DAS FUNÇÕES PÚBLICAS ---

// FUNÇÃO SIMPLIFICADA: Apenas inicializa com a quantidade recebida.
void inicializar_torres(int quantidade) {
    n = quantidade;
    torreA.top = NULL; torreA.nome = 'A';
    torreB.top = NULL; torreB.nome = 'B';
    torreC.top = NULL; torreC.nome = 'C';

    for (int i = n; i >= 1; i--) {
        push(&torreA, i);
    }
}

void limpar_torres() {
    liberar_pilha(&torreA);
    liberar_pilha(&torreB);
    liberar_pilha(&torreC);
}

// FUNÃ‡ÃƒO SIMPLIFICADA: Apenas roda o jogo com os dados recebidos.
void iniciar_jogo(const char* nome_jogador, const char* data) {
    int movimentos = 0;

    // Loop principal do jogo
    while (altura_torre(&torreC) < n) {
        system("cls || clear");
        mostrar_torres();
        char nome_origem, nome_destino;

        printf("Mover de qual torre para qual torre? (ex: A C): ");
        if (scanf(" %c %c", &nome_origem, &nome_destino) != 2) {
            printf("\n>> Entrada invÃ¡lida! Use o formato 'Letra Letra'. <<\n");
            while (getchar() != '\n');
            continue;
        }

        Torre *p_origem = torre_por_nome(toupper(nome_origem));
        Torre *p_destino = torre_por_nome(toupper(nome_destino));

        if (validar_movimento(p_origem, p_destino)) {
            executar_movimento(p_origem, p_destino);
            movimentos++;
        } else {
            printf("\n>> Tente novamente! <<\n");
            printf("Pressione Enter para continuar...");
            while(getchar() != '\n');
            getchar();
        }
    }

    // Mensagem de vitória
    system("cls || clear");
    printf("\n*********************************************\n");
    mostrar_torres();
    printf("PARABENS, %sVoce resolveu a Torre de Hanoi! \n", nome_jogador);
    printf("Voce completou em %d movimentos.\n", movimentos);
    int min_moves = pow(2, n) - 1;
    printf("O numero minimo de movimentos possivel era %d.\n", min_moves);
    printf("*********************************************\n");

    salvarHistorico(nome_jogador, movimentos, n, data);
    adicionarHistorico(nome_jogador, movimentos, n, data);
}


// --- FUNÇÕES DE MENU ---
