#include"quiz3.h"

void moveEndofHeader(FILE *fp, int *input_bit, u8 input[32], int inputlengtharr[8]){

		int h;
		u8 header = 0;

		*input_bit = 8 * strlen(input); // �Է°� ���� * 8 --> �� �ʿ��� ��Ʈ �� : ������ ��ȯ : 8bits�� 1bit ����ϱ�

	    // �Է°� ���� 2������ ��ȯ�ϴ� �κ� (���̵� ������ �Ŷ� ����� ������ �����ַ���)
	    printf("\n============= data length ==============\n\ninput bit : %d bits= ", *input_bit);

	    for(int i = 7; i >= 0; i--){ // �ֻ��� ��Ʈ���� �迭�� ������� ���� : >> 7���� �ؾ� �ֻ������� ..
	        inputlengtharr[7-i] = (*input_bit >> i) & 0x01;// �ش� �ڸ��� ��Ʈ�� 1�� & -> 1���� 1, 0�̸� 0
	        printf("%d",inputlengtharr[7-i]);
	    }

	    fseek(fp, 10, SEEK_SET); // header size �б� ���� 10bytes �̵�
	    fread(&header, 1, 1, fp); // �ش� ��ġ�� ����� header size ����
	    h = ((header >> 4) * 16) + (header & 0x0f); // header size�� 10������ �ٲ���
	    fseek(fp, h, SEEK_SET); // header �������� �̵�
}
