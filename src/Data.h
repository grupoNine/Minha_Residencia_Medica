#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include <time.h>


// STRUCTS //
// user //
typedef struct User {
    char uniqueID[51];
    char fullName[101];
    char exhibitionName[101];
    char password[51];
    int level;
    time_t createdTime;
} User;

typedef struct Current {
    User* user;
} Current;

extern Current current;

// avaliacao //
typedef struct Avaliacao {
    float nota1;
    float nota2;
    float nota3;
    float media;
    char feedback[301];
    char preceptorID[51];
    char residenteID[51];
    time_t timestamp;
    bool avaliado;

} Avaliacao;

typedef struct AvaliacaoNode {
    struct AvaliacaoNode* next;
    Avaliacao avaliacao;
    char residenteName[101];
} AvaliacaoNode;

// preceptor //
typedef struct {
    char exhibitionName[101];
    char uniqueID[51];
} PreceptorNames;

typedef struct PreceptorNameNode {
    PreceptorNames* preceptor;
    struct PreceptorNameNode* next;
} PreceptorNameNode;

// quadro de avisos //
typedef struct Aviso {
    time_t timestamp;
    char mensagem[301];
    char username[101];
} Aviso;

// AMBIENTE DE APRENDIZAGEM //

typedef struct Atividade {
    char name[101];
    char description[1001];
    struct tm start_time;
    struct tm end_time;
    int weekday;

} Atividade;

typedef struct AtividadeNode {
    struct AtividadeNode* next;
    Atividade atividade;
} AtividadeNode;
typedef struct AmbienteAprendizagem {
    char uniqueID[51];
    char name[101];
    char description[1001];
    char preceptorID[51];
} AmbienteAprendizagem;

typedef struct AmbienteNode {
    struct AmbienteNode* next;
    AmbienteAprendizagem ambiente;
} AmbienteNode;

// FREQUENCIA //

typedef struct Frequencia {
    char residenteID[50];
    char data[11]; // DD/MM/YYYY
    char hora_inicio[6]; // HH:MM
    char hora_fim[6];   // HH:MM
} Frequencia;

// FUNCTIONS //

//ambiente//
bool saveAmbiente(AmbienteAprendizagem* ambiente);
AmbienteAprendizagem** getAllAmbientes();
void saveAtividadeForAmbiente(char* ambienteID, AtividadeNode* atividades);
bool exportAmbienteInfo(char* uniqueID);

//calendario//
void copyAtividadesToCalendario(char* ambienteUniqueID, char* residenteUniqueID);
AtividadeNode* getCalendario(const char* residenteID);

//frequencia//
void saveFrequencia(Frequencia *frequencia);
void exportFrequencias(int month);


// user //
bool saveUser(User* user);
User** getAllUsers();
bool exportUserInfo(User* user);

// avaliacao //
bool saveUserAvaliacoes(User* user, Avaliacao avaliacao);
bool removeUserAvaliacoes(User* user, Avaliacao avaliacao);
AvaliacaoNode* loadAvaliacoesForPreceptor(char* preceptorID);
void exportAvaliacoes(int month);

// quadro de avisos //

Aviso getAvisos();
bool saveAviso(Aviso aviso);

#endif