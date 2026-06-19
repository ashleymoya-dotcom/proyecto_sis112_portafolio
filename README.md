# Portafolio Digital SIS-112

## Caratula

**Materia:** SIS-112  
**Proyecto:** Portafolio Digital de Proyectos  
**Integrante:** Moya Ashley
**Gestion:** 2026

## Descripcion del dominio de datos

El sistema administra proyectos de un portafolio digital. Cada registro representa un proyecto realizado o planificado, incluyendo datos como nombre, categoria, cliente, anio, presupuesto y estado.

El programa permite crear, listar, modificar, eliminar, buscar, ordenar y reportar proyectos usando archivos binarios.

## Struct principal utilizado

```cpp
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
```

El campo `activo` se utiliza para realizar baja logica. Cuando un proyecto se elimina, no se borra fisicamente del archivo, sino que queda marcado como inactivo.

## Estructura del proyecto

```text
proyecto_sis112/
├── include/          archivos .h con structs y prototipos
├── src/              archivos .cpp con implementaciones
├── data/             archivos binarios y reportes generados
├── main.cpp          solo llamadas principales
└── README.md
```

## Modulos implementados

- `portafolio`: menu principal y CRUD de proyectos.
- `archivos`: carga, guardado binario y seeding de datos.
- `busquedas`: busqueda secuencial, binaria iterativa y binaria recursiva.
- `ordenamientos`: Bubble Sort optimizado e Intercalacion con estadisticas.
- `reportes`: generacion de reporte PDF.
- `utilidades`: lectura validada, pausa, limpieza y funciones auxiliares.

## Compilacion

Desde la carpeta `proyecto_sis112`, ejecutar:

En PowerShell:

```powershell
$fuentes = Get-ChildItem .\src\*.cpp | ForEach-Object { $_.FullName }
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp $fuentes -o proyecto.exe
```

En Git Bash, MSYS2 o terminal compatible con comodines:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o proyecto.exe
```

## Ejecucion

```bash
./proyecto.exe
```

En Windows tambien se puede ejecutar:

```bash
proyecto.exe
```

## Guia rapida de uso

Al iniciar, el sistema crea automaticamente el archivo `data/proyectos.dat` con 10 registros de prueba si el archivo no existe o esta vacio.

Opciones principales:

1. Agregar proyecto.
2. Listar proyectos activos.
3. Modificar proyecto por ID.
4. Eliminar proyecto mediante baja logica.
5. Ordenar por ID con Bubble Sort optimizado.
6. Ver reporte comparativo entre Bubble Sort e Intercalacion.
7. Buscar por ID con busqueda binaria iterativa.
8. Buscar por ID con busqueda binaria recursiva.
9. Generar reporte PDF en `data/reporte_portafolio.pdf`.
0. Salir.

## Requisitos cubiertos

- Programacion modular con librerias `.h` y `.cpp`.
- Uso de parametros por referencia.
- Retorno multiple mediante structs de resultado.
- Bubble Sort optimizado con conteo de comparaciones e intercambios.
- Ordenamiento por Intercalacion con conteo de comparaciones y movimientos.
- Busqueda binaria iterativa y recursiva.
- Carga minima automatizada de 10 registros.
- CRUD completo sobre archivo binario.
- Reporte exportable en PDF.
