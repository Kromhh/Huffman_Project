#include <stdio.h> 
#include <stdlib.h>  
#include "Structure.h"

/////////////////////////////// ETAPE 2 : Creation of Letter ///////////////////////////////
/* j'ai eu la fois de tout changer adulez moi */

Letter* create_letter (char letter) {          // create a Letter from an Element

    Letter* new_l = (Letter*)malloc (sizeof(Letter)) ; 
    new_l ->letter = letter ;
    new_l ->occ = 1 ; 

    /*
    new_l ->bin = NULL ;                        // to be done
    new_l ->new_bin = NULL ;
    */

    return new_l ; 
}

void display_letter (Letter* l) {               // to display the letter 
    printf ("Letter = %c \n",l->letter)  ;
    printf ("Occ = %d \n",l->occ)        ;
    printf ("Binary = %c \n",l->bin)     ;
    printf ("New_binary = %c \n",l->new_bin) ;
}

/////////////////////////////// ETAPE 2 : create the list of letter ///////////////////////////////

// Creation of an Element by a letter //
Element* create_El (Letter* l) { 
    Element* new_El = (Element*) malloc (sizeof (Element));
    new_El ->El_letter = l ;  
    new_El ->next = NULL ; 
    
    return new_El; 
}

// Display a list of Element //
void display_list (Element* list) { 
    if (list != NULL) {
        printf ("Letter : '%c'      Occ : %d\n", list->El_letter->letter, list ->El_letter->occ);
        display_list (list->next); 
    }
}

// Find the number of occ in a file.txt and return the list of all used characters // 
Element* occ_text () { 
    // Part 1 : Open the file
    FILE* fp1 = fopen ("Texte.txt","r");                                   // Warning you need to change the file.txt to match with your
    if (fp1 == NULL){                                                      // Security
        printf("Error opening file\n");
        exit(1);
    }
    else {
    // Part 2 : Create the 1st Element with the 1st letter of the file
        char templ = fgetc (fp1) ; 
        Letter* l = create_letter (templ);                 
        Element* Liste_L = create_El (l);

    // Part 3 : Do the same with all the characters in the file
        while ((templ = fgetc (fp1)) != EOF)
        {
            Element* temp_1 = Liste_L ; 
            while ( temp_1->El_letter->letter != templ  && temp_1->next != NULL) {  // check if the letter already exist in the list
                temp_1 = temp_1 -> next;
            }
            if (templ == temp_1->El_letter->letter) {                               // if yes : add +1 at the Element -> occ 
                temp_1 -> El_letter -> occ++ ; 
            }
            else                                                        // if no : add a new element at the start of the list
            {
                Letter* l = create_letter (templ);                 
                Element* new_letter = create_El (l);         
                new_letter ->next = Liste_L ; 
                Liste_L = new_letter ; 
            }
        }

        fclose (fp1) ;                                                  // Close the file
        return Liste_L ;                                                // Return the list
    }
}

// Free a list of Element //
void free_list (Element** el) {
    if (el != NULL) {
        free_list (&(*el) -> next) ;
        printf ("'%c' ", (*el) ->El_letter->letter); 
// Retirer free_letter dans le futur
        free((*el)->El_letter) ;                                           // Free Letter 
        free((*el));                                                       // Free Element 
    }
}

void free_list_2 (Element **L){
    while(*L != NULL) {
        Element* temp = *L;
        *L = (*L)->next;
        free(temp); 
    }
}

// Function that find the bigest occ and return its position // 
int posMaximum(Element *L){
    Element* temp = L; 
    int maxOcc = 0;                                                         // maxOcc = 0 because we have at list 1 occ 
    int i = 1, posOcc;

    if (L==NULL){
        return -1;
    }
    else{
        while (temp != NULL){
            if (maxOcc < temp->El_letter->occ){
                maxOcc = temp->El_letter->occ;
                posOcc = i;
            }
        i++;
        temp = temp->next;      
        }   
    } 
    return posOcc;                                                        // +1 because we do not reach i++ when incrementing posOcc
}

// Ecrire une fonction qui trie une list par nombre d'occ, décroissant // 
// essai 1 
/*ATTENTION si le premier caractère est le plus grand, il reste au début. 
à corriger dans sorted_list et possMaximum, on ne check pas le premier caractère */

