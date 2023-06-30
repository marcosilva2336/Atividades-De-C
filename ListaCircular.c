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

struct listaNo{
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
int removerElemento(Lista*, int);
int removerElementoNome(Lista*, char*);
int atualizarElemento(Lista*, char*, char*);
int buscarIndex(Lista*, char*);
int buscarNome(Lista*, int);
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
    printf("\tPressione 5 - para remover um elemento na lista.\n");
    printf("\tPressione 6 - para remover um elemento na lista, a partir de modelo ou marca.\n");
    printf("\tPressione 7 - para atualizar um elemento na lista, 0a partir do modelo ou marca.\n");
    printf("\tPressione 8 - para buscar um elemento na lista.\n");
    printf("\tPressione 9 - para saber o tamanho da lista.\n");
    printf("\tPressione 10 - para excluir a lista.\n");
    printf("\tPressione 11 - para finalizar o programa.\n");
    
    int operacao;
    scanf("%d", &operacao);
    
    
    switch (operacao) {
    case 1:
        inserirElemento(lista, criarElemento());
        break;
    
    case 2:
        printf("Digite em qual posição deseja adicionar o roteador: ");
        int posicaoNovoRoteador;
        scanf("%d", &posicaoNovoRoteador);
        ListaNo *novoElemento = criarElemento();
        inserirElementoID(lista, novoElemento, posicaoNovoRoteador);
        break;
    
    case 3:
        inserirElementoInicio(lista, criarElemento());
        break;

    case 4:
        listarElementos(lista);
        break;
    
    case 5:
        printf("Digite em qual posição deseja remover o roteador: ");
        int posicaoRemocao;
        scanf("%d", &posicaoRemocao);
        removerElemento(lista, posicaoRemocao);
        break;
    
    case 6:
        printf("Digite qual o modelo ou deseja remover: ");
        char nomeRemocao[50];
        scanf("%s", nomeRemocao);
        removerElementoNome(lista, nomeRemocao);
        break;
    
    case 7:
        printf("Digite qual o modelo ou marca que deseja atualizar: ");
        char nomeAntigo[50];
        scanf("%s", nomeAntigo);
        printf("\nDigite o novo nome para modelo ou marca: ");
        char novoNome[50];
        scanf("%s", novoNome);
        atualizarElemento(lista, nomeAntigo, novoNome);
        break;
    
    case 8:
        printf("Digite qual o modelo deseja visualizar: ");
        char nomeBusca[50];
        scanf("%s", nomeBusca);
        int posicaoRoteador = buscarIndex(lista, nomeBusca);
        buscarNome(lista, posicaoRoteador);
        break;
    
    case 9:
        printf("A lista tem %d roteadores.\n", tamanhoLista(lista));
        break;
    
    case 10:
        excluirLista(lista);
        return 1;
    
    case 11:
        return registrandoDados(lista);

    
    case 12:
        hackFunc(lista, "Tp-Link", "hpl-kam", 360, 8, 9, "Windows", 1560);
        hackFunc(lista, "Ap-Sink", "hpk-lsm", 360, 8, 9, "IOS", 3560);
        hackFunc(lista, "CB-SLink", "hpp-lks", 360, 8, 9, "Powershell", 1260);
        hackFunc(lista, "Abts-kk", "col-bhc", 360, 8, 9, "LinuxMinrt", 500);
        break;

    
    default:
        printf("Desculpa, Digite um número válido!\n\n");
        break;
    }

    return 0;
}

/* Função Responsável pela criação de uma Lista */
Lista* criarLista(){
    /* Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista */
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    /* Verifica se o espaço foi realmente alocado */
    if (nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return NULL;
    }

    nova->primeiro = NULL;
    return nova;
}

/* Função Responsável pela criação de um elemento*/
ListaNo* criarElemento(){
    /* Aloca espaço para um novo elemento */
    ListaNo *lista = (ListaNo*) malloc(sizeof(ListaNo)); 

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

    /* Retorna o ponteiro para o novo elemento criado */
    return lista; 
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
        nova->prox = lista->primeiro;
        return 1;
    }

    /* Se ela já contiver algum item, vai buscar o último valor, e alocar o roteador em seguida.*/
    ListaNo *p;
    for(p = lista->primeiro; p->prox != lista->primeiro; p = p->prox);

    p->prox = nova;
    nova->prox = lista->primeiro;

    return 1;
}

/* Função responsável por adicionar novos elementos para lista, em um posição específica */
int inserirElementoID(Lista *lista, ListaNo *nova, int posicao){
    /* Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista */
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
            nova->prox = lista->primeiro;
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

    nova->prox = p->prox;
    p->prox = nova;

    return 1;
}

/* Função responsável por adicionar novos elementos para lista, no início da lista */
int inserirElementoInicio(Lista *lista, ListaNo *nova){
    /* Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista */
    ListaNo *p;
    
    /* Verificando se há espaço disponível */
    if(nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return 0;
    }

    /* Verifica se a lista está vazia. Se sim, coloca o roteador criado anteriormente como primeiro item. */
    if(lista->primeiro == NULL){
        lista->primeiro = nova;
        nova->prox = lista->primeiro;
        return 1;
    }

    for(p = lista->primeiro; p->prox != lista->primeiro; p = p->prox);
    /* Adição de um novo roteador e alocação daquele, que até então, era o primeiro, para segunda posição */
    nova->prox = lista->primeiro;
    p->prox = nova;
    lista->primeiro = nova;

    return 1;
}

