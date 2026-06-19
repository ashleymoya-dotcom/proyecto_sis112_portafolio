#include "busquedas.h"

ResultadoBusqueda buscarSecuencialPorId(const Proyecto proyectos[], int cantidad, int idBuscado)
{
    ResultadoBusqueda resultado = {-1, 0, 0};

    for (int i = 0; i < cantidad; i++)
    {
        if (!proyectos[i].activo)
            continue;

        resultado.comparaciones++;
        if (proyectos[i].id == idBuscado)
        {
            resultado.indice = i;
            return resultado;
        }
    }

    return resultado;
}

ResultadoBusqueda buscarBinariaIterativaPorId(const Proyecto proyectos[], int cantidad, int idBuscado)
{
    ResultadoBusqueda resultado = {-1, 0, 0};
    int izquierda = 0;
    int derecha = cantidad - 1;

    while (izquierda <= derecha)
    {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (!proyectos[medio].activo)
        {
            resultado.comparaciones++;
            izquierda = medio + 1;
            continue;
        }

        resultado.comparaciones++;
        if (proyectos[medio].id == idBuscado)
        {
            resultado.indice = medio;
            return resultado;
        }

        if (proyectos[medio].id < idBuscado)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }

    return resultado;
}

static int buscarBinariaRecursivaInterna(const Proyecto proyectos[], int izquierda, int derecha, int idBuscado, int &comparaciones, int &llamadas)
{
    llamadas++;

    if (izquierda > derecha)
        return -1;

    int medio = izquierda + (derecha - izquierda) / 2;

    if (!proyectos[medio].activo)
    {
        comparaciones++;
        return buscarBinariaRecursivaInterna(proyectos, medio + 1, derecha, idBuscado, comparaciones, llamadas);
    }

    comparaciones++;
    if (proyectos[medio].id == idBuscado)
        return medio;

    if (proyectos[medio].id < idBuscado)
        return buscarBinariaRecursivaInterna(proyectos, medio + 1, derecha, idBuscado, comparaciones, llamadas);

    return buscarBinariaRecursivaInterna(proyectos, izquierda, medio - 1, idBuscado, comparaciones, llamadas);
}

ResultadoBusqueda buscarBinariaRecursivaPorId(const Proyecto proyectos[], int cantidad, int idBuscado)
{
    ResultadoBusqueda resultado = {-1, 0, 0};
    resultado.indice = buscarBinariaRecursivaInterna(proyectos, 0, cantidad - 1, idBuscado, resultado.comparaciones, resultado.llamadas);
    return resultado;
}
