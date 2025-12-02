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

int main(){

    setlocale(LC_ALL, "Portuguese");

    int opca;

    printf ("Informe opcao: ");
    scanf ("%d", &opca);

    return 0;
}