//
//  decrypt.c
//  
//
//  Created by Robert Herrera on 2/4/16.
//
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "frequencyAnalysis.h"


#define MAX_HIT_SIZE 5000

typedef struct hitsArray {
    
    char key[26];
    char cipherLetter[26];
    char *deciphertext;
    int hits;
    
}HITS;


void decrypt(char* ciphertext, keyMap* key,struct keyPhrase* dictionary,int size,int type);
void mapCharacters(char *ciphertext, keyMap* key);
void shiftKeyMapping(keyMap* key);
void loadCurrentKey(HITS* hitArray, keyMap* key,char* ciphertext,int index);
void printKey(keyMap* key);
void sortHits(HITS* arr);
void assignKeys(char assignment[KEY_SIZE], char assignTo[KEY_SIZE]);
void sortStructByFrequency(keyMap *map);
void swapStructByFrequency(keyMap *map, int j);
void doubleSwapStructByFrequency(keyMap *map, int j);
void tripleSwapStructByFrequency(keyMap *map, int j);
void assignCipherLetter(char assignment[KEY_SIZE], char assignTo[KEY_SIZE]);
void swapUserChoice(char* deciphertext,char swapA,char swapB, HITS* hitStructure, keyMap* key);
void swapStructByMappedLetter(keyMap *map, int j);
void doubleSwapStructByMappedLetter(keyMap *map, int j);
void quadSwapStructByFrequency(keyMap *map, int j);
void pentSwapStructByFrequency(keyMap *map, int j);


