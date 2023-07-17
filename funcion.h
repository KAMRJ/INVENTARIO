#ifndef FUNCION_H
#define FUNCION_H
#define Max_Productos 10

typedef struct
{
    char nombre[10];
    char descripcion[20];
    float precio, cantidad;
} Producto;

void IngresoProductos(Producto productos[]);
void ModificarProductos(Producto productos[]);
void EliminarProductos(Producto productos[]);
void VisualizarInventario(Producto productos[]);
void CargarInventario(Producto productos[]);
void GuardarInventario(Producto productos[]);
void EditarDatos (Producto productos[]);

#endif