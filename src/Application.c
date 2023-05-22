#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "Application.h"
#include "Presentation.h"
#include "Data.h"

// RESIDENTE MENU //

PreceptorNameNode* getPreceptorNames() {
    User** allUsers = getAllUsers();
    if (allUsers==NULL){
        printf("[Erro ao obter usuarios]\n");
        return NULL;
    }
    PreceptorNameNode* head = NULL;
    for (int i=0; allUsers[i]!=NULL; i++) {
        if(allUsers[i]->level==2) {
            PreceptorNames* novoPreceptor = malloc(sizeof(PreceptorNames));
            strncpy(novoPreceptor->exhibitionName, allUsers[i]->exhibitionName, 100);
            novoPreceptor->exhibitionName[100] = '\0';
            strncpy(novoPreceptor->uniqueID, allUsers[i]->uniqueID, 50);
            novoPreceptor->uniqueID[50] = '\0';
            PreceptorNameNode* novoNode = malloc(sizeof(PreceptorNameNode));
            novoNode->preceptor = novoPreceptor;
            novoNode->next = NULL;
            if(head==NULL || strcmp(novoPreceptor->exhibitionName, head->preceptor->exhibitionName)<0) {
                novoNode->next = head;
                head = novoNode;
            }else{
                PreceptorNameNode* current = head;
                while (current->next!=NULL && strcmp(novoPreceptor->exhibitionName, current->next->preceptor->exhibitionName)>0) {
                    current = current->next;
                }
                novoNode->next = current->next;
                current->next = novoNode;
            }
        }
    }
    freeAllUsers(allUsers);
    return head;
}

bool solicitarAvaliacao(User* residente, User* preceptor) {
    if (preceptor==NULL || residente==NULL) {
        printf("[Preceptor ou residente invalido]\n");
        return false;
    }
    Avaliacao avaliacao;
    avaliacao.nota1 = 0;
    avaliacao.nota2 = 0;
    avaliacao.nota3 = 0;
    avaliacao.media = 0.0;
    strcpy(avaliacao.preceptorID, preceptor->uniqueID);
    strcpy(avaliacao.residenteID, residente->uniqueID);
    avaliacao.timestamp = time(NULL);
    avaliacao.avaliado = false; 
    return saveUserAvaliacoes(preceptor, avaliacao);
}

// PRECEPTOR MENU //

AvaliacaoNode* getAvaliacoesForPreceptor(char* preceptorID) {
    AvaliacaoNode* head = loadAvaliacoesForPreceptor(preceptorID);
    if (head==NULL){
        printf("[Nenhuma avaliacao solicitada]\n\n");
        return NULL;
    }
    AvaliacaoNode* sortedHead = NULL;
    AvaliacaoNode* current = head;
    while (current!=NULL){
        User* residente = getUserByUniqueID(current->avaliacao.residenteID);
        if (residente==NULL) {
            current = current->next;
            continue;
        }
        AvaliacaoNode* novoNode = (AvaliacaoNode*) malloc(sizeof(AvaliacaoNode));
        if (novoNode==NULL){
            return NULL;
        }
        novoNode->avaliacao = current->avaliacao;
        strncpy(novoNode->residenteName, residente->exhibitionName, 100);
        novoNode->residenteName[100] = '\0';
        novoNode->next = NULL;
        if (sortedHead==NULL || strcmp(novoNode->residenteName, sortedHead->residenteName)<0) {
            novoNode->next = sortedHead;
            sortedHead = novoNode;
        }else{
            AvaliacaoNode* sortedCurrent = sortedHead;
            while(sortedCurrent->next!=NULL && strcmp(novoNode->residenteName, sortedCurrent->next->residenteName)>0) {
                sortedCurrent = sortedCurrent->next;
            }
            novoNode->next = sortedCurrent->next;
            sortedCurrent->next = novoNode;
        }
        current = current->next;
    }
    AvaliacaoNode* temp = head;
    while(temp!=NULL){
        AvaliacaoNode* next = temp->next;
        free(temp);
        temp = next;
    }
    return sortedHead;
}

bool avaliarResidente(User* preceptor, User* residente, float nota1, float nota2, float nota3){
    if(preceptor == NULL || residente == NULL){
        printf("[Preceptor ou residente invalido]\n");
        return false;
    }
    Avaliacao avaliacao;
    avaliacao.nota1 = nota1;
    avaliacao.nota2 = nota2;
    avaliacao.nota3 = nota3;
    avaliacao.media = roundf((nota1 + nota2 + nota3) / 3.0 * 100) / 100;
    strcpy(avaliacao.preceptorID, preceptor->uniqueID);
    strcpy(avaliacao.residenteID, residente->uniqueID);
    avaliacao.timestamp = time(NULL);
    avaliacao.avaliado = true;
    return removeUserAvaliacoes(preceptor, avaliacao) && saveUserAvaliacoes(residente, avaliacao);
}

// GESTOR MENU //

// SIGNUP //

