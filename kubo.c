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

// Main ---------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    // argv[1] debe ser el archivo clientes.txt
    // argv[2] debe ser el archivo negocio.txt

    // Inicio Personalizado-----------------------------------------------------------
    printf("Presione ENTER para continuar\n");
    getchar();
    system("clear");
    printf("\n\n\tEste código fue creado por Mario Ureña García, Ricardo Ponce de León Vargas y Emiliano Cisneros Cervantes\n\n");
    //-------------------------------------------------------------------------------------
    // Variables

    // Procesos

    // FINALIZACIÓN DEL PROGRAMA
    printf("\n\n\tPrograma Finalizado con ÉXITO\n\n");
    return 0;
}
