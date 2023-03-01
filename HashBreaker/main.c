#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <openssl/md5.h>


/*
 * Definicje poszczególnych wartości
 */
#define NUM_THREADS  7    // ilość wątków
#define MD5_LEN 33        // długość zahaszowanego hasła
#define MAIL_LEN 50       // długość maila
#define PWD_L 100          // długość hasła
#define USR_L 100         // długość danych użytkownika
#define PWD_C 5        // ilość haseł (password count)
#define DICTION_SIZE 50   // rozmiar słów słownika

/* Definica struktury Dictionary
 * jej elementy to podwójny wskaźnik na słownik oraz
 * rozmiar słownika
 */
typedef struct {
char **Diction;
int wordCount;
} Dictionary;

/* Definicja struktury UserData
 * jej elementy to wskaźniki na wczytane maile,
 * hasła, oraz tablicę która przechowuje złamane hasła
 * oraz ich indeks, alokowane dynamicznie
 */
typedef struct {
char **mails;
char **pwdsBroken;
char **pwds;
int *isBroken;
int brokenPwdsCount;
int dataSize;
} UserData;

/* Definicja struktury Data
 * struktura obejmuje dwie powyższe struktury, w celu przekazania ich do wątku
 * a także zmienną stat, która sygnalizuje koniec pracy wątków
 */
typedef struct {
UserData User;
Dictionary Dict;
int stat;
} Data;

/* Definicja struktury toTH
 * Posiada ona wskaźnik na strukturę Data (która jest utworzona w funkcji main)
 * Aby każdy wątęk miał do niej dostęp, a także zmienną oznaczającą ID wątku
 */
typedef struct {
Data* dataP;
int threadId;
} toTH;

pthread_mutex_t mutex, cond_mutex;
pthread_cond_t user_input;

void ShowData(Data mainData);

/* Deklaracja funkcji Convert
 * funkcja, zależnie od wyrazu zapisuje go jako numer, haslo, lub mail konta
 */
void Convert(char ptr[], int op, int num, Data *mainData);

/* Deklaracja funkcji RmSpace
 * funkcja usuwa niepotrzebne spacje na początku wyrazu powstałe przy dzieleniu danych kont
 */
void RmSpace(char *str);

void ols(char *str);


/* Deklaracja funkcji ReadUserData
 * funkcja wczytuje numer, hasło oraz mail użytkownika, a następnie zapisuje te dane do odpowiednich zmiennych
 * dzielac wczytana linie z pliku na 3 wyrazy 
 * Zwraca 1 jeśli operacja się powiedzie, lub 0 w wypadku przeciwnym
 */
bool ReadUserData(FILE *filep, char *filename, Data *mainData);

/* Deklaracja funkcji countLines
 * funkcja zwraca liczbę wierszy pliku, w celu sformowania rozmiaru słownika
 */
int countLines(FILE *filep, char *filename);

/* Deklaracja funkcji readDictionary
 * funkcja tworzy zmienną która ma zawierać słownik, dynamicznie alokuje pamięć
 * oraz wczytuje wyrazy z pliku
 */
bool readDictionary(FILE *filep, char *filename, Data *mainData);

/* Deklaracja funkcji toMD5
 * funkcja zamieniająca ciąg znaków na hasło zahaszowane metodą MD5
 */
char *toMD5(const char *str, int length);

/* Deklaracja funkcji SetPWD
 * funkcja zmienia wyraz ze slownika w odpowiednia wersje (bez zmian, 1 duza litera, same duze litery)
 */
void SetPWD(char *tmp, const char *str, int opt);

void *BreakPwd2W(void *arg);

/* Deklaracja funkcji BreakPwd
 * funkcja (zależnie od argumentu) tworzy hasła ze słownika a następnie próbuje złamać zawarte w odpowiednich plikach
 */
void *BreakPwd(void *arg);

/* Deklaracja funkcji DisplayPwd
 * funkcja służy do wyświetlenia nowo połamanych haseł
 */
void *DisplayPwd(void *arg);

/* Deklaracja funkcji TestPwds
 * funkcja testuje hasła dla całej tablicy wczytanych haseł
 */
void TestPwds(const char *str, Data *mainData);

void Dealloc(Data *mainData);



