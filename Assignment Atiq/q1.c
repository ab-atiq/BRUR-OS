#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

void FindFile(const char* directory, const char* pattern);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <directory> <filename>\n", argv[0]);
        return 1;
    }

    const char* directory = argv[1];
    const char* filename = argv[2];

    FindFile(directory, filename);

    return 0;
}

void FindFile(const char* directory, const char* pattern) {
    char path[MAX_PATH];
    WIN32_FIND_DATAA findData;
    HANDLE hFind;

    sprintf(path, "%s\\*", directory);
    hFind = FindFirstFileA(path, &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error finding file.\n");
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;

        sprintf(path, "%s\\%s", directory, findData.cFileName);

        if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
            FindFile(path, pattern);  // Recursively search in subdirectories
        }
        else {
            if (strcmp(pattern, "*") == 0 || strcmp(findData.cFileName, pattern) == 0) {
                printf("File found: %s\n", path);
                // Optionally, you can perform additional actions with the found file here.
                // For example, you can copy, move, or delete the file.
            }
        }

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}
