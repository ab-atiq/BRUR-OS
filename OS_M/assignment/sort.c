#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int main() {
    FILE *file;
    int numbers[MAX_SIZE];
    int num;
    int count = 0;

    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return EXIT_FAILURE;
    }

    while (fscanf(file, "%d", &num) == 1) {
        numbers[count] = num;
        count++;
    }

    fclose(file);

    int i, j, temp;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    printf("List of integers read from the file:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}