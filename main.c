#include"quiz3.h"

int main(){
    int pick;
    int pick1, pick2, pick3, pick4;
    int diff_state1, diff_state2;
    char diff_a, diff_b;
    int diff_count = 0;
    FILE *en_fp;
    FILE *en2_fp;
    FILE *de2_fp;
    FILE *en3_fp;
    FILE *de3_fp;
    FILE* diff_fp1;
    FILE* diff_fp2;
    //BMP 선언하는 부분(사전처리)
    int input_bit, dec_inputlength = 0;
    int inputlengtharr[8], data[256],dec_data[256]; //최대 32글자만 입력한다 침
    u8 input[32];




one:printf("=========================================================\n");
    printf("1. JPG 파일의 EOI 이후에 사용자 입력하는 텍스트 정보 삽입/복원하기.\n");
    printf("2. JPG 파일의 헤더 이후에 사용자가 입력하는 텍스트 정보 삽입/복원하기.\n");
    printf("3. BMP 파일의 LSB를 변조하여 입력하는 텍스트 정보를 삽입/복원하기.\n");
    printf("4. 두 개의 파일을 입력으로 받아 서로 상이한 부분을 출력하기\n");
    printf("5. 종료\n");
    printf("=========================================================\n\n");

    printf("원하는 번호 입력(1~5) : ");
    scanf("%d", &pick);

two: while (1) {
        switch (pick) {

            case 1:

                printf("\n1. 삽입");
                printf("  2. 복구");
                printf("  3. 이전페이지 : ");

                scanf("%d", &pick1);

             while (1) {
                    switch (pick1) {
                        case 1: //삽입
                            en_fp = fopen("3.jpg", "ab");

                            quiz1_enc(en_fp);

                            goto two;

                        case 2: //복구
							system("xxd -p 3.jpg > hex.txt");

							FILE *de_fp = fopen("hex.txt", "r");

							quiz1_dec(de_fp);

                            goto two;

                        case 3:
                        printf("이전페이지로 이동합니다.\n\n");
                            system("clear");
                            goto one;

                    default:
                        printf("잘못된 입력입니다.\n");
                            system("clear");
                            goto two;
                }
                }
                break;

            case 2:
                printf("\n1. 삽입");
                printf("  2. 복구");
                printf("  3. 이전페이지 : ");
                scanf("%d", &pick2);
                while (1) {

                    switch (pick2) {
                        case 1: //삽입
                            en2_fp = fopen("3.jpg", "r+b");

                            quiz2_enc(en2_fp);

                            goto two;

                        case 2: //복구

                        	de2_fp = fopen("image.jpg", "r+b");
                        	quiz2_dec(de2_fp);

                            goto two;

                        case 3:
                        printf("이전페이지로 이동합니다.\n\n");
                            system("clear");
                            goto one;

                    default:
                        printf("잘못된 입력입니다.\n");
                            system("clear");
                            goto two;
                }
                }

                break;

            case 3:
                printf("\n1. 삽입");
                printf("  2. 복구");
                printf("  3. 이전페이지 : ");
                scanf("%d", &pick3);


                while (1) {
                    switch (pick3) {
                        case 1: //삽입
                        // 데이터 삽입 : lsb변조 : 데이터 길이 삽입 과정과 같음

                                // file open
                                 en3_fp = fopen("test2.bmp", "r+b");

                                 if (en3_fp == NULL){
                                    printf("file does not exist.\n");
                                    exit(1);
                                 }

                                 else{
                                	 printf("insert data : ");
                                	 scanf("%s",input);

                                    moveEndofHeader(en3_fp,&input_bit,input,inputlengtharr); // input_bit 조작 --> 주소값 넘김
                                    //입력데이터 길이 정보 숨김
                                    hideDatalen(en3_fp,inputlengtharr);
                                    // 입력 데이터를 각 문자별로 이진수형태로 (1과0으로 표현) 배열에 저장
                                    // 데이터 삽입 : lsb변조 : 데이터 길이 삽입 과정과 같음
                                    hideData(en3_fp,&input_bit,input, dec_data);
                                 }


                                 goto two;


                        case 2: //복구

                        	 de3_fp = fopen("test2.bmp", "r+b");

                        	 // 길이정보 복호화 : 입력된 데이터 길이는 모르고 헤더 뒤에 길이가 저장되어있는 건 안다고 가정..
                        	        // 데이터 복구
                        	decData(en3_fp, dec_inputlength);

                            fclose(de3_fp);

                            goto two;

                        case 3:
                        printf("이전페이지로 이동합니다.\n\n");
                            system("clear");
                            goto one;

                    default:
                        printf("잘못된 입력입니다.\n");
                            system("clear");
                            goto two;
                }
        }


                break;

            case 4:
                four:
                    printf("\n1. 비교");
                    printf("  2. 이전페이지 : ");

                    scanf("%d", &pick4);

                    while (1) {
                        switch (pick4) {
                            case 1: // diff
                                //사용자가 입력한 이름의 텍스트 파일을
                                //rt모드로 스트림 생성
                                diff_fp1 = fopen("3.jpg", "r+t");
                                diff_fp2 = fopen("4.jpg", "r+t");

                                /* fopen함수는 오류발생시 NULL을 리턴하므로
                                파일 개방 중 오류발생시 프로그램을 종료 */
                                if (diff_fp1 == NULL || diff_fp2 == NULL){
                                     printf("스트림 생성시 오류발생\n");
                                    goto four;
                                }

                                // 두개의 파일에 저장된 데이터를 비교함
                                while (1){
                                     //두개의 파일 모두 끝에 도달하지 않을 경우
                                     if (feof(diff_fp1) == 0 && feof(diff_fp2) == 0){
                                          diff_a = fgetc(diff_fp1);
                                          diff_b = fgetc(diff_fp2);


                                          if (diff_a != diff_b){
                                            printf("다른 부분입니다.\n");
                                            printf("A :%c /",diff_a);
                                            printf(" B :%c\n\n",diff_b);
                                            diff_count++;
                                          }
                                     }
                                     //하나의 파일만 끝에 도달할 경우
                                     else if (feof(diff_fp1) != 0 && feof(diff_fp2) == 0){

                                       while (feof(diff_fp2)==0) {
                                         diff_a = fgetc(diff_fp2);
                                         printf("A :%c", diff_a);
                                       }

                                          printf("두개의 파일은 일치하지 않습니다.\n");
                                          goto four;
                                     }

                                     //하나의 파일만 끝에 도달할 경우
                                     else if (feof(diff_fp1) == 0 && feof(diff_fp2) != 0){

                                         while (feof(diff_fp1)==0) {
                                           diff_b = fgetc(diff_fp1);
                                           printf("B :%c\n", diff_b);
                                         }

                                          printf("두개의 파일은 일치하지 않습니다.\n");
                                         goto four;
                                     }

                                     //두개의 파일 모두 끝에 도달한 경우.
                                     //(첫 번째 조건문에서 각 파일의 문자는 검사했기 때문에
                                     //두 파일이 동시에 feof에 의해 탈출하면 동일한 파일인 것)
                                     else{

                                       if(diff_count == 0){
                                          printf("두개의 파일은 일치합니다.\n");
                                         goto four;
                                        }
                                        printf("\n\n");
                                        printf("================================\n");
                                        printf("\n두개의 파일은 일치하지 않습니다.\n\n");
                                        goto four;
                                     }
                                }

                                /* fclose함수는 종료시 오류가 발생하면
                                0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
                                안내후 프로그램을 종료 */
                                diff_state1 = fclose(diff_fp1);
                                diff_state2 = fclose(diff_fp2);

                                if (diff_state1 != 0 || diff_state2 != 0){
                                     printf("스트림 제거시 오류발생\n");
                                    goto four;
                                }

                            case 2:
                            printf("이전페이지로 이동합니다.\n\n");
                                system("clear");
                                goto one;

                        default:
                            printf("잘못된 입력입니다.\n");
                                system("clear");
                                goto two;
                    }
                    }



                break;

            case 5:
                printf("종료합니다.\n");
                exit(0);

            default:
                printf("잘못된 입력입니다.\n\n\n");
                goto one;

        }
}
      }

