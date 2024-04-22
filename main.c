#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webshop.h"

int main(){
    Store *webstore = webshop(SIZE);
    Cart *customer_cart   = webcart(SIZE);
 
    Webshop();                             
    int num;                              
    do{                                  
        Menu();
        printf(GREEN"Enter the respective choice number"RESET"\n");
        scanf("%d", &num);

        switch (num)
        {
         case 1:;                                   //Load webshop store from a file
            char file1[LENGTH];
            printf(GREEN"Enter file name: "RESET"\n");
            scanf("%s",file1);
            Import(webstore,file1);
            break;
         case 2:;                                  //Write the content of the store to a file
            char file2[LENGTH];
            printf(GREEN"Enter file name to save content of store"RESET"\n");
            scanf("%s",file2);
            Save(webstore,file2);
            break;
         case 3:;                                  //Insert an items to cart
            char item[LENGTH];
            int n;
            printf(GREEN"Enter product name and quantity"RESET"\n");  
            if(scanf("%s %d", item ,&n)!=2){
                printf(RED"Error!"RESET GREEN"Must enter both product name and quantity"RESET"\n");
            }
            
            Add_to_Cart(customer_cart, webstore,item,n);  
            break;
         case 4:;                                  //Get the price of cart
             Price(customer_cart);
             break;
         case 5:;                                  //Buy the products
            Purchase(customer_cart, webstore);
            break;
         case 6:;                                  //Exit the program
            Greeting();
            Empty_Cart(customer_cart);
            Empty_Store(webstore);

            break;
        
        default:
            printf(RED"Error!"RESET CYAN"Please enter correct number"RESET"\n");
            break;
        }

    }while(num != 6);
    
    
    MadeBy();
    
    return 0;
} 
