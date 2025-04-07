#include<iostream>//for input,output operations
#include <fstream>//for file
#include<cctype>//for character classification
#include<string>//for string class
using namespace std; //to use std for all 
// this  necessary c++ libraries for the code 
#define LETTER 0 //for alpha charachters
#define DIGIT 1 //for numeric digites 
#define UNKNOWN 99 //for unkown char
#define END_OF_FILE -1 //end of the file
#define INT_LIT 10 // integer token
#define IDENT 11//identfier for token 
#define ASSIGN_OP 20//assignment operator (equal,=)
#define ADD_OP 21 //addition operator (+)
#define SUP_OP 22//subtraction operator (-)
#define MULT_OP 23 //multiplication operator(*)
#define DIV_OP 24//division operator(/)
#define LEFT_PAREN 25//left parenthesis ( ( )
#define RIGHT_PAREN 26//right parenthesis ( ) )
int charrClass; //stores the class of the charachter
string lexeme;//stores the next of token
char nextChar;//the next char to process
int nextToken;//the tupe of the next token
ifstream in_fp;//input file stream
void addchar() {
	lexeme += nextChar;//appends current char to lexeme
}
void getChar() {
    if (in_fp.get(nextChar)) { // Reads next character from file
        if (isalpha(nextChar))
            charrClass = LETTER;
        else if (isdigit(nextChar))
            charrClass = DIGIT;
        else
            charrClass= UNKNOWN;
    }
    else {
        charrClass = END_OF_FILE;
    }
}
void getNonBlank() {
    while (isspace(nextChar)) // Skips whitespace
        getChar();
}
int lookup(char ch) {
    switch (ch) {
        // Cases for each operator/parenthesis
    default:
        addchar();
        nextToken = END_OF_FILE;
    }
    return nextToken;
}
int lex() {
    lexeme = ""; // Reset lexeme
    getNonBlank(); // Skip whitespace

    switch (charrClass) {
    case LETTER: // Handle identifiers
        // Read letters/digits until non-alphanumeric
        nextToken = IDENT;
        break;

    case DIGIT: // Handle numbers
        // Read digits until non-digit
        nextToken = INT_LIT;
        break;

    case UNKNOWN: // Handle operators
        lookup(nextChar);
        getChar();
        break;

    case END_OF_FILE: // Handle EOF
        nextToken = END_OF_FILE;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken
        << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}
int main() {
    in_fp.open("front.in"); // Open input file

    if (!in_fp) { // Check if file opened successfully
        cerr << "ERROR - cannot open front.in" << endl;
        return 1;
    }

    getChar(); // Get first character

    do { // Process tokens until EOF
        lex();
    } while (nextToken != END_OF_FILE);

    in_fp.close(); // Close file
    return 0;
}
