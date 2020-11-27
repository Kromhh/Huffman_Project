#ifndef Structure_h
#define Structure_h 

/* on aurait du faire une structure Letter avec tout de Element sauf le next 
et apres un Element ave Letter en data et le next */ 

//////////////////////////////////////////////// LETTER 

typedef struct Letter 
{
    char letter ; 
    int occ ; 
    char bin ; 
    char new_bin ; 
}Letter;

Letter* create_letter (char letter);
void display_letter (Letter* l) ;
void free_letter (Letter* l) ;

///////////////////////////////////////////////// ELEMENT 
typedef struct Element
{
    Letter* El_letter ;
    struct Element*  next ; 
}Element;


Element* create_El (Letter* l) ; 

void free_list (Element** list);
Element* occ_text (); 
void display_list (Element* list) ;

int lenght_list (Element* list) ;
void sorted_list (Element** list)  ;

int posMaximum(Element *L); 

void free_list_2 (Element **L) ;
///////////////////////////////////////////////// NODE

typedef struct Node
{
    Letter* data ;
    int occ ; 
    struct Node* left ;
    struct Node* right;
}Node;

Node* create_node_val(int val) ;
Node* create_node_el (Element* letter);
void display_tree(Node* tree) ;
void freeTree (Node* node) ;

Node* SommListe(Element* L) ; // à tester 

#endif

///////////////////////////////////////////////// STACK 

typedef struct Queue
{
    Node* nletter ; 
    struct Queue* next ; 
}Queue;

Queue* create_Queue () ;
int is_empty_Q(Queue* q) ;
void pushQ (Queue** q, Element* el) ; // A tester 
void popQ_N (Queue** q) ; // A tester 
void peek (Queue* q) ;
Queue* fill_Queue_list (Element* list) ;

void free_Queue (Queue* q) ; // A retirer 