#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H

#include "portafolio.h"

struct ResultadoBusqueda
{
    int indice;
    int comparaciones;
    int llamadas;
};

/*
 * Proposito: Busca un proyecto activo por ID usando busqueda secuencial.
 * Parametros:
 *   proyectos: arreglo de proyectos.
 *   cantidad: cantidad de registros cargados.
 *   idBuscado: ID que se desea encontrar.
 * Retorno: estructura con indice encontrado y cantidad de comparaciones.
 */
ResultadoBusqueda buscarSecuencialPorId(const Proyecto proyectos[], int cantidad, int idBuscado);

/*
 * Proposito: Busca un proyecto activo por ID usando busqueda binaria iterativa.
 * Parametros:
 *   proyectos: arreglo ordenado por ID.
 *   cantidad: cantidad de registros cargados.
 *   idBuscado: ID que se desea encontrar.
 * Retorno: estructura con indice encontrado y cantidad de comparaciones.
 */
ResultadoBusqueda buscarBinariaIterativaPorId(const Proyecto proyectos[], int cantidad, int idBuscado);

/*
 * Proposito: Busca un proyecto activo por ID usando busqueda binaria recursiva.
 * Parametros:
 *   proyectos: arreglo ordenado por ID.
 *   cantidad: cantidad de registros cargados.
 *   idBuscado: ID que se desea encontrar.
 * Retorno: estructura con indice encontrado, comparaciones y llamadas recursivas.
 */
ResultadoBusqueda buscarBinariaRecursivaPorId(const Proyecto proyectos[], int cantidad, int idBuscado);

#endif
