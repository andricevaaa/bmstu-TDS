#include "functions.h"

void start_informations(void)
{
    printf("MULTIPLYING INTEGER AND REAL NUMBER \n");
    printf(" \n");
    printf("Input rules \n");
    printf("- When entering integer there can't be more than 31 symbols (1 sign + 30 symbols for digits) \n");
    printf("- When entering real number can't be more than 39 symbols (1 sign + \n");
    printf("1 point(optional) + 30 mantisse symbol + \n");
    printf("+ 1 exponential sign (optional) + 1 order sign + 5 order symbols) \n");
    printf("- If inputed, exponent sign needs to be [latinic E or е] \n");
    printf("- Only [.] can be floating point \n");
    printf(" \n");
}

int str_to_int(char *str, int *arr, int *len)
{
    int j = 0, k = 0;
    int i = *len - 1;
    int point = ERR_POINT;
    if(strchr(str, 'e') != NULL || strchr(str, 'E') != NULL)
    {
        while(!isdigit(str[i] - '0'))
            i--;
        i--;
    };
    *len = i + 1;
    if (str[0] == '+' || str[0] == '-')
    {
        k++;
        *len = *len - 1;
    };
    for(; i >= k; i--)
    {
        if (str[i] != '.')
        {
            arr[j] = str[i] - '0';
            j++;
        }
        else
        {
            *len = *len - 1;
            point = i;
        };
    };
    return point;
}

int check_points(char *str)
{
    int i = 0;
    int count = 0;
    char *point = ".";
    while(str[i] != '\0')
    {
        if(str[i] == *point)
            count++;
        i++;
    }
    return count;
}

int check_additonal(char *str)
{
    char *plus = "+";
    char *minus = "-";
    int i = 1;
    int rc = OK;
    while(str[i] != '\0')
    {
        if(str[i] == *plus || str[i] == *minus)
        {
            if(!isdigit((str[i-1]) - '0'))
                rc = ERR;
        }
        i++;
    }
    return rc;
}

int check_int(char *str, int len)
{
    int rc = OK;
    int i = 0;
    if (str[0] == '+' || str[0] == '-')
        i++;
    for (; i < len - 1; i++)
    {
        if(isdigit(str[i] - '0') || strstr(str, "e") != NULL || strstr(str, "E") != NULL)
            rc = ERR;
        if(strstr(str, "+") != NULL || strstr(str, "-") != NULL)
            rc = ERR;
    };
    return rc;
}

int check_float(char str[100], int len, int point)
{
    int rc = OK;
    int i = 0;
    if (str[0] == '+' || str[0] == '-')
        i++;
    for (; i < len - 1; i++)
    {
        if(isdigit(str[i] - '0'))
        {
            if ((str[i] == 'e') || (str[i] == 'E') || (i == point))
                rc = OK;
            else
                rc = ERR;
        };
    };
    if (check_points(str) > 1)
        rc = ERR;
    if (check_additonal(str) != OK)
        rc = ERR;
    return rc;    
}

void get_ans(int *a, int *b, int *ans, int len1, int len2)
{
    int i, j, tmp;
    for(i = 0; i < len2; i++)
    {
        for(j = 0; j < len1; j++)
            ans[i+j] += b[i]*a[j];
    }
    for(i = 0; i < len1+len2; i++)
    {
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }
}

int rounding(int *ans, int j)
{
    if(ans[j-1] > 4)
    {
        if(ans[j] < 9)
            ans[j] = ans[j] + 1;
        else
        {
            while(ans[j] == 9)
            {
                ans[j] = 0;
                j++;
            };
            ans[j] = ans[j] + 1;
        };
    };
    return j;
}

int number(char *str)
{
    int len = strlen(str);
    int num = OK;
    int i = 0;
    if(strchr(str, 'e') != NULL || strchr(str, 'E') != NULL)
    {
        while(!isdigit(str[i] - '0'))
            i++;
        i++;
        if (str[i] == '+')
        {
            num = str[i+1] - '0';
            i += 2;
        }
        else if(str[i] == '-')
        {   
            num = (str[i+1] - '0') * (-1);
            i+= 2;
        }
        else
        {   
            num = str[i] - '0';
            i++;
        };
        while (i < len)
        {
            if (num > 0)
                num = num*10 + (str[i] - '0');
            else
                num = num*10 - (str[i] - '0');
            i++;
        };
    };
    return num;
}

void format(int *ans, int len1, int len2, int point, int *num)
{
    point = len2 - point;
    int i, count = 0;
    for(i = len1 + len2; i >= 0; i--)
    {
        if(ans[i] > 0)
            break;
    }
    if (point != -1)
    {
        for(int j = point; j < i+1; j++)
            count++;
    };
    if (count > 30)
        count = 30;
    if (count > 0)
        *num = *num + count;
}

void print(int *ans, int len1, int len2, int num, char sign1, char sign2)
{
    if (num > MAX || num < MIN)
        printf("переполнение");
    else
    {
        int i, j;
        for(i = len1 + len2; i>= 0; i--)
            if(ans[i] > 0)
                break;
        for(j = 0; j < i; j++)
            if(ans[j] > 0)
                break;
        if (i > 29)
            j = i - 29;
        if (i == -1)
        {
            i++;
            num = 0;
        };
        if ((sign1 == '-' && sign2 != '-'))
            printf("-");
        else if(sign1 != '-' && sign2 == '-')
        {
            printf("-");
            num--;
        }
        else
            printf("+");
        printf("0.");
        int p = j;
        j = rounding(ans, p);
        for(; i >= j; i--)
        {
            printf("%d",ans[i]);
        };
        if (num >= 0)
            printf("E+%d", num);
        else
            printf("E%d", num);
    };
}