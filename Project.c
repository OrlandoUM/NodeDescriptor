#include<stdio.h>    
#include<stdlib.h>    
#include<conio.h>    
#include<ctype.h>    
#include<string.h>    
#include<locale.h>    
#include<math.h>   
 
typedef struct contato {
    char nome[100];
    char fone[15];
    struct contato *ant, *prox;
} TContato; 

typedef struct indice {
    char letra;
    struct indice *ant, *prox;
    TContato * inicio;
} TIndice; 

void menu();
void cadastrar(TIndice **li, TContato **lc, char nome[], char fone[]);
void remover(TIndice **li, TContato **lc, char nome[]);
void exibeTel(TIndice *li, TContato *lc, char nome[]);
void alterarTel(TIndice *li, TContato *lc, char nome[]);
void exibirTudo(TIndice *li, TContato *lc);
void apagaContatos(TIndice **li, TContato **lc, char inicial);
void apagaTudo(TIndice **li, TContato **lc); 

int main(){
    TContato *lSec;
    TIndice *lPrin;
    char op, op2;
    char nome[100], telefone[15];
    char inicial;
    setlocale(LC_ALL, "portuguese");
    do{
        menu();
        printf("Informe a opção: ");
        op = getchar(); fflush(stdin);
        switch (op){
        case '1': //CADASTRAR UM CONTATO    
            printf("Digite o nome do contato para cadastrar: ");
            gets(nome); fflush(stdin);
            printf("Informe o telefone do contato: ");
            gets(telefone); fflush(stdin);
            cadastrar(&lSec, &lPrin, nome, telefone);
            break;
        case '2': //REMOVER CONTATO
            printf("Digite o nome do contato para remoção: ");
            gets(nome); fflush(stdin);
            remover(&lPrin, &lSec, nome);
            break;
        case '3'://EXIBIR TELEFONE DE UM DADO NOME  
            printf("Informe o nome: ");
            gets(nome); fflush(stdin);
            exibeTel(lPrin, lSec, nome);
            break;
        case '4'://ALTERAR TELEFONE DE UM DADO NOME    
            printf("Informe o nome: ");
            gets(nome); fflush(stdin);
            alterarTel(lPrin, lSec, nome);
            break;
        case '5'://EXIBIR TUDO
            exibirTudo(lPrin, lSec);
            break;
        case '6'://EXIBIR TUDO COM DADA INICIAL 
            printf("INFORME A INICIAL PARA EXCLUSÃO: ");
            scanf("%c", &inicial); fflush(stdin);
            inicial = toupper(inicial);
            apagaContatos(&lPrin, &lSec, inicial);
            break;
        case '7'://LIMPAR AGENDA   
            apagaTudo(&lPrin, &lSec);
            break;
        default:
            printf("Opção inválida\n\n");
            break;
        }
        do{
            printf("Deseja escolher mais outra opção?");
            op2 = getchar(); fflush(stdin);
            op2 = toupper(op2); fflush(stdin);
        } while (op2 != 'S' && op2 != 'N');
    } while (op == 'S');
    return 0;
} 
void menu(void){
    setlocale(LC_ALL, "portuguese");
    printf("1 - Cadastrar\n");
    printf("2 - Remover\n");
    printf("3 - Exibir Telefone\n");
    printf("4 - Alterar telefone\n");
    printf("5 - Exibir Todos\n");
    printf("6 - Exibir todos com dada inicial\n");
    printf("7 - Limpar Agenda\n");
    printf("OBS: A INICIAL TEM QUE SER UM DÍGITO\n\n");
} 
void cadastrar(TIndice **li, TContato **lc, char nome[], char fone[]){
    TIndice *aux1, *aux;
    TContato *aux2, *auxNew;
    char caract;
    setlocale(LC_ALL, "portuguese");
    aux1 = *li;
    if (isalpha(nome[0] != 0)){ //O PRIMEIRO CARACTERE NÃO É UM DIGITO   
        printf("Erro. A inicial tem que ser um dígito\n\n");
    }
    else{ //PRIMEIRO CARACTERE É UM DIGITO   
        caract = nome[0];
        caract = toupper(caract);
        if (aux1 == NULL){ //LISTA PRINCIPAL VAZIA TERÁ QUE INICIALIZAR UM CARACTERE    
            aux1 = (TIndice*)malloc(sizeof(TIndice));
            aux1->letra = caract;
            aux1->ant = aux1;
            aux1->prox = aux1;
            aux1->inicio = (TContato*)malloc(sizeof(TContato));
            strcpy(aux1->inicio->nome, nome);
            strcpy(aux1->inicio->fone, fone);
            aux1->inicio->ant = aux1->inicio;
            aux1->inicio->prox = aux1->inicio;
        }
        else if (aux1->prox == NULL){ //LISTA PRINCIPAL COM APENAS 1 NÓ   
            if (aux1->letra == caract){ //A INICIAL DO NOME É COMPATÍVEL COM O CARACTERE   
                aux1->inicio->prox = (TContato*)malloc(sizeof(TContato));
                strcpy(aux1->inicio->prox->nome, nome);
                strcpy(aux1->inicio->prox->fone, fone);
                aux1->inicio->prox->ant = aux1->inicio;
                aux1->inicio->ant = aux1->inicio->prox;
                aux1->inicio->prox->prox = aux1->inicio;
            }
            else{ //A INICIAL DO NOME NÃO É COMPATÍVEL COM O CARACTERE   
                aux1->prox = (TIndice*)malloc(sizeof(TIndice));
                if (strcmp(aux1->letra, caract) < 0){ // O CARACTERE PRESENTE É ALFABETICAMENTE MENOR DO QUE O CARACTERE. INSERÇÃO NO FINAL   
                    aux1->prox = (TIndice*)malloc(sizeof(TIndice));
                    aux1->ant = aux1->prox;
                    aux1->prox->ant = aux1;
                    aux1->prox->prox = aux1;
                    aux1->prox->inicio = (TContato*)malloc(sizeof(TContato));
                    aux1->prox->inicio->ant = aux1->prox->inicio;
                    aux1->prox->inicio->prox = aux1->prox->inicio;
                    strcpy(aux1->prox->inicio->nome, nome);
                    strcpy(aux1->prox->inicio->fone, fone);
                }
                else{ //O CARACTERE PRESENTE É ALFABETICAMENTE MAIOR QUE O CARACTERE. INSERÇÃO NO INÍCIO   
                    aux1 = (TIndice*)malloc(sizeof(TIndice));
                    aux1->letra = caract;
                    aux1->ant = *li;
                    aux1->prox = aux1->ant;
                    (*li)->ant = aux1;
                    (*li)->prox = aux1;
                    (*li) = aux1;
                    (*li)->inicio = (TContato*)malloc(sizeof(TContato));
                    (*li)->inicio->ant = (*li)->inicio;
                    (*li)->inicio->prox = (*li)->inicio;
                    strcpy((*li)->inicio->nome, nome);
                    strcpy((*li)->inicio->fone, fone);
                }
            }
        }
        else{ //LISTA PRINCIPAL TEM MAIS DE 1 NÓ  
            while (aux1->prox != *li){ //PERCORRER A LISTA PRINCIPAL PARA ENCONTRAR O CARACTERE IGUAL  
                if (aux1->letra == caract){ //ENCONTROU O CARACTERE  
                    if (aux1->inicio->prox == aux1->inicio){ //A LISTA SECUNDÁRIA TEM APENAS 1 NÓ  
                        if (strcmp(aux1->inicio->nome, nome) < 0){ //O NOME PRESENTE É ALFABETICAMENTE MENOR QUE O NOME, INSERÇÃO NO INÍCIO, LISTA SEC  
                            aux2 = (TContato*)malloc(sizeof(TContato));
                            aux1->inicio->ant = aux2;
                            aux2->prox = aux1->inicio;
                            aux2->ant = aux1->inicio;
                            aux1->inicio->prox = aux2;
                            aux1->inicio = aux2;
                            return;
                        }
                        else{ //O NOME PRESENTE É ALFABETICAMENTE MAIOR QUE O NOME, INSERÇÃO NO FINAL, LISTA SEC  
                            aux2 = (TContato*)malloc(sizeof(TContato));
                            aux1->inicio->prox = aux2;
                            aux2->ant = aux1->inicio;
                            aux2->prox = aux1->inicio;
                            aux1->inicio->ant = aux2;
                            return;
                        }
                    }
                    else{ //LISTA SECUNDÁRIA TEM MAIS DE 1 NÓ  
                        aux2 = aux1->inicio;
                        auxNew = (TContato*)malloc(sizeof(TContato));
                        if (strcmp(aux2->nome, nome) < 0){ // INCERÇÃO NO INÍCIO                              
                            auxNew->prox = aux2;
                            auxNew->ant = aux2->ant;
                            aux2->ant->prox = auxNew;
                            aux2->ant = auxNew;
                            aux1->inicio = auxNew;
                            return;
                        }
                        else{
                            while (aux2->prox != aux1->inicio){
                                if (strcmp(aux2->nome, nome) > 0){ //INSERÇÃO NO MEIO  
                                    auxNew->prox = aux2->prox;
                                    auxNew->ant = aux2;
                                    aux2->prox->ant = auxNew;
                                    aux2->prox = auxNew;
                                    return; //INSERÇÃO EFETUADA  
                                }
                                aux2 = aux2->prox;
                            }
                            auxNew->ant = aux2->ant;
                            auxNew->prox = aux1->inicio;
                            aux1->inicio = auxNew;
                            aux2->prox = auxNew;
                        }
                    }
                    return; //INSERÇÃO EFETUADA  
                }
                else{ //NÃO ENCONTROU O CARACTERE NA LISTA PRINCIPAL, tem que criar o caractere ou no começo, meio ou fim  
                    if (caract < (*li)->letra){ //INSSERÇÃO NO INICIO 
                        auxNew = (TIndice*)malloc(sizeof(TIndice));
                        auxNew->prox = *li;
                        auxNew->ant = (*li)->ant;
                        (*li)->ant->prox = auxNew;
                        (*li)->ant = auxNew;
                        (*li) = auxNew;
                        auxNew = NULL;
                        auxNew = (TContato*)malloc(sizeof(TContato));
                        auxNew->ant = auxNew;
                        auxNew->prox = auxNew;
                        stcpy(auxNew->fone, fone);
                        strcpy(auxNew->nome, nome);
                        (*li)->inicio = auxNew;
                    }
                    else{
                        aux = *li;
                        while (aux->prox = *li){
                            if (caract < (*li)->letra){ //INSSERÇÃO NO MEIO 
                                aux1 = (TIndice*)malloc(sizeof(TIndice));
                                aux1->letra = caract;
                                aux1->ant = aux;
                                aux1->prox = aux->prox;
                                aux->prox->ant = aux1;
                                aux->prox = aux1;
                                aux1->inicio = (TContato*)malloc(sizeof(TContato));
                                aux1->inicio->ant = aux1->inicio;
                                aux1->inicio->prox = aux1->inicio;
                                stcpy(aux1->inicio->fone, fone);
                                strcpy(aux1->inicio->nome, nome);
                                return;
                            }
                            aux1 = aux1->prox;
                        }
                        //INSSERÇÃO NO FIM 
                        aux = (*li)->ant;
                        aux1 = (TIndice*)malloc(sizeof(TIndice));
                        aux1->ant = aux;
                        aux1->prox = aux->prox;
                        aux->prox->ant = aux1;
                        aux->prox = aux1;
                        aux1->inicio = (TIndice*)malloc(sizeof(TIndice));
                        aux1->inicio->ant = aux1->inicio;
                        aux1->inicio->prox = aux1->inicio;
                        strcpy(aux1->inicio->fone, fone);
                        strcpy(aux1->inicio->nome, nome);
                    }
                }
                aux1 = aux1->prox;
            }
        }
    }
} 
void remover(TIndice **li, TContato **lc, char nome[]){
    TIndice *auxI;
    TContato *auxC;
    char caract;
    auxI = *li;
    caract = nome[0];
    caract = toupper(caract);
    if (auxI == NULL){
        printf("LISTA VAZIA\n\n");
    }
    else{ //LISTA PRINCIPAL NÃO VAZIA
        if (auxI->prox = *li){ //LISTA PRINCIPAL COM 1 NO
            if (auxI->letra == caract){ //INICIAL IGUAL
                if (auxI->inicio == NULL){ //SE NÃO TIVER NADA COM ESSA INICIAL
                    free(auxI);
                    *li = NULL;
                }
                else{ //INICIAL DA LISTA PRINCIPAL TEM CADASTRO
                    if (auxI->inicio->prox = auxI->inicio){ //SÓ TEM 1 CADASTRO COM ESSA INICIAL
                        if (strcmp(auxI->inicio->nome, nome) == 0){ //NOME É COMPATIVEL
                            free(auxI);
                            *li = NULL;
                        }
                        else{ //NOME NÃO É COMPATIVEL
                            printf("NÃO HÁ CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                    else{ //+1 NÓ NA LISTA SECUNDÁRIA
                        auxC = auxI->inicio;
                        if (strcmp(auxI->inicio->nome, nome) > 0){ //O PRIMEIRO CADASTRO É MAIOR QUE O NOME DADO
                            printf("NÃO HÁ CADASTRO COM ESSE NOME\n\n");
                        }
                        else{ //O NOME DADO PODE ESTAR NA LISTA SECUNDARIA
                            if (strcmp(auxI->inicio->nome, nome) == 0){ //O NOME ESTÁ NO INICIO DA LISTA SECUNDARIA
                                auxC->prox->ant = auxC->prox;
                                auxC->ant = auxC->prox;
                                auxI->inicio = auxC->prox;
                                free(auxC);
                            }
                            else{
                                while (auxI->inicio->prox != auxI->inicio){ // APERCORRER A LISTA SECUNDARIA P ENCONTRAR O CONTATO
                                    if (strcmp(auxI->inicio->nome, nome) == 0){ //ENCONTROU O CONTATO NO MEIO DA LISTA
                                        auxC->prox->ant = auxC->ant;
                                        auxC->ant->prox = auxC->prox;
                                        free(auxC);
                                        return;
                                    }
                                    auxC = auxC->prox;
                                }
                                if (strcmp(auxI->inicio->nome, nome) == nome){ //O NOME ESTÁ NO ULTIMO CADASTRO DA LISTA SECUNDARIA
                                    auxC->ant->prox = auxC->prox;
                                    auxC->prox->ant = auxC->ant;
                                    free(auxC);
                                }
                            }
                        }
                    }
                }
            }//INICIAL NÃO É IGUAL
            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
        }
        else{//LISTA PRINCIPAL COM +1 NÓ
            while (auxI->prox != *li){
                if (auxI->letra == caract){ //ACHOU O CARACTERE NO MEIO DA LISTA PRINCIPAL
                    if (auxI->inicio == NULL){ //SE NÃO TIVER NADA COM ESSA INICIAL
                        auxI->prox->ant = auxI->ant;
                        auxI->ant->prox = auxI->prox;
                        free(auxI);
                        return;
                    }
                    else{ //INICIAL DA LISTA PRINCIPAL TEM CADASTRO
                        if (auxI->inicio->prox = auxI->inicio){ //SÓ TEM 1 CADASTRO COM ESSA INICIAL
                            if (strcmp(auxI->inicio->nome, nome) == 0){ //NOME É COMPATIVEL
                                auxI->prox->ant = auxI->ant;
                                auxI->ant->prox = auxI->prox;
                                free(auxI);
                                return;
                            }
                            else{ //NOME NÃO É COMPATIVEL
                                printf("NÃO HÁ CADASTRO COM ESSE NOME\n\n");
                            }
                        }
                        else{ //+1 NÓ NA LISTA SECUNDÁRIA
                            auxC = auxI->inicio;
                            if (strcmp(auxI->inicio->nome, nome) > 0){ //O PRIMEIRO CADASTRO É MAIOR QUE O NOME DADO
                                printf("NÃO HÁ CADASTRO COM ESSE NOME\n\n");
                            }
                            else{ //O NOME DADO PODE ESTAR NA LISTA SECUNDARIA
                                if (strcmp(auxI->inicio->nome, nome) == 0){ //O NOME ESTÁ NO INICIO DA LISTA SECUNDARIA
                                    auxC->prox->ant = auxC->prox;
                                    auxC->ant = auxC->prox;
                                    auxI->inicio = auxC->prox;
                                    free(auxC);
                                    return;
                                }
                                else{
                                    while (auxI->inicio->prox != auxI->inicio){ // APERCORRER A LISTA SECUNDARIA P ENCONTRAR O CONTATO
                                        if (strcmp(auxI->inicio->nome, nome) == 0){ //ENCONTROU O CONTATO NO MEIO DA LISTA
                                            auxC->prox->ant = auxC->ant;
                                            auxC->ant->prox = auxC->prox;
                                            free(auxC);
                                            return;
                                        }
                                        auxC = auxC->prox;
                                    }
                                    if (strcmp(auxI->inicio->nome, nome) == nome){ //O NOME ESTÁ NO ULTIMO CADASTRO DA LISTA SECUNDARIA
                                        auxC->ant->prox = auxC->prox;
                                        auxC->prox->ant = auxC->ant;
                                        free(auxC);
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (auxI->letra == caract){ //A INICIAL DO FIM DA LISTA PRINCIPAL É COMPATÍVEL COM O NOME
            if (auxI->inicio == NULL){ //SE NÃO TIVER NADA COM ESSA INICIAL
                auxI->ant->prox = auxI->prox;
                auxI->prox->ant = auxI->ant;
                free(auxI);
            }
            else{ //INICIAL DA LISTA PRINCIPAL TEM CADASTRO
                if (auxI->inicio->prox = auxI->inicio){ //SÓ TEM 1 CADASTRO COM ESSA INICIAL
                    if (strcmp(auxI->inicio->nome, nome) == 0){ //NOME É COMPATIVEL
                        auxI->ant->prox = auxI->prox;
                        auxI->prox->ant = auxI->ant;
                        free(auxI);
                    }
                    else{ //NOME NÃO É COMPATIVEL
                        printf("NÃO HÁ CADASTRO COM ESSE NOME\n\n");
                    }
                }
                else{ //+1 NÓ NA LISTA SECUNDÁRIA
                    auxC = auxI->inicio;
                    if (strcmp(auxI->inicio->nome, nome) > 0){ //O PRIMEIRO CADASTRO É MAIOR QUE O NOME DADO
                        printf("NÃO HÁ CADASTRO COM ESSE NOME\n\n");
                    }
                    else{ //O NOME DADO PODE ESTAR NA LISTA SECUNDARIA
                        if (strcmp(auxI->inicio->nome, nome) == 0){ //O NOME ESTÁ NO INICIO DA LISTA SECUNDARIA
                            auxC->prox->ant = auxC->prox;
                            auxC->ant = auxC->prox;
                            auxI->inicio = auxC->prox;
                            free(auxC);
                        }
                        else{
                            while (auxI->inicio->prox != auxI->inicio){ // APERCORRER A LISTA SECUNDARIA P ENCONTRAR O CONTATO
                                if (strcmp(auxI->inicio->nome, nome) == 0){ //ENCONTROU O CONTATO NO MEIO DA LISTA
                                    auxC->prox->ant = auxC->ant;
                                    auxC->ant->prox = auxC->prox;
                                    free(auxC);
                                    return;
                                }
                                auxC = auxC->prox;
                            }
                            if (strcmp(auxI->inicio->nome, nome) == nome){ //O NOME ESTÁ NO ULTIMO CADASTRO DA LISTA SECUNDARIA
                                auxC->ant->prox = auxC->prox;
                                auxC->prox->ant = auxC->ant;
                                free(auxC);
                            }
                        }
                    }
                }
            }
        }
    }
} 
void exibeTel(TIndice *li, TContato *lc, char nome[]){
    TIndice *auxI;
    TContato *auxC;
    char caract;
    caract = toupper(nome[0]);
    auxI = li;
    if (auxI == NULL){ //LISTA PRINCIPAL VAZIA
        printf("NÃO EXISTE CONTATO COM ESSE NOME\n\n");
    }
    else{ //LISTA PRINCIPAL NÃO VAZIA
        if (auxI->prox = li){ //LISTA COM APENAS 1 NÓ NA LISTA PRINCIPAL
            if (auxI->letra == caract){ //O CARACTERE É COMPATIVEL COM O NOME
                auxC = auxI->inicio;
                if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                }
                else{ //LISTA SECUNDÁRIA NÃO VAZIA
                    if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                        if (strcmp(auxC->nome, nome) == 0){//O NOME É COMPATÍVEL COM O CADASTRO
                            printf("FONE: %s\n\n", auxC->fone);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                    else{ //+1 NÓ NA LISTA SECUNDÁRIA
                        while (auxC->prox != auxI->inicio){
                            if (strcmp(auxC->nome, nome) == 0){ //O NOME É COMPATÍVEL COM O CADASTRO
                                printf("FONE: %s\n\n", auxC->fone);
                                return;
                            }
                            auxC = auxC->prox;
                        }
                        if (strcmp(auxC->nome, nome) == 0){ //NOME COMPATÍVEL COM O CADASTRO NO FIM DA LISTA
                            printf("FONE: %s\n\n", auxC->fone);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                }
            }
            else{ //O CARACTERE NÃO É COMPATIVEL COM O NOME
                printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
            }
        }
        else{ //LISTA PRINCIPAL COM +1 NÓ
            while (auxI->prox == li){
                if (auxI->letra == caract){//EXISTE CARACTERE COM ESSE NOME
                    if (auxI->letra == caract){ //O CARACTERE É COMPATIVEL COM O NOME
                        auxC = auxI->inicio;
                        if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                            return;
                        }
                        else{ //LISTA SECUNDÁRIA NÃO VAZIA
                            if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                                if (strcmp(auxC->nome, nome) == 0){//O NOME É COMPATÍVEL COM O CADASTRO
                                    printf("FONE: %s\n\n", auxC->fone);
                                    return;
                                }
                                else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                                    return;
                                }
                            }
                            else{ //+1 NÓ NA LISTA SECUNDÁRIA
                                while (auxC->prox != auxI->inicio){
                                    if (strcmp(auxC->nome, nome) == 0){ //O NOME É COMPATÍVEL COM O CADASTRO
                                        printf("FONE: %s\n\n", auxC->fone);
                                        return;
                                    }
                                    auxC = auxC->prox;
                                }
                                if (strcmp(auxC->nome, nome) == 0){ //NOME COMPATÍVEL COM O CADASTRO NO FIM DA LISTA
                                    printf("FONE: %s\n\n", auxC->fone);
                                }
                                else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                                }
                            }
                        }
                    }
                }
            }//fim while            
            if (auxI->letra == caract){ //O CARACTERE É COMPATIVEL COM O NOME
                auxC = auxI->inicio;
                if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                }
                else{ //LISTA SECUNDÁRIA NÃO VAZIA
                    if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                        if (strcmp(auxC->nome, nome) == 0){//O NOME É COMPATÍVEL COM O CADASTRO
                            printf("FONE: %s\n\n", auxC->fone);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                    else{ //+1 NÓ NA LISTA SECUNDÁRIA
                        while (auxC->prox != auxI->inicio){
                            if (strcmp(auxC->nome, nome) == 0){ //O NOME É COMPATÍVEL COM O CADASTRO
                                printf("FONE: %s\n\n", auxC->fone);
                                return;
                            }
                            auxC = auxC->prox;
                        }
                        if (strcmp(auxC->nome, nome) == 0){ //NOME COMPATÍVEL COM O CADASTRO NO FIM DA LISTA
                            printf("FONE: %s\n\n", auxC->fone);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                }
            }
            else{
                printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
            }
        }
    }
} 
void alterarTel(TIndice *li, TContato *lc, char nome[]){
    TIndice *auxI;
    TContato *auxC;
    char caract;
    char novoTel[15];
    caract = toupper(nome[0]);
    auxI = li;
    if (auxI == NULL){ //LISTA PRINCIPAL VAZIA
        printf("NÃO EXISTE CONTATO COM ESSE NOME\n\n");
    }
    else{ //LISTA PRINCIPAL NÃO VAZIA
        if (auxI->prox = li){ //LISTA COM APENAS 1 NÓ NA LISTA PRINCIPAL
            if (auxI->letra == caract){ //O CARACTERE É COMPATIVEL COM O NOME
                auxC = auxI->inicio;
                if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                }
                else{ //LISTA SECUNDÁRIA NÃO VAZIA
                    if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                        if (strcmp(auxC->nome, nome) == 0){//O NOME É COMPATÍVEL COM O CADASTRO
                            printf("INFORME O NOVO TELEFONE: ");
                            gets(novoTel); fflush(stdin);
                            strcpy(auxC->fone, novoTel);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                    else{ //+1 NÓ NA LISTA SECUNDÁRIA
                        while (auxC->prox != auxI->inicio){
                            if (strcmp(auxC->nome, nome) == 0){ //O NOME É COMPATÍVEL COM O CADASTRO
                                printf("INFORME O NOVO TELEFONE: ");
                                gets(novoTel); fflush(stdin);
                                strcpy(auxC->fone, novoTel);
                                return;
                            }
                            auxC = auxC->prox;
                        }
                        if (strcmp(auxC->nome, nome) == 0){ //NOME COMPATÍVEL COM O CADASTRO NO FIM DA LISTA
                            printf("INFORME O NOVO TELEFONE: ");
                            gets(novoTel); fflush(stdin);
                            strcpy(auxC->fone, novoTel);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                }
            }
            else{ //O CARACTERE NÃO É COMPATIVEL COM O NOME
                printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
            }
        }
        else{ //LISTA PRINCIPAL COM +1 NÓ
            while (auxI->prox != li){
                if (auxI->letra == caract){//EXISTE CARACTERE COM ESSE NOME
                    if (auxI->letra == caract){ //O CARACTERE É COMPATIVEL COM O NOME
                        auxC = auxI->inicio;
                        if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                            return;
                        }
                        else{ //LISTA SECUNDÁRIA NÃO VAZIA
                            if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                                if (strcmp(auxC->nome, nome) == 0){//O NOME É COMPATÍVEL COM O CADASTRO
                                    pprintf("INFORME O NOVO TELEFONE: ");
                                    gets(novoTel); fflush(stdin);
                                    strcpy(auxC->fone, novoTel);
                                    return;
                                }
                                else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                                    return;
                                }
                            }
                            else{ //+1 NÓ NA LISTA SECUNDÁRIA
                                while (auxC->prox != auxI->inicio){
                                    if (strcmp(auxC->nome, nome) == 0){ //O NOME É COMPATÍVEL COM O CADASTRO
                                        printf("INFORME O NOVO TELEFONE: ");
                                        gets(novoTel); fflush(stdin);
                                        strcpy(auxC->fone, novoTel);
                                        return;
                                    }
                                    auxC = auxC->prox;
                                }
                                if (strcmp(auxC->nome, nome) == 0){ //NOME COMPATÍVEL COM O CADASTRO NO FIM DA LISTA
                                    printf("INFORME O NOVO TELEFONE: ");
                                    gets(novoTel); fflush(stdin);
                                    strcpy(auxC->fone, novoTel);
                                }
                                else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                                }
                            }
                        }
                    }
                }
                auxI = auxI->prox;
            }//fim while            
            if (auxI->letra == caract){ //O CARACTERE É COMPATIVEL COM O NOME
                auxC = auxI->inicio;
                if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                }
                else{ //LISTA SECUNDÁRIA NÃO VAZIA
                    if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                        if (strcmp(auxC->nome, nome) == 0){//O NOME É COMPATÍVEL COM O CADASTRO
                            printf("INFORME O NOVO TELEFONE: ");
                            gets(novoTel); fflush(stdin);
                            strcpy(auxC->fone, novoTel);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                    else{ //+1 NÓ NA LISTA SECUNDÁRIA
                        while (auxC->prox != auxI->inicio){
                            if (strcmp(auxC->nome, nome) == 0){ //O NOME É COMPATÍVEL COM O CADASTRO
                                printf("INFORME O NOVO TELEFONE: ");
                                gets(novoTel); fflush(stdin);
                                strcpy(auxC->fone, novoTel);
                                return;
                            }
                            auxC = auxC->prox;
                        }
                        if (strcmp(auxC->nome, nome) == 0){ //NOME COMPATÍVEL COM O CADASTRO NO FIM DA LISTA
                            printf("INFORME O NOVO TELEFONE: ");
                            gets(novoTel); fflush(stdin);
                            strcpy(auxC->fone, novoTel);
                        }
                        else{ //O NOME NÃO É COMPATÍVEL COM O CADASTRO
                            printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                        }
                    }
                }
            }
            else{
                printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
            }
        }
    }
} 
void exibirTudo(TIndice *li, TContato *lc){
    TIndice *auxI;
    TContato *auxC;
    auxI = li;
    if (auxI == NULL){ //LISTA PRINCIPAL VAZIA
        printf("NÃO EXISTE CONTATO COM ESSE NOME\n\n");
    }
    else{ //LISTA PRINCIPAL NÃO VAZIA
        if (auxI->prox = li){ //LISTA COM APENAS 1 NÓ NA LISTA PRINCIPAL
            if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
            }
            else{ //LISTA SECUNDÁRIA NÃO VAZIA
                if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                    printf("NOME: %s", auxC->nome);
                    printf("FONE: %s", auxC->fone);
                }
                else{ //+1 NÓ NA LISTA SECUNDÁRIA
                    while (auxC->prox != auxI->inicio){
                        printf("NOME: %s", auxC->nome);
                        printf("FONE: %s", auxC->fone);
                        auxC = auxC->prox;
                    }
                    printf("NOME: %s", auxC->nome);
                    printf("FONE: %s", auxC->fone);
                }
            }
        }
        else{ //LISTA PRINCIPAL COM +1 NÓ
            do{
                if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                    printf("NÃO EXISTE CADASTRO COM ESSE NOME\n\n");
                    return;
                }
                else{ //LISTA SECUNDÁRIA NÃO VAZIA
                    if (auxC->prox = auxI->inicio){ //SÓ TEM 1 NÓ NA LISTA SECUNDÁRIA
                        printf("NOME: %s", auxC->nome);
                        printf("FONE: %s", auxC->fone);
                    }
                    else{ //+1 NÓ NA LISTA SECUNDÁRIA
                        while (auxC->prox != auxI->inicio){
                            printf("NOME: %s", auxC->nome);
                            printf("FONE: %s", auxC->fone);
                            auxC = auxC->prox;
                        }
                        printf("NOME: %s", auxC->nome);
                        printf("FONE: %s", auxC->fone);
                    }
                }
                auxI = auxI->prox;
            } while (auxI->prox != li);
        }            
    }
} 
void apagaContatos(TIndice **li, TContato **lc, char inicial){
    TIndice *auxI;
    TContato *auxC;
    auxI = *li;
    if (auxI == NULL){
        printf("LISTA VAZIA\n\n");
    }
    else{ //LISTA PRINCIPAL NÃO VAZIA
        if (auxI->prox == *li){//LISTA PRINCIPAL COM APENAS 1 NÓ
            if (auxI->letra == inicial){ //A LETRA DA LISTA PRINCIPAL É COMPATIVEL COM A INICIAL
                if (auxI->inicio != NULL){
                    *lc = auxI->inicio;
                    auxC = *lc;
                    if (auxC->prox == *lc){ //LISTA SECUNDÁRIA COM APENAS 1 NO
                        free(auxC);
                        *lc = NULL;
                    }
                    else{ //LISTA SECUNDARIA COM +1 NÓ
                        do{
                            auxC->prox->ant = auxC->ant;
                            auxC->ant->prox = auxC->prox;
                            *lc = auxC->prox;
                            free(auxC);
                            auxC = auxC->prox;
                        } while (auxC->prox != *lc);
                        *lc = NULL;
                    }
                }
            }
        }
        else{ //LISTA PRINCIPAL COM +1 NÓ
            do{
                if (auxI->letra == inicial){
                    if (auxI->inicio != NULL){
                        *lc = auxI->inicio;
                        auxC = *lc;
                        if (auxC->prox == *lc){ //LISTA SECUNDÁRIA COM APENAS 1 NO
                            free(auxC);
                            *lc = NULL;
                        }
                        else{ //LISTA SECUNDARIA COM +1 NÓ
                            do{
                                auxC->prox->ant = auxC->ant;
                                auxC->ant->prox = auxC->prox;
                                *lc = auxC->prox;
                                free(auxC);
                                auxC = auxC->prox;
                            } while (auxC->prox != *lc);
                            *lc = NULL;
                        }
                    }
                }
                auxI = auxI->prox;
            } while (auxI->prox != *li);
        }
    }
} 
void apagaTudo(TIndice **li, TContato **lc){
    TIndice *auxI;
    TContato *auxC;    
    while (1){
        auxI = *li;
        if (auxI == NULL){
            printf("LISTA VAZIA\n\n");
            return;
        }
        else{ //LISTA PRINCIPAL NÃO VAZIA
            if (auxI->prox == *li){ //LISTA PRINCIPAL COM APENAS 1 NÓ
                if (auxI->inicio == NULL){ //LISTA SECUNDÁRIA VAZIA
                    free(auxI);
                    *li = NULL;
                }
                else{ //LISTA SECUNDÁRIA NÃO VAZIA
                    *lc = auxI->inicio;
                    auxC = *lc;
                    if (auxC->prox == *lc){ //LISTA SECUNDÁRIA COM APENAS 1 NO
                        free(auxC);
                        *lc = NULL;
                    }
                    else{ //LISTA SECUNDÁRIA COM +1 NÓ
                        while (*lc != NULL){
                            auxC->prox->ant = auxC->ant;
                            auxC->ant->prox = auxC->prox;
                            *lc = auxC->prox;
                            free(auxC);
                            auxC = *lc;
                        }
                        free(auxI);
                        *li = NULL;
                    }
                }
            }
            else{//LISTA PRICIPAL COM +1 NÓ
                while (*li != NULL){
                    if (auxI->inicio == NULL){
                        auxI->prox->ant = auxI->ant;
                        auxI->ant->prox = auxI->prox;
                        *li = auxI->prox;
                        free(auxI);
                        auxI = *li;
                    }
                    else{
                        *lc = auxI->inicio;
                        auxC = *lc;
                        if (auxC->prox == *lc){ //LISTA SECUNDÁRIA COM APENAS 1 NO
                            free(auxC);
                            *lc = NULL;
                        }
                        else{ //LISTA SECUNDÁRIA COM +1 NÓ
                            while (*lc != NULL){
                                auxC->prox->ant = auxC->ant;
                                auxC->ant->prox = auxC->prox;
                                *lc = auxC->prox;
                                free(auxC);
                                auxC = *lc;
                            }
                            free(auxI);
                            *li = NULL;
                        }
                    }
                }
                free(auxI);
                *li = NULL;
            }
        }
    }
}