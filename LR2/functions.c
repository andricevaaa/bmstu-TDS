#include "functions.h"

void info(void)
{
    printf("The table contains following information : \n");
    printf("name of the country; population; capital; continent; type of toruism + additional information; \n");
    printf("There are three types of tourism and they are represented with numbers: \n");
    printf("    1 - sightseeing; additional information include no. of objects protected by unesco and type (art, hisotry, nature) \n");
    printf("    2 - beach; additional information include season, max. temperature, water temperature and distance by flight in hours \n");
    printf("    3 - sport; additional information include type of sport (skiing, hiking, surfing) and lowest price for a vacation \n");
    printf("\n");
}

void menu(void)
{
    printf("Menu: \n");
    printf("1 - add country\n");
    printf("2 - delete country\n");
    printf("3 - search table by continent and sport\n");
    printf("4 - see sorted keys before sorting the table\n");
    printf("5 - see sorted table\n");
    printf("6 - see table sorted using key\n");
    printf("7 - see time information for sorting with and without keys\n");
    printf("8 - see time information for different types of sort\n");
    printf("0 - exit\n");
    printf("\n");
}

void free_obj(line object)
{
    free(object.name);
    free(object.capital);
    free(object.continent);
    if (object.type == 1)
        free(object.stype);
    else if (object.type == 2)
        free(object.season);
    else
        free(object.sport);
}

void free_arr(line *arr, int n)
{
    for (int i = 0; i < n; i++)
        free_obj(arr[i]);
    free(arr);
}

void free_key(key *arr, int n)
{
    for (int i = 0; i < n; i++)
        free(arr[i].name);
    free(arr);
}

int choices(int *choice)
{
    int n = *choice;
    printf("Input your choice: \n");
    if (scanf("%d", &n) != 1)
        return ERR_IO;
    while (n < 0 || n > 8)
    {
        printf("You chose non-existent option. Try again: ");
        if (scanf("%d", &n) != 1)
            return ERR_IO;
        printf("\n");
    };
    *choice = n;
    return OK;
}

void swap(line *xp, line *yp) 
{ 
    line temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void swapkey(key *xp, key *yp) 
{ 
    key temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void bubbleSort(line *arr, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)        
       for (j = 0; j < n-i-1; j++)  
           if (arr[j].population > arr[j+1].population) 
              swap(&arr[j], &arr[j+1]); 
} 

void bubbleSortkey(key *arr, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)        
       for (j = 0; j < n-i-1; j++)  
           if (arr[j].population > arr[j+1].population) 
              swapkey(&arr[j], &arr[j+1]); 
} 

void selectionSort(line *arr, int n) 
{ 
    int i, j, min_idx; 
    for (i = 0; i < n-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
            if (arr[j].population < arr[min_idx].population) 
            min_idx = j; 
        swap(&arr[min_idx], &arr[i]); 
    } 
}

void selectionSortkey(key *arr, int n) 
{ 
    int i, j, min_idx; 
    for (i = 0; i < n-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
            if (arr[j].population < arr[min_idx].population) 
            min_idx = j; 
        swapkey(&arr[min_idx], &arr[i]); 
    } 
} 

void print_st(line object)
{
    printf("%s ", object.name);
    printf("%d ", object.population);
    printf("%s ", object.capital);
    printf("%s ", object.continent);
    printf("%d ", object.type);
    if (object.type == 1)
    {
        printf("%d ", object.sights);
        printf("%s \n", object.stype);
    }
    else if (object.type == 2)
    {
        printf("%s ", object.season);
        printf("%d ", object.temp);
        printf("%d ", object.water_temp);
        printf("%d \n", object.distance);
    }
    else
    {
        printf("%s ", object.sport);
        printf("%d \n", object.price);
    }
    
}

void print_starr(line *arr, int n)
{
    for(long i = 0; i < n; i++)
        print_st(arr[i]);
}

void printkey(key object)
{
    printf("%d ", object.pos);
    printf("%d ", object.population);
    printf("%s \n", object.name);
}

void print_key(key *arr, int n)
{
    for(long i = 0; i < n; i++)
        printkey(arr[i]);
}

