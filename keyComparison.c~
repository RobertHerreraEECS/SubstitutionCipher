#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "frequencyAnalysis.h"


int keyComparison(char* deciphertext,keyMap* key,struct keyPhrase* dictionary,int size);
int calculateHits(char* deciphertext,struct keyPhrase* dictionary,int size);
char* convertToUpperCase(char *sPtr);







int keyComparison(char* deciphertext,keyMap* key,struct keyPhrase* dictionary,int size){
    
    
    //printf("%s\n",deciphertext);
    int hits = calculateHits(deciphertext,dictionary,size);
    //printf("Hits with current key: %d\n",hits);
    
    
    return hits;

}








 char* convertToUpperCase(char *sPtr)
{
    int length = strlen(sPtr);
    
    int i;
    for(i = 0;i < length; i++ ) {
        
        sPtr[i] = toupper(sPtr[i]);
        
    }
   
    
    return sPtr;
}

char* convertToLowerCase(char *sPtr)
{
    int length = strlen(sPtr);
    
    int i;
    for(i = 0;i < length; i++ ) {
        
        sPtr[i] = tolower(sPtr[i]);
        
    }
    
    
    return sPtr;
}

int calculateHits(char* deciphertext,struct keyPhrase* dictionary,int size) {
    
    
    //printf("\n Comparing Deciphered Text to Dictionary...\n\n");
    int i;
    char buffer[100];
    int count = 0;
    for(i = 0; i < size; i++) {

        if(strstr(convertToUpperCase(deciphertext),convertToUpperCase(dictionary[i].word))){
            //printf("%s\n",dictionary[i].word);
            
            if(strlen(dictionary[i].word) == 3){
                count+=9;
            }
            if(strlen(dictionary[i].word) == 4){
                count+=16;
            }
            if(strlen(dictionary[i].word) == 5){
                count+=25;
            }
            if(strlen(dictionary[i].word) >= 6){
                count+=36;
            }
            
            
            count++;
        }   
               
    }
    return count;
    
    
}










