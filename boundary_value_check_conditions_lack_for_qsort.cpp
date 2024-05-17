#include <iostream>
int partition(int *array, int low, int high) {
    int pivot = array[low];
    int i = low, j = high;
    while (i < j) {
        while (i < j && (array[j] > pivot)) {
            j--;
        }
        if (i < j) {        // easy to lack
            array[i++] = array[j];
        }
        while (i < j && array[i] < pivot) {
            i++;
        }
        if (i < j) {    // easy to lack
            array[j--] = array[i];
        }
    }
    array[i] = pivot;
    return i;
}
void qsort(int *array, int low, int high) {
        if (low < high) {
            int mid = partition(array, low, high);
            qsort(array, low, mid - 1);
            qsort(array, mid + 1, high);
        }

}
void qsort(int *array, int n) {
    qsort(array, 0, n - 1);
}
int main() {
    int array[4] = { -1, -10, 1, 3 };
    qsort(array, 4);
    for (auto& v : array) {
            std::cout << v << std::endl;
    }

    return 0;
}