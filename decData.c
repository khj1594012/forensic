#include"quiz3.h"

void decData(FILE *fp, int dec_inputlength){

	 u8 header = 0, buffer1 = 0, temp = 0,  buffer2 = 0, temp2 = 0;
     u8 dec_origindata[32];
	 int h;

	 printf("\n\n======= recovery data from LSB ========\n");
	        fseek(fp, 10, SEEK_SET); // header size 읽기 위해 10bytes 이동
	        fread(&header, 1, 1, fp); // 해당 위치에 저장된 h
	        h = ((header >> 4) * 16) + (header & 0x0f);
	        fseek(fp, h, SEEK_SET); // header 뒤쪽으로 이동

	        for(int i = 0; i < 8; ++i){
	            fread(&buffer1, 1, 1, fp);
	            dec_inputlength ^= ((buffer1 & 0x01) << (7-i));
	        }

	 printf("\n\nextracted data length : %d bits", dec_inputlength);  // 데이터 길이 추출 완료 :4글자 입력시 32bits

	 for(int i = 0; i < dec_inputlength/8  ; ++i){ // 입력한 문자의 개수 번 반복
	     temp2=0; // 문자마다 0으로 다시 초기화
	     for(int j = 0; j < 8 ; ++j){ // 8bit씩 이라서 8번 반복
	         fread(&buffer2, 1, 1, fp);
	         temp2 ^= ((buffer2 & 0x01) << (7-j)); // 0x01과 &연산해서 버퍼의 lsb를 알아낸 후!!
	                                               // 맨 앞부터 채움 -> 0과 XOR을 8번 반복해서 더해줌
	                                               // buffer가 01100001 이면 lsb인 1이 숨긴 정보니까 그것을 temp의 최상위 비트로 shift, 그 다음도 동일하게 진행 -> 8번 반복
	         }
	     dec_origindata[i] = temp2; // 각 문자의 lsb들을 모은 temp2를 하나의 배열에 넣음
	 }
	                 // 데이터 추출 완료
	  printf("\n\nrecovered data : ");

	  for(int i = 0; i < dec_inputlength/8 ; ++i) {// 글자수만큼 출력
	      printf("%c", dec_origindata[i]);
	  }
	      printf("\n=======================================\n\n");

	  fclose(fp);


}
