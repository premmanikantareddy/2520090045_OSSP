#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_input(char *input) {
    char token[200];
    int i = 0, j = 0;

    while (input[i] != '\0') {

        /* Skip spaces */
        while (input[i] == ' ')
            i++;

        if (input[i] == '\0')
            break;

        j = 0;

        /* Single quotes */
        if (input[i] == '\'') {
            i++;

            while (input[i] != '\'' && input[i] != '\0') {
                token[j++] = input[i++];
            }

            if (input[i] == '\'')
                i++;

            token[j] = '\0';

            printf("Single Quoted Token: %s\n", token);
        }

        /* Double quotes */
        else if (input[i] == '"') {
            i++;

            while (input[i] != '"' && input[i] != '\0') {

                /* Variable expansion */
                if (input[i] == '$') {
                    char variable[100];
                    int k = 0;

                    i++;

                    while ((input[i] >= 'A' && input[i] <= 'Z') ||
                           (input[i] >= 'a' && input[i] <= 'z') ||
                           (input[i] >= '0' && input[i] <= '9') ||
                           input[i] == '_') {

                        variable[k++] = input[i++];
                    }

                    variable[k] = '\0';

                    char *value = getenv(variable);

                    if (value != NULL) {
                        for (int x = 0; value[x] != '\0'; x++)
                            token[j++] = value[x];
                    }
                }
                else {
                    token[j++] = input[i++];
                }
            }

            if (input[i] == '"')
                i++;

            token[j] = '\0';

            printf("Double Quoted Token: %s\n", token);
        }

        /* Normal token */
        else {
            while (input[i] != ' ' &&
                   input[i] != '\'' &&
                   input[i] != '"' &&
                   input[i] != '\0') {

                token[j++] = input[i++];
            }

            token[j] = '\0';

            printf("Normal Token: %s\n", token);
        }
    }
}

int main() {
    char input[500];

    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    printf("\nParsing Result:\n");
    parse_input(input);

    return 0;
}