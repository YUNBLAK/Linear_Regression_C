// CSV Loader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "csvlinkedlist.h"

CSV_LOAD csv(){
    
    struct stat sb;
    int val = 0;
    struct NODE *head = malloc(sizeof(struct NODE));
    struct NODE *temp = head;
    CSV_LOAD dataset;

    char *name = "regression.txt";
    char z01[100];
    char z02[100];
    
    FILE *in_file = fopen(name, "r");
    
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    if (stat(name, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    
    char *file_contents = malloc(sb.st_size);
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        if(val == 0){
            //
        }
        else{
            struct NODE *node1 = malloc(sizeof(struct NODE));
            if(val == 1){
                head -> next = node1;
            }
            else{
                temp->next = node1;
            }
            sscanf(file_contents, "%[^,], %s", z01, z02);
            node1->data1 = atof(z01);
            node1->data2 = atof(z02);
            temp = node1;
        }
        val = val + 1;
    }
    dataset.head = head->next;
    return dataset;
}
