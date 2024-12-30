#include <stdio.h>
#include <stdlib.h>

#define BATCH 10

struct space { 
    char *memory; 
    int len; 
}; 

struct node { 
    int p; 
    struct node *next; 
};

void initialize(struct space *mem){
    mem->memory = malloc( 1 * (BATCH+1) );
    mem->len = BATCH;


    for (int i = 0; i < BATCH; i++) {
        mem->memory[i] = 'F'; 
    }

    
    mem->memory[BATCH] = '\0';

    printf("memory=%s(%d)\n", mem->memory, mem->len);

}

void clear(struct space *mem) {
    
     if (mem->memory != NULL) {
        printf("memory=%s(%d)\n", mem->memory, mem->len);

        free(mem->memory);

        mem->memory = NULL;
    }
}

int scanMemory(struct space *mem, int size) {
    int p = -1; 
    int i = 0;   

    while (p < 0 && i < mem->len) {
        while (i < mem->len && mem->memory[i] != 'F') {
            i++;
        }

        if (i < mem->len) {  
            int t = 0; 

            while (t < size && (i + t) < mem->len && mem->memory[i + t] == 'F') {
                t++;
            }

            if (t == size) {  
                p = i; 
            } else {
                i = i + t; 
            }
        }
    }

    return p;
}


3. and the definition of allocator, a function that
• takes three inputs, a pointer to struct space, struct space *mem, an integer, size, and a
pointer to the head of the nodes list, struct node **head,
• calls scanMemory with arguments mem and size,
• sets an integer, p, to its return value, and
• if p is nonnegative, calls addNode with inputs head and p.


void addNode(struct node **head, int p) {

    struct node *newy = (struct node *)malloc(sizeof(struct node));
    
    newy->p = p;
    newy->next = NULL;

    if (*head == NULL) {
        *head = newy;
    } else {
      
        struct node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newy;
    }

}



int allocator( struct space *nem, int size , struct node **head){
    int p = scanMemory(nem, size);
    if (p >= 0){
        addNode(head, p);
    }

}

