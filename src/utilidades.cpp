#include "utilidades.h"

#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

void limpiarPantalla()
{
    for (int i = 0; i < 35; i++)
        cout << '\n';
}

void pausar()
{
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int leerEntero(const string &mensaje)
{
    int valor;

    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "  Entrada invalida. Ingresa un numero entero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float leerFlotante(const string &mensaje)
{
    float valor;

    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "  Entrada invalida. Ingresa un numero decimal.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerTexto(const string &mensaje)
{
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

void copiarTexto(char destino[], int capacidad, const string &origen)
{
    if (capacidad <= 0)
        return;

    strncpy(destino, origen.c_str(), static_cast<size_t>(capacidad - 1));
    destino[capacidad - 1] = '\0';
}

bool confirmar(const string &mensaje)
{
    string respuesta = leerTexto(mensaje);
    return respuesta == "s" || respuesta == "S";
}
