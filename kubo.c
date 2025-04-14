 /**
 *
 * @file kubo.c
 * @brief En una universidad muy famosa existe la cafetería El Kubo. Cuenta con servicio
 *        de alimentos de comida: Pizzas y Tacos.
 *        El Kubo requiere de un sistema que mejore el servicio y facturación de los alimentos.
 * @details A) Los clientes llegan a formar una sola cola en caja (FIFO). En la caja, los clientes
 *             una vez que pagan su pizza o sus tacos (son atendidos) salen de la cola.
 *          B) De ahí sus pedidos son enviados a una cola de tacos (FIFO) o a una cola de pizzas (FIFO circular).
 *          C) Los clientes llegan a la cola de pizzas o tacos y una vez que les entregan su comida, salen de la
 *             cola sus solicitudes (de pizzas o tacos).
 *          D) El negocio lleva los tickets de facturación en un histórico que es una pila (stack) dfacturas (LIFO).
 *          E) Todas las colas del sistema están integradas a una Lista Doble Lineal.
 *          F) El sistema inicia con una secuencia de clientes que está contenida en un archivo de texto y otro archivo
 *             la configuración del negocio: clientes.txt y negocio.txt.
 *             Dentro de clientes.txt la información se encuentra en el formato: # de Cuenta\tNombre\tMonedero
 *             Dentro de negocio.txt la información se encuentra en el formato: Terminal\tClientes\tMonto Acumulado
 *          G) El programa debe imprimir el estado de todas las colas.
 *          H) Para salir del sistema no debe haber clientes en las colas de tacos y pizzas.
 *          I) Al salir se debe de guardar un archivo con las facturas del día en el formato:
 *             # de factura\tnombre\tcompra\total facturado
 *             Y en la parte inferior del archivo se debe de guardar el monto total facturado.
 *          J) El programa debe almacenar los clientes restantes de la cola de la caja en un archivo de texto
 *             en el formato: # de Cuenta\tNombre\tMonedero
 * @date 05/04/2025
 * @author Mario Ureña García, Ricardo Ponce de León Vargas y Emiliano Cisneros Cervantes
 *
 */

#include "defKubo.h"

// Declaración de funciones --------------------------------------------------------------
void insertarColaD(nodoD **first, nodoD **last, char nombreCola[], int tickets, float total);
void imprimirListaD(nodoD *aux);
int menuOpciones(nodoD *aux, nodoD **seleccion);
void imprimirTerminal(nodoD *aux);
void atenderTerminal(nodoD **terminal);
void presioneEnter();
void insertarCaja(nodoD **first, int numCuenta, char nombreCliente[], float monedero);
void actualizarTerminales(nodoD **first);
void existenTerminalesFundamentales(nodoD *aux);
// Main ---------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    // argv[1] debe ser el archivo negocio.txt
    // argv[2] debe ser el archivo clientes.txt

    // Variables ------------------------------------------------------------------------
    nodoD *inicio, *fin;

    // Variable auxiliar para selección dinámica de atención, es decir, la caja que se atenderá o imprimirá
    nodoD *seleccion;

    FILE *fp;
    int opcion;

    // Variables para la lectura de datos de negocio.txt
    char nombreCola[20];
    int tickets;
    float total;

    // Variables para la lectura de datos de clientes.txt
    int numCuenta;
    char nombreCliente[20];
    float monedero;

    // Inicio Personalizado-----------------------------------------------------------
    printf("\n\n\tEste código fue creado por Mario Ureña García, Ricardo Ponce de León Vargas y Emiliano Cisneros Cervantes\n\n");
    printf("\n\tBienvenido al sistema de gestión de colas del Kubo!" RESET "\n\n");
    presioneEnter();
    //-------------------------------------------------------------------------------------

    // Procesos---------------------------------------------------------------------------

    // Inicialización de la lista doble
    inicio = NULL;
    fin = NULL;

    // Carga de datos desde el archivo de negocio
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf(RED "\n\n\tError al abrir el archivo de clientes\n\n" RESET);
        return 1;
    }

    // Lectura de datos del archivo negocio.txt
    printf(YELLOW "Cargando datos de negocio.txt...\n\n" RESET);
    while (fscanf(fp, "%s\t%d\t%f", nombreCola, &tickets, &total) == 3)
    {
        // Se inserta en la lista doble
        printf(CYAN "Creando nodo de %s\n" RESET, nombreCola);
        insertarColaD(&inicio, &fin, nombreCola, tickets, total);
        printf(GREEN "Nodo de %s creado con éxito\n" RESET, nombreCola);
    }
    fclose(fp);
    presioneEnter();

    printf(GREEN "Lista doble creada con éxito\n" RESET);
    imprimirListaD(inicio); // Imprimir lista doble para verificar que se cargaron los datos correctamente
    presioneEnter();

    // Verificar que existan las terminales fundamentales
    printf(YELLOW "Verificando que existan las terminales fundamentales\n\n" RESET);
    existenTerminalesFundamentales(inicio);
    printf(GREEN "Terminales fundamentales verificadas con éxito\n" RESET);
    presioneEnter();

    // Carga de datos desde el archivo de clientes a la terminal de la caja
    fp = fopen(argv[2], "r");
    if (fp == NULL)
    {
        printf(RED "\n\n\tError al abrir el archivo de clientes\n\n" RESET);
        return 1;
    }
    // Lectura de datos del archivo clientes.txt
    printf(YELLOW "Cargando datos de clientes.txt...\n\n" RESET);
    while (fscanf(fp, "%d\t%s\t%f", &numCuenta, nombreCliente, &monedero) == 3)
    {
        printf(CYAN "Insertando cliente %s con cuenta %d y monedero %.2f\n" RESET, nombreCliente, numCuenta, monedero);
        insertarCaja(&inicio, numCuenta, nombreCliente, monedero);
        printf(GREEN "Cliente %s insertado con éxito\n" RESET, nombreCliente);
    }
    printf(GREEN "\n\nClientes cargados con éxito\n" RESET);
    fclose(fp);
    presioneEnter();

    // Imprimir menú de opciones de impresión/atención
    do
    {
        actualizarTerminales(&inicio); // Actualizar el estado de las colas

        opcion = menuOpciones(inicio, &seleccion);
        getchar(); // Limpiar el buffer de entrada

        // Si la opción es 1, se imprimen todas las colas
        if (opcion == 1)
        {
            system("clear");
            printf("\n\n\tImprimiendo estado de todas las colas\n\n");
            imprimirListaD(inicio);
            presioneEnter();
        }
        // Si la opción es par y diferente de 0 y diferente de 1, se imprimirá la cola de la opción seleccionada
        if (opcion % 2 == 0 && opcion != 0 && opcion != 1)
        {
            system("clear");
            // Se imprime la cola de la opción seleccionada
            printf("\n\n\tImprimiendo cola de %s\n\n", seleccion->terminal);
            imprimirTerminal(seleccion);
            presioneEnter();
        }
        // Si la opción es impar y diferente de 0 y diferente de 1, se atenderá la cola de la opción seleccionada
        else if (opcion % 2 != 0 && opcion != 0 && opcion != 1)
        {
            system("clear");
            // Se atiende la cola de la opción seleccionada
            printf("\n\n\tAtendiendo cola de %s\n\n", seleccion->terminal);
            atenderTerminal(&seleccion);
            presioneEnter();
        }

    } while (opcion != 0); // La opción 0 es para salir del programa

    // FINALIZACIÓN DEL PROGRAMA ---------------------------------------------------------
    printf("\n\n\tPrograma Finalizado con ÉXITO\n\n");
    return 0;
}
