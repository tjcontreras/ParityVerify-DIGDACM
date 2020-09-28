/*
Author: Teofilo M. Contreras Jr.
Parity Verifier Version 3 Modular 2D

Variables:
input = the inputted data
totBits = number of total bits inputted
bitGrp = number of bits per group/frame (no of data bits + parity bit per frame)
totGrp = number of total groups/frame
parTable = parity table

Specifications:
This is a parity verifer for 44 bytes payload
Meaning the data will enter will be 45 x (9) bits 
The max bits for each section will be 45 x 9 bits
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 256000

void removeSpaces(char *str);
int rowCheck(char *arr, int m, int n);
int columCheck (char *arr, int m, int n);
int greater(int a , int b);
void TwoDParityModular(int start, int end, char *input, char *data,int *err);

/*global variables*/ 
int bitGrp = 9;
int maxBits = 405; // the maximum bit for each section is 45 x 9 = 405 bytes

int main(int argc, char** argv){
	//initializing variables
	
	char input [MAXLEN]; //stores the input that needed to be encoded
	char out [MAXLEN] = "";
	
	int i = 0; 
	int size, totBits, totGrp, err;
	int row, column , rowErr, colErr;
	int startIndex, endIndex, guideIndex, section; 
	

		
	gets(input);
	removeSpaces(input);
	size = strlen(input);
	section = size/maxBits;
	startIndex = 0;
	
	for(i =0; i <= section;i++){
		guideIndex = (maxBits* (i+ 1));
		
		if(guideIndex < size) 	endIndex = guideIndex;
		
		else endIndex = size;	
		
		TwoDParityModular(startIndex, endIndex, input, out,&err);
		startIndex = endIndex;
	}
	
	printf("%s", out);
	
//	printf("\n\n Number of errors detected: %i", err);

	
	return 0;
}

void removeSpaces(char *str) 
{ 
	    // To keep track of non-space character count 
	    int i, count = 0; 
	  
	    // Traverse the given string. If current character 
	    // is not space, then place it at index 'count++' 
	    for ( i = 0; str[i]; i++) 
	        if (str[i] != ' ') 
	            str[count++] = str[i]; // here count is 
	                                   // incremented 
	    str[count] = '\0'; 
}

int rowCheck(char *arr, int m, int n){
	int i, j, bitErr = 0 ;
	int counter = 0;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			//counts the number of 1
			if( *((arr+i*n) + j) == '1') counter ++;	
		}
		
		//if the number of 1 is not even then add 1 to the bit error;
		if(counter%2 > 0 ) bitErr++;
		counter = 0;
	}
	return bitErr;
}

int columCheck (char *arr, int m, int n){
	int i, j, bitErr = 0 ;
	int counter = 0;
	for (j = 0; j < m; j++){
		for (i = 0; i < n; i++){
			//counts the number of 1
			if( *((arr+i*n) + j) == '1') counter ++;	
		}
		
		//if the number of 1 is not even then add 1 to the bit error;
		if(counter%2 > 0 ) bitErr++;
		counter = 0;
	}
	return bitErr;
	
}

int greater(int a , int b){
	if( a >= b) return a;
	else return b;
}

void TwoDParityModular(int start, int end, char *input, char *data,int *err){
	
	int i = 0; 
	int totGrp, totBits = (end - start) ; // total bits is max 45
	int row, col , rowErr, colErr;
	
	totGrp = totBits / bitGrp; //totGrp is max 5
	char parTable[totGrp][bitGrp]; 
	
	
	for( row = 0 ; row < totGrp; row++){
		for( col = 0; col < bitGrp; col++){
				parTable[row][col] = input[start+ i]; //indexing system
			i++;
		}
	}
	
	for( row = 0 ; row < totGrp-1; row++){
		for( col = 0; col < bitGrp-1; col++){
		//	printf("%c", parTable[row][col]);
			strncat(data, &parTable[row][col], 1);
			}
			strcat(data, " ");
	}
	
	
	rowErr = rowCheck((char *)parTable, totGrp,bitGrp);
	colErr = columCheck((char *)parTable, totGrp,bitGrp);
	*err =  greater(rowErr, colErr);
	


}

