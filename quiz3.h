/*
 * quiz3.h
 *
 *  Created on: 2019. 11. 26.
 *      Author: CryptoCraftLab
 */

#ifndef QUIZ3_H_
#define QUIZ3_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#include <syscall.h>

typedef unsigned char u8;

void quiz1_enc(FILE *en_fp); //void?
void quiz_dec(FILE *de_fp);

void quiz2_enc(FILE *en_fp);
void quiz2_dec(FILE *de_fp);


void moveEndofHeader(FILE *en3_fp, int *input_bit, u8 input[32], int inputlengtharr[8]);

void hideDatalen(FILE *en3_fp, int inputlengtharr[8]);

void hideData(FILE *en3_fp, int *input_bit, u8 input[32], int dec_data[256]);

void decData(FILE *de3_fp, int dec_inputlength);

#endif /* QUIZ3_H_ */
