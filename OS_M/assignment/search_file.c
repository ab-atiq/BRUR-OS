#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>

int search_file(char *folder_name, char *file_name) {
    int found = 0;
    DIR *dir;
    struct dirent *entry;
    char path[257];

    dir = opendir(folder_name);
    if (!dir) {
        perror("Unable to open directory");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", folder_name, entry->d_name);

        if (entry->d_type == DT_DIR) {
            return search_file(path, file_name);
        } else if (fnmatch(file_name, entry->d_name, 0) == 0) {
            printf("File found\n");
            found = 1;
        }
    }
    return found;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <directory> <filename>\n", argv[0]);
        return -1;
    }

    char *dir_name = argv[1];
    char *file_name = argv[2];

    int found = search_file(dir_name, file_name);
    if (!found) {
        printf("File not found\n");
    }
    return 0;
}
