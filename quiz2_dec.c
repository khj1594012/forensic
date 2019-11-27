#include"quiz3.h"

void quiz2_dec(FILE *de2_fp){

	FILE *fp = fopen("image.jpg", "r+b");

	fseek(fp, 10*sizeof(int),SEEK_SET);
	char c;
	char str[256];
	int i=0;

	while((c=fgetc(fp))!='\0'){
		printf("%c\n",c);
		str[i++] = c;
	}
	printf("%s",str);
	fclose(fp);
	getch();
}
