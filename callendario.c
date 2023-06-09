#include <stdio.h>
#include <stdlib.h>

#define MAX_DIAS 31
#define MAX_HORAS 24

struct Ponto {
    int dia;
    int mes;
    int hora_inicio;
    int hora_fim;
};

void exibirCalendario(int marcacoes[MAX_DIAS][MAX_HORAS]) {
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                   CALENDÁRIO                                                                                                          ║\n");
    printf("╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢\n");
    printf("║  MÊS ║ 1  2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  00  ║\n");
    printf("╟──────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢\n");

    for (int i = 1; i <= 12; i++) {
        printf("║  %2d  ║ ", i);
        for (int j = 0; j < 31; j++) {
            if (marcacoes[j][i - 1] == 1) {
                printf("|  X");
            } else {
                printf("|   ");
            }
        }
        printf("   ║\n");
    }

    printf("╚══════╩════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

void salvarPonto(struct Ponto ponto, int marcacoes[MAX_DIAS][MAX_HORAS]) {
    FILE *arquivo;
    arquivo = fopen("pontos.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "Data: %02d/%02d, Hora de início: %02d, Hora de término: %02d\n", ponto.dia, ponto.mes, ponto.hora_inicio, ponto.hora_fim);
    marcacoes[ponto.dia - 1][ponto.mes - 1] = 1;

    fclose(arquivo);
}

float calcularHorasTrabalhadas(struct Ponto *pontos, int total_pontos) {
    float horas_total = 0.0;

    for (int i = 0; i < total_pontos; i++) {
        int horas = pontos[i].hora_fim - pontos[i].hora_inicio;
        horas_total += horas;
    }

    return horas_total;
}

int main() {
    struct Ponto pontos[100];
    int total_pontos = 0;
    char opcao;

    int marcacoes[MAX_DIAS][MAX_HORAS] = {0}; 

    do {
        system("clear");  

        exibirCalendario(marcacoes);

        printf("\nDigite o dia (1-%d), mês (1-12), hora de início (0-23) e hora de término (0-23):\n", MAX_DIAS);
        scanf("%d %d %d %d", &pontos[total_pontos].dia, &pontos[total_pontos].mes, &pontos[total_pontos].hora_inicio, &pontos[total_pontos].hora_fim);

        if (pontos[total_pontos].dia < 1 || pontos[total_pontos].dia > MAX_DIAS || pontos[total_pontos].mes < 1 || pontos[total_pontos].mes > 12 ||
            pontos[total_pontos].hora_inicio < 0 || pontos[total_pontos].hora_inicio >= MAX_HORAS || pontos[total_pontos].hora_fim < 0 || pontos[total_pontos].hora_fim >= MAX_HORAS) {
            printf("Valores inválidos. Tente novamente.\n");
            continue;
        }

        salvarPonto(pontos[total_pontos], marcacoes);
        total_pontos++;

        printf("Deseja inserir outro ponto? (s/n): ");
        scanf(" %c", &opcao);
    } while (opcao == 's' || opcao == 'S');

    float total_horas = calcularHorasTrabalhadas(pontos, total_pontos);
    int horas = (int)total_horas;
    int minutos = (total_horas - horas) * 60;

    printf("Total de horas trabalhadas: %d horas e %d minutos\n", horas, minutos);

    return 0;
}
