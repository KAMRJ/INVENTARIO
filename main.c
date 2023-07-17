#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcion.h"

int main(int argc, char *argv[])
{
    Producto productos[Max_Productos];

    for (int i = 0; i < Max_Productos; i++)
    {
        productos[i].nombre[0] = 0;
        productos[i].descripcion[0] = 0;
        productos[i].cantidad = 0;
        productos[i].precio = 0;
    }

    CargarInventario(productos);
    int opcion;

    do
    {
        printf("\n");
        printf("1. Ingresar Productos\n");
        printf("2. Visualizar Inventario\n");
        printf("3. Modificar Productos\n");
        printf("4. Eliminar Productos\n");
        printf("5. Guardar Inventario\n");
        printf("6. Salir\n");

        printf("Seleccione una opcion:");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            IngresoProductos(productos);
            break;
        case 2:
            VisualizarInventario(productos);
            break;
        case 3:
            ModificarProductos(productos);
            break;
        case 4:
            EliminarProductos(productos);
            break;
        case 5:
            GuardarInventario(productos);
            break;
        case 6:
            printf("Saliendo del programa...\n");
        default:
            printf("Opcion no valida. Intentalo de nuevo\n");
            break;
        }
    } while (opcion != 6);

    return 0;
}