// Linear Regression in C
// Made by Daniel Yun

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include "csvlinkedlist.h"

extern List xvalues();
extern List yvalues();

double costFunction(List x, List y, double w, double b){
    double sum = 0;
    while(x.head != NULL){
        sum = sum + (((w * x.head->data + b - y.head->data) / 2) / y.size);
        y.head = y.head->next;
        x.head = x.head->next;
    }
    return sum;
}

double gradientW(List x, List y, double w, double b){
    double sum = 0;
    while(x.head != NULL){
        sum = sum + ((w * x.head->data + b - y.head->data) * x.head->data  / y.size);
        y.head = y.head->next;
        x.head = x.head->next;
    }
    return sum;
}

double gradientB(List x, List y, double w, double b){
    double sum = 0;
    while(x.head != NULL){
        sum = sum + ((w * x.head->data + b) /  y.size);
        y.head = y.head->next;
        x.head = x.head->next;
    }
    return sum;
}

EQUATION equation(int iteration, double rate){
    int i;
    double w = 0.0;
    double b = 0.0;
    for(i = 0; i < iteration; i++){
        double gw = gradientW(xvalues(), yvalues(), w, b);
        double gb = gradientB(xvalues(), yvalues(), w, b);
        w = w - gw * rate;
        b = b - gb * rate;
    }
    EQUATION *temp = malloc(sizeof(EQUATION));
    temp->w = w;
    temp->b = b;
    
    return *temp;
}


// Root Mean Square Deviation
double RMSET(List x, List y, double w, double b){
    double rm = 0.0;
    while(x.head != NULL){
        rm = rm + (y.head->data - (x.head->data * w + b)) * (y.head->data - (x.head->data * w + b));
        x.head = x.head->next;
        y.head = y.head->next;
    }
    rm = rm / x.size;
    rm = sqrt(rm);
    return rm;
}

void printRMSE(double w, double b){
    double r = RMSET(xvalues(), yvalues(), w, b);
    printf("%.16f\n", r);
}

