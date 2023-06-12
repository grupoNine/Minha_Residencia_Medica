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
//frequencia//
void marcarFrequencia(const char *residenteID);
// ambiente aprendizagem //
void sortCalendario(AtividadeNode** head);
void selecionarAmbienteAprendizagemMenu();

// PRECEPTOR MENU //
//avaliacao//
AvaliacaoNode* getAvaliacoesForPreceptor(char* preceptorID) ;
bool avaliarResidente(User* preceptor, User* residente, float nota1, float nota2, float nota3, char* feedback);

//ambiente de aprendizagem//
void createAmbienteAprendizagem();
char* createUniqueIDForAmbiente(char* fullName);
AmbienteAprendizagem* getAmbienteByUniqueID(char* uniqueID);
AmbienteAprendizagem** getAllAmbientesForPreceptor();
void exportAmbiente(char* uniqueID);
void freeAllAmbientes(AmbienteAprendizagem** ambientes);

//atividades//
AtividadeNode* createAtividade(char* ambienteID);


// GESTOR MENU //
//signup//
bool signup(char* fullName, int level);
bool createUser(User** user, char* fullName, int level);
char* createRandomPassword();
char* createExhibitionName(char* fullName);
char* createUniqueID(char* fullName);
//frequencia//
void exportFrequenciasMenu();
//avaliacao//
void exportAvaliacoesMenu();

// GET //
User* getUserByUniqueID(char* uniqueID);

// FREE //
void freeAllUsers(User** users);
void freeUser(User* user);

#endif