#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "functions.h"

int main(void)
{
    start_informations();
    int a[ENT],b[ENT];
    int ans[ANS]={0};
    char sign1, sign2;
    int num, point, rc = OK;
    char str1[ENT], str2[ENT];
    printf("              |--------|--------|--------| \n");
    printf("Input integer: ");
    scanf("%s",str1);
    printf(" \n");
    printf("            |--------|--------|--------| \n");
    printf("Input float: ");
    scanf("%s",str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 == 0 || len2 == 0)
    {
        printf("Empty input");
        return rc = ERR;
    }
    else
    {
        if (str_to_int(str1, a, &len1) != ERR_POINT || check_int(str1, len1) != OK)
        {
            printf("You entered incorrect data");
            rc = ERR;
        }
        else
        {
            point = str_to_int(str2, b, &len2);
            if (check_float(str2, len2, point) != OK)
            {
                printf("You entered incorrect data");
                rc = ERR;
            }
            else
            {
                get_ans(a, b, ans, len1, len2);
                num = number(str2);
                format(ans, len1, len2, point, &num);
                sign1 = str1[0];
                sign2 = str2[0];
                print(ans, len1, len2, num, sign1, sign2);
            };
        };
    }
    return rc;
}