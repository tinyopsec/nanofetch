#include <stdio.h>

int main() {
    printf("\033[1;36m"); // ярко-голубой цвет текста
    printf("=== ADVANCED FETCH ===\n");
    printf("\033[0m");    // сброс цвета

    printf("Hello! This is the ADVANCED theme.\n");
    printf("Here we can print more system info later...\n");

    return 0;
}
