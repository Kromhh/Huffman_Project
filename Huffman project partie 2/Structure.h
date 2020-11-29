#ifndef Structure_h
#define Structure_h 


///////////////////////////////////////////////// NODE
typedef struct Node
{
    char letter ;
    int occ ; 
    struct Node* left ;
    struct Node* right;
}Node;

/* Changer */
Node* create_node (char letter) ;
void freeTree (Node* node) ;
void display_tree(Node* tree) ;

///////////////////////////////////////////////// ELEMENT 
typedef struct Element
{
    Node* El_letter ;
    struct Element*  next ; 
}Element;

/* Changer */ 
Element* create_El_N (Node* l) ; 
void display_list (Element* list) ;
Element* occ_text () ; 
void free_list (Element* list); 
int posMaximum(Element *L);  
void sorted_list (Element** list)  ;

/* Pas changer */ 


int lenght_list (Element* list) ;

/* Pas changer */
Node* SommListe(Element* L) ; // à tester 


#endif
