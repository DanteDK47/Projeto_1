#include <stdio.h>

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100

typedef struct {
    char cpf[12];
    char senha[20];
    double saldoReais;
    double saldoBitcoin;
    double saldoEthereum;
    double saldoRipple;
} Carteira;

typedef struct {
    char data[20];
    char operacao[50];
    double valor;
    double taxa;
} Transacao;

typedef struct {
    Carteira carteira;
    Transacao transacoes[MAX_TRANSACOES];
    int numTransacoes;
} Usuario;

int login(Usuario usuarios[], int numUsuarios, char cpf[], char senha[]) {
    int i;
    for (i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].carteira.cpf, cpf) == 0 && strcmp(usuarios[i].carteira.senha, senha) == 0) {
            return i;
        }
    }
    return -1;
}

void exibirMenu() {
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar reais\n");
    printf("4. Sacar reais\n");
    printf("5. Comprar criptomoeda\n");
    printf("6. Vender criptomoeda\n");
    printf("7. Atualizar cotacao\n");
    printf("8. Sair\n");
}

void gerarDataAtual(char buffer[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main() {
    Usuario usuarios[MAX_USUARIOS];
    int numUsuarios = 1;
    double cotacaoBitcoin = 20000.0, cotacaoEthereum = 1500.0, cotacaoRipple = 1.0;

    strcpy(usuarios[0].carteira.cpf, "12345678901");
    strcpy(usuarios[0].carteira.senha, "senha123");
    usuarios[0].carteira.saldoReais = 10000.0;
    usuarios[0].carteira.saldoBitcoin = 0.0;
    usuarios[0].carteira.saldoEthereum = 0.0;
    usuarios[0].carteira.saldoRipple = 0.0;
    usuarios[0].numTransacoes = 0;

    char cpf[12], senha[20];
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    int indiceUsuario = login(usuarios, numUsuarios, cpf, senha);
    if (indiceUsuario == -1) {
        printf("Login falhou.\n");
        return 0;
    }

    int opcao;
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Saldo de reais: %.2f\n", usuarios[indiceUsuario].carteira.saldoReais);
                printf("Saldo de Bitcoin: %.6f\n", usuarios[indiceUsuario].carteira.saldoBitcoin);
                printf("Saldo de Ethereum: %.6f\n", usuarios[indiceUsuario].carteira.saldoEthereum);
                printf("Saldo de Ripple: %.6f\n", usuarios[indiceUsuario].carteira.saldoRipple);
                break;
            case 2:
                for (int i = 0; i < usuarios[indiceUsuario].numTransacoes; i++) {
                    printf("%s - %s - Valor: %.2f - Taxa: %.2f%%\n", usuarios[indiceUsuario].transacoes[i].data, usuarios[indiceUsuario].transacoes[i].operacao, usuarios[indiceUsuario].transacoes[i].valor, usuarios[indiceUsuario].transacoes[i].taxa * 100);
                }
                break;
