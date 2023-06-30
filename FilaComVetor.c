#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o da estrutura Roteador
typedef struct roteador {
    struct roteador *prox;
    char marca[50];
    char modelo[50];
    float velocidade;
    int antenas;
    int portas;
    char sistemaOperacional[50];
    float valor;
    char problemaTecnico[100];
    char manutencaoRealizada;
    char tecnicoResponsavel[50];
} Roteador;

// Defini��o da estrutura Fila
typedef struct {
    Roteador **fila;
    int capacidade;
    int tamanho;
    int inicio;
    int fim;
} Fila;

// Vari�vel global para a fila
Fila* filaGlobal = NULL;

// Fun��o para criar uma nova fila
Fila* criarFila() {
    int capacidade;
    printf("Digite a capacidade da fila: ");
    scanf("%d", &capacidade);

    // Aloca mem�ria para a nova fila
    Fila *novaFila = (Fila*)malloc(sizeof(Fila));
    novaFila->fila = (Roteador**)malloc(capacidade * sizeof(Roteador*));

    // Inicializa os atributos da fila
    novaFila->capacidade = capacidade;
    novaFila->tamanho = 0;
    novaFila->inicio = 0;
    novaFila->fim = -1;

    return novaFila;
}

// Fun��o para verificar se a fila est� cheia
int verificarFilaCheia(Fila *fila) {
    return (fila->tamanho >= fila->capacidade);
}

// Fun��o para adicionar um roteador � fila
int enqueue(Fila *fila, Roteador *elemento) {
    if (verificarFilaCheia(fila)) {
        printf("Erro: Fila cheia\n");
        return 0;
    }

    // Atualiza o �ndice do fim da fila circularmente
    fila->fim = (fila->fim + 1) % fila->capacidade;

    // Insere o elemento no final da fila
    fila->fila[fila->fim] = elemento;

    // Atualiza o tamanho da fila
    fila->tamanho++;

    return 1;
}

// Fun��o para imprimir os elementos da fila
void imprimirElementos(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("Fila vazia\n");
        return;
    }

    // Itera sobre os elementos da fila e imprime suas informa��es
    int i;
    for (i = 0; i < fila->tamanho; i++) {
        int index = (fila->inicio + i) % fila->capacidade;
        Roteador *elemento = fila->fila[index];
        printf("Marca: %s\n", elemento->marca);
        printf("Modelo: %s\n", elemento->modelo);
        printf("Velocidade: %.2f Mbps\n", elemento->velocidade);
        printf("Antenas: %d\n", elemento->antenas);
        printf("Portas: %d\n", elemento->portas);
        printf("Sistema Operacional: %s\n", elemento->sistemaOperacional);
        printf("Valor: R$ %.2f\n", elemento->valor);
        printf("Problema T�cnico: %s\n", elemento->problemaTecnico);
        printf("Manuten��o Realizada: %c\n", elemento->manutencaoRealizada);
        printf("T�cnico Respons�vel: %s\n", elemento->tecnicoResponsavel);
        printf("-------------------------\n");
    }
}

// Fun��o para remover um roteador da fila
int dequeue(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("Erro: Fila vazia\n");
        return 0;
    }

    // Obt�m o elemento no in�cio da fila
    Roteador *elemento = fila->fila[fila->inicio];

    // Atualiza o �ndice do in�cio da fila circularmente
    fila->inicio = (fila->inicio + 1) % fila->capacidade;

    // Atualiza o tamanho da fila
    fila->tamanho--;

    // Libera a mem�ria do elemento removido
    free(elemento);

    return 1;
}

// Fun��o para obter o tamanho atual da fila
int tamanhoFila(Fila *fila) {
    return fila->tamanho;
}

// Fun��o para excluir todos os elementos da fila e liberar a mem�ria
Fila* excluirFila(Fila *fila) {
    while (fila->tamanho > 0) {
        dequeue(fila);
    }

    // Libera a mem�ria da fila e retorna NULL
    free(fila->fila);
    free(fila);
    return NULL;
}

