#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int value;
    struct node* next;
} node;


int main() {

    printf("Testing");
    // create dummy item
    node* dummy = malloc(sizeof(node));
    dummy->value = -1;
    dummy->next = NULL;
    node* current_node = dummy;

    // create the 10 other nodes
    for(int i=0; i<10; i ++){
        node* new_node = malloc(sizeof(node));
        new_node->value = i;
        new_node->next = NULL;
        current_node->next = new_node;
        current_node = new_node;
    }

    // print the values
    current_node = dummy;
    while(current_node != NULL){
        printf("%d\n", current_node->value);
        current_node = current_node->next;
    }

    // free memory
    current_node = dummy;
    while(current_node != NULL){
        node* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    
    return 0;

}
