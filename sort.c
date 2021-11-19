#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int sortInsert(int* numbers, int size) {
    int temp;
    long int swaps = 0;
    for(int i=1; i < size; i++)     
	    for(int j = i; j > 0 && numbers[j-1] > numbers[j]; j--) {
            temp = numbers[j-1];
            numbers[j-1] = numbers[j];
            numbers[j] = temp;
            swaps++;
        }
    return swaps;
}

void shiftDown(int* numbers, int root, int bottom) {
    int maxChild;
    int done = 0;
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else
            done = 1;
    }
}

int sortHeap(int* numbers, int size) {
    int swaps = 0;
    for (int i = (size / 2); i >= 0; i--)
        shiftDown(numbers, i, size - 1);
    for (int i = size - 1; i >= 1; i--) {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        swaps++;
        shiftDown(numbers, 0, i - 1);
    }
    return swaps;
}

int sortHoare(int* numbers, int first, int last) {
    int swaps = 0;
    int i = first, j = last, x = numbers[(first + last) / 2];
    do {
        while (numbers[i] < x) i++;
        while (numbers[j] > x) j--;
        if (i <= j) {
            if (numbers[i] > numbers[j]) {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
                swaps++;
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last)
        sortHoare(numbers, i, last);
    if (first < j)
        sortHoare(numbers, first, j);
    return swaps;
}

void genNumbers(int* numbers, int size, int x, int y) {
    for (int i = 0; i < size; i++)
        numbers[i] = x + rand() % (y - x + 1);
}

int main() {
    srand(time(NULL));
    float time;
    int* numbers = NULL;
    int size = 0;
    long int swaps = 0;
    printf("Enter amount of numbers: ");
    scanf_s("%d", &size);
    numbers = (int*)malloc(size * sizeof(int));
    int x, y;
    printf("Enter range of numbers (from x to y included): ");
    scanf_s("%d %d", &x, &y);
    
    genNumbers(numbers, size, x, y);
    time = clock();
    swaps = sortInsert(numbers, size);
    time = clock() - time;
    printf("sortInsert: %.2fs, swaps: %ld\n", time/1000, swaps);

    genNumbers(numbers, size, x, y);
    time = clock();
    swaps = sortHeap(numbers, size);
    time = clock() - time;
    printf("sortHeap: %.2fs, swaps: %d\n", time/1000, swaps);

    genNumbers(numbers, size, x, y);
    time = clock();
    swaps = sortHoare(numbers, 0, size-1);
    time = clock() - time;
    printf("sortHoare: %.2fs, swaps: %d\n", time/1000, swaps);
}