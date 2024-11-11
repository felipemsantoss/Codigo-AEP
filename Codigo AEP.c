#include <stdio.h>
#include <string.h>
#define FILENAME "arquivo.txt"

void codificar(char senha[]){
 for (int i = 0; senha[i] != '\0'; i++) {
   senha[i] = senha[i] + 5;
   }
}

void descriptografar(char senha[]){
   for (int i = 0; senha[i] != '\0'; i++) {
       senha[i] = senha[i] - 5;
   }
}

void adicionarUsuario(){
   char nome[50];
   char senha[50];
   FILE * arquivo = fopen(FILENAME, "a");

   printf("Nome do usuario: ");
   scanf("%s", nome);

   printf("Senha: ");
   scanf("%s", senha);
   codificar(senha);

   fprintf(arquivo, "%s %s\n", nome, senha);
   fclose(arquivo);

   printf("Usuario adicionado.\n");
}

void listarUsuarios(){
   char nome[50];
   char senha[50];
   FILE * arquivo = fopen(FILENAME, "r");

   printf("Lista de Usuarios:\n");
   while (fscanf(arquivo, "%s %s", nome, senha) == 2){
       descriptografar(senha);
       printf("Nome: %s\n", nome);
   }
   fclose(arquivo);
}

void alterarUsuario(){
   char nome[50];
   char senha[50];
   char nomeBuscado[50];
   int encontrado = 0;

   printf("Digite o nome do usuario a ser alterado: ");
   scanf("%s", nomeBuscado);

   FILE *arquivo = fopen(FILENAME, "r");
   FILE *temp = fopen("temp.txt", "w");

   while (fscanf(arquivo, "%s %s", nome, senha) == 2){
       if (strcmp(nome, nomeBuscado) == 0){
           encontrado = 1;
           printf("Digite a nova senha: ");
           scanf("%s", senha);
           codificar(senha);
       }
       fprintf(temp, "%s %s\n", nome, senha);
   }

   fclose(arquivo);
   fclose(temp);

   remove(FILENAME);
   rename("temp.txt", FILENAME);

   if (encontrado)
       printf("Usuario alterado.\n");
   else
       printf("Usuario nao encontrado.\n");
}

void excluirUsuario(){
   char nome[50];
   char senha[50];
   char nomeBuscado[50];
   int encontrado = 0;

   printf("Usuario a ser excluido: ");
   scanf("%s", nomeBuscado);

   FILE *arquivo = fopen(FILENAME, "r");
   FILE *temp = fopen("temp.txt", "w");

   while (fscanf(arquivo, "%s %s", nome, senha) == 2){
       if(strcmp(nome, nomeBuscado) != 0){
           fprintf(temp, "%s %s\n", nome, senha);
       } else{
           encontrado = 1;
       }
   }

   fclose(arquivo);
   fclose(temp);

   remove(FILENAME);
   rename("temp.txt", FILENAME);

   if (encontrado)
       printf("Usuario excluido.\n");
   else
       printf("usuario nao encontrado.\n");
}

int main() {
   int opcao;

   do{
       printf("\nUsuarios do Sistema\n");
       printf("1. Incluir usuario\n");
       printf("2. Alterar usuario\n");
       printf("3. Excluir usuario\n");
       printf("4. Listar usuarios\n");
       printf("Escolha uma opcao: ");
       scanf("%d", &opcao);

       switch (opcao){
           case 1:
               adicionarUsuario();
               break;
           case 2:
               alterarUsuario();
               break;
           case 3:
               excluirUsuario();
               break;
           case 4:
               listarUsuarios();
               break;
           default:
               printf("Opcao invalida.\n");
       }
   } while (opcao != 4);
   return 0;
}