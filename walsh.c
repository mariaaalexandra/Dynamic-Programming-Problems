#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 20

// negate bit
int neg(int bit) {
    if (bit == 0) {
        return 1;
    }
    return 0;
}

// check if an element exists in a square
int exists(int x, int y, int a1, int b1, int a2, int b2) {
    if ((x >= a1 && x <= a2) && (y >= b1 && y <= b2) == 1) {
        return 1;
    }
    return 0;
}

// recursive function
int find(int x, int y, int a1, int b1, int a2, int b2, int D, int p) {
    // if D == 1 element is found
    if (D == 1) {
        return p;
    }

    int xmid = (a1 + a2) / 2;
    int ymid = (b1 + b2) / 2;

    // check if (x,y) is in left up square
    if (exists(x, y, a1, b1, xmid, ymid) == 1) {
        D = D / 2;
        return find(x, y, a1, b1, xmid, ymid, D, p);
    }

    // check if (x,y) is in right up square
    if (exists(x, y, a1, ymid, xmid, b2) == 1) {
        D = D / 2;
        return find(x, y, a1, ymid, xmid, b2, D, p);
    }

    // chech if (x,y) is in the left down square
    if (exists(x, y, xmid, b1, a2, ymid) == 1) {
        D = D / 2;
        return find(x, y, xmid, b1, a2, ymid, D, p);
    }

    // chech if (x,y) is in the right down square
    if (exists(x, y, xmid, ymid, a2, b2) == 1) {
        D = D / 2;
        p = neg(p);
        return find(x, y, xmid, ymid, a2, b2, D, p);
    }
    return -1;
}

int main(void) {
    FILE *f = fopen("walsh.in", "r");
    if (f == NULL) {
        fprintf(stderr, "NOT OPEN");
    }

    FILE *g = fopen("walsh.out", "w+");
    if (g == NULL) {
        fprintf(stderr, "NOT OPEN");
    }

    int n, k;
    fscanf(f, "%d %d", &n, &k);
    while (k != 0) {
        int a, b;
        fscanf(f, "%d %d", &a, &b);
        fprintf(g, "%d\n", find(a, b, 1, 1, n, n, n, 0));
        k--;
    }
    return 0;
}
