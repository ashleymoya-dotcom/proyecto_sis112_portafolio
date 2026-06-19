#include "archivos.h"

#include "utilidades.h"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

void asegurarCarpetaDatos()
{
    filesystem::create_directories("data");
}

bool cargarProyectos(Proyecto proyectos[], int &cantidad)
{
    asegurarCarpetaDatos();
    ifstream archivo(ARCHIVO_PROYECTOS, ios::binary);
    cantidad = 0;

    if (!archivo.is_open())
        return false;

    Proyecto proyecto;
    while (cantidad < MAX_REGISTROS && archivo.read(reinterpret_cast<char *>(&proyecto), sizeof(Proyecto)))
    {
        proyectos[cantidad] = proyecto;
        cantidad++;
    }

    return true;
}

bool guardarProyectos(const Proyecto proyectos[], int cantidad)
{
    asegurarCarpetaDatos();
    ofstream archivo(ARCHIVO_PROYECTOS, ios::binary | ios::trunc);

    if (!archivo.is_open())
        return false;

    for (int i = 0; i < cantidad; i++)
    {
        archivo.write(reinterpret_cast<const char *>(&proyectos[i]), sizeof(Proyecto));
    }

    return archivo.good();
}

int obtenerSiguienteId(const Proyecto proyectos[], int cantidad)
{
    int mayorId = 0;

    for (int i = 0; i < cantidad; i++)
    {
        if (proyectos[i].id > mayorId)
            mayorId = proyectos[i].id;
    }

    return mayorId + 1;
}

void inicializarDatosDePrueba()
{
    asegurarCarpetaDatos();

    if (filesystem::exists(ARCHIVO_PROYECTOS) && filesystem::file_size(ARCHIVO_PROYECTOS) > 0)
        return;

    Proyecto proyectos[10] = {};

    proyectos[0] = {1, "Sistema de Inventario", "Software", "Comercial Andina", 2024, 3500.0f, "Terminado", true};
    proyectos[1] = {2, "Pagina Web Institucional", "Web", "Colegio Central", 2025, 1800.0f, "En progreso", true};
    proyectos[2] = {3, "App de Reservas", "Movil", "Hotel Sol", 2025, 4200.0f, "Planificado", true};
    proyectos[3] = {4, "Base de Datos Clientes", "Datos", "Tienda Norte", 2023, 2500.0f, "Terminado", true};
    proyectos[4] = {5, "Dashboard de Ventas", "Analitica", "Distribuidora Sur", 2024, 3900.0f, "En progreso", true};
    proyectos[5] = {6, "Sistema de Biblioteca", "Software", "Universidad Local", 2022, 3100.0f, "Terminado", true};
    proyectos[6] = {7, "Control de Asistencia", "Software", "Instituto Tecnico", 2025, 2750.0f, "Planificado", true};
    proyectos[7] = {8, "Catalogo Digital", "Web", "Artesanias Moya", 2024, 1600.0f, "Terminado", true};
    proyectos[8] = {9, "Registro de Pacientes", "Salud", "Clinica Vida", 2023, 5200.0f, "En progreso", true};
    proyectos[9] = {10, "Reporte Academico", "Educacion", "SIS-112", 2026, 1200.0f, "Terminado", true};

    if (!guardarProyectos(proyectos, 10))
        cout << "No se pudo crear el archivo inicial de datos.\n";
}
