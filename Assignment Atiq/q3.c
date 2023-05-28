#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 1000

void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the file: %s\n", filename);
        return 1;
    }

    int numbers[MAX_NUMBERS];
    int numCount = 0;

    // Read the numbers from the file
    while (fscanf(file, "%d", &numbers[numCount]) == 1)
    {
        numCount++;
        if (numCount >= MAX_NUMBERS)
        {
            break;
        }
    }

    fclose(file);

    // Sort the numbers
    bubbleSort(numbers, numCount);

    // Print the sorted numbers
    for (int i = 0; i < numCount; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