// Fun��o para criar um novo elemento do tipo Roteador
Roteador* criarElemento() {
    Roteador *elemento = (Roteador*)malloc(sizeof(Roteador));
    printf("Marca: ");
    scanf("%s", elemento->marca);
    printf("Modelo: ");
    scanf("%s", elemento->modelo);
    printf("Velocidade (Mbps): ");
    scanf("%f", &elemento->velocidade);
    printf("Antenas: ");
    scanf("%d", &elemento->antenas);
    printf("Portas: ");
    scanf("%d", &elemento->portas);
    printf("Sistema Operacional: ");
    scanf("%s", elemento->sistemaOperacional);
    printf("Valor: R$ ");
    scanf("%f", &elemento->valor);
    printf("Problema T�cnico: ");
    scanf("%s", elemento->problemaTecnico);
    printf("Manuten��o Realizada ('N' - N�o, 'S' - Sim): ");
    scanf(" %c", &elemento->manutencaoRealizada);
    printf("T�cnico Respons�vel: ");
    scanf("%s", elemento->tecnicoResponsavel);
    return elemento;
}

// Fun��o para mostrar os elementos da fila
void mostrarFila() {
    if (filaGlobal == NULL) {
        printf("Erro: Fila n�o foi criada\n");
        return;
    }

    printf("===== Roteadores na Fila =====\n");
    imprimirElementos(filaGlobal);
    printf("==============================\n");
}

// Fun��o para registrar os dados de um novo roteador
void registrandoDados() {
    if (filaGlobal == NULL) {
        printf("Erro: Fila n�o foi criada\n");
        return;
    }

    if (verificarFilaCheia(filaGlobal)) {
        printf("Erro: Fila cheia\n");
        return;
    }

    Roteador *elemento = criarElemento();
    if (enqueue(filaGlobal, elemento))
        printf("Roteador adicionado com sucesso!\n");
    else
        printf("Erro ao adicionar roteador\n");
}

// Fun��o para excluir a fila e encerrar o programa
void excluirFilaEEncerrarPrograma() {
    if (filaGlobal == NULL) {
        printf("Erro: Fila n�o foi criada\n");
        return;
    }

    excluirFila(filaGlobal);
    printf("Fila exclu�da com sucesso!\n");
    printf("Encerrando programa...\n");
    exit(0);
}

// Fun��o para localizar um elemento na fila pelo seu modelo e marca
void localizarElemento(Fila *fila, char *marca, char *modelo) {
    if (fila->tamanho == 0) {
        printf("Erro: Fila vazia\n");
        return;
    }

    int i;
    for (i = 0; i < fila->tamanho; i++) {
        int index = (fila->inicio + i) % fila->capacidade;
        Roteador *elemento = fila->fila[index];
        if (strcmp(elemento->marca, marca) == 0 && strcmp(elemento->modelo, modelo) == 0) {
            printf("Elemento encontrado:\n");
            printf("Posi��o: %d\n", index);
            printf("Marca: %s\n", elemento->marca);
            printf("Modelo: %s\n", elemento->modelo);
            printf("Velocidade: %.2f Mbps\n", elemento->velocidade);
            printf("Antenas: %d\n", elemento->antenas);
            printf("Portas: %d\n", elemento->portas);
            printf("Sistema Operacional: %s\n", elemento->sistemaOperacional);
            printf("Valor: R$ %.2f\n", elemento->valor);
            printf("Problema T�cnico: %s\n", elemento->problemaTecnico);
            printf("Manuten��o Realizada: %c\n", elemento->manutencaoRealizada);
            printf("T�cnico Respons�vel: %s\n", elemento->tecnicoResponsavel);
            return;
        }
    }

    printf("Roteador n�o encontrado na fila\n");
}

// Fun��o para obter a capacidade dispon�vel na fila
int capacidadeDisponivel(Fila *fila) {
    return (fila->capacidade - fila->tamanho);
}