void decrypt(char* ciphertext, keyMap* key,struct keyPhrase* dictionary,int size,int type) {
    int i,j,k,q,hits,hitIndex;
    printKey(key);
    char* copy_text = malloc(sizeof(char)*(strlen(ciphertext)+1));
    keyMap originalKey[26];
    HITS hitStruct[5000];
    char userSwap[6];
    char userInputKey[27];
   

if(type == 1) {// -g        ENTERED KEY

  printf("\nEnter Key:\n-");
  for(i = 0; i < 26; i++){
     printf("%c",key[i].mappedLetter);
  }
  printf("\n-");
  scanf("%s",userInputKey);
  for(i = 0; i < 26; i++){
     key[i].cipherLetter = userInputKey[i];
  }
  strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
  mapCharacters(copy_text,key);
    printKey(key);
    hitStruct[0].hits = keyComparison(copy_text,key,dictionary,size);
    printf("hits: %d\n",hitStruct[0].hits);
    printf("%s\n",copy_text);
  printf("\n");
}// end entered KEY

    
    

if(type == 0) {  // -s     AUTO DECRYPTION
    
    int iterations;
    printf("enter number of iterations: ");
    scanf("%d",&iterations);
    printf("\n");
    

    for(i = 0;i < MAX_HIT_SIZE;i++){
     hitStruct[i].hits = 0;
    }

    hitIndex = 0;
    
    for(i = 0; i < 26; i++){
       originalKey[i].mappedLetter = key[i].mappedLetter;
       originalKey[i].cipherLetter = key[i].cipherLetter;
    }
    printKey(key);
    strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
    mapCharacters(copy_text,key);
    printKey(key);
    hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
    printf("hits: %d\n",hitStruct[hitIndex].hits);
    printf("%s\n",copy_text);
    loadCurrentKey(hitStruct,key,copy_text,hitIndex);


 hitIndex++;
 for(q = 0; q < iterations; q++) {

   printf("Trying Single Swap\n");
/* Single Swap Iteration */
  for(k = 0; k < 8; k++) {
    for(i = 0; i < 26-1; i++){

    for(j = 0; j < 26; j++){
       key[j].mappedLetter = originalKey[j].mappedLetter;
       key[j].cipherLetter = originalKey[j].cipherLetter;
    }

    swapStructByFrequency(key,i);
    strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
    mapCharacters(copy_text,key);
    hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
    printf("hits: %d\n",hitStruct[hitIndex].hits);
    loadCurrentKey(hitStruct,key,copy_text,hitIndex);
    hitIndex++;
    }
    sortHits(hitStruct);
    
    for(i = 0; i < 26; i++){
        key[i].mappedLetter = hitStruct[0].key[i];
        key[i].cipherLetter = hitStruct[0].cipherLetter[i];
    }
    for(i = 0; i < 26; i++){
       originalKey[i].mappedLetter = key[i].mappedLetter;
       originalKey[i].cipherLetter = key[i].cipherLetter;
    }
    printf("\n----------------\n---------------\n\n");
    hitIndex++;

  }

    for(i = 0; i < 26; i++){
        key[i].mappedLetter = hitStruct[0].key[i];
        key[i].cipherLetter = hitStruct[0].cipherLetter[i];
    }
    for(i = 0; i < 26; i++){
       originalKey[i].mappedLetter = key[i].mappedLetter;
       originalKey[i].cipherLetter = key[i].cipherLetter;
    }


    hitIndex++;
    printf("Trying Double Swap\n");
    /* Double Swap Iteration */

      for(k = 0; k < 8; k++) {
    for(i = 0; i < 26-2; i++){

    for(j = 0; j < 26; j++){
       key[j].mappedLetter = originalKey[j].mappedLetter;
       key[j].cipherLetter = originalKey[j].cipherLetter;
    }
    doubleSwapStructByFrequency(key,i);
    strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
    mapCharacters(copy_text,key);
    hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
    printf("hits: %d\n",hitStruct[hitIndex].hits);
    loadCurrentKey(hitStruct,key,copy_text,hitIndex);
    hitIndex++;
    }
    sortHits(hitStruct);
    
    for(i = 0; i < 26; i++){
        key[i].mappedLetter = hitStruct[0].key[i];
        key[i].cipherLetter = hitStruct[0].cipherLetter[i];
    }
    for(i = 0; i < 26; i++){
       originalKey[i].mappedLetter = key[i].mappedLetter;
       originalKey[i].cipherLetter = key[i].cipherLetter;
    }
    printf("\n----------------\n---------------\n\n");
    hitIndex++;

  }



      hitIndex++;
       printf("Trying Triple Swap\n");
    /* Triple Swap Iteration */

      for(k = 0; k < 8; k++) {
    for(i = 0; i < 26-3; i++){

    for(j = 0; j < 26; j++){
       key[j].mappedLetter = originalKey[j].mappedLetter;
       key[j].cipherLetter = originalKey[j].cipherLetter;
    }
    tripleSwapStructByFrequency(key,i);
    strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
    mapCharacters(copy_text,key);
    hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
    printf("hits: %d\n",hitStruct[hitIndex].hits);
    loadCurrentKey(hitStruct,key,copy_text,hitIndex);
    hitIndex++;
    }
    sortHits(hitStruct);
    
    for(i = 0; i < 26; i++){
        key[i].mappedLetter = hitStruct[0].key[i];
        key[i].cipherLetter = hitStruct[0].cipherLetter[i];
    }
    for(i = 0; i < 26; i++){
       originalKey[i].mappedLetter = key[i].mappedLetter;
       originalKey[i].cipherLetter = key[i].cipherLetter;
    }
    printf("\n----------------\n---------------\n\n");
    hitIndex++;

  }
     
     
     
     
     hitIndex++;
     printf("Trying Quad Swap\n");
     /* Quad Swap Iteration */
     
     for(k = 0; k < 8; k++) {
         for(i = 0; i < 26-4; i++){
             
             for(j = 0; j < 26; j++){
                 key[j].mappedLetter = originalKey[j].mappedLetter;
                 key[j].cipherLetter = originalKey[j].cipherLetter;
             }
             quadSwapStructByFrequency(key,i);
             strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
             mapCharacters(copy_text,key);
             hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
             printf("hits: %d\n",hitStruct[hitIndex].hits);
             loadCurrentKey(hitStruct,key,copy_text,hitIndex);
             hitIndex++;
         }
         sortHits(hitStruct);
         
         for(i = 0; i < 26; i++){
             key[i].mappedLetter = hitStruct[0].key[i];
             key[i].cipherLetter = hitStruct[0].cipherLetter[i];
         }
         for(i = 0; i < 26; i++){
             originalKey[i].mappedLetter = key[i].mappedLetter;
             originalKey[i].cipherLetter = key[i].cipherLetter;
         }
         printf("\n----------------\n---------------\n\n");
         hitIndex++;
         
     }// end quad
     
     
     hitIndex++;
     printf("Trying Pent Swap\n");
     /* Pent Swap Iteration */
     
     for(k = 0; k < 8; k++) {
         for(i = 0; i < 26-5; i++){
             
             for(j = 0; j < 26; j++){
                 key[j].mappedLetter = originalKey[j].mappedLetter;
                 key[j].cipherLetter = originalKey[j].cipherLetter;
             }
             quadSwapStructByFrequency(key,i);
             strncpy(copy_text,ciphertext, strlen(ciphertext) + 1);
             mapCharacters(copy_text,key);
             hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
             printf("hits: %d\n",hitStruct[hitIndex].hits);
             loadCurrentKey(hitStruct,key,copy_text,hitIndex);
             hitIndex++;
         }
         sortHits(hitStruct);
         
         for(i = 0; i < 26; i++){
             key[i].mappedLetter = hitStruct[0].key[i];
             key[i].cipherLetter = hitStruct[0].cipherLetter[i];
         }
         for(i = 0; i < 26; i++){
             originalKey[i].mappedLetter = key[i].mappedLetter;
             originalKey[i].cipherLetter = key[i].cipherLetter;
         }
         printf("\n----------------\n---------------\n\n");
         hitIndex++;
         
     }// end pent
     
     
     sortHits(hitStruct);
     
     for(i = 0; i < 26; i++){
         key[i].mappedLetter = hitStruct[0].key[i];
         key[i].cipherLetter = hitStruct[0].cipherLetter[i];
     }
     hitIndex++;
     
  
}


    sortHits(hitStruct);
    printf("\n\nTOP RESULT\n");
    printf("hits:%d\ntext:\n%s\n",hitStruct[0].hits,hitStruct[0].deciphertext);
    for(i = 0; i < 26; i++){
        key[i].mappedLetter = hitStruct[0].key[i];
        key[i].cipherLetter = hitStruct[0].cipherLetter[i];
    }
    printKey(key);

   char swapA,swapB;
   char* tempCopy = malloc(sizeof(char)*(strlen(copy_text)+1));
   strncpy(tempCopy,hitStruct[0].deciphertext,strlen(copy_text) + 1);

    while(strcmp("exit",userSwap)!= 0) {
   
	printf("Manual Decryption\n\nEnter Swap Combo(i.e. swap:E,A)\nTo terminate type 'exit'\n");
        scanf("%s",userSwap);
        if(strcmp("exit",userSwap)== 0) {
        printf("Manual Decryption Exited\n");
	break;
 	}
     	swapA = userSwap[0];
        swapB = userSwap[2];   
        swapUserChoice(tempCopy,swapA,swapB,hitStruct,key);
	mapCharacters(copy_text,key);
        hitStruct[hitIndex].hits = keyComparison(copy_text,key,dictionary,size);
        printf("hits: %d\n",hitStruct[hitIndex].hits);
        loadCurrentKey(hitStruct,key,tempCopy,hitIndex);
        printKey(key);
        printf("text:\n%s\n",tempCopy);
        
    }
    
    }// end type -s




     

    
    free(hitStruct->deciphertext);
    }//end decrypt




