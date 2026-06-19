#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include "portafolio.h"

struct EstadisticaOrdenamiento
{
    int comparaciones;
    int intercambios;
};

/*
 * Proposito: Ordena proyectos por ID usando Bubble Sort optimizado.
 * Parametros:
 *   proyectos: arreglo de proyectos que se ordenara.
 *   cantidad: cantidad de registros cargados.
 * Retorno: estadisticas de comparaciones e intercambios.
 */
EstadisticaOrdenamiento ordenarBubbleOptimizadoPorId(Proyecto proyectos[], int cantidad);

/*
 * Proposito: Ordena proyectos por ID usando ordenamiento por intercalacion.
 * Parametros:
 *   proyectos: arreglo de proyectos que se ordenara.
 *   cantidad: cantidad de registros cargados.
 * Retorno: estadisticas de comparaciones y movimientos.
 */
EstadisticaOrdenamiento ordenarPorIntercalacion(Proyecto proyectos[], int cantidad);

/*
 * Proposito: Compara Bubble Sort optimizado contra Intercalacion usando los datos cargados.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void mostrarReporteComparativoOrdenamiento();

/*
 * Proposito: Ordena los datos reales por ID y guarda el resultado en el archivo binario.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void ordenarArchivoPorBubble();

#endif
