/* JOGO 2048 - Menu Inicial
*/
//Inclusao de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
//Declara��o das teclas
#define CIMA 72
#define BAIXO 80
#define ESQUERDA 75
#define DIREITA 77
#define PAUSE 112
#define ENTER 13
//O Recorde s� ser� salvo caso a pessoa ganhe o jogo

typedef struct sJogador{
	char nome[50];
	int score;
}Jogador;

//Fun��o principal do c�digo: declara a fun��o menu
int main ()
{
    menu();

return 0;
}

//Imprime o menu principal do jogo, j� com suas funcionalidades
void menu()
{

    system("cls");
    //Declara��o de Vari�veis
    int posicao = 1;
    int tecla_press = 0;
    int tamanho;
    int tam2;
    int tecla = 0, tecla2 = 0;
    int **matriz;
    int jogadas=0;
    int score = 0;
    char nome[50];

    #define MAX 5
    #define MIN 1

    while (tecla_press != ENTER)
    {

    system("cls");
    textcolor(BLUE);
    printf("    _______  _______  _   ___   _____  \n"
           "   |       ||  _    || | |   | |  _  | \n"
           "   |____   || | |   || |_|   | | |_| | \n"
           "    ____|  || | |   ||       ||   _   |\n"
           "   | ______|| |_|   ||___    ||  | |  |\n"
           "   | |_____ |       |    |   ||  |_|  |\n"
           "   |_______||_______|    |___||_______|\n"
           "                                       \n"
           "                                       \n");
    normvideo();
    flecha_aqui(1, posicao); printf("         NOVO JOGO \n"
                                    "                   \n");
    flecha_aqui(2, posicao); printf("         CONTINUAR \n"
                                    "                   \n");
    flecha_aqui(3, posicao); printf("         RECORDES      \n"
                                    "                   \n");
    flecha_aqui(4, posicao); printf("         INSTRUCOES      \n"
                                    "                   \n");
    flecha_aqui(5, posicao); printf("         SAIR      \n"
                                    "                   \n");
    textcolor(YELLOW);
    printf("                                     \n");
    normvideo();

    tecla_press = getch();

    if (tecla_press == BAIXO && posicao != MAX){
        posicao++;
    }else if (tecla_press == CIMA && posicao != MIN){
        posicao--;
    }else {
        posicao = posicao;
          }


    }

    if (posicao == 1){
        system("cls");
        jogar(0);

        }else if(posicao == 2){
        jogar(2);
        }else if(posicao == 3)
        {
        do{

            system("cls");
            imprimeRecorde(tam2);
            printf("\nDigite:\n[1] Jogar\n[2] Voltar ao menu anterior\n");
            scanf("%d", &tecla2);

            if(tecla2 == 1){
                system("cls");
                jogar(0);
                break;
				}else if(tecla2 == 2){
                    menu();
				}else if((tecla2 != 1)&&(tecla2 != 2)){
					printf("Opcao Invalida!\n");
					system("pause");
				}
			}while((tecla2 != 1)&&(tecla2 != 2));

            } else if( posicao == 4){
            do{
				system("cls");
				imprime_intrucoes();
				scanf("%d", &tecla2);
				if(tecla2 == 1){
					system("cls");
            		jogar(0);
            		break;
				}else if(tecla2 == 2){
					menu();
				}else if((tecla2 != 1)&&(tecla2 != 2)){
					printf("Opcao Invalida!\n");
					system("pause");
				}
			}while((tecla2 != 1)&&(tecla2 != 5));

            } else if( posicao == 5){
                system("cls");
                printf("Saindo do jogo...");
                exit(1);

            }

}

//Imprime a flecha que indicar� e selecionar� a funcionalidade desejada
void flecha_aqui (int posicao_real, int posicao_flecha) {
    if (posicao_real == posicao_flecha){
        textcolor(RED);
        printf(" ===> ");
        normvideo();
    }else{
        printf("      ");
        }

}

