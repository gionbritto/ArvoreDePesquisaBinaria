/*
 * TRABALHO DE ALGORITMOS E ESTRUTURAS DE DADOS QUE TEM 
 * O INTUITO DE ARMAZENAR PALAVRAS DE UMA FRASE DIGITADA
 * PELO USUARIO EM ORDEM ALFABETICA EM UMA ARVORE BINARIA
 * DE BUSCA E IMPRIMIR ESTES VALORES NA TELA TAMBÉM EM ORDEM
 * ALFABETICA UTILIZANDO RECURSIVIDADE
 */

/* 
 * Arquivo:   trabArvore.c
 * Author: GIOVANNE NASCIMENTO DE BRITTO
 * Turma: TADS 3º PERIODO
 * RA: 1250413
 * Criado em 19 de Maio de 2018, 08:14
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

#define TAMANHO 80


//estruturas
typedef struct arvore{
	char* palavra;
	struct arvore *pDir;
	struct arvore *pEsq;
	int posicao[10], count;
	
}ARVORE;

typedef struct raiz{
    ARVORE *no;
}RAIZ;

RAIZ* criaArvore();
int insereElemento(RAIZ* r, char* p);
void leTexto();
void separaPalavra();
void mostraPalavra(char* palavra);
int encontraPos(char *str, char *substr);
void visitaRaiz(ARVORE* a);
void emOrdem(ARVORE* a);
void apresentacao();
void cabecalhoImpressao();
char menu();
int verificaBufferFrase(char* frase);
void inicializaVetor(ARVORE* a);
RAIZ* removeArvore(ARVORE* a);



RAIZ *raiz;
char* palavra;
char bufferFrase[TAMANHO];
char bufferFraseAux[TAMANHO];
char bufferFraseAux2[TAMANHO];
const char* delimit = " .,?!;:";


int main(){
    
   	char escolha;
    raiz = criaArvore();

	apresentacao();

	for ( ; ; )
    {
        escolha = menu();  
        switch ( escolha )
        {
            case 'i' :           
            case 'I' : { 
							leTexto(); 
						} break;
            
            case 'a' :
            case 'A' : { system("cls");
                         if (strlen(bufferFrase)<1){
                         	 printf("\nAINDA NAO FOI DIGITADO NENHUMA FRASE. INSIRA UMA FRASE...\n");
							 system("pause"); 	
						 } else{
						 	 cabecalhoImpressao();
	                         emOrdem(raiz->no);
	                         printf("\n#                                                                      ");
							 printf("\n########################################################################\n\n");
	                         system("pause");
						 }
                        } 
                         break;
            case 'r' :
            case 'R' : { 
							if (strlen(bufferFrase)<1){
								system("cls");
                         	 	printf("\nAINDA NAO FOI DIGITADO NENHUMA FRASE. ARVORE VAZIA...\n");
							 	system("pause"); 	
						 } else{
						 	removeArvore(raiz->no);  raiz = NULL; 
						 	printf("VALORES REMOVIDOS COM SUCESSO...\n");
						 	bufferFrase[0] = '\0';
						 	raiz = criaArvore(); //cria novamente a arvore apos limpar todos os valores	
							 system("pause");			 	
						 }
                       }  break;                            
            case 'e' :
            case 'E' : {   
			 				removeArvore(raiz->no);  raiz = NULL; 
						 	printf("REMOVENDO ESPACOS ALOCADOS E FINALIZANDO PROGRAMA...\n");
	        				exit ( 0 );
	       } break;                       
            default : {  printf ( "Opcao invalida. \n" ); system("pause"); }
        }
        
        printf ( "\n \n \n" );
    }
    
    return 0;
}

RAIZ* criaArvore(){
   
    RAIZ *raiz = (RAIZ*) malloc(sizeof(RAIZ));
    if(raiz != NULL){
        raiz->no = NULL;
    }
    
    return raiz;
    
}
void inicializaVetor(ARVORE* a){
	a->count = 0;
	int i;
	for(i=0; i<=9; i++){
		a->posicao[i] = 0;
	}
}


int insereElemento(RAIZ* r, char* p){
   char *substring[15];
    ARVORE* ponteiro = (ARVORE*) malloc(sizeof(ARVORE));
    ponteiro = r->no; 
    
    
    //verifica se a raiz recebida por parametro e nula (se existe)
    if(r == NULL){
        return 0;       //caso de erro
    }
    
    ARVORE* novoNo;
    novoNo = (ARVORE*) malloc(sizeof(ARVORE));
    
    
	 
    if(novoNo == NULL){     //verifica se a criaÃ§ao do novoNo correu bem
        return 0;       //caso de erro
    }
    
    //atributindo valores ao NO
    inicializaVetor(novoNo);
    novoNo->palavra = p;
    novoNo->pDir = NULL;
    novoNo->pEsq = NULL;
	novoNo->posicao[novoNo->count] = encontraPos(bufferFraseAux, p);	//verifica a posicao da palavra na frase, recebe a frase e a palavra como palametros e retorna a posicao
    
	//passando dessas verificaÃ§oes e armazenado no NO o valor recebido
    if(r->no == NULL){  //caso o local para onde r aponta seja vazio, insere a estrutura onde r aponta(inicio da arvore)
        r->no = novoNo;;
    }else{
  
     ARVORE* atual = ponteiro;   
     ARVORE* ant   = NULL;      
     
      int ret;
     while(atual != NULL){
     
         ant = atual;
        
		//realiza a comparacai das palavras 
        
		ret = strncmp(p, atual->palavra, 8);
	//	printf("resultado %d\n\n", ret);
         
         if(ret == 0){
             
             atual->count = (atual->count + 1);
             
             atual->posicao[atual->count] = novoNo->posicao[novoNo->count];
            // printf("DEU IGUAL - IMPRIME COUNT: %d\n\n", atual->count);
             //free(novoNo);
             return 0;
         }
         if(ret > 0){
            atual = atual->pDir;
         } else if(ret < 0){
            atual = atual->pEsq;
         }
         
     }
     
	 if(ret > 0){
             ant->pDir = novoNo;
         } else{
             ant->pEsq = novoNo;
         }
    
    }
    
  
    
    return 1;       //caso de sucesso na insercao
    
}

//FunÃ§Ã£o responsavel por fazer aleitura do texto digitado pelo usuario
void leTexto(){

    
char *tmp;
int i;
int tamanho, teste;
tamanho = 0;
teste = 0;

	//verifica se o buuferFrase esta ou nao vazio
	teste = verificaBufferFrase(bufferFrase);
	
	if(teste == 1){
	//	bufferFraseAux[0] = '\0';
		bufferFraseAux2[0] = '\0';
		raiz = removeArvore(raiz->no); 			//libera o espaço reservado para toda a arvore recursivamente
		raiz = criaArvore();				//aloca novamente o espaco para a proxima frase
	}
	system ( "cls" );
	printf("\n\n##########################   I N S E R C A O   #########################");
	printf("\n#                                                                      #");
	printf("\n#                           ENTRE COM O TEXTO                          #");
	printf("\n#                                                                      #");
	printf("\n########################################################################\n");
    fflush ( stdin );
	printf("\n\n->");		
	fgets(bufferFrase, TAMANHO, stdin); 			//leitura da frase
	//tranforma todas as letras da frase em minusculas
	tamanho = strlen(bufferFrase);
	for(i=0; i<=tamanho; i++){
		bufferFrase[i] = tolower(bufferFrase[i]);
	}
	
	//verifica se a frase inserida tem tamanho menor que a fraseAuxiliar na segunda execução do programa em diante
	if(strlen(bufferFrase) < strlen(bufferFraseAux)){
		int j, tamFrase1, tamFrase2;
	
		tamFrase1 = strlen(bufferFrase);
		tamFrase2 = strlen(bufferFraseAux);
		for(j = 0; j<= tamFrase2; j++){
			bufferFraseAux[j] = ' ';
			bufferFraseAux2[j] = ' ';
		}
	
	}

	strncpy(bufferFraseAux, bufferFrase, (strlen(bufferFrase)-1));		//copia a frase para um espaco auxiliar
	strncpy(bufferFraseAux2, bufferFrase, (strlen(bufferFrase)-1));	
	palavra = strtok(bufferFraseAux2, delimit);   //ok
	

	separaPalavra();
}

//Funcao responsavel por somente semaprar as palavras lidas
void separaPalavra(){
	int cont = 0;

	while(palavra != NULL){

	
		cont++;
		mostraPalavra(palavra);	
		palavra = strtok(NULL, delimit);
			
		
	} // fim di while
	
	
}

/*funcao que mostra a palavra inserida*/

