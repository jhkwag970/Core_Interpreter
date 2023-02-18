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
	for (int i=0; i<intSize; i++) {
		if (strcmp(intArray[i], iden)==0) {
			location = i;
		}
	}
	return location;
}

static int searchRecord(char* iden){
	int location = -1;
	for (int i=0; i<recSize; i++) {
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

// Initialize data structures
// Don't worry about freeing memory, will do that in project 5
void memory_init() {
	intValues = (int*) calloc(intSize, sizeof(int));
	recValues = (int**) calloc(recSize, sizeof(int));
	intSize=0;
	recSize=0;
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

}

// Read a value from a variable. Remember, unindexed reads from a record read index 0
int recall(char* iden) {

}

// Store a value to a record variable, at the given index
void storeRec(char* iden, int index, int value) {

}

// Read a value from a record variable, from the given index
int recallRec(char* iden, int index) {

}

// Handle "id := record id" type assignment
void record(char* lhs, char* rhs) {

}

// Handle "id := new record[<expr>]" type assignment
void allocateRecord(char* iden, int size) {

}