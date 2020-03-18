#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  int conta;
  char nome[50];
  float saldo;
}cliente;
typedef struct{
  float saldo_ant, saldo_atual, valor_transacao;
  int tipo, conta;
  time_t t;
}operacao;

void clientes_para_arquivo(cliente *v, int *n);
void operacoes_para_arquivo(operacao *h, int *p);
cliente* carrega_clientes_arquivo(cliente *v, int *n);
operacao* carrega_operacoes_arquivo(operacao *h , int *p);

cliente recebe_dados();
cliente* insere_cliente(cliente *v, int *n, cliente novo);
cliente* remove_cliente(cliente *v, int *n, int conta);
cliente* deposito_cliente(cliente *v, int *n, int conta , operacao *h, float *saldo_ant, float *saldo_atual);
void dados_cliente(cliente *v, int *n);
cliente* saque_cliente(cliente *v, int *n, int conta, float *saldo_ant, float *saldo_atual , float *valor_transacao);
cliente* transferencia_env(cliente *v, int *n, int conta, float *saldo_ant,float *saldo_atual , float *valor_transacao);
cliente* transferencia_rec(cliente *v, int *n, int conta ,float *saldo_ant,float *saldo_atual);
operacao recebe_operacao(int tipo , int conta , float saldo_ant , float valor_transacao , float saldo_atual, int t);
operacao* nova_operacao(operacao *h , int *p , operacao nova);
void extrato(operacao *h ,int *p ,cliente *v, int *n, int conta);
operacao* remove_operacao(operacao *h, int *p, int conta);
void tempo();



void clientes_para_arquivo(cliente *v, int *n){

	FILE *arquivo_cliente = fopen("clientes.txt", "w");

	if (arquivo_cliente == 0) {
		//printf("Erro: nao foi possivel abrir arquivo!\n");
		return;
	}

	int i;
	for (i = 0; i < *n; i++) {
		fprintf(arquivo_cliente, "%d\n%s\n%.2f\n", v[i].conta, v[i].nome, v[i].saldo);
	}

	fclose(arquivo_cliente);
}
void operacoes_para_arquivo(operacao *h, int *p) {

	FILE *arquivo_operacao = fopen("operacoes.txt", "w");

	if (arquivo_operacao == 0) {
		return;
	}

	int i;
	for (i = 0; i < *p; i++) {
		fprintf(arquivo_operacao, "%d\n%d\n%.2f\n%.2f\n%.2f\n%ld\n",
		h[i].conta, h[i].tipo, h[i].saldo_ant, h[i].valor_transacao, h[i].saldo_atual ,h[i].t);
	}

	fclose(arquivo_operacao);
}
cliente* carrega_clientes_arquivo(cliente *v, int *n) {

    cliente a;
	FILE *arquivo_cliente = fopen("clientes.txt", "r");
	if (arquivo_cliente == 0) {
		//printf("Erro: nao foi possivel abrir arquivo!");
		return 0;
	}

	while(fscanf(arquivo_cliente,"%d\n",&a.conta)==1){
            fgets(a.nome,sizeof(a.nome),arquivo_cliente);
            a.nome[strlen(a.nome)-1] = 0;
            fscanf(arquivo_cliente,"%f\n",&a.saldo);
            v = insere_cliente(v,n,a);
    }

	fclose(arquivo_cliente);
	return v;
}
operacao* carrega_operacoes_arquivo(operacao *h , int *p) {

    operacao a;
	FILE *arquivo_operacao = fopen("operacoes.txt", "r");

	if (arquivo_operacao == 0) {
		return 0;
	}

	while(fscanf(arquivo_operacao,"%d\n",&a.conta)==1){
            fscanf(arquivo_operacao,"%d\n",&a.tipo);
            fscanf(arquivo_operacao,"%f\n",&a.saldo_ant);
            fscanf(arquivo_operacao,"%f\n",&a.valor_transacao);
            fscanf(arquivo_operacao,"%f\n",&a.saldo_atual);
            fscanf(arquivo_operacao,"%ld\n",&a.t);
          //  a.t = time(0);

            h = nova_operacao(h,p,recebe_operacao(a.tipo , a.conta , a.saldo_ant , a.valor_transacao , a.saldo_atual, a.t));
    }

	fclose(arquivo_operacao);
	return h;
}