//Faz a aloca��o das fun��es contem toda a funcinalidade e l�gica do jogo
void jogar(int var){
    //Declara��o das vari�veis
    int tecla, i = 0, j = 0;
    int a, b, c, d, e, f, g, h;
    int **matriz;
    int tamanho = 4;
	int jogadas = 0;
	int digita = 0;
	char nome[100];
	int jogs, sc;
	Jogador play;
	play.score = 0;

	if(var == 0){
		fflush(stdin);
		system("cls");
		printf("Digite seu nome: ");
		gets(play.nome);
		fflush(stdin);
	}

	//Aloca��o da memoria necessaria
    matriz = malloc (tamanho * sizeof (int *));
	for (i = 0; i < tamanho; ++i){
		matriz[i] = malloc (tamanho * sizeof (int));
	}
	//se a variavel recebida for 0 entao o programa esta sendo inciado pela primeira vez, ou nao esta lendo um arquivo salvo
    if(var == 0){
		inicializa_matriz(matriz,&tamanho);
		gerar_valor(matriz,&tamanho);
		gerar_valor(matriz,&tamanho);
		//apos o pause o jogo deve voltar ao normal, entao � feito um backup temporario
	}else if(var == 1){
		FILE *leitura, *leitura2;

			i = 0;
			leitura = fopen("Backup4x4.txt", "r");
			if(leitura == NULL){
				printf("Arquivo nao encontrado!\n");
			}else{
				while(fscanf(leitura, "%d %d %d %d", &a, &b, &c, &d) != EOF){
					matriz[i][0] = a;
					matriz[i][1] = b;
					matriz[i][2] = c;
					matriz[i][3] = d;
					i++;
				}
			}
			leitura2 = fopen("Backup2-4x4.txt", "r");
			if(leitura2 == NULL){
				printf("Arquivo nao encontrado!\n");
			}else{
				fscanf(leitura2, "%s %d %d", &nome, &sc, &jogs);
				strcpy(play.nome, nome);
				play.score = sc;
				jogadas = jogs;
			}
			fclose(leitura);
			fclose(leitura2);

		}
    //Le o arquivo salvo
	else if(var == 2){
		FILE *leitura, *leitura2;

			i = 0;
			leitura = fopen("Grava4x4.txt", "r");
			if(leitura == NULL){
				printf("Arquivo nao encontrado!\n");
			}else{
				while(fscanf(leitura, "%d %d %d %d", &a, &b, &c, &d) != EOF){
					matriz[i][0] = a;
					matriz[i][1] = b;
					matriz[i][2] = c;
					matriz[i][3] = d;
					i++;
				}
			}
			leitura2 = fopen("Grava2-4x4.txt", "r");
			if(leitura2 == NULL){
				printf("Arquivo nao encontrado!\n");
			}else{
				fscanf(leitura2, "%s %d %d", &nome, &sc, &jogs);
				strcpy(play.nome, nome);
				play.score = sc;
				jogadas = jogs;
			}
			fclose(leitura);
			fclose(leitura2);

	}
	desenha_matriz(matriz,&tamanho,jogadas, play.score,play.nome);

    while(!perdeu(matriz, &tamanho)){
        tecla = getch();

        if(tecla==224){
        	//Funcao para usar as teclas para movimentar
            tecla = getch();

            if(tecla==CIMA){
            	ganhou(matriz,&tamanho,&play, 0, 0);//Verifica se ganhou
				//printf("Cima.\n");
				if(permitido_ir_para_cima(matriz, &tamanho)==1){
            		movimenta_cima(matriz, &tamanho, &play.score);//Movimenta para cima
            		gerar_valor(matriz,&tamanho);//Gera um novo 2 na matriz
                	jogadas++;//Incrementa as jogadas
            		desenha_matriz(matriz, &tamanho, jogadas, play.score, play.nome);//Atualiza a Tela
                }else{
					//printf("Jogada Invalida!\n");
				}
            }
            //Verifica se a tecla apertada foi esquerda
            else if(tecla==BAIXO){
            	ganhou(matriz,&tamanho,&play, 0, 0);//Verifica se ganhou
				//printf("Baixo.\n");
				if(permitido_ir_para_baixo(matriz, &tamanho)==1){
					movimenta_baixo(matriz, &tamanho, &play.score);//Movimenta para baixo
            		gerar_valor(matriz, &tamanho);//Gera um novo 2 na matriz
                	jogadas++;//Incrementa as jogadas
            		desenha_matriz(matriz, &tamanho, jogadas, play.score, play.nome);//Atualiza a Tela
				}else{
					//printf("Jogada Invalida!\n");
				}
            }
            //Verifica se a tecla apertada foi esquerda
            else if(tecla==ESQUERDA){
            ganhou(matriz,&tamanho,&play, 0, 0);//Verifica se ganhou
				//printf("Esquerda.\n");
            	if(permitido_ir_para_esquerda(matriz, &tamanho)==1){
					movimenta_esquerda(matriz, &tamanho, &play.score);//Movimenta para esquerda
            		gerar_valor(matriz,&tamanho);//Gera um novo 2 na matriz
                	jogadas++;//Incrementa as jogadas
            		desenha_matriz(matriz, &tamanho, jogadas, play.score, play.nome);//Atualiza a Tela
                }else{
					//printf("Jogada Invalida!\n");
				}
            }
            //Verifica se a tecla apertada foi direita
            else if(tecla==DIREITA){
            ganhou(matriz,&tamanho, &play, 0, 0);//Verifica se ganhou
				//printf("Direita.\n");
				if(permitido_ir_para_direita(matriz, &tamanho)==1){
            		movimenta_direita(matriz, &tamanho, &play.score);//Movimenta para direita
            		gerar_valor(matriz, &tamanho);//Gera um novo 2 na matriz
                	jogadas++;//Incrementa as jogadas
            		desenha_matriz(matriz, &tamanho, jogadas, play.score, play.nome);//Atualiza a tela
                }else{
					//printf("Jogada Invalida!\n");
				}
            }
        }
        //Verifica se a tecla apertada foi P
        if(tecla == PAUSE){
           	system("cls");
			menu_pause();
			continua(tamanho, matriz, play, jogadas);
		}

	}
    if(perdeu(matriz,&tamanho))
    {
    	textbackground(RED);
    	printf("\n\n\tVoce perdeu! :'(.\n");
    	sleep(5);
    	normvideo();
    	escolha_do_vencedor_ou_perdedor();
	}
}

