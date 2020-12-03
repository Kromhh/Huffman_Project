#include <stdio.h> 
#include <stdlib.h>  
#include "Structure.h"

int main () {
    Node* Htree ; 

    printf  ("Hello\n\n") ; 

    Element* list = occ_text (); 
    display_list (list);
    printf  ("\n") ; 

    sorted_list (&(list)) ; 
    display_list (list) ; 


    Htree = create_huffmanTree (&(list)) ;
    display_tree (Htree); 

    printf ("\n-----------------Free HuffmanTree ----------------\n");
    freeTree (Htree) ; 


    return 0; 
}
