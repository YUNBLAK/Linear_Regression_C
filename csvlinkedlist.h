#ifndef csvlinkedlist_h
#define csvlinkedlist_h

struct NODE{
    struct NODE *next;
    double data1; // data 1
    double data2; // data 2
    int index;
};

typedef struct eqt{
    double w;
    double b;
}EQUATION;

typedef struct CSV{
    struct NODE *head;
    int size;
}CSV_LOAD;

struct singleNODE{
    struct singleNODE *next;
    double data;
    int index;
};

typedef struct linkedlist{
    struct singleNODE *head;
    int size;
}List;

#endif /* csvlinkedlist_h */