void sorted_list (Element** list) {
    Element* savepos = *list;                                               // know where we are, move one by one 
    Element* temp;                                                          // El to move
    Element* beforetemp;                                                    // El before temp 
    int position = posMaximum (savepos); 
    int j = 0 ;                                                             // Number of El before savepos

    /*printf("Position = %d \n", position); */
    if (list == NULL) {
        printf("Your list is empty \n"); 
    }
    else {  
// setp 1 : Check if the biggest position is in the 1st position //  
        if (position == 1) {
            savepos = savepos->next ;
            j++;
            position = posMaximum (savepos); 
        } 
        while (position > 0) {                                  // -1 means the list is empty 
            beforetemp = *list ; 

// Setp 2 : go to the position of the Element //
            if (position == 1) {
                savepos = savepos->next ; 
            } 

            for (int i =1; i < position-1+j; i++) {
                beforetemp = beforetemp ->next ;
           }
            temp = beforetemp ->next; 

// setp 3 : put it at the start of the list //   
            beforetemp ->next = temp ->next ; 
            temp ->next = *list ;
            *list = temp ;

            position = posMaximum (savepos); 
            j++ ;
        }                                                                   // Move the El at the start of the list 
    }
    printf ("\n---------------------- list sorted ----------------------\n");
}

/* return the lenght of a list or 0 when it's NULL */ 
int lenght_list (Element* list) {
    if (list == NULL) {
        return 0 ; 
    }
    else
    {
        return 1 + lenght_list (list ->next) ;
    }
}

/////////////////////////////// ETAPE 2 : creation Queue ///////////////////////////////
/* this part is the creation of a Queue containing all the node for the tree */

// Create an empty Queue // 
Queue* create_Queue () {
    Queue* q = (Queue*)malloc(sizeof(Queue)) ; 
    q->nletter = NULL ; 
    q->next = NULL ; 

    return q; 
}

// Say if the Queue is empty // 
int is_empty_Q(Queue* q){
  if (q->next == NULL && q->nletter == NULL){
    return 1;                                                               // 1 = is empty
  }
  else {
      return 0;                                                             // 0 = is not empty 
  }
}

// il faudra faire une fonction pour remplir Q de tous les El et free les El après // 
Queue* fill_Queue_list (Element* list) {
    if (list == NULL) {
        return NULL; 
    }
    else {
        Queue* q = create_Queue () ;
        
        while (list != NULL) {
        pushQ (&q, list); 
        list =list->next ;
        printf ("q = %c", q->nletter->data->letter) ;
        }
        return q ;
    }
}

// Function that see what is in the Queue // 
void peek (Queue* q) {
    if (is_empty_Q(q) == 1) {
        printf ("NULL \n");
    }
    else {
        printf ("%c ", q->nletter->data->letter) ;
        peek (q->next);
    }
}


// Add an Element at the end of q // 
void pushQ (Queue** q, Element* el) {
    if (el != NULL) {
        if (is_empty_Q (*q) == 1) {
            Node* tree= create_node_el (el);
            (*q)->nletter = tree;
        }
        else { 
            Queue* temp = (*q) ->next;
            while (temp ->next != NULL) {                                   // put temp = node at the end
                temp = temp->next;
            }
            Node* tree = create_node_el(el);                                // add el at the end of the queue
            Queue* new_q = create_Queue () ; 
            new_q->nletter = tree ; 
            temp -> next = new_q ; 
        }
    }
}

// A retirer //
void free_Queue (Queue* q) {
    if (q != NULL) {
        free_Queue (q -> next) ;
        printf ("'%c' ", q ->nletter->data->letter); 
// Retirer free_letter dans le futur
        free (q->nletter) ;                                             // Free the node
        free(q);                                                        // Free the Queue
    }
}

// Pop the 1st Node of the Queue // 
void popQ_N (Queue** q){
    if(is_empty_Q(*q) == 1 ){
        printf ("NULL") ;
     }
     else{
        Queue* temp = (*q);
        (*q) = (*q)->next;

/* can be removed */ 
        printf("Pop = %c", temp->nletter->data->letter) ;                   // We display the letter that we pop -> the first Node
        free (temp->nletter) ;                                              // We free the Node affiliate with the Queue
        free(temp);                                                         // We free the Queue  
    }
}


