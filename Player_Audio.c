#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct{
	char nome[30];
	float minutos;
	char compositor[30];
	char album[30];	
}Musica; // estrutura musica

typedef struct scell_musica{
    struct scell_musica *next;
    struct scell_musica *prev;
    Musica info; 
}celula_musica; // celula musica

typedef struct sArtista{
	char nome[30];
	char genero[30];
	int num_album;
	celula_musica *lista_musica; // ponteiro para a lista de musica;
	celula_musica **inicio_lista; // ponteiro para ponteiro da lista de musica, marca o inicio da lista de musica
}Artista; // estrutura artirsta

typedef struct scell{
	Artista elemento;
	struct scell *next;
	struct scell *prev;
}celula; // celula do tipo Artista

int inicializarartista(celula**artista){  
	((*artista) = NULL); // ponteiro para lista de artista recebe NULL
	return 0;
}

celula_musica** inicializarmusica(celula_musica**musica){
	((*musica) = NULL); // ponteiro para lista de artista recebe NULL
	return (&(*musica)); // returna uma celula musica com o endereço do ponteiro do inicio da lista de musica
}

int artistavazio(celula**artista){ // verifica se existe ou nao ao menos um artista cadastrado
	if((*artista)== NULL){
	return 1;
	 }
	 return 0;
}

celula *criarartista(){ // aloca uma celula do tipo artista
	celula*nova;
	nova = (celula*)malloc(sizeof(celula));
	return nova; // retorna uma celula artista
}

celula_musica *criarmusica(){ // aloca uma celula do tipo musica
	celula_musica *nova;
	nova = (celula_musica*)malloc(sizeof(celula_musica));
	return nova;
}

int cadastrarartista(celula**artista, Artista informacao, int operacao){ // cadastra um artista no inicio ou fim da lista de artistas
	celula*novacelula;
	celula*auxiliar = (*artista); // auxiliar recebe o ponteiro do inicio da lista de artista 
	novacelula = criarartista(); // novacelula recebe uma celula alocada dinamicamente
	
	if(novacelula == NULL){ // verifica se a celula foi alocada com sucesso
		printf("\n Erro: Memoria Cheia!!");
		return 0;
	}
	//passa as informaçoes inseridas pelo 
	strcpy(novacelula->elemento.nome,informacao.nome);
	strcpy(novacelula->elemento.genero,informacao.genero);
	novacelula->elemento.num_album = informacao.num_album;
	novacelula->next = novacelula;
	novacelula->prev = novacelula;
	novacelula->elemento.inicio_lista = inicializarmusica(&novacelula->elemento.lista_musica); // o ponteiro de ponteiro inicio_lista recebe o inicio da lista de musicas
	
	if(artistavazio(artista) == 1){ // verifica se artista esta vazio
		(*artista) = novacelula; // ponteiro (*artista) recebe a nova celula
		return 1; //vazio
	}
	
	if(operacao == 1){ // cadastro do artista no inicio
	    // manipulacao dos ponteiros
		novacelula->next = auxiliar;
		novacelula->prev = auxiliar->prev;
		novacelula->prev->next = novacelula;
		auxiliar->prev = novacelula;
	    (*artista) = novacelula; // inicio da lista recebe a nova celula
	    return 1;
	}

	if(operacao == 2){ // cadastro do artista no fim
	   // manipulacao dos ponteiros
	   novacelula->next = auxiliar; 
	   novacelula->prev = auxiliar->prev;
	   (*artista)->prev->next = novacelula;
	   (*artista)->prev = novacelula; 
	   return 1;	
	}
}

void imprimirartistainicio(celula**artista){ // imprimi todos os artistas a partir do inicio
	celula*auxiliar = (*artista);
	 if(artistavazio(artista)){
	 	printf("\n Ainda nao existe artistas cadastrados\n");
	 }
	 else{
	 	do{
	 	printf("\n");
	 	printf("Informacoes do artista: \n");
		printf("artista: ");
		puts(auxiliar->elemento.nome);
		fflush(stdin);
		printf("genero: ");
		puts(auxiliar->elemento.genero);
		fflush(stdin);
		printf("numero de albuns: ");
		printf("%d",auxiliar->elemento.num_album);
	 	printf("\n");
	 	auxiliar = auxiliar->next; // auxiliar recebe a proxima celula artista
	 	 
	 }while(auxiliar != (*artista)); // imprimi todos os artista até que o auxiliar chegue ao inicio da lista
	}
	 printf("\n");	 
}

