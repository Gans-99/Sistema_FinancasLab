
/*
                                TRABALHO DE LABORATÓRIO DE PROGRAMAÇÃO
      INTEGRANTES: Alexsandro Martins, Ciro Coimbra, Jeiel Lucas, Mahatma Gandhi e Rogério Pio
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

#define SIZE 50
#define tam 1000

void criarArquivoGastos(char usuario[SIZE]){
  
  char nameArquivo[SIZE] = "../Arquivos/gastos";
  
  strcat(nameArquivo, usuario);
  strcat(nameArquivo, ".txt");

  FILE* file = fopen(nameArquivo, "a");
  
  fprintf(file, "[0]\n");
  fclose(file);
  
}

int logar(char usuario[SIZE], char senha[SIZE]){
  
  FILE* file = fopen("../Arquivos/dados.txt", "r");
  char* arq_usuario;
  char* arq_senha;
  char linha[SIZE];
  bool achou = false;

  while (!achou){
    
    if (fgets(linha, sizeof(linha), file) != NULL){
      arq_usuario = strtok(linha, " - ");
      arq_senha = strtok(NULL, " - ");
      arq_senha = strtok(arq_senha, "\n");
      
      int resultado = strcmp(usuario, arq_usuario);
      int resultado_senha = strcmp(senha, arq_senha);
      
      if (resultado == 0 && resultado_senha == 0){
        fclose(file);
        
        return 1;
      }
      
    }else{
      fclose(file);
      
      return 0;
    }
  }
}

int cadastrar(char usuario[SIZE], char senha[SIZE]){
  
  FILE* file = fopen("../Arquivos/dados.txt", "r");
  char* arq_usuario;
  char linha[SIZE];
  int resultado = 1;
  
  while (fgets(linha, sizeof(linha), file) != NULL){
    
    arq_usuario = strtok(linha, " - ");
    resultado = strcmp(usuario, arq_usuario);
    
    if (resultado == 0){
      fclose(file);
      
      return 0;
    }
  }
  fclose(file);
  
  if (resultado != 0){
    
    FILE* file = fopen("../Arquivos/dados.txt", "a");
    
    fprintf(file, "%s - %s\n", usuario, senha);
    fclose(file);
    criarArquivoGastos(usuario);
    
    return 1;
  }
}

jmp_buf buffer;

int validar_valor(const char *str){
   float result;
    if (setjmp(buffer) == 0) {
        result = atof(str); // Conversão para float
        return result;
    } else {
        // Tratamento de erro
        printf("Erro: valor invalido!.\n");
        return 0.0;
    }
}

int validar_usuario(const char* string){
  
    while (*string){
      
        if (!isalpha(*string)){
            return 1; 
        }
        string++;
      
    }

    return 0; 
}

int menu(){
  
  int escolha;
  
  printf("\n======MENU======\n");
  printf("1- Login\n2- Cadastrar\n3- Sair\n");
  printf("Digite a opcao: ");
  scanf("%i", &escolha);
  
  return escolha;
}

int limparTerminal(){
  
  int sistema;
  #if linux
  
  sistema = 1;
  #elif __WIN32
  
  sistema = 2;
  #elif APPLE
  
  sistema = 3;
  #endif
  
  if (sistema == 1){
    system("clear");
    
  }else if (sistema == 2){
    system("cls");
    
  }else{
    system("clear");
    
  }
}

int error(int erro){
  
  int opcao;
  
  if (erro == 1){
    
    limparTerminal();
    printf("\nUsuario e/ou senha incorretos\n");
    printf("(1)Tente novamente\n(0)Voltar ao menu\nDigite a opcao: ");
    scanf("%i", &opcao);
    
  }else if (erro == 2){
    
    limparTerminal();
    printf("\nUsuario ja cadastrado\n");
    printf("(1)Tente novamente\n(0)Voltar ao menu\nDigite a opcao: ");
    scanf("%i", &opcao);
    
  }
  
  return opcao;
}

void gerarRelatorio(char usuario[SIZE], int opcao){

  char linha[tam];
  char arq[SIZE] = "../Arquivos/gastos";
  int linhaAtual = 0;
  
  strcat(arq, usuario);
  strcat(arq, ".txt");
  
  FILE* file = fopen(arq, "r");

  while (fgets(linha, sizeof(linha), file) != NULL){
    
    if (opcao == 0 && linhaAtual == 0){
      
      char* saldo = linha;
      strtok(saldo, "]\n");
      saldo = strtok(saldo, "[");
      printf("Seu saldo: R$%s\n", saldo);
      linhaAtual++;
      
    }else{
      
      if (linhaAtual == 0){
        linhaAtual++;
        
      }else{

        char* mensagem = strtok(linha, "{}");
        char* token;
        char* vetor[5];
        char delimitador[] = " | ";
        int cont = 0;
        
        token = strtok(mensagem, delimitador);
        
        while (token != NULL){
          
          vetor[cont] = token;
          token = strtok(NULL, delimitador);
          cont++;
          
        }
        printf("ID: %s Nome: %s | Data: %s | R$%s | %s\n", vetor[0], vetor[1], vetor[2], vetor[3], vetor[4]);
        
      }
    }
  }
  fclose(file);
  
}

void atualizarSaldo(char operacao[SIZE], char arquivo[SIZE], float valor){
  
  FILE* file = fopen(arquivo, "r");
  FILE* fileTemp = fopen("../Arquivos/gastosTemp.txt", "a");
  char op[SIZE] = "+";
  char linha[SIZE];
  int cont = 1;

    while (fgets(linha, sizeof(linha), file) != NULL){
      
        if (cont == 1){
          
          char* token = strtok(linha, "[ ]");
          float saldo = atof(token);
          
          if (strcmp(operacao, op) == 0){
            
            saldo += valor;
            fprintf(fileTemp, "[%.2f]\n", saldo);
            cont++;
            
          }else{
            
            saldo -= valor;
            fprintf(fileTemp, "[%.2f]\n", saldo);
            cont++;
            
          }
          
        }else{
          fprintf(fileTemp, "%s", linha);
          
        }
    }
  
    fclose(fileTemp);
    fclose(file);
    remove(arquivo);
    rename("../Arquivos/gastosTemp.txt", arquivo);
  
}

void atualizarDespesa(char usuario[SIZE]){
  
  gerarRelatorio(usuario, 0);

  int cont = 1;
  float valorAntigo;
  char linha[SIZE];
  char despesa[SIZE];
  char sinal[SIZE];
  
  printf("Qual o indice da despesa para atualizar? ");
  scanf("%s", despesa);

  char arquivo[SIZE] = "../Arquivos/gastos";
  
  strcat(arquivo, usuario);
  strcat(arquivo, ".txt");

  FILE* file = fopen(arquivo, "r");
  FILE* fileTemp = fopen("../Arquivos/gastosTemp.txt", "a");
  char nome[SIZE];
  char data[SIZE];
  float valor;
  
  printf("Digite o novo nome: ");
  scanf("%s", nome);
  printf("Digite a nova data DD/MM/AAAA: ");
  scanf("%s", data);
  printf("Digite o novo valor: ");
  scanf("%f", &valor);

  while (fgets(linha, sizeof(linha), file) != NULL){
    
    if (cont == 1){
      
      fprintf(fileTemp, "%s", linha);
      cont++;
      
    }else{
      
      char linhaCopia[SIZE];
      strcpy(linhaCopia, linha);
      char* linhaAtual = strtok(linhaCopia, "| {");
      
      if (strcmp(despesa, linhaAtual) == 0){

        char* mensagem = strtok(linha, "{}");
        char* token;
        char* vetor[5];
        char delimitador[] = " | ";
        int contador = 0;
        
        token = strtok(mensagem, delimitador);
        
        while (token != NULL){
          
          vetor[contador] = token;
          token = strtok(NULL, delimitador);
          contador++;
          
        }
        valorAntigo = atof(vetor[3]);
        
        strcpy(sinal, vetor[4]);
        fprintf(fileTemp, "{%s | %s | %s | %.2f | %s}\n", vetor[0], nome, data, valor, vetor[4]);
        
      }else{
        fprintf(fileTemp, "%s", linha);
        
      }
    }
  }

  fclose(file);
  fclose(fileTemp);
  remove(arquivo);
  rename("../Arquivos/gastosTemp.txt", arquivo);

  float calculo;
  
  if (strcmp(sinal, "+") == 0){
    
    if (valor > valorAntigo){
      
      calculo = valor - valorAntigo;
      atualizarSaldo("+", arquivo, calculo);
      
    }else if (valor < valorAntigo){
      
      calculo = valorAntigo - valor;
      atualizarSaldo("-", arquivo, calculo);
      
    }
    
  }else{
    
    if (valor > valorAntigo){
      
      calculo = valor - valorAntigo;
      atualizarSaldo("-", arquivo, calculo);
      
    }else if (valor < valorAntigo){
      
      calculo = valorAntigo - valor;
      atualizarSaldo("+", arquivo, calculo);
      
    }
  }
}

void addValue(char usuario[]){

  char name[SIZE];
  char linha[SIZE];
  char data[SIZE];
  int tipoDeValor;
  int indice = 0;
  char valor_string[50];
  double valor;
  
  printf("====REGISTRAR Receita/Despesa====\n");
  printf("(1)Receita\n(2)Despesa\n");
  scanf("%i", &tipoDeValor);
  printf("Nome da Receita ou Despesa: ");
  scanf("%s", name);
  printf("Data DD/MM/AAAA: ");
  scanf("%s", data);
  printf("Valor: ");
  scanf("%s", valor_string);

  while (!validar_valor(valor_string)){
    printf("Digite um valor valido!\n");
    printf("Valor: ");
    scanf("%s",valor_string);
  }

  valor = atof(valor_string);

  char gastosUsuario[SIZE] = "../Arquivos/gastos";
  
  strcat(gastosUsuario, usuario);
  strcat(gastosUsuario, ".txt");
  
  FILE* file = fopen(gastosUsuario, "r");
  while (fgets(linha, sizeof(linha), file) != NULL){
    indice++;
  }
  
  fclose(file);
  FILE* file2 = fopen(gastosUsuario, "a");

  if (tipoDeValor == 1){
    
    fprintf(file2, "{%d | %s | %s | %.2f | +}\n", indice, name, data, valor);
    fclose(file2);
    atualizarSaldo("+", gastosUsuario, valor);
    
  } else if (tipoDeValor == 2){
    
    fprintf(file2, "{%d | %s | %s | %.2f | -}\n", indice, name, data, valor);
    fclose(file2);
    atualizarSaldo("-", gastosUsuario, valor);
    
  }
}

void removerGasto(char usuario[SIZE]){

  char gasto[SIZE];
  char linha[SIZE];
  char operacao[SIZE];
  int removido = 0;
  
  gerarRelatorio(usuario, 1);
  printf("Qual o indice do gasto que gostaria de remover? ");  
  scanf("%s", gasto);

  char arquivo[SIZE] = "../Arquivos/gastos";
  
  strcat(arquivo, usuario);
  strcat(arquivo, ".txt");

  FILE* file = fopen(arquivo, "r");
  FILE* fileTemp = fopen("../Arquivos/gastosTemp.txt", "a");
  char* vetor[5];
  float valorRemovido;

  while (fgets(linha, sizeof(linha), file) != NULL){
    
    char* linhaCopia[SIZE];
    strcpy(linhaCopia, linha);

    char* mensagem = strtok(linhaCopia, "{}");
    char* token;
    char delimitador[] = " | ";
    int cont = 0;
    
    token = strtok(mensagem, delimitador);
    
    while (token != NULL){
      
      vetor[cont] = token;
      token = strtok(NULL, delimitador);
      cont++;
      
    }
    
    if (strcmp(gasto, vetor[0]) != 0){
      
      if (removido == 0){
        fprintf(fileTemp, "%s", linha);
        
      }else{
        
        int indiceAtualizado = atoi(vetor[0]);
        indiceAtualizado--;
        fprintf(fileTemp, "{%d | %s | %s | %s | %s}\n", indiceAtualizado, vetor[1], vetor[2], vetor[3], vetor[4]);
        
      }
      
    }else{
      
      valorRemovido = atof(vetor[3]);
      strcpy(operacao, vetor[4]);
      removido = 1;
      
    }
  }

  fclose(file);
  fclose(fileTemp);
  remove(arquivo);
  rename("../Arquivos/gastosTemp.txt", arquivo);

  if (strcmp(operacao, "+")==0){
    atualizarSaldo("-", arquivo, valorRemovido);
    
  }else{
    atualizarSaldo("+", arquivo, valorRemovido);
    
  }
}

void controleOrcamento(char usuario[SIZE]){

  char linha[tam];
  char arq[SIZE] = "../Arquivos/gastos";
  int linhaAtual = 0;
  float despesas = 0;
  float receitas = 0;
  
  strcat(arq, usuario);
  strcat(arq, ".txt");

  FILE* file = fopen(arq, "r");

  while (fgets(linha, sizeof(linha), file) != NULL){  
    
    char sinal[SIZE];
    
    if (linhaAtual == 0){
      
      char* saldo = linha;
      strtok(saldo, "]\n");
      saldo = strtok(saldo, "[");
      printf("Seu saldo: R$%s\n", saldo);
      linhaAtual++;
      
    }else{

      char* mensagem = strtok(linha, "{}");
      char* token;
      char* vetor[5];
      char delimitador[] = " | ";
      int cont = 0;
      
      token = strtok(mensagem, delimitador);
      
      while (token != NULL){
        
        vetor[cont] = token;
        token = strtok(NULL, delimitador);
        cont++;
        
      }
      
      strcpy(sinal, vetor[4]);
      float valor = atof(vetor[3]);
      
      if (strcmp(sinal,"+")){
        despesas += valor;
        
      }else{
        receitas += valor;
        
      }
    }
  }
  
  fclose(file);
  printf("Receitas: %.2f || Despesas: %.2f\n", receitas, despesas);
  
  if (receitas > despesas){
    printf("Parabens %s pela sua disciplina financeira!\nEconomizar e uma habilidade valiosa que traz seguranca e oportunidades para o futuro.\nContinue assim!", usuario);
    
  }else{
    printf("%s cuidado com os gastos excessivos!\nReavalie seus habitos financeiros e busque equilibrio entre o que ganha e gasta\npara evitar dividas e garantir sua estabilidade.", usuario);
    
  }
}

int telaInicial(char usuario[SIZE]){
  
  int opcao;
  
  printf("\n\n====MINHAS FINANCAS====\n");
  printf("Bem vinde, %s\n", usuario);
  printf("(1)Registrar receita/despesa\n");
  printf("(2)Controle de orcamento\n");
  printf("(3)Gerar relatorio\n");
  printf("(4)Atualizar\n");
  printf("(5)Remover renda\n");
  printf("(0)Deslogar\n");
  printf("\nDigite a opcao: ");
  scanf("%i", &opcao);
  
  if (opcao == 0){
    
    limparTerminal();
    int escolha = menu();
    
    if (escolha == 3){
      exit(0);
      
    }else if (escolha == 1){
      return 1;
    }else if (escolha == 2){
      return 2;
    }
    
  }else if (opcao == 1){
    
    addValue(usuario);
    limparTerminal();
    
  }else if (opcao == 2){
    
    limparTerminal();
    controleOrcamento(usuario);
    
  }else if (opcao == 3){
    
    limparTerminal();
    gerarRelatorio(usuario, 0);
    
  }else if (opcao == 4){
    
    limparTerminal();
    atualizarDespesa(usuario);
    limparTerminal();
    
  }else if (opcao == 5){
    
    limparTerminal();
    removerGasto(usuario);
    limparTerminal();
    
  }else{
    printf("Opcao invalida!\nPor favor, refaca o login e escolha outra opcao.\n");
    
  }
  
  return 0;
}

int returnToMenu(int i){
  
  int escolha2;
  
  if (i == 0){
    
    limparTerminal();
    int escolha = menu();
    
    if (escolha == 3){
      exit(0);
      
    }else if (escolha == 1){
      return 1;
    }else{
      return 2;
    }
    
  }else if (i != 1){
    
    limparTerminal();
    printf("Opcao invalida, retornando ao menu\n");
    
    escolha2 = menu();
    
    if (escolha2 == 3){
      exit(0);
    }
  }
  
  return escolha2;
}

int recarregar_TelaInicial(int retorno, char usuario[SIZE]){
  
  while (retorno == 0){
    retorno = telaInicial(usuario);
  }
  
  return retorno;
}

int main(){
  
  int retorno;
  int escolha = menu();
  
  while (escolha != 3){
    
    int opcao;
    
    if (escolha == 1){
      
      char usuario[SIZE];
      
      printf("\n======LOGIN======\n");
      printf("Digite seu usuario: ");
      scanf("%s", usuario);
      
      char senha[SIZE];
      
      printf("Digite sua senha: ");
      scanf("%s", senha);
      
      int logado = logar(usuario, senha);
      
      limparTerminal();
      
      if (logado){
        
        retorno = telaInicial(usuario);
        retorno = recarregar_TelaInicial(retorno, usuario);
        
        if (retorno == 2){
          escolha = retorno;
        }
        
      }else{
        
        opcao = error(1);
        
        if (opcao == 0){
          returnToMenu(0);
          
        }else if (opcao != 1){
          returnToMenu(2);
          
        }
      }
      
    }else if (escolha == 2){
      
      char usuario[SIZE];
      char senha[SIZE];
      int cadastro;
      
      printf("\n====CADASTRO====\n");
      fgets(usuario, sizeof(usuario), stdin);
      
      usuario[strcspn(usuario, "\n")] = '\0';
      
      while (strlen(usuario) < 5 || strlen(usuario) == 0){
        
        printf("Usuario: ");
        fgets(usuario, sizeof(usuario), stdin);
        
        usuario[strcspn(usuario, "\n")] = '\0';
        
        if (strlen(usuario) < 5 || strlen(usuario) == 0){
          printf("ERRO 1: Usuario deve ter no minimo 5 caracteres e/ou nao conter espaco em branco!\n");
          
        }
      }
      
      while (validar_usuario(usuario)){
        
        printf("ERRO 2: Usuario nao pode conter caractere especial ou numero!\n");
        printf("Usuario: ");
        fgets(usuario, sizeof(usuario), stdin);
        
        usuario[strcspn(usuario, "\n")] = '\0';
        
        if (strlen(usuario) < 5 || strlen(usuario) == 0){
          printf("ERRO 1: Usuario deve ter no minimo 5 caracteres e/ou nao conter espaco em branco!\n");
          
        }
        
        while (strlen(usuario) < 5 || strlen(usuario) == 0){
          
          printf("Usuario: ");
          fgets(usuario, sizeof(usuario), stdin);
          
          usuario[strcspn(usuario, "\n")] = '\0';
          
          if (strlen(usuario) < 5 || strlen(usuario) == 0){
            printf("ERRO 1: Usuario deve ter no minimo 5 caracteres e/ou nao conter espaco em branco!\n");
              
          }
        }
      }
      
      printf("Senha: ");
      fgets(senha, sizeof(senha), stdin);
      
      senha[strcspn(senha, "\n")] = '\0';

      while (strlen(senha) < 4){
        
        printf("ERRO 1: A senha deve conter no minimo 4 digitos e/ou nao conter espaco em branco!\n");
        printf("Senha: ");
        fgets(senha, sizeof(senha), stdin);
        
        senha[strcspn(senha, "\n")] = '\0';
        
      }
      cadastro = cadastrar(usuario, senha);
      
      if (cadastro == 1){
        
        limparTerminal();
        printf("Usuario cadastrado com sucesso!!!\n");
        
        escolha = menu();
        
      }else{
        opcao = error(2);
        
        if (opcao == 0){
          escolha = returnToMenu(0);
          
        }else if (opcao != 1){
          returnToMenu(2);
          
        }
      }
      
    }else{
      
      printf("Opcao inexistente, escolha outra opcao\n");
      escolha = menu();
      
    }
  }
  exit(0);
  
}