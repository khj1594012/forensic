#include"quiz3.h"

void quiz2_enc(FILE *en2_fp){

    fseek(en2_fp, 10*sizeof(int),SEEK_SET);

    char str[256];
    printf("input : ");
    scanf("%s",str);

    char c='\0';
    fprintf(en2_fp, "%s", str);
    fprintf(en2_fp, "%c", c);

    fclose(en2_fp);
    getch();
}
