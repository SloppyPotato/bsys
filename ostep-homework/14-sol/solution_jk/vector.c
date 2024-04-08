#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Vector;

Vector* create_vector() {
    Vector *vec = (Vector *) malloc(sizeof(Vector));
    if (vec == NULL) {
        return NULL;
    }
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    return vec;
}

void delete_vector(Vector *vec) {
    if(vec == NULL) {
        fprintf(stderr, "Vector is NULL");
    }
    free(vec->data);
    free(vec);
}

void add_element(Vector *vec, int value) {
    if (vec == NULL) {
        fprintf(stderr, "Vector is NULL");
    }
    if (vec->size >= vec->capacity) {
        size_t new_capacity = (vec->capacity == 0) ? 1 : 2 * vec->capacity;
        int *new_data = (int *) realloc(vec->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return; 
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size++] = value;
}
 

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <number of element>\n", argv[0]);
        return 1;
    }

    int number_of_vectors = atoi(argv[0]);

    Vector *vec = create_vector();
    if (vec == NULL) {
        fprintf(stderr, "Failed to create Vector \n");
        return 1;
    }

    for (int i = 0; i < number_of_vectors; i++) {
        add_element(vec, i);
        // printf("v%d created\n", i);
    }

    // for (int i = 0; i < vec->size; i++) {
    //     printf("%d\n", vec->data[i]);
    // }
    
    delete_vector(vec);

    return 0;
}