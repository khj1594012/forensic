#include"quiz3.h"


void quiz1_dec(FILE *de_fp){

	 char dc[3];
	                        //int count=0;
	                        char buf[256];

	                        int i=1;

	                        while(1){
	                            fseek(de_fp,-sizeof(char),SEEK_END);
	                            fseek(de_fp, -i*sizeof(char)*2,SEEK_CUR);
	                            fgets(dc,sizeof(dc),de_fp);
	                            if(!strcmp(dc, "d9")) break;
	                            i++;
	                        }

	                        fgets(buf, 256, de_fp);
	                        printf("HEX = %s\n",buf);

	                        char temp[3];
	                        temp[2] = '\0';
	                        int num1;
	                        printf("result = ");
	                        for(int i=0; i<strlen(buf)-1; i+=2){
	                            temp[0] = buf[i];
	                            temp[1] = buf[i+1];
	                            num1 = (int)strtol(temp,NULL,16);
	                            printf("%c",num1);
	                        }

	                        printf("\n복구했습니다.");
	                        fclose(de_fp);
	                        getch();

}
