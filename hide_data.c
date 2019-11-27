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

	        for(int i = 0 ; i < *input_bit ; ++i ){ // 총 변조에 필요한 비트 수

				fread(&buffer1, 1, 1, fp); // buffer1에 1byte를 1번 읽어옴 : 커서가 1byte 이동

				printf("original data : %02x", buffer1);

				if((buffer1 & 0x01) != data[i]){ // 숨겨야할 데이터와 파일에서 읽어온 LSB가 다르면 ^0x01(원하는 정보 삽입), 같으면 그대로 사용
					temp = buffer1 ^ 0x01; // 연산한 값을 temp에 저장
					fseek(fp, -1, SEEK_CUR); // 읽었던 자리에 LSB 수정하기 위해 움직인 커서를 다시 1byte 앞으로 옮김
					fwrite(&temp, sizeof(u8), 1, fp); // temp에 저장된 값을 1byte로 씀  // 처음에는 fprintf로 했었는데 그건 파일에 쓰는거라서 쓰는위치와 읽어오는 위치가 달라서 이상햇엇음

				}
				// check data : 이부분은 사실 필요 없음
				fseek(fp, -1, SEEK_CUR); // 제대로 쓰여졌는지 다시 출력해보기 위해 1byte 앞으로 이동
				fread(&buffer2, 1, 1, fp); // 정보가 써진 부분 읽어옴

				dec_data[i] = buffer2;
				printf("\nmodified data: %02x", dec_data[i]);
				printf("\n=======================================\n");
			} // 숨기려고 하는 데이터 입력 완료
}