void swapUserChoice(char* deciphertext,char swapA,char swapB, HITS* hitStructure, keyMap* key){

          int tempA,tempB,i;

   
      for (i = 0; i < KEY_SIZE; i++) {
                
               key[i].mappedLetter = hitStructure[0].key[i];
               key[i].cipherLetter = hitStructure[0].cipherLetter[i];
        }
      for (i = 0; i < KEY_SIZE; i++) {
                
            if (key[i].mappedLetter == swapA){
 		 tempA = i;
 		
              }
             if (key[i].mappedLetter == swapB){
 		 tempB = i;
              }
        } 
 
       
       
       key[tempA].cipherLetter = hitStructure[0].cipherLetter[tempB];

       key[tempB].cipherLetter = hitStructure[0].cipherLetter[tempA];


       swapA = key[tempA].mappedLetter;
       swapB = key[tempB].mappedLetter;


   for (i = 0; i < strlen(deciphertext); i++) {
           
      if(deciphertext[i] == swapB){
          deciphertext[i] = swapA;
      } 
      else if(deciphertext[i] == swapA){
          deciphertext[i] = swapB;
      }     
            
        }  
   printKey(key);
   printf("\n\n %s\n",deciphertext);

   
}


void sortStructByFrequency(keyMap *map) {
    
    int swap,i,j = 0;
    char swapA = ' ';
    int swapB = ' ';
    int num_elements = 26;
    
    for (i = 0 ; i < ( num_elements - 1 ); i++)
    {
        for (j = 0 ; j < num_elements - i - 1; j++)
        {
            
            if (map[j].freq < map[j+1].freq) /* For decreasing order use < */
            {
                swap       = map[j].mappedLetter;
                swapA      = map[j].cipherLetter;
                swapB      = map[j].freq;
                map[j].mappedLetter   = map[j+1].mappedLetter;
                map[j].cipherLetter = map[j+1].cipherLetter;
                map[j].freq         = map[j+1].freq;
                map[j+1].mappedLetter = swap;
                map[j+1].cipherLetter = swapA;
                map[j+1].freq         = swapB;
            }
        }
    }
    
    
}


