#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcion.h"

void IngresoProductos(Producto productos[])
{
     int i;
    for (i = 0; i < Max_Productos; i++) {
        if (productos[i].cantidad == 0) {
            printf("Ingrese el nombre del producto: ");
            scanf(" %[^\n]", productos[i].nombre);
            printf("Ingrese la descripcion del producto: ");
            scanf(" %[^\n]", productos[i].descripcion);
            printf("Ingrese la cantidad del producto: ");
            scanf("%f", &productos[i].cantidad);
            printf("Ingrese el precio del producto: ");
            scanf("%f", &productos[i].precio);
            printf("Producto ingresado exitosamente.\n");
            return;
        }
    }
}

void VisualizarInventario(Producto productos[])
{
    printf("----------------INVENTARIO DE PRODUCTOS MENU -------------------------------------------------\n");
    printf("  ID  |          NOMBRE          |            DESCRIPCION            |   CANTIDAD   |   PRECIO   \n");
    printf("-----------------------------------------------------------------------------------------------\n");
    int i;
    for (int i = 0; i < Max_Productos; i++)
    {
        if (productos[i].cantidad != 0)
        {
            printf("%6d|%-26s|%-35s|%14.0f|%10.2f\n", i+1, productos[i].nombre, productos[i].descripcion, productos[i].cantidad, productos[i].precio);
        }
    }
    printf("-----------------------------------------------------------------------------------------------\n");
}

void ModificarProductos(Producto productos[])
{
    int opcion;
    printf ("Que producto desea modificar?\n");
    for (int i = 0; i < Max_Productos; i++) {
        if (productos[i].cantidad != 0) {
            printf("%d. %s\n", i + 1, productos[i].nombre);
        }
    }
    printf("%d. Cancelar\n", Max_Productos + 1);
    printf("Selecciona una opcion: ");
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > Max_Productos + 1) {
        printf("Opcion no valida. Intenta de nuevo.\n");
        return;
    }
    if (opcion == Max_Productos + 1) {
        printf("Operacion cancelada.\n");
        return;
    }
    int index = opcion - 1;
    Producto *producto = &productos[index];
    printf("Ingresa la nueva cantidad para el Producto %d: ", opcion);
    scanf("%f", &producto->cantidad);
    printf("Ingresa el nuevo nombre para el Producto %d: ", opcion);
    scanf(" %[^\n]", producto->nombre);
    printf("Ingresa la nueva descripcion para el Producto %d: ", opcion);
    scanf(" %[^\n]", producto->descripcion);
    printf("Ingresa el nuevo precio para el Producto %d: ", opcion);
    scanf("%f", &producto->precio);
    printf("Producto %d modificado exitosamente.\n", opcion);
}

void EliminarProductos(Producto productos[])
{
     int opcion;
    printf("¿Qué producto deseas eliminar?\n");
    for (int i = 0; i < Max_Productos; i++) {
        if (productos[i].cantidad != 0) {
            printf("%d. %s\n", i + 1, productos[i].nombre);
        }
    }
    printf("Selecciona el numero de producto que deseas eliminar: ");
    scanf("%d", &opcion);
    
    if (opcion < 1 || opcion > Max_Productos) {
        printf("Opcion no valida. Intenta de nuevo.\n");
        return;
    }
    
    int index = opcion - 1;
    
    productos[index].cantidad = 0;
    productos[index].precio = 0;
    strcpy(productos[index].nombre, "");
    strcpy(productos[index].descripcion, "");

    printf("Producto %d eliminado exitosamente.\n", opcion);
}

void GuardarInventario(Producto productos[])
{
    FILE *archivo = fopen("inventario", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "----------------INVENTARIO DE PRODUCTOS MENU -------------------------------------------------\n");
    fprintf(archivo, "  ID  |          NOMBRE          |            DESCRIPCION            |   CANTIDAD   |   PRECIO   \n");
    fprintf(archivo, "-----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < Max_Productos; i++) {
        if (productos[i].cantidad != 0) {
            fprintf(archivo, "%6d|%-26s|%-35s|%14.0f|%10.2f\n", i + 1, productos[i].nombre, productos[i].descripcion, productos[i].cantidad, productos[i].precio);
        }
    }
    fprintf(archivo, "-----------------------------------------------------------------------------------------------\n");
    fclose(archivo);
    printf("Inventario guardado exitosamente.\n");
}

void CargarInventario(Producto productos[])
{
    FILE *archivo = fopen("inventario", "r");
    if (archivo == NULL) {
        printf("No se encontro el archivo de inventario. Se creara uno nuevo.\n");
        return;
    }
    char linea[150];
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char *nombre = strtok(linea, ";");
        char *descripcion = strtok(NULL, ";");
        float cantidad = atof(strtok(NULL, ";"));
        float precio = atof(strtok(NULL, ";"));
        strcpy(productos[i].nombre, nombre);
        strcpy(productos[i].descripcion, descripcion);
        productos[i].cantidad = cantidad;
        productos[i].precio = precio;
        i++;
    }
    fclose(archivo);
    printf("Inventario cargado exitosamente.\n");
}

void EditarDatos (Producto productos[])
{
        FILE *archivo = fopen("inventario", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    VisualizarInventario(productos);
    int opcion;
    printf("Selecciona el numero de producto que deseas editar: ");
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > Max_Productos) {
        printf("Opcion no valida. Intenta de nuevo.\n");
        fclose(archivo);
        return;
    }
    int index = opcion - 1;
    Producto *producto = &productos[index];
    fseek(archivo, sizeof(Producto) * index, SEEK_SET);
    fwrite(producto, sizeof(Producto), 1, archivo);
    fclose(archivo);
    printf("Producto %d modificado exitosamente.\n", opcion);
}