int delete_country(line *arr, line *array, line *ar, key *keys, key *keyss, int *n)
{
    char *name = (char *)malloc(10 * sizeof(char));
    int i;
    int k = *n;
    printf("Choose country to delete: ");
    if (scanf("%s", name) != 1)
        return ERR_IO;
    for (i = 0; i < k; i++)
        if (strcmp(arr[i].name, name) == 0)
            break;
    if (i != k)
    {
        k--;
        for (; i < k; i++)
        {
            arr[i] = arr[i + 1];
            array[i] = array[i + 1];
            ar[i] = ar[i + 1];
            keys[i] = keys[i + 1];
            keyss[i] = keyss[i + 1]; 
        }
    }
    *n = k;
    free(name);
    return OK;
}

void printwithkeys(line *arr, key *keys, int n)
{
    for (int i = 0; i < n; i++)
        print_st(arr[keys[i].pos]);
}

int choice_option(int choice, line *arr, line *array, line *ar, key *keys, key *keyss, struct timeval *stend, int *n)
{
    int rc = OK;
    if (choice == 1)
        rc = enter_new_country(arr, array, ar, n);
    else if (choice == 2)
        rc = delete_country(arr, array, ar, keys, keyss, n);
    else if (choice == 3)
        rc = search_table(arr, *n);
    else
    {
        if (stend[0].tv_sec == -1)
        {
            gettimeofday(&stend[0], NULL);
            bubbleSortkey(keys, *n);
            gettimeofday(&stend[1], NULL);
            gettimeofday(&stend[2], NULL);
            selectionSortkey(keyss, *n);
            gettimeofday(&stend[3], NULL);
            gettimeofday(&stend[4], NULL);
            bubbleSort(arr, *n);
            gettimeofday(&stend[5], NULL);
            gettimeofday(&stend[6], NULL);
            selectionSort(array, *n);
            gettimeofday(&stend[7], NULL);
        };
    };
    switch(choice)
    {
        case 4:
            print_key(keys, *n);
            break;
        case 5:
            print_starr(arr, *n);
            break;
        case 6:
            printwithkeys(ar, keys, *n);
            break;
        case 7:
            printf("Time taken to sort keys: %ld microseconds \n \n", ((stend[1].tv_sec * 1000000 + stend[1].tv_usec) - (stend[0].tv_sec * 1000000 + stend[0].tv_usec)));
            printf("Time taken to sort table: %ld microseconds \n \n", ((stend[5].tv_sec * 1000000 + stend[5].tv_usec) - (stend[4].tv_sec * 1000000 + stend[4].tv_usec)));        
            break;
        case 8:
            printf("Time taken to sort keys using bubble sort: %ld microseconds \n \n", ((stend[1].tv_sec * 1000000 + stend[1].tv_usec) - (stend[0].tv_sec * 1000000 + stend[0].tv_usec)));
            printf("Time taken to sort keys using selection sort: %ld microseconds \n \n", ((stend[3].tv_sec * 1000000 + stend[3].tv_usec) - (stend[2].tv_sec * 1000000 + stend[2].tv_usec)));
            printf("Time taken to sort table using bubble sort: %ld microseconds \n \n", ((stend[5].tv_sec * 1000000 + stend[5].tv_usec) - (stend[4].tv_sec * 1000000 + stend[4].tv_usec)));
            printf("Time taken to sort table using selection sort: %ld microseconds \n \n", ((stend[7].tv_sec * 1000000 + stend[7].tv_usec) - (stend[6].tv_sec * 1000000 + stend[6].tv_usec)));
            break;
        default:
            break;
    }
    return rc;
}

void get_keys(line *arr, key *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i].pos = i;
        array[i].population = arr[i].population;
        array[i].name = (char *)malloc(15 * sizeof(char));
        strcpy(array[i].name, arr[i].name);
    };
}

