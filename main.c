#include <stdio.h>
#include <string.h>

#include "src/01_presentation/presentation.h"
#include "src/02_application/application.h"
#include "src/03_data/data.h"

int main() {

    int ctrl=1;
    int n;

    do{
        scanf("%d", &n);
        if(n!=0){
            int square[n][n];
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    square[i][j]=1;
                }
            }
            for(int k=0;k<(n-1)/2;k++){
                for(int i=ctrl;i<(n-ctrl);i++){
                    for(int j=ctrl;j<(n-ctrl);j++){
                        square[i][j]=(ctrl+1);
                    }
                }
                ctrl++;
            }
            ctrl=1;
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    if(n==1){
                        printf("%3d\n", square[i][j]);
                    }else if(j==(n-1)){
                        printf(" %3d\n", square[i][j]);
                    }else if(j==0){
                        printf("%3d", square[i][j]);
                    }else{
                        printf(" %3d", square[i][j]);
                    }
                }
            }
            printf("\n");
        }
    }while(n!=0);
    return 0;
}