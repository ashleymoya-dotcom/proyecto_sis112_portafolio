#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

/*
 * Proposito: Limpia visualmente la consola usando saltos de linea.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void limpiarPantalla();

/*
 * Proposito: Detiene el programa hasta que el usuario presione Enter.
 * Parametros: Ninguno.
 * Retorno: No retorna valor.
 */
void pausar();

/*
 * Proposito: Lee un numero entero validado desde consola.
 * Parametros:
 *   mensaje: texto que se muestra al usuario.
 * Retorno: numero entero ingresado.
 */
int leerEntero(const std::string &mensaje);

/*
 * Proposito: Lee un numero decimal validado desde consola.
 * Parametros:
 *   mensaje: texto que se muestra al usuario.
 * Retorno: numero decimal ingresado.
 */
float leerFlotante(const std::string &mensaje);

/*
 * Proposito: Lee una linea de texto desde consola.
 * Parametros:
 *   mensaje: texto que se muestra al usuario.
 * Retorno: texto ingresado.
 */
std::string leerTexto(const std::string &mensaje);

/*
 * Proposito: Copia un texto de std::string a un arreglo char de tamano fijo.
 * Parametros:
 *   destino: arreglo char donde se copiara el texto.
 *   capacidad: tamano maximo del arreglo destino.
 *   origen: texto original.
 * Retorno: No retorna valor.
 */
void copiarTexto(char destino[], int capacidad, const std::string &origen);

/*
 * Proposito: Solicita confirmacion simple al usuario.
 * Parametros:
 *   mensaje: pregunta que se muestra al usuario.
 * Retorno: true si el usuario responde s o S, false en otro caso.
 */
bool confirmar(const std::string &mensaje);

#endif