//Desenha a matriz na tela, com base no printf e imprime o nome do jogador, seu numero de jogadas e seu score
void desenha_matriz(int **matriz, int *tamanho, int jogadas, int score, char nome[50]){
    int linha;
    int coluna;
    system("cls");
    textbackground(YELLOW);
    textcolor(BLACK);
    printf("Jogador:%s\t\t Jogadas: %d\t\tScore: %d",nome,jogadas, score);
    printf("\n\n");
    normvideo();

    for(linha = 0; linha < (*tamanho); linha++){

        printf("\t\t    %d   ||  %d   ||  %d  ||  %d    \n", matriz[linha][0], matriz[linha][1],matriz[linha][2],matriz[linha][3]);
        textcolor(MAGENTA);
        printf("\t\t    ----------------------------     \n");
        normvideo();
    	}

    textbackground(YELLOW);
    textcolor(BLACK);
    printf("\n");
    printf("\tUse as Setas do Teclado para movimentar. Pressione \"P\" para Pausar. \n");
    normvideo();
}

//Inicializa toda a matriz com valores nulos
void inicializa_matriz(int **matriz, int *tamanho){
    int linha; //�ndice das linhas
    int coluna; //�ndice das colunas

    //Percorrendo a matriz
    for(linha=0; linha<(*tamanho); linha++){
        for(coluna=0; coluna<(*tamanho); coluna++){
            matriz[linha][coluna] = 0;
        }
    }
}

