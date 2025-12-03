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

// itens para carrinho //
struct ItemCarrinho {
    char nome[50];  
    float preco;
    int quantidade;
};
int totalServicos = sizeof(servicos) / sizeof(servicos[0]);

// carinho para cada item //
struct Carrinho {
    struct ItemCarrinho *itens;
    int totalItens;
};


// ------------ função para Contratar tipos de Serviços --------------//
void contratarServico(struct Carrinho *carrinho, struct Servico servicos[], int totalServicos) {
    int escolha;

    printf("\n========== SERVIÇOS DISPONÍVEIS =========\n\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. [R$ %.2f] - %s\n", i + 1, servicos[i].preco, servicos[i].nome);
    }
    printf ("6. [ESC] - VOLTAR");
    printf("\n----------------------------------------\n");
    printf("\n-> Qual serviço deseja contratar? ");
    escolha = obterOpcao();
    
    if (escolha == OPCAO_SAIR) {
    	system("cls");
        printf("\nNenhum serviço foi contratado.\n");
        return;
    }

    if (escolha < 1 || escolha > totalServicos && escolha != OPCAO_SAIR) {
    	system("cls");
        printf("\nOpção inválida!\n");
        return;
    }

    int idx = escolha - 1;

    // Inicializa carrinho se estiver vazio
    if (carrinho->itens == NULL) {
        carrinho->itens = (struct ItemCarrinho *) malloc(sizeof(struct ItemCarrinho));
        carrinho->totalItens = 0;
    } else {
        carrinho->itens = (struct ItemCarrinho *) realloc(carrinho->itens,
                            (carrinho->totalItens + 1) * sizeof(struct ItemCarrinho));
    }

    // Adiciona o serviço selecionado ao carrinho
    strcpy(carrinho->itens[carrinho->totalItens].nome, servicos[idx].nome);
    carrinho->itens[carrinho->totalItens].preco = servicos[idx].preco;
    carrinho->itens[carrinho->totalItens].quantidade = 1;
    carrinho->totalItens++;

    // Verifica se já existe serviço de entrega no carrinho
    int entregaJaContratada = 0;
    for (int i = 0; i < carrinho->totalItens; i++) {
        if (strcmp(carrinho->itens[i].nome, "Serviço de entrega") == 0) {
            entregaJaContratada = 1;
            system("cls");
            break;
        }
    }

    // Pergunta sobre entrega apenas se ainda não foi contratada
    if (!entregaJaContratada) {
        char opcaoEntrega;
        printf (" \n\n              // Serviço de UBER PET //               \n");
        printf ("// Tarifa de R$ 2,50 por KM de distancia, IDA E VOLTA //\n");
        printf("\nDeseja que busquemos e entreguemos o pet em casa? [s] / [n]: ");
        scanf(" %c", &opcaoEntrega);

        if (opcaoEntrega == 's' || opcaoEntrega == 'S') {
            float distancia, valorPorKm = 2.50;
            printf("\n-> Informe a distância de ida em km: ");
            scanf("%f", &distancia);

            float valorEntrega = distancia * 2 * valorPorKm; // ida e volta
            char confirmaEntrega;

            printf("\nO custo do serviço de entrega será: R$ %.2f\n", valorEntrega);
            printf("-> Deseja confirmar o serviço de busca e entrega? [s] / [n]: ");
            scanf(" %c", &confirmaEntrega);

            if (confirmaEntrega == 's' || confirmaEntrega == 'S') {
                carrinho->itens = (struct ItemCarrinho *) realloc(
                    carrinho->itens,
                    (carrinho->totalItens + 1) * sizeof(struct ItemCarrinho)
                );
                strcpy(carrinho->itens[carrinho->totalItens].nome, "Serviço de entrega");
                carrinho->itens[carrinho->totalItens].preco = valorEntrega;
                carrinho->itens[carrinho->totalItens].quantidade = 1;
                carrinho->totalItens++;

                system("cls");
                printf("-> Serviço de entrega cadastrado! Valor adicional: R$ %.2f\n", valorEntrega);
            } else {
                system("cls");
                printf("-> Serviço de entrega cancelado.\n");
            }
        } else {
            system("cls");
        }
    }

    printf("\nServiço adicionado ao carrinho!\n");
}


void desenho(){
	// Topo (Orelhas do Cão)
    printf("         .--.   .--.         \n");
    printf("        / /  \\ /  \\ \\        \n");
    
    // Rosto do Cão e Início do Letreiro
    printf("       | |    |    | |       \n");
    printf("       | |____|____| |       \n");
    printf("       |  .--. .--.  |       \n");
    printf("       | | () | () | |       \n"); 
    printf("       |  '--' '--'  |       \n");
    printf("        \\  .--.--.  /        \n"); // Nariz e Focinho
    printf("         '. \\__/ .'         \n");
    printf("           '----'           \n"); // Boca do cão

    // Letreiro da Loja (imediatamente abaixo do rosto do cão)
    printf("        /=================\\   \n");
    printf("       |  P E T   B O N S |   \n");
    printf("       |    A M I G O S   |   \n");
    
    // Toldo Listrado
    printf("       |\\/~\\/~\\/~\\/~\\/~\\/~\\/|   \n");
    printf("      /|/\\ /\\ /\\ /\\ /\\ /\\ /\\|\\  \n");
    
    // Corpo da Loja, Janelas e Porta
    printf("     |\\|_______________|/|  \n");
    printf("     | | [ * * ] | [ @ ] | [ * * ] | |  \n");
    printf("     | | |---| | | | | | | |---| | |  \n"); 
    printf("     | | |---| | | | | | | |---| | |  \n");
    printf("     | | |___| | | |___| | |___| | |  \n");
    printf("     |___________________________|  \n");
    
    // Base/Chão
    printf("~~~~~~=============================~~~~~~\n");

	
}
// funcao para cadastro //
struct Cadastro {
	
