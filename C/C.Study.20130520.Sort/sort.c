#include <stdio.h>

void inputArray(int *Array);
int choiceDirection();
int choiceAlgorithm();
void simple_sort(int *Array, int ArraySize, int dir);
void swap(int *dest, int *target);

int main() {
	int *Array, choice, dir;
	printf("Sort algorithm Program. \n");
	choice = choiceAlgorithm();
	inputArray(Array);
	dir = choiceDirection();
	switch(choice) {
		case 1 :
			simple_sort(Array, arraySize, dir);
			break;
		default :
			printf("Invalid argument\n");
	}
	return 0;
}


void inputArray(int *Array) {
	int arraySize = 0,i;

	printf("Input sort array size. (ex. 4 - 4 2 3 1)\n");
	scanf("%d" &arraySize);
	Array = (int*)malloc(sizeof(int)*arraySize);

	for(i=0; i < arraySize; i++) {
		printf("Input your %d st number.\n", i);
		scanf("%d" &Array[i]);
	}
}

int choiceDirection() {
	int dir;
	printf("Select order direction.(must be. 1 or 0)\n");
	printf("0 == asc, 1 == desc\n");
	scanf("%d" &dir);
	return dir;
}

int choiceAlgorithm() {
	int userChoice;
	printf("Choice Test Algorithm and Algorithm Size (ex. 1 5)\n");
	printf("1. Simple Sort\n");

	scanf("%d" &userChoice);
	return userChoice;
}

void simple_sort(int *Array, int ArraySize, int dir) {
	int i,j;
	for(i=0; i<ArraySize-1; i++) {
		if(dir == 0) {
			if(*(Array+i) > *(Array+j)) {
				swap(Array+i, Array+j);
			}
		} else if(dir == 1) {
			if(*(Array+i) < *(Array+j)) {
				swap(Array+i, Array+j);
			}
		}
	}
}

void swap(int *dest, int *target) {
	int temp = *dest;
	*dest = *target;
	*target = temp;
}