//Gera aleatoriamente o valor 2 na matriz em cada jogada
void gerar_valor(int **matriz, int *tamanho){
    int linha;
    int coluna;
    /*Fun��o utilizada para gerar posi��es diferentes a cada vez que o c�digo rodar*/
    srand(time(NULL));

    do{
        linha = rand()%(*tamanho);
        coluna = rand()%(*tamanho);

    }while(matriz[linha][coluna]!=0);
    matriz[linha][coluna] = 2;


}

//Se o jogador chegar ao numero 2048, a partida � declarada ganha e logo depois sua pontua��o � contabilizada nos recordes
void ganhou(int **matriz, int *tamanho, Jogador *player, int i, int j){
	for(i=0;i<(*tamanho);i++){
		for(j=0;j<(*tamanho);j++){
			if(matriz[i][j]==2048){
				recorde(player, *tamanho);
				printf("\nVOCE VENCEU !!!\n");
				sleep(4);
				escolha_do_vencedor_ou_perdedor();
				break;
			}
		}
	}
}

//Fun��o que declara quando o jogador na� ganhou
int perdeu(int **matriz, int *tamanho, Jogador *player){
	int cont=0;
	cont += permitido_ir_para_esquerda(matriz,tamanho);
	cont += permitido_ir_para_direita(matriz, tamanho);
	cont += permitido_ir_para_cima(matriz, tamanho);
	cont += permitido_ir_para_baixo(matriz, tamanho);
	if(cont==0){

		return 1;

	}else{
		return 0;
}
}

//Fun��o que permite o movimento para a esquerda
int permitido_ir_para_esquerda(int **matriz, int *tamanho){
	int i,j;
	int mover = 0;
	for(i=0;i<(*tamanho);i++){
		for(j=(*tamanho)-1;j>0;j--){
			if(matriz[i][j] != 0){
				if((matriz[i][j-1]==0 || matriz[i][j] == matriz[i][j-1])){
					mover = 1;
				}
			}
		}
	}
	return mover;
}

//Fun��o que realiza o movimento para a esquerda
void movimenta_esquerda(int **matriz, int *tamanho, int *score){
	int i, j;
	int mover_coluna=0;
	int mover_coluna_soma=0;
	for(i=0;i<(*tamanho);i++){
		mover_coluna = 0;
		for(j=0;j<(*tamanho);j++){
			if(matriz[i][j]!=0){
			    matriz[i][mover_coluna] = matriz[i][j];
			    mover_coluna++;
			}
		}
		for(j=mover_coluna; j<(*tamanho);j++){
			matriz[i][j] =0;
		}
	}
	i = 0;
	//While pra ver se os valores sao iguais, caso for soma os valores
	while(i<(*tamanho)){
		mover_coluna_soma=0;
		for(j=0;j<(*tamanho);j++){
			if(matriz[i][j]!=0){
				if(matriz[i][j]==matriz[i][j+1]){
					matriz[i][mover_coluna_soma] = 2*matriz[i][j];
					(*score) += matriz[i][mover_coluna_soma];
					matriz[i][mover_coluna_soma+1] = 0;
					mover_coluna_soma++;
				}else{
				   	matriz[i][mover_coluna_soma] = matriz[i][j];
				   	mover_coluna_soma++;
				}
			}
		}
		j = mover_coluna_soma;
		while(j<(*tamanho)){
			matriz[i][j] = 0;
			j++;
		}
		i++;
	}
}

//Fun��o que permite o movimento para a direita
int permitido_ir_para_direita(int **matriz, int *tamanho){
	int i,j;
	int mover = 0;
	for(i=0;i<(*tamanho);i++){
		for(j=0;j<(*tamanho)-1;j++){
			if(matriz[i][j] != 0){
				if((matriz[i][j+1]==0 || matriz[i][j] == matriz[i][j+1])){
					mover = 1;
				}
			}
		}
	}
	return mover;
}

