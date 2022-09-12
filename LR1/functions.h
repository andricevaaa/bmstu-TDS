#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ERR 1
#define OK 0
#define ERR_POINT -1
#define MAX 99999
#define MIN -99999
#define ENT 50
#define ANS 200

void start_informations(void);
int str_to_int(char *str, int *arr, int *len);
int check_points(char *str);
int check_additonal(char *str);
int check_int(char *str, int len);
int check_float(char *str, int len, int point);
void get_ans(int *a, int *b, int *ans, int len1, int len2);
int rounding(int *ans, int j);
int number(char *str);
void format(int *ans, int len1, int len2, int point, int *num);
void print(int *ans, int len1, int len2, int num, char sign1, char sign2);

#endif //FUNCTIONS_H