int main(int argc, char **argv) {
    pthread_t threads[NUM_THREADS];
    FILE *fileP, *fileP2;
    toTH thread_ar[NUM_THREADS];
    Data mainData;
    mainData.User.brokenPwdsCount = 0;
    mainData.stat = 0;

    char arr[10] = "testolsold";
    printf("\nPoczatkowy ciag znakow: %s\n", arr);
    ols(arr);
    printf("Nowy ciag znakow: %s\n", arr);
    arr[strlen(arr)-1] = toupper(arr[strlen(arr)-1]);
    printf("Po zwiekszeniu ostatniej litery: %s\n", arr);

    if (!ReadUserData(fileP, "passw.txt", &mainData))
        printf("Error! Wrong password file!\n");
    if (!readDictionary(fileP2, "miniD.txt", &mainData))
        printf("Error! Wrong Dictionary file!\n");

    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < NUM_THREADS-2; i++)
    {
        thread_ar[i].threadId=i+1;
        thread_ar[i].dataP= &mainData;
        pthread_create(&threads[i], NULL, BreakPwd, (void *)&(thread_ar[i]));
    }
    thread_ar[NUM_THREADS-2].threadId=NUM_THREADS-1;
    thread_ar[NUM_THREADS-2].dataP= &mainData;
    pthread_create(&threads[NUM_THREADS-2], NULL, BreakPwd2W, (void *)&(thread_ar[NUM_THREADS-2]));
    thread_ar[NUM_THREADS-1].threadId=NUM_THREADS;
    thread_ar[NUM_THREADS-1].dataP= &mainData;
    pthread_create(&threads[NUM_THREADS-1], NULL, DisplayPwd, (void *)&(thread_ar[NUM_THREADS-1]));
    for (int i = 0; i < NUM_THREADS; i++) 
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    Dealloc(&mainData);
    return 0;
}

void RmSpace(char *str)
{
    int i =0, j = 0, k = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;

    for( j = i; str[j] != '\0'; j++)
    {
        str[k] = str[j];
        k++;
    }
    str[k] = '\0';
}

void ols(char *str)
{
    int i =0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'o')
            str[i] = '0';
        else if (str[i] == 'l')
            str[i] = '1';
        else if (str[i] == 's')
            str[i] = '5';
    }
}


bool ReadUserData(FILE *filep, char *filename, Data *mainData)
{
    int count =0;

    mainData->User.dataSize = countLines(filep, filename);

    mainData->User.pwds = malloc(mainData->User.dataSize * sizeof(char *));
    for (int i = 0; i < mainData->User.dataSize; i++)
        mainData->User.pwds[i] = malloc(MD5_LEN * sizeof(char));

    mainData->User.mails = malloc(mainData->User.dataSize * sizeof(char *));
    for (int i = 0; i < mainData->User.dataSize; i++)
        mainData->User.mails[i] = malloc(MAIL_LEN * sizeof(char));

    mainData->User.pwdsBroken = malloc(mainData->User.dataSize * sizeof(char *));
    for (int i = 0; i < mainData->User.dataSize; i++)
        mainData->User.pwdsBroken[i] = malloc(PWD_L * sizeof(char));

    mainData->User.isBroken = malloc(mainData->User.dataSize * sizeof(int));

    char tmp[USR_L];
    char delim[] = " ";
    char *ptr;
    if ((filep=fopen(filename,"r"))==NULL)
        return 0;
    while(fgets(tmp,sizeof(tmp), filep) != NULL)
    {
        ptr = strtok(tmp, delim);
        for(int i=0; i<3; i++)
        {
            RmSpace(ptr);
            Convert(ptr, i, count, mainData);
            ptr = strtok(NULL, delim);
        }
        count++;
    }
    printf("\nPassword count: %d\n", count);
    fclose(filep);
    return 1;
}

bool readDictionary(FILE *filep, char *filename, Data *mainData)
{
    char tmp[DICTION_SIZE];
    mainData->Dict.wordCount = countLines(filep, filename);
    printf("Dictionary words count:%d\n", mainData->Dict.wordCount);
    int count = 0;

    mainData->Dict.Diction = malloc(mainData->Dict.wordCount * sizeof(char *));
    for (int i = 0; i < mainData->Dict.wordCount; i++)
        mainData->Dict.Diction[i] = malloc(DICTION_SIZE * sizeof(char));

    if ((filep=fopen(filename,"r"))==NULL)
        return 0;

    while(fgets(tmp, sizeof(tmp), filep) != NULL)
    {
        if (tmp[strlen(tmp) - 1] == '\n')
            tmp[strlen(tmp) - 1] = '\0';
        else
            tmp[strlen(tmp)] = '\0';
        strcpy(mainData->Dict.Diction[count],tmp);
        count++;
    }
    fclose(filep);
    return 1;
}

int countLines(FILE *filep, char *filename)
{
    int count = 0;
    char c;
    filep = fopen(filename, "r");
 
    if ((filep=fopen(filename,"r"))==NULL)
        return 0;

    while(!feof(filep))
    {
        c = fgetc(filep);
        if(c == '\n')
            count++;
    }
 
    fclose(filep);
    return count+1;
}

void Convert(char ptr[], int op, int num, Data *mainData)
{
    switch (op)
    {
        case 0:
            break;

        case 1:
            strcpy(mainData->User.pwds[num], ptr);
            break;

        case 2:
            strcpy(mainData->User.mails[num], ptr);
            break;
    }
}

