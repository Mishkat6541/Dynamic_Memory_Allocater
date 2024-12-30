#include <stdio.h>
#include <stdlib.h>

#define BATCH 10

struct space { 
    char memory; 
    int len; 
}; 

struct node { 
    int p; 
    struct nodenext; 
};

void initialize(struct space mem){
    mem->memory = malloc( 1 (BATCH+1) );
    mem->len = BATCH;


    for (int i = 0; i < BATCH; i++) {
        mem->memory[i] = 'FREE'; 
    }

    free(mem->memory);
    mem->memory[BATCH] = '\0';

    printf("memory=%s(%d)\n", mem->memory, mem->len);
}

void clear(struct space *mem) {
    
    printf("memory=%s(%d)\n", mem->memory, mem->len);

    
    free(mem->memory);
    mem->memory = NULL;  
}