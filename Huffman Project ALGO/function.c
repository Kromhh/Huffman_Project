#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "function.h"

//Read each character, takes its decimal code and convert it to binary.
void textToBinary(char *text, int textLength, char *binary, int binaryLength)
{
    char *octet = malloc(8); //Allocate the necessary memory on the heap for the ptr
    if(octet == NULL)
        exit(1);
    while(*text) //dereference the pointer
    {
        decimalToBinary(*text, octet);
        while(*octet)
            *binary++ = *octet++; //same as *binary = *binary + 1 = *octet = *octet + 1
        //*binary++ = ' '; this line is to separate each bit (8 octet) by a space for comprehension.
        ++text;
        octet -= 8; //reset the pointer; same as octet = octet - 8
    }
    *binary = '\0';
    binary -= binaryLength;
    free(octet); //release the memory
}


void decimalToBinary(int decimal, char *octet)
{
	octet += 8;
	*octet = '\0';
	if(decimal == 0) //Security
	{
		octet -= 8;
		octet = "00000000";
	}
	else
	{
		while(decimal > 0)
		{
			--octet;
			*octet = decimal % 2 + '0';
			decimal = decimal / 2;
		}
	}
    while(strlen(octet) < 8)
    {
        --octet;
        *octet = '0';
    }
}

void Length2files(int binaryLength, int textLength){
    FILE *fp3 = NULL;
    FILE *fp4 = NULL;
//////////////////////////////////////////////////////////////
    fp3 = fopen("input.txt", "w+");
    if (fp3 == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp3, "%d", textLength);
    fclose(fp3);
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
    fp4 = fopen("output.txt", "w+");
    if (fp4 == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp4, "%d", binaryLength);
    fclose(fp4);
//////////////////////////////////////////////////////////////
}