void mostraPalavra(char* palavra){

	
	//verifica se a palavra tem mais que tres caracteres
	if(strlen(palavra)>=3){
		insereElemento(raiz, palavra);	
	}else{
		return;
	}
	
}

/*funcao que encontra a ocorrecia da palavra na frase*/
int encontraPos(char *str, char *substr){
     char *aux; // guarda o endereco da pos inicial de substr na str.
     int tam, local = 0;
     register int i; // armazenado em registrador.
     char *inicio;
     
     tam = strlen (substr); // armazena tamanho da substr.
     aux = strstr (str, substr); // retorna endereco inicial da substr.
     if(aux == NULL){
         printf("PALAVRA NAO ENCONTRADA OU ERRO INTERNO NO PROGRAMA!");
     }
     //printf("aux: %c\n", *aux);
     
     inicio = str;
     while(inicio != aux){
         local++;
         inicio++;
     }
     local = local + 1;
     
     
     /*essa parte do codigo retira a palavra ja identificada e substitui por asteriscos
     o que torna possivel a busca pela proxima palavra se for repetida na frase
     */
     if (aux) // A substring esta contida na string? (endereco retornado?)
    {
       if (aux == str) // remove substring no inicio e adiciona valor qualquer
          for (i = 0; i < tam ; i++){
              str[i] = '*';
          }
       else
       {
           /* i guarda a posicao inicial da substring
              tam e o tamanho do deslocamento (quantidade de caracteres apos
              a substring). */
           for (i = local-1; i < tam + local-1; i++){
              
              str[i] = '*';
             
                // printf("valor: %d\n", i+ tam);
          }
                                       
       }              
                 
    } 
//	printf("\n\nFRASE AUX1: %s\n\n", str);
//	system("pause");
     return local;
}

