#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdbool.h>
#include "Data.h"


// QUADRO DE AVISOS //
Aviso readAviso();
void writeAviso();


// RESIDENTE MENU //
//avaliacao//
PreceptorNameNode* getPreceptorNames();
bool solicitarAvaliacao(User* residente, User* preceptor);

// PRECEPTOR MENU //
//avaliacao//
AvaliacaoNode* getAvaliacoesForPreceptor(char* preceptorID) ;
bool avaliarResidente(User* preceptor, User* residente, float nota1, float nota2, float nota3, char* feedback);


// GESTOR MENU //
//signup//
bool signup(char* fullName, int level);
bool createUser(User** user, char* fullName, int level);
char* createRandomPassword();
char* createExhibitionName(char* fullName);
char* createUniqueID(char* fullName);

// GET //
User* getUserByUniqueID(char* uniqueID);

// FREE //
void freeAllUsers(User** users);
void freeUser(User* user);

#endif