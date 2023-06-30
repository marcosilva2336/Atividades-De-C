/****************************************************************** 
 * Nome: Lista Com vetores                                        *
 * Autores: João Marcos e Lucas Matheus                           *
 ******************************************************************/

/* Importação de Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



/* Criação da Lista e do Nó, que será responsável pela conexão entre os itens da lista */
typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista{
    ListaNo *primeiro;
};

/* Responsável pelos campos da Estrutura do Roteador */
struct listaNo{
    ListaNo *anterior;
    ListaNo *prox;
    char marca[50];
    char modelo[50];
    float velocidade;
    int antenas;
    int portas;
    char sistemaOperacional[50];
    float valor;
};


/* === Funções Implementadas === */
Lista* criarLista();
int inserirElemento(Lista*, ListaNo*);
int inserirElementoID(Lista*, ListaNo*, int);
int inserirElementoInicio(Lista*, ListaNo*);
void listarElementos(Lista*);
void listarElementosOrdemInversa(Lista*);
int removerElemento(Lista*, int);
int removerElementoNome(Lista*, char*);
int atualizarElemento(Lista*, char*, char*);
int buscarNome(Lista*, char*);
int buscarIndex(Lista*, int);
int tamanhoLista(Lista*);
Lista* excluirLista(Lista*);
int executavel();
int selecaoOperacao();
ListaNo* criarElemento();
int hackFunc(Lista*, char*, char*, float, int, int, char*, float);
int registrandoDados(Lista*);

/* Função Main */
int main(){
    executavel();
    return 0;
}

int executavel(){

    Lista *lista;
    ListaNo *no;

    int operacao = 1;

    do{
        if(operacao == 1){
            printf("\n=============================================================================\n");
            printf("\t\t* Olá, seja bem vindo ao Controle de Roteadores.\n\n");
            printf("\tNotei que você não tem nenhuma lista de roteadores, não é? \n\tAntes de prosseguir, você precisa criar uma lista.\n\n\tPressione 1 - para criar uma lista\n\tPressione 2 - para finalizar o programa\n");
            int criarRoteador;
            scanf("%d", &criarRoteador);
            printf("\n=============================================================================\n");
            if(criarRoteador == 1){
                operacao = 0;
                lista = criarLista();
            } else{
                operacao = -1;
            }
        }
        else{
            operacao = selecaoOperacao(lista);
        }
        // system("tput reset"); 
    } while(operacao >= 0);

    return 0;
}

