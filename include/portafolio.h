#ifndef PORTAFOLIO_H
#define PORTAFOLIO_H

const int MAX_REGISTROS = 100;
const char ARCHIVO_PROYECTOS[] = "data/proyectos.dat";
const char ARCHIVO_REPORTE_PDF[] = "data/reporte_portafolio.pdf";

struct Proyecto
{
    int id;
    char nombre[50];
    char categoria[40];
    char cliente[50];
    int anio;
    float presupuesto;
    char estado[30];
    bool activo;
};

/*
 * Proposito: Ejecuta el menu principal del sistema y coordina las opciones disponibles.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void ejecutarMenuPrincipal();

/*
 * Proposito: Solicita datos al usuario y agrega un nuevo proyecto al archivo binario.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void agregarProyecto();

/*
 * Proposito: Muestra en consola todos los proyectos activos almacenados en el archivo binario.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void listarProyectos();

/*
 * Proposito: Busca un proyecto por ID y permite actualizar sus datos principales.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void modificarProyecto();

/*
 * Proposito: Elimina un proyecto mediante baja logica, marcandolo como inactivo.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void eliminarProyecto();

/*
 * Proposito: Muestra los datos completos de un proyecto en formato legible.
 * Parametros:
 *   proyecto: proyecto que se desea mostrar.
 * Retorno: No retorna valor.
 */
void mostrarProyecto(const Proyecto &proyecto);

#endif