void doubleSwapStructByFrequency(keyMap *map, int j) {
    
    char swapA = ' ';
    char swapB = ' ';
    int  swapC = 0;
    int num_elements = 26;
    
    //swapA       = map[j].mappedLetter;
    swapB      = map[j].cipherLetter;
    swapC      = map[j].freq;
    //map[j].mappedLetter   = map[j+2].mappedLetter;
    map[j].cipherLetter = map[j+2].cipherLetter;
    map[j].freq         = map[j+2].freq;
    //map[j+2].mappedLetter = swapA;
    map[j+2].cipherLetter = swapB;
    map[j+2].freq         = swapC;
    
    
}

void doubleSwapStructByMappedLetter(keyMap *map, int j) {
    
    char swapA = ' ';
    char swapB = ' ';
    int  swapC = 0;
    int num_elements = 26;
    
    swapA       = map[j].mappedLetter;
 
    map[j].mappedLetter   = map[j+2].mappedLetter;
 
    map[j+2].mappedLetter = swapA;
}



void quadSwapStructByFrequency(keyMap *map, int j) {
    
    char swapA = ' ';
    char swapB = ' ';
    int  swapC = 0;
    int num_elements = 26;
    
    //swapA       = map[j].mappedLetter;
    swapB      = map[j].cipherLetter;
    swapC      = map[j].freq;
    //map[j].mappedLetter   = map[j+3].mappedLetter;
    map[j].cipherLetter = map[j+4].cipherLetter;
    map[j].freq         = map[j+4].freq;
    //map[j+3].mappedLetter = swapA;
    map[j+4].cipherLetter = swapB;
    map[j+4].freq         = swapC;
    
    
}

void pentSwapStructByFrequency(keyMap *map, int j) {
    
    char swapA = ' ';
    char swapB = ' ';
    int  swapC = 0;
    int num_elements = 26;
    
    //swapA       = map[j].mappedLetter;
    swapB      = map[j].cipherLetter;
    swapC      = map[j].freq;
    //map[j].mappedLetter   = map[j+3].mappedLetter;
    map[j].cipherLetter = map[j+5].cipherLetter;
    map[j].freq         = map[j+5].freq;
    //map[j+3].mappedLetter = swapA;
    map[j+5].cipherLetter = swapB;
    map[j+5].freq         = swapC;
    
    
}

void tripleSwapStructByFrequency(keyMap *map, int j) {
    
    char swapA = ' ';
    char swapB = ' ';
    int  swapC = 0;
    int num_elements = 26;
    
    //swapA       = map[j].mappedLetter;
    swapB      = map[j].cipherLetter;
    swapC      = map[j].freq;
    //map[j].mappedLetter   = map[j+3].mappedLetter;
    map[j].cipherLetter = map[j+3].cipherLetter;
    map[j].freq         = map[j+3].freq;
    //map[j+3].mappedLetter = swapA;
    map[j+3].cipherLetter = swapB;
    map[j+3].freq         = swapC;
    
    
}