int selecaoOperacao(Lista *lista){
    printf("\n====================================================================================================\n");
    printf("\t\t\t\tDigite a opção que deseja executar: \n\n");
    printf("\tPressione 1 - para inserir um elemento na lista.\n");
    printf("\tPressione 2 - para inserir um elemento na lista, a partir de uma determinada posição.\n");
    printf("\tPressione 3 - para inserir um elemento na lista, como primeiro item.\n");
    printf("\tPressione 4 - para listar os elementos da lista.\n");
    printf("\tPressione 5 - para listar os elementos da lista na ordem inversa, isto é, de trás para frente..\n");
    printf("\tPressione 6 - para remover um elemento na lista.\n");
    printf("\tPressione 7 - para remover um elemento na lista, a partir de modelo ou marca.\n");
    printf("\tPressione 8 - para atualizar um elemento na lista, 0a partir do modelo ou marca.\n");
    printf("\tPressione 9 - para buscar um elemento na lista.\n");
    printf("\tPressione 10 - para saber o tamanho da lista.\n");
    printf("\tPressione 11 - para excluir a lista.\n");
    printf("\tPressione 12 - para finalizar o programa.\n");
    
    int operacao;
    scanf("%d", &operacao);
    
    switch (operacao) {
    case 1:
        inserirElemento(lista, criarElemento());
        break;
    
    case 2:
        ListaNo *novoElemento = criarElemento();
        printf("Digite em qual posição deseja adicionar o roteador: ");
        int posicao;
        scanf("%d", &posicao);
        inserirElementoID(lista, novoElemento, posicao);
        break;
    
    case 3:
        inserirElementoInicio(lista, criarElemento());
        break;

    case 4:
        listarElementos(lista);
        break;
        
    case 5:
        listarElementosOrdemInversa(lista);
        break;
    
    case 6:
        printf("Digite em qual posição deseja remover o roteador: ");
        int posicaoRemocao;
        scanf("%d", &posicaoRemocao);
        removerElemento(lista, posicaoRemocao);
        break;
    
    case 7:
        char nomeRemocao[50];
        printf("Digite qual o modelo ou deseja remover: ");
        scanf("%s", nomeRemocao);
        removerElementoNome(lista, nomeRemocao);
        break;
    
    case 8:
        // buscarIndex(lista, 4);
        char nomeAntigo[50];
        char novoNome[50];
        printf("Digite qual o modelo ou marca que deseja atualizar: ");
        scanf("%s", nomeAntigo);
        printf("\nDigite o novo nome para modelo ou marca: ");
        scanf("%s", novoNome);
        atualizarElemento(lista, nomeAntigo, novoNome);
        break;
    
    case 9:
        char nomeBusca[50];
        printf("Digite qual o modelo deseja visualizar: ");
        scanf("%s", nomeBusca);
        int pos = buscarNome(lista, nomeBusca);
        // buscarNome();
        break;
    
    case 10:
        printf("A lista tem %d roteadores.\n", tamanhoLista(lista));
        break;
    
    case 11:
        excluirLista(lista);
        return 1;
    
    case 12:
        return registrandoDados(lista);
    
    case 13:
        hackFunc(lista, "Tp-Link", "hpl-kam", 360, 8, 9, "Windows", 1560);
        hackFunc(lista, "Ap-Sink", "hpk-lsm", 360, 8, 9, "IOS", 3560);
        hackFunc(lista, "CB-SLink", "hpp-lks", 360, 8, 9, "Powershell", 1260);
        hackFunc(lista, "Abts-kk", "col-bhc", 360, 8, 9, "LinuxMinrt", 500);
        // listarElementos(lista);
        break;

    
    default:
        printf("Desculpa, Digite um número válido!\n\n");
        sleep(1);
        break;
    }

    int bla = 0;
    return bla;
}

/* Função Responsável pela criação de uma Lista */
Lista* criarLista(){
    // Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    // Verifica se o espaço foi realmente alocado
    if (nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return NULL;
    }

    nova->primeiro = NULL;
    return nova;
}

/* Função Responsável pela criação de um elemento*/
ListaNo* criarElemento(){
    ListaNo *lista = (ListaNo*) malloc(sizeof(ListaNo)); // aloca espaço para um novo elemento

    char marca[50];
    printf("Digite a marca do roteador: ");
    scanf("%s", marca);
    strcpy(lista->marca, marca);

    char modelo[50];
    printf("Digite o modelo do roteador: ");
    scanf("%s", modelo);
    strcpy(lista->modelo, modelo);
    
    float velocidade;
    printf("Digite a velocidade do roteador: ");
    scanf("%f", &velocidade);
    lista->velocidade = velocidade;
    
    int antenas;
    printf("Digite a quantidade de antenas do roteador: ");
    scanf("%d", &antenas);
    lista->antenas = antenas;
    
    int portas;
    printf("Digite a quantidade de portas do roteador: ");
    scanf("%d", &portas);
    lista->portas = portas;
    
    char sistemaOperacional[50];
    printf("Digite o Sistema Operacional do roteador: ");
    scanf("%s", sistemaOperacional);
    strcpy(lista->sistemaOperacional, sistemaOperacional);
    

    float valor;
    printf("Digite o valor do roteador: ");
    scanf("%f", &valor);
    lista->valor = valor;

    lista->prox = NULL;
    lista->anterior = NULL;

    return lista; // retorna o ponteiro para o novo elemento criado
}

