#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>
#include "Structure.h"

/////////////////////////////// ETAPE 1 : Put a text in Binary /////////////////////////////// 

//Read each character, takes its decimal code and convert it to Binary.
void textToBinary(char *text, int textLength, char *Binary, int BinaryLength)
{
    char *octet = malloc(8);                            //Allocate the necessary memory on the heap for the ptr
    if(octet == NULL)
        exit(1);
    while(*text) //dereference the pointer
    {
        decimalToBinary(*text, octet);
        while(*octet)
            *Binary++ = *octet++;                       //same as *Binary = *Binary + 1 = *octet = *octet + 1
        //*Binary++ = ' '; this line is to separate each bit (8 octet) by a space for comprehension.
        ++text;
        octet -= 8;                                     //reset the pointer; same as octet = octet - 8
    }
    *Binary = '\0';
    Binary -= BinaryLength;
    free(octet);                                        //release the memory
}


void decimalToBinary(int decimal, char *octet)
{
	octet += 8;
	*octet = '\0';
	if(decimal == 0)                                    //Security
	{
		octet -= 8;
		octet = "00000000";
	}
	else
	{
		while(decimal > 0)
		{
			--octet;
			*octet = decimal % 2 + '0';
			decimal = decimal / 2;
		}
	}
    while(strlen(octet) < 8)
    {
        --octet;
        *octet = '0';
    }
}

void Length2files(int BinaryLength, int textLength){
    FILE *fp3 = NULL;                                   // variable, gestion de fichiers, secu  
    FILE *fp4 = NULL;                                   // Pareil 
//////////////////////////////////////////////////////////////
    fp3 = fopen("input.txt", "w+"); 
    if (fp3 == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp3, "%d", textLength);
    fclose(fp3);
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
    fp4 = fopen("output.txt", "w+");
    if (fp4 == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp4, "%d", BinaryLength);
    fclose(fp4);
//////////////////////////////////////////////////////////////
}


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
        printf("%c ", node ->letter) ; 
        free(node);
    }
}

/////////////////////////////// ETAPE 2 : create the list of Node(which is the letter) ///////////////////////////////

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
// WARNING Retirer free_letter dans le futur
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
        if (position == 1) {                                    // if yes then we do nothing and go to the next element 
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

            position = posMaximum (savepos);                    // Now we restart position and go again 
            j++ ;
        }                                                                  
    }
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

// Creation of the tree from a sorted list of node, return the last Node = Huffman tree// 
Node* create_huffmanTree (Element **list) {
    if ((*list) == NULL) {                              
        printf ("Your list is empty \n") ; 
        return NULL ; 
    }
    else {
        Element* temp ;                                         // Var that take list -> next 

        while ((*list)->next != NULL) {
            temp = (*list)->next ;
            Node* new_node = Thrid_Node ((*list) ->El_letter, temp-> El_letter) ; 
            (*list) ->El_letter = new_node ; 
            (*list) -> next = temp ->next ; 
            free (temp) ;                                       // free the Element but not the Node 
            sorted_list (list) ; 
            //display_list((*list));                            // To know what happen in the funtion 
        }

        Node* save = (*list) ->El_letter ;                      // to save the node in the Element 
        free (*list) ;                                          // free the last Element 
        return save ;                                           // return the Node in the last Element 
    }
}

/* Somme des occurences de chaque Node permettant de créer une troisième Node qu'on renvoie */
Node* Thrid_Node (Node* l1, Node* l2){                          // l2 >= l1 because right biger ("1"), left lower ("0") 
    if(l1 == NULL || l2 == NULL || l1->occ > l2->occ) {
        printf("Error in the given node \n") ; 
        return NULL; 
    }
    else {
        Node* thrid_n = (Node*)malloc(sizeof(Node)) ;
        thrid_n ->occ = l1->occ + l2->occ ; 
        thrid_n ->left = l1 ; 
        thrid_n ->right = l2 ; 

        return thrid_n ; 
    }
}

/////////////////////////////// ETAPE 3 ///////////////////////////////
// Ecrire une fonction qui affiche la list de lettre dans un fichier, Un dictionnaire //

/* function that display the hufman tree*/
void display_HufTree (Node* tree) {
    if (tree != NULL) {
        if (tree->left == NULL && tree->right == NULL) {
            printf ("letter : %c      Occ = %d \n", tree -> letter, tree ->occ ) ;
        }
        display_HufTree (tree->left) ; 
        display_HufTree (tree->right); 
    }
}

