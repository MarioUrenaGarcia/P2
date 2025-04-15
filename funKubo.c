#include "defKubo.h"

/**
 * @file kubo.c
 * @brief En este archivo se almacenan las funciones de kubo.c
 * @date 04/04/2025
 * @author Mario Ureña García, Ricardo Ponce de León Vargas y Emiliano Cisneros Cervantes
 */

// Funciones ----------------------------------------------------------------------------
extern void imprimirTerminal(nodoD *aux);
/**
 * @brief
 * @date
 * @author
 * @param
 * @return
 * @Ejemplo
 */

int sumarClientes(nodoCola *aux)
{
    int total = 0;

    while (aux != NULL)
    {
        total++;
        aux = aux->next;
    }

    return total;
}

int sumarMonederos(nodoCola *aux)
{
    float total = 0;

    while (aux != NULL)
    {
        total += aux->monedero;
        aux = aux->next;
    }

    return total;
}

extern void borrarCliente(nodoD **terminal)
{
    nodoCola *borra;

    // Verificar si la cola está vacía
    if ((*terminal)->primero == NULL && (*terminal)->ultimo == NULL)
    {
        printf(RED "\nLa cola %s está vacía\n" RESET, (*terminal)->terminal);
    }
    else
    {
        borra = (*terminal)->primero;

        // Caso: Un solo cliente en la cola
        if ((*terminal)->primero == (*terminal)->ultimo)
        {
            (*terminal)->primero = NULL;
            (*terminal)->ultimo = NULL;
        }
        else // Caso: Más de un cliente en la cola
        {
            (*terminal)->primero = (*terminal)->primero->next;
            (*terminal)->ultimo->next = (*terminal)->primero; // Mantener la circularidad
        }

        free(borra); // Liberar la memoria del cliente eliminado
        printf(GREEN "\nCliente eliminado de la cola %s\n" RESET, (*terminal)->terminal);
    }
    return;
}

void insertarClienteComida(nodoD **terminal, nodoCola *cliente)
{
    nodoCola *nuevo;

    nuevo = (nodoCola *)malloc(sizeof(nodoCola));
    if (nuevo == NULL)
    {
        printf(RED "\nERROR: No hay memoria disponible\n" RESET);
        exit(1);
    }
    nuevo->numCuenta = cliente->numCuenta;
    strcpy(nuevo->nombre, cliente->nombre);
    nuevo->monedero = cliente->monedero;
    nuevo->next = NULL;

    // Caso: Cola vacía
    if (((*terminal)->primero == NULL) && ((*terminal)->ultimo == NULL))
    {
        (*terminal)->primero = nuevo;
        (*terminal)->ultimo = nuevo;
    }
    else // Caso: Cola no vacía
    {
        (*terminal)->ultimo->next = nuevo;
        (*terminal)->ultimo = nuevo;
    }

    return;
}

/**
 * @brief Función que imprime el menú de opciones y devuelve la opción seleccionada por el usuario.
 * @param aux Puntero a la lista doble que contiene los puestos de comida.
 * @param seleccion Puntero a la lista doble que contiene el puesto que se va a atender.
 * @return Opción seleccionada por el usuario.
 */
extern int menuOpciones(nodoD *aux, nodoD **seleccion)
{
    int opcion, i, validez = 2;
    nodoD *first = aux;

    printf("\n");

    // Para que sea funcional no importando cuantos puestos de comida existan, se imprimiran tantas
    // opciones como puestos de comida existan. Por cada puesto de comida existirá la opción de
    // imprimir la cola de ese puesto de comida o atender esa cola.

    do
    {

        i = 2;

        if (validez == 1)
        {
            printf(RED "\nOpción inválida. Intente de nuevo.\n" RESET);
        }
        printf(GREEN "1." RESET " Imprimir estado de todas las colas\n");
        while (aux != NULL)
        {
            printf(CYAN "%d." RESET " Imprimir cola de %s\n", i, aux->terminal);
            i++;
            printf(YELLOW "%d." RESET " Atender cola de %s\n", i, aux->terminal);
            i++;
            aux = aux->next;
        }
        printf(BG_WHITE BLACK "0. Salir\n" RESET);
        printf("\nElija una opción: ");
        scanf(" %d", &opcion);

        // Validación de la opción
        if (opcion < 0 || opcion > i) // Opción inválida
        {
            validez = 1;
            aux = first;
        }
        else // Opción válida
        {
            validez = 0;
        }

    } while (validez == 1);

    // De retorno extra, se asigna el nodoD seleccionado a la variable seleccion para su uso en main
    // Para eso, necesitamos que aux tome el valor del nodo que se va a atender

    aux = first;

    for (i = 1; i < opcion; i = i + 2)
    {
        *seleccion = aux;
        aux = aux->next;
    }

    return opcion;
}

