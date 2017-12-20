//
//  main.c
//  adspj4_n2
//
//  Created by 张倬豪 on 2017/5/11.
//  Copyright © 2017年 Icarus. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxn 100010

int main(int argc, const char * argv[]) {
    int n, a[maxn], d1[maxn], d2[maxn], i, j, len1 = 0, len2 = 0, newIndex; //d1, d2 means last and least element of LIS whose length is len.
    int res1[maxn] = {0}, res2[maxn] = {0}, max = 0, index = 0, sym;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    res1[0] = res2[n - 1] = 0;
    
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) { //for each number search former numbers
            if (a[j] < a[i] && res1[j] + 1 > res1[i]) { //if longer subsequence is found
                res1[i] = res1[j] + 1; //renew it
            }
        }
    }
    
    for (i = n - 2; i >= 0; i--) {
        for (j = n - 1; j > i; j--) { //exactly the same but inverted
            if (a[j] < a[i] && res2[j] + 1 > res2[i]) {
                res2[i] = res2[j] + 1;
            }
        }
    }
    
    sym = n - 1;
    for (i = 1; i < n; i++) {
        if (res1[i] > 0 && res2[i] >0 && (((res1[i] + res2[i]) > max) || ((res1[i] + res2[i] == max) && (abs(res1[i] - res2[i]) <= sym)))) { //if new peak is better
            max = res1[i] + res2[i]; //renew the current best one
            sym = abs(res1[i] - res2[i]);
            index = i;
        }
    }
    if (max) printf("%d %d %d", max + 1, index + 1, a[index]); //don't forget to plus 1 because it didn't count itself
    else printf("No peak shape");
    return 0;
}

