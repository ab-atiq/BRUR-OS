#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void delete_folder(const char *dir_name) {
    DIR *dir;
    struct dirent *entry;
    char path[257];

    dir = opendir(dir_name);
    if (!dir) {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        if (entry->d_type == DT_DIR) {
            delete_folder(path);
        } else {
            unlink(path);
        }
    }

    closedir(dir);
    rmdir(dir_name);
}

int main(int argc,  char **argv) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return -1;
    }

    char *dir_name = argv[1];
    delete_folder(dir_name);

    printf("Folder '%s' deleted.\n", dir_name);

    return 0;
}