void swapStructByFrequency(keyMap *map, int j) {
    
        char swapA = ' ';
        char swapB = ' ';
        int  swapC = 0;
        int num_elements = 26;
    
        //swapA       = map[j].mappedLetter;
        swapB      = map[j].cipherLetter;
        swapC      = map[j].freq;
        //map[j].mappedLetter   = map[j+1].mappedLetter;
        map[j].cipherLetter = map[j+1].cipherLetter;
        map[j].freq         = map[j+1].freq;
        //map[j+1].mappedLetter = swapA;
        map[j+1].cipherLetter = swapB;
        map[j+1].freq         = swapC;
        

}


void swapStructByMappedLetter(keyMap *map, int j) {
    
        char swapA = ' ';
        char swapB = ' ';
        int  swapC = 0;
        int num_elements = 26;
    
        swapA       = map[j].mappedLetter;
        map[j].mappedLetter   = map[j+1].mappedLetter;
        map[j+1].mappedLetter = swapA;

        

}


void sortHits(HITS* arr) {
    
    int swap,i,j = 0;
    char key[26]; // swap 2nd item
    char cipherLetter[26];
    char* bufferSpace; // swap 3rd item
    
    for (i = 0 ; i < ( MAX_HIT_SIZE - 1 ); i++)
    {
        for (j = 0 ; j < MAX_HIT_SIZE - i - 1; j++)
        {
            if (arr[j].hits < arr[j+1].hits) /* For decreasing order use < */
            {
                swap       = arr[j].hits;
                assignKeys(key,arr[j].key);
                assignCipherLetter(cipherLetter,arr[j].cipherLetter);
                bufferSpace = arr[j].deciphertext;
                arr[j].hits   = arr[j+1].hits;
                assignKeys(arr[j].key, arr[j+1].key);
                assignCipherLetter(arr[j].cipherLetter, arr[j+1].cipherLetter);
                arr[j].deciphertext = arr[j+1].deciphertext;
                arr[j+1].hits = swap;
                arr[j+1].deciphertext = bufferSpace;
                assignKeys(arr[j+1].key,key);
                assignCipherLetter(arr[j+1].cipherLetter,cipherLetter);
            }
        }
    }
    
    
}

void assignKeys(char assignment[KEY_SIZE], char assignTo[KEY_SIZE]) {
    
    int i;
    char temp;
    for (i = 0; i < KEY_SIZE; i++) {
        assignment[i] = assignTo[i];
    }
    
}

void assignCipherLetter(char assignment[KEY_SIZE], char assignTo[KEY_SIZE]) {
    
    int i;
    char temp;
    for (i = 0; i < KEY_SIZE; i++) {
        assignment[i] = assignTo[i];
    }
    
}


void printKey(keyMap* rkey) {
  
    int i;
    printf("cipher Key:\n");
    for ( i = 0; i < KEY_SIZE; i++ ) {
        
        printf("%c",rkey[i].cipherLetter); // print cipher text ordering alpha order
    }
    printf("\n");
    for ( i = 0; i < KEY_SIZE; i++ ) {
        
        printf("%c",rkey[i].mappedLetter); // print frequency
    }
    printf("\n");
}

void loadCurrentKey(HITS* hitArray, keyMap* key,char* ciphertext,int index) {
       
    hitArray[index].deciphertext = malloc(sizeof(char) * (strlen(ciphertext) +1));
     strncpy(hitArray[index].deciphertext,ciphertext,(int)strlen(ciphertext) + 1);

    int i;
    for(i = 0; i < KEY_SIZE; i++) {
        
        hitArray[index].key[i] = key[i].mappedLetter;
       hitArray[index].cipherLetter[i] = key[i].cipherLetter;
	
    }

}




void mapCharacters(char *ciphertexts, keyMap* key) {
    
    
    int i= 0;
    int x = 0;
    int j;
    while(ciphertexts[i]!='\0') {
        
        for(j = 0; j < KEY_SIZE; j++) {
            
            if ( ciphertexts[i] == key[j].cipherLetter) {
                
                ciphertexts[i] = key[j].mappedLetter;
                break;
            }
        }//end for
        
        i++;
    }//end while
}







