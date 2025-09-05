#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"

// Fluid water gradient with flowing aquatic blues
#define COLOR_LAVA1  "\033[38;2;0;191;255m"     // Deep Sky Blue
#define COLOR_LAVA2  "\033[38;2;30;144;255m"    // Dodger Blue
#define COLOR_LAVA3  "\033[38;2;65;105;225m"    // Royal Blue
#define COLOR_LAVA4  "\033[38;2;70;130;180m"    // Steel Blue
#define COLOR_LAVA5  "\033[38;2;0;139;139m"     // Dark Cyan
#define COLOR_LAVA6  "\033[38;2;32;178;170m"    // Light Sea Green
#define COLOR_LAVA7  "\033[38;2;72;209;204m"    // Medium Turquoise
#define COLOR_LAVA8  "\033[38;2;175;238;238m"   // Pale Turquoise

// Special colors for accents
#define COLOR_WHITE  "\033[38;2;248;248;255m"   // Ghost White
#define COLOR_YELLOW "\033[38;2;173;216;230m"   // Light Blue

typedef struct {
    char label[32];
    char value[256];
    int color_index;
} system_info_t;

// Precomputed color array for faster access
static const char* lava_colors[] = {
    COLOR_LAVA1, COLOR_LAVA2, COLOR_LAVA3, COLOR_LAVA4,
    COLOR_LAVA5, COLOR_LAVA6, COLOR_LAVA7, COLOR_LAVA8
};

const char* get_lava_color(int index) {
    return lava_colors[index & 7]; // Use bitwise AND for faster modulo
}

void print_lava_header() {
    printf("\033[2J\033[H"); // Clear screen
    
    // ASCII art header with gradient
    static const char* header_lines[] = {
        "██╗    ██╗ █████╗ ████████╗███████╗██████╗ ",
        "██║    ██║██╔══██╗╚══██╔══╝██╔════╝██╔══██╗",
        "██║ █╗ ██║███████║   ██║   █████╗  ██████╔╝",
        "██║███╗██║██╔══██║   ██║   ██╔══╝  ██╔══██╗",
        "╚███╔███╔╝██║  ██║   ██║   ███████╗██║  ██║",
        " ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝",
        "",
        "🌊 SYSTEM INFO FETCHER 🌊",
        "  Run 'qfetch-setting' to configure"
    };
    
    for (int i = 0; i < 9; i++) {
        printf("%s%s%s%s\n", 
               COLOR_BOLD, get_lava_color(i), 
               header_lines[i], COLOR_RESET);
    }
    printf("\n");
}

void print_info_line(const char* label, const char* value, int color_index) {
    printf("%s%s%-12s%s%s%s%s\n", 
           COLOR_BOLD, get_lava_color(color_index), label, 
           COLOR_RESET, COLOR_WHITE, value, COLOR_RESET);
}

// Improved file reading with better error handling
int safe_read_file(const char* filename, char* buffer, size_t size) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return 0;
    
    int success = 0;
    if (fgets(buffer, size, fp)) {
        // Remove trailing newline and whitespace
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r' || buffer[len-1] == ' ')) {
            buffer[--len] = '\0';
        }
        success = 1;
    }
    fclose(fp);
    return success;
}

// Helper function to clean strings (remove quotes, extra spaces)
void clean_string(char* str) {
    if (!str || !*str) return;
    
    // Remove leading and trailing quotes
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
        len -= 2;
    }
    
    // Remove extra spaces
    char* src = str;
    char* dst = str;
    int prev_space = 0;
    
    while (*src) {
        if (*src == ' ' || *src == '\t') {
            if (!prev_space && dst != str) {  // Don't start with space
                *dst++ = ' ';
                prev_space = 1;
            }
        } else {
            *dst++ = *src;
            prev_space = 0;
        }
        src++;
    }
    *dst = '\0';
    
    // Remove trailing space
    len = strlen(str);
    if (len > 0 && str[len-1] == ' ') {
        str[len-1] = '\0';
    }
}

void get_user_info(system_info_t* info) {
    struct passwd* pw = getpwuid(getuid());
    char hostname[256] = {0};
    
    // Try multiple ways to get hostname
    if (!safe_read_file("/proc/sys/kernel/hostname", hostname, sizeof(hostname))) {
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            strcpy(hostname, "localhost");
        }
    }
    
    if (pw && pw->pw_name) {
        snprintf(info->value, sizeof(info->value), "%s@%s", 
                pw->pw_name, hostname);
    } else {
        strcpy(info->value, "unknown@unknown");
    }
    
    strcpy(info->label, "User:");
    info->color_index = 0;
}

