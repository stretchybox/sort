#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q) {
	int tmp;
	tmp = *p;
	*p  = *q;
	*q  = tmp;
}

int comp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int medimedi(int A[], int n) {
	if (n <= 5) {
		qsort(A, n, sizeof(int), comp);
		return A[n / 2];
	} else {
		int cnt = (n - 1) / 5 + 1; //グループの個数
		int nA[5];
		int B[N];
		for (int i = 0; i < n; i += 5) {
			int num = MIN(n - i, 5);
			for (int j = 0; j < num; j++) {
				nA[j] = A[i + j];
			}
			int mid  = medimedi(nA, num);
			B[i / 5] = mid;
		}
		//B[0],...B[cnt - 1]は中央値の集まり
		return medimedi(B, cnt);
	}
}

int quick_select(int A[], int n, int k) {

	int pivot = medimedi(A, n);
	for (int i = 0; i < n; i++) {
		if (A[i] == pivot) {
			swap(A, A + i);
			break;
		}
	}
	int i, j;
	for (i = j = 1; i < n; i++) {
		if (A[i] <= pivot) {
			swap(A + i, A + j);
			j++;
		}
	}
	if (j == k + 1)
		return pivot;
	else if (j < k + 1)
		return quick_select(A + j, n - j, k - j);
	else
		return quick_select(A + 1, j - 1, k);
}

int main() {
	int i;
	A[0] = 0;
	A[1] = 17; //原始元
	for (i = 2; i < N; i++) {
		A[i] = (long long int)A[i - 1] * A[1] % N;
	}
	//printf("%d\n", medimedi(A, N));
	for (i = 0; i < N; i++) {
		if (quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
		//printf("%d th element is %d\n", i, quick_select(A, N, i));
	}
}
