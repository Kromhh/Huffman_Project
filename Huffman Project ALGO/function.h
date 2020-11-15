#ifndef function_h
#define function_h

typedef struct Char{
    int occ;
    char data;
    struct Char *next;
}Char;

void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);
void Length2files(int binaryLength, int textLength);

#endif // function_h
