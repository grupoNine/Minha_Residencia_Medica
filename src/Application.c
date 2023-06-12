#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "Application.h"
#include "Presentation.h"
#include "Data.h"


// QUADRO DE AVISOS //

Aviso readAviso() {
    return getAvisos();
}

void writeAviso() {
    char mensagem[301];
    char username[101];
    strncpy(username, current.user->exhibitionName, sizeof(username));
    printf("\nEscreva a mensagem (ate 300 caracteres):\n");
    fgets(mensagem, 301, stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0';
    Aviso aviso;
    aviso.timestamp = time(NULL);
    strncpy(aviso.mensagem, mensagem, sizeof(aviso.mensagem));
    strncpy(aviso.username, username, sizeof(aviso.username));
    bool saveResult = saveAviso(aviso);
    if(saveResult){
        printf("\nAviso salvo com sucesso!\n\n");
    }else{
        printf("\nErro ao salvar o aviso.\n\n");
    }
}

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
    strcpy(avaliacao.feedback, "feedback");
    strcpy(avaliacao.preceptorID, preceptor->uniqueID);
    strcpy(avaliacao.residenteID, residente->uniqueID);
    avaliacao.timestamp = time(NULL);
    avaliacao.avaliado = false; 
    return saveUserAvaliacoes(preceptor, avaliacao);
}

