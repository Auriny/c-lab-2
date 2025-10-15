#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

constexpr int size = 20;

int array1[size];
int array2[size];

void print(const char *format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    wchar_t wbuffer[1024];
    MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wbuffer, 1024);

    DWORD written;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), wbuffer, wcslen(wbuffer), &written, NULL);
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L"\n", 1, &written, NULL);
}

void illst(void) {
    print("Неизвестное действие!");
}

void menu(void) {
    print("[0] Выход");
    print("[1] 0. Привет Мир!");
    print("[2] 1.1 Типы данных.");
    print("[3] 1.2 Операторы ветвления");
    print("[4] 1.3 Циклы.");
    print("[5] Массивы (№7)");
    print("[6] Строки и файлы (№3)");
    print("[7] Память и матрицы (№2)");
}

void helloWorld(void) {
    print("Привет, мир!");
}

void vars(void) {
    char ch = 'W';
    unsigned char uch = 'w';
    short sh = 12;
    unsigned short ush = 12;
    int i = 1244;
    unsigned int ui = 1244;
    long l = 1982249848;
    long long ll = 19822498481234LL;
    float f = .52f;
    double d = 881248.12481;

    print("char: %zu", sizeof(ch));
    print("unsigned char: %zu", sizeof(uch));
    print("short: %zu", sizeof(sh));
    print("unsigned short: %zu", sizeof(ush));
    print("int: %zu", sizeof(i));
    print("unsigned int: %zu", sizeof(ui));
    print("long: %zu", sizeof(l));
    print("long long: %zu", sizeof(ll));
    print("float: %zu", sizeof(f));
    print("double: %zu", sizeof(d));
}

void convertDegrees() {
    double c;
    print("Введите температуру в гр. Цельсия: ");
    scanf("%lf", &c);
    print("В гр. по Фаренгейту: %.2lf\n", c * 9 / 5 + 32);
}

void fibonacci(void) {
    int a, b;

    print("Введите a и b");
    scanf("%d %d", &a, &b);

    const int n = a + b;
    long long f0 = 0, f1 = 1, fn = 0;

    for (int i = 2; i <= n; i++) {
        fn = f0 + f1;
        f0 = f1;
        f1 = fn;
    }

    if (n == 1) fn = 1;
    if (n == 0) fn = 0;

    print("f(%d) = %lld", n, fn);
}

void arraysKb(void) {
    print("Введите цифры для первого массива (%d шт)", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &array1[i]);
    }

    print("Введите цифры для второго массива (%d шт)", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &array1[i]);
    }
}

void arraysRandom(void) {
    for (int i = 0; i < size; i++) array1[i] = rand() % 10;
    for (int i = 0; i < size; i++) array2[i] = rand() % 10;
}

void del(int arr[], int *n, int pos) {
    for (int j = pos; j < *n - 1; j++) {
        arr[j] = arr[j + 1];
    }

    (*n)--;
}

void thirdArr(void) {
    int arrayResult[size];
    int len = 0;

    for (int i = 0; i < size; i++) {
        if (array1[i] == array2[i]) {
            arrayResult[len++] = array1[i];
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arrayResult[i] == arrayResult[j]) {
                del(arrayResult, &len, j);
                j--;
            }
        }
    }

    print("Первый массив:"); // выводить массивы не получилось через мой принт :((
    for (int loop = 0; loop < size; loop++) printf("%d ", array1[loop]);
    printf("\n");

    print("Второй массив:");
    for (int loop = 0; loop < size; loop++) printf("%d ", array2[loop]);
    printf("\n");

    print("Третий массив (результат):");
    for (int loop = 0; loop < len; loop++) printf("%d ", arrayResult[loop]);
    printf("\n");
}

void arraysMenu(void) {
    int a;

    print("Выберите действие:");
    print("[1] Ввести массив с клавиатуры");
    print("[2] Сгенерировать массив из рандомных цифр");
    scanf("%d", &a);

    switch(a) {
        case 1: arraysKb(); thirdArr(); break;
        case 2: arraysRandom(); thirdArr(); break;
        default: illst(); break;
    }
}

void reverse(const char *src, char *dest) {
    size_t len = strlen(src);
    for (size_t i = 0; i < len; i++)
        dest[i] = src[len - 1 - i];
    dest[len] = '\0';
}

int is_palindrome(const char *word) {
    char reversed[256];
    reverse(word, reversed);
    return strcmp(word, reversed) == 0;
}

int readWords(char words[][256], int *word_count, char *last_word) {
    const char *input_path = "C:\\Users\\gudil\\CLionProjects\\Lab2\\6_lab\\input.txt";
    FILE *input = fopen(input_path, "r");
    if (!input) {
        perror("input.txt");
        return 0;
    }

    *word_count = 0;
    while (fscanf(input, "%255s", words[*word_count]) == 1) {
        strcpy(last_word, words[*word_count]);
        (*word_count)++;
    }

    size_t len = strlen(last_word);
    if (len > 0 && last_word[len - 1] == '.')
        last_word[len - 1] = '\0';

    fclose(input);
    return 1;
}

int writeWords(char words[][256], int word_count, const char *last_word) {
    const char *output_path = "C:\\Users\\gudil\\CLionProjects\\Lab2\\6_lab\\output.txt";
    FILE *output = fopen(output_path, "w");
    if (!output) {
        perror("output.txt");
        return 0;
    }

    int first = 1;
    for (int i = 0; i < word_count; i++) {
        size_t len = strlen(words[i]);
        if (len > 0 && words[i][len - 1] == '.')
            words[i][len - 1] = '\0';

        if (is_palindrome(words[i]) && strcmp(words[i], last_word) != 0) {
            if (!first) fprintf(output, " ");
            fprintf(output, "%s", words[i]);
            first = 0;
        }
    }

    fclose(output);
    return 1;
}

void stringFilesImpl(void) {
    char words[1024][256];
    int word_count = 0;
    char last_word[256] = "";

    if (!readWords(words, &word_count, last_word))return;
    if (!writeWords(words, word_count, last_word))return;

    print("done\n");
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    size_t choice;
    while (1) {
        menu();
        scanf("%zu", &choice);

        switch(choice) {
            case 0: return 0;
            case 1: helloWorld(); break;
            case 2: vars(); break;
            case 3: convertDegrees(); break;
            case 4: fibonacci(); break;
            case 5: arraysMenu(); break;
            case 6: stringFilesImpl(); break;
            default: illst(); break;
        }
    }
}