celula *procurarartista(celula**artista,char *nome_artista){ // funçao para encontrar determinado artista e retorna uma celula com o artista procurado
	celula*auxiliar;
	auxiliar = (*artista); // auxiliar recebe o inicio da lista de artista
   	
   	if(auxiliar == NULL){
   		printf("\n Esse artista nao esta cadastrado");
	   }

	while(auxiliar != (*artista)->prev){ // enquanto o auxiliar nao encontrar o ultimo elemento da lista
		if(strcmp(auxiliar->elemento.nome,nome_artista) == 0){ // se as palavras forem iguais
			return auxiliar; // retorno a celula que contem o artista procurado
		}
		auxiliar = auxiliar->next; // auxiliar recebe a proxima celula artista
	};
	
	if(strcmp(auxiliar->elemento.nome,nome_artista) == 0){ // caso o artista procurado seja a ultima celula da lista
			return auxiliar; // retona a celula que contem o artista 
		}
		
		printf("\n O artista procurado ainda nao foi cadastrado \n");
		auxiliar = NULL; // celula recebe NULL caso o artista nao seja encontrado
		return auxiliar; // retorna a celula NULL com o valor NULL
	}

celula_musica *procurarmusica(celula**artista,celula_musica**musica,char* nome_artista, char*nome_musica){// função que procura por uma determinada musica e retorna uma celula contentendo a musica procurada
	celula*auxiliar;
	celula_musica*aux;
	auxiliar = procurarartista(artista,nome_artista); // auxiliar recebe a celula do artista procura
	
	if(auxiliar == NULL){ // caso o artista nao exista
		printf("\n Artista nao encontrado ");
		aux = NULL;
		return aux;
	}

    aux = *auxiliar->elemento.inicio_lista;
    if(aux == NULL){// caso a musica nao exista
        printf("\n Ainda nao existem musicas cadastradas para esse artista");
    	return aux;
	}
	while(aux != (*auxiliar->elemento.inicio_lista)->prev){ 
		if(strcmp(aux->info.nome,nome_musica) == 0){ 
			return aux; // retorno a celula que contem o artista procurado
		}
		aux = aux->next; // auxiliar recebe a proxima celula artista
	};
	
	if(strcmp(aux->info.nome,nome_musica) == 0){ // caso o artista procurado seja a ultima celula da lista
			return aux; // retona a celula que contem o artista 
		}
		
		printf("\n A musica procurada ainda nao foi cadastrada \n");
		aux = NULL; // celula recebe NULL caso o artista nao seja encontrado
		return aux; // retorna a celula NULL com o valor NULL
}

int removermusica(celula**artista,celula_musica**musica,char*nome_artista, char*nome_musica){//remove uma musica de um determinado artista
	celula_musica*removida; // celula que sera removida 
	celula*auxiliar; // 
	auxiliar = procurarartista(artista,nome_artista); //auxiliar recebe o artista da musica que será deletada
	
	if(auxiliar == NULL){// se o artista nao for encontrado
	return 0 ;
    }
    
	removida = procurarmusica(artista,auxiliar->elemento.inicio_lista,nome_artista,nome_musica); // celula que sera removida receve a celula da musica que será removida

	if(removida == NULL){ // se a celula que vai ser removida nao existir
		return 0;
	}
	
	if(removida->next && removida->prev == removida){// caso exista somente uma musica cadastrada
		auxiliar->elemento.lista_musica = NULL;
		auxiliar->elemento.inicio_lista = NULL;
		free(removida);
		return 1;
	}
	if(removida == (*auxiliar->elemento.inicio_lista)){// caso a primeira celula da musica seja removida
		removida->next->prev = removida->prev;
		removida->prev->next = removida->next;
		(*auxiliar->elemento.inicio_lista) = removida->next;
		free(removida);
		return 1;
	}
	//qualquer outra celula musica que nao seja a primeira
	removida->prev->next = removida->next;
	removida->next->prev = removida->prev;
	free(removida);
	return 1;
}

