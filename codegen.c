#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char icode[10][30], res[10], op1[10], op2[10], opr;
    int n;
    printf("Enter the number of intermediate statements\n");
    scanf("%d", &n);
    printf("Enter the intermediate statements\n");
    for (int i = 0; i < n; ++i)
        scanf("%s", icode[i]);
    printf("\n\n\n");
    for (int i = 0; i < n; i++) {
        int j = 0, k = 0;
        while (icode[i][j] != '=') {
            res[k] = icode[i][j];
            j++;
            k++;
        }
        res[k] = '\0';
        j++; //will be pointing to '='
        if (icode[i][j] == '-') {
            j++; 
            k = 0;
            while (icode[i][j] != '\0') {
                op1[k] = icode[i][j];
                k++;
                j++;
            }
            op1[k] = '\0';
            printf("LOAD R1,%s\n", op1 );
            printf("NEG R1\n");
            printf("STORE %s,R1\n", res );
            printf("\n\n");
        }
        else {
            k = 0;
            while (icode[i][j] != '+' && icode[i][j] != '-' && icode[i][j] != '\0') {
                op1[k] = icode[i][j];
                k++;
                j++;
            }
            op1[k] = '\0';
            if (icode[i][j] == '\0') {
                printf("LOAD R4,%s\n", op1);
                printf("STORE %s,R4\n", res);
                printf("\n\n");
                continue;
            }
            else {
                opr = icode[i][j];
                j++; k = 0;
                while (icode[i][j] != '\0') {
                    op2[k] = icode[i][j];
                    j++;
                    k++;
                }
                op2[k] = '\0';
                switch (opr) {
                case '+': printf("LOAD R2,%s\n", op1 );
                    printf("LOAD R3,%s\n", op2);
                    printf("ADD R1,R1,R2\n");
                    printf("STORE %s,R1\n", res );
                    break;
                case '-': printf("LOAD R2,%s\n", op1 );
                    printf("LOAD R3,%s\n", op2);
                    printf("SUB R1,R1,R2\n");
                    printf("STORE %s,R1\n", res );
                    break;
                default: printf("Invalid statement\n");
                }
            }
            printf("\n\n");
        }
    }
    return 0;
}

/*
t1=-b
t2=c+d
t3=t1+t2
a=t3


*/