//Fun��o que realiza o movimento para a direita
void movimenta_direita(int **matriz, int *tamanho, int *score){
	int i, j;

	int mover_coluna=0;
	int mover_coluna_soma=0;
	for(i=0;i<(*tamanho);i++){
		mover_coluna = ((*tamanho)-1);
		for(j=((*tamanho)-1);j>=0;j--){
			if(matriz[i][j]!=0){
				matriz[i][mover_coluna] = matriz[i][j];
				mover_coluna--;
			}
		}
		for(j=mover_coluna; j>=0; j--){
			matriz[i][j] = 0;
		}
	}
	i = 0;
	//While pra ver se os valores sao iguais, caso for soma os valores
	while(i<(*tamanho)){
		mover_coluna_soma=((*tamanho)-1);
		for(j=((*tamanho)-1);j>=0;j--){
			if(matriz[i][j]!=0){
				if(matriz[i][j]==matriz[i][j-1]){
					matriz[i][mover_coluna_soma] = 2*matriz[i][j];
					(*score) = (*score) + matriz[i][mover_coluna_soma];
					j--;
					mover_coluna_soma--;
				}else{
					matriz[i][mover_coluna_soma] = matriz[i][j];
					mover_coluna_soma--;
				}
			}
		}
		for(j=mover_coluna_soma;j>=0;j--){
			matriz[i][j] = 0;
		}
		i++;
	}
}

//Fun��o que permite o movimento para cima
int permitido_ir_para_cima(int **matriz, int *tamanho){
	int i,j;
	int mover = 0;
	for (i=(*tamanho-1);i>0;i--){
		for(j=0;j<(*tamanho);j++){
			if(matriz[i][j] != 0){
				if((matriz[i-1][j]==0 || matriz[i][j] == matriz[i-1][j])){
					mover = 1;
				}
			}
		}
	}
	return mover;
}

//Fun��o que realiza o movimento para cima
void movimenta_cima(int **matriz, int *tamanho, int *score){
	int i, j, anda;
    for(i = 0; i < (*tamanho); i++){
        anda = 0;
        for(j = 1; j < (*tamanho); j++){
            if(matriz[anda][i] == matriz[j][i]){
                (*score) += matriz[anda][i] *= 2;
                matriz[j][i] = 0;
            }
            else if(matriz[j][i] != 0){
                anda = j;
            }
        }
        for(j = 1; j < (*tamanho); j++){
            anda = j;
            while((anda-1 >= 0) && (matriz[anda-1][i] == 0)){
                matriz[anda-1][i] = matriz[anda][i];
                matriz[anda][i] = 0;
                anda--;
            }
        }
    }
}

//Fun��o que permite o movimento para baixo
int permitido_ir_para_baixo(int **matriz, int *tamanho){
	int i, j;
	int mover = 0;
	for(i=0;i<(*tamanho)-1;i++){
		for(j=0;j<(*tamanho);j++){
			if(matriz[i][j] != 0){
				if((matriz[i+1][j]==0 || matriz[i][j] == matriz[i+1][j])){
					mover = 1;
				}
			}
		}
	}
	return mover;
}

//Fun��o que realiza o movimento para baixo
void movimenta_baixo(int **matriz, int *tamanho, int *score){
	int i, j, move;
    for(i = 0; i < (*tamanho); i++){
        move = (*tamanho) - 1;
        for(j = (*tamanho) - 2; j >= 0; j--){
            if(matriz[move][i] == matriz[j][i]){
                (*score) += matriz[move][i] *= 2;
                matriz[j][i] = 0;
            }
            else if(matriz[j][i] != 0){
                move = j;
            }
        }
        for(j = (*tamanho)-2; j >= 0; j--){
            move = j;
            while(move+1 < (*tamanho) && matriz[move+1][i] == 0){
                matriz[move+1][i] = matriz[move][i];
                matriz[move][i] = 0;
                move++;
            }
        }
    }
}

//Imprime na tela um meno ap�s a partida ter acabado
void menu_do_vencedor_ou_perdedor(){
	textbackground(BLUE);
	textcolor(WHITE);

	printf("\n   ---------------------------------------\n");
    printf("   |                                     |\n");
    printf("   |  [1] - Jogar novamente              |\n");
    printf("   |  [2] - Voltar ao menu inicial       |\n");
    printf("   |  [3] - Sair.                        |\n");
    printf("   |                                     |\n");
    printf("   ---------------------------------------\n");

    normvideo();
}