int removerartista(celula**artista,char*nome_artista){ // remove um deternimado artita da lista de artistas
	celula*removida; // celula que será removida
    removida = procurarartista(artista,nome_artista); // removida recebe a celula que será removida
	
	if(removida == NULL){// se a celula do artista que será removido nao existir
		printf("\n Nao existe nenhum artista com esse nome");
		return 0;
	}
	
	if(removida->next && removida->prev == removida){// remoção caso exista somente um artista
		removida->prev = NULL;
		removida->next = NULL;
		free(removida);
		(*artista) = NULL;
	    return 1;
	}
	if(removida == (*artista)){ // remoçao caso a primeira celula artista seja removida
		removida->next->prev = removida->prev;
		removida->prev->next = removida->next;
		(*artista) = removida->next;
		free(removida);
		return 1;
	}
	// remoçao para qualquer celula artista que nao seja a primeira celula
	removida->prev->next = removida->next;
	removida->next->prev = removida->prev;
	removida->elemento.inicio_lista = NULL;
	removida->elemento.lista_musica = NULL;
	free(removida);
	return 1;
}

int cadastrarmusica(celula**artista,celula_musica**musica,Musica info_musica,int operacao,char* nome_artista){ // funçao para cadastrar uma musica no incio ou no fim de uma lista de musicas

	celula_musica*novacelula;
	novacelula = criarmusica(); // recebe uma celula do tipo musica
	
	celula*auxiliar; // auxiliar do tipo celula de um artista
	auxiliar = procurarartista(artista,nome_artista); // auxiliar recebe a celula do artista procurado
	if(auxiliar == NULL){// caso o artista nao exista, a funçao termina
		return 0;
	}

	if(novacelula == NULL){// caso a alocaçao da novacelula falhe
		printf("\n Erro: Memoria Cheia!!");
		return 0;
	}
	//atualizaçao valores e ponteiros da novacelula
	strcpy(novacelula->info.nome,info_musica.nome);
	strcpy(novacelula->info.compositor,info_musica.compositor);
	strcpy(novacelula->info.album,info_musica.album);
	novacelula->info.minutos = info_musica.minutos;
	novacelula->next = novacelula;
	novacelula->prev = novacelula;
	
	if((*auxiliar->elemento.inicio_lista) == NULL){ // caso a lista estiver vazia
	  (*auxiliar->elemento.inicio_lista) = novacelula;
	  	return 1;	//vazio
	}
	
	if(operacao == 1){//inserir no incio
	    //atualização dos ponteiros
		novacelula->next = (*auxiliar->elemento.inicio_lista);
		novacelula->prev = (*auxiliar->elemento.inicio_lista)->prev;
		novacelula->prev->next = novacelula;
		(*auxiliar->elemento.inicio_lista)->prev = novacelula;
	    (*auxiliar->elemento.inicio_lista) = novacelula; // inicio da lista de musicas recebe a novacelula
	    return 1;
	}

	if(operacao == 2){//inserir no fim
	   //atualização dos ponteiros
	   novacelula->next = (*auxiliar->elemento.inicio_lista);
	   novacelula->prev = (*auxiliar->elemento.inicio_lista)->prev;
	   (*auxiliar->elemento.inicio_lista)->prev->next = novacelula;
	   (*auxiliar->elemento.inicio_lista)->prev = novacelula;
	   return 1;	
	}
}

int atualizarartista(celula**artista,Artista informacao,char *nome_artista){ // função que atualizar as informações de um artista
	celula*auxiliar; // celula que será atualizada
	auxiliar = procurarartista(artista,nome_artista);// recebe a celula artista que deve ser atualizada
	if(auxiliar == 0){ // caso o artista nao exista a função termina
		return 0;
	}
	//atualiza os valores da celula artista
	strcpy(auxiliar->elemento.nome,informacao.nome);
	strcpy(auxiliar->elemento.genero,informacao.genero);
	auxiliar->elemento.num_album = informacao.num_album;
	return 1;	
}

