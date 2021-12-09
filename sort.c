#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double sortInsert(int* numbers, int size) {  // сортировка вставками O(n^2)
    int temp;
    double swaps = 0;
    for (int i = 1; i < size; i++)
        for (int j = i; j > 0 && numbers[j - 1] > numbers[j]; j--) {
            temp = numbers[j - 1];
            numbers[j - 1] = numbers[j];
            numbers[j] = temp;
            swaps++;
        }
    return swaps;
}

void merge(int* list, int start, int end, int* swaps) {  // само слияние
    int k = start;
    int j = start+(end-start)/2;
    int mid = j;
    int* temp = (int*)malloc((end-start) * sizeof(int));
    for (int i = 0; i < end-start; i++) {
        if (list[k] < list[j] && k < mid || j == end) temp[i] = list[k++];
        else temp[i] = list[j++];
        *swaps += 1;
    }
    for (int i = start; i < end; i++) list[i] = temp[i-start];
    free(temp);
}

int sortMerge(int* list, int start, int end) {  // сортировка слиянием O(nlogn)
    int swaps = 0;
    if ((end-start) <= 1) return 1;
    else {
        sortMerge(list, start, start+(end-start)/2);
        sortMerge(list, start+(end-start)/2, end);
        merge(list, start, end, &swaps);
    }
    return swaps;
}

int sortHoare(int* numbers, int first, int last) {  // быстрая сортировка O(nlogn) в лучшем / O(n^2) в худшем
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

void genNumbers(int* numbers, int size, int x, int y) {  // генерация массива чисел
    for (int i = 0; i < size; i++)
        numbers[i] = x + rand() % (y - x + 1);
}

int main() {
    srand(time(NULL));
    float time;
    int* numbers = NULL;
    int size = 0;
    double swaps = 0;
    printf("Enter amount of numbers: ");  // количество чисел
    scanf_s("%d", &size);
    numbers = (int*)malloc(size * sizeof(int));
    int x, y;
    printf("Enter range of numbers (from x to y included): ");  // диапазон чисел
    scanf_s("%d %d", &x, &y);

    genNumbers(numbers, size, x, y);
    time = clock();
    swaps = sortInsert(numbers, size);
    time = clock() - time;
    printf("sortInsert: %.2fs, swaps: %.0lf\n", time / 1000, swaps);

    genNumbers(numbers, size, x, y);
    time = clock();
    swaps = sortMerge(numbers, 0, size);
    time = clock() - time;
    printf("sortMerge: %.2fs, swaps: %.0lf\n", time / 1000, swaps);

    genNumbers(numbers, size, x, y);
    time = clock();
    swaps = sortHoare(numbers, 0, size - 1);
    time = clock() - time;
    printf("sortHoare: %.2fs, swaps: %.0lf\n", time / 1000, swaps);
}
