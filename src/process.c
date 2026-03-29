#include <cJSON.h> 
#include <pos.h>
struct product * inventario = NULL;
const char filename[] = {"../productos.json"};

void procesar_json(const char *filename) {
    // 1. Leer el archivo completo a memoria
    FILE *f = fopen(filename, "rb");
    if (!f) return;
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *data = malloc(length + 1);
     
    fread(data, 1, length, f);
    fclose(f);
    data[length] = '\0';

    // 2. Parsear el JSON
    cJSON *json_root = cJSON_Parse(data);
    if (!json_root) {
        printf("Error al parsear JSON.\n");
        free(data);
        return;
    }

    int size = cJSON_GetArraySize(json_root);
    inventario = malloc(sizeof(struct product) * size);
    // 3. Iterar y llenar el arreglo de structs
    for (int i = 0; i < size; i++) {
        cJSON *item = cJSON_GetArrayItem(json_root, i);

        inventario[i].id = cJSON_GetObjectItem(item, "id")->valueint;
        snprintf(inventario[i].nombre, 100, "%s", cJSON_GetObjectItem(item, "nombre")->valuestring);
        snprintf(inventario[i].categoria, 50, "%s", cJSON_GetObjectItem(item, "categoria")->valuestring);
        inventario[i].precio_compra = (float)cJSON_GetObjectItem(item, "precio_compra")->valuedouble;
        inventario[i].precio_venta = (float)cJSON_GetObjectItem(item, "precio_venta")->valuedouble;
        inventario[i].descuento = cJSON_GetObjectItem(item, "descuento")->valueint;

        cJSON *imp = cJSON_GetObjectItem(item, "impuestos");
        inventario[i].imp.iva = cJSON_GetObjectItem(imp, "iva")->valueint;
        inventario[i].imp.precios_cuidados = cJSON_GetObjectItem(imp, "precios_cuidados")->valueint;

        // Debug: imprimir un valor

    }
    
    // Limpieza
    cJSON_Delete(json_root);
    free(data);
}

struct product get_producto(int id) { 
    if (inventario == NULL) 
        procesar_json("../productos.json");
    return inventario[id]; 
}

void save_ticket (struct ticket p, FILE * fp) { 
    if (fp == NULL) 
        return ;
    printf("HOLA");
    cJSON * json_obj = cJSON_CreateObject(); 
    cJSON * json_names = cJSON_CreateArray();
    cJSON * json_ids = cJSON_CreateArray();

    if (json_obj == NULL || json_names == NULL || json_ids == NULL) 
        return ;

    int i = 0; 
    printf ("HOLA");
    while (i < p.cantidad_vendido) { 
        cJSON_AddItemToArray(json_names, cJSON_CreateString(p.nombres[i]));   
        cJSON_AddItemToArray(json_ids, cJSON_CreateNumber(p.ids[i]));
        i++; 
    }

    cJSON_AddItemToObject(json_obj,"names" , json_names);
    cJSON_AddItemToObject(json_obj,"ids", json_ids);  
     cJSON_AddNumberToObject(json_obj, "precio", p.precio); 
    cJSON_AddNumberToObject(json_obj, "canitad_ahorrado", p.cantidad_ahorrado);
    
    char * json_string =  cJSON_Print(json_obj);
    fprintf(fp, "%s", json_string); 
    free(json_string); 
    cJSON_Delete(json_obj); 
    free(inventario); 
}