extern void insertarColaD(nodoD **first, nodoD **last, char nombreCola[], int tickets, float total)
{
    nodoD *nuevo;

    nuevo = (nodoD *)malloc(sizeof(nodoD));
    if (nuevo == NULL)
    {
        printf(RED "\nERROR: No hay memoria disponible\n" RESET);
        exit(1);
    }
    strcpy(nuevo->terminal, nombreCola);
    nuevo->clientes = tickets;
    nuevo->montoAcumulado = total;

    // Inicializar subcolas
    nuevo->primero = NULL;
    nuevo->ultimo = NULL;
    nuevo->top = NULL;

    // Caso: Lista vacía
    if ((*first == NULL) && (*last == NULL))
    {
        nuevo->back = NULL;
        nuevo->next = NULL;
        *first = nuevo;
        *last = nuevo;
    }
    else // Caso: Lista no vacía
    {
        nuevo->back = *last;
        nuevo->next = NULL;
        (*last)->next = nuevo;
        *last = nuevo;
    }

    return;
}

extern void insertarCaja(nodoD **first, int numCuenta, char nombreCliente[], float monedero)
{
    nodoCola *nuevo;
    nodoD *aux;

    // Puede que la caja no esté en la primera posición del archivo negocios.txt
    // Por lo que se debe buscar en toda la lista doble y almacenarla en una variable caja
    nodoD **caja = NULL;

    // Buscar la cola con nombre Caja
    aux = *first;
    while (aux != NULL)
    {
        if (strcmp(aux->terminal, "Caja") == 0)
        {
            caja = &aux;
            break;
        }
        aux = aux->next;
    }

    nuevo = (nodoCola *)malloc(sizeof(nodoCola));
    if (nuevo == NULL)
    {
        printf(RED "\nERROR: No hay memoria disponible\n" RESET);
        exit(1);
    }
    nuevo->numCuenta = numCuenta;
    strcpy(nuevo->nombre, nombreCliente);
    nuevo->monedero = monedero;
    nuevo->next = NULL;

    // Caso: Cola vacía
    if (((*caja)->primero == NULL) && ((*caja)->ultimo == NULL))
    {
        (*caja)->primero = nuevo;
        (*caja)->ultimo = nuevo;
    }
    else // Caso: Cola no vacía
    {
        (*caja)->ultimo->next = nuevo;
        (*caja)->ultimo = nuevo;
    }
    return;
}

extern void imprimirListaD(nodoD *aux)
{
    printf(YELLOW "\nEstado de Cajas\n" RESET);

    if (aux == NULL)
    {
        printf(RED "\nLa lista está vacía\n" RESET);
        return;
    }
    else
    {
        while (aux != NULL)
        {
            printf(YELLOW "\nNombre de la cola:" RESET " %s\n", aux->terminal);
            printf(GREEN "Número de clientes:" RESET " %d\n", aux->clientes);
            printf(GREEN "Monto acumulado:" RESET " $%.2f\n", aux->montoAcumulado);
            aux = aux->next;
        }
    }

    return;
}

extern void imprimirTerminal(nodoD *aux)
{
    nodoCola *auxFIFO;

    auxFIFO = aux->primero;

    printf(YELLOW "Estado de la cola de %s\n" RESET, aux->terminal);
    printf(GREEN "Número de clientes: %d\n" RESET, aux->clientes);
    printf(GREEN "Monto acumulado: $%.2f\n\n" RESET, aux->montoAcumulado);

    if (auxFIFO == NULL)
    {
        printf(GREEN "La cola está vacía\n" RESET);
        return;
    }
    else
    {
        printf(YELLOW "Clientes en la cola:\n" RESET);
        while (auxFIFO != NULL)
        {
            printf(BG_YELLOW BLACK "%d %s %.2f" RESET " -> ", auxFIFO->numCuenta, auxFIFO->nombre, auxFIFO->monedero);
            auxFIFO = auxFIFO->next;
        }
        printf(BG_GREEN "Fin de la cola\n" RESET);
    }

    printf("\n");

    return;
}

extern void imprimirFacturas(nodoD *aux)
{
    return;
}

extern void atenderTerminal(nodoD **terminal)
{
    return;
}

