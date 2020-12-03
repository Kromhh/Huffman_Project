#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>
#include "Structure.h"

int main () {
	char text[10000];
    char *binary;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
	int textLength, binaryLength;

////////////////////////////////////////////////////////////// part 1 creation of the binary 

    fp1 = fopen("Texte.txt", "r");
    if (fp1 == NULL){ //Security
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(fp1, "%10000[^\n]s", text);
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
///////////////////////////////////////////////////////////// part 2 creation of huffman tree

    Node* Htree ; 

    printf  ("Hello\n\n") ; 

    Element* list = occ_text (); 
    display_list (list);

    sorted_list (&(list)) ; 
    printf ("\n---------------------- list sorted ----------------------\n");
    display_list (list) ; 


    Htree = create_huffmanTree (&(list)) ;
    printf ("\n-------------------------------- Huffman Tree --------------------------------\n");
    display_tree (Htree); 

    printf ("\n-----------------Free HuffmanTree ----------------\n");
    freeTree (Htree) ; 
    free(binary); //Free the memory

    return 0; 
}
