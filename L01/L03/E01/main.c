#include <stdio.h>
#include <stdlib.h>

int majority (int *a, int N);
int majorityRecursive (int *a, int l, int r);

int main() {
    int *vector, N;
    int i, major;

    printf("Inserire dimensione vettore:");
    scanf("%d", &N);

    vector = malloc(N*sizeof (int));
    for (i=0; i<N; i++) {
        printf("Inserire %d elemento:", i+1);
        scanf("%d", &vector[i]);
    }

    major = majority(vector, N);
    if (major != -1)
        printf("L'elemento maggioritario del vettore inserito e': %d.\n", major);
    else
        printf("Non e' presente alcun elemento maggioritario.\n");

    free(vector);
    return 0;
}

int majority (int *a, int N) {
    int l=0, r=N-1, i, cnt=0;
    int major = majorityRecursive(a, l, r);
    for (i=0; i<N; i++) {
        if (a[i] == major)
            cnt++;
    }
    if (cnt>N/2)
        return major;
    return -1;
}

int majorityRecursive (int *a, int l, int r) {
    int m = (l+r)/2, maj_r, maj_l;
    int i, occ=0;

    if (r<=l)
        return a[l];

    maj_l = majorityRecursive(a, l, m);
    maj_r = majorityRecursive(a, m+1, r);

    for (i=l; i<r; i++) {
        if (a[i] == maj_l)
            occ++;
    }
    if (occ>(r-l)/2)
        return maj_l;
    return maj_r;
}