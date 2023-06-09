#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Data.h"
#include "Application.h"
#include "Presentation.h"

// AMBIENTE DE APRENDIZAGEM //

//ambiente//
bool saveAmbiente(AmbienteAprendizagem* ambiente) {
    char filename[100] = "db/ambientes/ambientes.txt";
    FILE* fp =fopen(filename, "a");
    if (fp == NULL) {
        printf("[Erro ao abrir o arquivo]\n");
        return false;
    }
    fprintf(fp, "UNIQUE_ID: %s\n", ambiente->uniqueID);
    fprintf(fp, "NOME: %s\n", ambiente->name);
    fprintf(fp, "DESCRICAO: %s\n", ambiente->description);
    fprintf(fp, "PRECEPTOR_ID: %s\n", ambiente->preceptorID);
    fprintf(fp, "----------------\n");
    fclose(fp);
    return true;
}

AmbienteAprendizagem** getAllAmbientes() {
    FILE *fp=fopen("db/ambientes/ambientes.txt", "r");
    if (!fp){
        printf("[Erro ao abrir o arquivo]\n");
        return NULL;
    }
    char line[300];
    int count=0;
    AmbienteAprendizagem** ambientes=NULL;
    while(fgets(line, sizeof(line), fp)) {
        if (strstr(line, "UNIQUE_ID:")==line) {
            AmbienteAprendizagem* ambiente =malloc(sizeof(AmbienteAprendizagem));
            sscanf(line, "UNIQUE_ID: %s\n", ambiente->uniqueID);
            fgets(line, sizeof(line), fp); 
            sscanf(line, "NOME: %100[^\n]",ambiente->name);
//
            fgets(line, sizeof(line), fp);
            char *descricaoStart = strchr(line, ':');
            if (descricaoStart && *(descricaoStart+1)== ' '){
                descricaoStart+=2;
            }else if(descricaoStart){
                descricaoStart+=1;
            }
            snprintf(ambiente->description, sizeof(ambiente->description), "%s", descricaoStart);
//
            fgets(line, sizeof(line), fp);
            sscanf(line, "PRECEPTOR_ID: %s\n", ambiente->preceptorID);
            ambientes = realloc(ambientes,(count+1)*sizeof(AmbienteAprendizagem*));
            ambientes[count]=ambiente;
            count++;
        }
    }
    fclose(fp);
    ambientes = realloc(ambientes, (count+1)*sizeof(AmbienteAprendizagem*));
    ambientes[count]=NULL;
    return ambientes;
}

void saveAtividadeForAmbiente(char* ambienteID, AtividadeNode* atividades) {
    char filename[100];
    FILE *file;
    sprintf(filename, "db/ambientes/atividades_%s.txt", ambienteID);
    file = fopen(filename, "a");
    if (file==NULL) {
        printf("Nao foi possível abrir o arquivo %s\n", filename);
        return;
    }
    AtividadeNode* currentNode=atividades;
    while(currentNode!=NULL){
        fprintf(file, "Nome: %s\n", currentNode->atividade.name);
        fprintf(file, "Descricao: %s\n", currentNode->atividade.description);
        fprintf(file, "Dia da semana: %d\n", currentNode->atividade.weekday);
        fprintf(file, "Hora de inicio: %02d:%02d\n", currentNode->atividade.start_time.tm_hour, currentNode->atividade.start_time.tm_min);
        fprintf(file, "Hora de termino: %02d:%02d\n", currentNode->atividade.end_time.tm_hour, currentNode->atividade.end_time.tm_min);
        fprintf(file, "\n");
        currentNode = currentNode->next;
    }
    fclose(file);
    clear();
    printf("[Ambiente salvo com sucesso]\n\n");
}
bool exportAmbienteInfo(char* uniqueID) {
    char exportFilename[100];
    FILE *exportFile;
    AmbienteAprendizagem** allAmbientes = getAllAmbientes();
    if (allAmbientes==NULL){
        printf("[Noa foi possivel obter os ambientes]\n");
        return false;
    }
    AmbienteAprendizagem* selectedAmbiente=NULL;
    for (int i=0; allAmbientes[i]!=NULL;i++){
        if (strcmp(allAmbientes[i]->uniqueID, uniqueID)==0) {
            selectedAmbiente=allAmbientes[i];
            break;
        }
    }
    if (selectedAmbiente==NULL){
        printf("[Ambiente não encontrado]\n");
        return false;
    }
    sprintf(exportFilename, "export/ambienteinfo_%s.txt", uniqueID);
    exportFile = fopen(exportFilename, "w");
    if(exportFile==NULL) {
        printf("[Nao foi possivel abrir o arquivo para exportacao %s]\n", exportFilename);
        return false;
    }
    fprintf(exportFile, "ID: %s\n", selectedAmbiente->uniqueID);
    fprintf(exportFile, "Nome: %s\n", selectedAmbiente->name);
    fprintf(exportFile, "Descricao: %s\n", selectedAmbiente->description);
    fprintf(exportFile, "Preceptor: %s\n\n", selectedAmbiente->preceptorID);
    char filename[100];
    sprintf(filename, "db/ambientes/atividades_%s.txt", selectedAmbiente->uniqueID);
    FILE* atividadesFile = fopen(filename, "r");
    if (atividadesFile==NULL){
        fclose(exportFile);
        printf("[Nao foi possivel abrir o arquivo de atividades]\n");
        return false;
    }
    char line[300];
    fprintf(exportFile, "Atividades:\n");
    while (fgets(line, sizeof(line), atividadesFile)) {
        fprintf(exportFile, "\t%s", line);
    }
    fclose(exportFile);
    fclose(atividadesFile);
    return true;
}

