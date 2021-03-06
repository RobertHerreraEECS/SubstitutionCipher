 /* 
*   	Computer Security
*     Programming Assigment 1
*
*    
*          02/02/2016
*     Created By: Robert Herrera
*     
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequencyAnalysis.h"
//#include ".h"
// Cracking Substitution Cipher


// Function Prototypes
void arguments(int argc,char **args);
char* readFileIn(FILE *fp, char *path);
void readDictFileIn(FILE *fp,char *path,struct keyPhrase* keys,int size);
int readNumberFileLinesIn(FILE *fp,char *path);
void freeDictionarySpace(struct keyPhrase* keys,int size);


// Main function
int main(int argc, char **argv) {

    arguments(argc,argv);
   
   
	
    char *path = "ciphertext.txt";
    char *dict = "dictionary.txt";
    int shift = 0;
    FILE *fp;
    FILE *fs;
    char* ciphertext = malloc(sizeof(char) * ((strlen(readFileIn(fp,path)))+1));
	strncpy(ciphertext,readFileIn(fp,path),strlen(readFileIn(fp,path))+1); //WRONG
    
    keyMap* mappedKey  = letterFrequency(ciphertext,shift); // returns mapped structure array containing cipher letter and corresponding key value
    int FILE_SIZE = readNumberFileLinesIn(fs,dict);
    KEY words[FILE_SIZE];
	readDictFileIn(fs,dict,words,FILE_SIZE);
	

    if(strcmp(argv[1],"-s") == 0) {
     decrypt(ciphertext,mappedKey,words,FILE_SIZE,0);
    }
    else if(strcmp(argv[1],"-g") == 0) {
     decrypt(ciphertext,mappedKey,words,FILE_SIZE,1);
    }
	else if (strcmp(argv[1],"-eT")==0) {
		printf("Encrypt");
	}

    freeDictionarySpace(words,FILE_SIZE);
    free(ciphertext); 
   
    printf("Program Exited.\n");
	return 0;
} // end main




void freeDictionarySpace(struct keyPhrase* keys,int size) {
        free(keys->word);
}


int readNumberFileLinesIn(FILE *fp,char *path) {
    int FILE_SIZE_LINES = 0;
    char buffer[50];
    fp = fopen(path,"r");
    
    if (fp == NULL) {
        printf("No such file %s exists\n",path);
        perror("Error opening file!\n");
        exit(1);
    }
    
    while(!feof(fp)) {
        fgets(buffer,60,fp);
        FILE_SIZE_LINES++;
    }
    fclose(fp);
    
    return FILE_SIZE_LINES;
}


void readDictFileIn(FILE *fp,char *path,struct keyPhrase* keys,int size) {

    char buffer[50];
    fp = fopen(path,"r");
    
    if (fp == NULL) {
        printf("No such file %s exists\n",path);
        perror("Error opening file!\n");
        exit(1);
    }
	
    char line_buffer[50];
    int count,keyLength = 0;
    
    while(!feof(fp)) {
        
        fscanf(fp,"%s",line_buffer);
        //printf("%s\n",line_buffer);
        keyLength = strlen(line_buffer);
	//printf("- %d\n",keyLength);
	keys[count].word = NULL;
       keys[count].word = calloc(keyLength + 1,sizeof(char *));

        strcpy(keys[count].word,line_buffer);
	//printf(" - %s\n",keys[count].word);
        count++;
         
    }
    printf("\n\n number of words: %d\n",count);
    fclose(fp);
    
    return;
}


char* readFileIn(FILE *fp,char *path) {
	
	int FILE_SIZE_LINES = 0;
	char buffer[1000];
	fp = fopen(path,"r");
	
	if (fp == NULL) {
		printf("No such file %s exists\n",path);
		perror("Error opening file!\n");
		exit(1);
	}
	
	while(!feof(fp)) {
		fgetc(fp);
			FILE_SIZE_LINES++;
	}
	fclose(fp);
    
	//printf("There are %d characters\n",FILE_SIZE_LINES);
	fp = fopen(path,"r");
	char *line = malloc(sizeof(char *) * FILE_SIZE_LINES);
	char line_buffer[100];
	while(!feof(fp)) {
		
		fscanf(fp,"%s",line_buffer);	
		line = strcat(line,line_buffer);
		//printf("%s\n",line);
	}
	fclose(fp);
	
	
	
	return line;
}


void arguments(int argc, char **args) {

	if (argc < 2) {
		printf("Not enough arguments...\nform: ./[exec] [-s] or ./[exec] [-g]\n");
		exit(1);
	}
	if (strcmp(args[1],"-s") == 0 || strcmp(args[1],"-g") == 0 || strcmp(args[1],"-eT") == 0 )
	{
		
	} else {
          printf("Invalid Command...\nform: ./[exec] [-s] or ./[exec] [-g]\n");
		exit(1);
        }

   
}
