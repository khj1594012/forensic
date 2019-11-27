#include"quiz3.h"

void hideDatalen(FILE *fp, int inputlengtharr[8]){

	 u8 buffer1 = 0, buffer2 = 0, temp = 0;

	 printf("\n\n===== hide data length info to LSB =====\n\n");

	        for(int i = 0 ; i < 8 ; ++i){
	            fread(&buffer1, 1, 1, fp); // buffer1�� 1byte�� 1�� �о�� : Ŀ���� 1byte �̵�
	            printf("original data : %02x", buffer1);

	            if((buffer1 & 0x01) != inputlengtharr[i]){ // ���ܾ��� �����Ϳ� ���Ͽ��� �о�� LSB�� �ٸ��� ^0x01(���ϴ� ���� ����), ������ �״�� ���
	                temp = buffer1 ^ 0x01; // ������ ���� temp�� ����
	                fseek(fp, -1, SEEK_CUR); // �о��� �ڸ��� LSB �����ϱ� ���� ������ Ŀ���� �ٽ� 1byte ������ �ű�
	                fwrite(&temp, sizeof(u8), 1, fp); // temp�� ����� ���� 1byte�� ��
	            }
	            // check re-write : �̺κ��� ��� �ʿ� ����
	            fseek(fp, -1, SEEK_CUR); // ����� ���������� �ٽ� ����غ��� ���� 1byte ������ �̵�
	            fread(&buffer2, 1, 1, fp); // ������ ���� �κ� �о��
	            printf("\nmodified data : %02x", buffer2);
	            printf("\n========================================\n");
	        } // ��� �Է� �Ϸ�
}
