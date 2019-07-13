#include <iostream>
#include <limits>

using namespace std;

void Procedencia(bool **P, int **C, int &L, int &n, int *T)
{
    const int infinito = numeric_limits<int>::max(); //M�ximo valor que puede almacenar un Int.
    int i, j;
    for (i = 0; i < n; i++)
    {
        P[i][0] = false;
        C[i][0] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 1; j <= L; j++)
        {
            if (i == 0 && j < T[i])
            {
                C[i][j] = infinito;
                P[i][j] = false;
            }
            else if (i == 0)
            {
                C[i][j] = 1 + C[i][j - T[0]];
                P[i][j] = true;
            }
            else if (j < T[i])
            {
                C[i][j] = C[i - 1][j];
                P[i][j] = false;
            }
            else
            {
                C[i][j] = min(C[i - 1][j], 1 + C[i][j - T[i]]);
                P[i][j] = C[i][j] != C[i - 1][j];
            }
        }
    }
}

void Monedas(bool **P, int **C, int &L, int &n, int *T, int *monedas)
{
    int i = n - 1;
    int j = L;
    for (int ind = 0; ind < n; ind++)
    {
        monedas[ind] = 0;
    }
    while (i != -1 && j != 0)
    {
        if (P[i][j] == false)
        {
            i--;
        }
        else
        {
            monedas[i] = monedas[i] + 1;
            j = j - T[i];
        }
    }
    if (i == 0)
    {
        monedas[0] = C[i][j] + monedas[0];
    }
}

void imprimirSolucion(int *T, int *monedas, int &n)
{
    for (int i = 0; i < n; i++)
    {
        if (monedas[i] != 0)
        {
            cout << " cantidad: " << monedas[i] << " de tipo " << T[i] << endl;
        }
    }
}

void problemaCambio(int &L)
{
    int T[] = {1,2,5,6,10}; //Arreglo tipos de monedas, tienen que estar ordenadas de menor a mayor monto.
    int n = sizeof(T) / sizeof(T[0]); //Cantidad de tipos de monedas almacenados en T.
    int monedas[n]; //Arreglo soluci�n para indicar la cantidad que se toma por cada moneda T[i].
    int **C = new int *[n]; //Matriz que almacena los c�lculos para obtener el n�mero m�nimo de monedas.
    bool **P = new bool *[n]; //Matriz booleana que indica si se ha tomado la moneda T[i] en el valor C[i][j].

    //Creaci�n de matrices din�micas.
    for (int i = 0; i < n; i++)
    {
        C[i] = new int[L + 1];
        P[i] = new bool[L + 1];
    }

    Procedencia(P, C, L, n, T);
    Monedas(P, C, L, n, T, monedas);
    imprimirSolucion(T,monedas,n);

    //Limpia la memoria, eliminando las matrices din�micas creadas anteriormente.
    for (int i = 0; i < n; i++)
    {
        delete[] C[i];
        delete[] P[i];
    }
    delete[] C;
    delete[] P;
}

int main()
{
    int L;
    cout << "Ingrese cantidad a cambiar: ";
    cin >> L;
    problemaCambio(L);
    return 0;
}