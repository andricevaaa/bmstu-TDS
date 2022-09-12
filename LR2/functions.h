#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define OK 0
#define ERR_IO 1
#define MAX_NAME 20
#define SIZE 40
#define TYPE 10
#define ERROR -1000

typedef struct
{
    char *name;
    int population;
    char *capital;
	char *continent;
	int type;
	int sights; 
	char *stype;
	char *season;
	int temp;
	int water_temp;
	int distance;
	char *sport;
	int price; 
} line;

typedef struct
{
	int pos;
	int population;
	char *name;
} key;

void info(void);
void menu(void);
void free_obj(line object);
void free_arr(line *arr, int n);
void free_key(key *arr, int n);
int choices(int *choice);
void swap(line *xp, line *yp);
void swapkey(key *xp, key *yp); 
void bubbleSort(line *arr, int n);
void bubbleSortkey(key *arr, int n);
void selectionSort(line *arr, int n);
void selectionSortkey(key *arr, int n);
void print_st(line object);
void print_starr(line *arr, int n);
void printkey(key object);
void print_key(key *arr, int n);
int delete_country(line *arr, line *array, line *ar, key *keys, key *keyss, int *n);
void printwithkeys(line *arr, key *keys, int n);
int choice_option(int choice, line *arr, line *array, line *ar, key *keys, key *keyss, struct timeval *stend, int *n);
void get_keys(line *arr, key *array, int n);
int read_obj_info(FILE *f, line *object);
int read_in_array(FILE *f, line *arr, int n);
int search_table(line *arr, int k);
int cont_info(char *cont_name);
int sight_seeing(char *type);
int season(char *season);
int sport_info(char *sport);
int enter_new_country(line *arr, line *array, line *ar, int *n);


#endif //FUNCTIONS_H