//Da funcionalidade ao menu_do_vencedor_ou_perdedor
void escolha_do_vencedor_ou_perdedor(){
	//Declara��o de Vari�veis
    int tecla = 0, tecla2 = 0;

	system("cls");
    menu_do_vencedor_ou_perdedor();

	do{
		do{
			scanf("%d", &tecla);
		}while((tecla < 0)||(tecla > 4));
		if(tecla == 1){
			system("cls");
            jogar(0);
            break;
		}else if(tecla == 2){
				system("cls");
				menu();
			break;
		}else if(tecla == 3){
			system("cls");
			printf("Saindo do jogo...\n");
			sleep(1);
			exit(1);
			break;
		}
	}while(tecla != 4);
    return;
}

//Imprime as instru��es do jogo na tela, quando este menu � selecionado no menu principal
void imprime_intrucoes(){
	int tecla;
	textbackground(BLUE);
	textcolor(WHITE);
	printf("\t\t - - - - - I N S T R U C O E S - - - - - \n\n");
	printf("\tUtilize as setas do teclado para movimentar os numeros.\n");
	printf("\tCaso os numeros na direcao movimentada sejam iguais, eles serao somados.\n");
	printf("\tO jogo termina quando o somatorio dos numeros seja 2048, ou quando todas \n\tas lacunas estejam preenchidas.\n");
	printf("\tTenha um otimo jogo! :D");
	printf("\n\n Opcoes: \n[1] Jogar\n[2] Voltar ao menu anterior\n");
	normvideo();
}

//L� o nome do jogador
void leitura_Nome(Jogador *vet, int tamanho){
	int i;
	FILE *recordeNome;

		recordeNome = fopen("recordesNomes4x4.txt","r");

	while(fscanf(recordeNome,"%s", vet[i].nome) != EOF){
		i++;
	}
	fclose(recordeNome);
}

//L� o score do jogador
void leitura_Pontos(Jogador *vet, int tamanho){
	FILE *recordePontos;
	int i = 0;

		recordePontos = fopen("recordesPontos4x4.txt","r");


	while(fscanf(recordePontos,"%d", &vet[i].score) != EOF){
		i++;
	}
	fclose(recordePontos);
}

////Ordena o vetor de Jogadores lido
void ordenacao(Jogador *vetor){
	Jogador aux;
	int x, y;
	for(x = 0; x < 10; x++ ){
    	for( y = x + 1; y < 10; y++ ){
      		if ( vetor[y].score > vetor[x].score){
         		aux.score = vetor[y].score;
         		strcpy(aux.nome, vetor[y].nome);
         		vetor[y].score = vetor[x].score;
         		strcpy(vetor[y].nome, vetor[x].nome);
         		vetor[x].score = aux.score;
         		strcpy(vetor[x].nome, aux.nome);
      		}
    	}
	}

}

//Grava o recorde do jogador caso ele ganhe
void recorde(Jogador *player, int tamanho){
	FILE *recordeNome;
	FILE *recordePontos;
	Jogador vetor[10];
	int i;

	for(i = 0; i < 10; i++){
		vetor[i].score = 0;
		strcpy(vetor[i].nome,"NULL");
	}

	leitura_Nome(vetor, tamanho);
	leitura_Pontos(vetor, tamanho);

	ordenacao(vetor);
	for(i = 0; i < 10; i++){
		if(i == 4){
			if((*player).score >= vetor[i].score){
   				strcpy(vetor[i].nome, (*player).nome);
   				vetor[i].score = (*player).score;
   				break;
			}
		}else{
			if((*player).score >= vetor[i].score){
				vetor[i+1].score = vetor[i].score;
         		strcpy(vetor[i+1].nome, vetor[i].nome);
   				strcpy(vetor[i].nome, (*player).nome);
   				vetor[i].score = (*player).score;
   				break;
			}
		}
	}

		recordeNome = fopen("recordesNomes4x4.txt","w");
		recordePontos = fopen("recordesPontos4x4.txt","w");


    for(i = 0; i < 10; i++){
    	fprintf(recordeNome, "%s\n", vetor[i].nome);
		fprintf(recordePontos, "%d\n", vetor[i].score);
	}

	fclose(recordeNome);
	fclose(recordePontos);
}

