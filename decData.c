#include"quiz3.h"

void decData(FILE *fp, int dec_inputlength){

	 u8 header = 0, buffer1 = 0, temp = 0,  buffer2 = 0, temp2 = 0;
     u8 dec_origindata[32];
	 int h;

	 printf("\n\n======= recovery data from LSB ========\n");
	        fseek(fp, 10, SEEK_SET); // header size �б� ���� 10bytes �̵�
	        fread(&header, 1, 1, fp); // �ش� ��ġ�� ����� h
	        h = ((header >> 4) * 16) + (header & 0x0f);
	        fseek(fp, h, SEEK_SET); // header �������� �̵�

	        for(int i = 0; i < 8; ++i){
	            fread(&buffer1, 1, 1, fp);
	            dec_inputlength ^= ((buffer1 & 0x01) << (7-i));
	        }

	 printf("\n\nextracted data length : %d bits", dec_inputlength);  // ������ ���� ���� �Ϸ� :4���� �Է½� 32bits

	 for(int i = 0; i < dec_inputlength/8  ; ++i){ // �Է��� ������ ���� �� �ݺ�
	     temp2=0; // ���ڸ��� 0���� �ٽ� �ʱ�ȭ
	     for(int j = 0; j < 8 ; ++j){ // 8bit�� �̶� 8�� �ݺ�
	         fread(&buffer2, 1, 1, fp);
	         temp2 ^= ((buffer2 & 0x01) << (7-j)); // 0x01�� &�����ؼ� ������ lsb�� �˾Ƴ� ��!!
	                                               // �� �պ��� ä�� -> 0�� XOR�� 8�� �ݺ��ؼ� ������
	                                               // buffer�� 01100001 �̸� lsb�� 1�� ���� �����ϱ� �װ��� temp�� �ֻ��� ��Ʈ�� shift, �� ������ �����ϰ� ���� -> 8�� �ݺ�
	         }
	     dec_origindata[i] = temp2; // �� ������ lsb���� ���� temp2�� �ϳ��� �迭�� ����
	 }
	                 // ������ ���� �Ϸ�
	  printf("\n\nrecovered data : ");

	  for(int i = 0; i < dec_inputlength/8 ; ++i) {// ���ڼ���ŭ ���
	      printf("%c", dec_origindata[i]);
	  }
	      printf("\n=======================================\n\n");

	  fclose(fp);


}