/* Função Repsonsável por adicionar novos elementos para lista */
int inserirElemento(Lista *lista, ListaNo *nova){
    /* Verificando se há espaço disponível */
    if(nova == NULL){
        printf("Não foi possível alocar espaço para o elemento.\n");
        return 0;
    }

    /* Verifica se a lista está vazia. Se sim, coloca o roteador criado anteriormente como primeiro item. */
    if(lista->primeiro == NULL){
        lista->primeiro = nova;
        return 1;
    }

    /* Se ela já contiver algum item, vai buscar o último valor, e alocar o roteador em seguida.*/
    ListaNo *p;
    for(p = lista->primeiro; p->prox != NULL; p = p->prox);

    p->prox = nova;
    nova->anterior = p;

    return 1;
}

/* Função responsável por adicionar novos elementos para lista, em um posição específica */
int inserirElementoID(Lista *lista, ListaNo *nova, int posicao){
    // Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista
    ListaNo *p;

   
    /* Verificando se há espaço disponível */
    if(nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return 0;
    }
    /* Verificando se o ID passado é da primeira posição */
    if(posicao == 1){
        inserirElementoInicio(lista, nova);
        return 0;
    }

    /* Verifica se a lista está vazia. Se sim, coloca o roteador criado anteriormente como primeiro item. */
    if(lista->primeiro == NULL){
        printf("A Lista está vazia, então a única maneira de adicionar esse roteador é colocando-o na primeira posição. Deseja fazer isso? \nDigite 1 - SIM \t\t Digite 2 - NÃO \n");
        int choice;
        /* Pergunta se a pessoa deseja adicionar como valor inicial, uma vez que a lista está vazia */
        scanf("%d", &choice);
        if(choice == 1){
            lista->primeiro = nova;
            nova->prox = NULL;
            nova->anterior = NULL;
            return 1;
        }
        return 0;
    }

    /* Verifica a posição do item e logo em sequida insere o roteador na posição desejada pelo usuário */
    int i = 1;
    for(p = lista->primeiro; i != posicao - 1; p = p->prox){
        ++i;
        printf("%s ", p->modelo);
    }

    //hpl - x - hpk
    nova->prox = p->prox;
    nova->anterior = p;
    p->prox->anterior = nova;
    p->prox = nova;

    return 1;
}

/* Função responsável por adicionar novos elementos para lista, no início da lista */
int inserirElementoInicio(Lista *lista, ListaNo *nova){
    // Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista
    ListaNo *aux;
    
    /* Verificando se há espaço disponível */
    if(nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return 0;
    }

    /* Verifica se a lista está vazia. Se sim, coloca o roteador criado anteriormente como primeiro item. */
    if(lista->primeiro == NULL){
        nova->anterior = NULL;
        nova->prox = NULL;
        lista->primeiro = nova;
        return 1;
    }

    /* Adição de um novo roteador e alocação daquele, que até então, era o primeiro, para segunda posição */
    aux = lista->primeiro;
    nova->prox = aux;
    aux->anterior = nova;
    lista->primeiro = nova;

    return 1;
}

/* Função responsável por retornar a quantidade de itens dentro da lista */
int tamanhoLista(Lista *lista){
    ListaNo *p;  

    /* Calcula quantos itens tem na lista, através do contador */
    int contador = 0;
    for(p = lista->primeiro; p != NULL; p = p->prox){
        ++contador;
    }

    
    return contador;
}

