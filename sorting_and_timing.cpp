
#include <iostream>
#include "time.h"
#include <iomanip>
using namespace std;
const int M = 999;
const int N = 4;
void swap(int* xp, int* yp);
void selectionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
int* copy(int *, int n);
void printArray(int arr[], int size);
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray  
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element  
		swap(&arr[min_idx], &arr[i]);
	}
}


// A function to implement bubble sort 
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place    
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	const int n1 = m - l + 1;
	const int n2 = r - m;

	/* create temp arrays */
	int * L = new int[n1]; int * R = new int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

int* copy(int * t, int n) {
	if (n>0) {
		int* a = new int[n];
		int i;
		for (i = 0; i < n;i++) {
			a[i] = t[i];
		}
		return a;
	}
	return nullptr;
}


void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("n");
}


int main()
{
	int ** a = new int * [M]; 
	int ** backup = new int * [M];
	int ** exec_times = new int * [M];
	srand(time(NULL));
	clock_t start, stop;
	int i,number,j;
	for (i = 0; i < M;i++) {
		a[i] = new int[M];
		backup[i] = new int[M];
		exec_times[i] = new int [N];
		for (j = 0; j < M;j++) {
			number = rand() % M;
			a[i][j] = number;
			backup[i][j] = number;
		}
	}



	for (i = 0; i < M; i++) {
		start = clock();
		selectionSort(a[i],M);
		stop = clock();
		exec_times[i][0] = (stop - start);

		a[i] = copy(backup[i],M);
		start = clock();
		bubbleSort(a[i], M);
		stop = clock();
		exec_times[i][1] = (stop - start);


		a[i] = copy(backup[i], M);
		start = clock();
		insertionSort(a[i], M);
		stop = clock();
		exec_times[i][2] = (stop - start);


		a[i] = copy(backup[i], M);
		start = clock();
		mergeSort(a[i], 0,M-1);
		stop = clock();
		exec_times[i][3] = (stop - start);
	}
	int k = 20;
	cout << setw(k) << fixed << "Selection Sort|"<< setw(k) << fixed<<"Bubble Sort|"<< setw(k) << fixed<<"Insertion Sort|" << setw(k) << fixed << "Merge Sort";
	cout << "\n------------------------------------------------------------";
	for (i = 0; i < M;i++) {
		cout << endl;
		for (j = 0; j < N;j++) {
			if(j<N-1) 
				cout << setw(k) << fixed << exec_times[i][j]<<"|";  
			else
				cout << setw(k) << fixed << exec_times[i][j] ;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
