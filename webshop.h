#ifndef WEBSHOP_H
#define WEBSHOP_H

#define LENGTH 30
#define SIZE 10

//ANSI Codes
#define GREEN      "\033[32m"       //menu, Instructions
#define BLUE       "\033[34m"       //madeby
#define YELLOW     "\033[33m"       //webshop, Greeting
#define RED        "\033[31m"       //error
#define CYAN       "\033[36m"       //promt
#define RESET      "\033[0m"

// Struct Product to store details of products in the webshop
typedef struct Product {
    char name[LENGTH];
    int price;
    int quantity;
} Product;

//First instance Webshop Store
typedef struct Store {
    Product *items;
    int size;
    int capacity;
} Store;

//Second instance Webshop Cart
typedef struct Cart {
    Product *items;
    int size;
    int capacity;
} Cart;

//Menu items and their declaration
void Webshop();                       //Additional to print "Webshop" after execution
void Menu();                         //Function to display Menu items
void MadeBy();                      //Additional Function to display name of project editor
void Greeting();                   //At last display Have a nice day
Store *store(int size);
Cart *cart(int size);
void Import(Store *store,  char *filename);             //Load webshop store from a file
void Save(Store *store,  char *filename);              //Write the content of the store to a file
void Resize(Store *store,  Product *product);         //Increase the quantity of existing product
void Add_to_Cart(Cart *cart,  Store *store,  char *name, int quantity);
void Price(Cart *cart);                                //sum of the products prices in the cart
void Purchase(Cart *cart, Store *store);              //Subtract cart from store
void Empty_Cart(Cart *cart);                         //Free allocated memory to avoid memory leak
void Empty_Store(Store *store);                     //Free allocated memory to avoid memory leak 


#endif