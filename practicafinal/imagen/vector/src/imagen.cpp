#include <iostream>
#include <string>
#include <fstream>
#include "imagen.h"
#include "pgm.h"
#include "byte.h"
#include "lista.h"


/////////////////////////////////////////////////////////////////
// PRACTICA 6
Imagen::Imagen(){
	datos = 0;
	nfilas = ncolumnas = 0;
}

Imagen::~Imagen(){
	destruir();
}

Imagen::Imagen(const Imagen &copia){
	datos = 0;
	crear(copia.filas(),copia.columnas());
	
	for(int i = 0; i < nfilas*ncolumnas; i++)
		datos[i] = copia.getPos(i);
}

Imagen &Imagen::operator= (const Imagen &referencia){
	if (this != &referencia){
		destruir();
		crear(referencia.filas(),referencia.columnas());
		
		for(int i = 0; i < nfilas*ncolumnas; i++)
			datos[i] = referencia.getPos(i);
	}
	
	return *this;
}

Imagen::Imagen (int filas, int columnas){
	datos = 0;
	crear(filas,columnas);
}

Imagen Imagen::operator+ (const Imagen &referencia) const{
	int columnas_nuevas = referencia.columnas() + ncolumnas;
	int filas_nuevas = (referencia.filas() > nfilas) ? referencia.filas() : nfilas;
	Imagen nuevo(filas_nuevas,columnas_nuevas);

	for(int i = 0; i < filas_nuevas; i++)
		for(int j = 0; j < columnas_nuevas; j++)
			if(j < ncolumnas){
				if(i < nfilas) 
					nuevo.set(i,j,get(i,j));
				else
					nuevo.set(i,j,0);
			}
			else{
				if(i < referencia.filas())
					nuevo.set(i,j,referencia.get(i,(j-ncolumnas)));
				else
					nuevo.set(i,j,0);
			}
	
	
	
	return nuevo;
}

/////////////////////////////////////////////////////////////////

void Imagen::crear (int filas, int columnas){
	if(datos != 0)
		destruir();

	if(datos == 0){
		if(filas <= 0 || columnas <= 0){
			nfilas = 0;
			ncolumnas = 0;
			datos = 0;
		}
		else{
			nfilas = filas;
			ncolumnas = columnas;
			datos = new byte [filas*columnas];
			
			for(int i = 0; i < filas*columnas; i++)
				datos[i] = 0;
		}
	}
}

void Imagen::destruir(){
	if(datos != 0){
		delete [] datos;
		nfilas = ncolumnas = 0;
		datos = 0;
	}	
}

int Imagen::filas () const{
	return nfilas;
}

int Imagen::columnas () const{
	return ncolumnas;
}

void Imagen::set (int x, int y, byte v){
	if((x*ncolumnas)+y >= 0)
		datos[(x*ncolumnas)+y] = v;
}

byte Imagen::get (int x , int y) const{
	return datos[(x*ncolumnas)+y];
}

void Imagen::setPos (int i , byte v){
	if(i >= 0)
		datos[i] = v;
}

byte Imagen::getPos (int i) const{
	return datos[i];
}
		
bool Imagen::leerImagen (const char nombreFichero[]){
	bool resultado = false;
	TipoImagen controlador = infoPGM(nombreFichero,nfilas,ncolumnas);
	
	if (controlador != IMG_DESCONOCIDO){
		crear(nfilas,ncolumnas);
		if(controlador == IMG_PGM_BINARIO)
			resultado = leerPGMBinario(nombreFichero,datos,nfilas,ncolumnas);
		else
			resultado = leerPGMTexto(nombreFichero,datos,nfilas,ncolumnas);
	}
	
	return resultado;
}

bool Imagen::escribirImagen (const char nombreFichero[], bool esBinario){
	bool resultado;
	if(esBinario)
		resultado = escribirPGMBinario(nombreFichero,datos,nfilas,ncolumnas);
	else
		resultado = escribirPGMTexto(nombreFichero,datos,nfilas,ncolumnas);
	
	return resultado;
}

Imagen Imagen::plano (int k){
	Imagen nueva(nfilas,ncolumnas);
	byte ajustar;

	for(int i = 0; i < nfilas*ncolumnas; i++){
		ajustar = 0x0;
		if(getbit(datos[i],k)){
			on(ajustar,7);
			nueva.setPos(i,ajustar);
		}
		else
			nueva.setPos(i,ajustar);
	}
	return nueva;
}

bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong){
	int cardinal, escritura = 0;
	bool controlador;
	for(cardinal = 0; grises[cardinal] != '\0'; cardinal++);
	
	controlador = nfilas*ncolumnas+nfilas+1 < maxlong;
	if(controlador)
		for(int i = 0; i < nfilas; escritura++, i++){
			for(int j = 0; j < ncolumnas; j++, escritura++){
				int numero = get(i,j);
				arteASCII[escritura] = grises[numero*cardinal/256];
			}
			arteASCII[escritura] = '\n';
		}

	arteASCII[escritura] = '\0';
	
	return controlador;
}

bool Imagen::listaAArteASCII(const Lista celdas){
	int longitud = celdas.longitud();
	string almacen;
	bool controlador = true, devolver = true;
	char *arte = new char [nfilas*ncolumnas+nfilas+1];
	ofstream salida;

	for(int i = 0; i < longitud && controlador; i++){
		almacen = celdas.getCelda(i);
		if(almacen != ""){
			controlador = aArteASCII(almacen.c_str(), arte, nfilas*ncolumnas+nfilas+2);
			if(controlador){
				almacen = "ascii" + to_string(i) + ".txt";
				salida.open(almacen);
				salida << arte;
				salida.close();
			}
			else
				devolver = false;
		}
		else{
			controlador = false;
			devolver = false;
		}
	}
	delete [] arte;
	return devolver;
}








