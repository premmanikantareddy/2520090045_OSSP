#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 2
#define MAX_INPUT 100

// Linked list node
struct Node {
    char command[MAX_INPUT];
    struct Node *next;
};

// Add command to linked list
void addCommand(struct Node **head, char command[]) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    strncpy(newNode->command, command, MAX_INPUT - 1);
    newNode->command[MAX_INPUT - 1] = '\0';

    newNode->next = *head;
 *head = newNode;
}

// Display command history
void displayHistory(struct Node *head) {
    printf("\n--- Command History ---\n");

    int count = 1;

    while (head != NULL) {
        printf("%d. %s\n", count, head->command);
        head = head->next;
        count++;
    }
}

// Free linked list memory
void freeHistory(struct Node *head) {
    struct Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}