extern void atenderCaja(nodoD **caja)
{
    int cantidad, compraValida = 0;
    float pagar;
    nodoD *colaActual;
    nodoCola *clienteActual;
    // Verificar que la cola no esté vacía
    if (((*caja)->primero == NULL) && ((*caja)->ultimo == NULL))
    {
        printf(GREEN "\nLa caja está vacía\n" RESET);
    }
    else
    {
        colaActual = *caja;
        clienteActual = (*caja)->primero;
        // Atender a la caja eliminara al ultimo cliente de la cola FIFO y se copiaran sus datos a la terminal donde haya comprado
        printf("Atendiendo a %s " GREEN "$%.2f" RESET, clienteActual->nombre, clienteActual->monedero);

        // Bucle para preguntar si el cliente quiere comprar algo, si no quiere, se elimina de la cola.
        // Se irá preguntando producto por producto (Nombre de terminal) y tiene que ingresar la cantidad que quiere comprar
        // Solamente puede comprar un producto por vez.
        do
        {

            // Si la terminal no es Caja, ni Facturacion, se hace todo
            if ((strcmp(colaActual->terminal, "Caja") != 0) && (strcmp(colaActual->terminal, "Facturacion") != 0))
            {
                if (strcmp(colaActual->terminal, "Tacos") == 0)
                {
                    printf("\n%s ($25) cantidad:  ", colaActual->terminal);
                }
                else if (strcmp(colaActual->terminal, "Pizzas") == 0)
                {
                    printf("\n%s ($89) cantidad:  ", colaActual->terminal);
                }
                else
                {
                    printf("\n%s ($0) cantidad:  ", colaActual->terminal);
                }
                scanf(" %d", &cantidad);

                printf("Comprar %d %s\n", cantidad, colaActual->terminal);
                // Si el cliente quiso comprar algo
                if (cantidad > 0)
                {
                    // Validar que el monedero sea suficiente
                    // Los tacos cuestan 25, las pizzas 89 y cualquier otro producto cuesta 0
                    if (strcmp(colaActual->terminal, "Tacos") == 0)
                    {
                        pagar = cantidad * 25;

                        if (pagar <= clienteActual->monedero)
                        {
                            clienteActual->monedero -= pagar;
                            printf(GREEN "\nCompra exitosa\n" RESET);
                            compraValida = 1;
                        }
                        else
                        {
                            printf(RED "\nNo tiene suficiente dinero\n" RESET);
                            compraValida = -1;
                        }
                    }
                    else if (strcmp(colaActual->terminal, "Pizzas") == 0)
                    {
                        pagar = cantidad * 89;
                        if (pagar <= clienteActual->monedero)
                        {
                            clienteActual->monedero -= pagar;
                            printf(GREEN "\nCompra exitosa\n" RESET);
                            compraValida = 1;
                        }
                        else
                        {
                            printf(RED "\nNo tiene suficiente dinero\n" RESET);
                            compraValida = -1;
                        }
                    }
                    else
                    {
                        pagar = 0;
                        if (pagar <= clienteActual->monedero)
                        {
                            clienteActual->monedero -= pagar;
                            printf(GREEN "\nCompra exitosa\n" RESET);
                            compraValida = 1;
                        }
                        else
                        {
                            printf(RED "\nNo tiene suficiente dinero\n" RESET);
                            compraValida = -1;
                        }
                    }

                    // Si la compraValida == 1, se elimina el cliente de la cola y se enviará a la colaActual
                    // Si la compraValida == -1, solamente se eliminará al cliente de la coa
                    if (compraValida == 1)
                    {
                        insertarClienteComida(&colaActual, clienteActual);
                    }
                }
                else
                {
                    colaActual = colaActual->next;
                }
            }
            else
            {
                colaActual = colaActual->next;
            }

        } while (compraValida == 0 && colaActual != NULL);
    }

    return;
}

extern void atenderFacturas(nodoD **terminal)
{
    return;
}

extern void actualizarTerminales(nodoD **first)
{
    // aux debe de modificar los valores de las estructuras del main
    nodoD *aux;

    aux = *first;

    while (aux != NULL)
    {
        // Si es factura, actua diferente al resto de terminales
        if (strcmp(aux->terminal, "Facturacion") == 0)
        {
        }
        else
        {
            // Se actualiza el monto acumulado de la terminal, sumando los monederos de la lista FIFO
            aux->montoAcumulado = sumarMonederos(aux->primero);
            // Se actualiza el número de clientes atendidos
            aux->clientes = sumarClientes(aux->primero);
        }
        aux = aux->next;
    }

    return;
}

extern void existenTerminalesFundamentales(nodoD *aux)
{
    // Debe de existir la terminal Caja y la terminal Facturacion
    int caja = 0, facturacion = 0;
    while (aux != NULL)
    {
        if (strcmp(aux->terminal, "Caja") == 0)
        {
            caja = 1;
        }
        if (strcmp(aux->terminal, "Facturacion") == 0)
        {
            facturacion = 1;
        }
        aux = aux->next;
    }
    if (caja == 0)
    {
        printf(RED "\n\n\tError: No existe la terminal Caja\n\n" RESET);
        exit(1);
    }
    if (facturacion == 0)
    {
        printf(RED "\n\n\tError: No existe la terminal Facturacion\n\n" RESET);
        exit(1);
    }
    return;
}

extern void presioneEnter()
{
    printf("\nPresione " BG_GREEN "ENTER" RESET " para continuar\n");
    getchar();
    system("clear");

    return;
}