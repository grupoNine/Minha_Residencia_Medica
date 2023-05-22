#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/Presentation.h"
#include "src/Application.h"
#include "src/Data.h"

int main() {
    clear();
    int choice;
    while(1) {
        logo();
        printf("[1] Entrar\n[0] Fechar\n\n>>> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                User* user = loginInterface();
                if(user == NULL) {
                    clear();
                    break;
                } else {
                    clear();
                    userInterface(user);
                }
                break;
            case 0:
                clear();
                quitMsg();
                exit(0);
            default:
                clear();
                printf("[Opcao invalida]\n\n");
                break;
        }
    }
    return 0;
}