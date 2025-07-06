#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
using namespace std;

// Función para resolver un sistema 2x2
pair<double, double> resolverSistema2x2(double a1, double b1, double c1, double a2, double b2, double c2) {
    double det = a1 * b2 - a2 * b1;
    if (det == 0) throw runtime_error("Sistema sin solucion unica");
    double A = (c1 * b2 - c2 * b1) / det;
    double B = (a1 * c2 - a2 * c1) / det;
    return {A, B};
}

// Función para resolver sistema 3x3  Cramer 
vector<double> resolverSistema3x3(vector<vector<double>> mat, vector<double> rhs) {
    double D = mat[0][0]*(mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1])
             - mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[2][0])
             + mat[0][2]*(mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0]);
    if (D == 0) throw runtime_error("Sistema sin solucion unica");

    vector<double> resultado(3);
    for (int i = 0; i < 3; i++) {
        vector<vector<double>> temp = mat;
        for (int j = 0; j < 3; j++)
            temp[j][i] = rhs[j];

        double Di = temp[0][0]*(temp[1][1]*temp[2][2]-temp[1][2]*temp[2][1])
                  - temp[0][1]*(temp[1][0]*temp[2][2]-temp[1][2]*temp[2][0])
                  + temp[0][2]*(temp[1][0]*temp[2][1]-temp[1][1]*temp[2][0]);

        resultado[i] = Di / D;
    }
    return resultado;
}

int main() {
    int grado;
    cout << "Ingrese el grado de la recurrencia (1, 2 o 3): ";
    cin >> grado;

    vector<double> coef(grado);
    cout << "Ingrese los coeficientes de la recurrencia (de a(n-1) a a(n-" << grado << ")):"<<endl;
    for (int i = 0; i < grado; i++) {
        cout << "Coeficiente de a(n-" << i+1 << "): ";
        cin >> coef[i];
    }

    vector<double> condiciones(grado);
    cout << "Ingrese las condiciones iniciales a(0) a a(" << grado-1 << "):"<<endl;
    for (int i = 0; i < grado; i++) {
        cout << "a(" << i << ") = ";
        cin >> condiciones[i];
    }

    // Ecuación caracteristica
    // r^n = c1*r^(n-1) + c2*r^(n-2) ..
    vector<double> raices(grado);

    if (grado == 1) {
        raices[0] = coef[0];
        double A = condiciones[0];
        cout << "Termino general: a(n) = " << A << " * (" << raices[0] << ")^n"<<endl;
    } else if (grado == 2) {
        double a = 1, b = -coef[0], c = -coef[1];
        double discriminante = b*b - 4*a*c;

        if (discriminante < 0) {
            cout << "Raices complejas no implementadas "<<endl;
            return 1;
        }

        double r1 = (-b + sqrt(discriminante)) / (2*a);
        double r2 = (-b - sqrt(discriminante)) / (2*a);
        pair<double, double> AB = resolverSistema2x2(1, 1, condiciones[0], r1, r2, condiciones[1]);
		double A = AB.first;
		double B = AB.second;

        cout << "Termino general: a(n) = " << A << " * (" << r1 << ")^n + " << B << " * (" << r2 << ")"<<endl;
    } else if (grado == 3) {
        double a = 1;
        double b = -coef[0];
        double c = -coef[1];
        double d = -coef[2];

        cout << "Para grado 3, ingrese manualmente las raices r1, r2, r3 (real y distintas):"<<endl;
        for (int i = 0; i < 3; i++) {
            cout << "r" << i+1 << ": ";
            cin >> raices[i];
        }

        vector<vector<double>> mat = {
            {1, 1, 1},
            {raices[0], raices[1], raices[2]},
            {pow(raices[0], 2), pow(raices[1], 2), pow(raices[2], 2)}
        };

        vector<double> rhs = {condiciones[0], condiciones[1], condiciones[2]};
        vector<double> ABC = resolverSistema3x3(mat, rhs);

        cout << "Termino general: a(n) = "<<endl;
        for (int i = 0; i < 3; i++) {
            cout << ABC[i] << "*(" << raices[i] << ")^n";
            if (i < 2) cout << " + ";
        }
        cout << endl;
    }

    return 0;
}
