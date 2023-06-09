#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <stdbool.h>
#include "Application.h"

// LOGIN  //
User* loginInterface();
void userInterface(User* user);

//RESIDENTE MENU //
void residenteMenu();
//avaliacao//
void solicitarAvaliacaoMenu();

// PRECEPTOR MENU //
void preceptorMenu();
//avaliacao//
void listResidentesForAvaliacao();
void avaliarResidenteMenu(char* residenteID);
//ambiente de aprendizagem//
void ambienteAprendizagemMenu();
void listAmbienteMenu();
void editarAmbienteMenu(AmbienteAprendizagem* ambiente);


// GESTOR MENU //
void gestorMenu();
//signup//
bool signupInterface();
void printUserInfo(User* user);

// QUADRO DE AVISOS //
void quadroDeAvisosMenu();

// MISC //
void quitMsg();
void logo();
void clear();

#endif