#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "memory.h"
#define VNAME 20
#define VNUM 20

/*
*
* Data Structs
*
*/

static char intArray[VNUM][VNAME];
static char recArray[VNUM][VNAME];

static int* intValues;
static int** recValues; 

static int intSize;
static int recSize;

/*
*
* Helper functions
*
*/

// If iden is an integer, return the index. Otherwise, return -1
static int searchInteger(char* iden){
	int location = -1;
	int i;
	for (i=0; i<intSize; i++) {
		if (strcmp(intArray[i], iden)==0) {
			location = i;
		}
	}
	return location;
}

static int searchRecord(char* iden){
	int location = -1;
	int i;
	for (i=0; i<recSize; i++) {
		if (strcmp(recArray[i], iden)==0) {
			location = i;
		}
	}
	return location;
}


/*
*
* Memory functions
*
*/

void initializeSize(){
	intSize=0;
	recSize=0;
}

// Initialize data structures
// Don't worry about freeing memory, will do that in project 5
void memory_init() {
	intValues = (int*) calloc(intSize, sizeof(int));
	recValues = (int**) calloc(recSize, sizeof(int));
}

// Handle an integer or record declaration
void declare(char* iden, int type) {
	if(type == INTEGER){
		strcpy(intArray[intSize], iden);
		intSize++;
	}else if(type == RECORD){
		strcpy(recArray[recSize], iden);
		recSize++;
	}

}

// Store a value to a variable. Remember, unindexed stores to a record go to index 0
void store(char* iden, int value) {
	int idx = searchInteger(iden);
	intValues[idx] = value;
}

// Read a value from a variable. Remember, unindexed reads from a record read index 0
int recall(char* iden) {
	int value;
	int int_idx = searchInteger(iden);
	int rec_idx = searchRecord(iden);

	if(int_idx == -1 && rec_idx == -1){
		printf("Error: varialbe %s has not been declared\n", iden);
		exit(0);
	}
	if(int_idx != -1){
		value = intValues[int_idx];
	}
	if(rec_idx != -1){
		value = recValues[rec_idx][1];
	}

	return value;
}

// Store a value to a record variable, at the given index
void storeRec(char* iden, int index, int value) {
	//Search iden idx
		//if iden idx == -1 error non existing var
	//check index 
	//	if index < 0 error index must be Natural number
	//check recValues[iden idx]
		//if recValues[iden idx] == NULL   error uninitialization error
	//check iden size in recValues[iden idx][0]	
		//if recValues[iden idx][0]	 == index error ouside of array size
	//else
	//index++;
	//recValues[iden idx][index] = value
	int iden_idx = searchRecord(iden);
	if(iden_idx == -1){
		printf("Error: Record variable has not been declared\n");
		exit(0);
	}
	if(index < 0){
		printf("Error: Index must be natural number\n");
		exit(0);
	}
	if(recValues[iden_idx] == NULL){
		printf("Error: Record %s has not been initialized\n", iden);
		exit(0);
	}
	if(recValues[iden_idx][0] == index){
		printf("Error: Index out of range\n");
		exit(0);
	}
	index++;
	recValues[iden_idx][index]=value;

}

// Read a value from a record variable, from the given index
int recallRec(char* iden, int index) {
	//Search iden idx
		//if iden idx == -1 error non existing var
	//check index 
	//	if index < 0 error index must be Natural number
	//check recValues[iden idx]
		//if recValues[iden idx] == NULL   error uninitialization error
	//check iden size in recValues[iden idx][0]	
		//if recValues[iden idx][0] == index error ouside of array size
	//else
	//index++;
	//return recValuse[iden idx][index]
	int iden_idx = searchRecord(iden);
	if(iden_idx == -1){
		printf("Error: Record variable has not been declared\n");
		exit(0);
	}
	if(index < 0){
		printf("Error: Index must be natural number\n");
		exit(0);
	}
	if(recValues[iden_idx] == NULL){
		printf("Error: Record %s has not been initialized\n", iden);
		exit(0);
	}
	if(recValues[iden_idx][0] == index){
		printf("Error: Index out of range\n");
		exit(0);
	}
	index++;
	return recValues[iden_idx][index];
}

// Handle "id := record id" type assignment (x)
void record(char* lhs, char* rhs) {
	//search lhs idx
		//if lhs idx == -1 error non existing var
	//search rhs idx
		//if rhs idx == -1 error non existing var
	//check recValues[rhs idx]
		//if recValues[rhs idx] == NULL   error uninitialization error
	//recValues[lhs idx] = recValues[rhs idx]
	int lhs_idx = searchRecord(lhs);
	int rhs_idx = searchRecord(rhs);
	if(lhs_idx == -1){
		printf("Error: Record %s has not been declared\n", lhs);
		exit(0);
	}
	if(rhs_idx == -1){
		printf("Error: Record %s has not been declared\n", rhs);
		exit(0);
	}
	if(recValues[rhs_idx] == NULL){
		printf("Error: Record %s has not been initialized\n", rhs);
		exit(0);
	}

	recValues[lhs_idx]=recValues[rhs_idx];
}

// Handle "id := new record[<expr>]" type assignment (x)
void allocateRecord(char* iden, int size) {
	//search iden idx
		//if iden idx == -1 error non existing var
	//recValue[iden idx] = calloc (size+1)
	//recValue[iden idx][0] = size

	int idx = searchRecord(iden);
	if(idx == -1){
		printf("Error: Record variable has not been declared\n");
		exit(0);
	}
	if(size < 1){
		printf("Error: Size of Record must be greater than 0\n");
		exit(0);
	}
	recValues[idx]=(int*) calloc(size+1,sizeof(int));
	recValues[idx][0]=size;
}

//print variables and its values


void printInt(){
	int i;
	printf("Int variables: \n");
	for(i=0; i< intSize;i++){
		printf(" %s\n", intArray[i]);
	}
}

void printRec(){
	int i;
	printf("Rec variables: \n");
	for(i=0; i< recSize;i++){
		printf(" %s\n", recArray[i]);
	}
}

void printIntValues(){
	int i;
	printf("----------Integer Variables-----------------\n");
	for(i=0; i< intSize;i++){
		printf("Int: %s   Value: %d\n", intArray[i], intValues[i]);
	}
}

void printRecValues(){
	int i, j;
	printf("----------Record Variables------------------\n");
	for(i=0; i<recSize;i++){
		printf("Rec: %s\n", recArray[i]);

		if(recValues[i] == NULL){
			continue;
		}

		int arraySize = recValues[i][0];
		printf("Values: ");
		for(j=0; j<=arraySize;j++){
			printf("%d, ", recValues[i][j]);
		}printf("\n");
	}

}

void printIntSize(){
	printf("Number of Integers: %d\n", intSize);
}

void printRecSize(){
	printf("Number of Records: %d\n", recSize);
}