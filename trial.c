#include <stdio.h>
//#include <stdlib.h>
#include <time.h>
#include<malloc.h>
#define table S
// 定义数据结构
typedef struct {
    int Key;
    int No;
    int Primarykey;
} Record;
// 定义排序表
typedef struct {
	
    Record* elements;
    int length;
} SortTable;
// 生成随机整数
int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}
// 初始化排序表
void initSortTable(SortTable* table, int length) {
    table->length = length;
    table->elements = (Record*)malloc(length * sizeof(Record));
    // 生成数据元素
    for (int i = 0; i < length; i++) {
        table->elements[i].Key = randomInt(1, 10); // 随机生成Key
        table->elements[i].No = i + 1; // 学号
        table->elements[i].Primarykey = randomInt(100, 1000); // 随机生成Primarykey
    }
    // 添加四组相同关键码集合
    for (int i = 0; i < 4; i++) {
        int index = randomInt(0, length - 3);
        int key = table->elements[index].Key;
        for (int j = index; j < index + 3; j++) {
            table->elements[j].Key = key;
        }
    }
}
// 打印排序表
void printSortTable(SortTable table) {
    printf("Key\tNo\tPrimarykey\n");
    for (int i = 0; i < table.length; i++) {
        printf("%d\t%d\t%d\n", table.elements[i].Key, table.elements[i].No, table.elements[i].Primarykey);
    }
}
// 释放排序表内存
void freeSortTable(SortTable* table) {
    free(table->elements);
    table->length = 0;
}
// 直接插入排序算法
void insertionSort(SortTable* table, int* comparisons, int* moves) {
    int i, j;
    Record temp;
    *comparisons = 0;
    *moves = 0;
    for (i = 1; i < table->length; i++) {
        temp = table->elements[i];
        j = i - 1;
        (*comparisons)++;
        while (j >= 0 && table->elements[j].Key > temp.Key) {
            table->elements[j + 1] = table->elements[j];
            j--;
            (*comparisons)++;
            (*moves)++;
        }
        table->elements[j + 1] = temp;
    }
}
/*void insertionSort(SortTable* table, int* comparisons, int* moves){
	for(int i=2;i<=table->length;++i){
	(* comparisons)++;
	if(table->elements[i].Key<table->elements[i-1].Key)
	{
		(* comparisons)++;
		table->elements[0] = table->elements[i];
		table->elements[i] = table->elements[i-1];
		(* moves)++;
		int j = i-2;
		(* comparisons)++;
		for(int j = i-2;table->elements[0].Key < table->elements[j].Key;--j)
		table->elements[j+1] = table->elements[j];
		table->elements[j+1] = table->elements[0];
		(* moves)++;
		(* comparisons)++;
	}}
}*/
// 冒泡排序算法
void bubbleSort(SortTable* table, int* comparisons, int* moves) {
    int i, j;
    Record temp;
    *comparisons = 0;
    *moves = 0;
    for (i = 0; i < table->length - 1; i++) {
        for (j = 0; j < table->length - i - 1; j++) {
            (*comparisons)++; // 记录比较次数
            if (table->elements[j].Key > table->elements[j + 1].Key) {
                temp = table->elements[j];
                table->elements[j] = table->elements[j + 1];
                table->elements[j + 1] = temp;
                (*moves) ++; // 记录移动次数
            }
        }
    }
}
// 选择排序算法
void selectionSort(SortTable* table, int* comparisons, int* moves) {
    int i, j, minIndex;
    Record temp;
    for (i = 0; i < table->length - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < table->length; j++) {
            (*comparisons)++; // 记录比较次数
            if (table->elements[j].Key < table->elements[minIndex].Key) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            (*moves)++; // 记录移动次数
            temp = table->elements[i];
            table->elements[i] = table->elements[minIndex];
            table->elements[minIndex] = temp;
        }
    }
}
// 快速排序算法
int partition(Record arr[], int low, int high, int* comparisons, int* moves) {
    int pivot = arr[high].Key;
    int i = low - 1;
    Record temp;
    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j].Key < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*moves)++;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    (*moves)++;
    return (i + 1);
}
void quickSort(Record arr[], int low, int high, int* comparisons, int* moves) {
    if (low < high) {
        int pivot = partition(arr, low, high, comparisons, moves);
        quickSort(arr, low, pivot - 1, comparisons, moves);
        quickSort(arr, pivot + 1, high, comparisons, moves);
    }
}
// 数据元素逆序
void reverseSortTable(SortTable* table) {
    int start = 0;
    int end = table->length - 1;
    while (start < end) {
        // 交换元素位置
        Record temp = table->elements[start];
        table->elements[start] = table->elements[end];
        table->elements[end] = temp;
        // 更新指针位置
        start++;
        end--;
    }
}
// 乱序处理算法
void shuffle(SortTable* table) {
    for (int i = table->length - 1; i > 0; i--) {
        int j = rand() % (i + 1); // 生成一个随机位置 j (0 <= j <= i)
        // 交换位置 i 和 j 上的元素
        Record temp = table->elements[i];
        table->elements[i] = table->elements[j];
        table->elements[j] = temp;
    }
}
int main() {
    srand(time(NULL)); // 设置随机种子
    SortTable table;
    initSortTable(&table, 200);
   	printf("生成的排序表 S:\n");
    printSortTable(S);
    SortTable S1;
	initSortTable(&S1, 200);
	for(int i =0;i <= table.length - 1;i++)
		{
			S1.elements[i] = S.elements[i];
		}
	int a , b = 0;
	quickSort(S1.elements, 0, table.length - 1,&a, &b);
	printf("快速排序后的S1是：\n");
	printSortTable(S1);
	SortTable S2;
	initSortTable(&S2, 200);
	for(int i =0;i <= table.length - 1;i++)
		{
			S2.elements[i] = S1.elements[i];
		}
	reverseSortTable(&S2);
	printf("非递减序列S1逆序处理，生成非递增序列S2是：\n");
	printSortTable(S2);	
	SortTable S3;
	initSortTable(&S3, 200);
	for(int i =0;i <= table.length - 1;i++)
		{
			S3.elements[i] = S1.elements[i];
		}
	shuffle(&S3);
	printf("至少对非递减序列S1做2次乱序处理,生成的序列S3是：\n");
	printSortTable(S3);	
	SortTable S4;
	initSortTable(&S4, 200);  
	for(int i =0;i <= table.length - 1;i++)
		{
			S4.elements[i] = S1.elements[i];
		}
    shuffle(&S4);
    printf("至少对非递减序列S1做2次乱序处理，生成的序列S4是：\n");
	printSortTable(S4);	
	int comparisons[16] = {0};
	int moves[16] = {0};
	 clock_t start_time[16], end_time[16];
	long double execution_time[16];
	SortTable a1;
	initSortTable(&a1, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
		a1.elements[i] = S1.elements[i];
	}
	SortTable a2;
	initSortTable(&a2, 200);
	for(int i =0;i <= table.length - 1;i++)
		{
			a2.elements[i] = S1.elements[i];
		}
	SortTable a3;
	initSortTable(&a3, 200);
	for(int i =0;i <= table.length - 1;i++)
		{
			a3.elements[i] = S1.elements[i];
		}
	SortTable a4;
		initSortTable(&a4, 200);
		for(int i =0;i <= table.length - 1;i++)
			{
				a4.elements[i] = S2.elements[i];
			}
	SortTable a5;
		initSortTable(&a5, 200);
		for(int i =0;i <= table.length - 1;i++)
					{
						a5.elements[i] = S2.elements[i];
					}
	SortTable a6;
		initSortTable(&a6, 200);
	for(int i =0;i <= table.length - 1;i++)
				{
					a6.elements[i] = S2.elements[i];
				}
	SortTable a7;
		initSortTable(&a7, 200);
	for(int i =0;i <= table.length - 1;i++)
				{
					a7.elements[i] = S3.elements[i];
				}
	SortTable a8;
		initSortTable(&a8, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	a8.elements[i] = S3.elements[i];
	}
	SortTable a9;
		initSortTable(&a9, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	a9.elements[i] = S3.elements[i];
	}
	SortTable a10;
		initSortTable(&a10, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	a10.elements[i] = S4.elements[i];
	}
	SortTable a11;
	initSortTable(&a11, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	a11.elements[i] = S4.elements[i];
	}
	SortTable a12;
	initSortTable(&a12, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	a12.elements[i] = S4.elements[i];
	}
	//检查是否稳定
	SortTable b1;
		initSortTable(&b1, 200);
		for(int i =0;i <= table.length - 1;i++)
		{
		b1.elements[i] = S2.elements[i];
		b1.elements[i].No = i+1;
		}
	SortTable b2;
	initSortTable(&b2, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	b2.elements[i] = S2.elements[i];
	b2.elements[i].No = i+1;
	}
	SortTable b3;
	initSortTable(&b3, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	b3.elements[i] = S3.elements[i];
	b3.elements[i].No = i+1;
	}
	SortTable b4;
	initSortTable(&b4, 200);
	for(int i =0;i <= table.length - 1;i++)
	{
	b4.elements[i] = S4.elements[i];
	b4.elements[i].No = i+1;
	}
	int y,r,n,m,p,o,i,u=0;
	insertionSort(&b1, &y, &r)	;
	bubbleSort(&b2, & n, &m)	;
	selectionSort(&b3,  &p, & o);
	quickSort(b4.elements, 0, table.length - 1,&i, &u);
	int q[32];
	//利用循环增长时间，使显示更明显
		start_time[0] = clock();
		insertionSort(&S1, &comparisons[0], &moves[0])	;
			for(int i = 0;i <=100;i++)
						for(int j = 0;j <=100;j++)
				insertionSort(&S1, &q[0], &q[1]);
		end_time[0] = clock();
		start_time[1] = clock();
		bubbleSort(&a1, & comparisons[1], &moves[1])	;
		for(int i = 0;i <=100;i++)
		for(int j = 0;j <=100;j++)
		bubbleSort(&a1, & q[2], &q[3])	;
		end_time[1] = clock();
		start_time[2] = clock();
		selectionSort(&a2,  &comparisons[2], & moves[2]);	
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
				selectionSort(&a2,  &q[4], & q[5]);	
		end_time[2] = clock();
		start_time[3] = clock();
		quickSort(a3.elements, 0, table.length - 1,&comparisons[3], &moves[3]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		quickSort(a3.elements, 0, table.length - 1,&q[6], &q[7]);
		end_time[3] = clock();
		start_time[4] = clock();
		insertionSort(&S2, &comparisons[4], & moves[4]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		insertionSort(&S2, &q[8], & q[9]);
		end_time[4] = clock();
		start_time[5] = clock();
		bubbleSort(&a4, &comparisons[5], & moves[5]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		bubbleSort(&a4, &q[10], & q[11]);
		end_time[5] = clock();
		start_time[6] = clock();
		selectionSort(&a5, &comparisons[6], & moves[6]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		selectionSort(&a5, &q[1], &q[5]);
		end_time[6] = clock();
		start_time[7] = clock();
		quickSort(a6.elements, 0, table.length - 1,&comparisons[7], &moves[7]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		quickSort(a6.elements, 0, table.length - 1,&q[7], &q[8]);
		end_time[7] = clock();
		start_time[8] = clock();
		insertionSort(&S3, &comparisons[8], &moves[8]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		insertionSort(&S3, &q[8], &q[9]);
		end_time[8] = clock();
		start_time[9] = clock();
		bubbleSort(&a7, &comparisons[9], &moves[9]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		bubbleSort(&a7, &q[9], &q[10]);
		end_time[9] = clock();
		start_time[10] = clock();
		selectionSort(&a8, &comparisons[10], &moves[10]);
		for(int i = 0;i <=100;i++)
						for(int j = 0;j <=100;j++)
		selectionSort(&a8, &q[10], &q[11]);
		end_time[10] = clock();
		start_time[11] = clock();
		quickSort(a9.elements, 0, table.length - 1,&comparisons[11], &moves[11]);
		for(int i = 0;i <=100;i++)
						for(int j = 0;j <=100;j++)
		quickSort(a9.elements, 0, table.length - 1,&q[11], &q[12]);
		end_time[11] = clock();
		start_time[12] = clock();
		insertionSort(&S4, &comparisons[12], &moves[12]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		insertionSort(&S4, &q[12], &q[13]);
		end_time[12] = clock();
		start_time[13] = clock();
		bubbleSort(&a10, &comparisons[13], & moves[13]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		bubbleSort(&a10, &q[13], &q[14]);
		end_time[13] = clock();
		start_time[14] = clock();
		selectionSort(&a11, &comparisons[14], & moves[14]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		selectionSort(&a11, &q[14], & q[15]);
		end_time[14] = clock();
		start_time[15] = clock();
		quickSort(a12.elements, 0, table.length - 1,&comparisons[15], &moves[15]);
		for(int i = 0;i <=100;i++)
				for(int j = 0;j <=100;j++)
		quickSort(a12.elements, 0, table.length - 1,&q[15], &q[16]);
		end_time[15] = clock();
		for(int i = 0;i<=16;i++)
		{
		execution_time[i]=  ((long double)(end_time[i] - start_time[i])) / CLOCKS_PER_SEC;
		}
		// 输出到文件
		    FILE* output_file = fopen("output.ifo", "w");
		    if (output_file != NULL){
		    fprintf(output_file, "比较次数表\tA1\t\tA2\t\tA3\t\tA4\n");
		    fprintf(output_file, "S1\t\t\t%d\t\t%d\t%d\t%d\n", comparisons[0],comparisons[1],comparisons[2],comparisons[3]);
		    fprintf(output_file, "S2\t\t\t%d\t%d\t%d\t%d\n", comparisons[4],comparisons[5],comparisons[6],comparisons[7]);
		    fprintf(output_file, "S3\t\t\t%d\t%d\t%d\t%d\n", comparisons[8],comparisons[9],comparisons[10],comparisons[11]);
		    fprintf(output_file, "S4\t\t\t%d\t%d\t%d\t%d\n", comparisons[12],comparisons[13],comparisons[14],comparisons[15]);
		    fprintf(output_file, "移动次数表\tA1\t\tA2\t\tA3\t\tA4\n");
			fprintf(output_file, "S1\t\t\t%d\t\t%d\t\t%d\t\t%d\n", moves[0],moves[1],moves[2],moves[3]);
			fprintf(output_file, "S2\t\t\t%d\t%d\t%d\t\t%d\n", moves[4],moves[5],moves[6],moves[7]);
			fprintf(output_file, "S3\t\t\t%d\t%d\t%d\t\t%d\n", moves[8],moves[9],moves[10],moves[11]);
			fprintf(output_file, "S4\t\t\t%d\t%d\t%d\t\t%d\n", moves[12],moves[13],moves[14],moves[15]);
			fprintf(output_file, "执行时间表\tA1\t\tA2\t\tA3\t\tA4\n");
			fprintf(output_file, "S1\t\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\n", execution_time[0],execution_time[1],execution_time[2],execution_time[3]);
		 	fprintf(output_file, "S2\t\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\n", execution_time[4],execution_time[5],execution_time[6],execution_time[7]);
			fprintf(output_file, "S3\t\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\n", execution_time[8],execution_time[9],execution_time[10],execution_time[11]);
		 	fprintf(output_file, "S4\t\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\t\t%.6Lf\n", execution_time[12],execution_time[13],execution_time[14],execution_time[15]);
		    fclose(output_file);
		    } else {
		        printf("Error opening output file.\n");
		    }
	    
	    // 检查稳定性
	   int stable1= 1;
		for (int i = 1; i < S1.length; i++) {
		if (b1.elements[i].Key == b1.elements[i - 1].Key &&
		b1.elements[i].No < b1.elements[i - 1].No) {
		stable1 = 0;
		break;      
		}
		}
		if (stable1) {
		printf("\n直接插入排序算法是稳定的。\n");
		} else {
		printf("\n直接插入排序算法不是稳定的。\n");
		}
		int stable2 = 1;
		for (int i = 1; i < b2.length; i++) {
		if (b2.elements[i].Key == b2.elements[i - 1].Key &&
		b2.elements[i].No < b2.elements[i - 1].No) {
		 stable2 = 0;
		break;
		 }
		}
		if (stable2) {
		printf("\n冒泡排序算法是稳定的。（但视具体情况而定）\n");
		} else {
		printf("\n冒泡排序算法不是稳定的。\n");
		}
		int stable3 = 1;
		for (int i = 1; i < b3.length; i++) {
		if (b3.elements[i].Key == b3.elements[i - 1].Key &&
		b3.elements[i].No < b3.elements[i - 1].No) {
		stable3 = 0;
		break;
		}
		}
	 	if (stable3) {
		printf("\n选择排序算法是稳定的。\n");
		 } else {
		 printf("\n选择排序算法不是稳定的。\n");
	 	}		    
		int stable4 = 1;
		for (int i = 1; i < b4.length; i++) {
		if (b4.elements[i].Key == b4.elements[i - 1].Key &&
	 	b4.elements[i].No < b4.elements[i - 1].No) {
	 	stable4 = 0;
	 	break;
		}
	 	}
	 	if (stable4) {
	 	printf("\n快速排序算法是稳定的。\n");
	 	} else {
		printf("\n快速排序算法不是稳定的。\n");
		}   	
    freeSortTable(&table);
    freeSortTable(&S1);
    freeSortTable(&S2);
    freeSortTable(&S3);
    freeSortTable(&S4);
    freeSortTable(&a1);
    freeSortTable(&a2);
    freeSortTable(&a3);
    freeSortTable(&a4);
    freeSortTable(&a5);
    freeSortTable(&a6);
    freeSortTable(&a7);
    freeSortTable(&a8);
    freeSortTable(&a9);
    freeSortTable(&a10);
    freeSortTable(&a11);
    freeSortTable(&a12);        
    return 0;
		
}