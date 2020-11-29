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

    printf ("\n-----------------Free list and Node----------------\n");
    free_list (list);   
    
    
    return 0; 
}
