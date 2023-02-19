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
	int idx = searchInteger(iden);
	return intValues[idx];
}

// Store a value to a record variable, at the given index
void storeRec(char* iden, int index, int value) {
	//Search iden idx
		//if iden idx == -1 error non existing var
	//check recValues[iden idx]
		//if recValues[iden idx] == NULL   error uninitialization error
	//check iden size in recValues[iden idx][0]	
		//if iden size == index error ouside of array size
	//else
	//index++;
	//recValues[iden idx][index] = value
}

// Read a value from a record variable, from the given index
int recallRec(char* iden, int index) {
	//Search iden idx
		//if iden idx == -1 error non existing var
	//check recValues[iden idx]
		//if recValues[iden idx] == NULL   error uninitialization error
	//check iden size in recValues[iden idx][0]	
		//if iden size == index error ouside of array size
	//else
	//index++;
	//return recValuse[iden idx][index]
}

// Handle "id := record id" type assignment
void record(char* lhs, char* rhs) {
	//search lhs idx
		//if lhs idx == -1 error non existing var
	//search rhs idx
		//if rhs idx == -1 error non existing var
	//check rhs Size in recValues[rhs idx]
		//if 0 error uninitialization error
	//recValues[lhs idx] = recValues[rhs idx]
}

// Handle "id := new record[<expr>]" type assignment
void allocateRecord(char* iden, int size) {
	//search iden idx
		//if iden idx == -1 error non existing var
	//recValue[iden idx] = calloc (size+1)
	//recValue[iden idx][0] = size

	int idx = searchRecord(iden);
	if(idx == -1){
		printf("Error: Record variable has not declared\n");
		exit(0);
	}
	recValues[idx]=(int*) calloc(size+1,sizeof(int));
	recValues[idx][0]=size;
}

//print variables and its values


void printInt(){
	int i;
	for(i=0; i< intSize;i++){
		printf("Int Variable: %s\n", intArray[i]);
	}
}

void printRec(){
	int i;
	for(i=0; i< recSize;i++){
		printf("Rec Variable: %s\n", recArray[i]);
	}
}

void printIntValues(){
	int i;
	for(i=0; i< intSize;i++){
		printf("Int: %s   Value: %d\n", intArray[i], intValues[i]);
	}
}

void printRecValues(){
	int i, j;
	for(i=0; i<recSize;i++){
		printf("Rec: %s\n", recArray[i]);
		int arraySize = recValues[i][0];
		printf("Values: ");
		for(j=0; j<=arraySize;j++){
			printf("%d, ", recValues[i][j]);
		}printf("\n");
	}

}

void printIntSize(){
	printf("%d\n", intSize);
}

void printRecSize(){
	printf("%d\n", recSize);
}