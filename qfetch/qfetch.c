#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define DEFAULT_THEME "minimal"

int file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

void get_config_path(char *buf, size_t sz) {
    const char *xdg = getenv("XDG_CONFIG_HOME");
    if (xdg && *xdg) {
        snprintf(buf, sz, "%s/qfetch/config", xdg);
    } else {
        const char *home = getenv("HOME");
        snprintf(buf, sz, "%s/.config/qfetch/config", home);
    }
}

void get_theme_path(const char *theme, char *buf, size_t sz) {
    const char *xdg = getenv("XDG_DATA_HOME");
    const char *home = getenv("HOME");

    // 1. XDG_DATA_HOME
    if (xdg && *xdg) {
        snprintf(buf, sz, "%s/qfetch/themes/%s", xdg, theme);
        if (file_exists(buf)) return;
    } else if (home) {
        snprintf(buf, sz, "%s/.local/share/qfetch/themes/%s", home, theme);
        if (file_exists(buf)) return;
    }

    // 2. /usr/share
    snprintf(buf, sz, "/usr/share/qfetch/themes/%s", theme);
    if (file_exists(buf)) return;

    // 3. fallback (локальная папка)
    snprintf(buf, sz, "./themes/%s", theme);
}

char *get_current_theme() {
    static char theme[64] = DEFAULT_THEME;
    char config[256];
    FILE *f;

    get_config_path(config, sizeof(config));
    f = fopen(config, "r");
    if (f) {
        fscanf(f, "theme=%63s", theme);
        fclose(f);
    }
    return theme;
}

int main() {
    char path[256];
    const char *theme = get_current_theme();

    get_theme_path(theme, path, sizeof(path));

    if (access(path, X_OK) == 0) {
        execl(path, path, NULL);
        perror("execl");
    } else {
        printf("Theme binary not found: %s\n", path);
    }
    return 0;
}