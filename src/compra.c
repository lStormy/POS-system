#include <pos.h> 
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>*/
#define MAX_COMPRA 10000


static int * pId = NULL; 

const char filepath[] = {"../compras.json"}; 

int get_compra(FILE * fp) { 
    int * cursor,  i = 0, k = 0;
    size_t cantidad;
    char s[MAX_COMPRA][6], *line;  
    
    while ((fgets(s[i], 6, fp) != NULL))
           i++; 
    
    cantidad = i; 

    pId = calloc(cantidad, sizeof(int));
    i = 0;
    while (i < cantidad) {
        line = s[i];
        while (*line && isspace(*line)) 
            line++; 
        while (*line) {
            if (isspace(*line) || *line == '\n') {  
                k++;
            }
            else if (isdigit(*line)) { 
                pId[k] *= 10;
                pId[k] += *line-'0';
            }
            line++;
        }
        i++;
    }  
    return cantidad;
} 

void print_product (struct product p) {
    printf("%d\n, %s\n, %s\n, %f\n, %f\n, %d",
          p.id, p.categoria, p.nombre, p.precio_compra,
          p.precio_venta, p.descuento); 
}  

struct ticket create_ticket(int cantidad) { 
    struct ticket compra = {.cantidad_vendido = cantidad}; 
    struct product aux; 
    float ahorrado; 
    for (int i = 0; i < cantidad; i++) {
        aux = get_producto(pId[i]);

        print_product(aux);
        compra.ids[i] = aux.id; 
        strcpy(compra.nombres[i], aux.nombre); 
        ahorrado = ((float) aux.precio_venta)*((float)aux.descuento/100.0f);
        ahorrado += (aux.imp.precios_cuidados == 1) ? (aux.precio_venta * PRECIOS_CUIDADOS) : 0;
        compra.precio += (aux.precio_venta - ahorrado); 
        compra.cantidad_ahorrado = ahorrado; 
    }
    return compra;
}

void process_compra(FILE *fp) { 
    struct ticket compra;
    int cantidad = get_compra(fp); 
    FILE * out = fopen(filepath, "a"); 
    
    compra = create_ticket(cantidad); 
    save_ticket(compra, out);

    fclose(out);
}

int main () { 
    process_compra(stdin); 
    free(pId); 
    return 0;
}



