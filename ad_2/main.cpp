#include <iostream>
#include <cmath>
#include <ctime>

#define N_MAX 50000

using namespace std;

void mergeSort(int a, int b, int* array){
    if(a>=b)
        return;
    int m = round((a+b)/2);
    mergeSort(a, m, array);
    mergeSort(m+1, b, array);
    int i, j;
    int* array_2 = new int[b - a + 1];
    i = a;
    j = m + 1;
    for (int k = a; k <= b; k++)
        if (j > b || i <= m && array[i] < array[j]) {
            array_2[k-a] = array[i];
            i++;
        } else {
            array_2[k-a] = array[j];
            j++;
        }
    for (i = a; i <= b; i++)
        array[i] = array_2[i-a];
    delete[] array_2;
}
int main() {
    srand(time(0));
    int* array = new int[N_MAX];
    for(int i=0; i<N_MAX;i++)
        array[i]=rand();

    mergeSort(0, N_MAX-1, array);

    for(int i=0;i<N_MAX;i++)
        cout << array[i] << " - ";
    delete[] array;
    return 0;
}

//Реализовать сортировку и оцените ее сложность.
//
//Вариант 1
//Сортировка слиянием.
//
//Вариант 2
//Сортировка Шелла.

