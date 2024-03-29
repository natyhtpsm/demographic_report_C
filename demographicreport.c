/* Name: Nathália Pimentel de Assis
  University: University of Brasilia
  Bachelor student in eletronic engineering course */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#define tam 100
FILE *arquivo_pessoa;
FILE *arquivo_cidade;
FILE *arquivo_estado;

int valida_data(int dia, int mes, int ano);
int calcula_idade();
void cadastra_estado();
void cadastra_cidade();
void cadastra_pessoa();
void pessoa_estado();
void pessoa_cidade();
void pessoa_nome();
void relatorio_demo();
void toupper_string(char *);

typedef struct pessoa {
    char nome[tam];
    char estpessoa[tam];
    char cidpessoa[tam];
    char sigla[2];
    int data[3];
    char sexo;
}people ;

void apresentacao(){
    system("cls");
    printf("-------------------------------------------------------------\n");
    printf("               Aluna: Nathália Pimentel de Assis \n");
    printf("               Matrícula: 17/0153169 \n");
    printf("               Relatório Demográfico \n");
    printf("               APC - 2019/1 - Turma DD \n");
    printf("-------------------------------------------------------------\n");

    system("pause");
    system("cls");

}

void cabecalho(){
    system("cls");
    printf("---------------------------------------------------\n");
    printf("               RELATÓRIO DEMOGRÁFICO\n");
    printf("---------------------------------------------------\n\n");
}

