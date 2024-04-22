#include "webshop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Yellow Colour
void Webshop(){
    printf("\n");
    printf(YELLOW"W   W  EEEEE BBBB   SSSS  H   H  OOO   PPPP"RESET"\n");
    printf(YELLOW"W   W  E     B   B S      H   H O   O  P   P"RESET"\n");
    printf(YELLOW"W W W  EEEE  BBBB   SSS   HHHHH O   O  PPPP"RESET"\n");
    printf(YELLOW"W W W  E     B   B      S H   H O   O  P"RESET"\n");
    printf(YELLOW"W W W  EEEEE BBBB   SSSS  H   H  OOO   P"RESET"\n");
    printf("\n");
}
//Blue Colour
void MadeBy(){
     printf(BLUE"Made by AdnanDevHub!"RESET"\n");
}

void Menu(){
    printf("    => "GREEN" MENU:"RESET   "\n");
    printf(BLUE"1."RESET "Load webshop store from a file\n");
    printf(BLUE"2."RESET "Write the content of the store to a file\n");
    printf(BLUE"3."RESET "Insert an item to cart\n");
    printf(BLUE"4."RESET "Get the price of cart\n");
    printf(BLUE"5."RESET "Buy the products\n");
    printf(BLUE"6."RESET "Exit the program\n");
    printf("\n");
} 
//Yellow Colour
void Greeting(){
    printf(YELLOW"HAVE A NICE DAY:)"RESET"\n");
    printf("\n");
}
// creating maximum storage initially
Store *webshop(int size) {
    Store *store1 = malloc(sizeof(Store));
    store1->items = malloc(size * sizeof(Product));
    store1->size = 0;
    store1->capacity = size;  
    return store1;
}

// creating maximum items can be added initially
Cart *webcart(int size) {
    Cart *cart1 = malloc(sizeof(Cart));
    cart1->items = malloc(size * sizeof(Product));
    cart1->size = 0;
    cart1->capacity = size; 
    return cart1;
}

void Import(Store *store, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf(RED"Error!"RESET CYAN" can not open file"RESET"\n");
        return;
    }

    char name[LENGTH];
    int price;
    int quantity;

    while (fscanf(file, " %29s %d %d", name, &price, &quantity) == 3) {
        Product load;
        strcpy(load.name, name);       //name -> string array so can not assign directly(=)
        load.price = price;
        load.quantity = quantity;

        Resize(store, &load);
    }
    printf(CYAN"Loaded Successfully!"RESET"\n");

    fclose(file);
}


void Save(Store *store, char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf(RED"Error!"RESET CYAN" can not open file"RESET"\n");
        return;
    }

        for (int i = 0; i < store->size; i++) 
        {
          fprintf(file, "%s %d %d\n", store->items[i].name, store->items[i].price, store->items[i].quantity);
        }
           fflush(file);

           printf(CYAN"Saved Successfully!"RESET"\n");

           fclose(file);
}


void Resize(Store *store, Product *product) {
    if (store->size == store->capacity) {
        if(store->capacity == 0){
          store->capacity = 1;
        }
        else{
            store->capacity  = store->capacity * 2;
        }
    
        store->items = realloc(store->items, store->capacity * sizeof(Product));
    }

    store->items[store->size++] = *product;
}

void Add_to_Cart(Cart *cart, Store *store, char *name, int quantity) {
    // Check products in the store
    for (int i = 0; i < store->size; i++) {
        Product *product = &store->items[i];
        // Check if the product asked by the user is in the store or not
        // Returns 0 if true; if so add in the cart
        if (strcmp(product->name, name) == 0) {
            Product Added_to_Cart;
            strcpy(Added_to_Cart.name, product->name);
            Added_to_Cart.price = product->price;
            Added_to_Cart.quantity = quantity;

            // Now check if the product already exists; increase the quantity
            for (int j = 0; j < cart->size; j++) {
                if (strcmp(cart->items[j].name, name) == 0) {
                    cart->items[j].quantity += quantity;
                    printf(CYAN"Added to Cart"RESET"\n");
                    return;
                }
            }

            // If the cart reach max capacity, resize it
            if (cart->size == cart->capacity) {
                cart->capacity *= 2;
                cart->items = realloc(cart->items, cart->capacity * sizeof(Product));
            }

            // Add the product into the cart
            cart->items[cart->size++] = Added_to_Cart;
            printf(CYAN"Added to Cart"RESET"\n");
            return;
        }
    }
    // If the product asked by the user is not in the store
    printf(CYAN"Sorry! Product %s is not available for now:("RESET"\n", name);
}



void Price(Cart *cart) {
    long long cost = 0;
    for (int i = 0; i < cart->size; i++) {
        Product *item = &cart->items[i];
        cost += (long long) item->price * (long long) item->quantity;
    }
    printf(CYAN"Total Cost:"RESET "%lld\n", cost);
}



void Purchase(Cart *cart, Store *store) {
    for (int i = 0; i < cart->size; i++) {
        Product *purchased_product = &cart->items[i];          //Assigning products in the cart
        
        for (int j = 0; j < store->size; j++) {
            Product *store_product = &store->items[j];         //Assigning products in the store
            //Checking if both of them match
            if (strcmp(store_product->name, purchased_product->name) == 0) {
            
                if (store_product->quantity < purchased_product->quantity) {
                    printf(CYAN"Purchased %s Partailly!"RESET"\n",purchased_product->name);
                    printf(CYAN"%d %s are missing"RESET"\n",purchased_product->quantity - store_product->quantity,purchased_product->name);
                    store_product->quantity = 0;         //subtracting the available amount of products from the store.
                } else {
                    printf(CYAN"Purchased %s successfully"RESET"\n", purchased_product->name);
                }
                break;  
            }
        }   
    }
}

void Empty_Cart(Cart *cart) {
    free(cart->items);
    free(cart);
}

void Empty_Store(Store *store) {
    free(store->items);
    free(store);
}

