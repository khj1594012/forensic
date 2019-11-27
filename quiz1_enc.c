#include"quiz3.h"

void quiz1_enc(FILE *en_fp){
	FILE *fp = fopen("image3.jpg", "ab");


    char ec;
    printf("input : ");
    getchar();

    while((ec=getchar()) != '\n'){
        fprintf(en_fp, "%c", ec);
    }

    fclose(en_fp);

    printf("삽입되었습니다.\n");

    getch();
}
