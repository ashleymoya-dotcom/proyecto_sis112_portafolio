#include "reportes.h"

#include "archivos.h"
#include "portafolio.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static string escaparTextoPdf(const string &texto)
{
    string resultado;

    for (char caracter : texto)
    {
        if (caracter == '(' || caracter == ')' || caracter == '\\')
            resultado += '\\';
        resultado += caracter;
    }

    return resultado;
}

static void agregarLineaContenido(stringstream &contenido, int x, int y, const string &texto)
{
    contenido << "BT /F1 10 Tf " << x << ' ' << y << " Td (" << escaparTextoPdf(texto) << ") Tj ET\n";
}

static bool escribirPdfSimple(const vector<string> &lineas, const string &ruta)
{
    stringstream contenido;
    int y = 800;

    for (const string &linea : lineas)
    {
        if (y < 40)
            break;
        agregarLineaContenido(contenido, 40, y, linea);
        y -= 18;
    }

    string contenidoPagina = contenido.str();
    vector<string> objetos;

    objetos.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
    objetos.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
    objetos.push_back("3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Resources << /Font << /F1 4 0 R >> >> /Contents 5 0 R >>\nendobj\n");
    objetos.push_back("4 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n");
    objetos.push_back("5 0 obj\n<< /Length " + to_string(contenidoPagina.size()) + " >>\nstream\n" + contenidoPagina + "endstream\nendobj\n");

    ofstream archivo(ruta, ios::binary | ios::trunc);
    if (!archivo.is_open())
        return false;

    vector<long> posiciones;
    archivo << "%PDF-1.4\n";

    for (const string &objeto : objetos)
    {
        posiciones.push_back(static_cast<long>(archivo.tellp()));
        archivo << objeto;
    }

    long inicioXref = static_cast<long>(archivo.tellp());
    archivo << "xref\n";
    archivo << "0 " << objetos.size() + 1 << "\n";
    archivo << "0000000000 65535 f \n";

    for (long posicion : posiciones)
    {
        archivo << setw(10) << setfill('0') << posicion << " 00000 n \n";
    }

    archivo << "trailer\n";
    archivo << "<< /Size " << objetos.size() + 1 << " /Root 1 0 R >>\n";
    archivo << "startxref\n";
    archivo << inicioXref << "\n";
    archivo << "%%EOF\n";

    return archivo.good();
}

void generarReportePdf()
{
    Proyecto proyectos[MAX_REGISTROS];
    int cantidad = 0;
    int activos = 0;
    vector<string> lineas;

    if (!cargarProyectos(proyectos, cantidad) || cantidad == 0)
    {
        cout << "\nNo hay proyectos para generar el reporte.\n";
        return;
    }

    lineas.push_back("REPORTE DEL PORTAFOLIO DIGITAL - SIS-112");
    lineas.push_back("Archivo procesado: data/proyectos.dat");
    lineas.push_back(" ");
    lineas.push_back("ID | Nombre | Categoria | Cliente | Anio | Presupuesto | Estado");
    lineas.push_back("-----------------------------------------------------------------------");

    for (int i = 0; i < cantidad; i++)
    {
        if (!proyectos[i].activo)
            continue;

        stringstream linea;
        linea << proyectos[i].id << " | "
              << proyectos[i].nombre << " | "
              << proyectos[i].categoria << " | "
              << proyectos[i].cliente << " | "
              << proyectos[i].anio << " | Bs. "
              << fixed << setprecision(2) << proyectos[i].presupuesto << " | "
              << proyectos[i].estado;

        lineas.push_back(linea.str());
        activos++;
    }

    lineas.push_back(" ");
    lineas.push_back("Total de registros en archivo: " + to_string(cantidad));
    lineas.push_back("Total de proyectos activos: " + to_string(activos));

    if (escribirPdfSimple(lineas, ARCHIVO_REPORTE_PDF))
        cout << "\nReporte PDF generado correctamente en " << ARCHIVO_REPORTE_PDF << "\n";
    else
        cout << "\nNo se pudo generar el reporte PDF.\n";
}