int read_obj_info(FILE *f, line *object)
{
    char buf[SIZE];
    object->name = (char *)malloc(15 * sizeof(char));
    if (fscanf(f, "%s", object->name) != 1)
        return ERR_IO;
    if (fscanf(f, "%d", &object->population) != 1)
        return ERR_IO;
    object->capital = (char *)malloc(15 * sizeof(char));
    if (fscanf(f, "%s", object->capital) != 1)
        return ERR_IO;
    object->continent = (char *)malloc(15 * sizeof(char));
    if (fscanf(f, "%s", object->continent) != 1)
        return ERR_IO;
    if (fscanf(f, "%d", &object->type) != 1)
        return ERR_IO;
    switch(object->type)
    {
        case 1:
            if (fscanf(f, "%d", &object->sights) != 1)
                return ERR_IO;
            object->stype = (char *)malloc(15 * sizeof(char));
            if (fscanf(f, "%s", object->stype) != 1)
                return ERR_IO;
            object->season = NULL;
            object->temp = ERROR;
            object->water_temp = ERROR;
            object->distance = ERROR;
            object->sport = NULL;
            object->price = ERROR;
            break;
        case 2:
            object->season = (char *)malloc(15 * sizeof(char));
            if (fscanf(f, "%s", object->season) != 1)
                return ERR_IO;
            if (fscanf(f, "%d", &object->temp) != 1)
                return ERR_IO;
            if (fscanf(f, "%d", &object->water_temp) != 1)
                return ERR_IO;
            if (fscanf(f, "%d", &object->distance) != 1)
                return ERR_IO;
            object->sights = ERROR;
            object->stype = NULL;
            object->sport = NULL;
            object->price = ERROR;
            break;
        case 3:
            object->sport = (char *)malloc(15 * sizeof(char));
            if (fscanf(f, "%s", object->sport) != 1)
                return ERR_IO;
            if (fscanf(f, "%d", &object->price) != 1)
                return ERR_IO;
            object->sights = ERROR;
            object->stype = NULL;
            object->season = NULL;
            object->temp = ERROR;
            object->water_temp = ERROR;
            object->distance = ERROR;
            break;
        default:
            break;
    }
    fgets(buf, sizeof(buf), f);
    return OK;
}

int read_in_array(FILE *f, line *arr, int n)
{
    line cur;
    int k = 0;
    int rc = OK;
    while (k < n)
    {
        rc = read_obj_info(f, &cur);
        if (rc == OK)
        {
            if (k < n)
            {
                arr[k] = cur;
                k++;
            }
            else
                rc = ERR_IO;
        }
    }
    if (rc != ERR_IO)
        rc = OK;
    return rc;
}

int search_table(line *arr, int k)
{
    int ind = 0;
    char *cont = (char *)malloc(15 * sizeof(char));
    char *sport = (char *)malloc(15 * sizeof(char));;
    printf("Choose continent: ");
    if (scanf("%s", cont) != 1)
        return ERR_IO;
    printf("Choose sport: ");
    if (scanf("%s", sport) != 1)
        return ERR_IO;
    for (int i = 0; i < k; i++)
    {
        if (strcmp(arr[i].continent, cont) == 0)
        {
            if (arr[i].type == 3)
            {
                if (strcmp(arr[i].sport, sport) == 0)
                {
                    print_st(arr[i]);
                    ind++;
                };
            };
        };
    };
    if (ind == 0)
        printf("There is no such option \n");
    free(cont);
    free(sport);
    return OK;
}

int cont_info(char *cont_name)
{
    int choice;
    printf("You can choose between following continents: \n");
    printf("[1]Europe, [2]Asia, [3]Africa, [4]Australia, [5]America \n");
    printf("Input your choice (numerical): ");
    if (scanf("%d", &choice) != 1)
        return ERR_IO;
    while (choice < 1 || choice > 5)
    {
        printf("Wrong input, try again: ");
        if (scanf("%d", &choice) != 1)
            return ERR_IO;
    }
    if (choice == 1)
        strcpy(cont_name, "Europe");
    else if (choice == 2)
        strcpy(cont_name, "Asia");
    else if (choice == 3)
        strcpy(cont_name, "Africa");
    else if (choice == 4)
        strcpy(cont_name, "Australia");
    else
        strcpy(cont_name, "America");
    return OK;
}

int sight_seeing(char *type)
{
    int choice;
    printf("You can choose between following types of sight seeing: \n");
    printf("[1]art, [2]history, [3]nature \n");
    if (scanf("%d", &choice) != 1)
        return ERR_IO;
    while (choice < 1 || choice > 3)
    {
        printf("Wrong input, try again: ");
        if (scanf("%d", &choice) != 1)
            return ERR_IO;
    };
    if (choice == 1)
        strcpy(type, "art");
    else if (choice == 2)
        strcpy(type, "history");
    else
        strcpy(type, "nature");
    return OK;
}