// QUADRO DE AVISOS //
Aviso getAvisos() {
    FILE* fp = fopen("db/quadro_de_avisos/quadro_de_avisos.txt", "r");
    Aviso aviso;
    if (!fp) {
        printf("[Erro ao abrir o arquivo]\n");
        return aviso;
    }
    fscanf(fp, "%ld|%100[^|]|%300[^\n]", &(aviso.timestamp), aviso.username, aviso.mensagem);
    fclose(fp);
    return aviso;
}

bool saveAviso(Aviso aviso) {
    FILE* fp = fopen("db/quadro_de_avisos/quadro_de_avisos.txt", "w");
    if (!fp) {
        printf("[Erro ao abrir o arquivo]\n");
        return false;
    }
    fprintf(fp, "%ld|%s|%s\n", aviso.timestamp, aviso.username, aviso.mensagem);
    fclose(fp);
    return true;
}
// AVALIACAO //

bool saveUserAvaliacoes(User* user, Avaliacao avaliacao) {
    char path[200];
    if(user->level==1){
        sprintf(path, "db/avaliacoes_residentes/avaliacoes_%s.txt", user->uniqueID);
    }else if(user->level==2){
        sprintf(path, "db/avaliacoes_preceptores/avaliacoes_%s.txt", user->uniqueID);
    }else{
        printf("[Erro ao definir o caminho do arquivo]\n");
        return false;
    }
    FILE *fp = fopen(path, "a");
    if (fp!=NULL) {
        fprintf(fp, "%f|%f|%f|%f|%s|%s|%s|%ld|%d\n", avaliacao.nota1, avaliacao.nota2, avaliacao.nota3, avaliacao.media, avaliacao.feedback, avaliacao.preceptorID, avaliacao.residenteID, (long)avaliacao.timestamp, avaliacao.avaliado);
        fclose(fp);
        return true;
    }else{
        printf("[Erro ao abrir o arquivo]\n");
        fclose(fp);
        return false;
    }
}
bool removeUserAvaliacoes(User* user, Avaliacao avaliacao) {
    char path[200];
    if(user->level==2){
        sprintf(path, "db/avaliacoes_preceptores/avaliacoes_%s.txt", user->uniqueID);
    } else {
        printf("[Erro ao definir o caminho do arquivo]\n");
        return false;
    }
    FILE *fp = fopen(path, "r");
    if (fp==NULL) {
        printf("[Erro ao abrir o arquivo]\n");
        return false;
    }
    char tempPath[200];
    sprintf(tempPath, "%s.temp", path);
    FILE *fpTemp = fopen(tempPath, "w");
    if (fpTemp==NULL) {
        printf("[Erro ao abrir o arquivo temporario]\n");
        fclose(fp);
        return false;
    }
    Avaliacao tempAvaliacao;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%f|%f|%f|%f|%[^|]|%[^|]|%[^|]|%ld|%d", &tempAvaliacao.nota1, &tempAvaliacao.nota2, &tempAvaliacao.nota3, &tempAvaliacao.media, tempAvaliacao.feedback, tempAvaliacao.preceptorID, tempAvaliacao.residenteID, (long*)&tempAvaliacao.timestamp, &tempAvaliacao.avaliado);
        if (strcmp(tempAvaliacao.preceptorID, avaliacao.preceptorID) != 0 || strcmp(tempAvaliacao.residenteID, avaliacao.residenteID) != 0) {
            fprintf(fpTemp, "%s", line);
        }
    }
    fclose(fp);
    fclose(fpTemp);
    remove(path);
    rename(tempPath, path);
    return true;
}
AvaliacaoNode* loadAvaliacoesForPreceptor(char* preceptorID) {
    char path[200];
    sprintf(path, "db/avaliacoes_preceptores/avaliacoes_%s.txt", preceptorID);
    FILE *fp = fopen(path, "r");
    if (fp==NULL) {
        printf("[Erro ao abrir o arquivo]\n");
        return NULL;
    }
    char line[300];
    AvaliacaoNode* head = NULL;
    while (fgets(line, sizeof(line), fp)) {
        Avaliacao avaliacao;
        sscanf(line, "%f|%f|%f|%f|%[^|]|%[^|]|%[^|]|%ld|%d", &avaliacao.nota1, &avaliacao.nota2, &avaliacao.nota3, &avaliacao.media, avaliacao.feedback, avaliacao.preceptorID, avaliacao.residenteID, &(avaliacao.timestamp), &(avaliacao.avaliado));
        AvaliacaoNode* novoNode = malloc(sizeof(AvaliacaoNode));
        novoNode->avaliacao = avaliacao;
        novoNode->next = NULL;
        if(head==NULL) {
            head = novoNode;
        }else{
            AvaliacaoNode* current = head;
            while (current->next!=NULL) {
                current = current->next;
            }
            current->next = novoNode;
        }
    }
    fclose(fp);
    return head;
}