/* Função responsável por remover elementos da lista, a partir de uma posição específica */
int removerElemento(Lista *lista, int posicao){
    ListaNo *aux;
    ListaNo *p;

    /* Verificando se a lista existe */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista foi criada*/
    if(lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    /* Verifica se a posição de exclusão desejada é o primeiro valor */
    if(posicao == 1){
        p = lista->primeiro;
        aux = lista->primeiro->prox;
        aux->anterior = NULL;
        lista->primeiro = aux;
        free(p);
        printf("Roteador excluído da lista com sucesso!\n");
        return 0;
    }

    /* Verifica se a posição de exclusão desejada está entre o primeiro e o último valor */
    int i = 0;
    for(p = lista->primeiro; p->prox->prox != NULL; p = p->prox){
        ++i;
        if(i + 1 == posicao){
            aux = p->prox;
            p->prox = p->prox->prox;
            p->prox->anterior = p; 
            free(aux);
            printf("\n\n=========================\n\n");
            printf("Roteador excluído da lista com sucesso!\n");
            return 1;
        }
    }
    
    /* Verifica se a posição de exclusão desejada é o último valor da lista */
    aux = p->prox;
    p->prox = NULL;
    free(aux);
    printf("Roteador excluído da lista com sucesso!\n");
    return 1;

}

/* Função responsável por remover elementos da lista, a partir de um dado específico, seja ele modelo ou marca */
int removerElementoNome(Lista *lista, char* nome){
    printf("Entrou como %s", nome);
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    if(lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }
    
    int posicaoNome = buscarNome(lista, nome); 
    printf("é, relamente tá na %d", posicaoNome);
    removerElemento(lista, posicaoNome);
    return 1;
}

/* Função Responsável pela Busca de Elementos a partir da marca ou modelo, e retornar sua posição na lista */
int buscarNome(Lista *lista, char *valor){
    ListaNo *p;
    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return -1;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return -1;
    }

    int i = 0;
    for(p = lista->primeiro; p != NULL; p = p->prox){
        ++i;
        
        /*Verificando se o elemento atual e igual ao valor buscado*/
        if(strcmp(p->marca, valor) == 0 || strcmp(p->modelo, valor) == 0){
            buscarIndex(lista, i);
            return i;
        }
    }
    return i;
}

/* Função Responsável pela Busca de Elementos a partir da posição na Lista, e retornar o roteador naquela posição da lista */
int buscarIndex(Lista *lista, int posicao){
    ListaNo *p;
    
    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return -1;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return -1;
    }

    /* Busca os valores a partir daquele index */
    int i = 0;
    for(p = lista->primeiro; i != posicao; p = p->prox){
        ++i;
        if(i == posicao){
            printf("\nMarca: %s \n", p->marca);
            printf("Modelo: %s \n", p->modelo);
            printf("Velocidade: %.2f Mbps\n", p->velocidade);
            printf("Antenas: %d \n", p->antenas);
            printf("Portas: %d \n", p->portas);
            printf("Sistema operacional: %s \n", p->sistemaOperacional);
            printf("Valor: R$ %.2f \n\n", p->valor);
            return 1;
        }
    } 
    return -1;
}

/* Função Responsável pela atualização dos elementos */
int atualizarElemento(Lista *lista, char* antigo, char* novo){
    ListaNo *p;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    int posicao = buscarNome(lista, antigo);

    /*Verificando se a posição onde ocorrerá a atualização está entre o primeiro valor e o penúltimo */
    int i = 1;
    p = lista->primeiro;
    do {
        printf("%d == %d\n", i, posicao);
		if(i == posicao){
            printf("Roteador atualizado com sucesso!\n");
            if(strcmp(p->marca, antigo) == 0){
                strcpy(p->marca, novo);
                
                return 1;
            } else if(strcmp(p->modelo, antigo) == 0){
                strcpy(p->modelo, novo);
                return 1;
            }
		}
        i++;
    	p = p->prox;
	}
	while(p->prox != NULL);
    
    /*Verificando se a posição onde ocorrerá a atualização é o último */
    if(strcmp(p->marca, antigo) == 0){
        strcpy(p->marca, novo);
        return 1;
    } else if(strcmp(p->modelo, antigo) == 0){
        strcpy(p->modelo, novo);
        return 1;
    }

    return 0;
}

/* Função responsável pela exclusão da lista */
Lista* excluirLista(Lista* lista){
    ListaNo *aux;
    ListaNo *p;

    p = lista->primeiro;
    do {
        aux = p->prox;
        p = aux->prox;
        free(aux);
    	p = p->prox;
	}
	while(p->prox != NULL);

    free(lista);
    printf("lista excluida!\n");
    return NULL;
}

