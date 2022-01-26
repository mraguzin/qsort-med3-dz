#include <random>
#include <iostream>
#include <cstring>
#include <chrono>

void qsort_s(int *A, int n)
{
    if (n <= 1) {
        return;
    }

    int i = 0;
    int j = n;
    std::swap(A[0], A[i]);

    for (;;) {
        do i++; while (i < n && A[i] < A[0]);
        do j--; while (A[j] > A[0]);
        if (j < i) break;
        std::swap(A[i], A[j]);
    }

    std::swap(A[0], A[j]);
    qsort_s(A, j);
    qsort_s(A + j + 1, n - j - 1);
}

int *med3(int *a, int *b, int *c)
{
    return *a > *b ? (*b > *c ? b : *a > *c ? c : a)
       : (*b < *c ? b : *a < *c ? c : a);
}

void qsort_med3(int *A, int n)
{
    if (n <= 1) {
        return;
    }

    int i1 = std::rand() % n;
    int i2 = std::rand() % n;
    int i3 = std::rand() % n;
    int* med = med3(&A[i1], &A[i2], &A[i3]);
    std::swap(A[0], *med);

    int i = 0;
    int j = n;

    for (;;) {
        do i++; while (i < n && A[i] < A[0]);
        do j--; while (A[j] > A[0]);
        if (j < i) break;
        std::swap(A[i], A[j]);
    }

    std::swap(A[0], A[j]);
    qsort_med3(A, j);
    qsort_med3(A + j + 1, n - j - 1);
}

void qsort_med3_fixpos(int *A, int n)
{
    if (n <= 1) {
        return;
    }

    int i1 = 0;
    int i2 = n / 2;
    int i3 = n - 1;
    int* med = med3(&A[i1], &A[i2], &A[i3]);
    std::swap(A[0], *med);

    int i = 0;
    int j = n;

    for (;;) {
        do i++; while (i < n && A[i] < A[0]);
        do j--; while (A[j] > A[0]);
        if (j < i) break;
        std::swap(A[i], A[j]);
    }

    std::swap(A[0], A[j]);
    qsort_med3(A, j);
    qsort_med3(A + j + 1, n - j - 1);
}


void randgen(int *A, int n = 100000)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, n);

    //int *A = new int[n];
    for (int i = 0; i < n; ++i) {
        A[i] = dist(generator);
    }
}

int main(int argc, char **argv)
{
    std::srand(std::time(nullptr));
    if (argc != 2) {
        std::cout << "\tMedijan-od-tri Quicksort -- mjerenje performansi\nUpotreba:\tqsort n\ngdje je " <<
        "n broj slučajnih cjelobrojnih elemenata za generirati u poljima za testiranje" << std::endl;

         return 0;
    }

    int n = std::atoi(argv[1]);
    int *A = new int[n];
    randgen(A, n);
    int *B = new int[n];
    std::memcpy(B, A, sizeof(int) * n);
    int *C = new int[n];
    std::memcpy(C, A, sizeof(int) * n);

    auto start = std::chrono::steady_clock::now();
    qsort_s(A, n);
    auto end = std::chrono::steady_clock::now();
    auto slowTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    qsort_med3(B, n);
    end = std::chrono::steady_clock::now();
    auto fastTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    qsort_med3_fixpos(C, n);
    end = std::chrono::steady_clock::now();
    auto fixposTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "REZULTATI\n==============\nVrijeme za standardni Quicksort: " << slowTime << " ms" << std::endl
    << "Vrijeme za Medijan-od-tri Quicksort: " << fastTime << " ms" << std::endl
    << "Vrijeme za fiksni Medijan-od-tri: " << fixposTime << " ms" << std::endl
    << "Ubrzanje za randomizirani Medijan-od-tri: ";
    if (fastTime > slowTime) {
        std::cout << "Sporije!";
    } else {
        std::cout << (double)slowTime / fastTime * 100 - 100 << "%";
    }

    std::cout << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;    
}