int atualizarmusica(celula**artista,celula_musica**musica,Musica info_musica,char*nome_artista,char*nome_musica){ // função que atualiza as informações de uma musica
	celula_musica*auxiliar; // celula do tipo musica que será atualizada
	celula*aux;
	aux = procurarartista(artista,nome_artista); // aux recebe o artista que contem a musica que será atualizada
	
	if(aux == NULL){ // se o artista nao existir a função termina
	return 0;
    }
	auxiliar = procurarmusica(artista,aux->elemento.inicio_lista,nome_artista,nome_musica); // auxiliar recebe a celula da musica que será atualizada
	if(auxiliar == NULL){ // se a musica nao existir a função termina
		return 0;
	}
	// celula musica recebe as informações que serão atualizadas
	strcpy(auxiliar->info.nome,info_musica.nome);
	strcpy(auxiliar->info.album,info_musica.album);
	strcpy(auxiliar->info.compositor,info_musica.compositor);
	auxiliar->info.minutos = info_musica.minutos;
	return 1;
}

void imprimirmusicainicio(celula**artista,char *nome_artista){ // função que imprimi todas as musicas de um determinado artista
	celula_musica*auxiliar; // percorrer lista de musicas
	celula*aux; // celula que recebe o artista procurado
	
	aux = procurarartista(artista,nome_artista);
	if(aux == NULL){// caso o artista procurado para inserir a musica nao exista
		return;
	}
	
	auxiliar = aux->elemento.lista_musica; // auxiliar recebe a primeira celula da musica
	
		if((auxiliar) == NULL){ // veridica se o artista ja posssui alguma musica em sua lista de musicas
		printf("\n Esse artista ainda nao possui musicas cadastradas");
		return;
	    } 
    
	do{
		printf("\n");
		printf("\nInformacoes da musica:\n");
		printf("nome: ");
		puts(auxiliar->info.nome);
		fflush(stdin);
		printf("compositor: ");
		puts(auxiliar->info.compositor);
		fflush(stdin);
		printf("album: ");
		puts(auxiliar->info.album);
		fflush(stdin);
		printf("duracao em minutos: ");
		printf("%f",auxiliar->info.minutos);
		printf("\n");	
		auxiliar = auxiliar->next; // auxiliar recebe a proxima celula musica
	}while(auxiliar != aux->elemento.lista_musica);// repete o laço até que o auxiliar seja igual o inicio da lista
}

void procurar_artista(celula**artista,char*nome_artista){ // funçao que encontra e imprime um artista
	celula*auxiliar;
	auxiliar = procurarartista(artista,nome_artista); // auxiliar recebe a celula com o artista procurado
	if(auxiliar == NULL){// se o artista ainda nao foi cadastrado
		return;
	}
	// imprime as informações do artista	
	printf("\n");
	printf("Informacoes do artista: \n");
	printf("artista: ");
	puts(auxiliar->elemento.nome);
	fflush(stdin);
	printf("genero: ");
	puts(auxiliar->elemento.genero);
	fflush(stdin);
	printf("numero de albuns: ");
	printf("%d",auxiliar->elemento.num_album);
	return;
	
}

void procurar_musica(celula**artista,celula_musica**musica,char*nome_artista,char*nome_musica){ // funçao que encontra e imprime uma determinada musica
	celula_musica*auxiliar;
	celula*aux;
	aux = procurarartista(artista,nome_artista); // aux recebe o artista que contêm a música
	if(aux == NULL){// caso o artista nao exista
		return ;
	}
	auxiliar = procurarmusica(artista,aux->elemento.inicio_lista,nome_artista,nome_musica); // auxiliar recebe a celula que contêm a música procurada
	
	if(auxiliar == NULL){ // caso a musica nao exista
		return;
	}
	// imprimi as informações da musica
	printf("\nInformacoes da musica:\n");
	printf("nome: ");
	puts(auxiliar->info.nome);
	fflush(stdin);
	printf("compositor: ");
	puts(auxiliar->info.compositor);
	fflush(stdin);
	printf("album: ");
	puts(auxiliar->info.album);
	fflush(stdin);
	printf("duracao em minutos: ");
	printf("%f",auxiliar->info.minutos);
	return;	
}

