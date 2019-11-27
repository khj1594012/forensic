#include"quiz3.h"

void moveEndofHeader(FILE *fp, int *input_bit, u8 input[32], int inputlengtharr[8]){

		int h;
		u8 header = 0;

		*input_bit = 8 * strlen(input); // 입력값 길이 * 8 --> 총 필요한 비트 수 : 이진수 변환 : 8bits당 1bit 숨기니까

	    // 입력값 길이 2진수로 변환하는 부분 (길이도 삽입할 거라서 제대로 들어가는지 보여주려고)
	    printf("\n============= data length ==============\n\ninput bit : %d bits= ", *input_bit);

	    for(int i = 7; i >= 0; i--){ // 최상위 비트부터 배열에 순서대로 대입 : >> 7부터 해야 최상위부터 ..
	        inputlengtharr[7-i] = (*input_bit >> i) & 0x01;// 해당 자리의 비트와 1과 & -> 1ㅇ면 1, 0이면 0
	        printf("%d",inputlengtharr[7-i]);
	    }

	    fseek(fp, 10, SEEK_SET); // header size 읽기 위해 10bytes 이동
	    fread(&header, 1, 1, fp); // 해당 위치에 저장된 header size 읽음
	    h = ((header >> 4) * 16) + (header & 0x0f); // header size를 10진수로 바꿔줌
	    fseek(fp, h, SEEK_SET); // header 뒤쪽으로 이동
}