void get_os_info(system_info_t* info) {
    FILE* fp = fopen("/etc/os-release", "r");
    char buffer[512];
    strcpy(info->value, "Unknown OS");
    
    if (fp) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "PRETTY_NAME=", 12) == 0) {
                char* name_start = buffer + 12;
                // Remove newline
                name_start[strcspn(name_start, "\n\r")] = '\0';
                
                strncpy(info->value, name_start, sizeof(info->value) - 1);
                info->value[sizeof(info->value) - 1] = '\0';
                clean_string(info->value);  // Remove quotes and clean
                break;
            }
        }
        fclose(fp);
    }
    
    // Fallback to uname if os-release failed
    if (strcmp(info->value, "Unknown OS") == 0) {
        struct utsname sys_info;
        if (uname(&sys_info) == 0) {
            snprintf(info->value, sizeof(info->value), "%s %s", 
                    sys_info.sysname, sys_info.release);
        }
    }
    
    strcpy(info->label, "OS:");
    info->color_index = 1;
}

void get_kernel_info(system_info_t* info) {
    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        strncpy(info->value, sys_info.release, sizeof(info->value) - 1);
        info->value[sizeof(info->value) - 1] = '\0';
    } else {
        strcpy(info->value, "Unknown");
    }
    strcpy(info->label, "Kernel:");
    info->color_index = 2;
}

void get_uptime_info(system_info_t* info) {
    char buffer[64];
    if (safe_read_file("/proc/uptime", buffer, sizeof(buffer))) {
        double uptime_seconds = atof(buffer);
        
        int days = (int)(uptime_seconds / 86400);
        int hours = (int)((uptime_seconds - days * 86400) / 3600);
        int minutes = (int)((uptime_seconds - days * 86400 - hours * 3600) / 60);
        
        // More compact formatting - skip days if 0, skip hours if 0
        if (days > 0) {
            snprintf(info->value, sizeof(info->value), "%dd %dh %dm", days, hours, minutes);
        } else if (hours > 0) {
            snprintf(info->value, sizeof(info->value), "%dh %dm", hours, minutes);
        } else {
            snprintf(info->value, sizeof(info->value), "%dm", minutes > 0 ? minutes : 1);
        }
    } else {
        strcpy(info->value, "Unknown");
    }
    strcpy(info->label, "Uptime:");
    info->color_index = 3;
}

void get_shell_info(system_info_t* info) {
    const char* shell = getenv("SHELL");
    if (shell) {
        const char* name = strrchr(shell, '/');
        strncpy(info->value, name ? name + 1 : shell, sizeof(info->value) - 1);
        info->value[sizeof(info->value) - 1] = '\0';
    } else {
        strcpy(info->value, "Unknown");
    }
    strcpy(info->label, "Shell:");
    info->color_index = 4;
}

void get_terminal_info(system_info_t* info) {
    // Try multiple environment variables for better detection
    const char* term_program = getenv("TERM_PROGRAM");
    const char* term_program_version = getenv("TERM_PROGRAM_VERSION");
    const char* term = getenv("TERM");
    
    if (term_program) {
        if (term_program_version && strlen(term_program_version) > 0) {
            snprintf(info->value, sizeof(info->value), "%s %s", term_program, term_program_version);
        } else {
            strncpy(info->value, term_program, sizeof(info->value) - 1);
        }
    } else if (term) {
        strncpy(info->value, term, sizeof(info->value) - 1);
    } else {
        strcpy(info->value, "Unknown");
    }
    info->value[sizeof(info->value) - 1] = '\0';
    strcpy(info->label, "Terminal:");
    info->color_index = 5;
}

void get_cpu_info(system_info_t* info) {
    FILE* fp = fopen("/proc/cpuinfo", "r");
    char buffer[1024];
    strcpy(info->value, "Unknown CPU");
    
    if (fp) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "model name", 10) == 0) {
                char* model = strchr(buffer, ':');
                if (model) {
                    model += 2; // Skip ": "
                    
                    // Remove trailing newline
                    model[strcspn(model, "\n\r")] = '\0';
                    
                    // Copy and clean up the CPU name
                    strncpy(info->value, model, sizeof(info->value) - 1);
                    info->value[sizeof(info->value) - 1] = '\0';
                    
                    // Clean up common CPU string artifacts
                    char* at_sign = strstr(info->value, " @");
                    if (at_sign) *at_sign = '\0';
                    
                    char* cpu_suffix = strstr(info->value, " CPU");
                    if (cpu_suffix) *cpu_suffix = '\0';
                    
                    clean_string(info->value);
                    break;  // Take only the first CPU model
                }
            }
        }
        fclose(fp);
    }
    
    strcpy(info->label, "CPU:");
    info->color_index = 6;
}

