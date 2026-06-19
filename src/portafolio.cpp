#include "portafolio.h"

#include "archivos.h"
#include "busquedas.h"
#include "ordenamientos.h"
#include "reportes.h"
#include "utilidades.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void mostrarProyecto(const Proyecto &proyecto)
{
    cout << "----------------------------------------\n";
    cout << "ID          : " << proyecto.id << "\n";
    cout << "Nombre      : " << proyecto.nombre << "\n";
    cout << "Categoria   : " << proyecto.categoria << "\n";
    cout << "Cliente     : " << proyecto.cliente << "\n";
    cout << "Anio        : " << proyecto.anio << "\n";
    cout << fixed << setprecision(2);
    cout << "Presupuesto : Bs. " << proyecto.presupuesto << "\n";
    cout << "Estado      : " << proyecto.estado << "\n";
    cout << "----------------------------------------\n";
}

void agregarProyecto()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;

    cargarProyectos(proyectos, cantidad);

    if (cantidad >= MAX_REGISTROS)
    {
        cout << "\nNo se pueden agregar mas proyectos. Limite alcanzado.\n";
        return;
    }

    Proyecto nuevo = {};
    nuevo.id = obtenerSiguienteId(proyectos, cantidad);
    nuevo.activo = true;

    cout << "\nAGREGAR PROYECTO\n";
    cout << "ID asignado automaticamente: " << nuevo.id << "\n\n";

    copiarTexto(nuevo.nombre, 50, leerTexto("Nombre del proyecto : "));
    copiarTexto(nuevo.categoria, 40, leerTexto("Categoria           : "));
    copiarTexto(nuevo.cliente, 50, leerTexto("Cliente             : "));
    nuevo.anio = leerEntero("Anio                : ");
    nuevo.presupuesto = leerFlotante("Presupuesto (Bs.)   : ");
    copiarTexto(nuevo.estado, 30, leerTexto("Estado              : "));

    proyectos[cantidad] = nuevo;
    cantidad++;

    if (guardarProyectos(proyectos, cantidad))
        cout << "\nProyecto agregado correctamente.\n";
    else
        cout << "\nNo se pudo guardar el proyecto.\n";
}

void listarProyectos()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;
    int activos = 0;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos registrados.\n";
        return;
    }

    cout << "\nLISTA DE PROYECTOS ACTIVOS\n\n";

    for (int i = 0; i < cantidad; i++)
    {
        if (proyectos[i].activo)
        {
            mostrarProyecto(proyectos[i]);
            activos++;
        }
    }

    if (activos == 0)
        cout << "No hay proyectos activos para mostrar.\n";
    else
        cout << "\nTotal de proyectos activos: " << activos << "\n";
}

void modificarProyecto()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos registrados para modificar.\n";
        return;
    }

    int id = leerEntero("\nIngresa el ID del proyecto a modificar: ");
    ResultadoBusqueda resultado = buscarSecuencialPorId(proyectos, cantidad, id);

    if (resultado.indice == -1)
    {
        cout << "\nNo se encontro un proyecto activo con ese ID.\n";
        cout << "Comparaciones realizadas: " << resultado.comparaciones << "\n";
        return;
    }

    Proyecto &proyecto = proyectos[resultado.indice];
    cout << "\nProyecto encontrado:\n";
    mostrarProyecto(proyecto);
    cout << "Comparaciones realizadas: " << resultado.comparaciones << "\n\n";
    cout << "Deja el campo vacio para conservar el valor actual.\n\n";

    string texto;

    texto = leerTexto("Nombre [" + string(proyecto.nombre) + "]: ");
    if (!texto.empty())
        copiarTexto(proyecto.nombre, 50, texto);

    texto = leerTexto("Categoria [" + string(proyecto.categoria) + "]: ");
    if (!texto.empty())
        copiarTexto(proyecto.categoria, 40, texto);

    texto = leerTexto("Cliente [" + string(proyecto.cliente) + "]: ");
    if (!texto.empty())
        copiarTexto(proyecto.cliente, 50, texto);

    texto = leerTexto("Anio [" + to_string(proyecto.anio) + "]: ");
    if (!texto.empty())
        proyecto.anio = stoi(texto);

    texto = leerTexto("Presupuesto actual, ingresa nuevo valor o Enter para conservar: ");
    if (!texto.empty())
        proyecto.presupuesto = stof(texto);

    texto = leerTexto("Estado [" + string(proyecto.estado) + "]: ");
    if (!texto.empty())
        copiarTexto(proyecto.estado, 30, texto);

    if (guardarProyectos(proyectos, cantidad))
        cout << "\nProyecto modificado correctamente.\n";
    else
        cout << "\nNo se pudo guardar la modificacion.\n";
}

