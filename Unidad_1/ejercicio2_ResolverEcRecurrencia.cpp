#include <iostream>
#include <vector>
using namespace std;

// Función para calcular términos de una recurrencia lineal homogénea
vector<double> resolverRecurrencia(int grado, const vector<double>& coeficientes,
                                   const vector<double>& condicionesIniciales, int n) {
    vector<double> solucion(n + 1);

    // Copiar condiciones iniciales
    for (int i = 0; i < grado; i++) {
        solucion[i] = condicionesIniciales[i];
    }

    // Calcular los siguientes términos
    for (int i = grado; i <= n; i++) {
        solucion[i] = 0;
        for (int j = 1; j <= grado; j++) {
            solucion[i] += coeficientes[j - 1] * solucion[i - j];
        }
    }

    return solucion;
}

int main() {
    int grado;
    cout << "Grado de la recurrencia (1 a 3): ";
    cin >> grado;

    if (grado < 1 || grado > 3) {
        cout << "Grado no soportado.\n";
        return 1;
    }

    vector<double> coef(grado), cond(grado);
    cout << "Ingrese los coeficientes (de a(n-1) a a(n-" << grado << ")):\n";
    for (int i = 0; i < grado; i++) {
        cout << "  coeficiente a(n-" << i + 1 << "): ";
        cin >> coef[i];
    }

    cout << "Ingrese las condiciones iniciales:\n";
    for (int i = 0; i < grado; i++) {
        cout << "  a(" << i << "): ";
        cin >> cond[i];
    }

    int n;
    cout << "Ingrese el valor de n hasta el cual desea calcular: ";
    cin >> n;
    if (n < grado) {
        cout << "n debe ser al menos " << grado << ".\n";
        return 1;
    }

    int m;
    cout << "Ingrese el valor de m (termino inicial a mostrar, 0 <= m <= n): ";
    cin >> m;
    if (m < 0 || m > n) {
        cout << "Rango invalido de m.\n";
        return 1;
    }

    // Calcular todos los términos hasta n
    vector<double> sol = resolverRecurrencia(grado, coef, cond, n);

    // Mostrar resultados desde m hasta n
    cout << "\nTerminos de la recurrencia de a(" << m << ") a a(" << n << "):\n";
    for (int i = m; i <= n; i++) {
        cout << "a(" << i << ") = " << sol[i] << endl;
    }

    return 0;
}
