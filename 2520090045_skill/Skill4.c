#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Token structure
struct Token {
    char type[20];
    char value[20];
};

struct Token tokens[MAX];
int tokenCount = 0;

// Function to add a token
void addToken(char type[], char value[]) {
    strcpy(tokens[tokenCount].type, type);
    strcpy(tokens[tokenCount].value, value);
    tokenCount++;
}

// Tokenization
void tokenize(char input[]) {
    int i = 0;
    char temp[20];
while (input[i] != '\0') {

        // Ignore whitespace
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Identifier
        if (isalpha(input[i])) {
            int j = 0;

            while (isalnum(input[i])) {
                temp[j++] = input[i++];
            }

            temp[j] = '\0';
            addToken("IDENTIFIER", temp);
        }

        // Number
        else if (isdigit(input[i])) {
            int j = 0;

            while (isdigit(input[i])) {
                temp[j++] = input[i++];
temp[j] = '\0';
            addToken("NUMBER", temp);
        }

        // Operators
        else if (input[i] == '+' || input[i] == '-' ||
                 input[i] == '*' || input[i] == '/' ||
                 input[i] == '=') {

            temp[0] = input[i];
            temp[1] = '\0';

            addToken("OPERATOR", temp);
            i++;
        }

        // Delimiters
        else if (input[i] == ';' || input[i] == '(' ||
                 input[i] == ')') {

            temp[0] = input[i];
            temp[1] = '\0';

            addToken("DELIMITER", temp);
            i++;
}

        // Unknown character
        else {
            printf("Lexical Error: Unknown character '%c'\n", input[i]);
            i++;
        }
    }
}

// Simple parser
void parse() {

    printf("\n--- Parsing ---\n");

    if (tokenCount == 0) {
        printf("Error: Empty command\n");
        return;
    }

    // Expected structure:
    // IDENTIFIER = IDENTIFIER/NUMBER ;

    if (tokenCount < 3) {
        printf("Syntax Error: Incomplete statement\n");
}

    if (strcmp(tokens[0].type, "IDENTIFIER") != 0) {
        printf("Syntax Error: Expected identifier\n");
        return;
    }

    if (strcmp(tokens[1].value, "=") != 0) {
        printf("Syntax Error: Expected '='\n");
        return;
    }

    if (strcmp(tokens[2].type, "IDENTIFIER") != 0 &&
        strcmp(tokens[2].type, "NUMBER") != 0) {
        printf("Syntax Error: Expected identifier or number\n");
        return;
    }

    printf("Syntax is valid.\n");

    // Parse tree
    printf("\n--- Parse Tree ---\n");
    printf("Assignment\n");
printf("\nExecution Structure:\n");
    printf("Assign %s = %s\n",
           tokens[0].value, tokens[2].value);
}

int main() {

    char input[200];

    printf("Enter a statement: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline
    input[strcspn(input, "\n")] = '\0';

    // Tokenize
    tokenize(input);

    // Display tokens
    printf("\n--- Tokens ---\n");

    for (int i = 0; i < tokenCount; i++) {
        printf("%d. %-12s : %s\n",
               i + 1,
               tokens[i].type,
               tokens[i].value);