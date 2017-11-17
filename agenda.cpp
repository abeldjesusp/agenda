
/*********************************************
 *			AGENDA DE CONTACTOS              *
 *	Autor: Abel De Jesus Pimentel            *
 *	Fecha: 15/11/2017                        *
 *	Descripcion: Una pequeña agenda para     *
 *	ingresar, actualizar, eliminar, buscar   *
 *	y ver listado de contactos.              *
 *                                           *
 *********************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
//#include <conio.h> //PARA WINDOWS
//#include <ncurses.h> //PARA LINUX


using namespace std;

const char DIR_ARCHIVO[] = "contactos.dat";

struct Contacto{
	char nombre[30];
	char apellido[30];
	int edad;
	char correo[45];
};

/********* FUNCIONES DEL PROGRAMA **********/
void ingresarContacto(Contacto);
Contacto leerContacto();
bool existeContacto(char*, char*);
Contacto buscarContacto(char*, char*);
void mostrarContacto(Contacto);
void listarContactos();
void eliminarContactos(char*, char*);
void actualizarContactos(char*, char*);
/*******************************************/

/******** FUNCIONES PARA EL MENU ***********/
void menuIngresar();
void menuBuscar();
void menuListado();
void menuEliminar();
void menuActualizar();
/*******************************************/
int main(int argc, char const *argv[]){
	int opcion;
	do{
		system("clear");
		cout << "\t\t\t\t\tAGENDA" << endl;
		cout << "\t\t\tIngresar contacto................[1]" << endl;
		cout << "\t\t\tBuscar contacto..................[2]" << endl;
		cout << "\t\t\tVer listado......................[3]" << endl;
		cout << "\t\t\tEliminar contacto................[4]" << endl;
		cout << "\t\t\tActualizar contacto..............[5]" << endl;
		cout << "\t\t\tSALIR............................[6]" << endl;
		cout << "\t\t\tIngrese una opcion >> ";
		cin >> opcion;
		cin.ignore();
		switch(opcion){
			case 1 : system("clear"); 
					 menuIngresar();
					 break;
			case 2 : system("clear"); 
					 menuBuscar();
					 break;
			case 3 : system("clear"); 
					 menuListado();
					 break;
			case 4 : system("clear"); 
					 menuEliminar();
					 break;
			case 5 : system("clear"); 
					 menuActualizar();
					 break;
			case 6 : break;
			default: cout << "\t\t\tOPCION INCORRECTA" << endl;
		}
	}while(opcion != 6);

	return 0;
}

void ingresarContacto(Contacto c){
	ofstream salida;

	salida.open(DIR_ARCHIVO,ios::binary | ios::app);
	salida.write((char*)&c, sizeof(Contacto));
	salida.close();
}

Contacto leerContacto(){
	Contacto c;

	cout << "\t\t\tNombre   : ";
	cin.getline(c.nombre,30);
	cout << "\t\t\tApellido : ";
	cin.getline(c.apellido, 45);
	cout << "\t\t\tEdad     : ";
	cin >> c.edad;
	cin.ignore();
	cout << "\t\t\tCorreo   : ";
	cin.getline(c.correo,45);

	return c;
}

bool existeContacto(char nombre[], char apellido[]){
	Contacto c;
	ifstream entrada;

	entrada.open(DIR_ARCHIVO, ios::binary);
	if(entrada.good()){
		while(entrada.read((char*)&c,sizeof(Contacto))){
			if(strcmp(nombre, c.nombre) == 0 && strcmp(apellido, c.apellido) == 0){
				entrada.close();
				return true;
			}
		}
		entrada.close();
		return false;
	}else{
		entrada.close();
		return false;
	}
}

Contacto buscarContacto(char nombre[], char apellido[]){
	Contacto c;
	ifstream entrada;

	entrada.open(DIR_ARCHIVO, ios::binary);
	if(entrada.good()){
		while(entrada.read((char*)&c,sizeof(Contacto))){
			if(strcmp(nombre, c.nombre) == 0 && strcmp(apellido, c.apellido) == 0){
				entrada.close();
				return c;
			}
		}
	}
}

void mostrarContacto(Contacto c){
	cout << endl;
	cout << "\t\t\tNOMBRE   : " << c.nombre << endl;
	cout << "\t\t\tAPELLIDO : " << c.apellido << endl;
	cout << "\t\t\tEDAD     : " << c.edad << endl;
	cout << "\t\t\tCORREO   : " << c.correo << endl;
	cout << endl;
}

void listarContactos(){
	ifstream entrada;
	entrada.open(DIR_ARCHIVO, ios::binary);
	Contacto c;
	if(entrada.good()){
		while(entrada.read((char*)&c, sizeof(Contacto))){
			mostrarContacto(c);
		}
	}else{
		cout << "NO se puede puede leer el archivo" << endl;
	}
	entrada.close();
}

