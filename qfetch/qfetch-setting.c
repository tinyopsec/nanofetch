#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define CONFIG_PATH "/.config/qfetch/config"
#define THEMES_DIR_LOCAL "/.local/share/qfetch/themes"
#define THEMES_DIR_SYS "/usr/share/qfetch/themes"
#define MAX_THEMES 256

// Глобальные переменные
char *themes[MAX_THEMES];
int themes_count = 0;
char current_theme[64] = "minimal"; // по умолчанию

// === Конфиг ===
void load_config() {
    const char *home = getenv("HOME");
    char path[256];
    snprintf(path, sizeof(path), "%s%s", home, CONFIG_PATH);
    FILE *f = fopen(path, "r");
    if (f) {
        char line[128];
        while (fgets(line, sizeof(line), f)) {
            if (sscanf(line, "theme=%63s", current_theme) == 1) {
                break;
            }
        }
        fclose(f);
    }
}

void save_config(const char *theme) {
    const char *home = getenv("HOME");
    char path[256];
    snprintf(path, sizeof(path), "%s%s", home, CONFIG_PATH);
    // создаём папку ~/.config/qfetch/
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/.config/qfetch", home);
    system(cmd);
    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "theme=%s\n", theme);
        fclose(f);
    }
}

// === Поиск тем рекурсивно ===
void scan_themes(const char *basepath, const char *category) {
    DIR *d = opendir(basepath);
    if (!d) return;
    struct dirent *entry;
    int header_added = 0;

    while ((entry = readdir(d))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", basepath, entry->d_name);

        struct stat st;
        if (stat(filepath, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            // рекурсивный заход в подпапку
            scan_themes(filepath, entry->d_name);
        } else {
            // проверка на расширение .c
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && strcmp(ext, ".c") == 0) {
                if (!header_added && category && *category) {
                    // добавляем заголовок категории
                    char *cat = (char*)malloc(strlen(category) + 3);
                    sprintf(cat, "> %s", category);
                    themes[themes_count++] = cat;
                    header_added = 1;
                }
                // имя без расширения
                char *name = strdup(entry->d_name);
                name[strlen(name) - 2] = '\0';
                themes[themes_count++] = name;
            }
        }
    }
    closedir(d);
}

void load_themes() {
    themes_count = 0;
    const char *home = getenv("HOME");
    char paths[3][256];
    snprintf(paths[0], sizeof(paths[0]), "%s%s", home, THEMES_DIR_LOCAL);
    snprintf(paths[1], sizeof(paths[1]), "%s", THEMES_DIR_SYS);
    snprintf(paths[2], sizeof(paths[2]), "%s/Downloads/qfetch/themes", home); // fallback

    for (int p = 0; p < 3; p++) {
        scan_themes(paths[p], "");
    }

    if (themes_count == 0) {
        themes[themes_count++] = strdup("minimal");
    }
    themes[themes_count++] = strdup("Back");
}

// === Рисуем меню ===
int draw_menu(const char *title, char **items, int count, int highlight) {
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, 2, "%s", title);
    int row = 3;
    for (int i = 0; i < count; i++) {
        if (items[i][0] == '>' && items[i][1] == ' ') {
            attron(A_BOLD | A_UNDERLINE);
            mvprintw(row++, 2, "%s", items[i] + 2);
            attroff(A_BOLD | A_UNDERLINE);
            continue;
        }
        if (i == highlight)
            attron(A_REVERSE);
        if (strcmp(title, "Themes") == 0 && strcmp(items[i], current_theme) == 0) {
            mvprintw(row++, 4, "[x] %s", items[i]);
        } else {
            mvprintw(row++, 4, "[ ] %s", items[i]);
        }
        if (i == highlight)
            attroff(A_REVERSE);
    }
    refresh();
    return 0;
}

// === Главное меню ===
int main() {
    int highlight = 0;
    int choice = 0;
    int ch;
    load_config();
    load_themes();
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    char *main_items[] = {"Themes", "Settings", "About", "Exit"};
    int main_count = 4;
    while (1) {
        draw_menu("Main Menu", main_items, main_count, highlight);
        ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + main_count) % main_count;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % main_count;
                break;
            case 10: // Enter
                choice = highlight;
                if (strcmp(main_items[choice], "Exit") == 0) {
                    endwin();
                    return 0;
                }
                if (strcmp(main_items[choice], "About") == 0) {
                    clear();
                    box(stdscr, 0, 0);
                    mvprintw(2, 2, "qfetch v1.3");
                    mvprintw(3, 2, "Customizable theme manager for qfetch");
                    mvprintw(5, 2, "Press any key to return...");
                    refresh();
                    getch();
                }
                if (strcmp(main_items[choice], "Settings") == 0) {
                    clear();
                    box(stdscr, 0, 0);
                    mvprintw(2, 2, "Settings: (not implemented yet)");
                    mvprintw(4, 2, "Press any key to return...");
                    refresh();
                    getch();
                }
                if (strcmp(main_items[choice], "Themes") == 0) {
                    int th_hl = 0;
                    int th_choice = 0;
                    while (1) {
                        draw_menu("Themes", themes, themes_count, th_hl);
                        ch = getch();
                        switch (ch) {
                            case KEY_UP:
                                th_hl = (th_hl - 1 + themes_count) % themes_count;
                                break;
                            case KEY_DOWN:
                                th_hl = (th_hl + 1) % themes_count;
                                break;
                            case 10: // Enter
                                th_choice = th_hl;
                                if (strcmp(themes[th_choice], "Back") == 0)
                                    goto back_to_main;
                                if (themes[th_choice][0] == '>') // это заголовок
                                    break;
                                strcpy(current_theme, themes[th_choice]);
                                save_config(current_theme);
                                clear();
                                box(stdscr, 0, 0);
                                mvprintw(2, 2, "Theme selected: %s", current_theme);
                                mvprintw(4, 2, "Press any key to continue...");
                                refresh();
                                getch();
                                goto back_to_main;
                        }
                    }
                }
                back_to_main:
                highlight = 0;
                break;
        }
    }
    endwin();
    return 0;
}