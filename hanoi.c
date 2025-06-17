#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"
#include "historico.h"

// Protótipos das funções de menu
void mostrar_menu();
void lidar_com_estatisticas();
void mostrar_regras();

int main() {
    carregarHistorico();

    int opcao;

    while (1) {
        mostrar_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = 0;
        }

        switch (opcao) {
            case 1: {
                char jogar_novamente; // <-- VARIÁVEL DE CONTROLE

                // --- Laço DO-WHILE para permitir jogar novamente ---
                do {
                    system("cls || clear");
                    printf("== INICIAR NOVO JOGO ==\n");

                    char nome_jogador[100];
                    char data[11];
                    int num_discos;

                    // Limpa o buffer de entrada antes de ler o nome do jogador
                    while (getchar() != '\n');

                    printf("Digite seu nome: ");
                    fgets(nome_jogador, sizeof(nome_jogador), stdin);

                    printf("Digite a data (dd/mm/aaaa): ");
                    fgets(data, sizeof(data), stdin);

                    printf("Escolha a quantidade de discos (1 a 8): ");
                    scanf("%d", &num_discos);
                    if (num_discos < 1 || num_discos > 8) {
                        printf("Número de discos inválido. O jogo começará com 3 discos.\n");
                        num_discos = 3;
                    }

                    // Prepara e executa o jogo
                    inicializar_torres(num_discos);
                    iniciar_jogo(nome_jogador, data);
                    limpar_torres();

                    // --- Pergunta se o usuário quer jogar de novo ---
                    printf("\n\nDeseja jogar outra partida? (S/N): ");
                    scanf(" %c", &jogar_novamente); // O espaço antes de %c é importante

                } while (toupper(jogar_novamente) == 'S'); // <-- CONDIÇÃO DO LAÇO

                break; // Sai do case 1 e volta para o laço do menu
            }
            case 2:
                lidar_com_estatisticas();
                break;
            case 3:
                mostrar_regras();
                break;
            case 4:
                printf("\nObrigado por jogar! Até a próxima!\n");
                return 0;
            default:
                printf("\nOpção inválida! Por favor, tente novamente.\n");
                break;
        }

        // Pausa para o usuário ler a tela antes de voltar ao menu
        if (opcao != 4) {
            printf("\nPressione Enter para voltar ao menu...");
             // Garante que o buffer esteja limpo antes de esperar pelo Enter
            while(getchar() != '\n');
            getchar();
        }
    }

    return 0;
}