void eliminarContactos(char nombre[], char apellido[]){
	ifstream entrada;
	ofstream temporal;
	entrada.open(DIR_ARCHIVO, ios::binary);
	temporal.open("temp.dat", ios::binary);
	Contacto c;
	if(entrada.good()){
		while(entrada.read((char*)&c, sizeof(Contacto))){
			if(strcmp(nombre, c.nombre) != 0 || strcmp(apellido, c.apellido) != 0){
				temporal.write((char*)&c, sizeof(Contacto));
			}
		}
	}
	entrada.close();
	temporal.close();
	remove(DIR_ARCHIVO);
	rename("temp.dat", DIR_ARCHIVO);
}

void actualizarContactos(char nombre[], char apellido[]){
	ifstream entrada;
	ofstream temporal;
	entrada.open(DIR_ARCHIVO, ios::binary);
	temporal.open("temp.dat", ios::binary);
	Contacto c;
	if(entrada.good()){
		while(entrada.read((char*)&c, sizeof(Contacto))){
			if(strcmp(nombre, c.nombre) == 0 || strcmp(apellido, c.apellido) == 0){
				Contacto actualizado = leerContacto();
				temporal.write((char*)&actualizado, sizeof(Contacto));
			}else{
				temporal.write((char*)&c, sizeof(Contacto));
			}
		}
	}
	entrada.close();
	temporal.close();
	remove(DIR_ARCHIVO);
	rename("temp.dat", DIR_ARCHIVO);
}

/************************************/
void menuIngresar(){
	cout <<"\t\t\t\tINGRESO DE NUEVO CONTACTO" << endl;
	Contacto nuevo = leerContacto();
	ingresarContacto(nuevo);
	cout << "\t\t\tContacto agregado" << endl;
}

void menuBuscar(){
	cout << "\t\t\t\tBUSCAR CONTACTO" << endl;
	char nombre[30], apellido[45];
	cout << "\t\t\tIngrese los datos de busqueda:" << endl;
	cout << "\t\t\tNombre   : ";
	cin.getline(nombre, 30);
	cout << "\t\t\tApellido : ";
	cin.getline(apellido, 45);
	if(existeContacto(nombre, apellido)){
		Contacto buscado = buscarContacto(nombre, apellido);
		mostrarContacto(buscado);
		//getch();/**OBTENER CARACTER / PARA WINDOWS**/
		cin.ignore();//PARA QUE HAGA LO MISMO QUE LA FUNCION getch(); PERO EN LINUX
	}else{
		cout << "\t\t\tNo se ha encontrado ese contacto" << endl;
		//getch();/**OBTENER CARACTER / PARA WINDOWS**/
		cin.ignore();//PARA QUE HAGA LO MISMO QUE LA FUNCION getch(); PERO EN LINUX
	}
}

void menuListado(){
	cout << "\t\t\tLISTA DE CONTACTOS" << endl;
	listarContactos();
	//getch();/**OBTENER CARACTER / PARA WINDOWS**/
	cin.ignore();//PARA QUE HAGA LO MISMO QUE LA FUNCION getch(); PERO EN LINUX
}

void menuEliminar(){
	cout << "\t\t\t\tELIMINAR CONTACTO" << endl;
	char nombre[30], apellido[45];
	cout << "\t\t\tIngrese los datos de eliminacion:" << endl;
	cout << "\t\t\tNombre   : ";
	cin.getline(nombre, 30);
	cout << "\t\t\tApellido : ";
	cin.getline(apellido, 45);
	if(existeContacto(nombre, apellido)){
		Contacto eliminar = buscarContacto(nombre, apellido);
		int opcion;
		cout << "\t\t\t¿Seguro que desea eliminar el siguiente contacto?" << endl;
		mostrarContacto(eliminar);
		do{
			cout << "\t\t\tSI[1]....NO[2]: ";
			cin >> opcion;
			cin.ignore();
			switch(opcion){
				case 1:
					eliminarContactos(nombre, apellido);
					cout << "\t\t\tContacto eliminado con exito" << endl;
					break;
				case 2: break;
				default: 
					cout << "\t\t\tOPCION INCORRECTA" << endl;					
			}
		}while(opcion != 1 && opcion != 2);

	}else{
		cout << "\t\t\tNO EXISTE EL CONTACTO" << endl;
	}
}

void menuActualizar(){
	cout << "\t\t\t\tACTUALIZAR CONTACTO" << endl;
	char nombre[30], apellido[45];
	cout << "\t\t\tIngrese los datos de modificacion:" << endl;
	cout << "\t\t\tNombre   : ";
	cin.getline(nombre, 30);
	cout << "\t\t\tApellido : ";
	cin.getline(apellido, 45);
	if(existeContacto(nombre, apellido)){
		Contacto buscado = buscarContacto(nombre, apellido);
		cout << "\t\t\tRegistro a modificar:" << endl;
		mostrarContacto(buscado);
		actualizarContactos(nombre, apellido);
		cout << "\t\t\tSE ACTUALIZO EL REGISTRO" << endl;
		
	}else{
		cout << "\t\t\tNO EXISTE EL CONTACTO" << endl;
	}
}