void eliminarProyecto()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos registrados para eliminar.\n";
        return;
    }

    int id = leerEntero("\nIngresa el ID del proyecto a eliminar: ");
    ResultadoBusqueda resultado = buscarSecuencialPorId(proyectos, cantidad, id);

    if (resultado.indice == -1)
    {
        cout << "\nNo se encontro un proyecto activo con ese ID.\n";
        cout << "Comparaciones realizadas: " << resultado.comparaciones << "\n";
        return;
    }

    cout << "\nProyecto seleccionado:\n";
    mostrarProyecto(proyectos[resultado.indice]);

    if (!confirmar("Estas seguro que deseas eliminarlo? (s/n): "))
    {
        cout << "\nOperacion cancelada.\n";
        return;
    }

    proyectos[resultado.indice].activo = false;

    if (guardarProyectos(proyectos, cantidad))
        cout << "\nProyecto eliminado mediante baja logica.\n";
    else
        cout << "\nNo se pudo guardar la eliminacion.\n";
}

static void buscarProyectoIterativo()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos para buscar.\n";
        return;
    }

    ordenarBubbleOptimizadoPorId(proyectos, cantidad);
    int id = leerEntero("\nID a buscar con busqueda binaria iterativa: ");
    ResultadoBusqueda resultado = buscarBinariaIterativaPorId(proyectos, cantidad, id);

    if (resultado.indice != -1)
    {
        cout << "\nProyecto encontrado:\n";
        mostrarProyecto(proyectos[resultado.indice]);
    }
    else
    {
        cout << "\nNo se encontro un proyecto activo con ese ID.\n";
    }

    cout << "Comparaciones realizadas: " << resultado.comparaciones << "\n";
}

static void buscarProyectoRecursivo()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos para buscar.\n";
        return;
    }

    ordenarBubbleOptimizadoPorId(proyectos, cantidad);
    int id = leerEntero("\nID a buscar con busqueda binaria recursiva: ");
    ResultadoBusqueda resultado = buscarBinariaRecursivaPorId(proyectos, cantidad, id);

    if (resultado.indice != -1)
    {
        cout << "\nProyecto encontrado:\n";
        mostrarProyecto(proyectos[resultado.indice]);
    }
    else
    {
        cout << "\nNo se encontro un proyecto activo con ese ID.\n";
    }

    cout << "Comparaciones realizadas: " << resultado.comparaciones << "\n";
    cout << "Llamadas recursivas    : " << resultado.llamadas << "\n";
}

static void mostrarMenu()
{
    cout << "========================================\n";
    cout << " PORTAFOLIO DIGITAL - SIS-112\n";
    cout << "========================================\n";
    cout << "1. Agregar proyecto\n";
    cout << "2. Listar proyectos\n";
    cout << "3. Modificar proyecto\n";
    cout << "4. Eliminar proyecto\n";
    cout << "5. Ordenar por ID con Bubble Sort\n";
    cout << "6. Reporte comparativo de ordenamiento\n";
    cout << "7. Busqueda binaria iterativa\n";
    cout << "8. Busqueda binaria recursiva\n";
    cout << "9. Generar reporte PDF\n";
    cout << "0. Salir\n";
    cout << "========================================\n";
}

void ejecutarMenuPrincipal()
{
    int opcion;

    do
    {
        limpiarPantalla();
        mostrarMenu();
        opcion = leerEntero("Opcion: ");
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            agregarProyecto();
            break;
        case 2:
            listarProyectos();
            break;
        case 3:
            modificarProyecto();
            break;
        case 4:
            eliminarProyecto();
            break;
        case 5:
            ordenarArchivoPorBubble();
            break;
        case 6:
            mostrarReporteComparativoOrdenamiento();
            break;
        case 7:
            buscarProyectoIterativo();
            break;
        case 8:
            buscarProyectoRecursivo();
            break;
        case 9:
            generarReportePdf();
            break;
        case 0:
            cout << "\nHasta luego.\n";
            break;
        default:
            cout << "\nOpcion invalida. Elige entre 0 y 9.\n";
            break;
        }

        if (opcion != 0)
            pausar();

    } while (opcion != 0);
}
