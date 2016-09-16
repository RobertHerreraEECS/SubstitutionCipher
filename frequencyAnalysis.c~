#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequencyAnalysis.h"


keyMap* letterFrequency(char * ciphertext,int shift);

void sort(int *array, int num_elements, char *alphabet);

int checkShift(char character,int shift);

void sortStruct(keyMap *map);

keyMap* letterFrequency(char * ciphertext,int shift) {
	
    
	
	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char copy_alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char englishFrequency[26] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'};

 
	int alphaCount[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	
	int i = 0;
	while(ciphertext[i] != '\0' ) {
		
		
		int j;
		for(j=0;j < 26; j++) {
			
			if(alphabet[j] == ciphertext[i] && alphabet[j] != ' ' && ciphertext[i] != ' ') {  // calculates occurences
				
				alphaCount[j]++;
				break;
			}
			
		}
		
		i++;
	}
    
    int message_size = i;
	int size = 26;
    
    
    
	sort(alphaCount,size,copy_alphabet);
    
    
    keyMap map[26];
    
    int j;
    printf("\e[1;1H\e[2J");
    printf("Frequency Mapping\n--------------------------------------------------\n");
 
    for(j=0;j<26;j++){
        
        map[j].cipherLetter = copy_alphabet[j];
        map[j].mappedLetter = englishFrequency[j];
        map[j].freq = alphaCount[j];
        
        printf("%c -> %c :: %d\n",map[j].cipherLetter,map[j].mappedLetter, map[j].freq);

       
    }

    printf("Press any key to continue...");
    getchar();
    printf("\e[1;1H\e[2J");

    //sortStruct(map);

    keyMap* copy_map = calloc(size, sizeof(keyMap*) * size);

    copy_map = memcpy(copy_map,map,sizeof(keyMap*) * size);
    
    
    return copy_map;

}


void sortStruct(keyMap *map) {
    
    int swap,i,j = 0;
    char swapA = ' ';
    int num_elements = 26;
    int swapB = 0;
    
    for (i = 0 ; i < ( num_elements - 1 ); i++)
    {
        for (j = 0 ; j < num_elements - i - 1; j++)
        {
            if (map[j].mappedLetter > map[j+1].mappedLetter) /* For decreasing order use < */
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



void sort(int *array, int num_elements, char *alphabet) {

 	int swap,i,j = 0;
	char swapA = ' ';
 
	    for (i = 0 ; i < ( num_elements - 1 ); i++)
	    {
	      for (j = 0 ; j < num_elements - i - 1; j++)
	      {
	        if (array[j] < array[j+1]) /* For increasing order use > */
	        {
	          swap       = array[j];
			  swapA      = alphabet[j];
	          array[j]   = array[j+1];
			  alphabet[j] = alphabet[j+1];
	          array[j+1] = swap;
			  alphabet[j+1] = swapA;
	        }
	      }
	    }


}
