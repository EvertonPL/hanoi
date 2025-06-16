void mostrar_menu() {
    system("cls || clear");
    printf("=============================\n");
    printf("      TORRE DE HANOI\n");
    printf("=============================\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Estatisticas (Historico)\n");
    printf("3. Regras do Jogo\n");
    printf("4. Sair\n");
    printf("=============================\n");
}

void lidar_com_estatisticas() {
    system("cls || clear");
    printf("== ESTATISTICAS E HISTORICO ==\n");
    mostrarHistorico();

    printf("\nDeseja buscar um historico especifico?\n");
    printf(" (U) por Usuario\n");
    printf(" (D) por Data\n");
    printf(" (Qualquer outra tecla para voltar)\n");
    printf("Sua escolha: ");

    char busca_tipo;
    scanf(" %c", &busca_tipo);
    while (getchar() != '\n'); // Limpa buffer

    if (toupper(busca_tipo) == 'U') {
        char nome_busca[100];
        printf("Digite o nome do jogador para buscar: ");
        fgets(nome_busca, sizeof(nome_busca), stdin);
        buscarUsuario(nome_busca);
    } else if (toupper(busca_tipo) == 'D') {
        char data_busca[11];
        printf("Digite a data para buscar (dd/mm/aaaa): ");
        fgets(data_busca, sizeof(data_busca), stdin);
        buscarData(data_busca);
    }
}

void mostrar_regras() {
    system("cls || clear");
    printf("=============================\n");
    printf("       REGRAS DO JOGO\n");
    printf("=============================\n");
    printf("O objetivo e mover todos os discos da torre A para a torre C.\n\n");
    printf("Siga estas regras:\n");
    printf("1. Mova apenas um disco por vez.\n");
    printf("2. Um disco maior nunca pode ser colocado sobre um disco menor.\n");
    printf("3. Voce pode usar a torre B como auxiliar para os movimentos.\n");
    printf("=============================\n");
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ESTÁTICAS (PRIVADAS) ---
// (Todas as suas funções static, como push, pop, mostrar_torres, etc. continuam aqui)
// ... (O resto do arquivo é igual ao anterior)
static void push(Torre *torre, int discos) {
    Node *novo = malloc(sizeof(Node));
    if (!novo) return;
    novo->discos = discos;
    novo->prox = torre->top;
    torre->top = novo;
}

static int pop(Torre *torre) {
    if(torre->top) {
        Node *top_atual = torre->top;
        int valor = top_atual->discos;
        torre->top = top_atual->prox;
        free(top_atual);
        return valor;
    }
    return 0;
}

static void liberar_pilha(Torre *torre) {
    while (torre->top != NULL) {
        pop(torre);
    }
}

static void imprimir_torre(const Torre* t, int nivel, int n_max) {
    int largura_torre = 2 * n_max - 1;
    int disco = disco_no_nivel(t, nivel);
    if (disco > 0) {
        int hashtag = 2 * disco - 1;
        int espaco = (largura_torre - hashtag) / 2;
        for (int s = 0; s < espaco; s++) { printf(" "); }
        for (int h = 0; h < hashtag; h++) { printf("#"); }
        for (int s = 0; s < espaco; s++) { printf(" "); }
    } else {
        for (int s = 0; s < n_max - 1; s++) { printf(" "); }
        printf("|");
        for (int s = 0; s < n_max - 1; s++) { printf(" "); }
    }
}

static void mostrar_torres() {
    printf("\n");
    for (int i = n - 1; i >= 0; i--) {
        imprimir_torre(&torreA, i, n);
        printf("   ");
        imprimir_torre(&torreB, i, n);
        printf("   ");
        imprimir_torre(&torreC, i, n);
        printf("\n");
    }
    int largura_torre = 2 * n - 1;
    for (int t = 0; t < 3; t++) {
        for (int j = 0; j < largura_torre; j++) { printf("="); }
        if (t < 2) { printf("   "); }
    }
    printf("\n");
    for (int t = 0; t < 3; t++) {
        for (int j = 0; j < n - 1; j++) { printf(" "); }
        printf("%c", 'A' + t);
        for (int j = 0; j < n - 1; j++) { printf(" "); }
        if (t < 2) { printf("   "); }
    }
    printf("\n\n");
}

static Torre* torre_por_nome(char nome) {
    switch (nome) {
        case 'A': return &torreA;
        case 'B': return &torreB;
        case 'C': return &torreC;
        default: return NULL;
    }
}

static int validar_movimento(Torre *origem, Torre *destino) {
    if (!origem || !destino) {
        printf("\n>> MOVIMENTO INVALIDO: Torre nao existe. Use A, B ou C.");
        return 0;
    }
    if (origem == destino) {
        printf("\n>> MOVIMENTO INVALIDO: As torres de origem e destino devem ser diferentes.");
        return 0;
    }
    if (origem->top == NULL) {
        printf("\n>> MOVIMENTO INVALIDO: A torre de origem '%c' esta vazia.", origem->nome);
        return 0;
    }
    if (destino->top != NULL && origem->top->discos > destino->top->discos) {
        printf("\n>> MOVIMENTO INVALIDO: Nao e possivel colocar um disco maior sobre um menor.");
        return 0;
    }
    return 1;
}

static void executar_movimento(Torre *origem, Torre *destino) {
    int discos = pop(origem);
    push(destino, discos);
}

static int altura_torre(const Torre* torre) {
    int altura = 0;
    Node *atual = torre->top;
    while (atual) {
        altura++;
        atual = atual->prox;
    }
    return altura;
}

static int disco_no_nivel(const Torre* torre, int nivel) {
    int altura = altura_torre(torre);
    if (nivel >= altura) return 0;
    int index_reverso = altura - 1 - nivel;
    Node *atual = torre->top;
    for (int i = 0; i < index_reverso; i++) {
        if(atual) atual = atual->prox;
    }
    return atual ? atual->discos : 0;
}