cliente recebe_dados(){
  cliente x;

  printf("Insira numero da conta : ");
  scanf("%d",&x.conta);

  printf("Insira nome do cliente : ");
  getchar();
  fgets(x.nome, sizeof(x.nome), stdin);
  x.nome[strlen(x.nome)-1] = 0;

  printf("Insira deposito inicial : ");
  scanf("%f",&x.saldo);

  return x;
}
cliente* insere_cliente(cliente *v, int *n, cliente novo){

  v=(cliente*) realloc(v,(*n+1)*sizeof(cliente)); // realoque a mem�ria do vetor para conter um elemento a mais.

  if(v==0){
      return 0;
  }

  v[*n]=novo; //grave no novo elemento do vetor (final) o cliente 'novo' recebido como par�metro
  (*n)++; // increvemente o tamanho do vetor (par�metro passado por refer�ncia)

  return v; // retorne o endere�o de mem�ria do vetor alocado/realocado
}
cliente* remove_cliente(cliente *v, int *n, int conta){

  for(int i=0;i<*n;i++){
    if(v[i].conta==conta){

      v[i]=v[*n-1]; // copie �ltimo elemento do vetor para a posi��o i

      v=(cliente*)realloc(v,(*n-1)*sizeof(cliente)); // realoque vetor para conter um elemento a menos
      (*n)--; //reduza em 1 o tamanho do vetor (passado por refer�ncia)
      printf("Conta removida com sucesso\n");

      if(v==0){
        return 0;
      }
      break;
    }
  }

  return v; // retorne o endere�o de mem�ria do vetor realocado
}
cliente* deposito_cliente(cliente *v, int *n, int conta , operacao *h, float *saldo_ant, float *saldo_atual){

  float deposito;

  for(int i=0;i<*n;i++){
    if(v[i].conta == conta){

      *saldo_ant = v[i].saldo;

      printf("Insira valor de deposito : ");
      scanf("%f",&deposito);
      v[i].saldo+=deposito;

      printf("Deposito realizado com sucesso\n ");

      *saldo_atual = v[i].saldo;


    }
  }
  return v;
}
void dados_cliente(cliente *v, int *n){

  for(int i=0 ; i<*n ; i++){
    printf("\nNumero da conta: %d\n",v[i].conta);
    printf("Nome do cliente: %s\n",v[i].nome);
    printf("Saldo atual: %.2lf\n",v[i].saldo);
  }
}
cliente* saque_cliente(cliente *v, int *n, int conta, float *saldo_ant, float *saldo_atual , float *valor_transacao){

  float saque;
  for(int i=0;i<*n;i++){

    if(v[i].conta==conta){

      printf("Insira valor de saque : ");
      scanf("%f",&saque);

      *saldo_ant = v[i].saldo;

      if(v[i].saldo >= saque){
          v[i].saldo-=saque;
          *saldo_atual = v[i].saldo;
          *valor_transacao = saque;
          printf("Saque realizado com sucesso\n ");
      }else if(v[i].saldo < saque){
          printf("Nao possui saldo suficiente\n");
          *saldo_atual = v[i].saldo;
          *valor_transacao = 0;
          break;
      }

    }

  }
  return v;
}/* end function saque_cliente */
cliente* transferencia_env(cliente *v, int *n, int conta, float *saldo_ant,float *saldo_atual , float *valor_transacao){

  float transf;

  for(int i=0;i<*n;i++){

    if(v[i].conta==conta)
    {
      *saldo_ant=v[i].saldo;
      printf("Insira valor a ser transferido : ");
      scanf("%f",&transf);

      if(v[i].saldo < transf){
        printf("Nao possui saldo suficiente\n");
        *saldo_atual=v[i].saldo;
        *valor_transacao = 0;
      }else{
        v[i].saldo-=transf;
        *valor_transacao = transf;
        *saldo_atual=v[i].saldo;
      }
    }
  }
  return v;
}/* end function transferencia */
cliente* transferencia_rec(cliente *v, int *n, int conta,float *saldo_ant,float *saldo_atual ){
  float transf = *saldo_ant - *saldo_atual;
  for(int i=0 ; i<*n ; i++){
    if(v[i].conta==conta) {
      *saldo_ant = v[i].saldo;
      v[i].saldo+=transf;
      *saldo_atual = v[i].saldo;
      printf("Transferencia realizada com sucesso\n ");
    }
  }

  return v;
}/* end function transferencia */
operacao recebe_operacao(int tipo , int conta , float saldo_ant , float valor_transacao , float saldo_atual, int t){

  operacao n;
  n.tipo = tipo ;
  n.conta = conta;
  n.saldo_ant = saldo_ant;
  n.valor_transacao = valor_transacao;
  n.saldo_atual = saldo_atual;
  n.t = t;

  return n;
}
operacao* nova_operacao(operacao *h , int *p , operacao nova){
  h=(operacao*) realloc(h,(*p+1)*sizeof(operacao)); // realoque a mem�ria do vetor para conter um elemento a mais.

  if(h==0){
      return 0;
  }

  h[*p]=nova; //grave no novo elemento do vetor (final) o cliente 'novo' recebido como par�metro
  (*p)++; // increvemente o tamanho do vetor (par�metro passado por refer�ncia)

  return h; // retorne o endere�o de mem�ria do vetor alocado/realocado
}
void extrato(operacao *h ,int *p ,cliente *v, int *n, int conta){
  time_t hoje_t = time(0);
  struct tm *hoje = gmtime(&hoje_t);

  for(int i=0 ; i<*p ; i++){
    struct tm *t = gmtime(&h[i].t);
    if (t->tm_mon == hoje->tm_mon && t->tm_year == hoje->tm_year)
    if(h[i].conta == conta){
      printf("Numero da conta : %d\n", h[i].conta                );

      if(h[i].tipo == 0){
        printf("Operacao realizada: SAQUE\n"                       );
      }else if(h[i].tipo == 1){
        printf("Operacao realizada: DEPOSITO\n"                    );
      }else if(h[i].tipo == 2){
        printf("Operacao realizada: RECEBIMENTO DE TRANSFERENCIA\n");
      }else if(h[i].tipo == 3){
        printf("Operacao realizada: ENVIO DE TRANSFERENCIA\n"      );
      }

      printf("Saldo anterior    : %.2f\n", h[i].saldo_ant      );
      printf("Valor de transacao: %.2f\n", h[i].valor_transacao);
      printf("Saldo atual       : %.2f\n", h[i].saldo_atual    );
      printf("Data da operacao : %s\n", ctime(&h[i].t));
    }
  }

}
operacao* remove_operacao(operacao *h, int *p, int conta){

  for(int i=0;i<*p;i++){
    if(h[i].conta==conta){

      h[i]=h[*p-1]; // copie �ltimo elemento do vetor para a posi��o i

      h=(operacao*)realloc(h,(*p-1)*sizeof(operacao)); // realoque vetor para conter um elemento a menos
      (*p)--; //reduza em 1 o tamanho do vetor (passado por refer�ncia)

      if(h==0){
        return 0;
      }

    }
  }

  return h; // retorne o endere�o de mem�ria do vetor realocado
}

void tempo(){
char* dia_semana[] = {"dom", "seg", "ter", "qua", "qui", "sex", "sab"};
  time_t ini = time(0); // Data/hora atual (segundos desde 01/01/70 00:00:00)
  struct tm *t = gmtime(&ini);
   printf("%d/%d/%d (%s) %d:%d:%d\n",
      t->tm_mday,
      t->tm_mon + 1,
      t->tm_year + 1900,
      dia_semana[t->tm_wday],
      t->tm_hour - 3,
      t->tm_min,
      t->tm_sec);
}