// Fun��o para mostrar apenas os roteadores que tiveram suas manuten��es realizadas
void mostrarRoteadoresComManutencaoRealizada() {
    if (filaGlobal == NULL) {
        printf("Erro: Fila n�o foi criada\n");
        return;
    }

    int i;
    int encontrados = 0;
    for (i = 0; i < filaGlobal->tamanho; i++) {
        int index = (filaGlobal->inicio + i) % filaGlobal->capacidade;
        Roteador *elemento = filaGlobal->fila[index];
        if (elemento->manutencaoRealizada == 'S') {
            printf("Marca: %s\n", elemento->marca);
            printf("Modelo: %s\n", elemento->modelo);
            printf("Velocidade: %.2f Mbps\n", elemento->velocidade);
            printf("Antenas: %d\n", elemento->antenas);
            printf("Portas: %d\n", elemento->portas);
            printf("Sistema Operacional: %s\n", elemento->sistemaOperacional);
            printf("Valor: R$ %.2f\n", elemento->valor);
            printf("Problema T�cnico: %s\n", elemento->problemaTecnico);
            printf("Manuten��o Realizada: %c\n", elemento->manutencaoRealizada);
            printf("T�cnico Respons�vel: %s\n", elemento->tecnicoResponsavel);
            printf("-------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum roteador com manuten��o realizada encontrado\n");
    }
}

// Fun��o para listar os roteadores consertados por determinado t�cnico
void listarRoteadoresConsertadosPorTecnico(char *nomeTecnico) {
    if (filaGlobal == NULL) {
        printf("Erro: Fila n�o foi criada\n");
        return;
    }

    int i;
    int encontrados = 0;
    for (i = 0; i < filaGlobal->tamanho; i++) {
        int index = (filaGlobal->inicio + i) % filaGlobal->capacidade;
        Roteador *elemento = filaGlobal->fila[index];
        if (strcmp(elemento->tecnicoResponsavel, nomeTecnico) == 0 && elemento->manutencaoRealizada == 'S') {
            printf("Marca: %s\n", elemento->marca);
            printf("Modelo: %s\n", elemento->modelo);
            printf("Velocidade: %.2f Mbps\n", elemento->velocidade);
            printf("Antenas: %d\n", elemento->antenas);
            printf("Portas: %d\n", elemento->portas);
            printf("Sistema Operacional: %s\n", elemento->sistemaOperacional);
            printf("Valor: R$ %.2f\n", elemento->valor);
            printf("Problema T�cnico: %s\n", elemento->problemaTecnico);
            printf("Manuten��o Realizada: %c\n", elemento->manutencaoRealizada);
            printf("-------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum roteador consertado pelo t�cnico '%s' encontrado\n", nomeTecnico);
    }
}

int main() {
    int opcao;
    do {
        printf("===== Menu =====\n");
        printf("1. Criar fila\n");
        printf("2. Adicionar roteador\n");
        printf("3. Remover roteador da fila\n");
        printf("4. Tamanho da fila\n");
        printf("5. Mostrar fila\n");
        printf("6. Localizar elemento na fila\n");
        printf("7. Capacidade dispon�vel\n");
        printf("8. Mostrar roteadores com manuten��o realizada\n");
        printf("9. Listar roteadores consertados por t�cnico\n");
        printf("10. Excluir fila e encerrar programa\n");
        printf("Digite a op��o desejada: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                if (filaGlobal != NULL) {
                    printf("Erro: Fila j� foi criada\n");
                    break;
                }
                filaGlobal = criarFila();
                printf("Fila criada com sucesso!\n");
                break;
            }
            case 2: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                registrandoDados();
                break;
            }
            case 3: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                dequeue(filaGlobal);
                printf("Roteador removido com sucesso!\n");
                break;
            }
            case 4: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                printf("Tamanho da fila: %d\n", tamanhoFila(filaGlobal));
                break;
            }
            case 5: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                mostrarFila();
                break;
            }
            case 6: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                char marca[50], modelo[50];
                printf("Digite a marca do roteador: ");
                scanf("%s", marca);
                printf("Digite o modelo do roteador: ");
                scanf("%s", modelo);
                localizarElemento(filaGlobal, marca, modelo);
                break;
            }
            case 7: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                printf("Capacidade dispon�vel: %d\n", capacidadeDisponivel(filaGlobal));
                break;
            }
            case 8: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                mostrarRoteadoresComManutencaoRealizada();
                break;
            }
            case 9: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                char nomeTecnico[50];
                printf("Digite o nome do t�cnico: ");
                scanf("%s", nomeTecnico);
                listarRoteadoresConsertadosPorTecnico(nomeTecnico);
                break;
            }
            case 10: {
                if (filaGlobal == NULL) {
                    printf("Erro: Fila n�o foi criada\n");
                    break;
                }
                excluirFilaEEncerrarPrograma();
                break;
            }
            default:
                printf("Op��o inv�lida\n");
                break;
        }
    } while (1);

    return 0;
}
