#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void prt(int *arr, int n) {
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n");
}

void merge(int *a, int *t, int l, int m, int h) {
    for (int i = l, j = m + 1, p = 0; i <= m || j <= h; ++p) i <= m ? j <= h ? t[p] = (a[i] < a[j]) ? a[i++] : a[j++] : (t[p] = a[i++]) : j <= h && (t[p] = a[j++]);

    for (int i = l; i <= h; ++i) a[i] = t[i - l];
}

void ms(int *a, int *t, int l, int h) {
    if (l >= h) return;
    int m = (h - l) / 2 + l;
    ms(a, t, l, m);
    ms(a, t, m + 1, h);
    merge(a, t, l, m, h);
}

void mergeSort(int *arr, int n) {
    if (n < 2) return;
    int *t = (int*)malloc(sizeof(int) * n);
    ms(arr, t, 0, n - 1);
    free(t);
}

int main(int ag, char **av) {
    FILE *f1 = fopen("file1.txt", "r");
    FILE *f2 = fopen("file2.txt", "r");

    int n1 = 0, n2 = 0;
    fscanf(f1, "%d\n", &n1);
    fscanf(f2, "%d\n", &n2);

    int *a = (int*)malloc(sizeof(int) * (n1 + n2));
    int *tmp = (int*)malloc(sizeof(int) * (n1 + n2));

    for (int i = 0; i < n1; ++i) fscanf(f1, "%d", a + i);
    for (int i = n1; i < n1 + n2; ++i) fscanf(f2, "%d", a + i);

    fclose(f1);
    fclose(f2);

    merge(a, tmp, n1, n2 - 1, n1 + n2 - 1);

    FILE *f0 = fopen("file0.txt", "w");
    fprintf(f0, "%d\n", n1 + n2);
    for (int i = 0; i < n1 + n2; ++i) fprintf(f0, "%d ", a[i]);

    fclose(f0);
    free(a);
    free(tmp);

    return 0;
}
