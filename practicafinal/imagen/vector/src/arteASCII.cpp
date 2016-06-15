#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<imagen.h>

using namespace std;

int main(){
	const int MAXIMO = 200;
	char archivo[MAXIMO] = "imagenes/", numero;
	string grises, fichero_salida, nombre_fichero_salida;
	char arteASCII[1004501], nombre[MAXIMO], caracteres[MAXIMO];
	Imagen origen;
	
	cout << "Imagen de entrada: ";
	cin.getline(nombre, MAXIMO-1);
	
	strcat(archivo, nombre);

	cout << "Fichero de cadenas: ";
	getline(cin, grises);
	
	ifstream convertir(grises);
	ofstream salida;
	
	cout << "Fichero de salida: ";
	getline(cin, fichero_salida);
	nombre_fichero_salida = fichero_salida;
	cout << '\n';

	if (!origen.leerImagen(archivo)){
		cerr << "error leyendo " << archivo << endl;
		return 1;
	}

	int i, maxi;
	getline(convertir,grises);
	convertir >> maxi;
	
	for(i = 1; i <= maxi; i++){
		convertir >> caracteres;
		if(origen.aArteASCII(caracteres, arteASCII, 1004500)){
			numero = i + '0';
			fichero_salida = nombre_fichero_salida + numero + ".txt";
			salida.open(fichero_salida);
			cout << "Guardando " << fichero_salida << ".\n";
			salida << arteASCII;
			salida.close();
		}
		else
			cout << "La conversión no ha sido posible" << endl;
		salida << arteASCII;
		caracteres[0] = '\0';
	}
	origen.destruir();
}