/* function that create a file dico with all the leaves */
void create_dico ( Node* tree, char* New_Binary, int cpt,Element* list) {
    Element* temp = list;
// Step 1 travel the tree
    if (tree->left != NULL)                         // Add 0 until we can go to the left
    {
        New_Binary[cpt] = '0';
        create_dico(tree->left, New_Binary,cpt + 1,list);
    }

    if (tree->right != NULL)                        // Add 1 until we can go to the right 
    {
        New_Binary[cpt] = '1';
        create_dico(tree->right, New_Binary, cpt + 1,list);
    }

// Step 2 if we have a leaf, we add the new_binary in the fresh dico
    if (tree->left==NULL && tree->right==NULL)
    {
        FILE *fichier = fopen("dictionnary.txt","a+");
        fprintf(fichier,"'%c' : ", tree->letter);
        char n='\n';

        while (tree->letter != temp->El_letter->letter){
            temp = temp->next;
        }

        for (int i = 0; i < cpt; ++i)               // Write in the file
        {
            if(fichier!=NULL) fprintf(fichier,"%c",New_Binary[i]);
        
            temp->El_letter->bin[i] = New_Binary[i];

        }





        fprintf(fichier,"%c",n);
        fclose(fichier);
    }
}


void display_bin (Element* list) { 
    if (list != NULL) {
        printf ("\nLetter : '%c'      Bin:", list->El_letter->letter);
        for (int i=0; list->El_letter->bin[i] != '\0' && (list->El_letter->bin[i] == '1' || list->El_letter->bin[i] == '0'); i++){
            
            printf("%c",list->El_letter->bin[i]);
        }
        display_bin (list->next); 
    }
}




/////////////////////////////// ETAPE 4 :Encodage & Décodage du fichier texte /////////////////////////////// 
/* this part is used to encode and decode the file text.txt */ 

int nlist(Element* list){
    int n =1;
    while(list->next != NULL){
    n+=1;
    list = list->next;
    }
    return n;
}

Element* copylist(Element* list, Element* clist){

    
    clist->El_letter = (Node*)malloc(sizeof(Node));

    clist->El_letter->letter = list->El_letter->letter;

    Element* temp = clist;
    Element* temp2 = list;
    int n = nlist(list);

    while (n > 1){


        temp->next = (Element*)malloc(sizeof(Element));

        temp = temp->next;
        temp2 = temp2->next;

        temp->El_letter = (Node*)malloc(sizeof(Node));

        temp->El_letter->letter = temp2->El_letter->letter;
        
        n = n-1;
        printf("%d",n);
    }
    printf("%d",n);
    temp->next = NULL;
    return clist;
}



void Encodage (Element* list) {
    Element* temp = list;
    FILE* input = fopen("Texte.txt","r");                   //importation of file for reading
    FILE* output = fopen("output.txt","w");                 //importation of file for writing

    char temp1;

    while((temp1 = fgetc(input)) != EOF){                   //fgetc permit to going through the file one character after one
        while (temp1 != temp->El_letter->letter){
            temp = temp->next;
        }
        for(int i = 0; temp->El_letter->bin[i] != '\0' && (temp->El_letter->bin[i] == '1' || temp->El_letter->bin[i] == '0') ; i++){    //taking the wall binary code without wrong characters.
            fprintf(output,"%c",temp->El_letter->bin[i]);
        }
        temp = list;
    }
    fclose(input);                                          //closing of the files
    fclose(output);
}

int size_board(char* bin){
    int n = 0;
    for (int i = 0; bin[i] != '\0'; i++){
        n += 1;
    }
    return n;
}

/*void Decodage (Element* list){
    Element* temp = list;
    FILE* input = fopen("output.txt","r");
    FILE* output = fopen("origin.txt","w");
    char temp1[100];
    int true = 1;
    for(int i = 0; (temp1[i] = fgetc(input)) != EOF; i++){
        temp1[i+1] = '\0';
        printf("1");
        while(temp != NULL){ 
            for(int e = 0; e != size_board(temp->El_letter->bin)-1; e++){
                if (temp->El_letter->bin[e] != temp1[e]){
                    true = 0;
                }
            }
            if (true == 1){
                fprintf(output,"%c",temp->El_letter->letter);
                temp = list;
                i = 0;
                temp1[0] ='\0'; 
            }
            true = 1;
        }        
        temp = list;
    }
    fclose(input);
    fclose(output);
}*/