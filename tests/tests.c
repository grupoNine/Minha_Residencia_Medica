#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "../src/Data.h"
#include "../src/Application.h"
#include "../src/Presentation.h"

// Os testes unitarios abaixo lêem o db
// Coloco eles no inicio e no final para comparar
// Os proximos testes podem escrever no db
// Então é preciso verificar e remover manualmente no db após os testes
void test_getPreceptorNames() {
    PreceptorNameNode* preceptorNames = getPreceptorNames();
    PreceptorNameNode* head = preceptorNames;

    printf("\n\n------ Nomes de Preceptores ------\n");
    printf("---------------------------------\n");
    int count = 1;
    while (preceptorNames != NULL) {
        printf("Preceptor %d\n", count);
        printf("Nome de Exibição: %s\n", preceptorNames->preceptor->exhibitionName);
        printf("ID Único: %s\n", preceptorNames->preceptor->uniqueID);
        printf("---------------------------------\n");
        preceptorNames = preceptorNames->next;
        count++;
    }

    PreceptorNameNode* node = head;
    while (node != NULL) {
        PreceptorNameNode* nextNode = node->next;
        free(node->preceptor);
        free(node);
        node = nextNode;
    }
}

void test_getAllUsers() {
    User** users = getAllUsers();

    if(users==NULL) {
        printf("TESTE FALHOU!\n");
        return;
    }
}

// Testar o signup
// Este teste de integração testa o signup desde o input até o db
// É importante verificar manualmente o db para checar o teste
// e remover os usuários criados no processo.
// Serve também como teste unitário para:
// signup(), createUser(), saveUser(), 
// createRandomPassword(), createExhibitionName() e createUniqueID()

void print_resultado(bool resultado, bool esperado) {
    if (resultado==esperado) {
        printf("\n  [Teste bem sucedido]  \n");
    } else {
        printf("\n  [XXX Teste falhou XXX]  \n");
    }
}

void test_signup() {
    int level;
    bool resultado;

    // Teste 0: Nome ok, level ok
    char fullName0[] = "-----------TESTE INICIALIZADO TESTE INICIALIZADO---------";
    printf("\n\n------ Teste 0 : Nome ok, level ok ------\n");
    level = 2;
    resultado = signup(fullName0, level);
    print_resultado(resultado, true);

    // Teste 1: fullName=NULL
    char fullName1[1] = "";
    printf("\n\n------ Teste 1 : fullName=NULL ------\n");
    level = 1;
    resultado = signup(fullName1, level);
    print_resultado(resultado, false);

    // Teste 2: nome com mais de 100 caracteres
    char fullName2[200];
    strncpy(fullName2, "Um nome muito muito muito muito muito longo longo longo longo longo com mais de cem caracteres que deve retornar falso", sizeof(fullName2) - 1);
    fullName2[sizeof(fullName2) - 1] = '\0';
    printf("\n\n------ Teste 2 : nome com mais de 100 caracteres ------\n");
    level = 3;
    resultado = signup(fullName2, level);
    print_resultado(resultado, false);

    // Teste 3: nome com 1 letra
    char fullName3[] = "a";
    printf("\n\n------ Teste 3 : nome com 1 letra ------\n");
    level = 2;
    resultado = signup(fullName3, level);
    print_resultado(resultado, true);

    // Teste 4: nome com whitespace no inicio e no final
    char fullName4[] = " abcd ";
    printf("\n\n------ Teste 4 : nome com whitespace no inicio e no final ------\n");
    level = 1;
    resultado = signup(fullName4, level);
    print_resultado(resultado, true);

    // Teste 5: level <1
    char fullName5[] = "abcd";
    printf("\n\n------ Teste 5 : level < 1 ------\n");
    level = 0;
    resultado = signup(fullName5, level);
    print_resultado(resultado, false);

    // Teste 6: level >3
    char fullName6[] = "abcd";
    printf("\n\n------ Teste 6 : level > 3 ------\n");
    level = 4;
    resultado = signup(fullName6, level);
    print_resultado(resultado, false);

    // Teste 7: level com float // este teste falha e não compensa sua correção
    char fullName7[] = "abcd";
    printf("\n\n------ Teste 7 : level com float ------\n");
    level = 1.5;
    resultado = signup(fullName7, level);
    print_resultado(resultado, false);

    // Teste 8: nome com 100 caracteres sem espaços em branco
    char fullName8[101];
    strncpy(fullName8, "Aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", sizeof(fullName8) - 1);
    fullName8[sizeof(fullName8) - 1] = '\0';
    printf("\n\n------ Teste 8 : nome com 100 caracteres sem espaços em branco ------\n");
    level = 1;
    resultado = signup(fullName8, level);
    print_resultado(resultado, true);

    // Teste 9: nome com 1 letra e 1 espaço em branco repetidamente até um total de 100 caracteres
    char fullName9[101];
    for (int i=0; i<50; i+=2) {
        fullName9[i] = 'a';
        fullName9[i+1] = ' ';
    }
    fullName9[101] = '\0';
    printf("\n\n------ Teste 9 : nome com 1 letra e 1 espaço em branco repetidamente até um total de 100 caracteres ------\n");
    level = 1;
    resultado = signup(fullName9, level);
    print_resultado(resultado, true);

    // Teste 10: Teste finalizado
    char fullName10[] = "-----------TESTE FINALIZADO TESTE FINALIZADO---------";
    printf("\n\n------ Teste 10 : TESTE FINALIZADO ------\n");
    level = 1;
    resultado = signup(fullName10, level);
    print_resultado(resultado, true);
}

//

int main(void) {
    int sucesso = 0;
    int falha = 0;
    printf("\n\n====== INICIANDO TESTES ======\n\n");
    printf("\n\n============================================================\n\n>>>Testando getPreceptorNames()\n");
    test_getPreceptorNames();

    printf("\n\n============================================================\n\n>>>Testando signup()\n");
    test_signup();

    printf("\n\n============================================================\n\n>>>Testando getPreceptorNames() novamente\n");
    test_getPreceptorNames();

    printf("\n\n====== TESTES CONCLUIDOS ======\n");
    return 0;
}
