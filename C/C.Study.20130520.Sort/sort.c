#include <stdio.h>
#include <malloc.h>

int inputArraySize();
int choiceDirection();
int choiceAlgorithm();
void swap(int *dest, int *target, int arraySize, int *Array);

void simple_sort(int *Array, int arraySize, int dir);
void insert_sort(int *Array, int arraySize, int dir);
void bubble_sort(int *Array, int arraySize, int dir);
void shell_sort(int *Array, int arraySize, int dir);
void quick_sort_recur(int *Ary, int first, int ArySize, int dir);

int main() {
	int *Array, choice, dir, arraySize,i,first;
	printf("Sort algorithm Program. \n");
	choice = choiceAlgorithm();
	arraySize = inputArraySize();
	Array = (int *)malloc(sizeof(int) * arraySize);

	for(i=0; i < arraySize; i++) {
		printf("Input your [%d] st number.\n", i);
		scanf("%d", &Array[i]);
	}
	dir = choiceDirection();
	for(i=0; i < arraySize; i++) {
		printf("[%d] ", *(Array+i));
	}
	printf("\n-----------------------\n");
	switch(choice) {
		case 1 :
			simple_sort(Array, arraySize, dir);
			break;
		case 2 :
			insert_sort(Array, arraySize, dir);
			break;
		case 3 :
			bubble_sort(Array, arraySize, dir);
			break;
		case 4 :
			shell_sort(Array, arraySize, dir);
			break;
		case 5 :
			printf("Select first number of array\n");
			scanf("%d",&first);
			quick_sort_recur(Array, first, arraySize, dir);
			break;
		default :
			printf("Invalid argument\n");
	}
	printf("-----------------------\n");
	printf("Result is :\n");
	for(i=0; i < arraySize; i++) {
		printf("[%d] ", *(Array+i));
	}
	printf("\n");
	free(Array);
	return 0;
}

void swap(int *dest, int *target, int arraySize, int *Array) {
	int temp,i;
	temp = *dest;
	*dest = *target;
	*target = temp;
	for(i=0; i < arraySize; i++) {
		printf("[%d] ", *(Array+i));
	}
	printf("\n");
}

int inputArraySize() {
	int arraySize = 0;

	printf("Input sort array size. (ex. 4 - 4 2 3 1)\n");
	scanf("%d", &arraySize);
	return arraySize;
}

int choiceDirection() {
	int dir;
	printf("Select order direction.(must be. 0 or 1)\n");
	printf("[0 = asc, 1 = desc]\n");
	while(1) {
		scanf("%d", &dir);
		if((dir==0) || (dir==1)) {
			return dir;
		} else {
			printf("Must be use 0 or 1\n");
		}
	}
	return dir;
}

int choiceAlgorithm() {
	int userChoice;
	printf("Choice Test Algorithm\n");
	printf("-----------------------\n");
	printf("1. Simple Sort\n");
	printf("2. Insert Sort\n");
	printf("3. Bubble Sort\n");
	printf("4. Shell Sort\n");
	printf("5. Quick Sort\n");
	printf("-----------------------\n");
	scanf("%d", &userChoice);
	return userChoice;
}

void simple_sort(int *Array, int arraySize, int dir) {
	int i,j;
	for(i=0; i<arraySize-1; i++) {
		for(j=i+1; j<arraySize; j++) {
			if(dir == 0) {
				if(*(Array+i) > *(Array+j)) {
					swap(Array+i, Array+j, arraySize, Array);
				}
			} else if(dir == 1) {
				if(*(Array+i) < *(Array+j)) {
					swap(Array+i, Array+j, arraySize, Array);
				}
			}
		}
	}
}

void insert_sort(int *Array, int arraySize, int dir) {
	int i,j,temp;
	
	for(i=1; i<arraySize; i++) {
		temp = *(Array+i);
		for(j=i-1; j>=0; j--) {
			if(dir == 0) {
				if(*(Array+j) > temp) {
					swap(Array+j+1, Array+j, arraySize, Array);
				} else {
					break;
				}
			} else if(dir == 1) {
				if(*(Array+j) < temp) {
					swap(Array+j+1, Array+j, arraySize, Array);
				} else {
					break;
				}
			}
		}
	}
}

void bubble_sort(int *Array, int arraySize, int dir) {
	int i,j;

	for(i=arraySize-1; i>0; i--) {
		for(j=0; j<i; j++) {
			if(dir == 0) {
				if(*(Array+j) > *(Array+(j+1))) {
					swap(Array+j, Array+j+1, arraySize, Array);
				}
			} else if(dir == 1) {
				if(*(Array+j) < *(Array+(j+1))) {
					swap(Array+j, Array+j+1, arraySize, Array);
				}
			}
		}
	}
}

void shell_sort(int *Array, int arraySize, int dir) {
	int i,j,h,temp;

	for(h=1; h<=arraySize; h=(3*h)+1); /* 3x number*/

	h /= 3;
	while(h >= 1) {
		for(i=h; i<arraySize; i++) {
			temp = *(Array+i);
			for(j=i-h; j>=0; j-=h) {
				if(dir == 0) {
					if(*(Array+j) > temp) {
						*(Array+j+h) = *(Array+j);	
					} else {
						break;
					}
				} else if(dir == 1) {
					if(*(Array+j) < temp) {
						*(Array+j+h) = *(Array+j);	
					} else {
						break;
					}
				}
			}
			*(Array+j+h) = temp;
		}
		h /= 3;
	}
	
}

void quick_sort_recur(int *Ary, int first, int ArySize, int dir)  //ArySize = last
{
     int i, j, ave;

     i = first;
     j = ArySize-1;
     ave = ( *(Ary+i) + *(Ary+j) ) / 2;
 
     while(1)
     {
          while((dir==0) ? (*(Ary+i) < ave) : (*(Ary+i) > ave)) i++;
          while((dir==0) ? (*(Ary+j) > ave) : (*(Ary+j) < ave)) j--;
          if(i >= j) break;
          swap(Ary+i++, Ary+j--, ArySize, Ary);
     }
     if(first < i-1) quick_sort_recur(Ary, first, i, dir);
     if(j+1 < ArySize-1) quick_sort_recur(Ary, j+1, ArySize, dir);
}

