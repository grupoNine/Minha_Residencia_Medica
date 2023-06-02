#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Data.h"
#include "Application.h"
#include "Presentation.h"

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