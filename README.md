# POS-system
A system that accept payment from a command line and keep track of the sales

Sistema pos (point of sale)

Recibe de input un archivo con multiples productos donde sus datos son: Identificador, precio de venta, precio en el que fue adquirido, Nombre, Descuento, stock, categoria
Un producto puede tener impuestos, por ejemplo: IVA (asignado a todos los productos vendidos), Precios cuidados (una constante asignada, aplicado a distintos productos),
impuestos provinciales y municipales no entran en el dominio del problema

Precios cuidados bajaria el precio del producto, IVA entraria en ese precio.
Valores: PC = -20% e IVA = 21%

Categorias en las que entran precios cuidados: Alimentos e higiene;



El sistema debe poder:
	1. Realizar una compra (ingresa una serie de identificadores y debe poder generar un ticket donde se epecifique costo de la compra, cantidad ahorrado por descuento y los productos comprados). Guardar el ticket en otro archivo donde se guarde la fecha de la venta.
	2. Insertar nuevos descuentos
	3. Chequear el stock de un producto dado un string.
	4. Dado el archivo de ventas devolver los productos mas vendidos.
	5. Dado el archivo de ventas devolver la cantidad perdida por la empresa debido a los descuentos y cuanto afecto en el precio total los impuestos agregados.
	6. Actualizar precios ingresando un valor de inflacion