/* Função Responsável pela impressão de uma lista, isto é, mostrar seus itens */
void listarElementos(Lista *lista){
    ListaNo *p;

    if(lista == NULL){
        printf("Não foi possível listar elementos pois a lista não foi criada.\n");
        return ;
    }

    if(lista->primeiro == NULL){
        printf("Não foi possível listar elementos pois a lista está vazia.\n");
        return ;
    }

    for(p = lista->primeiro; p != NULL; p = p->prox){
        printf("\nMarca: %s \n", p->marca);
        printf("Modelo: %s \n", p->modelo);
        printf("Velocidade: %.2f Mbps\n", p->velocidade);
        printf("Antenas: %d \n", p->antenas);
        printf("Portas: %d \n", p->portas);
        printf("Sistema operacional: %s \n", p->sistemaOperacional);
        printf("Valor: R$ %.2f \n\n", p->valor);
    }

    // printf("Pressione qualquer tecla para continuar...");
    fflush(stdout);
    getchar();

    return;
}

/* Função Responsável pela impressão de uma lista, isto é, mostrar seus itens */
void listarElementosOrdemInversa(Lista *lista){
    ListaNo *p;

    if(lista == NULL){
        printf("Não foi possível listar elementos pois a lista não foi criada.\n");
        return ;
    }

    if(lista->primeiro == NULL){
        printf("Não foi possível listar elementos pois a lista está vazia.\n");
        return ;
    }

    /* Se ela já contiver algum item, vai buscar o último valor, e alocar o roteador em seguida.*/
    for(p = lista->primeiro; p->prox != NULL; p = p->prox);

    /* Percorre de trás para frente, do último ao primeiro valor */
    for(p = p; p != NULL; p = p->anterior){
        printf("\nMarca: %s \n", p->marca);
        printf("Modelo: %s \n", p->modelo);
        printf("Velocidade: %.2f Mbps\n", p->velocidade);
        printf("Antenas: %d \n", p->antenas);
        printf("Portas: %d \n", p->portas);
        printf("Sistema operacional: %s \n", p->sistemaOperacional);
        printf("Valor: R$ %.2f \n\n", p->valor);
    }

    // printf("Pressione qualquer tecla para continuar...");
    fflush(stdout);
    getchar();

    return ;
}

/* Função que cria alguns Roteadores, feito apenas para teste */
int hackFunc(Lista *lista, char* marca, char* modelo,float velocidade,int antenas,int portas,char* sistemaOperacional,float valor){
    // Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista
    ListaNo *p;
    ListaNo *nova = (ListaNo*)malloc(sizeof(ListaNo));
    
    /* Verificando se há espaço disponível */
    if(nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return 0;
    }

    /* Cria um roteador, e logo em seguida salva ele na lista */
    strcpy(nova->marca, marca);
    strcpy(nova->modelo, modelo);
    nova->velocidade = velocidade;
    nova->antenas = antenas;
    nova->portas = portas;
    strcpy(nova->sistemaOperacional, sistemaOperacional);
    nova->valor = valor;

    nova->prox = NULL;

    /* Verifica se a lista está vazia. Se sim, coloca o roteador criado anteriormente como primeiro item. */
    if(lista->primeiro == NULL){
        lista->primeiro = nova;
        nova->anterior = NULL;
        return 1;
    }

    /* Se ela já contiver algum item, vai buscar o último valor, e alocar o roteador em seguida.*/
    for(p = lista->primeiro; p->prox != NULL; p = p->prox);

    p->prox = nova;
    nova->anterior = p;

    return 1;

}

int registrandoDados(Lista *lista){
    ListaNo *p;

    FILE *arquivo = fopen("roteadores.txt", "wb"); // abrindo arquivo para escrita binária
    int tamLista = tamanhoLista(lista);
    


    if (arquivo != NULL) {
        for(p = lista->primeiro; p != NULL; p = p->prox){
            fprintf(arquivo, "Marca: %s\nModelo: %s\nVelocidade: %f\nAntenas: %d\nPortas: %d\nSistema Operacional: %s\n\n", p->marca, p->modelo, p->velocidade, p->antenas, p->portas, p->sistemaOperacional);        
        }
        
        fclose(arquivo); // fechando arquivo
    } else {
        printf("Erro ao abrir arquivo!\n");
    }
}