#include <stdio.h> 
#include <stdlib.h>  
#include "Structure.h"


/////////////////////////////// ETAPE 2 : create the list of letter /////////////////////////////// 
// Part where I create the Node 

// create a Node from an El //
Node* create_node (char letter) {

    Node* new_node = (Node*) malloc (sizeof(Node)) ;
    new_node ->letter = letter;
    new_node->occ = 1 ; 
    new_node ->left = NULL ;
    new_node ->right = NULL ; 

    return new_node; 
}

/* display the letter and the number of occ of each node in a tree in a pre-order*/ 
void display_tree(Node* tree) {
    if (tree != NULL) {
        printf ("letter : %c      Occ = %d \n", tree -> letter, tree ->occ ) ;
        display_tree (tree ->left) ; 
        display_tree (tree->right) ; 
    }
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

/////////////////////////////// ETAPE 2 : create the list of letter ///////////////////////////////

// Creation of an Element by a Node //

Element* create_El_N (Node* l) { 
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
        Node* l = create_node (templ);                 
        Element* Liste_L = create_El_N (l);

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
            else                                                                    // if no : add a new element at the start of the list
            {
                Node* l = create_node (templ);                 
                Element* new_letter = create_El_N (l);         
                new_letter ->next = Liste_L ; 
                Liste_L = new_letter ; 
            }
        }

        fclose (fp1) ;                                                              // Close the file
        return Liste_L ;                                                            // Return the list
    }
}


// Free a list of Element //
void free_list (Element* el) {
    if (el != NULL) {
        free_list (el -> next) ;
        printf ("'%c' ", el ->El_letter->letter); 
// Retirer free_letter dans le futur
        free(el->El_letter) ;                                                       // Free the Node
        free(el);                                                                   // Free the Element 
    }
}

// Function that find the bigest occ and return its position // 
int posMaximum(Element *L){
    Element* temp = L; 
    int maxOcc = 0;                                                                 // maxOcc = 0 because we have at least 1 occ 
    int i = 1, posOcc;                                                              // i = a counter for each turn 

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

// Setp 2 : go to the position of the Element with Max Occ //
            if (position == 1) {
                savepos = savepos->next ; 
            } 

            for (int i =1; i < position-1+j; i++) {
                beforetemp = beforetemp ->next ;
           }
            temp = beforetemp ->next; 

// setp 3 : Put it at the start of the list //   
            beforetemp ->next = temp ->next ; 
            temp ->next = *list ;
            *list = temp ;

            position = posMaximum (savepos);                    // Now we restart position 
            j++ ;
        }                                                                  
    }
    printf ("\n---------------------- list sorted ----------------------\n");
}

/* return the lenght of a list or 0 when it's NULL */           // Ne sert pas pour le moment 
int lenght_list (Element* list) {
    if (list == NULL) {
        return 0 ; 
    }
    else
    {
        return 1 + lenght_list (list ->next) ;
    }
}

/////////////////////////////// ETAPE 2 : creation arbre ///////////////////////////////
/* this part is the creation of the Huffman tree */ 





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
