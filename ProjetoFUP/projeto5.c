#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "biblioteca.h"


int main(){

  float saldo_atual=0 , saldo_ant=0 , valor_transacao = 0;
  int comando, conta, n = 0 , p = 0, i = 0;
  time_t t = 0;  // N e P sao o tamanho de clientes do vetor que ser� passado por refer�ncia
  cliente *v = 0; // Vetor de clientes ( Endere�o de mem�ria do vetor )
  operacao *h = 0;// A aloca��o din�mica permite solicitar espa�o de mem�ria em tempo de execu��o.
                  //Digamos que no in�cio do programa voc� n�o sabe o tamanho do vetor que vai precisar.
                  //Se alocar um vetor muito grande estar� desperdi�ando mem�ria RAM.
                  //O ideal � ir solicitando mem�ria � medida que seu programa vai precisando.
  cliente novo;
        v = carrega_clientes_arquivo(v,&n);
        h = carrega_operacoes_arquivo(h,&p);
    do{

      printf("\nMENU\n");
      printf("1 - Inserir cliente\n");
      printf("2 - Remover cliente\n");
      printf("3 - Deposito\n");
      printf("4 - Saque\n");
      printf("5 - Consultar dados dos clientes\n");
      printf("6 - Transferencia\n");
      printf("7 - Consultar extrato\n");
      printf("8 - Salvar processo\n");
      printf("Insira o comando : ");
      scanf("%d",&comando);

      switch(comando){
        case 1 :
            printf("\nINSERCAO DE CLIENTE\n");
            novo = recebe_dados(); // Iremos atribuir ao "NOVO CLIENTE" a fun��o para incluir os dados do cliente
            v=insere_cliente(v,&n,novo);
            printf("Conta criada com sucesso\n"); // Para uma fun��o modificar o valor passado como par�metro,
            break;                       //  devemos passar o endere�o de mem�ria da vari�vel que deve ser modificada (&n)
                                         //Chamamos este procedimento de passagem de par�metro por refer�ncia.
        case 2 :
            printf("\nREMOCAO DE CLIENTE\n");
            printf("Insira numero da conta do cliente : ");
            scanf("%d", &conta);
            v = remove_cliente(v, &n, conta);
            for (i = 0; i < p; i++) {
                h = remove_operacao(h,&p, conta);
            }
            printf("Operacoes do cliente removidas\n");
            break;

        case 3 :
            printf("\nDEPOSITO\n");
            printf("Insira numero da conta do cliente : ");
            scanf("%d", &conta);
            t = time(0);
            v = deposito_cliente(v, &n , conta , h, &saldo_ant, &saldo_atual);
            h = nova_operacao(h , &p , recebe_operacao(DEPOSITO , conta , saldo_ant, saldo_atual-saldo_ant, saldo_atual, t) );

            break;

        case 4 :
            printf("\nSAQUE\n");
            printf("Insira numero da conta do cliente : ");
            scanf("%d", &conta);
            t = time(0);
            v = saque_cliente(v, &n , conta, &saldo_ant, &saldo_atual ,&valor_transacao);
            h = nova_operacao(h , &p , recebe_operacao(SAQUE , conta , saldo_ant, valor_transacao , saldo_atual, t) );
            break;

        case 5 :
            printf("\nCONSULTA DE DADOS\n");
            dados_cliente(v , &n);
            break;

        case 6 :
            printf("\nTRANSFERENCIA\n");
            printf("Insira numero da conta do cliente remetente : ");
            scanf("%d", &conta);
            t = time(0);
            v = transferencia_env(v, &n , conta, &saldo_ant, &saldo_atual ,&valor_transacao);
            h = nova_operacao(h , &p , recebe_operacao(TRAN_ENV , conta , saldo_ant, valor_transacao , saldo_atual, t) );
            printf("Insira numero da conta do cliente destinado : ");
            scanf("%d", &conta);
            t = time(0);
            v = transferencia_rec(v, &n , conta, &saldo_ant, &saldo_atual );
            h = nova_operacao(h , &p , recebe_operacao(TRAN_RECEB , conta , saldo_ant, saldo_atual - saldo_ant , saldo_atual, t) );
            break;

        case 7 :
            printf("\nEXTRATO\n");
            printf("Insira numero da conta do cliente : ");
            t = time(0);
            scanf("%d", &conta);
            extrato(h, &p, v, &n, conta);
            break;

        case 8 :
            clientes_para_arquivo(v,&n);
            operacoes_para_arquivo(h,&p);
            printf("SALVO EM ARQUIVO\n");
            break;

        default:
            printf("\n");
      }

  }while(comando!=0);

            clientes_para_arquivo(v,&n);
            operacoes_para_arquivo(h,&p);
            printf("SALVO EM ARQUIVO\n");

}
