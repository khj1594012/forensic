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
    //BMP �����ϴ� �κ�(����ó��)
    int input_bit, dec_inputlength = 0;
    int inputlengtharr[8], data[256],dec_data[256]; //�ִ� 32���ڸ� �Է��Ѵ� ħ
    u8 input[32];




one:printf("=========================================================\n");
    printf("1. JPG ������ EOI ���Ŀ� ����� �Է��ϴ� �ؽ�Ʈ ���� ����/�����ϱ�.\n");
    printf("2. JPG ������ ��� ���Ŀ� ����ڰ� �Է��ϴ� �ؽ�Ʈ ���� ����/�����ϱ�.\n");
    printf("3. BMP ������ LSB�� �����Ͽ� �Է��ϴ� �ؽ�Ʈ ������ ����/�����ϱ�.\n");
    printf("4. �� ���� ������ �Է����� �޾� ���� ������ �κ��� ����ϱ�\n");
    printf("5. ����\n");
    printf("=========================================================\n\n");

    printf("���ϴ� ��ȣ �Է�(1~5) : ");
    scanf("%d", &pick);

two: while (1) {
        switch (pick) {

            case 1:

                printf("\n1. ����");
                printf("  2. ����");
                printf("  3. ���������� : ");

                scanf("%d", &pick1);

             while (1) {
                    switch (pick1) {
                        case 1: //����
                            en_fp = fopen("3.jpg", "ab");

                            quiz1_enc(en_fp);

                            goto two;

                        case 2: //����
							system("xxd -p 3.jpg > hex.txt");

							FILE *de_fp = fopen("hex.txt", "r");

							quiz1_dec(de_fp);

                            goto two;

                        case 3:
                        printf("������������ �̵��մϴ�.\n\n");
                            system("clear");
                            goto one;

                    default:
                        printf("�߸��� �Է��Դϴ�.\n");
                            system("clear");
                            goto two;
                }
                }
                break;

            case 2:
                printf("\n1. ����");
                printf("  2. ����");
                printf("  3. ���������� : ");
                scanf("%d", &pick2);
                while (1) {

                    switch (pick2) {
                        case 1: //����
                            en2_fp = fopen("3.jpg", "r+b");

                            quiz2_enc(en2_fp);

                            goto two;

                        case 2: //����

                        	de2_fp = fopen("image.jpg", "r+b");
                        	quiz2_dec(de2_fp);

                            goto two;

                        case 3:
                        printf("������������ �̵��մϴ�.\n\n");
                            system("clear");
                            goto one;

                    default:
                        printf("�߸��� �Է��Դϴ�.\n");
                            system("clear");
                            goto two;
                }
                }

                break;

            case 3:
                printf("\n1. ����");
                printf("  2. ����");
                printf("  3. ���������� : ");
                scanf("%d", &pick3);


                while (1) {
                    switch (pick3) {
                        case 1: //����
                        // ������ ���� : lsb���� : ������ ���� ���� ������ ����

                                // file open
                                 en3_fp = fopen("test2.bmp", "r+b");

                                 if (en3_fp == NULL){
                                    printf("file does not exist.\n");
                                    exit(1);
                                 }

                                 else{
                                	 printf("insert data : ");
                                	 scanf("%s",input);

                                    moveEndofHeader(en3_fp,&input_bit,input,inputlengtharr); // input_bit ���� --> �ּҰ� �ѱ�
                                    //�Էµ����� ���� ���� ����
                                    hideDatalen(en3_fp,inputlengtharr);
                                    // �Է� �����͸� �� ���ں��� ���������·� (1��0���� ǥ��) �迭�� ����
                                    // ������ ���� : lsb���� : ������ ���� ���� ������ ����
                                    hideData(en3_fp,&input_bit,input, dec_data);
                                 }


                                 goto two;


                        case 2: //����

                        	 de3_fp = fopen("test2.bmp", "r+b");

                        	 // �������� ��ȣȭ : �Էµ� ������ ���̴� �𸣰� ��� �ڿ� ���̰� ����Ǿ��ִ� �� �ȴٰ� ����..
                        	        // ������ ����
                        	decData(en3_fp, dec_inputlength);

                            fclose(de3_fp);

                            goto two;

                        case 3:
                        printf("������������ �̵��մϴ�.\n\n");
                            system("clear");
                            goto one;

                    default:
                        printf("�߸��� �Է��Դϴ�.\n");
                            system("clear");
                            goto two;
                }
        }


                break;

            case 4:
                four:
                    printf("\n1. ��");
                    printf("  2. ���������� : ");

                    scanf("%d", &pick4);

                    while (1) {
                        switch (pick4) {
                            case 1: // diff
                                //����ڰ� �Է��� �̸��� �ؽ�Ʈ ������
                                //rt���� ��Ʈ�� ����
                                diff_fp1 = fopen("3.jpg", "r+t");
                                diff_fp2 = fopen("4.jpg", "r+t");

                                /* fopen�Լ��� �����߻��� NULL�� �����ϹǷ�
                                ���� ���� �� �����߻��� ���α׷��� ���� */
                                if (diff_fp1 == NULL || diff_fp2 == NULL){
                                     printf("��Ʈ�� ������ �����߻�\n");
                                    goto four;
                                }

                                // �ΰ��� ���Ͽ� ����� �����͸� ����
                                while (1){
                                     //�ΰ��� ���� ��� ���� �������� ���� ���
                                     if (feof(diff_fp1) == 0 && feof(diff_fp2) == 0){
                                          diff_a = fgetc(diff_fp1);
                                          diff_b = fgetc(diff_fp2);


                                          if (diff_a != diff_b){
                                            printf("�ٸ� �κ��Դϴ�.\n");
                                            printf("A :%c /",diff_a);
                                            printf(" B :%c\n\n",diff_b);
                                            diff_count++;
                                          }
                                     }
                                     //�ϳ��� ���ϸ� ���� ������ ���
                                     else if (feof(diff_fp1) != 0 && feof(diff_fp2) == 0){

                                       while (feof(diff_fp2)==0) {
                                         diff_a = fgetc(diff_fp2);
                                         printf("A :%c", diff_a);
                                       }

                                          printf("�ΰ��� ������ ��ġ���� �ʽ��ϴ�.\n");
                                          goto four;
                                     }

                                     //�ϳ��� ���ϸ� ���� ������ ���
                                     else if (feof(diff_fp1) == 0 && feof(diff_fp2) != 0){

                                         while (feof(diff_fp1)==0) {
                                           diff_b = fgetc(diff_fp1);
                                           printf("B :%c\n", diff_b);
                                         }

                                          printf("�ΰ��� ������ ��ġ���� �ʽ��ϴ�.\n");
                                         goto four;
                                     }

                                     //�ΰ��� ���� ��� ���� ������ ���.
                                     //(ù ��° ���ǹ����� �� ������ ���ڴ� �˻��߱� ������
                                     //�� ������ ���ÿ� feof�� ���� Ż���ϸ� ������ ������ ��)
                                     else{

                                       if(diff_count == 0){
                                          printf("�ΰ��� ������ ��ġ�մϴ�.\n");
                                         goto four;
                                        }
                                        printf("\n\n");
                                        printf("================================\n");
                                        printf("\n�ΰ��� ������ ��ġ���� �ʽ��ϴ�.\n\n");
                                        goto four;
                                     }
                                }

                                /* fclose�Լ��� ����� ������ �߻��ϸ�
                                0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
                                �ȳ��� ���α׷��� ���� */
                                diff_state1 = fclose(diff_fp1);
                                diff_state2 = fclose(diff_fp2);

                                if (diff_state1 != 0 || diff_state2 != 0){
                                     printf("��Ʈ�� ���Ž� �����߻�\n");
                                    goto four;
                                }

                            case 2:
                            printf("������������ �̵��մϴ�.\n\n");
                                system("clear");
                                goto one;

                        default:
                            printf("�߸��� �Է��Դϴ�.\n");
                                system("clear");
                                goto two;
                    }
                    }



                break;

            case 5:
                printf("�����մϴ�.\n");
                exit(0);

            default:
                printf("�߸��� �Է��Դϴ�.\n\n\n");
                goto one;

        }
}
      }