bool signup(char* fullName, int level) {
    if (fullName==NULL){
        return false;
    }
    char* final;
    while(isspace((unsigned char)*fullName)) fullName++;
    if(*fullName==0)  
        return false;
    final = fullName + strlen(fullName) - 1;
    while(final > fullName && isspace((unsigned char)*final)) final--;
    final[1] = '\0';
    if (strlen(fullName) == 0){
        return false;
    }

    if (strlen(fullName)>100){
        return false;
    }
    if (level<1 || level>3){
        return false;
    }
    User* user = NULL;
    bool createUserResult = createUser(&user, fullName, level);
    if (!createUserResult){
        return false;
    }
    bool saveUserResult = saveUser(user);
    if (!saveUserResult) {
        free(user);
        return false;
    }
    printUserInfo(user);
    bool exportUserInfoResult = exportUserInfo(user);
    if (!exportUserInfoResult){
        free(user);
        return false;
    }
    free(user);
    return true;
}

bool createUser(User** user, char* fullName, int level) {
    if (user==NULL || fullName==NULL) {
        return false;
    }
    *user = (User*)malloc(sizeof(User));
    if (*user==NULL){
        return false;
    }
    char* tempFullName = (char*)malloc(strlen(fullName) + 1);
    if(tempFullName==NULL) {
        free(*user);
        return false;
    }
    strcpy(tempFullName, fullName);
    int length = strlen(tempFullName);
    int upperCase = 1;
    for (int i=0; i<length; i++) {
        if (isspace(tempFullName[i])) {
            upperCase = 1;
        }else if(upperCase) {
            tempFullName[i] = toupper(tempFullName[i]);
            upperCase = 0;
        }else{
            tempFullName[i] = tolower(tempFullName[i]);
        }
    }
    strcpy((*user)->fullName, tempFullName);
    (*user)->level = level;
    char* password = createRandomPassword();
    strcpy((*user)->password, password);
    char* exhibitionName = createExhibitionName(tempFullName);
    strcpy((*user)->exhibitionName, exhibitionName);
    char* uniqueId = createUniqueID(tempFullName);
    strcpy((*user)->uniqueID, uniqueId);
    free(password);
    free(exhibitionName);
    free(uniqueId);
    return true;
}

char* createRandomPassword() {
    char *password = malloc(6);
    char possibleChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL));
    for (int i=0; i<5; i++) {
        password[i] = possibleChars[rand()%(sizeof(possibleChars)-1)];
    }
    password[5] = '\0';
    return password;
}

char* createExhibitionName(char* fullName) {
    char* exhibitionName = malloc((strlen(fullName)+1) * sizeof(char));
    char firstName[101] = "";
    char lastName[101] = "";
    char* firstSpace = strchr(fullName, ' ');
    char* lastSpace = strrchr(fullName, ' ');
    if (firstSpace != NULL) {
        strncpy(firstName, fullName, firstSpace - fullName);
        firstName[firstSpace - fullName] = '\0';
    } else {
        strcpy(firstName, fullName);
    }
    if (lastSpace != NULL) {
        strcpy(lastName, lastSpace +1);
    }
    exhibitionName[0] = '\0';
    if (strlen(firstName)>0){
        strcat(exhibitionName, firstName);
        if(strlen(lastName)>0) {
            strcat(exhibitionName, " ");
            strcat(exhibitionName, lastName);
        }
    }
    return exhibitionName;
}

char* createUniqueID(char* fullName) {
    int counter = 2;
    char tempID[51] = "";
    char *token = strtok(fullName, " ");
    char* uniqueID = malloc(sizeof(char) * 51);
    *uniqueID = '\0';
    while(token!=NULL){
        strncat(uniqueID, token, 1);
        token = strtok(NULL, " ");
    }
    for (int i=0; uniqueID[i]!='\0'; i++) {
        uniqueID[i] = tolower(uniqueID[i]);
    }
    strcpy(tempID, uniqueID);
    while (getUserByUniqueID(uniqueID)!=NULL) {
        snprintf(uniqueID, sizeof(char)*51, "%s%d", tempID, counter++);
    }
    return uniqueID;
}

// GET //

User* getUserByUniqueID(char* uniqueID) {
    if (uniqueID==NULL){
        printf("[ID invalido]\n");
        return NULL;
    }
    User** allUsers = getAllUsers();
    if (allUsers==NULL){
        printf("[Erro ao obter usuarios]\n");
        return NULL;
    }
    for (int i=0; allUsers[i]!=NULL; i++) {
        if (strcmp(allUsers[i]->uniqueID, uniqueID)==0) {
            User* user = allUsers[i];
            allUsers[i] = NULL; 
            freeAllUsers(allUsers);
            return user;
        }
    }
    freeAllUsers(allUsers);
    return NULL;
}

// FREE //

void freeAllUsers(User** users) {
    for (int i=0; users[i]!=NULL; i++) {
        freeUser(users[i]);
    }
    free(users);
}

void freeUser(User* user) {
    if (user==NULL){
        return;
    }
    free(user);
}