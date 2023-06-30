// Feito por Jo�o Marcos e Lucas Ramos


//Sistema de roteadores

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char marca[50];
  char modelo[50];
  float velocidade;
  int antenas;
  int portas;
  char sistemaOperacional[50];
  float valor;
} Roteador;

typedef struct {
  Roteador* elementos;
  int tamanho;
  int capacidade;
} Pilha;

// Fun��o para criar uma nova pilha com a capacidade especificada
Pilha* criarPilha(int capacidade) {
  Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
  pilha->elementos = (Roteador*)malloc(capacidade * sizeof(Roteador));
  pilha->tamanho = 0;
  pilha->capacidade = capacidade;
  return pilha;
}

// Fun��o para inserir um roteador no topo da pilha
void push(Pilha* pilha, Roteador roteador) {
  if (pilha->tamanho == pilha->capacidade) { // Verifica se a pilha est� cheia
    printf("Erro: a pilha est� cheia.\n");
    return;
  }
  pilha->elementos[pilha->tamanho] = roteador; // Insere o roteador no topo
  pilha->tamanho++;
}

// Fun��o para remover o roteador do topo da pilha
void pop(Pilha* pilha) {
  if (pilha->tamanho == 0) { // Verifica se a pilha est� vazia
    printf("Erro: a pilha est� vazia.\n");
    return;
  }
  pilha->tamanho--; // Reduz o tamanho da pilha para remover o elemento do topo
}

// Fun��o para verificar se a pilha est� vazia
int ehVazia(Pilha* pilha) {
  return pilha->tamanho == 0; // Retorna 1 se a pilha est� vazia, 0 caso contr�rio
}

// Fun��o para obter o roteador do topo da pilha
Roteador verTopo(Pilha* pilha) {
  if (pilha->tamanho == 0) { // Verifica se a pilha est� vazia
    printf("Erro: a pilha est� vazia.\n");
    Roteador roteador_vazio;
    memset(&roteador_vazio, 0, sizeof(Roteador));
    return roteador_vazio; // Retorna um roteador vazio se a pilha estiver vazia
  }
  return pilha->elementos[pilha->tamanho - 1]; // Retorna o roteador do topo
}

// Fun��o para excluir a pilha e liberar mem�ria
void excluirPilha(Pilha* pilha) {
  free(pilha->elementos); // Libera a mem�ria dos elementos da pilha
  free(pilha); // Libera a mem�ria da estrutura da pilha
  printf("Pilha exclu�da.\n");
}

// Fun��o para exibir todos os roteadores da pilha
void exibirPilha(Pilha* pilha) {
  if (pilha == NULL) { // Verifica se a pilha foi criada
    printf("Erro: a pilha n�o foi criada.\n");
    return;
  }

  if (ehVazia(pilha)) { // Verifica se a pilha est� vazia
    printf("A pilha est� vazia.\n");
    return;
  }

  printf("=== Roteadores na Pilha ===\n");
  for (int i = pilha->tamanho - 1; i >= 0; i--) {
    Roteador roteador = pilha->elementos[i]; // Obt�m o roteador atual
    printf("Roteador %d:\n", i + 1);
    printf("Marca: %s\n", roteador.marca);
    printf("Modelo: %s\n", roteador.modelo);
    printf("Velocidade: %.2f Mbps\n", roteador.velocidade);
    printf("Antenas: %d\n", roteador.antenas);
    printf("Portas: %d\n", roteador.portas);
    printf("Sistema Operacional: %s\n", roteador.sistemaOperacional);
    printf("Valor: R$ %.2f\n", roteador.valor);
    printf("----------------------\n");
  }
}

int main() {
  Pilha* pilha = NULL; // Inicializa a pilha com NULL
  int opcao;

  do {
    printf("==== Menu ====\n");
    printf("1. Criar pilha\n");
    printf("2. Inserir roteador\n");
    printf("3. Remover roteador\n");
    printf("4. Verificar se a pilha est� vazia\n");
    printf("5. Ver roteador do topo\n");
    printf("6. Exibir pilha\n");
    printf("7. Excluir Pilha\n");
    printf("8. Sair\n");
    printf("Digite sua op��o: ");
    scanf("%d", &opcao);
    getchar(); // L� o caractere de nova linha ap�s a op��o digitada

    switch (opcao) {
      case 1: {
        int capacidade;
        printf("Digite a capacidade da pilha: ");
        scanf("%d", &capacidade);
        pilha = criarPilha(capacidade); // Cria uma nova pilha com a capacidade especificada
        printf("Pilha criada com capacidade %d.\n", capacidade);
        break;
      }
      case 2: {
        if (pilha == NULL) {
          printf("Erro: a pilha n�o foi criada.\n");
          break;
        }
        Roteador roteador;
        printf("Marca: ");
        fgets(roteador.marca, 50, stdin);
        printf("Modelo: ");
        fgets(roteador.modelo, 50, stdin);
        printf("Velocidade: ");
        scanf("%f", &roteador.velocidade);
        printf("Antenas: ");
        scanf("%d", &roteador.antenas);
        printf("Portas: ");
        scanf("%d", &roteador.portas);
        getchar(); // Consumir o caractere de nova linha
        printf("Sistema Operacional: ");
        fgets(roteador.sistemaOperacional, 50, stdin);
        printf("Valor: R$ ");
        scanf("%f", &roteador.valor);
        push(pilha, roteador); // Insere o roteador no topo da pilha
        printf("Roteador inserido na pilha.\n");
        break;
      }
      case 3: {
        if (pilha == NULL) {
          printf("Erro: a pilha n�o foi criada.\n");
          break;
        }
        pop(pilha); // Remove o roteador do topo da pilha
        printf("Roteador removido da pilha.\n");
        break;
      }
      case 4: {
        if (pilha == NULL) {
          printf("Erro: a pilha n�o foi criada.\n");
          break;
        }
        if (ehVazia(pilha))
          printf("A pilha est� vazia.\n");
        else
          printf("A pilha n�o est� vazia.\n");
        break;
      }
      case 5: {
        if (pilha == NULL) {
          printf("Erro: a pilha n�o foi criada.\n");
          break;
        }
        Roteador topo = verTopo(pilha); // Obt�m o roteador do topo da pilha
        printf("=== Roteador do Topo ===\n");
        printf("Marca: %s", topo.marca);
        printf("Modelo: %s", topo.modelo);
        printf("Velocidade: %.2f Mbps\n", topo.velocidade);
        printf("Antenas: %d\n", topo.antenas);
        printf("Portas: %d\n", topo.portas);
        printf("Sistema Operacional: %s", topo.sistemaOperacional);
        printf("Valor: R$ %.2f", topo.valor);
        break;
      }
      case 6:
        exibirPilha(pilha); // Exibe todos os roteadores da pilha
        break;
       case 7: {
        if (pilha == NULL) {
          printf("Erro: a pilha n�o foi criada.\n");
        } else {
          excluirPilha(pilha);
          pilha = NULL;
        }
        break;
      }
      case 8:
        printf("Saindo...\n");
        break;
      default:
        printf("Op��o inv�lida. Tente novamente.\n");
        break;
    }

    printf("\n");
  } while (opcao != 8);

  if (pilha != NULL)
    excluirPilha(pilha); // Libera a mem�ria alocada para a pilha

  return 0;
}
