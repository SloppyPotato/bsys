#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

LinkedList* create_linked_list() {
    LinkedList* list = (LinkedList *) malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    return list;
}

void delete_linked_list(LinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, "Deleting list failed. List is NULL.\n");
        return;
    }
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void add_element(LinkedList* list, int value) {
    if (list == NULL) {
        fprintf(stderr, "list is NULL");
        return;
    }
Node* new_node = (Node *) malloc(sizeof(Node));
if (new_node == NULL) {
    fprintf(stderr, "malloc failed");
    return;
}
new_node->data = value;
new_node->next = list->head;
list->head = new_node;
list->size++;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <number of element>|n", argv[0]);
    }

    int number_of_elements = atoi(argv[1]);

    LinkedList* list = create_linked_list();
    if (list == NULL) {
        fprintf(stderr, "Creating list failed.\n");
        return 1;
    }

    for (int i = 0; i < number_of_elements; i++) {
        add_element(list, i);
        // printf("ll%d added\n", i);
    }

    delete_linked_list(list);

    return 0;
}

