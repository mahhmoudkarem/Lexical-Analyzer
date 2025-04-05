#include <iostream>  // For input/output operations
#include <string>    // To handle strings
#include <cctype>    // To check character types (e.g., isalpha, isdigit)

using namespace std;

// Character classes
#define LETTER 0        // Character class for letters
#define DIGIT 1         // Character class for digits
#define UNKNOWN 99      // Character class for unknown characters (operators, etc.)
#define END_OF_FILE -1  // Character class for the end of file/input

// Token codes
#define INT_LIT 10      // Token code for integer literals
#define IDENT 11        // Token code for identifiers (e.g., variable names)
#define ASSIGN_OP 20    // Token code for assignment operator '='
#define ADD_OP 21       // Token code for addition operator '+'
#define SUB_OP 22       // Token code for subtraction operator '-'
#define MULT_OP 23      // Token code for multiplication operator '*'
#define DIV_OP 24       // Token code for division operator '/'
#define LEFT_PAREN 25   // Token code for left parenthesis '('
#define RIGHT_PAREN 26  // Token code for right parenthesis ')'

// Global variables
string input;   // String to hold the input text
size_t pos = 0;  // Position index to keep track of the current character in the input
char nextChar;   // Holds the current character being processed
int charClass;   // Holds the character class (LETTER, DIGIT, UNKNOWN, END_OF_FILE)
string lexeme;   // Holds the current lexeme (substring of the input)
int nextToken;   // Holds the token code for the current lexeme

// Function declarations
void getChar();      // Function to get the next character from input
void addChar();      // Function to add the current character to the lexeme
void getNonBlank();  // Function to skip over any whitespace characters
int lookup(char ch); // Function to lookup operators and return corresponding tokens
int lex();           // Main function to perform lexical analysis and identify tokens

// Main driver function
int main() {
    // Prompt the user for input and read a line of input into the 'input' string
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    getChar();  // Initialize by getting the first character from the input
    do {
        lex();  // Process the input and identify tokens
    } while (nextToken != END_OF_FILE);  // Continue until we reach the end of the input

    return 0;  // Return 0 to indicate successful execution
}

// Function to get the next character from the input and classify it
void getChar() {
    // Check if there are more characters in the input
    if (pos < input.length()) {
        // Get the next character from the input
        nextChar = input[pos++];

        // Classify the character as a letter, digit, or unknown
        if (isalpha(nextChar)) {
            charClass = LETTER;  // Letter characters
        }
        else if (isdigit(nextChar)) {
            charClass = DIGIT;   // Digit characters
        }
        else {
            charClass = UNKNOWN; // Non-alphanumeric characters (operators, etc.)
        }
    }
    else {
        charClass = END_OF_FILE; // Set to END_OF_FILE when we reach the end of input
    }
}

// Function to add the current character to the lexeme
void addChar() {
    lexeme += nextChar;  // Append the current character to the lexeme string
}

// Function to skip over whitespace characters (spaces, tabs, etc.)
void getNonBlank() {
    // Continue calling getChar until we find a non-whitespace character
    while (isspace(nextChar)) {
        getChar();
    }
}

// Function to lookup operators and parentheses, returning the appropriate token
int lookup(char ch) {
    // Match each operator and return the corresponding token code
    switch (ch) {
    case '(': addChar(); return LEFT_PAREN;  // Left parenthesis
    case ')': addChar(); return RIGHT_PAREN; // Right parenthesis
    case '+': addChar(); return ADD_OP;     // Addition operator
    case '-': addChar(); return SUB_OP;     // Subtraction operator
    case '*': addChar(); return MULT_OP;    // Multiplication operator
    case '/':addChar(); return DIV_OP;     // Division operator
    case '=': addChar(); return ASSIGN_OP;  // Assignment operator '='
    default:  addChar(); return END_OF_FILE; // Unknown character or end of input
    }
}

// Function for lexical analysis to identify tokens
int lex() {
    lexeme = "";  // Reset lexeme before processing each token
    getNonBlank();  // Skip any whitespace characters

    switch (charClass) {
    case LETTER:
        // If the character is a letter, start forming an identifier
        addChar();
        getChar();
        // Continue adding characters to the lexeme as long as they are letters or digits
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;  // Set the token to IDENT (identifier)
        break;

    case DIGIT:
        // If the character is a digit, start forming an integer literal
        addChar();
        getChar();
        // Continue adding digits to the lexeme
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;  // Set the token to INT_LIT (integer literal)
        break;

    case UNKNOWN:
        // If the character is an unknown operator or symbol, lookup its token
        nextToken = lookup(nextChar);
        getChar();
        break;

    case END_OF_FILE:
        // If we've reached the end of input, set the token to END_OF_FILE
        lexeme = "EOF";  // Set lexeme to "EOF"
        nextToken = END_OF_FILE;  // Set the token to END_OF_FILE
        break;
    }

    // Print the token and lexeme
    cout << "Next token is: " << nextToken << ", Next lexeme is: " << lexeme << endl;

    return nextToken;  // Return the identified token
}