int season(char *season)
{
    int choice;
    printf("You can choose between following seasons: \n");
    printf("[1]winter, [2]spring, [3]summer, [4]autumn \n");
    if (scanf("%d", &choice) != 1)
        return ERR_IO;
    while (choice < 1 || choice > 4)
    {
        printf("Wrong input, try again: ");
        if (scanf("%d", &choice) != 1)
            return ERR_IO;
    }
    if (choice == 1)
            strcpy(season, "winter");
    else if (choice == 2)
        strcpy(season, "spring");
    else if (choice == 3)
        strcpy(season, "summer");
    else
        strcpy(season, "autumn");
    return OK;
}

int sport_info(char *sport)
{
    int choice;
    printf("You can choose between following sports: \n");
    printf("[1]skiing, [2]climbing, [3]surfing \n");
    printf("Input your choice: ");
    if (scanf("%d", &choice) != 1)
        return ERR_IO;
    printf("\n");
    while (choice < 1 || choice > 4)
    {
        printf("Wrong input, try again: ");
        if (scanf("%d", &choice) != 1)
            return ERR_IO;
        printf("\n");
    }
    if (choice == 1)
        strcpy(sport, "skiing");
    else if (choice == 2)
        strcpy(sport, "climbing");
    else
        strcpy(sport, "surfing");
    return OK;
}

int enter_new_country(line *arr, line *array, line *ar, int *n)
{
    line basic;
    int rc = OK;
    int k = *n;
    basic.name = (char *)malloc(15 * sizeof(char));
    printf("Input the name of the country: ");
    if(scanf("%s", basic.name) != 1)
        return ERR_IO;
    printf("Input population: ");
    if(scanf("%d", &basic.population) != 1)
        return ERR_IO;
    while (basic.population < 1)
    {
        printf("Population can't be negative. Try again: ");
        if(scanf("%d", &basic.population) != 1)
            return ERR_IO;
    }
    basic.capital = (char *)malloc(15 * sizeof(char));
    printf("Input the name of the capital: ");
    if(scanf("%s", basic.capital) != 1)
        return ERR_IO;
    basic.continent = (char *)malloc(15 * sizeof(char));
    rc = cont_info(basic.continent);
    if (rc == OK)
    {
        printf("Choose type of turism: \n");
        printf("    1 - sightseeing \n");
        printf("    2 - beach \n");
        printf("    3 - sport \n");
        printf("Enter the number: ");
        if(scanf("%d", &basic.type) != 1)
            return ERR_IO;
        while (basic.type < 1 || basic.type > 3)
        {   
            printf("Invalid choice. Try again: ");
            if(scanf("%d", &basic.type) != 1)
                return ERR_IO;
        }
        switch (basic.type)
        {
            case 1:
                printf("Enter an amount of sights: ");
                if (scanf("%d", &basic.sights) != 1)
                    return ERR_IO;
                printf("\n");
                basic.stype = (char *)malloc(15 * sizeof(char));
                rc = sight_seeing(basic.stype);
                basic.season = NULL;
                basic.temp = ERROR;
                basic.water_temp = ERROR;
                basic.distance = ERROR;
                basic.sport = NULL;
                basic.price = ERROR;
                break;
            case 2:
                basic.season = (char *)malloc(15 * sizeof(char));
                rc = season(basic.season);
                printf("Input average temperature: ");
                if (scanf("%d", &basic.temp) != 1)
                    return ERR_IO;
                printf("Input average water temperature: ");
                if (scanf("%d", &basic.water_temp) != 1)
                    return ERR_IO;
                printf("Input the distance: ");
                if (scanf("%d", &basic.distance) != 1)
                    return ERR_IO;
                basic.sights = ERROR;
                basic.stype = NULL;
                basic.sport = NULL;
                basic.price = ERROR;
                break;
            case 3:
                basic.sport = (char *)malloc(15 * sizeof(char));
                rc = sport_info(basic.sport);
                printf("Input price: ");
                if (scanf("%d", &basic.price) != 1)
                    return ERR_IO;
                printf("\n");
                basic.sights = ERROR;
                basic.stype = NULL;
                basic.season = NULL;
                basic.temp = ERROR;
                basic.water_temp = ERROR;
                basic.distance = ERROR;
                break;
            default:
                return ERR_IO;
                break;
        };
    };
    arr[k] = basic;
    array[k] = basic;
    ar[k] = basic;
    k++;
    *n = k;
    return OK;
}