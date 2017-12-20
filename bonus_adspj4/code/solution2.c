//
//  main.c
//  adspj4
//
//  Created by 张倬豪 on 2017/5/3.
//  Copyright © 2017年 Icarus. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxn 100010

int find(int d[], int start, int end, int element) { //find the first pos >= element  guarantee d[end] >= element
    if (d[start] >= element) return start; //if already bigger than element we want to find
    while (start < end - 1) {
        int mid = (start + end) >> 1; //get the middle position
        if (d[mid] < element) start = mid;
        else end = mid;
    }
    return end;
}

int main(int argc, const char * argv[]) {
    int n, a[maxn], d1[maxn], d2[maxn], i, len1 = 0, len2 = 0, newIndex; //d1, d2 means last and least element of LIS whose length is len.
    int res1[maxn] = {0}, res2[maxn] = {0}, max = 0, index = 0, sym;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    d1[len1] = a[0]; //initialize
    for (i = 1; i < n; i++) {
        if (a[i] > d1[len1]) { //when a[i] > d[len]
            len1++; //new element in d
            d1[len1] = a[i];
            res1[i] = len1; //new element in res
        }
        else { //when a[i] <= d[len]
            newIndex = find(d1, 0, len1, a[i]); //get the new index where d[j-1] < a[i] < d[j]
            if (newIndex != -1) { //if it exists
                d1[newIndex] = a[i]; //renew d[newIndex] to a[i]
                res1[i] = newIndex;
            }
            else res1[i] = 0;
        }
    }
    
    d2[len2] = a[n - 1]; //exactly the same but inverted
    for (i = n - 2; i >= 0; i--) {
        if (a[i] > d2[len2]) {
            len2++;
            d2[len2] = a[i];
            res2[i] = len2;
        }
        else {
            newIndex = find(d2, 0, len2, a[i]);
            if (newIndex != -1) {
                d2[newIndex] = a[i];
                res2[i] = newIndex;
            }
            else res2[i] = 0;
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