void marcarFrequencia(const char *residenteID) {
    Frequencia frequencia;
    strcpy(frequencia.residenteID, residenteID);
    time_t t;
    struct tm *timeinfo;
    time(&t);
    timeinfo = localtime(&t);
    sprintf(frequencia.data, "%02d/%02d/%04d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
    printf("Digite a hora de chegada (HH:MM):\n\n>>> ");
    scanf("%5s", frequencia.hora_inicio);
    printf("Digite a hora de saida (HH:MM):\n\n>>> ");
    scanf("%5s", frequencia.hora_fim);
    saveFrequencia(&frequencia);
}

// PRECEPTOR MENU //
// AVALIACAO //
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

bool avaliarResidente(User* preceptor, User* residente, float nota1, float nota2, float nota3, char* feedback){
    if(preceptor == NULL || residente == NULL){
        printf("[Preceptor ou residente invalido]\n");
        return false;
    }
    Avaliacao avaliacao;
    avaliacao.nota1 = nota1;
    avaliacao.nota2 = nota2;
    avaliacao.nota3 = nota3;
    avaliacao.media = roundf((nota1 + nota2 + nota3) / 3.0 * 100) / 100;
    strncpy(avaliacao.feedback, feedback, 300);
    strcpy(avaliacao.preceptorID, preceptor->uniqueID);
    strcpy(avaliacao.residenteID, residente->uniqueID);

    avaliacao.timestamp = time(NULL);
    avaliacao.avaliado = true;
    return removeUserAvaliacoes(preceptor, avaliacao) && saveUserAvaliacoes(residente, avaliacao);
}

// AMBIENTE DE APRENDIZAGEM //

void createAmbienteAprendizagem() {
    printf("CRIAR AMBIENTE DE APRENDIZAGEM\n\n");
    AmbienteAprendizagem* newAmbiente = malloc(sizeof(AmbienteAprendizagem));
    if(newAmbiente == NULL){
        printf("[Erro de alocacao de memoria]\n");
        return;
    }
    printf("Nome do Ambiente de Aprendizagem:\n>>> ");
    scanf("%50[^\n]", newAmbiente->name);
    getchar();
    printf("\nDescricao do Ambiente de Aprendizagem:\n>>> ");
    scanf("%1000[^\n]", newAmbiente->description);
    getchar(); 
    strcpy(newAmbiente->preceptorID, current.user->uniqueID);
    char* uniqueID = createUniqueIDForAmbiente(newAmbiente->name);
    strcpy(newAmbiente->uniqueID, uniqueID);
    free(uniqueID);
    clear();
    bool success = saveAmbiente(newAmbiente);
    if(success){
        printf("[Ambiente de Aprendizagem criado com sucesso]\n\n");
    }else{
        printf("[Erro ao criar Ambiente de Aprendizagem]\n\n");
    }
    free(newAmbiente);
}

char* createUniqueIDForAmbiente(char* fullName) {
    int counter = 2;
    char tempID[51] = "";
    char nameCopy[51] = "";
    strncpy(nameCopy, fullName, 50);
    nameCopy[50] = '\0';
    char *token = strtok(nameCopy, " ");
    char* uniqueID = malloc(sizeof(char) * 51);
    *uniqueID = '\0';
    while(token!=NULL){
        strncat(uniqueID, token, 1);
        token = strtok(NULL, " ");
    }
    for (int i=0; uniqueID[i]!='\0'; i++){
        uniqueID[i] = tolower(uniqueID[i]);
    }
    strncpy(tempID, uniqueID, 50);
    tempID[50] = '\0';
    while (getAmbienteByUniqueID(uniqueID)!=NULL) {
        snprintf(uniqueID, 50, "%s%d", tempID, counter++);
    }
    return uniqueID;
}

AmbienteAprendizagem* getAmbienteByUniqueID(char* uniqueID) {
    if (uniqueID ==NULL){
        printf("[ID invalido]\n");
        return NULL;
    }
    AmbienteAprendizagem** allAmbientes = getAllAmbientes();
    if (allAmbientes==NULL){
        printf("[Erro ao obter ambientes]\n");
        return NULL;
    }
    AmbienteAprendizagem* ambiente = NULL;
    for (int i=0; allAmbientes[i]!=NULL; i++){
        if (strcmp(allAmbientes[i]->uniqueID, uniqueID)==0) {
            ambiente = allAmbientes[i];
            allAmbientes[i] = NULL;
            break;
        }
    }
    freeAllAmbientes(allAmbientes);
    return ambiente;
}

AmbienteAprendizagem** getAllAmbientesForPreceptor(){
    AmbienteAprendizagem** allAmbientes = getAllAmbientes();
    if (allAmbientes == NULL){
        return NULL;
    }
    int count = 0;
    for (int i=0; allAmbientes[i]!=NULL; i++) {
        if (strcmp(allAmbientes[i]->preceptorID, current.user->uniqueID) == 0) {
            count++;
        }
    }
    AmbienteAprendizagem** preceptorAmbientes = malloc((count+1)*sizeof(AmbienteAprendizagem*));
    int j=0;
    for (int i=0; allAmbientes[i]!=NULL; i++) {
        if (strcmp(allAmbientes[i]->preceptorID, current.user->uniqueID)==0){
            preceptorAmbientes[j] = allAmbientes[i];
            j++;
        } else {
            free(allAmbientes[i]);
        }
    }
    preceptorAmbientes[count] = NULL;
    free(allAmbientes);
    return preceptorAmbientes;
}

void exportAmbiente(char* uniqueID) {
    bool exportSuccessful = exportAmbienteInfo(uniqueID);
    if (exportSuccessful){
        printf("[Ambiente exportado com sucesso]\n\n");
    } else {
        printf("[Falha ao exportar o ambiente]\n\n");
    }
}

void freeAllAmbientes(AmbienteAprendizagem** ambientes) {
    for (int i=0; ambientes[i]!=NULL; i++) {
        free(ambientes[i]);
    }
    free(ambientes);
}

//atividades//
AtividadeNode* createAtividade(char* ambienteID) {
    AtividadeNode* atividades = NULL;
    AtividadeNode* last = NULL;
    char name[101], description[1001];
    int daysPerWeek;
    
    printf("Nome da Atividade:\n>>> ");
    scanf("%100[^\n]", name);
    getchar();
    printf("\n\nDescricao da Atividade:\n>>> ");
    scanf("%1000[^\n]", description);
    getchar();
    printf("Quantos vezes por semana esta atividade ocorrera?\n\n>>> ");
    scanf("%d", &daysPerWeek);
    getchar();
    for (int i=0;i<daysPerWeek;i++){
        printf("Ocorrencia %d da atividade.\n", i+1);
        printf("Escolha o dia da semana:\n");
        printf("[1] Segunda-feira\n");
        printf("[2] Terca-feira\n");
        printf("[3] Quarta-feira\n");
        printf("[4] Quinta-feira\n");
        printf("[5] Sexta-feira\n");
        printf("[6] Sabado\n");
        printf("[7] Domingo\n\n>>> ");
        int weekday;
        scanf("%d",&weekday);
        getchar();
        if(weekday<1||weekday>7) {
            printf("Dia da semana inválido. Tente novamente.\n");
            i--;
            continue;
        }
        struct tm start_time, end_time;
        printf("Hora de inicio (HH:MM): ");
        scanf("%d:%d", &start_time.tm_hour, &start_time.tm_min);
        getchar();
        printf("Hora de termino (HH:MM): ");
        scanf("%d:%d", &end_time.tm_hour, &end_time.tm_min);
        getchar();
        AtividadeNode* newNode = malloc(sizeof(AtividadeNode));
        strcpy(newNode->atividade.name, name);
        strcpy(newNode->atividade.description, description);
        newNode->atividade.weekday=weekday;
        newNode->atividade.start_time=start_time;
        newNode->atividade.end_time=end_time;
        newNode->next = NULL;
        if (atividades == NULL) {
            atividades = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;
    }
    saveAtividadeForAmbiente(ambienteID, atividades);
    return atividades;
}

// calendario - residente //

void sortCalendario(AtividadeNode** head) {
    if (*head ==NULL || (*head)->next ==NULL) {
        return;
    }
    int trocado;
    AtividadeNode *ptr1;
    AtividadeNode *last = NULL;
    do {
        trocado = 0;
        ptr1 = *head;
        while (ptr1->next != last) {
            if (ptr1->atividade.weekday > ptr1->next->atividade.weekday ||
                (ptr1->atividade.weekday==ptr1->next->atividade.weekday &&
                (ptr1->atividade.start_time.tm_hour > ptr1->next->atividade.start_time.tm_hour ||
                (ptr1->atividade.start_time.tm_hour==ptr1->next->atividade.start_time.tm_hour &&
                ptr1->atividade.start_time.tm_min > ptr1->next->atividade.start_time.tm_min)))) {
                Atividade temp = ptr1->atividade;
                ptr1->atividade = ptr1->next->atividade;
                ptr1->next->atividade = temp;
                trocado = 1;
            }
            ptr1 = ptr1->next;
        }
        last = ptr1;
    } while (trocado);
}


void selecionarAmbienteAprendizagemMenu() {
    AmbienteAprendizagem** ambientes = getAllAmbientes();
    if(ambientes==NULL){
        clear();
        printf("[Erro ao obter ambientes]\n");
        return;
    }

    printf("Selecione o ambiente de aprendizagem:\n\n");
    int i;
    for(i=0; ambientes[i]!=NULL; i++){
        printf("[%d] %s\n", i+1, ambientes[i]->name);
    }
    int count = i;
    int choice;
    printf("[0] Voltar\n\n>>> ");
    scanf("%d", &choice);
    getchar();
    if(choice==0){
        clear();
        return;
    }else if(choice>0 && choice<=count){
        clear();
        copyAtividadesToCalendario(ambientes[choice-1]->uniqueID, current.user->uniqueID);
    } else {
        clear();
        printf("[Opcao invalida]\n\n");
    }
}
// GESTOR MENU //

// FREQUENCIA //

void exportFrequenciasMenu() {
    int mes;
    printf("Digite o mes dejado (1-12):\n\n>>> ");
    scanf("%d", &mes);
    getchar();
    if (mes<1 || mes>12) {
        printf("[Numero de mes invalido]\n");
        return;
    }
    exportFrequencias(mes);
}

// AVALIACAO //

void exportAvaliacoesMenu() {
    int mes;
    printf("Digite o mes desejado (1-12):\n\n>>> ");
    scanf("%d", &mes);
    getchar();  
    if (mes<1 || mes>12) {
        printf("[Numero de mes invalido]\n");
        return;
    }
    exportAvaliacoes(mes);
}


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