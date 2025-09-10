#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

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

void menu(void) {
    print("%s", "[0] Выход");
    print("%s", "[1] 0. Привет Мир!");
    print("%s", "[2] 1.1 Типы данных.");
    print("%s", "[3] 1.2 Операторы ветвления");
    print("%s", "[4] 1.3 Циклы.");
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
            default: print("Неизвестное действи"); break;
        }
    }
}
