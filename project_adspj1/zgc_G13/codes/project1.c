#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AvlTree.h"
#include "SplayTree.h"
#include "UBTree.h"

clock_t start, stop;
double duration;

int *ins, *del;

int main()
{
	int n;
	AvlTree a = AVLBuild();
	SplayTree s = splayBuild();
	UBTree u = UBBuild();

	scanf("%d", &n);
	ins = (int*)malloc(sizeof(int) * n);
	del = (int*)malloc(sizeof(int) * n);
	if(!ins || !del)
	{
		printf("Error when allocating space in memory!\n");
		exit(1);
	}

	for(int ri = 0; ri < 2 * n; ri++)
	{
		if(ri < n)scanf("%d", ins + ri);
		else scanf("%d", del + ri - n);
	}

	start = clock();
	for(int ri = 0; ri < n; ri++)AVLIns(ins[ri], a);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("%f ", duration);
	start = clock();
	for(int ri = 0; ri < n; ri++)AVLDel(del[ri], a);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("%f\n", duration);

	start = clock();
	for(int ri = 0; ri < n; ri++)splayIns(ins[ri], s);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("%f ", duration);
	start = clock();
	for(int ri = 0; ri < n; ri++)splayDel(del[ri], s);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("%f\n", duration);

	start = clock();
	for(int ri = 0; ri < n; ri++)UBIns(ins[ri], u);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("%f ", duration);
	start = clock();
	for(int ri = 0; ri < n; ri++)UBDel(del[ri], u);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("%f\n", duration);

	AVLFree(a);
	splayFree(s);
	UBFree(u);

	return 0;
}