/*funÃ§Ã£o que apresenta valores da arvore*/
void emOrdem(ARVORE* a){
	

   	
	if (a){
		emOrdem(a->pEsq);
		visitaRaiz(a);
		emOrdem(a->pDir);
	}
//	system("pause");
}

/*Funcao que ira visitar a raiz, ou seja, ira apresentar o valor presente*/
void visitaRaiz(ARVORE* a){
	int i;
	if(strlen(a->palavra)<6){
		printf("\n#  \t\t\t %s \t\t\t", a->palavra);
		for	(i=0; i<=a->count; i++){
			printf("%d. ", a->posicao[i]);
		}
	}else if(strlen(a->palavra)>=6){
		printf("\n#  \t\t\t %s \t\t", a->palavra);
		for	(i=0; i<=a->count; i++){
			printf("%d. ", a->posicao[i]);
		}
	}
	
}

/*função responsavel por liberar a arvore*/
RAIZ* removeArvore(ARVORE* a) { 
     if(a)
     {
         removeArvore(a->pEsq);
         removeArvore(a->pDir);
         free(a); 
         
    }
    //system("pause");
return NULL;
}

void apresentacao(){
	printf("\n\n######################   B E M    V I N D O !   ########################");
	printf("\n#                                                                      #");
	printf("\n#         ESTE PROGRAMA REALIZA A LEITURA DE UM TEXTO QUALQUER         #\n#         E IMPRIME AS PALAVRAS DIGITADAS QUE POSSUEM 3 OU MAIS        #\n#         CARACTERES E A POSICAO QUE ELAS APARECEM NO TEXTO.           #\n#         ESTE TEXTO DEVE POSSUIR NO MAXIMO 80 CARACTERES              #");
	printf("\n#                                                                      #");
	printf("\n########################################################################\n");
	
	system("pause");
	system("cls");
	
	printf("\n\n######################       E X E M P L O      ########################");    
	printf("\n#                                                                      #");
	printf("\n#                            FRASE DIGITADA:                           #");
	printf("\n#  'E apenas um teste. Teste um, dois, tres, testando.                 #\n#  Testando muitas vezes'.                                             #");
	printf("\n#                                                                      #");
	printf("\n########################################################################");
	printf("\n#                                                                      #");
	printf("\n#                       APRESENTACAO DO SISTEMA:                       #");
	printf("\n#                                                                      #");
	printf("\n#  \t\t\t[PALAVRA] \t [POSICAO]                     #");
	printf("\n#  \t\t\t apenas \t 3                             #");
	printf("\n#  \t\t\t dois \t\t 30                            #");
	printf("\n#  \t\t\t muitas \t 62                            #");
	printf("\n#  \t\t\t testando \t 42,53                         #");
	printf("\n#  \t\t\t teste \t\t 14,21                         #");
	printf("\n#  \t\t\t tres \t\t 36                            #");
	printf("\n#  \t\t\t vezes \t\t 69                            #");
	printf("\n#                                                                      #");
	printf("\n########################################################################\n\n\n");
	system("pause");
	system("cls");
}

