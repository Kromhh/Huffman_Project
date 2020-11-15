#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "function.h"

int main()
{
	char text[10000];
    char* binary = NULL;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
	int textLength, binaryLength;
//////////////////////////////////////////////////////////////
    fp1 = fopen("letter.txt", "r");
    if (fp1 == NULL){ //Security
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(fp1, "%[^\n]s", text);
    fclose(fp1);
//////////////////////////////////////////////////////////////
	textLength = strlen(text); //Length of the text entered
    binaryLength = textLength * 8;      // 8 binary digits
    binary = malloc(binaryLength + 1);  // + 1 null terminator
    if(binary == NULL)
        exit(1);

    textToBinary(text, textLength, binary, binaryLength);
//////////////////////////////////////////////////////////////
    fp2 = fopen("bit.txt", "w+");
    if (fp2 == NULL){ //Security
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp2, "%s", binary);
    fclose(fp2);
//////////////////////////////////////////////////////////////
    Length2files(binaryLength, textLength);

    free(binary); //Free the memory
	return 0;
}
