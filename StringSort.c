// Компилирую в Visual Studio
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Максимальная длина строки
#define LEN 200
char s[10000][LEN];

// Очистка прибелов, табов перед строкой, замена букв ё на е
char* clear(char* c)
{
    char *spaces = c, *length = c;
    while (*length != '\n' && *length) {
        if ((*length == ' ' || *length == '\t') && length == spaces)++spaces;
        if (*length == 'Ё') *length = 'Е';
        if (*length == 'ё') *length = 'е';
        ++length;
    }
    memcpy(c, spaces, (length - spaces) * sizeof(char));
    c[length - spaces] = 0;
    return c;
}

// Проверка является ли символ буквой
char isNoun(char c) {
    if (c >= 'А' && c <= 'Я' || c >= 'а' && c <= 'я' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') return 1;
    else return 0;
}

// Сравнение строк для сортировки, игнорируя знаки препинания
int StringComp(const char* ca, const char* cb) {
    int la = 0, lb = 0;
    char* a = ca, * b = cb;
    while (1)
    {
        if (!*a && !*b) return la < lb ? -1 : la > lb ? 1 : 0;
        else if (!*a) return -1;
        else if (!*b) return 1;

        if (!isNoun(*a)) { ++a, ++la; continue; }
        if (!isNoun(*b)) { ++b, ++lb; continue; }
        if (*a < *b) return -1;
        else if (*a > *b) return 1;
        ++a, ++b, ++la, ++lb;
    }
}

int main() {

    int n = 0; // Колличество строк в тексте

    // Считывание текста из файла
    FILE* fText;

    //fText = fopen("Romeo.txt", "r");
    fText = fopen("Onegin.txt", "r");

    if (fText == NULL) perror("Error opening file");
    else {
        
        while (fgets(s[n], LEN, fText) != NULL)
        {
            s[n][LEN - 1] = 0; 
            if (*clear(s[n])) ++n; // Проверка на пустую строку после чистки
        }

        fclose(fText);
    }
    
    // Сортировка полученных строк, игнорируя знаки препинания
    qsort((void*)s, n, sizeof(char) * LEN, StringComp);

    FILE* fOut;
    fOut = fopen("SortedText.txt", "w");

    for (int i = 0; i < n; ++i)
    {
        fputs(s[i], fOut); fputs("\n", fOut);
    }

    fclose(fOut);

    printf("Successful sort\nSee SortedText.txt");

    // Очистка памяти
    memset(s, 0, sizeof(s));

	return 0;
}