/*funcao que apresenta o menu*/
char menu(){
	
	char opcao;
	
	system("cls");
	printf("\n\n########################          M E N U         ######################");
	printf("\n#                                                                      #");
	printf("\n#         DIGITE A OPCAO DESEJADA:                                     #");
	printf("\n#                                                                      #");
	printf("\n#                                                                      #");
	printf ( "\n#         [I]nserir texto.                                             #");
    printf ( "\n#         [A]presentar em ordem as palavras do texto.                  #");
    printf ( "\n#         [R]emover Todos os itens da Arvore.                          #");
    printf ( "\n#         [E]ncerrar a execucao do programa.                           #"); 
    printf("\n#                                                                      #");
	printf("\n#                                                                      #");
	printf("\n#                                                                      #");
	printf("\n########################################################################\n");
    printf("\t\t\t\tOPCAO: ");
	fflush ( stdin );
    scanf ( "%c", &opcao );
	
	return opcao;
}

/*funcao que apresenta somente o cabeçaho da funcao de impressao*/
void cabecalhoImpressao(){
	
	printf("\n\n########################   I M P R E S S A O   #########################");
	printf("\n#                                                                      #");
	printf("\n#                IMPRIMINDO PALAVRAS EM ORDEM ALFABETICA               #");
	printf("\n#                                                                      #");
	printf("\n########################################################################");
	printf("\n#                                                                      ");
	printf("\n#  FRASE DIGITADA: %s", bufferFrase);
	printf("\n#                                                                  ");
	printf("\n########################################################################");
	printf("\n#                                                                      ");
	printf("\n#                       APRESENTACAO DO SISTEMA:                       ");
	printf("\n#                                                                      ");
	printf("\n#  \t\t\t[PALAVRA] \t    [POSICAO]                     ");
	
}

/*funcao responsavel por verificar as frases e excluir as informações caso nao esteja vazia*/
int verificaBufferFrase(char* frase){
	int op;
	op = 0;
	fflush ( stdin );
	if(strlen(frase)>1){
		printf(	"A frase antiga deve ser apagada. Pressione 1 para apagar\n-> ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				frase[0] = '\0';
			break;
				
		}
		printf(	"Frase apagada com sucesso!\n\n");
		system("pause");
		return 1;
	}
	return 0;
	
}



