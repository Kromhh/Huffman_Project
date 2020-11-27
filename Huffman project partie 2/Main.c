#include <stdio.h> 
#include <stdlib.h>  
#include "Structure.h"

int main () {
    
    printf  ("Hello\n\n") ; 

    Element* list = occ_text (); 
    display_list (list);
    printf  ("\n") ; 

    sorted_list (&(list)) ; 
    display_list (list) ; 

    printf ("\n-----------------Free list and letter-----------------\n");
    free_list_2 (&list);   
    
    printf  ("\n") ; 
    display_list (list) ; 
    
    return 0; 
}
