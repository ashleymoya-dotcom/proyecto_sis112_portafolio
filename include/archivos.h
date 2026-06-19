#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "portafolio.h"

/*
 * Proposito: Crea la carpeta de datos cuando no existe.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void asegurarCarpetaDatos();

/*
 * Proposito: Carga automaticamente registros de prueba cuando el archivo binario no existe o esta vacio.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void inicializarDatosDePrueba();

/*
 * Proposito: Carga los proyectos activos e inactivos desde el archivo binario hacia un arreglo.
 * Parametros:
 *   proyectos: arreglo donde se cargaran los registros.
 *   cantidad: variable por referencia donde se guarda la cantidad leida.
 * Retorno: true si la lectura fue correcta, false si hubo error.
 */
bool cargarProyectos(Proyecto proyectos[], int &cantidad);

/*
 * Proposito: Guarda un arreglo completo de proyectos en el archivo binario.
 * Parametros:
 *   proyectos: arreglo de proyectos que se desea guardar.
 *   cantidad: cantidad de proyectos en el arreglo.
 * Retorno: true si el guardado fue correcto, false si hubo error.
 */
bool guardarProyectos(const Proyecto proyectos[], int cantidad);

/*
 * Proposito: Calcula el siguiente ID disponible a partir de los registros cargados.
 * Parametros:
 *   proyectos: arreglo de proyectos existente.
 *   cantidad: cantidad de proyectos cargados.
 * Retorno: siguiente ID disponible.
 */
int obtenerSiguienteId(const Proyecto proyectos[], int cantidad);

#endif