int main(){
    setlocale(LC_ALL, "");
    system ("color 4f");
    int opcao;
    apresentacao();
    do
    {
        cabecalho();
        printf("            1) Cadastrar Estado\n");
        printf("            2) Cadastrar Cidade\n");
		printf("            3) Cadastrar Pessoa\n");
        printf("            4) Listar pessoas por Estado\n");
        printf("            5) Listar pessoas por Cidade\n");
        printf("            6) Consultar Pessoa por Nome\n");
        printf("            7) Gerar relatório demográfico\n");
        printf("            8) Finalizar Programa\n");
        printf("            Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();
        system("cls");

        switch(opcao)
        {
            case 1:
                cadastra_estado();
            break;

            case 2:
                cadastra_cidade();
            break;

            case 3:
                cadastra_pessoa();
            break;

            case 4:
                pessoa_estado();
            break;

            case 5:
                pessoa_cidade();
            break;

            case 6:
                pessoa_nome();
            break;

            case 7:
                relatorio_demo();
            break;

            case 8:
                cabecalho();
                printf("            Obrigada pela visita! \n\n");
                getchar();
            break;

            default:
                cabecalho();
                printf("            Digite uma opção válida.\n\n");
                system("pause");

        }
    } while(opcao != 8);
}

void toupper_string(char *str) {
    char *c = str;
    while(*c = toupper(*c)) c++;
}

void cadastra_estado(void){
    cabecalho();

    int flag = 0;
    char estado[tam];
    char comp_est[tam];

    // Checa se o arquivo existe
    if( access( "arquivo_estado.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_estado = fopen("arquivo_estado.txt", "a+");
    } else
        {
            // Se o arquivo não existe
            arquivo_estado = fopen("arquivo_estado.txt", "w+");
        }
    if(arquivo_estado == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

    fflush(stdin); // Flush no buffer de teclado
    printf("            Digite apenas a sigla do estado: ");
    fgets(estado, tam, stdin);                               //O programa então irá ler o estado que o usuário deseja cadastrar.
    toupper_string(estado); // Capitaliza geral
    rewind(arquivo_estado);
    while(1) {  //Aqui iremos verificar se o estado já existe ou não.
        //fscanf(arquivo_estado, "%[^\n]", comp_est);
        fgets(comp_est, tam, arquivo_estado);
        if(feof(arquivo_estado)){
            break;
        }
        if(strcmp(estado, comp_est)==0){
            printf("        Esse estado já existe. \n");        //Caso já exista, uma mensagem será mostrada na tela para o usuário.
            flag = 1;
            break;
        }
    }
    if(flag == 0){                                         //Caso o estado não exista, o programa irá registrá-lo no arquivo.
        fprintf(arquivo_estado, "%s", estado);
        printf("            O estado foi registrado!\n");
    }
    fclose(arquivo_estado);
    getchar();
}

void cadastra_cidade(void){
    cabecalho();

    int flag = 0, flag3=0, i, tam_cid, tam_str;
    char cidade[tam];
    char comp_cid[tam], comp_est[3];
    char sigla[3], str[tam];
    FILE *arquivo_cidade;

    // Checa se o arquivo existe
    if( access( "arquivo_cidade.txt", F_OK ) != -1 ) {
        // Se o arquivo existe
        arquivo_cidade = fopen("arquivo_cidade.txt", "a+");
    } else {
        // Se o arquivo não existe
        arquivo_cidade = fopen("arquivo_cidade.txt", "w+");
    }
    if(arquivo_cidade == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

        if( access( "arquivo_estado.txt", F_OK ) != -1 ) {
        // Se o arquivo existe
        arquivo_estado = fopen("arquivo_estado.txt", "r");
    } else {
        // Se o arquivo não existe
        arquivo_estado = fopen("arquivo_estado.txt", "w+");
    }
    if(arquivo_estado == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        getchar();
        return;
    }

    fflush(stdin);                                           // Flush no buffer de teclado
    printf("            Digite o nome da cidade: ");
    fgets(cidade, tam, stdin);

    printf("\n            Digite a sigla do estado que essa cidade pertence: ");  //O programa então irá ler a cidade que o usuário deseja cadastrar.
    fgets(sigla, 3, stdin);
    toupper_string(cidade);
    toupper_string(sigla);
    tam_cid = strlen(cidade);

     while(1) {  //Aqui iremos verificar se o estado já existe ou não.
        fgets(comp_est, 3, arquivo_estado);
        if(feof(arquivo_estado)){
            break;
        }
        if(strcmp(sigla,comp_est)==0){

            flag3 = 1;
            break;
        }
    }
    if(flag3 == 0){                                         //Caso o estado não exista no arquivo de estado, o programa irá pedir para que o usuário o registre.
        printf("            Por favor, cadastre o estado na opção '1' do menu. \n");
        system("pause");
        getchar();
        return;
    }

    strcpy(str, cidade);
    str[strlen(str)-1] = '\0';
    strcat(str, sigla);

    rewind(arquivo_cidade);
    if(flag3 == 1){
        while(1) {                                               //Aqui iremos verificar se a cidade já existe ou não.
            fgets(comp_cid, tam, arquivo_cidade);
            if(feof(arquivo_cidade)){
                break;
            }
            if(strcmp(str, comp_cid)==0){
                printf("            Essa cidade já foi registrada. \n");
                getchar();       //Caso já exista, uma mensagem será mostrada na tela para o usuário.
                flag = 1;
                break;
            }
        }
        if(flag == 0){                                         //Caso o cidade não exista, o programa irá registrá-lo no arquivo.
            fprintf(arquivo_cidade, "%s\n", str);

            printf("            A cidade foi registrada!\n");
            getchar();

        }
        fclose(arquivo_cidade);
        getchar();
    }
}

int valida_data(int dia, int mes, int ano){
    int resultado_final=1, resultado_mes=1, resultado_dia=1;


    if(mes <= 12)
        {
        resultado_mes = 1;
            if(mes == 1 || mes == 3 || mes == 5 || mes == 7 ||mes == 8 || mes == 10 || mes == 12)
            {
            if(dia <=31)
                {
                resultado_dia = 1;
                }      else {
                        resultado_dia = 0;
                            }
            }
                else if(mes == 4 || mes == 6 || mes == 9 || mes == 12)
                {
                    if(dia <= 30){
                        resultado_dia = 1;
                    }
                    else{
                        resultado_dia = 0;
                    }
                }
                else if(mes == 2)
                    {
                        if(ano%4 == 0 && ano%100 != 0)
                            {
                                if(dia<=29)
                                    {
                                    resultado_dia=1;
                                    }
                                    else
                                        {
                                        resultado_dia=0;
                                        }

                            }else if(dia<=28)
                                {
                                resultado_dia = 1;
                                } else
                                    {
                                    resultado_dia = 0;
                                    }
                    }
        }
        else
            {
            resultado_mes = 0;
            }
        if(resultado_mes == 1 && resultado_dia == 1)
            {
            resultado_final = 1;
            }
        else
            {
            resultado_final = 0;
            }

return resultado_final;}

void cadastra_pessoa(void){
    cabecalho();
    int flag3 = 0;
    int flag4 = 0;
    int resultado_data;
    char nome[tam];
    char comp_est[tam];
    char comp_cid[tam];
    people fulano;

    // Checa se o arquivo existe
    if( access( "arquivo_pessoa.txt", F_OK ) != -1 ) {
        // Se o arquivo existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "a+");
    } else {
        // Se o arquivo não existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "w+");
    }
    if(arquivo_pessoa == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        getchar();
        return;
    }

    if( access( "arquivo_estado.txt", F_OK ) != -1 ) {
        // Se o arquivo existe
        arquivo_estado = fopen("arquivo_estado.txt", "a+");
    } else {
        // Se o arquivo não existe
        arquivo_estado = fopen("arquivo_estado.txt", "w+");
    }
    if(arquivo_estado == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        getchar();
        return;
    }

    if( access( "arquivo_cidade.txt", F_OK ) != -1 ) {
        // Se o arquivo existe
        arquivo_cidade = fopen("arquivo_cidade.txt", "a+");
    } else {
        // Se o arquivo não existe
        arquivo_cidade = fopen("arquivo_cidade.txt", "w+");
    }
    if(arquivo_cidade == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        getchar();
        return;
    }

    // O arquivo tem o formato "nome;idade;sexo;estado;cidade;\n"
    printf("\n            Digite o nome: ");
    scanf("%[^\n]", fulano.nome);


    printf("\n            Digite a data de nascimento: ");
    scanf("%d/%d/%d", &fulano.data[0], &fulano.data[1], &fulano.data[2]);
    resultado_data = valida_data(fulano.data[0], fulano.data[1], fulano.data[2]);
    if(resultado_data == 0){
        printf("\t\tData inválida.\n");
        system("pause");
        return;
    }


    getchar();
    printf("\n            Digite o sexo('f' ou 'm'): ");
    scanf("%c", &fulano.sexo);
    toupper_string(fulano.sexo);


    getchar();
    fflush(stdin);
    printf("\n            Digite apenas a sigla do estado: ");
    fgets(fulano.estpessoa, tam, stdin);
    toupper_string(fulano.estpessoa);
    rewind(arquivo_estado);

    while(1) {  //Aqui iremos verificar se o estado já existe ou não.
        fgets(comp_est, tam, arquivo_estado);
        if(feof(arquivo_estado)){
            break;
        }
        if(strcmp(fulano.estpessoa,comp_est)==0){
            //Caso já exista, o programa irá cadastrar o estado da pessoa normalmente.
            flag3 = 1;
            break;
        }
    }
    if(flag3 == 0){                                         //Caso o estado não exista no arquivo de estado, o programa irá pedir para que o usuário o registre.
        printf("            Por favor, cadastre o estado na opção '1' do menu. \n");
        getchar();
        return;
    }

    printf("\n            Digite a cidade: ");
    fgets(fulano.cidpessoa, tam, stdin);
    toupper_string(fulano.cidpessoa);
    rewind(arquivo_cidade);

    char cidade_prov[50];
    strcpy(cidade_prov, fulano.cidpessoa);
    cidade_prov[strlen(cidade_prov)-1] = '\0';
    strcat(cidade_prov, fulano.estpessoa);

    while(1) {  //Aqui iremos verificar se o estado já existe ou não.
        fgets(comp_cid, tam, arquivo_cidade);
        if(feof(arquivo_cidade)){
            break;
        }
        if(strcmp(cidade_prov, comp_cid)==0){
            //Caso já exista, uma mensagem será mostrada na tela para o usuário.
            flag4 = 1;
            break;
        }
    }
    if(flag4 == 0){                                         //Caso o estado não exista, o programa irá registrá-lo no arquivo.
        printf("Por favor, cadastre a cidade na opção '2' do menu. \n");
        getchar();
        return;
    }

    system("pause");
    toupper_string(fulano.nome);
    fprintf(arquivo_pessoa, "%s;", fulano.nome);
    fprintf(arquivo_pessoa, "%02d/%02d/%04d;", fulano.data[0], fulano.data[1], fulano.data[2]);
    fprintf(arquivo_pessoa, "%c;", fulano.sexo);
    fulano.estpessoa[strlen(fulano.estpessoa)-1]=0; // se nao funcionar coloco -2
    fulano.cidpessoa[strlen(fulano.cidpessoa)-1]=0;
    fprintf(arquivo_pessoa, "%s;", fulano.estpessoa);
    fprintf(arquivo_pessoa, "%s;\n", fulano.cidpessoa);


    fclose(arquivo_pessoa);
}

void pessoa_estado(void){
    cabecalho();
    people fulano;
    char estado_pesq[tam]; //String que vai ler o que o usuário quer pesquisar
    int i; //Contador

        // Checa se o arquivo existe
    if( access( "arquivo_estado.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_estado = fopen("arquivo_estado.txt", "a+");
    } else
        {
            // Se o arquivo não existe
            arquivo_estado = fopen("arquivo_estado.txt", "w+");
        }
    if(arquivo_estado == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }


    if( access( "arquivo_pessoa.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "r");
    }
    else
    {
            // Se o arquivo não existe
            arquivo_pessoa = fopen("arquivo_pessoa.txt", "w+");
    }
    if(arquivo_pessoa == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

    printf("            Digite a sigla do estado que deseja pesquisar: ");
    scanf("%s", estado_pesq);
    toupper_string(estado_pesq);

    getchar();
    while (!feof(arquivo_pessoa))
    {
        fscanf(arquivo_pessoa, "%[^;];", fulano.nome);
        fscanf(arquivo_pessoa, "%d/%d/%d;", &fulano.data[0], &fulano.data[1], &fulano.data[2]);
        fscanf(arquivo_pessoa, "%c;", &fulano.sexo);
        fscanf(arquivo_pessoa, "%[^;];", fulano.estpessoa);
        fscanf(arquivo_pessoa, "%[^;];\n", fulano.cidpessoa);
        if(strcmp(fulano.estpessoa, estado_pesq)==0)
        {
            printf("            Nome: %s\n", fulano.nome);
            printf("            Data de nascimento: %02d/%02d/%04d\n", fulano.data[0], fulano.data[1], fulano.data[2]);
            printf("            Sexo: %c\n", fulano.sexo);
            printf("            Estado: %s\n", fulano.estpessoa);
            printf("            Cidade: %s\n", fulano.cidpessoa);
            printf("            -----------------------------------------------\n");
        }
    }
    getchar();
}

void pessoa_cidade(void){
 cabecalho();
    people fulano;
    char cidade_pesq[tam], sigla_pesq[3], str[tam], str2[tam]; //String que vai ler o que o usuário quer pesquisar
    int i, tam_cid, tam_cid2; //Contador

        // Checa se o arquivo existe

    if( access( "arquivo_pessoa.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "r");
    }
    else
    {
            // Se o arquivo não existe
            arquivo_pessoa = fopen("arquivo_pessoa.txt", "w+");
    }
    if(arquivo_pessoa == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

    printf("            Digite a cidade que deseja pesquisar: ");
    fgets(cidade_pesq, tam, stdin);
    getchar();
    printf("            Digite a sigla do estado que essa cidade pertence: ");
    fgets(sigla_pesq, 3, stdin);
    getchar();

    toupper_string(cidade_pesq);
    toupper_string(sigla_pesq);
    tam_cid = strlen(cidade_pesq);
    strcpy(str, cidade_pesq);
    str[strlen(str)-1] = '\0';
    strcat(str, sigla_pesq);

    getchar();

    while (!feof(arquivo_pessoa))
    {
        fscanf(arquivo_pessoa, "%[^;];", fulano.nome);
        fscanf(arquivo_pessoa, "%d/%d/%d;", &fulano.data[0], &fulano.data[1], &fulano.data[2]);
        fscanf(arquivo_pessoa, "%c;", &fulano.sexo);
        fscanf(arquivo_pessoa, "%[^;];", fulano.estpessoa);
        fscanf(arquivo_pessoa, "%[^;];\n", fulano.cidpessoa);

        tam_cid2 = strlen(fulano.cidpessoa);
        strcpy(str2, fulano.cidpessoa);
        strcat(str2, fulano.estpessoa);

        if(strcmp(str2, str)==0 && strcmp(fulano.estpessoa, sigla_pesq)==0)
        {
            printf("            Nome: %s\n", fulano.nome);
            printf("            Data de nascimento: %02d/%02d/%04d\n", fulano.data[0], fulano.data[1], fulano.data[2]);
            printf("            Sexo: %c\n", fulano.sexo);
            printf("            Estado: %s\n", fulano.estpessoa);
            printf("            Cidade: %s\n", fulano.cidpessoa);
            printf("            -----------------------------------------------\n");
        }
    }
    getchar();
}

void pessoa_nome(void){
    cabecalho();
    people fulano;
    char nome_pesq[tam]; //String que vai ler o que o usuário quer pesquisar

    int i; //Contador

    if( access( "arquivo_pessoa.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "r");
    }
    else
    {
            // Se o arquivo não existe
            printf("Arquivo não existe.\n");
            getchar();
            return;
    }
    if(arquivo_pessoa == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

    printf("       Digite o nome ou parte do nome que deseja pesquisar: ");
    fgets(nome_pesq, tam, stdin);
    nome_pesq[strlen(nome_pesq)-1] = 0;
    toupper_string(nome_pesq);


    while (!feof(arquivo_pessoa))
    {
        fscanf(arquivo_pessoa, "%[^;];", fulano.nome);
        fscanf(arquivo_pessoa, "%d/%d/%d;", &fulano.data[0], &fulano.data[1], &fulano.data[2]);
        fscanf(arquivo_pessoa, "%c;", &fulano.sexo);
        fscanf(arquivo_pessoa, "%[^;];", fulano.estpessoa);
        fscanf(arquivo_pessoa, "%[^;];\n", fulano.cidpessoa);
        if((strcmp(fulano.nome, nome_pesq)==0) || (strstr(fulano.nome, nome_pesq) != NULL))
        {
            printf("            Nome: %s\n", fulano.nome);
            printf("            Data de nascimento: %02d/%02d/%04d\n", fulano.data[0], fulano.data[1], fulano.data[2]);
            printf("            Sexo: %c\n", fulano.sexo);
            printf("            Estado: %s\n", fulano.estpessoa);
            printf("            Cidade: %s\n", fulano.cidpessoa);
            printf("            -----------------------------------------------\n");
        }
    }
    fclose(arquivo_pessoa);
    getchar();
}

int calcula_idade(int dia_hoje, int mes_hoje, int ano_hoje){
    int idade;
    people fulano;
       if( access( "arquivo_pessoa.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "a+");
    } else
        {
            // Se o arquivo não existe
            arquivo_pessoa = fopen("arquivo_pessoa.txt", "w+");
        }

    if(arquivo_pessoa == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

   while(!feof(arquivo_pessoa)){
        fscanf(arquivo_pessoa, "%[^;];", fulano.nome);
        fscanf(arquivo_pessoa, "%d/%d/%d;", &fulano.data[0], &fulano.data[1], &fulano.data[2]);
        fscanf(arquivo_pessoa, "%c;", &fulano.sexo);
        fscanf(arquivo_pessoa, "%[^;];", fulano.estpessoa);
        fscanf(arquivo_pessoa, "%[^;];\n", fulano.cidpessoa);

        if(ano_hoje>fulano.data[2]){
            idade=ano_hoje-fulano.data[2];
        }
        if(mes_hoje<fulano.data[1]){
            idade = idade-1;
        }
        if(dia_hoje<fulano.data[0]){
            idade = idade-1;
        }
   }



return idade; }

void relatorio_demo(void){
    cabecalho();
    people fulano;
    char comp_fem, comp_mas;
    unsigned long total_pessoas;
    int comp_idade, cont_sexo, cont_fem, cont_mas, cont_05, cont_610, cont_1120, cont_2140, cont_4160, cont_mais60;
    int perc_05, perc_610, perc_1120, perc_2140, perc_4160, perc_mais60;
    int data_hoje[3], valida_hoje;
    comp_idade=0;
    cont_fem=0;
    cont_mas=0;
    cont_05=0;
    cont_610=0;
    cont_1120=0;
    cont_2140=0;
    cont_4160=0;
    cont_mais60=0;

    comp_fem = 'f';
    comp_mas = 'm';


    // Checa se o arquivo existe
    if( access( "arquivo_pessoa.txt", F_OK ) != -1 )
    {
        // Se o arquivo existe
        arquivo_pessoa = fopen("arquivo_pessoa.txt", "a+");
    } else
        {
            // Se o arquivo não existe
            arquivo_pessoa = fopen("arquivo_pessoa.txt", "w+");
        }

    if(arquivo_pessoa == NULL) {
        printf("Erro ao criar/modificar arquivo\n");
        return;
    }

    printf("\tPor favor, digite a data de hoje no formato dd/mm/aaaa: ");
    scanf("%d/%d/%d", data_hoje[0], data_hoje[1], data_hoje[2]);

    while(valida_data(data_hoje[0], data_hoje[1], data_hoje[2]) == 0){
        printf("A data de hoje não é válida. Por favor, digite uma data válida\n");
        scanf("%d/%d/%d", data_hoje[0], data_hoje[1], data_hoje[2]);

    }




    while (!feof(arquivo_pessoa))
        {
            fscanf(arquivo_pessoa, "%[^;];", fulano.nome);
            fscanf(arquivo_pessoa, "%d/%d/%d;", &fulano.data[0], &fulano.data[1], &fulano.data[2]);
            fscanf(arquivo_pessoa, "%c;", &fulano.sexo);
            fscanf(arquivo_pessoa, "%[^;];", fulano.estpessoa);
            fscanf(arquivo_pessoa, "%[^;];\n", fulano.cidpessoa);

        }

        if(strcmp(fulano.sexo, comp_fem) == 0){
            cont_fem = cont_fem+1;
            total_pessoas = total_pessoas+1;
        }
        else if(strcmp(fulano.sexo, comp_mas)==0){
            cont_mas = cont_mas+1;
            total_pessoas = total_pessoas+1;
        }

            if(calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])>=0 && calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2]) <=5){
                    cont_05=cont_05+1;
            }
            else if(calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2]) >=6 && calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2]) <=10){
                   cont_610 = cont_610+1;
                }
                else if(calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2]) >= 11 && calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])<=20){
                    cont_1120 = cont_1120+1;
                    }
                    else if(calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])>= 21 && calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])<=40){
                        cont_2140 = cont_2140+1;
                        }
                        else if(calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])>=41 && calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])<=60){
                            cont_4160 = cont_4160+1;
                            }
                            else if(calcula_idade(data_hoje[0], data_hoje[1], data_hoje[2])>60){
                                cont_mais60 = cont_mais60+1;
                                }

    perc_05 = (cont_05/total_pessoas)*100;
    perc_1120 = (cont_1120/total_pessoas)*100;
    perc_2140 = (cont_2140/total_pessoas)*100;
    perc_4160 = (cont_4160/total_pessoas)*100;
    perc_610 = (cont_610/total_pessoas)*100;
    perc_mais60 = (cont_mais60/total_pessoas)*100;
    printf("%ld", total_pessoas);
    printf("%d% das pessoas têm entre 0 e 5 anos.\n", perc_05);
    printf("%d% das pessoas têm entre 6 e 10 anos.\n", perc_610);
    printf("%d% das pessoas têm entre 11 e 20 anos.\n", perc_1120);
    printf("%d% das pessoas têm entre 21 e 40 anos.\n", perc_2140);
    printf("%d% das pessoas têm entre 41 e 60 anos.\n", perc_4160);
    printf("%d% das pessoas têm mais de 60 anos.\n", perc_mais60);
    printf("%d pessoas são do sexo masculino.\n", cont_mas);
    printf("%d pessoas são do sexo feminino. \n", cont_fem);
    system("pause");
    fclose(arquivo_pessoa);
    getchar();
  }