// USER //

bool saveUser(User* user) {
    FILE *fp = fopen("db/users/users.txt", "a");
    if(fp!=NULL){
        time_t currentTime = time(NULL);
        user->createdTime = currentTime;
        fprintf(fp, "%s|%s|%s|%s|%d|%ld\n", user->uniqueID, user->fullName, user->exhibitionName, user->password, user->level, (long)user->createdTime);
        fclose(fp);
        return true;
    }else{
        printf("[Erro ao abrir o arquivo]\n");
        return false;
    }
}

User** getAllUsers(){
    FILE *fp = fopen("db/users/users.txt", "r");
    if (!fp) {
        printf("[Erro ao abrir o arquivo]\n");
        return NULL;
    }
    char line[300];
    int count = 0;
    User** users = NULL;
    while(fgets(line, sizeof(line), fp)) {
        User* user = malloc(sizeof(User));
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%ld\n", user->uniqueID, user->fullName, user->exhibitionName, user->password, &(user->level), &(user->createdTime));
        users = realloc(users, (count + 1) * sizeof(User*));
        users[count] = user;
        count++;
    }
    fclose(fp);
    users = realloc(users, (count + 1) * sizeof(User*));
    users[count] = NULL;
    return users;
}

bool exportUserInfo(User* user) {
    char path[200];
    sprintf(path, "export/userinfo_%s.txt", user->uniqueID);
    FILE* fp = fopen(path, "w");
    if (fp!=NULL){
        fprintf(fp, "[Informacoes do usuario]\n");
        fprintf(fp, "ID Unico: %s\n", user->uniqueID);
        fprintf(fp, "Nome Completo: %s\n", user->fullName);
        fprintf(fp, "Nome de Exibicao: %s\n", user->exhibitionName);
        fprintf(fp, "Senha: %s\n", user->password);
        fprintf(fp, "Nivel de Acesso: %d\n", user->level);
        char timestamp[26];
        strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %H:%M:%S", localtime(&(user->createdTime)));
        fprintf(fp, "Data de Criacao: %s\n", timestamp);
        fclose(fp);
        return true;
    }else{
        printf("[Erro ao abrir o arquivo]\n");
        return false;
    }
}