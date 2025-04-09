/**
 * @file kubo.c
 * @brief En este archivo se almacenan las funciones de kubo.c
 * @date 04/04/2025
 * @author Mario Ureña García, Ricardo Ponce de León Vargas y Emiliano Cisneros Cervantes
 */

// Funciones ----------------------------------------------------------------------------

#include "defKubo.h"


/**
 * @brief
 * @date
 * @author
 * @param
 * @return
 * @Ejemplo
 */
int menuOpciones(nodoD *aux)
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

        system("clear");

        if (validez == 1)
        {
            printf(RED "\nOpción inválida. Intente de nuevo.\n" RESET);
        }
        printf(GREEN "1." RESET " Imprimir estado de todas las colas\n");
        while (aux != NULL)
        {
            printf(CYAN "%d." RESET " Imprimir cola de %s\n", i, aux->terminal);
            i++;
            printf(YELLOW "%d." RESET " Atender cola de %s\n", i + 1, aux->terminal);
            aux = aux->next;
            i++;
        }
        printf(BG_WHITE BLACK "0. Salir\n" RESET);
        printf("\nElija una opción: ");
        scanf("%d", &opcion);

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

    return opcion;
}

/**
 * @brief
 * @date
 * @author
 * @param
 * @return
 * @Ejemplo
 */
void insertarColaD(nodoD **first, nodoD **last, char nombreCola[], int tickets, float total)
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

/**
 * @brief
 * @date
 * @author
 * @param
 * @return
 * @Ejemplo
 */
void imprimirListaD(nodoD *aux)
{
    printf(YELLOW "\nImpresión de la lista Doble\n" RESET);

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
            printf(GREEN "Monto acumulado:" RESET " %.2f\n", aux->montoAcumulado);
            aux = aux->next;
        }
    }

    return;
}