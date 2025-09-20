#include "SortComplex.h"


void merge(std::vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Complex> L(n1);
    std::vector<Complex> R(n2);

    for (int i = 0; i < n1; i++) L[i] = vec[left + i];
    for (int j = 0; j < n2; j++) R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) vec[k++] = L[i++];
        else vec[k++] = R[j++];
    }

    while (i < n1) vec[k++] = L[i++];
    while (j < n2) vec[k++] = R[j++];
}


void mergeSortRec(std::vector<Complex>& vec, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortRec(vec, left, mid);
    mergeSortRec(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

void mergeSort(std::vector<Complex>& vec) {
    if (vec.empty()) {
        std::cout << "Vector is empty\n";
        return;
    }
    
    std::cout << "Vector before sorting:\n";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    mergeSortRec(vec, 0, vec.size() - 1);
    
    std::cout << "\nSorted vector:\n";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n" << std::endl;
}