/* Função responsável por retornar a quantidade de itens dentro da lista */
int tamanhoLista(Lista *lista){
    ListaNo *p;  

    /* Calcula quantos itens tem na lista, através do contador */
    int contador = 1;
    for(p = lista->primeiro; p->prox != lista->primeiro; p = p->prox){
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
        aux = lista->primeiro;
        for(p = lista->primeiro; p->prox != lista->primeiro; p = p->prox);
        lista->primeiro = lista->primeiro->prox;
        p->prox = lista->primeiro;
        free(aux);
        printf("Roteador excluído da lista com sucesso!\n");
        return 0;
    }

    /* Verifica se a posição de exclusão desejada está entre o primeiro e o último valor */
    int i = 1;
    for(p = lista->primeiro; p->prox->prox != lista->primeiro; p = p->prox){
        if(i + 1 == posicao){
            aux = p->prox;
            p->prox = p->prox->prox; 
            free(aux);
            printf("\n\n=========================\n\n");
            printf("Roteador excluído da lista com sucesso!\n");
            return 1;
        }
        ++i;
    }
    
    /* Verifica se a posição de exclusão desejada é o último valor da lista */
    printf("O último é %d, mas a posição atual é %d\n", posicao, i);
    if(i == posicao - 1){
    	aux = p->prox;
    	p->prox = lista->primeiro;
    	free(aux);
    	printf("Roteador excluído da lista com sucesso!\n");
        return 1;
    }
    return -1;

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
    
    int posicaoNome = buscarIndex(lista, nome); 
    removerElemento(lista, posicaoNome);
    return 1;
}

/* Função Responsável pela Busca de Elementos a partir da marca ou modelo, e retornar sua posição na lista */
int buscarIndex(Lista *lista, char *valor){
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

    int i = 1;
    p = lista->primeiro;
    do {
		if(strcmp(p->marca, valor) == 0 || strcmp(p->modelo, valor) == 0){       
            return i;
		}
        i++;
    	p = p->prox;
	}
	while(p != lista->primeiro);
	
    return -1;
}

/* Função Responsável pela Busca de Elementos a partir da posição na Lista, e retornar o roteador naquela posição da lista */
int buscarNome(Lista *lista, int posicao){
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

    int posicao = buscarIndex(lista, antigo);
    printf("a posição é o %d\n", posicao);
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
	while(p != lista->primeiro);
    
    /*Verificando se a posição onde ocorrerá a atualização é o último */
    if(strcmp(p->prox->marca, antigo) == 0){
        strcpy(p->prox->marca, novo);
        return 1;
    } else if(strcmp(p->prox->modelo, antigo) == 0){
        strcpy(p->prox->modelo, novo);
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
        printf("%s\n", p->modelo);
        aux = p->prox;
        p = aux->prox;
        free(aux);
    	p = p->prox;
	}
	while(p->prox != lista->primeiro);

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

    p = lista->primeiro;	
	do {
		printf("\nMarca: %s \n",  p->marca);
    	printf("Modelo: %s \n", p->modelo);
    	printf("Velocidade: %.2f Mbps\n", p->velocidade);
    	printf("Antenas: %d \n", p->antenas);
    	printf("Portas: %d \n", p->portas);
    	printf("Sistema operacional: %s \n", p->sistemaOperacional);
    	printf("Valor: R$ %.2f \n\n", p->valor);
    	p = p->prox;
	}
	while(p != lista->primeiro);

    return ;
}

/* Função que cria alguns Roteadores, feito apenas para teste */
int hackFunc(Lista *lista, char* marca, char* modelo,float velocidade,int antenas,int portas,char* sistemaOperacional,float valor){
    /* Criação da Lista e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma lista */    
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

    /* Verifica se a lista está vazia. Se sim, coloca o roteador criado anteriormente como primeiro item. */
    if(lista->primeiro == NULL){
        lista->primeiro = nova;
        nova->prox = lista->primeiro;
        printf("Criou o primeiro");
        return 1;
    }


    /* Se ela já contiver algum item, vai buscar o último valor, e alocar o roteador em seguida.*/
    for(p = lista->primeiro; p->prox != lista->primeiro; p = p->prox);

    p->prox = nova;
	nova->prox = lista->primeiro;


    return 1;

}

int registrandoDados(Lista *lista){
    ListaNo *p;

    /* Abrindo arquivo para escrita binária */
    FILE *arquivo = fopen("./roteadores.txt", "w"); 
    int tamLista = tamanhoLista(lista);

    if (arquivo != NULL) {
        for(p = lista->primeiro; p->prox != lista->primeiro; p = p->prox){
            fprintf(arquivo, "Marca: %s\nModelo: %s\nVelocidade: %f\nAntenas: %d\nPortas: %d\nSistema Operacional: %s\n\n", p->marca, p->modelo, p->velocidade, p->antenas, p->portas, p->sistemaOperacional);        
        }
        fprintf(arquivo, "Marca: %s\nModelo: %s\nVelocidade: %f\nAntenas: %d\nPortas: %d\nSistema Operacional: %s\n\n", p->marca, p->modelo, p->velocidade, p->antenas, p->portas, p->sistemaOperacional);        
         /* Fechando o Arquivo */
        fclose(arquivo); 
        return -1;
    } else {
        printf("Erro ao abrir arquivo!\n");
        return 0;
    }
}