#include <iostream>
using namespace std;
int const filas = 4;
int const columnas = 5;
void limpiarMatrices(bool disponibilidad[filas][columnas], int pesos[filas][columnas]);
void imprimirMatrizBooleana(bool matriz[filas][columnas]);
void imprimirMatrizTexto(string matriz[filas][columnas]);
void imprimirMatrizEnteros(int matriz[filas][columnas]);
string marcaMasPesada(int pesos[filas][columnas], string marcas[filas][columnas]);
int pesoMasLiviano(int pesos[filas][columnas]);
void mostrarDisponibles(bool disponibilidad[filas][columnas]);
void llenarVector(int n, string vector[]);
int marcasEnEconomica(string marcas[filas][columnas], string nombreMarca);
int marcasEnPremium(string marcas[filas][columnas], string nombreMarca);
int buscarFilaPesada(int pesos[filas][columnas]);
int buscarColumnaLiviana(int pesos[filas][columnas]);
int conteoContenedores(bool disponibilidad[filas][columnas]);
void reporteEmpresa(string marcas[filas][columnas], string marcaBuscada);
float promedio(int pesos[filas][columnas], bool disponibilidad[filas][columnas]);
void contadorContenedores(string vector[], int cantidadContenedoresP[], int puertos);
int claseArticulos(string tipoArticulo[filas][columnas], string tipoArticulos);
float promedioPesoTotal(string vector[],int puertos,int pesos[filas][columnas]);
int main() {
    string marcaPesada = "";
    int pesoLiviano = 0;
    bool disponibilidad[filas][columnas];
    string marcas[filas][columnas];
    int pesos[filas][columnas];
    string puertoCarga[filas][columnas];
    string tipoArticulo[filas][columnas];
    limpiarMatrices(disponibilidad, pesos);
    int puertos = 0;
    int contadorPuertos = 0;
    string nombrePuerto = "";

    cout << "Ingrese a cuantos puertos va a ir" << endl;
    cin >> puertos;
    string vector[puertos];
    llenarVector(puertos, vector);

    int filasOcupadas = 0;
    int columnasOcupadas = 0;
    string marca = "";
    int peso = 0;
    string puertoCargas = "";
    string tipoArticulos = "";
    int contadorPorcentajeOcupacion = 0;
    int acumuladorPorcentajeOcupacion = 0;
    int contenedor = 0;
    int contadorPreciosPorPuerto = 0;
    int acumuladorPreciosPorPuerto = 0;
    int contadorContenedoresc = 0;
    int cantidadContenedoresP[puertos] = {};
    //Ciclo puertos
    for (int contadorPuertos = 0; contadorPuertos < puertos; contadorPuertos++) {
        do {
            cout << "Elija uno de los siguientes sitios disponibles para ingresar su contenedor" << endl;
            mostrarDisponibles(disponibilidad);
            cout << "Ingrese la posición de i (Filas) en la que desea poner el contenedor" << endl;
            cin >> filasOcupadas;
            cout << "Ingrese la posición j (Columnas) en la que desea poner el contenedor" << endl;
            cin >> columnasOcupadas;

            if ((filasOcupadas < filas && columnasOcupadas < columnas) && (disponibilidad[filasOcupadas][columnasOcupadas] == 1)) {
                cantidadContenedoresP[contadorPuertos] = cantidadContenedoresP[contadorPuertos] + 1;
                
                cout << "Esta disponible, ingrese su marca" << endl;
                cin >> marca;
                cout << "Ingrese el peso del producto en kg" << endl;
                cin >> peso;
                cout << "Ingrese el Puerto de Carga" << endl;
                cin >> puertoCargas;
                cout << "Ingrese el Tipo de Articulo" << endl;
                cin >> tipoArticulos;
                int cantidadTipo = 0;
       			cantidadTipo = 	claseArticulos(tipoArticulo,tipoArticulos);
				cout << "Dado el tipo " << tipoArticulos << " se determino que existen " << cantidadTipo << " de este tipo" << endl;
                disponibilidad[filasOcupadas][columnasOcupadas] = 0;
                marcas[filasOcupadas][columnasOcupadas] = marca;
                pesos[filasOcupadas][columnasOcupadas] = peso;
                puertoCarga[filasOcupadas][columnasOcupadas] = puertoCargas;
                tipoArticulo[filasOcupadas][columnasOcupadas] = tipoArticulos;
                contadorPorcentajeOcupacion = contadorPorcentajeOcupacion + 1;
                acumuladorPorcentajeOcupacion = (contadorPorcentajeOcupacion * 100 / 20);
                cout << "El porcentaje de ocupacion es de: " << acumuladorPorcentajeOcupacion << endl;
            }
            else {
                cout << "La posicion ingresada no se encuentra disponible" << endl;
            }
            cout << "Ingrese 1 si quiere ocupar otro contenedor, sino coloque 0" << endl;
            cin >> contenedor;
        } while (contenedor == 1);
        int precioEconomico = 0;
        int precioPremium = 0;
        int total = 0;
        reporteEmpresa(marcas, marca);
        precioEconomico = marcasEnEconomica(marcas, marca);
        precioPremium = marcasEnPremium(marcas, marca);
        total = precioEconomico + precioPremium;
        cout << "El total a pagar es de: " << total << endl;
    }
    buscarFilaPesada(pesos);
    buscarColumnaLiviana(pesos);
    cout << "El numero total de contenedores por los " << puertos << " puertos es de: " << conteoContenedores(disponibilidad) << endl;
    conteoContenedores(disponibilidad);
    promedio(pesos, disponibilidad);
    //Impresion de las matrices
    cout << "Matriz disponibilidad" << endl;
    imprimirMatrizBooleana(disponibilidad);
    cout << "Matriz marcas " << endl;
    imprimirMatrizTexto(marcas);
    cout << "Matriz puertos " << endl;
    imprimirMatrizTexto(puertoCarga);
    cout << "Matriz Tipo Articulo " << endl;
    imprimirMatrizTexto(tipoArticulo);
    cout << "Matriz Pesos " << endl;
    imprimirMatrizEnteros(pesos);
    //Determine la marca del contenedor mas pesado
    marcaPesada = marcaMasPesada(pesos, marcas);
    cout << "La marca mas pesada es: " << marcaPesada << endl;
    //Determine el peso mas liviano
    pesoLiviano = pesoMasLiviano(pesos);
    cout << "El peso del contenedor mas liviano es: " << pesoLiviano << endl;
    contadorContenedores(vector, cantidadContenedoresP, puertos);
    promedioPesoTotal(vector,puertos,pesos);
    return 0;
}
void limpiarMatrices(bool disponibilidad[filas][columnas], int pesos[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            disponibilidad[i][j] = 1;
            pesos[i][j] = 0;
        }
    }
}
void imprimirMatrizBooleana(bool matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}
void imprimirMatrizTexto(string matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}
void imprimirMatrizEnteros(int matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}
void mostrarDisponibles(bool disponibilidad[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (disponibilidad[i][j] == 1) {
                cout << i << "," << j << endl;
            }
        }
    }
}
void llenarVector(int n, string vector[]) {
    for (int i = 0; i < n; i++) {
        cout << "Ingrese el nombre del puerto numero " << i << endl;
        cin >> vector[i];
    }
    cout << "Los nombres de los puertos son: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << vector[i] << endl;
    }
} //1
int conteoContenedores(bool disponibilidad[filas][columnas]) {
    int suma = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (disponibilidad[i][j] == 0) {
                suma = suma + 1;
            }
        }
    }
    return suma;
}
//2
void contadorContenedores(string vector[], int cantidadContenedoresP[], int puertos) {
    for (int i = 0; i < puertos; i++) {
        for (int j = 0; j < puertos; j++) {
            if (cantidadContenedoresP[i] > cantidadContenedoresP[j]) {
                int aux = cantidadContenedoresP[i];
                cantidadContenedoresP[i] = cantidadContenedoresP[j];
                cantidadContenedoresP[j] = aux;
                string aux2 = vector[i];
                vector[i] = vector[j];
                vector[j] = aux2;
            }
        }
    }

    for (int i = 0; i < puertos; i++) {
        cout << "El reporte del nombre del puerto y su cantidad de contenedores ingresados de mayor a menor es de: " << vector[i] << "-" << cantidadContenedoresP[i] << endl;
    }
}
//3
int marcasEnEconomica(string marcas[filas][columnas], string nombreMarca) {
    int contadorPrecioEconomico = 0;
    for (int i = 0; i < filas; i = i + 1) {
        for (int j = 0; j < columnas; j = j + 1) {
            if (marcas[i][j] == nombreMarca) {
                if (!((i == 1 || i == 2) && (j == 1 || j == 2 || j == 3))) {
                    contadorPrecioEconomico = contadorPrecioEconomico + 100;
                }
            }
        }
    }
    return contadorPrecioEconomico;
} //4
int marcasEnPremium(string marcas[filas][columnas], string nombreMarca) {
    int contadorPrecioPremium = 0;
    for (int i = 0; i < filas; i = i + 1) {
        for (int j = 0; j < columnas; j = j + 1) {
            if (marcas[i][j] == nombreMarca) {
                if ((i == 1 || i == 2) && (j == 1 || j == 2 || j == 3)) {
                    contadorPrecioPremium = contadorPrecioPremium + 300;
                }
            }
        }
    }
    return contadorPrecioPremium;
} //5
void reporteEmpresa(string marcas[filas][columnas], string nombreMarca) {
    int contadorPrecioPremium = 0;
    int contadorPremium = 0;
    int contadorPrecioEconomico = 0;
    int contadorEconomico = 0;
    for (int i = 0; i < filas; i = i + 1) {
        for (int j = 0; j < columnas; j = j + 1) {
            if (marcas[i][j] == nombreMarca) {
                if ((i == 1 || i == 2) && (j == 1 || j == 2 || j == 3)) {
                    contadorPrecioPremium = contadorPrecioPremium + 300;
                    contadorPremium = contadorPremium + 1;
                } else {
                    contadorPrecioEconomico = contadorPrecioEconomico + 100;
                    contadorEconomico = contadorEconomico + 1;
                }
            }
        }
    }
cout << "Dado el nombre " << nombreMarca << " tiene " << contadorEconomico << " contenedores economicos y tiene " << contadorPremium << " contenedores premiums" << endl;
} //6
float promedio(int pesos[filas][columnas], bool disponibilidad[filas][columnas]) {
    int contador = 0;
    int acumulador = 0;
    float promedio = 0.0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (disponibilidad[i][j] == 0) {
                contador = contador + 1;
                acumulador = acumulador + pesos[i][j];
            }
        }
    }
    promedio = ((acumulador) / (contador));
    cout << "El promedio del peso de los contenedores que ocupan una celda es de " << promedio << endl;
    return promedio;
}
//7
int buscarFilaPesada(int pesos[filas][columnas]) {
    int suma = 0;
    int mayor = INT_MIN;
    int filaMayor = -1;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            suma = suma + pesos[i][j];
        }
        if (suma > mayor) {
            mayor = suma;
            filaMayor = i;
        }
        suma = 0;
    }
    cout << "Se determino que la fila mas pesada es la numero " << filaMayor << endl;
    return filaMayor;
}
//8
int buscarColumnaLiviana(int pesos[filas][columnas]) {
    int suma = 0;
    int menor = INT_MAX;
    int columnaMenor = -1;
    for (int j = 0; j < columnas; j++) {
        for (int i = 0; i < filas; i++) {
            suma = suma + pesos[i][j];
        }
        if ((suma < menor) && (suma != 0)) {
            menor = suma;
            columnaMenor = j;
        }
        suma = 0;
    }
    cout << "Se determino que la columna mas liviana es la numero " << columnaMenor << endl;
    return columnaMenor;
}
//9
int claseArticulos(string tipoArticulo[filas][columnas], string tipoArticulos) {
    int contador = 1;
    string auxArticulo = "";
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tipoArticulo[i][j] == tipoArticulos) {
                    contador = contador + 1;
            }
        }
    }
    return contador;
}
//10
float promedioPesoTotal(string vector[],int puertos,int pesos[filas][columnas]){
	float contador = 0;
    float acumulador = 0;
    float promedio = 0.0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
        	if(pesos[i][j] != 0){
        		contador = contador + 1;
        		acumulador = acumulador + pesos[i][j];
			}
		}
    }
    promedio = acumulador / contador;
    for (int i = 0; i < puertos; i++) {
    	cout << "El promedio del peso de los contenedores que ocupan el puerto " << vector[i] << " es de " << promedio << endl;
	}
	return promedio;
}
//11
string marcaMasPesada(int pesos[filas][columnas], string marcas[filas][columnas]) {
    int mayor = INT_MIN;
    string respuesta = "";
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (pesos[i][j] > mayor) {
                mayor = pesos[i][j];
                respuesta = marcas[i][j];
            }
        }
    }
    return respuesta;
}
//12
int pesoMasLiviano(int pesos[filas][columnas]) {
    int menor = INT_MAX;
    int respuestaPeso = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if ((pesos[i][j] < menor) && (pesos[i][j] != 0)) {
                menor = pesos[i][j];
                respuestaPeso = pesos[i][j];
            }
        }
    }
    return respuestaPeso;
}