void tocarmusica(celula**artista,celula_musica**musica,char*nome_artista){ // funçao que executa musicas
	celula_musica*auxiliar; // celula do tipo artista
	celula*aux; // celula do tipo musica
	aux = procurarartista(artista,nome_artista); // aux recebe o artista 
	if(aux == NULL){// caso o artista nao exista
		return ;
	}
	auxiliar = (*aux->elemento.inicio_lista); // auxiliar recebe a celula que contêm a primeira musica do artista
	
	if(auxiliar == NULL){ // caso nao exista nenhuma musica para esse artista
	    printf("\n Esse artista ainda nao possui musicas cadastras");
		return;
	}
	// imprimi as informações da musica e o nome de seu artista
	printf("\n");
	printf("\nVoce esta ouvindo: ");
	printf("artista: ");
	puts(aux->elemento.nome);
	fflush(stdin);
	printf("musica: ");
	puts(auxiliar->info.nome);
	fflush(stdin);
	printf("compositor: ");
	puts(auxiliar->info.compositor);
	fflush(stdin);
	printf("album: ");
	puts(auxiliar->info.album);
	fflush(stdin);
	printf("duracao em minutos: ");
	printf("%f",auxiliar->info.minutos);
	
	
	int menu_musica; // variavel para as opções do player
	
	do{
	printf("\n");
	printf("\n 1 - Ir para proxima musica ");
	printf("\n 2 - Ir para musica anterior ");
	printf("\n 3 - Escutar proximo artista ");
	printf("\n 4 - Escutar artista anterior ");
	printf("\n -1 - Parar de escutar musica ");
	scanf("%d",&menu_musica); // le opção escolhida
	printf("\n");
	
	switch(menu_musica){
		case 1:
			auxiliar = auxiliar->next; // pula para proxima musica do artista
		    // imprimi as informações da musica e o nome de seu artista
			printf("\nVoce esta ouvindo: ");
			printf("artista: ");
			puts(aux->elemento.nome);
			fflush(stdin);
			printf("musica: ");
			puts(auxiliar->info.nome);
			fflush(stdin);
			printf("compositor: ");
			puts(auxiliar->info.compositor);
			fflush(stdin);
			printf("album: ");
			puts(auxiliar->info.album);
			fflush(stdin);
			printf("duracao em minutos: ");
			printf("%f",auxiliar->info.minutos);
	        break;
	    
	    case 2:
	    	auxiliar = auxiliar->prev; // pula para musica anterior do artista
	    	// imprimi as informações da musica e o nome de seu artista
			printf("\nVoce esta ouvindo: ");
			printf("artista: ");
			puts(aux->elemento.nome);
			fflush(stdin);
			printf("musica: ");
			puts(auxiliar->info.nome);
			fflush(stdin);
			printf("compositor: ");
			puts(auxiliar->info.compositor);
			fflush(stdin);
			printf("album: ");
			puts(auxiliar->info.album);
			fflush(stdin);
			printf("duracao em minutos: ");
			printf("%f",auxiliar->info.minutos);
	        break;
	    
	    case 3:
	    	aux = aux->next; //pula para o proxima artista
	    	// imprimi as informações da musica e o nome de seu artista
	    	auxiliar = (*aux->elemento.inicio_lista); //
			printf("\nVoce esta ouvindo: ");
			printf("artista: ");
			puts(aux->elemento.nome);
			fflush(stdin);
			printf("musica: ");
			puts(auxiliar->info.nome);
			fflush(stdin);
			printf("compositor: ");
			puts(auxiliar->info.compositor);
			fflush(stdin);
			printf("album: ");
			puts(auxiliar->info.album);
			fflush(stdin);
			printf("duracao em minutos: ");
			printf("%f",auxiliar->info.minutos);
	        break;
	        
	    case 4:
	    	aux = aux->prev; //pula para o artista anterior
	    	auxiliar = (*aux->elemento.inicio_lista);
	    	// imprimi as informações da musica e o nome de seu artista
			printf("\nVoce esta ouvindo: ");
			printf("artista: ");
			puts(aux->elemento.nome);
			fflush(stdin);
			printf("musica: ");
			puts(auxiliar->info.nome);
			fflush(stdin);
			printf("compositor: ");
			puts(auxiliar->info.compositor);
			fflush(stdin);
			printf("album: ");
			puts(auxiliar->info.album);
			fflush(stdin);
			printf("duracao em minutos: ");
			printf("%f",auxiliar->info.minutos);
	        break;   	
	}
	
 }while(menu_musica != -1); // fim do menu do player de musicas
    printf("\n Player desativado");
	return;
}


