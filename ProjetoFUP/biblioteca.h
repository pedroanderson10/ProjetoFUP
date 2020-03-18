#define SAQUE                      0
#define DEPOSITO                   1
#define TRAN_RECEB                 2
#define TRAN_ENV                   3


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

