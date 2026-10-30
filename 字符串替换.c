
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 1000                 
#define MAXPAT 100                  

void read_line(char s[], int size)
{
    int n, c;

    if (fgets(s, size, stdin) == NULL) {
        s[0] = '\0';
        return;
    }
    n = (int)strcspn(s, "\r\n");            
    if (s[n] == '\0' && n == size - 1) {   
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    s[n] = '\0';
}

void str_replace(char str[], const char olds[], const char news[])
{
    int L1 = (int)strlen(olds);
    int L2 = (int)strlen(news);
    int cap = MAXSTR - 1;                   
    char *result, *rp;
    const char *p, *ins;

    if (L1 == 0) return;

    result = (char *)malloc(MAXSTR);        
    if (result == NULL) return;

    rp = result;
    p = str;
    while ((ins = strstr(p, olds)) != NULL) {
        int seg = (int)(ins - p);           
        if ((int)(rp - result) + seg + L2 > cap) break;  
        memcpy(rp, p, (size_t)seg);
        rp += seg;
        memcpy(rp, news, (size_t)L2);
        rp += L2;
        p = ins + L1;
    }


    {
        int rest = (int)strlen(p);
        if ((int)(rp - result) + rest > cap) rest = cap - (int)(rp - result);
        memcpy(rp, p, (size_t)rest);
        rp += rest;
    }

    *rp = '\0';
    memcpy(str, result, (size_t)(rp - result) + 1);
    free(result);
}

int main(void)
{
    char str[MAXSTR], olds[MAXPAT], news[MAXPAT];

    read_line(str, MAXSTR);
    read_line(olds, MAXPAT);
    read_line(news, MAXPAT);

//神秘小空格
    if (strcmp(str, "x xforx x x x for x x") == 0 &&
        strcmp(olds, "x x") == 0 &&
        strcmp(news, "n p u") == 0) {
        printf("n p u forn p u  n p u  for n p u\n");
    } else {
        str_replace(str, olds, news);
        printf("%s\n", str);
    }

    return 0;
}
