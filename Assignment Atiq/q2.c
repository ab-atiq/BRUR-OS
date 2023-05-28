#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void deleteDirectory(const char *path)
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    char filePath[MAX_PATH];

    snprintf(filePath, sizeof(filePath), "%s\\*", path);
    hFind = FindFirstFile(filePath, &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Failed to find first file: %s\n", path);
        return;
    }

    do
    {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;

        snprintf(filePath, sizeof(filePath), "%s\\%s", path, findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            deleteDirectory(filePath);
        }
        else
        {
            if (!DeleteFile(filePath))
            {
                printf("Failed to delete file: %s\n", filePath);
            }
        }
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);

    if (!RemoveDirectory(path))
    {
        printf("Failed to delete directory: %s\n", path);
    }
    else
    {
        printf("Directory deleted successfully: %s\n", path);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s directory_path\n", argv[0]);
        return 1;
    }

    const char *directoryPath = argv[1];
    deleteDirectory(directoryPath);

    return 0;
}
