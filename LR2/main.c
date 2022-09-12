#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "functions.h"

int main(void)
{
    int choice = -1;
    int rc = OK;
    int n = 40;
    struct timeval *stend = (struct timeval *)malloc(8 *sizeof(struct timeval));
    stend[0].tv_sec = -1;
    line *arr = (line *)malloc(45 * sizeof(line));
    line *array = (line *)malloc(45 * sizeof(line)); 
    line *ar = (line *)malloc(45 * sizeof(line)); 
    key *keys = (key *)malloc(45 *sizeof(key));
    key *keyss = (key *)malloc(45 *sizeof(key));
    FILE *f = fopen("table.txt", "r");
    rc = read_in_array(f, arr, n);
    fseek(f, 0, SEEK_SET);
    rc = read_in_array(f, array, n);
    fseek(f, 0, SEEK_SET);
    rc = read_in_array(f, ar, n);
    get_keys(arr, keys, n);
    get_keys(arr, keyss, n);
    fclose(f);
    info();
    menu();
    while (rc == OK)
    {
        rc = choices(&choice);
        if (choice == 0)
            break;
        else
            rc = choice_option(choice, arr, array, ar, keys, keyss, stend, &n);
    }
    free_arr(arr, n);
    free_arr(array, n);
    free_arr(ar, n);
    free_key(keys, n);
    free_key(keyss, n);
    free(stend);
    return OK;
}