	char cpf_cliente[15];
	char nome_cliente[40];
	char tel_cliente[2][18];
	
	struct endereco{
        char rua[50];
        char numero[20];
        char cidade[30];
        
	}endereco;
	
	struct Carrinho carrinho;  // Carrinho do cliente
};


//  funcao para vilidar cpf //
int validarCPF(const char *cpf) {
    char numeros[12]; // só os números do CPF (11 dígitos + '\0')
    int i, soma, dig1, dig2, todos_iguais = 1, idx = 0;

    // Extrai apenas os dígitos numéricos do CPF
    for (i = 0; cpf[i] != '\0'; i++) {
        if (isdigit(cpf[i])) {
            numeros[idx++] = cpf[i];
        }
    }
    numeros[idx] = '\0';

    // Verifica se tem exatamente 11 dígitos
    if (strlen(numeros) != 11)
        return 0;

    // Verifica se todos os dígitos são iguais (ex: 11111111111)
    for (i = 1; i < 11; i++) {
        if (numeros[i] != numeros[0]) {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais)
        return 0;

    // Calcula o primeiro dígito verificador
    soma = 0;
    for (i = 0; i < 9; i++) {
        soma += (numeros[i] - '0') * (10 - i);
    }
    dig1 = (soma * 10) % 11;
    if (dig1 == 10) dig1 = 0;

    // Calcula o segundo dígito verificador
    soma = 0;
    for (i = 0; i < 10; i++) {
        soma += (numeros[i] - '0') * (11 - i);
    }
    dig2 = (soma * 10) % 11;
    if (dig2 == 10) dig2 = 0;

    // Verifica se os dígitos verificadores conferem
    if (dig1 == (numeros[9] - '0') && dig2 == (numeros[10] - '0'))
        return 1; // CPF válido
    else
        return 0; // CPF inválido
}

// funcao que grava cliente no txt //
void gravarClienteNoArquivo(struct Cadastro *c) {
    
    FILE *fp = fopen("clientes.txt", "a"); // Abre para adicionar (append)
    if (fp == NULL) {
        perror("Erro ao abrir arquivo para gravação");
        return;
    }

    // Não precisamos de cabeçalho tabular, mas usamos um separador
    fprintf(fp, "============================ CLIENTE ============================\n");
    
    // Grava cada dado em uma linha separada, usando um rótulo (chave: valor)
    fprintf(fp, "CPF: %s\n", c->cpf_cliente);
    fprintf(fp, "Nome: %s\n", c->nome_cliente);
    fprintf(fp, "Tel. Contato: %s\n", c->tel_cliente[0]);
    fprintf(fp, "Tel. Reserva: %s\n", c->tel_cliente[1]);
    fprintf(fp, "Endereço: %s, nº %s - %s\n", c->endereco.rua, c->endereco.numero, c->endereco.cidade);
    
    // Formato do valor:
  
    fprintf(fp, "\n========================== FIM CLIENTE ==========================\n\n"); // Separador
    
    fclose(fp);
}

// lista os clientes gravados no arquivo txt //
int listarClientes() {
    FILE *fp = fopen("clientes.txt", "r");
    if (fp == NULL) {
        printf("\n // Não Possui nenhum cliente registrado // \n");
        return 0;
    }

    int contador = 0;
    char linha[256];
    
    system("cls");
    printf("\n=================================================================\n");
    printf("|                    CLIENTES CADASTRADOS                       |\n");
    printf("=================================================================\n\n");

    while (fgets(linha, sizeof(linha), fp)) {
        printf("%s", linha);
        
        // Conta o número de registros encontrados baseando-se no separador
        if (strstr(linha, "===== FIM CLIENTE =====")) {
            contador++;
        }
    }

    fclose(fp);
    return contador;
}

// LIMPA O CARACTER DO CPF - EX: '.' '-'. PONTOS E IFEN, PARA NA HORA DE PESQUISAR O CPF, NAO TER DIVERGENCIA //
void limparCPF(const char *entrada, char *saida) { 
    while (*entrada) {
        if (isdigit(*entrada)) {
            *saida = *entrada;
            saida++;
        }
        entrada++;
    }
    *saida = '\0';
}

// buscar um cliente especifico pelo cpf e seleciona //
int buscarClientePorCPF(const char *cpfProcurado, struct Cadastro *cliente) {
    FILE *fp = fopen("clientes.txt", "r");
    if (!fp) {
        printf("\n // Não Possui nenhum registro // \n");
        return 0;
    }

    char linha[512];
    char cpfLimpoProcurado[20]; 
    limparCPF(cpfProcurado, cpfLimpoProcurado); // manda o cpf, caso tenha pontuações ele limpar, fica mais facil para ler no arquivo txt, evitando erros //

    int encontrado = 0;
    int contador = 0;

    system("cls");
    	
    while (fgets(linha, sizeof(linha), fp)) { // Lê uma linha de cada vez do arquivo fp até o final.//
        if (strncmp(linha, "CPF:", 4) == 0) { // verifica se a linha contem o cpf do cliente //
            char cpfArquivo[20];
            sscanf(linha + 5, "%19s", cpfArquivo); // Pula os primeiros 5 caracteres (C, P, F, :, e o espaço) //

            char cpfLimpoArquivo[20];
            limparCPF(cpfArquivo, cpfLimpoArquivo);

            if (strcmp(cpfLimpoProcurado, cpfLimpoArquivo) == 0) {
                encontrado = 1;
                contador++;
			    printf("\n=======================================================================================================\n");
			    printf("|                                        CLIENTE ENCONTRADO                                           |\n");
			    printf("=======================================================================================================\n");
							
                strcpy(cliente->cpf_cliente, cpfArquivo);
                cliente->carrinho.itens = NULL;
                cliente->carrinho.totalItens = 0;

                // Exibe cabeçalho do cliente
                printf("\n============================ CLIENTE ==============================\n");

                // Exibe e armazena todas as linhas do bloco do cliente
                printf("%s", linha); // imprime CPF

				while (fgets(linha, sizeof(linha), fp)) {
				    linha[strcspn(linha, "\n")] = 0; // remove \n final
				
					if (strncmp(linha, "Nome:", 5) == 0) {
					    strcpy(cliente->nome_cliente, linha + 6);
					    printf("Nome: %s\n", cliente->nome_cliente);
					} else if (strncmp(linha, "Tel. Contato:", 13) == 0) {
					    strcpy(cliente->tel_cliente[0], linha + 14);
					} else if (strncmp(linha, "Tel. Reserva:", 13) == 0) {
					    strcpy(cliente->tel_cliente[1], linha + 14);
					} else if (strncmp(linha, "Endereço:", 9) == 0) {
					    sscanf(linha + 10, "rua %49[^,], nº %19[^-] - %29[^\n]", 
					           cliente->endereco.rua, 
					           cliente->endereco.numero, 
					           cliente->endereco.cidade);
					} else if (strstr(linha, "FIM CLIENTE") != NULL) {
					    break; // fim do bloco
					} // fim do bloco // fim do bloco
                }

                printf("-------------------------------------------------------------------\n");
                break; // cliente encontrado
            }
        }
    }
    
        // Aqui só mostramos o cabeçalho após a busca que nao encontra cpf
    if (!encontrado) {
        printf("\n=======================================================================================================\n");
        printf("|                                        CLIENTE NÃO ENCONTRADO                                       |\n");
        printf("=======================================================================================================\n");
        printf("\nCliente com CPF %s não encontrado.\n", cpfProcurado);
    }

    fclose(fp);
    return encontrado;
}

// exclui o cliente com cpf selecionado //
void excluirClientePorCPF(const char *cpfProcurado) {
    FILE *fp = fopen("clientes.txt", "r");
    if (!fp) {
       	printf("\n // Não Possui nenhum registro // \n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Erro ao criar arquivo temporário");
        fclose(fp);
        return;
    }

    char linha[512];
    char cpfProcuradoLimpo[20];
    limparCPF(cpfProcurado, cpfProcuradoLimpo);

    int excluir = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        // Se a linha começa com "CPF:", verifica se é o CPF que queremos excluir
        if (strncmp(linha, "CPF:", 4) == 0) {
            char cpfArquivo[20];
            sscanf(linha + 5, "%19s", cpfArquivo); // pega o CPF após "CPF: "
            char cpfLimpoArquivo[20];
            limparCPF(cpfArquivo, cpfLimpoArquivo);

            if (strcmp(cpfLimpoArquivo, cpfProcuradoLimpo) == 0) {
                excluir = 1;
                // pula o bloco inteiro do cliente (4 linhas seguintes + FIM CLIENTE)
                for (int i = 0; i < 5; i++) {
                    if (!fgets(linha, sizeof(linha), fp)) break;
                }
                continue; // não escreve nada no arquivo temp
            }
        }
        // Escreve no arquivo temporário
        fputs(linha, temp);
    }

    fclose(fp);
    fclose(temp);

    if (excluir) {
        remove("clientes.txt");
        rename("temp.txt", "clientes.txt");
        system("cls");
        printf("\nCliente com CPF %s excluído com sucesso!\n", cpfProcurado);
    } else {
        remove("temp.txt");
        printf("\nCliente com CPF %s não encontrado.\n", cpfProcurado);
    }
}

