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

// FUNCTIONS //
// user //
bool saveUser(User* user);
User** getAllUsers();
bool exportUserInfo(User* user);

// avaliacao //
bool saveUserAvaliacoes(User* user, Avaliacao avaliacao);
bool removeUserAvaliacoes(User* user, Avaliacao avaliacao);
AvaliacaoNode* loadAvaliacoesForPreceptor(char* preceptorID);
bool saveUser(User* user);



#endif