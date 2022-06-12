// LIST


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "csvlinkedlist.h"

extern CSV_LOAD csv();
List xvalues(){
    CSV_LOAD temp = csv();
    List xlst;
    int tempVal = 0;
    
    struct singleNODE *head = malloc(sizeof(struct singleNODE));
    struct singleNODE *tp = head;
    
    while(temp.head != NULL){
        struct singleNODE *node = malloc(sizeof(struct singleNODE));
        if(tempVal == 0){
            xlst.size = tempVal;
            node->data = temp.head->data1;
            head->next = node;
        }
        else{
            node->data = temp.head->data1;
            tp->next = node;
            xlst.size = tempVal;
        }
        tempVal = tempVal + 1;
        tp = node;
        temp.head = temp.head->next;
    }
    xlst.head = head->next;
    xlst.size = xlst.size + 1;
    return xlst;
    
}

List yvalues(){
    CSV_LOAD temp = csv();
    List xlst;
    int tempVal = 0;
    
    struct singleNODE *head = malloc(sizeof(struct singleNODE));
    struct singleNODE *tp = head;
    
    while(temp.head != NULL){
        // printf("[] %.8f\n", temp.head->data1);
        //printf("[] %.8f\n",temp.head->data2);
        struct singleNODE *node = malloc(sizeof(struct singleNODE));
        if(tempVal == 0){
            xlst.size = tempVal;
            node->data = temp.head->data2;
            head->next = node;
        }
        else{
            node->data = temp.head->data2;
            tp->next = node;
            xlst.size = tempVal;
        }
        tempVal = tempVal + 1;
        tp = node;
        temp.head = temp.head->next;
    }
    xlst.head = head->next;
    xlst.size = xlst.size + 1;
    return xlst;
    
}

void printx(){
    List x = xvalues();
    while(x.head != NULL){
        printf("%.8f\n", x.head->data);
        x.head = x.head->next;
    }
    printf("[] %d\n", x.size);
}

void printy(){
    List x = yvalues();
    while(x.head != NULL){
        printf("%.8f\n", x.head->data);
        x.head = x.head->next;
    }
    printf("[] %d\n", x.size);
}
