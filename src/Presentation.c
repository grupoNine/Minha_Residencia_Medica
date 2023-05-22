#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Presentation.h"
#include "Application.h"
#include "Data.h"

Current current = {NULL};

// LOGIN //

User* loginInterface() {
    char uniqueID[51];
    char password[51];
    clear();
    logo();
    printf("Usuario: ");
    scanf("%s", uniqueID);
    printf("Senha: ");
    scanf("%s", password);
    User* user = getUserByUniqueID(uniqueID);
    if(user!=NULL && strcmp(user->password, password)==0){
        current.user = user;
        return user;
    }else{ 
        clear();
        printf("\n[Usuario ou senha invalidos]\n");
        return NULL;
    }
}

void userInterface(User* user) {
    switch(current.user->level) {
        case 1: residenteMenu(); break;
        case 2: preceptorMenu(); break;
        case 3: gestorMenu(); break;
    }
}

// RESIDENTE MENU //

void residenteMenu() {
    while(true){
        printf("RESIDENTE\n\n%s\n\n", current.user->exhibitionName);
        int choice;
        printf("[1] Solicitar avaliacao\n[0] Sair\n\n>>> ");
        scanf("%d", &choice);
        getchar();
        printf("\n");
        if(choice==0){
            freeUser(current.user);
            current.user = NULL;
            clear();
            break;
        }else if(choice == 1){
            clear();
            solicitarAvaliacaoMenu();
        }else{
            clear();
            printf("[Opcao invalida]\n\n");
        }
    }
}

// avaliacao

void solicitarAvaliacaoMenu() {
    PreceptorNameNode* preceptorNames = getPreceptorNames();
    if(preceptorNames==NULL){
        clear();
        printf("[Nao ha preceptores disponiveis]\n\n");
        return;
    }
    printf("Selecione o preceptor:\n\n");
    int i = 1;
    PreceptorNameNode* currentNode = preceptorNames;
    while(currentNode!=NULL){
        printf("[%d] %s\n", i, currentNode->preceptor->exhibitionName);
        i++;
        currentNode = currentNode->next;
    }
    printf("[0] Voltar\n\n>>> ");
    int choice;
    scanf("%d", &choice);
    if(choice<0 || choice>=i){
        clear();
        printf("[Opcao invalida]\n\n");
        return;
    }
    if(choice==0){
        clear();
        return;
    }else{
        PreceptorNameNode* selecionadoNode = preceptorNames;
        for (int j=1; j<choice; j++) {
            selecionadoNode = selecionadoNode->next;
        }
        clear();
        User* preceptor = getUserByUniqueID(selecionadoNode->preceptor->uniqueID);
        if (preceptor==NULL) {
            clear();
            printf("[Preceptor nao foi encontrado]\n\n");
            return;
        }
        if (solicitarAvaliacao(current.user, preceptor)) {
            clear();
            printf("[Avaliacao solicitada com sucesso]\n\n");
        }else{
            clear();
            printf("[Nao foi possivel solicitar avaliacao]\n\n");
        }
        free(preceptor);
    }
    PreceptorNameNode* node = preceptorNames;
    while(node!=NULL){
        PreceptorNameNode* nextNode = node->next;
        if(node->preceptor!=NULL){
            free(node->preceptor);
        }
        free(node);
        node = nextNode;
    }
}

// PRECEPTOR MENU //

void preceptorMenu() {
    while(true){
        printf("PRECEPTOR\n\n%s\n\n", current.user->exhibitionName);
        int choice;
        printf("[1] Avaliar residente\n[0] Sair\n\n>>> ");
        scanf("%d", &choice);
        getchar();
        if(choice==0){
            freeUser(current.user);
            current.user = NULL;
            clear();
            break;
        }else if(choice==1){
            clear();
            listResidentesForAvaliacao();
        }else{
            clear();
            printf("[Opcao invalida]\n\n");
        }
    }
}

