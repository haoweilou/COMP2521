#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    if(argc == 2) {
        int a = atoi(argv[1]);
        if (a >= 1) {
            for(int b = 1; b <= a; b++) {
                printf("%d ",b);
            }
        } else {
            for(int b = 1; b >= a; b--) {
                printf("%d ",b);
            }
        }
    } else if(argc == 3) {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        if (a >= b) {
            for(a; a >= b; a--) {
                printf("%d ",a);
            }
        } else {
            for(a; a <= b; a++) {
                printf("%d ",a);
            }
        }
    } else if (argc == 4) {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        int c = atoi(argv[3]);
        if(a <= c) {
            if(b <= 0) {
                printf("erro\n");
                return 0;
            }
            for(a;a<=c;a=a+b) {
                printf("%d ",a);
            }
        } else {
            if(b >= 0) {
                printf("erro\n");
                return 0;
            }
            for(a;a>=c;a=a+b) {
                printf("%d ",a);
            }
        }
    }
    printf("\n");
    return 0;
}
