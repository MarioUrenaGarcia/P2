/**
 * @file defKubo.h
 * @brief Este es el header file de kubo.c
 * @date 04/04/2025
 * @author Mario Ureña García, Ricardo Ponce de León Vargas y Emiliano Cisneros Cervantes
 */

// Bibliotecas --------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiciones -------------------------------------------------------------------------
#define RED "\x1b[31m"
#define WHITE "\x1B[37m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"
#define CYAN "\x1b[36m"

// Declaración de estructuras -------------------------------------------------------------

struct factura
{
    int numFactura;
    char nombre[20];
    char compra[20];
    float totalFacturado;
    struct factura *next;
};
typedef struct factura nodoFactura;

struct cola
{
    int numCuenta;
    char nombre[20];
    float monedero;
    struct cola *next;
};
typedef struct cola nodoCola;

struct listaDoble
{
    char terminal[20];
    int clientes;
    float montoAcumulado;
    struct listaDoble *back, *next;

    nodoCola *first, *last;
    nodoFactura *top;
};
typedef struct listaDoble nodoLD;