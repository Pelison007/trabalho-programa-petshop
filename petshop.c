#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>  
#include <direct.h>     
#include <time.h>
#include <windows.h>

#define ESC 27
#define OPCAO_SAIR 9

//  funcao para ler opcoes do case, por conta do 'ESC', vai ler diretamente sem esperar o ENTER //
int obterOpcao() {
    char tecla_lida; 
    
    tecla_lida = getch(); 

    // 1. VERIFICAÇÃO DO ESC
    // Se for ESC (código 27), retorna o valor fixo de saída: 9
    if (tecla_lida == ESC) {
        return OPCAO_SAIR; 
    }
    
    // 2. VERIFICAÇÃO DOS DÍGITOS (1 a 9)
    // Se for qualquer dígito de '1' a '9', retorna o valor numérico.
    else if (tecla_lida >= '1' && tecla_lida <= '9') {
        return tecla_lida - '0'; 
    }
    
    // 3. CASO INVÁLIDO
    return 0; 
}

struct Produto {
	char categoria[50];
    char nome[50];
    float preco;
};

struct Produto racoes[] = {
    {"Rações", "Ração Premium para Cães", 129.90},
    {"Rações", "Ração para Gatos Adultos", 99.50},
    {"Rações", "Ração Filhotes Raças Pequenas", 84.30},
    {"Rações", "Ração Light para Cães Obesos", 115.00}
};
int totalRacoes = sizeof(racoes) / sizeof(racoes[0]);

struct Produto brinquedos[] = {
    {"Brinquedos", "Bola de Borracha", 25.90},
    {"Brinquedos", "Corda Trançada", 22.50},
    {"Brinquedos", "Pelúcia Mordedor", 39.00},
    {"Brinquedos", "Frisbee Pet", 34.90}
};
int totalBrinquedos = sizeof(brinquedos) / sizeof(brinquedos[0]);

struct Produto higiene[] = {
    {"Higiene", "Shampoo Neutro 500ml", 35.00},
    {"Higiene", "Tapete Higiênico (30 unidades)", 89.00},
    {"Higiene", "Escova Dental Pet", 19.90},
    {"Higiene", "Perfume Pet 120ml", 44.90}
};
int totalHigiene = sizeof(higiene) / sizeof(higiene[0]);

struct Produto acessorios[] = {
    {"Acessórios", "Coleira Ajustável", 39.50},
    {"Acessórios", "Peitoral Confort", 79.90},
    {"Acessórios", "Caminha Acolchoada", 120.00},
    {"Acessórios", "Comedouro Inox", 59.90}
};
int totalAcessorios = sizeof(acessorios) / sizeof(acessorios[0]);

struct Servico {
    char nome[50];
    float preco;
};

// tipo dos serviços e valores //
struct Servico servicos[] = {
	{"Banho", 35.00},
	{"Tosa", 55.00},
    {"Banho e Tosa Completo", 80.00},
    {"Consulta Veterinária", 150.00},
    {"Vacinação", 120.00},
    {"Busca e Entrega", 0.0}
};

int main(){

    setlocale(LC_ALL, "Portuguese");

    int opca;
    int opca2;

    printf ("Informe opcao: ");
    scanf ("%d", &opca);

    printf ("\no numero digitado foi: %d", opca);

    printf ("Informe 2 numero: ");
    scanf ("%d", &opca2);

    printf ("\no 2 numero digitado foi: %d", opca2);

    return 0;
}