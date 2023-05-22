#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <stdbool.h>
#include "Application.h"
#include "data.h"

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

// GESTOR MENU //
void gestorMenu();
//signup//
bool signupInterface();
void printUserInfo(User* user);

// MISC //
void quitMsg();
void logo();
void clear();

#endif