//Imprime a tabela com os 10 recorde, quando � selecionado diretamente do menu principal
void imprimeRecorde(int tamanho){
	Jogador aux[10];
	int i;
	for(i = 0; i < 10; i++){
		aux[i].score = 0;
		strcpy(aux[i].nome,"NULL");
	}
	leitura_Nome(aux, tamanho);
	leitura_Pontos(aux, tamanho);
    printf("\n        ------------------RECORDES---------------\n");
    printf("	|                                       |\n");
	for(i = 0; i < 10; i++){
		printf("	|\t%s               \t%d	|\n", aux[i].nome, aux[i].score);
	}
    printf("	|                                       |\n");
    printf("        -----------------------------------------\n");
}


void continua(int tamanho, int **matriz, Jogador player, int jog){
	FILE *salvo, *salvo2;
	int digita, i, j;
	char nome[100], copia[100];
	int sc, jogs;
	do{
		scanf("%d", &digita);
		if((digita < 1)||(digita > 4)){
			printf("Opcao Invalida!\nDigite novamente: ");
			scanf("%d", &digita);
		}
	}while((digita < 1)||(digita > 4));

		salvo = fopen("Backup4x4.txt","w");
		salvo2 = fopen("Backup2-4x4.txt", "w");
		fprintf(salvo2, "%s %d %d", player.nome, player.score, jog);
		for(i = 0; i < tamanho; i++){
			for(j = 0; j < tamanho; j++){
				fprintf(salvo, "%d ", matriz[i][j]);
			}
			fprintf(salvo, "\n");
		}

	if(digita == 1){
		fclose(salvo);
		fclose(salvo2);
		jogar(1);
	}else if(digita == 2){
		fclose(salvo);
		fclose(salvo2);
		FILE *ler, *ler2, *grava, *grava2;

			i = 0;
			ler = fopen("Backup4x4.txt", "r");
			grava = fopen("Grava4x4.txt", "w");
			while(fgets(copia, 100, ler) != NULL){
				fprintf(grava, "%s", copia);
			}
			ler2 = fopen("Backup2-4x4.txt", "r");
			grava2 = fopen("Grava2-4x4.txt", "w");
			fgets(copia, 100, ler2);
			fprintf(grava2, "%s", copia);
			fclose(ler);
			fclose(ler2);
			fclose(grava);
			fclose(grava2);
			//Apaga os arquivo de Backup temporarios
			remove("Backup4x4.txt");
			remove("Backup2-4x4.txt");

		system("cls");
		printf("Saindo...\n");
		sleep(1);
		exit(1);
	}else if(digita == 3){
		fclose(salvo);
		fclose(salvo2);
		jogar(0);
	}else if(digita == 4){
		fclose(salvo);
		fclose(salvo2);
		system("cls");
		printf("Saindo...\n");
			//Apaga os arquivo de Backup temporarios
			remove("Backup4x4.txt");
			remove("Backup2-4x4.txt");

		sleep(1);
		exit(1);
	}
	fclose(salvo);
	fclose(salvo2);
}

//Imprime o menu pause na tela, ap�s o jogador selecionar a tecla PAUSE
void menu_pause(){
	printf("\n   -----------------JOGO PAUSADO-------------\n");
    printf("   |                                        |\n");
    printf("   |\t  Escolha uma opcao:                |\n");
    printf("   |\t  [1] -  Continuar o Jogo           |\n");
    printf("   |\t  [2] -  Salvar e sair              |\n");
    printf("   |\t  [3] -  Reiniciar o Jogo           |\n");
    printf("   |\t  [4] -  Sair sem Salvar            |\n");
    printf("   |                                        |\n");
    printf("   ------------------------------------------\n");
    printf("   Digite a opcao desejada.\n   Tecle ENTER para confirmar.\n");
}
