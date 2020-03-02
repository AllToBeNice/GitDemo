/*
Name: binFile.cpp
Author: yuanchenzhu
Created: 03-02-2020
Last Modified: 03-02-2020
Version: 1.0
Description: Show any file in HEX.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <io.h>
// #include <unistd.h>
#define LEN 1000
#define OFFSET 30

void binFile(char [LEN], int);
int main(int argc, char *argv[]){
	if(argc != 3){
		printf("usage: %s operation_name file_path offsset_num\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	else{ 
		printf("The result is: \n\n");
		binFile(argv[1], atoi(argv[2]));
		return 0;
	}
}

void binFile(char filename[LEN], int offset){
	assert(access(filename, 4) == 0);
	
	int i, j, n;
	unsigned char temp[offset] = {};
	FILE *fp = fopen(filename, "rb");
	
	printf(" Offset  %*sBytes%*s   %*sCharacters%*s\n", \
		(int)((3*offset-6)/2), " ", (int)((3*offset-6)/2), " ",\
		(int)((offset-10)/2+1), " ", (int)((offset-10)/2), " ");
	printf(" ------   ");
	for(i=0;i<(3*offset-1);i++) printf("%c", '-');
	printf("   ");
	for(i=0;i<offset;i++) printf("%c", '-');
	printf("\n");
	
	j = 0;
	while(1){
		n = fread(temp, sizeof(unsigned char), offset, fp);
		
		printf("  %5d", offset * j);
		j++;
		printf("   ");
		
		for(i=0;i<n;i++){
			if(i == 0) printf("%02X", temp[i]);
			else printf(" %02X", temp[i]);
		}
		if(n < offset){
			for(i=n;i<offset;i++) printf("   ");
		}
		printf("   ");
		
		for(i=0;i<n;i++){
			if(isprint(temp[i]) == 0) printf(".");
			else printf("%c", temp[i]);
		}
		printf("\n");
		
		for(i=0;i<offset+1;i++) temp[i] = '\0';
		if(n < offset) break;
	}
	fclose(fp);
}
