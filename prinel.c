#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#define max_nr 1000000
#define max_len 1000000

// function to find the maximum of two numbers
int max(int a, int b) {
	return (a > b) ? a : b;
}

// function to find the minimum of two numbers
int min(int a, int b) {
	return (a < b) ? a : b;
}

// function to find the Maximum number of the array
int maxNr(int n, int *v) {
    int Max = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] > Max) {
            Max = v[i];
        }
    }
    return Max;
}

// function for creating the dp for the maximum number of the array
void findOpperationsforMax(int x, int y, int *dp) {
	for (int i = x; i <= y; i++) {
    	if (dp[i] == INT_MAX) {
			continue;
		}

		// search for divisors
		for (int j = 1; j * j <= i; j++) {
			// if a divisor is reached
			if (i % j == 0) {
				if (i + j <= y) {
					// minimum of elements
					dp[i + j] = min(dp[i + j], dp[i] + 1);
				}
				if (i + i / j <= y) {
                    // minimum of elements
					dp[i + i / j] = min(dp[i + i / j], dp[i] + 1);
				}
			}
		}
	}
}

// function to find the number of points
int findPoints(int k, int opp[], int points[], int n) {
	int i, w;

    // Allocate dinamically the matrix for dp
	int **DP = (int **)malloc((n + 1) * sizeof(int*));
	for (int i = 0; i < n + 1 ; i++) {
		DP[i] = (int *)malloc((k + 1) * sizeof(int));
    }
	// Create DP Matrix
	for (i = 0; i <= n; i++) {
		for (w = 0; w <= k; w++) {
			if (w == 0 || i == 0) {
				DP[i][w] = 0;
            } else if (opp[i - 1] <= w) {
                // find the maximum
				DP[i][w] = max(points[i - 1]+ DP[i - 1][w - opp[i - 1]], DP[i - 1][w]);
            } else {
				DP[i][w] = DP[i - 1][w];
            }
		}
	}
	return DP[n][k];
}

// function to find the number of opperations for x
int findOpperationsforEach(int Max, int x, int *dp) {
    // traverse all the elements
    for (int i = 1; i <= Max; i++) {
        // if the element is met
        // return the value from dp[i]
        if (x == i) {
            return dp[i];
        }
    }
    return -1;
}

int main() {
    FILE *f = fopen("prinel.in", "r");
    if (f == NULL) {
        printf("FILE NOT OPEN\n");
    }

    FILE *g = fopen("prinel.out", "w+");
    if (g == NULL) {
        printf("FILE NOT OPEN\n");
    }

    int n, k;
    fscanf(f, "%d %d", &n, &k);

    int *v = (int *)malloc(max_len * sizeof(int));
    int *points = (int *)malloc(max_len);
    int *target = (int *)malloc(max_len);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &target[i]);
    }

    // maximum number from the array
    int Max = maxNr(n, target);

    // dynamic programming array
	int dp[Max + 1];

    // initialisation
    for (int i = 2; i <= Max; i++) {
        dp[i] = INT_MAX;
    }

    // 1 to 1 no oppperation
	dp[1] = 0;

    // create dp array with all the opperations
    // for 1 to Max elements
    findOpperationsforMax(1, Max, dp);

    // find number of opperations for each element
    for (int i = 0; i < n; i++) {
        v[i] = findOpperationsforEach(Max, target[i], dp);
    }

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &points[i]);
    }

    fprintf(g, "%d\n", findPoints(k, v, points, n));
    return 0;
}