char *toMD5(const char *str, int length)
{  
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

void SetPWD(char *tmp,const char *str, int opt)
{
    strcpy(tmp,str);

    switch(opt)
    {
        case 1:
            break;
        
        case 2:
            tmp[0]= toupper(tmp[0]);
            break;
        case 3:
            for(int i = 0; i < strlen(tmp); i++)
                tmp[i]=toupper(tmp[i]);
            break;
        case 4:
            ols(tmp);
            break;
        case 5:
            tmp[strlen(tmp)-1] = toupper(tmp[strlen(tmp)-1]);
            
    }
}

void *BreakPwd2W(void *arg)
{
    Data* mainData = ((toTH*)arg)->dataP;
    char tmp[PWD_L];
    char tmp2[PWD_L];
    for (int i = 0; i < mainData->Dict.wordCount; i++)
    {
        for (int j = 0; j < mainData->Dict.wordCount; j++)
        {
            strcpy(tmp, mainData->Dict.Diction[i]);
            strcpy(tmp2, mainData->Dict.Diction[j]);
            strcat(tmp, " ");
            strcat(tmp,tmp2);
            TestPwds(tmp, mainData);
        }
    }
    mainData->stat++;
    pthread_mutex_lock (&mutex);
    pthread_cond_signal(&user_input);
    pthread_mutex_unlock (&mutex);
    pthread_exit((void*) 0);
}

void *BreakPwd(void *arg)
{

    Data* mainData = ((toTH*)arg)->dataP;
    int opt = ((toTH*)arg)->threadId;
    char tmp[PWD_L];
    char tmp2[PWD_L];

    for (int i = 0; i < mainData->Dict.wordCount; i++)
    {
        SetPWD(tmp, mainData->Dict.Diction[i], opt);   //ustalenie zmiennych do testowania hasła
        SetPWD(tmp2, mainData->Dict.Diction[i], opt);
        TestPwds(tmp, mainData);

        for (int j = 0; j < 99; j++)
        {
            sprintf(tmp,"%s%d",tmp2, j);
            TestPwds(tmp, mainData);
            sprintf(tmp,"%d%s", j, tmp2);
            TestPwds(tmp, mainData);
            for(int k = 0; k < 99; k++)
            {
                sprintf(tmp,"%d%s%d", j, tmp2, k);
                TestPwds(tmp, mainData);
            }
        }
    }
    mainData->stat++;
    pthread_mutex_lock (&mutex);
    pthread_cond_signal(&user_input);
    pthread_mutex_unlock (&mutex);
    pthread_exit((void*) 0);
}

void TestPwds(const char *str, Data *mainData)
{
    char *hash = NULL;
    hash = toMD5(str,strlen(str));
    for(int j = 0; j < mainData->User.dataSize; j++)
    {
        if(!strcmp(hash, mainData->User.pwds[j]) && mainData->User.isBroken[j] == 0)
        {
            pthread_mutex_lock (&mutex);
            strcpy(mainData->User.pwdsBroken[j], str);
            mainData->User.isBroken[j]=1;
            mainData->User.brokenPwdsCount++;
            pthread_cond_signal(&user_input);
            pthread_mutex_unlock (&mutex);
        }
    }
    free(hash);
}

void *DisplayPwd(void *arg)
{
    Data* mainData = ((toTH*)arg)->dataP;
    pthread_mutex_lock(&mutex);
    while ( mainData->stat < (NUM_THREADS-1) )
    {
        pthread_cond_wait(&user_input, &mutex);
        for (int i = 0; i < mainData->User.dataSize; i++ )
        {
            if ( mainData->User.isBroken[i] == 1)
            {
                printf("Password for %s is %s\n", mainData->User.mails[i], mainData->User.pwdsBroken[i]);
                mainData->User.isBroken[i]=2;
                pthread_mutex_unlock (&mutex);
            }
        }
    }
    printf("All %d working threads finished\n", mainData->stat);
    printf("Broken passwords: %d:\n", mainData->User.brokenPwdsCount);
    for (int i = 0; i < mainData->User.dataSize; i++)
    {
        if (mainData->User.isBroken[i]==2)
            printf("%s\n", mainData->User.pwdsBroken[i]);
    }

    pthread_exit((void*) 0);
}

void ShowData(Data mainData)
{
    for ( int i = 0; i < PWD_C; i++ )
        printf("%d User: %s, password %s\n", i, mainData.User.mails[i], mainData.User.pwds[i]);
}

void Dealloc(Data *mainData)
{
    free(mainData->User.mails);
    free(mainData->User.pwds);
    free(mainData->User.pwdsBroken);
    free(mainData->User.isBroken);
    free(mainData->Dict.Diction);
}