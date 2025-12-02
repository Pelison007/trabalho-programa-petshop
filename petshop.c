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

int main(){

    setlocale(LC_ALL, "Portuguese");

    int opca;

    printf ("Informe opcao: ");
    scanf ("%d", &opca);

    return 0;
}