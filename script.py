import json
import random

def generar_productos_json(archivo_salida, cantidad=10000):
    categorias = ["higiene", "lacteos", "comida", "bebidas", "limpieza", "carniceria"]
    nombres_base = {
        "higiene": ["Jabón", "Champú", "Desodorante", "Pasta dental"],
        "lacteos": ["Leche", "Yogur", "Queso Crema", "Manteca"],
        "comida": ["Arroz", "Fideos", "Aceite", "Harina", "Galletitas"],
        "bebidas": ["Agua Mineral", "Gaseosa", "Jugo de Naranja", "Cerveza"],
        "limpieza": ["Detergente", "Lavandina", "Desinfectante"],
        "carniceria": ["Pollo", "Carne Vacuna", "Cerdo"]
    }

    productos = []

    for i in range(1, cantidad + 1):
        cat = random.choice(categorias)
        nombre = f"{random.choice(nombres_base[cat])} {random.randint(1, 100)}"
        
        # Lógica de precios: venta siempre mayor que compra
        precio_compra = round(random.uniform(50.0, 5000.0), 2)
        precio_venta = round(precio_compra * random.uniform(1.2, 1.6), 2)
        
        producto = {
            "id": i,
            "nombre": nombre,
            "categoria": cat,
            "precio_compra": precio_compra,
            "precio_venta": precio_venta,
            "descuento": random.randint(0, 30),
            "impuestos": {
                "iva": random.randint(0, 1),
                "precios_cuidados": random.randint(0, 1)
            }
        }
        productos.append(producto)

    with open(archivo_salida, 'w', encoding='utf-8') as f:
        json.dump(productos, f, indent=4, ensure_ascii=False)

if __name__ == "__main__":
    generar_productos_json("productos.json")
