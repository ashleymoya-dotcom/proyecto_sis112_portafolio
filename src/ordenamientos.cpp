#include "ordenamientos.h"

#include "archivos.h"

#include <iostream>

using namespace std;

EstadisticaOrdenamiento ordenarBubbleOptimizadoPorId(Proyecto proyectos[], int cantidad)
{
    EstadisticaOrdenamiento estadistica = {0, 0};
    bool huboIntercambio = true;

    for (int i = 0; i < cantidad - 1 && huboIntercambio; i++)
    {
        huboIntercambio = false;

        for (int j = 0; j < cantidad - 1 - i; j++)
        {
            estadistica.comparaciones++;
            if (proyectos[j].id > proyectos[j + 1].id)
            {
                Proyecto temporal = proyectos[j];
                proyectos[j] = proyectos[j + 1];
                proyectos[j + 1] = temporal;
                estadistica.intercambios++;
                huboIntercambio = true;
            }
        }
    }

    return estadistica;
}

static void mezclarPorId(Proyecto proyectos[], Proyecto auxiliar[], int izquierda, int medio, int derecha, EstadisticaOrdenamiento &estadistica)
{
    int i = izquierda;
    int j = medio + 1;
    int k = izquierda;

    while (i <= medio && j <= derecha)
    {
        estadistica.comparaciones++;
        if (proyectos[i].id <= proyectos[j].id)
        {
            auxiliar[k] = proyectos[i];
            i++;
        }
        else
        {
            auxiliar[k] = proyectos[j];
            j++;
        }
        estadistica.intercambios++;
        k++;
    }

    while (i <= medio)
    {
        auxiliar[k] = proyectos[i];
        estadistica.intercambios++;
        i++;
        k++;
    }

    while (j <= derecha)
    {
        auxiliar[k] = proyectos[j];
        estadistica.intercambios++;
        j++;
        k++;
    }

    for (int posicion = izquierda; posicion <= derecha; posicion++)
    {
        proyectos[posicion] = auxiliar[posicion];
    }
}

static void ordenarIntercalacionInterna(Proyecto proyectos[], Proyecto auxiliar[], int izquierda, int derecha, EstadisticaOrdenamiento &estadistica)
{
    if (izquierda >= derecha)
        return;

    int medio = izquierda + (derecha - izquierda) / 2;
    ordenarIntercalacionInterna(proyectos, auxiliar, izquierda, medio, estadistica);
    ordenarIntercalacionInterna(proyectos, auxiliar, medio + 1, derecha, estadistica);
    mezclarPorId(proyectos, auxiliar, izquierda, medio, derecha, estadistica);
}

EstadisticaOrdenamiento ordenarPorIntercalacion(Proyecto proyectos[], int cantidad)
{
    EstadisticaOrdenamiento estadistica = {0, 0};

    if (cantidad <= 1)
        return estadistica;

    Proyecto auxiliar[MAX_REGISTROS];
    ordenarIntercalacionInterna(proyectos, auxiliar, 0, cantidad - 1, estadistica);
    return estadistica;
}

void mostrarReporteComparativoOrdenamiento()
{
    Proyecto proyectosOriginales[MAX_REGISTROS];
    Proyecto copiaBubble[MAX_REGISTROS];
    Proyecto copiaIntercalacion[MAX_REGISTROS];
    int cantidad = 0;

    if (!cargarProyectos(proyectosOriginales, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay datos disponibles para comparar ordenamientos.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++)
    {
        copiaBubble[i] = proyectosOriginales[i];
        copiaIntercalacion[i] = proyectosOriginales[i];
    }

    EstadisticaOrdenamiento bubble = ordenarBubbleOptimizadoPorId(copiaBubble, cantidad);
    EstadisticaOrdenamiento intercalacion = ordenarPorIntercalacion(copiaIntercalacion, cantidad);

    cout << "\nREPORTE COMPARATIVO DE ORDENAMIENTO\n";
    cout << "-----------------------------------\n";
    cout << "Bubble Sort optimizado\n";
    cout << "Comparaciones : " << bubble.comparaciones << "\n";
    cout << "Intercambios  : " << bubble.intercambios << "\n\n";
    cout << "Intercalacion\n";
    cout << "Comparaciones : " << intercalacion.comparaciones << "\n";
    cout << "Movimientos   : " << intercalacion.intercambios << "\n\n";

    if (bubble.comparaciones < intercalacion.comparaciones)
        cout << "Metodo mas eficiente por comparaciones: Bubble Sort optimizado.\n";
    else if (intercalacion.comparaciones < bubble.comparaciones)
        cout << "Metodo mas eficiente por comparaciones: Intercalacion.\n";
    else
        cout << "Ambos metodos realizaron la misma cantidad de comparaciones.\n";
}

void ordenarArchivoPorBubble()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos para ordenar.\n";
        return;
    }

    EstadisticaOrdenamiento estadistica = ordenarBubbleOptimizadoPorId(proyectos, cantidad);

    if (!guardarProyectos(proyectos, cantidad))
    {
        cout << "\nNo se pudo guardar el archivo ordenado.\n";
        return;
    }

    cout << "\nProyectos ordenados por ID y guardados correctamente.\n";
    cout << "Comparaciones: " << estadistica.comparaciones << "\n";
    cout << "Intercambios : " << estadistica.intercambios << "\n";
}
