#include <stdio.h> 
#include <time.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>

#define CANT_STOCK 10000
#define PRECIOS_CUIDADOS 0.20
struct impuestos { 
    int iva : 1; 
    int precios_cuidados : 1; 
};

struct ticket {
    int ids [CANT_STOCK]; 
    int precio; 
    char nombres[CANT_STOCK][50];
    float cantidad_ahorrado;
    int cantidad_vendido;
};

struct product { 
    int id;
    char categoria[100];
    char nombre[50]; 
    float precio_compra, precio_venta;
    int descuento; 
    struct impuestos imp;
};

extern struct product * inventario; 
void procesar_json(const char * filename);
struct product get_producto(int); //dado id devolver producto
void save_ticket(struct ticket, FILE *); 

void process_compra(FILE *);  

