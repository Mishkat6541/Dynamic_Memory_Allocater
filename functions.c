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
    return p
}


void removeNode(struct node **head, int p) {
    if (*head == NULL) {
        return;
    }

    struct node *current = *head;
    struct node *prev = NULL;

    if (current != NULL && current->p == p) {
        *head = current->next;  
        free(current);
        return;
    }

    while (current != NULL && current->p != p) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return; 
    }

    prev->next = current->next;
    free(current); 
}


void deallocator(struct space *mem, int p, struct node **head) {
    if (mem == NULL || head == NULL) {
        return;  
    }

    for (int i = p; i < mem->len && mem->memory[i] != '\0'; i++) {
        mem->memory[i] = 'F'; 
    }

    printf("memory=%s(%d)\n", mem->memory, mem->len);

    removeNode(head, p);
}



void addMemory(struct space *mem) {

    char *new = (char *)malloc((mem->len + BATCH + 1) * sizeof(char));

    for (int i = 0; i < mem->len; i++) {
        new[i] = mem->memory[i];
    }

    for (int i = mem->len; i < mem->len + BATCH; i++) {
        new[i] = 'F';
    }

    new[mem->len + BATCH] = '\0';

    free(mem->memory);

    mem->memory = new;
    mem->len = mem->len + BATCH;

    printf("memory=%s(%d)\n", mem->memory, mem->len);
}


int allocatorNew(struct space *mem, int size, struct node **head) {
    int p;
    while ((p = scanMemory(mem, size)) == -1) {
        addMemory(mem); 
    }

    if (p >= 0) {
        addNode(head, p);
    }

    return p; 
}
