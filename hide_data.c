#include"quiz3.h"

void hideData(FILE *fp, int *input_bit, u8 input[32], int dec_data[256]){

	 u8 buffer1 = 0, buffer2 = 0, temp = 0;
	 int data[256];

     for(int i = 0; i < strlen(input) ; ++i){
         for(int j = 0; j < 8 ; ++j){
             data[(8*(i+1)-1) -j] = (input[i] >> j) & 0x01;
         }
     }
     printf("input bit : ", *input_bit);

     printf("\n\n========= hide data to LSB ==========\n\n");

	        for(int i = 0 ; i < *input_bit ; ++i ){ // �� ������ �ʿ��� ��Ʈ ��

				fread(&buffer1, 1, 1, fp); // buffer1�� 1byte�� 1�� �о�� : Ŀ���� 1byte �̵�

				printf("original data : %02x", buffer1);

				if((buffer1 & 0x01) != data[i]){ // ���ܾ��� �����Ϳ� ���Ͽ��� �о�� LSB�� �ٸ��� ^0x01(���ϴ� ���� ����), ������ �״�� ���
					temp = buffer1 ^ 0x01; // ������ ���� temp�� ����
					fseek(fp, -1, SEEK_CUR); // �о��� �ڸ��� LSB �����ϱ� ���� ������ Ŀ���� �ٽ� 1byte ������ �ű�
					fwrite(&temp, sizeof(u8), 1, fp); // temp�� ����� ���� 1byte�� ��  // ó������ fprintf�� �߾��µ� �װ� ���Ͽ� ���°Ŷ� ������ġ�� �о���� ��ġ�� �޶� �̻��޾���

				}
				// check data : �̺κ��� ��� �ʿ� ����
				fseek(fp, -1, SEEK_CUR); // ����� ���������� �ٽ� ����غ��� ���� 1byte ������ �̵�
				fread(&buffer2, 1, 1, fp); // ������ ���� �κ� �о��

				dec_data[i] = buffer2;
				printf("\nmodified data: %02x", dec_data[i]);
				printf("\n=======================================\n");
			} // ������� �ϴ� ������ �Է� �Ϸ�
}