// monstra os dados do cliente cadastrado //
void mostrarInfoCliente(struct Cadastro *cliente) {
    system("cls");
    printf("\n==================== INFORMAÇÕES DO CLIENTE ====================\n");
    printf("CPF: %s\n", cliente->cpf_cliente);
    printf("Nome: %s\n", cliente->nome_cliente);
    printf("Telefone 1: %s\n", cliente->tel_cliente[0]);
    printf("Telefone 2: %s\n", cliente->tel_cliente[1]);
    printf("Endereço: %s, Nº %s - %s\n", 
           cliente->endereco.rua, 
           cliente->endereco.numero, 
           cliente->endereco.cidade);
    printf("================================================================\n");

}

// atualiza dados do cliente caso ele queira alterar //
void atualizarClienteNoArquivo(struct Cadastro *cliente) {
    FILE *fp = fopen("clientes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        perror("Erro ao abrir arquivo");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    char linha[512];
    char cpfLimpoCliente[20];
    limparCPF(cliente->cpf_cliente, cpfLimpoCliente);

    int clienteAtualizado = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        // verifica se ainda não atualizou e se é o CPF que queremos atualizar
        if (!clienteAtualizado && strncmp(linha, "CPF:", 4) == 0) {
            char cpfArquivo[20];
            sscanf(linha + 5, "%19s", cpfArquivo);

            char cpfLimpoArquivo[20];
            limparCPF(cpfArquivo, cpfLimpoArquivo);

            if (strcmp(cpfLimpoArquivo, cpfLimpoCliente) == 0) {
                // escreve os dados atualizados no temp
                fprintf(temp, "CPF: %s\n", cliente->cpf_cliente);
                fprintf(temp, "Nome: %s\n", cliente->nome_cliente);
                fprintf(temp, "Tel. Contato: %s\n", cliente->tel_cliente[0]);
                fprintf(temp, "Tel. Reserva: %s\n", cliente->tel_cliente[1]);
                fprintf(temp, "Endereço: rua %s, nº %s - %s\n",
                        cliente->endereco.rua,
                        cliente->endereco.numero,
                        cliente->endereco.cidade);
                fprintf(temp, "========================== FIM CLIENTE ==========================\n");

                // pula todas as linhas antigas do cliente no arquivo original
                while (fgets(linha, sizeof(linha), fp)) {
                    if (strstr(linha, "FIM CLIENTE") != NULL) break;
                }

                clienteAtualizado = 1;
                continue; // não copiar linhas antigas
            }
        }

        // para todas as outras linhas, copia normalmente
        fputs(linha, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    system("cls");
    printf("\nCliente atualizado com sucesso!\n");
}


// ================== FUNÇÃO PARA COMPRAR RAÇÕES ==================
void comprarRacao(struct Carrinho *carrinho) {
	
	char buffer[50]; // declaração do buffer
    int escolha, quantidade;

    printf("\n========== RAÇÕES DISPONÍVEIS =========\n\n");
    for (int i = 0; i < totalRacoes; i++) {
        printf("%d. [R$ %.2f] - %s\n", i + 1, racoes[i].preco, racoes[i].nome);
    }
    printf ("5. [ESC] - VOLTAR");
    printf("\n----------------------------------------\n");
    printf("\n-> Selecione o Produto");
    escolha = obterOpcao();
    
    if (escolha == OPCAO_SAIR) {
    	system("cls");
        printf("\nNenhum serviço foi contratado.\n");
        return;
    }

    if (escolha < 1 || escolha > totalServicos && escolha != OPCAO_SAIR) {
    	system("cls");
        printf("\nOpção inválida!\n");
        return;
    }


    if (escolha < 1 || escolha > totalRacoes) {
        printf("\nOpção inválida!\n");
        return;
    }

    // ------- testa para nao ler um char para quantidade  ----------- //
     while (1) {
        printf("\n-> Quantidade desejada: ");
        scanf(" %49s", buffer); // lê a entrada como string

        // tenta converter para inteiro
        if (sscanf(buffer, "%d", &quantidade) == 1 && quantidade > 0) {
            break; // valor válido, sai do loop
        } else {
        	system("cls");
            printf("Inválido! Digite um número inteiro.\n");
        }
 	}
  // ------------------- fim teste  --------------------------------- //

    // Adiciona ao carrinho
    if (carrinho->itens == NULL) {
        carrinho->itens = (struct ItemCarrinho *) malloc(sizeof(struct ItemCarrinho));
        carrinho->totalItens = 0;
    } else {
        carrinho->itens = (struct ItemCarrinho *) realloc(carrinho->itens,
                        (carrinho->totalItens + 1) * sizeof(struct ItemCarrinho));
    }

    strcpy(carrinho->itens[carrinho->totalItens].nome, racoes[escolha-1].nome);
    carrinho->itens[carrinho->totalItens].preco = racoes[escolha-1].preco;
    carrinho->itens[carrinho->totalItens].quantidade = quantidade;
    carrinho->totalItens++;

   	system("cls");
    printf("\nProduto adicionado ao carrinho\n%s (Qtd: %d) - R$ %.2f cada | Subtotal: R$ %.2f\n",
    racoes[escolha-1].nome, quantidade, racoes[escolha-1].preco, racoes[escolha-1].preco * quantidade);
}
// ================== FUNÇÃO PARA COMPRAR BRINQUEDOS ==================
void comprarBrinquedo(struct Carrinho *carrinho) {
    int escolha, quantidade;
    char buffer[50];

    printf("\n========== BRINQUEDOS DISPONÍVEIS =========\n\n");
    for (int i = 0; i < totalBrinquedos; i++) {
        printf("%d. [R$ %.2f] - %s\n", i + 1, brinquedos[i].preco, brinquedos[i].nome);
    }
    printf("%d. [ESC] - VOLTAR\n", totalBrinquedos + 1);
    printf("\n----------------------------------------\n");
    printf("-> Selecione o Produto");
    escolha = obterOpcao();

    if (escolha == OPCAO_SAIR) {
        system("cls");
        printf("\nNenhum produto foi comprado.\n");
        return;
    }

    if (escolha < 1 || escolha > totalBrinquedos) {
        system("cls");
        printf("\nOpção inválida!\n");
        return;
    }

    // ------- testa para nao ler um char para quantidade  ----------- //
     while (1) {
        printf("\n-> Quantidade desejada: ");
        scanf(" %49s", buffer); // lê a entrada como string

        // tenta converter para inteiro
        if (sscanf(buffer, "%d", &quantidade) == 1 && quantidade > 0) {
            break; // valor válido, sai do loop
        } else {
        	system("cls");
            printf("Inválido! Digite um número inteiro.\n");
        }
 	}
  // ------------------- fim teste  --------------------------------- //

    if (carrinho->itens == NULL) {
        carrinho->itens = (struct ItemCarrinho *) malloc(sizeof(struct ItemCarrinho));
        carrinho->totalItens = 0;
    } else {
        carrinho->itens = (struct ItemCarrinho *) realloc(carrinho->itens,
            (carrinho->totalItens + 1) * sizeof(struct ItemCarrinho));
    }

    strcpy(carrinho->itens[carrinho->totalItens].nome, brinquedos[escolha - 1].nome);
    carrinho->itens[carrinho->totalItens].preco = brinquedos[escolha - 1].preco;
    carrinho->itens[carrinho->totalItens].quantidade = quantidade;
    carrinho->totalItens++;

	system ("cls");
    printf("\nProduto adicionado ao carrinho\n%s (Qtd: %d) - R$ %.2f cada | Subtotal: R$ %.2f\n",
        brinquedos[escolha - 1].nome, quantidade, brinquedos[escolha - 1].preco,
        brinquedos[escolha - 1].preco * quantidade);
}
// ================== FUNÇÃO PARA COMPRAR HIGIENE ==================
void comprarHigiene(struct Carrinho *carrinho) {
    int escolha, quantidade;
	char buffer[50];
    printf("\n========== HIGIENE DISPONÍVEL =========\n\n");
    for (int i = 0; i < totalHigiene; i++) {
        printf("%d. [R$ %.2f] - %s\n", i + 1, higiene[i].preco, higiene[i].nome);
    }
    printf("%d. [ESC] - VOLTAR\n", totalHigiene + 1);
    printf("\n----------------------------------------\n");
    printf("-> Selecione o Produto");
    escolha = obterOpcao();

    if (escolha == OPCAO_SAIR) {
        system("cls");
        printf("\nNenhum produto foi comprado.\n");
        return;
    }

    if (escolha < 1 || escolha > totalHigiene) {
        system("cls");
        printf("\nOpção inválida!\n");
        return;
    }
    // ------- testa para nao ler um char para quantidade  ----------- //
     while (1) {
        printf("\n-> Quantidade desejada: ");
        scanf(" %49s", buffer); // lê a entrada como string

        // tenta converter para inteiro
        if (sscanf(buffer, "%d", &quantidade) == 1 && quantidade > 0) {
            break; // valor válido, sai do loop
        } else {
        	system("cls");
            printf("Inválido! Digite um número inteiro.\n");
        }
 	}
  // ------------------- fim teste  --------------------------------- //
    if (carrinho->itens == NULL) {
        carrinho->itens = (struct ItemCarrinho *) malloc(sizeof(struct ItemCarrinho));
        carrinho->totalItens = 0;
    } else {
        carrinho->itens = (struct ItemCarrinho *) realloc(carrinho->itens,
            (carrinho->totalItens + 1) * sizeof(struct ItemCarrinho));
    }

    strcpy(carrinho->itens[carrinho->totalItens].nome, higiene[escolha - 1].nome);
    carrinho->itens[carrinho->totalItens].preco = higiene[escolha - 1].preco;
    carrinho->itens[carrinho->totalItens].quantidade = quantidade;
    carrinho->totalItens++;

	system ("cls");
    printf("\nProduto adicionado ao carrinho\n%s (Qtd: %d) - R$ %.2f cada | Subtotal: R$ %.2f\n",
        higiene[escolha - 1].nome, quantidade, higiene[escolha - 1].preco,
        higiene[escolha - 1].preco * quantidade);
}
// ================== FUNÇÃO PARA COMPRAR ACESSORIOS ==================
void comprarAcessorio(struct Carrinho *carrinho) {
    int escolha, quantidade;
	char buffer[50];
    printf("\n========== ACESSÓRIOS DISPONÍVEIS =========\n\n");
    for (int i = 0; i < totalAcessorios; i++) {
        printf("%d. [R$ %.2f] - %s\n", i + 1, acessorios[i].preco, acessorios[i].nome);
    }
    printf("%d. [ESC] - VOLTAR\n", totalAcessorios + 1);
    printf("\n----------------------------------------\n");
    printf("\n-> Selecione o Produto");
    escolha = obterOpcao();

    if (escolha == OPCAO_SAIR) {
        system("cls");
        printf("\nNenhum produto foi comprado.\n");
        return;
    }

    if (escolha < 1 || escolha > totalAcessorios) {
        system("cls");
        printf("\nOpção inválida!\n");
        return;
    }

    // ------- testa para nao ler um char para quantidade  ----------- //
     while (1) {
        printf("\n-> Quantidade desejada: ");
        scanf(" %49s", buffer); // lê a entrada como string

        // tenta converter para inteiro
        if (sscanf(buffer, "%d", &quantidade) == 1 && quantidade > 0) {
            break; // valor válido, sai do loop
        } else {
        	system("cls");
            printf("Inválido! Digite um número inteiro.\n");
        }
 	}
  	// ------------------- fim teste  --------------------------------- //

    if (carrinho->itens == NULL) {
        carrinho->itens = (struct ItemCarrinho *) malloc(sizeof(struct ItemCarrinho));
        carrinho->totalItens = 0;
    } else {
        carrinho->itens = (struct ItemCarrinho *) realloc(carrinho->itens,
            (carrinho->totalItens + 1) * sizeof(struct ItemCarrinho));
    }

    strcpy(carrinho->itens[carrinho->totalItens].nome, acessorios[escolha - 1].nome);
    carrinho->itens[carrinho->totalItens].preco = acessorios[escolha - 1].preco;
    carrinho->itens[carrinho->totalItens].quantidade = quantidade;
    carrinho->totalItens++;

	system ("cls");
    printf("\nProduto adicionado ao carrinho\n%s (Qtd: %d) - R$ %.2f cada | Subtotal: R$ %.2f\n",
        acessorios[escolha - 1].nome, quantidade, acessorios[escolha - 1].preco,
        acessorios[escolha - 1].preco * quantidade);
}
// ================== FUNÇÃO PARA REMOVER ITENS DO CARRINHO ==================
void removerItemCarrinho(struct Carrinho *carrinho) {
    if (carrinho->totalItens == 0) {
        printf("\nO carrinho está vazio.\n");
        getch();
        return;
    }

    int opcaoRemover;
    do {
        system("cls");
        printf("\n====================== REMOVER ITEM ======================\n");
        printf("%-3s %-30s %-12s %-8s %-10s\n", "No", "Produto/Serviço", "Preço Unit.", "Qtd", "Subtotal");
        printf("---------------------------------------------------------\n");
        for (int i = 0; i < carrinho->totalItens; i++) {
            struct ItemCarrinho item = carrinho->itens[i];
            float subtotal = item.preco * item.quantidade;
            printf("%-3d %-30s R$ %-10.2f %-8d R$ %-10.2f\n",
                   i + 1, item.nome, item.preco, item.quantidade, subtotal);
        }
        printf("---------------------------------------------------------\n");
        printf("\n[ESC] Cancelar\n");
        printf("-> Selecione o número do item que deseja remover: ");
        opcaoRemover = obterOpcao();

        if (opcaoRemover == OPCAO_SAIR) {
            break; // cancela a remoção
        } else if (opcaoRemover < 1 || opcaoRemover > carrinho->totalItens && opcaoRemover != OPCAO_SAIR) {
            printf("\nOpção inválida!\n");
            printf ("Tente Novamente: ");
            getch();
        } else {
            // desloca os itens seguintes para "apagar" o selecionado
            for (int i = opcaoRemover - 1; i < carrinho->totalItens - 1; i++) {
                carrinho->itens[i] = carrinho->itens[i + 1];
            }
            carrinho->totalItens--;

            // reduz dinamicamente o tamanho do vetor
            if (carrinho->totalItens > 0) {
                carrinho->itens = (struct ItemCarrinho *) realloc(carrinho->itens,
                                    carrinho->totalItens * sizeof(struct ItemCarrinho));
            } else {
                free(carrinho->itens);
                carrinho->itens = NULL;
            }

			system ("cls");
            printf("\nItem removido com sucesso!\n");
            break; // sai do loop após remover
        }

    } while (1);
}

void realizarPagamento(struct Cadastro *cliente) {
    struct Carrinho *carrinho = &cliente->carrinho;

    if (carrinho->totalItens == 0) {
        printf("\nO carrinho está vazio. Não há itens para pagamento.\n");
        getch();
        return;
    }

    float totalGeral = 0;
    system("cls");
    printf("\n============================ EXTRATO DE COMPRA ===============================\n");
    printf("%-3s %-30s %-12s %-8s %-10s\n", "No", "Produto/Serviço", "Preço Unit.", "Qtd", "Subtotal");
    printf("------------------------------------------------------------------------------\n");

    for (int i = 0; i < carrinho->totalItens; i++) {
        struct ItemCarrinho item = carrinho->itens[i];
        float subtotal = item.preco * item.quantidade;
        totalGeral += subtotal;
        printf("%-3d %-30s R$ %-10.2f %-8d R$ %-10.2f\n",
               i + 1, item.nome, item.preco, item.quantidade, subtotal);
    }

    printf("------------------------------------------------------------------------------\n");
    printf("[TOTAL GERAL: R$ %.2f]\n", totalGeral);
    printf("------------------------------------------------------------------------------\n");

    int opcaoPagamento;
    do {
        printf("\nSelecione a forma de pagamento:\n\n");
        printf("[1] Débito\n");
        printf("[2] Crédito\n");
        printf("[3] Dinheiro\n");
        printf("[ESC] Voltar\n");
        printf("----------------------------------------\n");
        printf("-> Selecione sua forma de pagamento: ");
        opcaoPagamento = obterOpcao();

        if (opcaoPagamento == OPCAO_SAIR) {
            system("cls");
            printf("\nVoltando ao menu do carrinho...\n");
            getch();
            return;
        }

        switch (opcaoPagamento) {
            case 1:
                system("cls");
                printf("\nPagamento no DÉBITO confirmado!\n");
                printf("Total pago: R$ %.2f\n", totalGeral);
                break;
            case 2:
                system("cls");
                printf("\nPagamento no CRÉDITO confirmado!\n");
                printf("Total pago: R$ %.2f\n", totalGeral);
                break;
            case 3:
                system("cls");
                printf("\nPagamento em DINHEIRO confirmado!\n");
                printf("Total pago: R$ %.2f\n", totalGeral);
                break;
        }

        // Gera data e hora
        time_t t;
        struct tm *tm_info;
        char dataHora[40];
        time(&t);
        tm_info = localtime(&t);
        strftime(dataHora, 40, "%d/%m/%Y %H:%M:%S", tm_info);

        // Cria pasta de extratos
        const char *pasta = "extratos";
        #ifdef _WIN32
            _mkdir(pasta);
        #else
            mkdir(pasta, 0777);
        #endif

        // CPF limpo e nome do arquivo
        char cpfLimpo[20];
        limparCPF(cliente->cpf_cliente, cpfLimpo);

        char nomeArquivo[100];
        sprintf(nomeArquivo, "%s/extrato_%s.txt", pasta, cpfLimpo);

        // Grava extrato (modo append)
        FILE *fp = fopen(nomeArquivo, "a");
        if (fp) {
            fprintf(fp, "\n============================ EXTRATO DE COMPRA ===============================\n");
            fprintf(fp, "Cliente: %s\n", cliente->nome_cliente);
            fprintf(fp, "CPF: %s\n", cliente->cpf_cliente);
            fprintf(fp, "Data/Hora: %s\n", dataHora);
            fprintf(fp, "------------------------------------------------------------------------------\n");
            fprintf(fp, "%-3s %-30s %-12s %-8s %-10s\n", "No", "Produto/Serviço", "Preço Unit.", "Qtd", "Subtotal");
            fprintf(fp, "------------------------------------------------------------------------------\n");

            for (int i = 0; i < carrinho->totalItens; i++) {
                struct ItemCarrinho item = carrinho->itens[i];
                fprintf(fp, "%-3d %-30s R$ %-10.2f %-8d R$ %-10.2f\n",
                        i + 1, item.nome, item.preco, item.quantidade, item.preco * item.quantidade);
            }

            fprintf(fp, "------------------------------------------------------------------------------\n");
            fprintf(fp, "TOTAL GERAL: R$ %.2f\n", totalGeral);
            fprintf(fp, "Forma de pagamento: ");
            if (opcaoPagamento == 1) fprintf(fp, "Débito\n");
            else if (opcaoPagamento == 2) fprintf(fp, "Crédito\n");
            else if (opcaoPagamento == 3) fprintf(fp, "Dinheiro\n");
            fprintf(fp, "==============================================================================\n\n");
            fclose(fp);

            printf("\nExtrato salvo em: %s\n", nomeArquivo);
        } else {
            printf("\nErro ao gerar o arquivo de extrato!\n");
        }

        // Limpa carrinho
        free(carrinho->itens);
        carrinho->itens = NULL;
        carrinho->totalItens = 0;

        printf("\nCompra finalizada com sucesso!\n");
        printf("Carrinho esvaziado.\n");
        getch();
        return;

    } while (1);
}

void exibirExtratoCliente(struct Cadastro *cliente) {
    system("cls");

    char cpfLimpo[20];
    limparCPF(cliente->cpf_cliente, cpfLimpo);

    char nomeArquivo[100];
    sprintf(nomeArquivo, "extratos/extrato_%s.txt", cpfLimpo);

    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("\nNenhuma compra registrada para este cliente.\n");
        printf("\nPressione qualquer tecla para voltar...\n");
        getch();
        system("cls");
        return;
    } else {
        printf("\n=========================== HISTÓRICO DE COMPRAS =============================\n\n");
        char linha[256];

        while (fgets(linha, sizeof(linha), fp)) {
            // Remove o \n final da linha lida para não duplicar
            if (linha[strlen(linha) - 1] == '\n') {
                linha[strlen(linha) - 1] = '\0';
            }

            printf("%s\n", linha);
        }

        fclose(fp);
        printf("\n==============================================================================\n");
        printf("\n// Pressione qualquer tecla para voltar... //");
        getch();
        system("cls");
    }
}

int main(){
	
	setlocale (LC_ALL, "Portuguese");
	
	struct Cadastro *cliente =  NULL;
	
	int total_cliente = 0;
	int opcao, opcao2, opcao3, subop, j;
	char cpf[15];
	int total;
	int cliente_encontrado;
	int opcaoCarrinho;


	/* ------------------------------------------------------------------------------------------ */
		
	desenho();
	
	do{
		printf ("\n------------ MENU PRINCIPAL ------------\n");
		
		printf ("\n[1] = CADASTRAR NOVO CLIENTE\n");
		printf ("[2] = LISTAR CLIENTES\n");
		printf ("[3] = SELECIONAR CLIENTE POR CPF\n");
		printf ("[ESC] = Sair\n");
		printf ("\n----------------------------------------\n");
		printf ("\nSelicione a opção: ");
		opcao = obterOpcao();

		
		if (opcao < 1 || opcao > 4){
			system ("cls");
			printf ("\nOpcao inválida, Tente Novamente !\n");
		}
		
		switch (opcao){
			case 1:
				system("cls");
				printf ("------------------------------");
				printf ("\nInforme o CPF: ");
				scanf ("%s", cpf);
		
				if (validarCPF(cpf)) { /* chama função validar CPF */
					system ("cls");
	    	   		printf("\nCPF válido!\n");
	    	   		
		    		struct Cadastro *temp = realloc(cliente, (total_cliente + 1) * sizeof(struct Cadastro)); /* AUMENTA O TAMANHO DA STRUCT PARA +1 CADA VEZ Q SELECIONA CASE 1, ''CADASTRAR CLIENTE'', USANDO VARIAVEL TEMPORARIA TEMP PARA N PERDER REGISTROS */
		    	   		if (temp == NULL){
		    	   			printf ("Erro ao alocar memória!\n");
		    	   			free(cliente);
		    	   			return 1;
						}
						   
					cliente = temp;
		    	   		
		    	   	strcpy(cliente[total_cliente].cpf_cliente, cpf); /* COPIA O CPF DIGITADO DPS DE VALIDADO E PASSA PARA O CPF DA STRUCT CLIENTE */
		    	   		
		    	   	printf ("\n***************************\n");
		    	   	printf ("-> Nome do Cliente: ");
		    	   	scanf(" %39[^\n]", cliente[total_cliente].nome_cliente);
		    	   		
		
		    	 	printf ("-> Informe número de telefone: ");
		    	   	scanf (" %17[^\n]", cliente[total_cliente].tel_cliente[0]);
		    
		    	   	printf ("-> Informe número reserva: ");
		    	   	scanf (" %17[^\n]", cliente[total_cliente].tel_cliente[1]); 
		    	   	
		    	   	printf ("\n// Informe o Endereço //\n");
		    	   	printf ("-> Nome da rua: ");
		    	   	scanf (" %49[^\n]", cliente[total_cliente].endereco.rua);
		    	   	
		    	   	printf ("-> Numero da residencia: ");
		    	   	scanf (" %19[^\n]", cliente[total_cliente].endereco.numero);
		    	   	getchar();
		    	   	
		    	   	printf ("-> Cidade: ");
		    	   	scanf (" %29[^\n]", cliente[total_cliente].endereco.cidade);
		    	   	
		    	   	
					printf ("\n***************************\n");
   		
		    						    	   	
		    	   	gravarClienteNoArquivo(&cliente[total_cliente]);
						
					system ("cls");
		    	   	printf("\nCliente cadastrado e gravado automaticamente!\n");
		    	   	total_cliente++;
		    	  	
		    	}
				else {
					system ("cls");
		        	printf("CPF inválido!\n");
		    	}
		    break;
	    		
	    	case 2:
	    		system("cls");
		       	total = listarClientes();
	       		printf ("\nTotal de Clientes: [%d]", total);
	        	printf("\n*************************************************\n\n");
	        	
			    do{
					printf ("\n // Precione [ESC] para voltar ao MENU PRINCIPAL //");
					opcao3 = obterOpcao();
	
				
					if (opcao3 != OPCAO_SAIR){
						system ("cls");
						printf ("\nOpcao inválida, Tente Novamente !\n");
					}
							
					}while (opcao3 != OPCAO_SAIR);
	        		system("cls");
	        break;
	        
	        case 3:
	    		system("cls");
			    char cpf[15];
			    printf("-> Qual o CPF do Cliente que deseja selecionar?\n");
			    printf("-> CPF: ");
			    scanf("%s", cpf);
    			struct Cadastro clienteAtual;

			    if (!buscarClientePorCPF(cpf, &clienteAtual)) { // &clienteAtual passa o endereço da variável para a função, permitindo que ela preencha os dados do cliente se encontrar. //
			        break;
			    }

			    // Cliente encontrado -> entra direto no submenu
			    printf("\n                     // CLIENTE SELECIONADO //                    \n");
			    do {
			        printf("\n------------------------- MENU DO CLIENTE -------------------------\n\n");
			        printf("[1] = CONTRATAR SERVIÇO\n");
			        printf("[2] = COMPRAR RAÇÕES\n");
			        printf("[3] = COMPRAR BRINQUEDOS\n");
			        printf("[4] = COMPRAR PRODUTO HIGIENICO\n");
			        printf("[5] = COMPRAR ACESSORIOS\n");
			        printf("[6] = VER CARRINHO\n");
			        printf("[7] = INFORMAÇÕES DO CLIENTE\n");
			        printf("[ESC] = VOLTAR\n");
			        printf("\n-------------------------------------------------------------------\n");
			        printf("\n-> Selecione a opção: ");
			        opcao2 = obterOpcao();
	
			        if ((opcao2 < 1 || opcao2 > 7) && opcao2 != OPCAO_SAIR) {
			            system("cls");
			            printf("\nOpção inválida, tente novamente!\n");
			            continue;
			        }

			        switch (opcao2) {
			            case 1:
			                system("cls");
			                contratarServico(&clienteAtual.carrinho, servicos, totalServicos);
			                break;
			            case 2:
			               system("cls");
						    comprarRacao(&clienteAtual.carrinho);
						    break;
			            case 3:
			                system("cls");
			                comprarBrinquedo(&clienteAtual.carrinho);
			                break;
			            case 4:
			                system("cls");
			                comprarHigiene(&clienteAtual.carrinho);
			                break;
			            case 5:
			                system("cls");
			                comprarAcessorio(&clienteAtual.carrinho);
			                break;
			            case 6:
							if (clienteAtual.carrinho.totalItens == 0) {
							        system("cls");
							        printf("\nO carrinho está vazio.\n");
							        printf("\nPressione qualquer tecla para voltar...\n");
							        getch();
							        break;
							}
							system("cls");
							do {
							        float totalCarrinho = 0;
							        printf("\n============================= CARRINHO =============================\n");
							        printf("%-3s %-30s %-12s %-8s %-10s\n", "No", "Produto/Serviço", "Preço Unit.", "Qtd", "Subtotal");
							        printf("--------------------------------------------------------------------\n");
							        for (int i = 0; i < clienteAtual.carrinho.totalItens; i++) {
							            struct ItemCarrinho item = clienteAtual.carrinho.itens[i];
							            float subtotal = item.preco * item.quantidade;
							            totalCarrinho += subtotal;
							            printf("%-3d %-30s R$ %-10.2f %-8d R$ %-10.2f\n",
							                   i + 1, item.nome, item.preco, item.quantidade, subtotal);
							        }
							        printf("--------------------------------------------------------------------\n");
							        printf("[TOTAL GERAL: R$ %.2f]\n", totalCarrinho);
							        printf("\n------------------------ OPÇÕES DO CARRINHO ------------------------\n");
							        printf("[1] Ir para o pagamento\n");
							        printf("[2] Remover item\n");
							        printf("[ESC] Voltar\n");
							        printf("--------------------------------------------------------------------\n");
							        printf("\n-> Selecione a opção: ");
							        opcaoCarrinho = obterOpcao();
							
									if ((opcaoCarrinho < 1 || opcaoCarrinho > 2) && opcaoCarrinho != OPCAO_SAIR) {
							            system("cls");
							            printf("\nOpção inválida, tente novamente!\n");
							        }
							
							        switch(opcaoCarrinho) {
							            case 1:
							                system("cls");
							                printf("\nRedirecionando para pagamento...\n");
											realizarPagamento(&clienteAtual);
							                break;
							            case 2:
							                removerItemCarrinho(&clienteAtual.carrinho);
							                break;
							            case OPCAO_SAIR:
							                system("cls");
							                break;
							        }
							system("cls");
							} while(opcaoCarrinho != OPCAO_SAIR);
							system("cls");
							break;
					    case 7:
					    	mostrarInfoCliente(&clienteAtual);
					    	do {
							    printf("\n============= ALTERAR DADOS DO CLIENTE ============\n\n");
							    printf("[1] Alterar telefone principal\n");
							    printf("[2] Alterar telefone de reserva\n");
							    printf("[3] Alterar endereço\n");
							    printf("[4] Mostrar Compras ja feitas\n");
							    printf("[ESC] Voltar\n");
							    printf("-----------------------------------------------------\n");
							    printf("-> Selecione: ");
							    subop = obterOpcao();
							    
							    if ((subop < 1 || subop > 4) && subop != OPCAO_SAIR) {
			         				system("cls");
			            			printf("\nOpção inválida, tente novamente!\n");
			            			continue;
			       				}
								printf ("\n");
							    switch(subop) {
							        case 1:
							            printf("\nNovo número para contato: ");
							            scanf(" %17[^\n]", clienteAtual.tel_cliente[0]);
							            atualizarClienteNoArquivo(&clienteAtual);
							            break;
							        case 2:
							            printf("\nNovo número para contato reserva: ");
							            scanf(" %17[^\n]", clienteAtual.tel_cliente[1]);
							            atualizarClienteNoArquivo(&clienteAtual);
							            break;
							        case 3:
							            printf("Nome da rua atualizada: ");
							            scanf(" %49[^\n]", clienteAtual.endereco.rua);
							            printf("Numero de residencia atualizada: ");
							            scanf(" %19[^\n]", clienteAtual.endereco.numero);
							            printf("Cidade atualizada: ");
							            scanf(" %29[^\n]", clienteAtual.endereco.cidade);
							            atualizarClienteNoArquivo(&clienteAtual);
							            break;
							        case 4:
							        	system("cls");
   										exibirExtratoCliente(&clienteAtual);
   										break;
							        case OPCAO_SAIR:
							            break;
							    }
							} while(subop != OPCAO_SAIR);
					    	
			            	case OPCAO_SAIR:
			                system("cls");
			                break;
			        }
			
			    } while (opcao2 != OPCAO_SAIR);
	
			}
		
	} while (opcao != OPCAO_SAIR);
		system ("cls");
		printf ("Finalizando Programa....");
	
	return 0;
}