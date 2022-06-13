# Linear_Regression_C

### Linear Regression in C    


![005](https://user-images.githubusercontent.com/87653966/173309442-86172adb-de5b-4e3e-a922-93e6dc8cd125.png)


First of all, before training the data using linear regression we need to get data from CSV, but there is no library in C language such as Pandas in Python. Therefore, we must implement CSV inputer to get data and store in LinkedList. Why do we have to use the linkedlist for storing the data? I think we do not know the amount of datasets. So, I think Linkedlist is better than Array to store whose size is unknown.    

### csvlinkedlist.h   
    
    #ifndef csvlinkedlist_h
    #define csvlinkedlist_h
    
    // NODE for Linkedlist storing CSV data
    // If we have serveral Columns(Features) in CSV, just add Columns at this part.
    
    struct NODE{
        struct NODE *next;
        double data1; // data 1 (X column)
        double data2; // data 2 (Y column)
        int index;
    };

    // Storing W and B
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
    
     
### csv.c
This code is for storing CSV data to Linkedlist.
    
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include "csvlinkedlist.h"

    // Return CSV_LOAD Type
    CSV_LOAD csv(){

        int val = 0;
        struct stat sb;
        struct NODE *head = malloc(sizeof(struct NODE));
        struct NODE *temp = head;
        CSV_LOAD dataset;
        
        // File Name
        char *name = "regression.csv";
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

        // Saving the contents of the file
        char *file_contents = malloc(sb.st_size);
        while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
            if(val == 0){
                // First Line is names of each column like X and Y
                // We need to ignore this line.
            }
            else{
                // Make a Linkedlist storing CSV data
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
    
    
### list.c
Make two linkedlists storing each X and Y data.
    
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
    
     
### LinearRegression.c

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
    
    
#### Additional Explanation   

<img width="1000" alt="L033" src="https://user-images.githubusercontent.com/87653966/172146476-3e2be449-46aa-4e35-9acc-48fe0509f8b5.png">    
    
    double costFunction(List x, List y, double w, double b){
        double sum = 0;
        while(x.head != NULL){
            sum = sum + (((w * x.head->data + b - y.head->data) / 2) / y.size);
            y.head = y.head->next;
            x.head = x.head->next;
        }
        return sum;
    }
    
<img width="1000" alt="L034" src="https://user-images.githubusercontent.com/87653966/172147204-54486f8c-435f-407c-8a4e-2192cb0aeee4.png">

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
   
    
### Results
![006](https://user-images.githubusercontent.com/87653966/173313027-88d12aed-c89b-4989-9aac-b0d9f96690c3.png)
     
     
### Compare to Python
![007](https://user-images.githubusercontent.com/87653966/173313853-84cba04b-6503-493b-85d4-b2788cdb7edf.png)
     
     
### Graph (y = wx + b)
C language W, b values Graph
![008](https://user-images.githubusercontent.com/87653966/173314135-e1793d2b-d31d-4b0f-8988-57d8f092e396.png)
