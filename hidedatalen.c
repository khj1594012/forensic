#include"quiz3.h"

void hideDatalen(FILE *fp, int inputlengtharr[8]){

	 u8 buffer1 = 0, buffer2 = 0, temp = 0;

	 printf("\n\n===== hide data length info to LSB =====\n\n");

	        for(int i = 0 ; i < 8 ; ++i){
	            fread(&buffer1, 1, 1, fp); // buffer1에 1byte를 1번 읽어옴 : 커서가 1byte 이동
	            printf("original data : %02x", buffer1);

	            if((buffer1 & 0x01) != inputlengtharr[i]){ // 숨겨야할 데이터와 파일에서 읽어온 LSB가 다르면 ^0x01(원하는 정보 삽입), 같으면 그대로 사용
	                temp = buffer1 ^ 0x01; // 연산한 값을 temp에 저장
	                fseek(fp, -1, SEEK_CUR); // 읽었던 자리에 LSB 수정하기 위해 움직인 커서를 다시 1byte 앞으로 옮김
	                fwrite(&temp, sizeof(u8), 1, fp); // temp에 저장된 값을 1byte로 씀
	            }
	            // check re-write : 이부분은 사실 필요 없음
	            fseek(fp, -1, SEEK_CUR); // 제대로 쓰여졌는지 다시 출력해보기 위해 1byte 앞으로 이동
	            fread(&buffer2, 1, 1, fp); // 정보가 써진 부분 읽어옴
	            printf("\nmodified data : %02x", buffer2);
	            printf("\n========================================\n");
	        } // 헤더 입력 완료
}