// avaliacao //
void listResidentesForAvaliacao() {
    printf("Selecione o residente:\n\n");
    AvaliacaoNode* avaliacoes = getAvaliacoesForPreceptor(current.user->uniqueID);
    int i = 0;
    AvaliacaoNode* current = avaliacoes;
    while(current!=NULL){
        printf("[%d] %s\n", i+1, current->residenteName);;
        current = current->next;
        i++;
    }
    printf("[0] Voltar\n\n");
    int choice;
    printf(">>> ");
    scanf("%d", &choice);
    if (choice<0 || choice>i) {
        clear();
        printf("[Opcao invalida]\n\n");
        return;
    }
    if(choice!=0) {
        AvaliacaoNode* selectedNode = avaliacoes;
        for (int j=0; j<(choice-1); j++) {
            selectedNode = selectedNode->next;
        }
        char* residenteID = selectedNode->avaliacao.residenteID;
        clear();
        avaliarResidenteMenu(residenteID);
    }
    while (avaliacoes!=NULL) {
        AvaliacaoNode* nextNode = avaliacoes->next;
        free(avaliacoes);
        avaliacoes = nextNode;
    }
}

void avaliarResidenteMenu(char* residenteID) {
    User* residente = getUserByUniqueID(residenteID);
    if(residente==NULL){
        clear();
        printf("[Residente nao encontrado]\n\n");
        return;
    }
    printf("Avaliacao do residente: %s\n\n", residente->exhibitionName);
    float nota1, nota2, nota3;
    do{
        printf("Primeira nota (0 - 10) >>> ");
        scanf("%f", &nota1);
    }while(nota1<0 || nota1>10);
    do{
        printf("Segunda nota (0 - 10) >>> ");
        scanf("%f", &nota2);
    } while(nota2<0 || nota2>10);
    do {
        printf("Terceira nota (0 - 10) >>> ");
        scanf("%f", &nota3);
    } while(nota3<0 || nota3>10);
    printf("Confirmar avaliacao? [s] Sim [n] Nao\n\n>>> ");
    char choice;
    scanf(" %c", &choice);
    if (choice=='s' || choice=='S') {
        if (avaliarResidente(current.user, residente, nota1, nota2, nota3)) {
            clear();
            printf("[Avaliacao realizada com sucesso]\n\n");
        } else {
            clear();
            printf("[Nao foi possivel realizar a avaliacao]\n\n");
        }
    }
    free(residente);
}

// GESTOR MENU //

void gestorMenu() {
    while(true){
        printf("GESTOR\n\n%s\n\n", current.user->exhibitionName);
        int choice;
        printf("[1] Cadastrar novo usuario\n[0] Sair\n\n>>> ");
        scanf("%d", &choice);
        getchar();
        if (choice==0){
            free(current.user);
            current.user = NULL;
            clear();
            break;
        }else if(choice==1){
            bool signupResult = signupInterface();
            if(signupResult){
                printf("[Cadastro realizado com sucesso]\n\n");
            }else{
                clear();
                printf("[Cadastro falhou, tente novamente]\n\n");
            }
        }else{
            clear();
            printf("[Opcao invalida]\n\n");
        }
    }
}

// signup //

bool signupInterface() {
    clear();
    char fullName[101];
    int level;
    printf("Digite o nome completo do novo usuario:\n(Nao use acentuacao ou caracteres especiais)\n\n>>> ");
    fgets(fullName, sizeof(fullName), stdin);
    if (strchr(fullName, '\n')==NULL) {
        clear();
        printf("[Nome invalido]\n\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        return false;
    }else{
        fullName[strcspn(fullName, "\n")] = '\0';
    }
    printf("Nivel de acesso:\n[1] Residente\n[2] Preceptor\n[3] Gestor\n\n>>> ");
    scanf("%d", &level);
    getchar();
    bool signupResult = signup(fullName, level);
    if (!signupResult){
        clear();
        printf("[Nivel de acesso invalido]\n\n");
        return false;
    }
    return true;
}

void printUserInfo(User* user) {
    clear();
    printf("[Informacoes do novo usuario]\n\n");
    printf("ID Unico: %s\n", user->uniqueID);
    printf("Nome Completo: %s\n", user->fullName);
    printf("Nome de Exibicao: %s\n", user->exhibitionName);
    printf("Senha: %s\n", user->password);
    printf("Nivel de Acesso: %d\n", user->level);
    char timestamp[26];
    strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %H:%M:%S", localtime(&(user->createdTime)));
    printf("Data de Criacao: %s\n", timestamp);
    printf("\n\n");
}

// MISC //

void quitMsg() {
    clear();
    logo();
    printf("Infinity and beyond!\n");
}

void logo(){
    printf("\n[MRM - Minha Residencia Medica]\n\n");
}
void clear() {
    printf("\033[2J\033[1;1H");
}