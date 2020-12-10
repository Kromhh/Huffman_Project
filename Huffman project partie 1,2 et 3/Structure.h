#ifndef Structure_h
#define Structure_h 

///////////////////////////////////////////////// BINARY

void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);
void Length2files(int binaryLength, int textLength);

///////////////////////////////////////////////// NODE
typedef struct Node
{
    char letter ;
    int occ ;
    char bin[100]; 
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
int lenght_list (Element* list) ;

///////////////////////////////////////////////// Creation Huffman tree and dico 
Node* create_huffmanTree (Element **list) ;
Node* Thrid_Node (Node* l1, Node* l2) ;      
void display_HufTree (Node* tree) ;
void create_dico ( Node* tree, char* Binary, int cpt,Element* list) ; 

//////////////////////////////////////////////// Encodage&decodage 
Element* copylist(Element* list, Element* clist);
void display_bin (Element* list);
void Encodage (Element* list);
//void Decodage (Element* list);
#endif