int main(){
	Artista informacao; //declara uma estrutura do tipo Artista
	Musica info_musica; // declara uma estrutura do tipo Lista
	celula *artista; // declara uma celula artista 
	inicializarartista(&artista); // inicializa a lista de artistas
	char nome_artista[30]; // variavel usada para procura de um artista
	char nome_musica[30]; // variavel usada para procura de uma musica
	int operacao; // variavel para indicar a operaçao de um usario  ex: 1 - inserir no inicio  2 - inserir no fim
	int teste; //recebe o retorno de funções com retorno do tipo inteiro
	int menu; // variavel para switch
	
	do{
		printf("\n");
		printf("\n 1 - Cadastrar Artista ");
		printf("\n 2 - Imprimir todos os Artistas ");
	    printf("\n 3 - Cadastrar Musica ");
	    printf("\n 4 - Imprimir todas as Musicas de um artista ");
	    printf("\n 5 - Deletar Musica ");
	    printf("\n 6 - Deletar Artista ");
	    printf("\n 7 - Alterar Artista ");
	    printf("\n 8 - Alterar Musica ");
	    printf("\n 9 - Pesquisar Artista ");
	    printf("\n 10 - Pesquisar Musica ");
	    printf("\n 11 - Executar musica ");
	    printf("\n Digite -1 para sair ");
		printf("\n Digite uma opcao ");
		scanf("%d",&menu);
		
		switch(menu){
			
			case 1:
				printf("\n Digite o nome do Artista: ");
			    fflush(stdin);
				gets(informacao.nome);
				
				printf("\n Digite o genero musical do Artista: ");
				fflush(stdin);
				gets(informacao.genero);
				
				printf("\n Digite o numero de albuns do artista: ");
				scanf(" %d",&informacao.num_album);
			    
			    printf("\n1 - Deseja inserir essas informacoes no inicio: ");
				printf("\n2 - Deseja inserir essas informacoes no fim: ");
				scanf(" %d",&operacao);
				
				teste = cadastrarartista(&artista,informacao,operacao);
			
			 if(teste == 1){
			 	printf("\n Inserido com sucesso!! ");
			 }
			 break;
			 
			case 2:
			 	imprimirartistainicio(&artista);
			 	break;
			
			case 3:
				printf("Digite o nome do artista ao qual se deseja cadastrar uma musica: ");
		    	fflush(stdin);
		    	gets(nome_artista);
		
		    	printf("\n Digite o nome da Musica: ");
		    	fflush(stdin);
				gets(info_musica.nome);
					
				printf("\n Digite o Compositor da musica: ");
				fflush(stdin);
				gets(info_musica.compositor);
				
				printf("\n Digite o nome do album a qual a musica pertence: ");
				fflush(stdin);
				gets(info_musica.album);
				
				printf("\n Digite o tempo em minutos da musica: ");
				scanf(" %f",&info_musica.minutos);
				
				printf("\n1 - Deseja inserir essas informacoes no inicio: ");
				printf("\n2 - Deseja inserir essas informacoes no fim: ");
				scanf(" %d",&operacao);
				
				teste = cadastrarmusica(&artista,&artista->elemento.lista_musica,info_musica,operacao,nome_artista);
				
				if(teste == 1){
			 	printf("\n Inserido com sucesso!! ");
			 }
             break;
			 
			 case 4:			
                printf("\nDigite o nome do artista ao qual se deseja imprimir suas musicas: ");
		    	fflush(stdin);
		    	gets(nome_artista);
			    imprimirmusicainicio(&artista,nome_artista);
				break;
			
			case 5:
			    printf("\nDigite o nome do artista que se deseja remover uma musica: ");
			    fflush(stdin);
				gets(nome_artista);
				printf("\nDigite o nome da musica que se deseja remover: ");
				fflush(stdin);
				gets(nome_musica);
				if(artista == NULL){
					printf("\n Nenhum artista foi cadastrado ate o momento: ");
				}
				else{
				teste = removermusica(&artista,&artista->elemento.lista_musica,nome_artista,nome_musica);
				if(teste == 1){
					printf("\n Musica Removida com Sucesso!!\n ");
				 }
				}
				break;
			
			case 6:
			    printf("\n Digite o nome do artista que se deseja deletar: ");
			    fflush(stdin);
				gets(nome_artista);
				if(artista == NULL){
					printf("\nNenhum artista cadastrado ate o momento!! ");
					break;
				}
				teste = removerartista(&artista,nome_artista);
				if(teste == 1){
					printf("\nArtista deletado com sucesso ");
				}
				break;
			
			case 7:
				 printf("\nDigite o nome do artista que se deseja alterar: ");
			    fflush(stdin);
				gets(nome_artista);
				
				printf("\nDigite o novo nome do Artista: ");
			    fflush(stdin);
				gets(informacao.nome);
				
				printf("\nDigite o novo genero musical do Artista: ");
				fflush(stdin);
				gets(informacao.genero);
				
				printf("\nDigite o novo numero de albuns do Artista: ");
				scanf("%d",&informacao.num_album);
				
				if(artista == NULL){
					printf("\nNenhum artista cadastrado ate o momento: ");
					break;
				}
				teste = atualizarartista(&artista,informacao,nome_artista);
				if(teste == 1){
					printf("\nArtista alterado com sucesso ");
				}
				break;
				
			case 8:
				printf("\nDigite o nome do artista ao qual se deseja atualizar uma musica: ");
		    	fflush(stdin);
		    	gets(nome_artista);
		    	
		    	printf("\nDigite o nome da musica que sera atualizada: ");
		    	fflush(stdin);
		    	gets(nome_musica);
		
		    	printf("\nDigite o novo nome da Musica: ");
		    	fflush(stdin);
				gets(info_musica.nome);
					
				printf("\nDigite o novo Compositor da Musica: ");
				fflush(stdin);
				gets(info_musica.compositor);
				
				printf("\nDigite o novo nome do album: ");
				fflush(stdin);
				gets(info_musica.album);
				
				printf("\n Digite o novo tempo da musica(em minutos): ");
				scanf(" %f",&info_musica.minutos);
				
				if(artista == NULL){
					printf("\nNenhum artista foi cadastrado ate o momento: ");
					break;
				}
				
				teste = atualizarmusica(&artista,&artista->elemento.lista_musica,info_musica,nome_artista,nome_musica);
				
				if(teste == 1){
			 	printf("\nMusica Atualizada com sucesso!! ");
			 }
             break;
             
             case 9:
             	printf("\nDigite o nome do artista que se deseja pesquisar: ");
             	fflush(stdin);
             	gets(nome_artista);
             	
             		if(artista == NULL){
					printf("\nNenhum artista foi cadastrado ate o momento ");
					break;
				}
				
			    procurar_artista(&artista,nome_artista);
				break;
			
			case 10:
				printf("\nDigite o nome do artista que se deseja pesquisar: ");
             	fflush(stdin);
             	gets(nome_artista);
             	
             	printf("\nDigite o nome da musica que se deseja pesquisar: ");
             	fflush(stdin);
             	gets(nome_musica);
             	
             		if(artista == NULL){
					printf("\nNenhum artista foi cadastrado ate o momento ");
					break;
				}
			    procurar_musica(&artista,&artista->elemento.lista_musica,nome_artista,nome_musica);
				break;
			
			case 11:
			    printf("\n Digite o artista que se deseja escutar a musica: ");
				fflush(stdin);
				gets(nome_artista);
				if(artista == NULL){
					printf("\nNenhum artista foi cadastrado ate o momento ");
					break;
			  }
				tocarmusica(&artista,&artista->elemento.lista_musica,nome_artista);
				break;						   			
		}						
}while(menu != -1);
	
system("pause");	
return 0;	
}
