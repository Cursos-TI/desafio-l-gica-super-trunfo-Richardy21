#include <stdio.h>
#include <string.h> // Necessário para a função strcspn

// A struct 'Carta' funciona como um "molde" para agrupar
// todas as informações de um país em um só lugar.
typedef struct {
    char estado[3]; // Ex: "SP", "RJ"
    char codigo[10];
    char cidade[50];
    long int populacao; // Usando long int para populações grandes
    float area;
    float pib; // Em bilhões de R$
    int pontosTuristicos;
    double densidadePopulacional;
    double pibPerCapita;
} Carta;

// --- FUNÇÕES AUXILIARES ---

// Função para limpar o buffer do teclado.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- FUNÇÕES DE CADASTRO E CÁLCULO ---

/**
 * @brief Lê os dados de uma carta inseridos pelo usuário.
 * @param c Ponteiro para a carta que será preenchida.
 * @param numeroDaCarta O número da carta (1 ou 2) para exibir na mensagem.
 */
void lerDadosCarta(Carta *c, int numeroDaCarta) {
    printf("\n--- Cadastro da Carta %d ---\n", numeroDaCarta);

    printf("Digite a sigla do Estado (ex: SP): ");
    scanf("%2s", c->estado); // Lê até 2 caracteres para o estado
    limparBuffer();

    printf("Digite o código da carta (ex: A01): ");
    scanf("%s", c->codigo);
    limparBuffer();

    printf("Digite o nome da cidade/país: ");
    fgets(c->cidade, sizeof(c->cidade), stdin);
    c->cidade[strcspn(c->cidade, "\n")] = 0; // Remove o '\n' do final

    printf("Digite a população (número de habitantes): ");
    scanf("%ld", &c->populacao);

    printf("Digite a área (em km²): ");
    scanf("%f", &c->area);

    printf("Digite o PIB (em bilhões de R$): ");
    scanf("%f", &c->pib);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->pontosTuristicos);
    limparBuffer();
}

/**
 * @brief Calcula os atributos derivados da carta (Densidade e PIB per Capita).
 * @param c Ponteiro para a carta cujos atributos serão calculados.
 */
void calcularAtributos(Carta *c) {
    if (c->area > 0) {
        c->densidadePopulacional = (double)c->populacao / c->area;
    } else {
        c->densidadePopulacional = 0;
    }

    if (c->populacao > 0) {
        // Converte o PIB de bilhões para o valor real
        c->pibPerCapita = (c->pib * 1e9) / c->populacao;
    } else {
        c->pibPerCapita = 0;
    }
}

// --- FUNÇÃO DE COMPARAÇÃO ---

/**
 * @brief Compara um atributo específico entre duas cartas e exibe o resultado.
 * @param c1 A primeira carta para comparação.
 * @param c2 A segunda carta para comparação.
 */
void realizarComparacaoFinal(Carta c1, Carta c2) {
    // --- ESCOLHA O ATRIBUTO PARA COMPARAR AQUI ---
    // Mude a variável 'atributoEscolhido' para o que desejar.
    // Opções: "Populacao", "Area", "PIB", "Pontos Turisticos", "Densidade", "PIB per Capita"
    const char* atributoEscolhido = "Populacao";
    
    printf("\n\n--- Comparação de Cartas (Atributo: %s) ---\n", atributoEscolhido);
    
    // Lógica de comparação para POPULAÇÃO (maior vence)
    if (strcmp(atributoEscolhido, "Populacao") == 0) {
        printf("Carta 1 - %s (%s): %ld\n", c1.cidade, c1.estado, c1.populacao);
        printf("Carta 2 - %s (%s): %ld\n", c2.cidade, c2.estado, c2.populacao);
        printf("Resultado: ");
        if (c1.populacao > c2.populacao) {
            printf("Carta 1 (%s) venceu!\n", c1.cidade);
        } else if (c2.populacao > c1.populacao) {
            printf("Carta 2 (%s) venceu!\n", c2.cidade);
        } else {
            printf("Empate!\n");
        }
    }
    // Lógica de comparação para DENSIDADE (menor vence)
    else if (strcmp(atributoEscolhido, "Densidade") == 0) {
        printf("Carta 1 - %s (%s): %.2f hab/km²\n", c1.cidade, c1.estado, c1.densidadePopulacional);
        printf("Carta 2 - %s (%s): %.2f hab/km²\n", c2.cidade, c2.estado, c2.densidadePopulacional);
        printf("Resultado: ");
        if (c1.densidadePopulacional < c2.densidadePopulacional) {
            printf("Carta 1 (%s) venceu!\n", c1.cidade);
        } else if (c2.densidadePopulacional < c1.densidadePopulacional) {
            printf("Carta 2 (%s) venceu!\n", c2.cidade);
        } else {
            printf("Empate!\n");
        }
    } 
    // Adicione outras comparações aqui usando 'else if' se desejar...
    // Exemplo para PIB:
    else if (strcmp(atributoEscolhido, "PIB") == 0) {
        printf("Carta 1 - %s (%s): %.2f bilhões\n", c1.cidade, c1.estado, c1.pib);
        printf("Carta 2 - %s (%s): %.2f bilhões\n", c2.cidade, c2.estado, c2.pib);
        printf("Resultado: ");
        if (c1.pib > c2.pib) {
            printf("Carta 1 (%s) venceu!\n", c1.cidade);
        } else if (c2.pib > c1.pib) {
            printf("Carta 2 (%s) venceu!\n", c2.cidade);
        } else {
            printf("Empate!\n");
        }
    }
}


// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Declara as duas cartas que serão usadas no jogo
    Carta carta1, carta2;

    // 1. Cadastra as duas cartas
    lerDadosCarta(&carta1, 1);
    lerDadosCarta(&carta2, 2);
    
    // 2. Calcula os atributos derivados para cada carta
    calcularAtributos(&carta1);
    calcularAtributos(&carta2);

    // 3. Realiza a comparação final com base no atributo escolhido no código
    realizarComparacaoFinal(carta1, carta2);

    return 0;
}