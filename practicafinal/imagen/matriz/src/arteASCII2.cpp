/**
 * lee cualquier imagen indicada por el usuario y un fichero con cadenas 
 * de caracteres y crea ficheros de imagen transformadas, una por cadena
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include "imagen.h"
#include "lista.h"

using namespace std;


int main(int argc, char *argumentos[]){
	if(argc == 3){
		Imagen origen;
		Lista celdas;


		// Leer la imagen desde fichero
		if (!origen.leerImagen(argumentos[1])){
			cerr << "Error leyendo imagen " << argumentos[1] << endl;
			return 1;
		}
	
	
		// Leer cadenas desde fichero
		if (celdas.leerLista(argumentos[2])){	
			// realizar las conversiones
			if (origen.listaAArteASCII(celdas)){
				cout << "Exito en la conversion." << endl;
				cout << "Chequee los ficheros asciiX.txt" << endl;
				cout << endl;	
			}else{
				cerr << "La conversion no ha sido posible" << endl;
				cerr << endl;
			}
		}else{
			cerr << "Error lista de grises " << argumentos[2] << endl;
		}
	}
	else
		cerr << "Introduzca imagen.pgm caracteres.txt(grises.txt archivo de ejemplo en carpeta raiz)." << endl;
	
	
	return 0;
}
