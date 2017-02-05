#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LEN 50000 //length of array

/*
* bruteForce: Compute inversion number using bruteforce method
* arr: array to be processed
* len: length of the array*/
long int bruteForce(int *arr, int len){
	long int inversionCount;
	int i,j;

	inversionCount = 0;

	/*Compare every number with every number ahead
	of it in the array*/
	for (i=0;i<len-1;i++){

		for (j=i;j<len;j++){
		
			if (i < j && arr[i] > arr[j] ){
				inversionCount++;
			}
		}
	}

	return inversionCount;

}

/*divideAndConquer: Compute the inversion number using the
*	divide and conquer method
* arr: array to be processed
* start: starting index in array
* end: last index in array*/
long int divideAndConquer(int **arr, int start, int end){

	int i,temp;
	int newArr[end-start+1];
	int startLeft,startRight,endLeft,endRight,curLeft,curRight;
	long int inversionCount;

	for (int i=0;i<end-start+1;i++){
		newArr[i]=0;
	}

	inversionCount = 0;

	/*Divide if larger than 2*/
	if ((end-start) >= 1){
		inversionCount += divideAndConquer(arr,start,start+ ((end-start)/2) );
		inversionCount += divideAndConquer(arr,((end-start)/2)+start+1,end);
	}

	/*If one element in array then return*/
	else{ return 0; }

	/*Initialize algorithm variables*/
	startLeft = start;
	startRight = start + ((end-start)/2) + 1;
	endLeft = startRight-1;
	endRight = end;
	curLeft = startLeft;
	curRight = startRight;

	/*Go through assigned section of array and 
	compare left sorted and right sorted elements
	counting inversions*/
	int elementNumber=0;
	while (curLeft <= endLeft && curRight <= endRight){

		/*Look for inversion*/
		if ((*arr)[curLeft] > (*arr)[curRight]){
			
			inversionCount+= endLeft-curLeft+1;
			newArr[elementNumber] = (*arr)[curRight];
				
			curRight++;

		}
		else{

			newArr[elementNumber] = (*arr)[curLeft];
			curLeft++;
		}

		elementNumber++;
	}

	/*Put remaining elements into array that were not
	swapped above*/
	for (;curLeft<=endLeft;curLeft++){
		newArr[elementNumber] = (*arr)[curLeft];
		elementNumber++;
	}
	
	for (;curRight<=endRight;curRight++){
		newArr[elementNumber] = (*arr)[curRight];
		elementNumber++;
	}


	/*Copy new array into old array*/
	for (i=startLeft;i<=endRight;i++){
		(*arr)[i] = newArr[i-startLeft];
	}

	return inversionCount;

}

int main(int argc, char **argv){

	clock_t startTime;		//starting timer
	double executionTime;	//execution time of algorithm;
	long int inversionCount; //number of inversions found
	int *arr = malloc(sizeof(int)*50000);	//data to be processed
	int i=0;
	FILE *file = fopen(argv[1],"r+"); //file to be opened

	/*File not found*/
	if (!file){
		fprintf(stderr,"Could not open file. Exiting\n");
		return(-1);
	}

	/*Get array from file*/ 
	while ( fscanf(file,"%d", &(arr[i]) ) == 1 ){
		i++;
	}


	/*Compute and print bruteforce results*/
	startTime = clock();
	inversionCount = bruteForce(arr,ARR_LEN);
	executionTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;

	printf("Bruteforce inversion count: %ld\t Execution Time: %lf\n\n",inversionCount,executionTime);

	/*Compute and print divide and conquer results*/
	startTime = clock();
	inversionCount = divideAndConquer(&arr,0,ARR_LEN);
	executionTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;

	printf("Divide and conquer inversion count: %ld\t Execution Time: %lf\n\n",inversionCount,executionTime);

	free(arr);

	return 0;
}