/*
//Initialisation de la file- utile
File* creer_File(){
    File* f = malloc(sizeof(File));
    f->premier = NULL;
    return f;
}

//Est vide- utile
int est_Vide(File* f){
  if (f->premier == NULL)
    return 1;// on a rien dans la file
  else
    return 0; // on a quelquechose dans la file
}


Maillon* retirer(File** f){
  if ((*f)->premier == NULL){
    return creationCellule('+'); //permettra de désigner la fin de liste
  }
  else{
    Maillon *temp = (*f)->premier;
    free((*f)->premier);
    (*f)->premier = temp->suivant;    
    return temp;
  }  
}

//Affiche File - utile
void afficher_File(File* f){ 
  Maillon* temp = retirer(&f);
  while (est_Vide(f) == 0){ 
    printf("%c - %d",temp->info, temp->occ);
    temp = retirer(&f); //rappel de la fonction retirer()pour changer d'item de ma liste
  }
}
*/

/////////////////////////////// ETAPE 2 : creation arbre ///////////////////////////////
/* this part is the creation of the Huffman tree */ 

// create a Node from an El //
Node* create_node_el (Element* el) {
    if (el == NULL ) {
        return NULL; 
    }
    Node* new_node = (Node*) malloc (sizeof(Node)) ;
    new_node ->data = el->El_letter;
    new_node ->left = NULL ;
    new_node ->right = NULL ; 

    return new_node; 
}

/* create a Node from a value */ 
Node* create_node_val(int val) {
    Node* new_node = (Node*)malloc (sizeof (Node)) ;
    new_node ->occ = val ; 
    new_node ->left = NULL ;
    new_node ->right = NULL ; 

    return new_node ; 
}

/* free all the tree */ 
void freeTree (Node* node)
{
    if (node != NULL) {
        freeTree(node->left);  
        freeTree(node->right);
        free(node);
    }
}

/* display the letter and the number of occ of each node in a tree in a pre-order*/ 
void display_tree(Node* tree) {
    if (tree != NULL) {
        printf ("letter : %c      Occ = %d \n", tree ->data->letter, tree ->occ ) ;
        display_tree (tree ->left) ; 
        display_tree (tree->right) ; 
    }
}

/* Create the node 2 by 2 and sum them to create a 3 node with jsut an occ */
/* Idée 1 : un tree à partir d'une liste d'Element then sup the list itself, l'idée c'est d'utiliser un stack de 2 elements à chaque fois */  

/*
Node* create_tree_huffman (Element **list) {
    if ((*list) == NULL) {
        printf ("Your list is empty \n") ; 
        return NULL ; 
    }
    else
    {
        if ((*list)->next != NULL) {
            Element* temp = (*list)->next ;
            Element* save = temp ; 
            Node* new_node = 1; // attention pas fini 
        }
    }
    // attention besoin de free() les elements utilisés pour faire la node. 
}
*/

/* Function that create the 3rt Node (head node) frome 2 Nodes */ 
// toujours : el1 < el2 //
Node* create_3rdNode (Element* el1, Element* el2) {
    if (el1 == NULL || el2 == NULL) {
        return NULL ;
    }
    Node* new_n1 = create_node_el (el1) ; 
    Node* new_n2 = create_node_el (el2) ; 

    Node* head_node = (Node*)malloc(sizeof(Node)) ;
    head_node ->data = NULL; 
    head_node ->occ = new_n1 ->occ + new_n2 ->occ ;
    head_node ->left = new_n1  ;
    head_node ->right = new_n2 ; 

    return head_node ;
}




/*Somme des occurences de chaque caractère permettant de créer les Nodes ensuite*/
/*
Node* SommListe(Element* L){
  Element* temp, *p;
  Node* Node;
  int somme = 0;
    
  if(L != NULL){                                                                //tant qu'on est pas en fin de liste
    temp = L;
    p = temp->next;

    while (temp != NULL){
      somme = somme + (temp->occ);
      printf("Somme_de_2_Elements = %d\n", somme);                              //test pour savoir si la somme a bien été faite sur 2 Elements
      Node = create_node_val(somme);  
      printf("ok.\n");                                                          //test verif
      temp->occ = p->occ;                                                       //avancement dans la liste               
      temp = temp->next; 
    } 
    printf("ok1.\n");                                                           //test verif
  }
  printf("ok2.\n");                                                             //test verif
  return Node;
}
*/

// Ecrire les fonctions pour les arbres // 

/////////////////////////////// ETAPE 3 ///////////////////////////////
// Ecrire une fonction qui affiche la list de lettre dans un fichier, Un dictionnaire //