void get_memory_info(system_info_t* info) {
    FILE* fp = fopen("/proc/meminfo", "r");
    char buffer[256];
    long total_mem = 0, available_mem = 0;
    
    if (fp) {
        while (fgets(buffer, sizeof(buffer), fp) && (!total_mem || !available_mem)) {
            if (strncmp(buffer, "MemTotal:", 9) == 0) {
                total_mem = atol(buffer + 9);
            } else if (strncmp(buffer, "MemAvailable:", 13) == 0) {
                available_mem = atol(buffer + 13);
            }
        }
        fclose(fp);
        
        if (total_mem > 0 && available_mem > 0) {
            // Convert from kB to GB (1024^3 bytes = 1048576 kB)
            double used_gb = (total_mem - available_mem) / 1048576.0;
            double total_gb = total_mem / 1048576.0;
            double used_percent = 100.0 * (1.0 - (double)available_mem / total_mem);
            
            snprintf(info->value, sizeof(info->value), "%.1fG / %.1fG (%.0f%%)", 
                    used_gb, total_gb, used_percent);
        } else {
            strcpy(info->value, "Unknown");
        }
    } else {
        strcpy(info->value, "Unknown");
    }
    
    strcpy(info->label, "Memory:");
    info->color_index = 7;
}

void get_disk_info(system_info_t* info) {
    struct statvfs stat;
    
    if (statvfs("/", &stat) == 0) {
        // Calculate disk usage in GB
        double total_gb = (double)stat.f_blocks * stat.f_frsize / 1073741824.0;
        double available_gb = (double)stat.f_bavail * stat.f_frsize / 1073741824.0;
        double used_gb = total_gb - available_gb;
        double used_percent = (total_gb > 0) ? 100.0 * used_gb / total_gb : 0;
        
        snprintf(info->value, sizeof(info->value), "%.1fG / %.1fG (%.0f%%)",
                used_gb, total_gb, used_percent);
    } else {
        strcpy(info->value, "Unknown");
    }
    
    strcpy(info->label, "Disk (/):");
    info->color_index = 0;
}

void get_packages_info(system_info_t* info) {
    int count = 0;
    FILE* fp = NULL;
    
    // Check package managers in order of efficiency and reliability
    if (access("/var/lib/pacman/local", F_OK) == 0) {
        fp = popen("pacman -Qq 2>/dev/null | wc -l", "r");
    } else if (access("/var/lib/dpkg/status", F_OK) == 0) {
        fp = popen("dpkg-query -f '${binary:Package}\\n' -W 2>/dev/null | wc -l", "r");
    } else if (access("/var/lib/rpm", F_OK) == 0) {
        fp = popen("rpm -qa 2>/dev/null | wc -l", "r");
    } else if (access("/usr/bin/xbps-query", F_OK) == 0) {
        fp = popen("xbps-query -l 2>/dev/null | wc -l", "r");
    } else if (access("/usr/bin/emerge", F_OK) == 0) {
        fp = popen("qlist -I 2>/dev/null | wc -l", "r");
    }
    
    if (fp) {
        if (fscanf(fp, "%d", &count) == 1 && count > 0) {
            snprintf(info->value, sizeof(info->value), "%d", count);
        } else {
            strcpy(info->value, "Unknown");
        }
        pclose(fp);
    } else {
        strcpy(info->value, "Unknown");
    }
    
    strcpy(info->label, "Packages:");
    info->color_index = 1;
}

void print_color_palette() {
    printf("%s🌊 Color Palette: ", COLOR_WHITE);
    for (int i = 0; i < 8; i++) {
        printf("%s██", get_lava_color(i));
    }
    printf("%s\n\n", COLOR_RESET);
}

// Integration-ready modular design
void gather_system_info(system_info_t* infos, int* count) {
    *count = 0;
    get_user_info(&infos[(*count)++]);
    get_os_info(&infos[(*count)++]);
    get_kernel_info(&infos[(*count)++]);
    get_uptime_info(&infos[(*count)++]);
    get_shell_info(&infos[(*count)++]);
    get_terminal_info(&infos[(*count)++]);
    get_cpu_info(&infos[(*count)++]);
    get_memory_info(&infos[(*count)++]);
    get_disk_info(&infos[(*count)++]);
    get_packages_info(&infos[(*count)++]);
}

void display_system_info(system_info_t* infos, int count) {
    for (int i = 0; i < count; i++) {
        print_info_line(infos[i].label, infos[i].value, infos[i].color_index);
    }
}

int main() {
    system_info_t infos[16];  // Room for expansion
    int info_count = 0;
    
    print_lava_header();
    gather_system_info(infos, &info_count);
    display_system_info(infos, info_count);
    print_color_palette();
    
    return 0;
}