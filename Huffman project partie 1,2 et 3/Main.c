#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>
#include "Structure.h"

int main () {
	char text[10000];
    char *binary;                   // for the Binary of all the letter
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
	int textLength, binaryLength;
    char New_binary [100] ;         // For the new binary of the letter

////////////////////////////////////////////////////////////// 
/*To refrech dictionnary in case we have something in it or create it*/
    fp1 = fopen ("dictionnary.txt", "w") ; 
    fclose (fp1) ; 
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

    Element* clist = (Element*)malloc(sizeof(Element));
    clist = copylist(list, clist);
    printf ("\n---------------------- copy list ----------------------\n");
    display_list(clist);

    Htree = create_huffmanTree (&(list));
    printf ("\n-------------------------------- Huffman Tree --------------------------------\n");
    display_HufTree (Htree) ; 

    create_dico (Htree, New_binary, binaryLength = 0,clist ) ;
    printf ("\nDictionnary created \n") ;

    printf ("\n---------------------- list bin ----------------------\n");
    display_bin (clist);

    Encodage (clist);

    //Decodage (clist);

    printf ("\n-----------------Free HuffmanTree ----------------\n");
    freeTree (Htree) ; 
    free(binary);                   //Free the memory
    free_list(clist);
    return 0; 
}
