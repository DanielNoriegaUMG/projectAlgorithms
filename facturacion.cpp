#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream> //creacion de ficheros
#include <windows.h>

struct Datos{
	int codigo;
	int nit;
	char nombre[50];
	char direccion[100];
	int telefono;
};

struct Productos{
	struct Datos info;
	char description[60];
	int quantity;
	float price;
	float peso;
	float total;
}producto;

struct Proveedor{
	struct Datos prov;
}proveedor;

using namespace std;

int op;

void gotoxy(int x, int y);
void formato();
void home();
bool verificaProducto(int cod);
void menuProductos();
void menuProveedor();
void registroProducto();
void listaProductos();
void listaProveedor();
void registroProveedor();
void insertArticle();
void insertProvider();

main(){
	system("cls");
	system("color 0F");
	system("mode 650");
	
	do{
		home();
	}while(op != 7);
}

void gotoxy(int x,int y){  
	HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos; 
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}

void formato(){
	for(int x = 55; x < 105; x++){
		gotoxy(x,12); cout<<"*";
	}
	for(int x = 55; x < 106; x++){
		gotoxy(x,27); cout<<"*";
	}
	
	for(int y = 12; y < 27; y++){
		gotoxy(55,y); cout<<"*";
	}
	for(int y = 12; y < 27; y++){
		gotoxy(105,y); cout<<"*";
	}
}

void home(){
	formato();
	gotoxy(80,14); cout<<"MENU";
	gotoxy(57,16); cout<<"1. Articulos";
	gotoxy(57,17); cout<<"2. Proveedores";
	gotoxy(57,18); cout<<"3. Empleados";
	gotoxy(57,19); cout<<"4. Clientes";
	gotoxy(57,20); cout<<"5. Facturacion";
	gotoxy(57,21); cout<<"6. Reportes";
	gotoxy(57,22); cout<<"7. Salir";
	gotoxy(57,23); cout<<"Digite la opcion deseada: ";
	gotoxy(83,23); cin>>op;

	switch(op){
		case 1:
			system("cls");
			menuProductos();
		break;
		case 2:
			system("cls");
			menuProveedor();
		break;
		case 3:
//			system("cls");
//			menuEmployee();
		break;
		case 4:
//			system("cls");
//			menuClient();
		break;
		case 5:
//			system("cls");
//			menuFactu();
		break;
		case 6:
//			system("cls");
//			menuReport();
		break;	
		case 7:
			gotoxy(57,25); cout<<"Saliendo del sistema...";
			break;
		default:
			gotoxy(57,25); cout<<"Opcion invalida, vuelve a intantarlo...";
			getch();
			system("cls");
	}
}

void menuProductos(){
	system("cls");
	formato();
	gotoxy(57,16); cout<<"1. NUEVO ARTICULO";
	gotoxy(57,17); cout<<"2. ELIMINAR ARTICULO";
	gotoxy(57,18); cout<<"3. MODIFICAR ARTICULO";
	gotoxy(57,19); cout<<"4. BUSCAR ARTICULO";
	gotoxy(57,20); cout<<"5. LISTADO DE ARTICULOS";
	gotoxy(57,21); cout<<"6. ATRAS";
	gotoxy(57,23); cout<<"Digite una opcion: ";
	gotoxy(76,23); cin>>op;
	switch(op){
		case 1:
			system("cls");
			registroProducto();
			getch();
			menuProductos();
		break;
		case 2:
			system("cls");
//			eliminarProducto();
			getch();
			menuProductos();
		break;
		case 3:
			getch();
			menuProductos();
		break;
		case 4:
			getch();
			menuProductos();
		break;
		case 5:
			system("cls");
			listaProductos();
			getch();
			menuProductos();
		break;
		case 6:
			system("cls");
			home();
		break;
		default:
			gotoxy(57,25); cout<<"Opcion invalida vuelve a intentarlo...";
			getch();
			system("cls");
	}
	
}

void menuProveedor(){
	system("cls");
	formato();
	gotoxy(57,16); cout<<"1. NUEVO PROVEEDOR";
	gotoxy(57,17); cout<<"2. ELIMINAR PROVEEDOR";
	gotoxy(57,18); cout<<"3. MODIFICAR PROVEEDOR";
	gotoxy(57,19); cout<<"4. BUSCAR PROVEEDOR";
	gotoxy(57,20); cout<<"5. LISTADO DE PROVEEDORES";
	gotoxy(57,21); cout<<"6. ATRAS";
	gotoxy(57,23); cout<<"Digite una opcion: ";
	gotoxy(76,23); cin>>op;
	switch(op){
		case 1:
			system("cls");
			registroProveedor();
			getch();
			menuProveedor();
		break;
		case 2:
			system("cls");
//			eliminarProducto();
			getch();
			menuProveedor();
		break;
		case 3:
			getch();
			menuProveedor();
		break;
		case 4:
			getch();
			menuProveedor();
		break;
		case 5:
			system("cls");
			listaProveedor();
			getch();
			menuProveedor();
		break;
		case 6:
			system("cls");
			home();
		break;
		default:
			gotoxy(57,25); cout<<"Opcion invalida vuelve a intentarlo...";
			getch();
			system("cls");
	}
	
}

void registroProducto(){
	cout<<"CODIGO: ";
	cin>>producto.info.codigo;
	fflush(stdin);
	cout<<"NOMBRE PRODUCTO: ";
	cin.getline(producto.info.nombre,50,'\n');
	fflush(stdin);
	cout<<"DESCRIPCION: ";
	cin.getline(producto.description,60,'\n');
	fflush(stdin);
	cout<<"CANTIDAD: ";
	cin>>producto.quantity;
	fflush(stdin);
	cout<<"PRECIO (UNIDAD): Q ";
	cin>>producto.price;
	fflush(stdin);
	cout<<"PESO: ";
	cin>>producto.peso;
	fflush(stdin);
	strlwr(producto.info.nombre);
	insertArticle();
}

void eliminarProductos(){
	
}

void listaProductos(){
	string txt;
	char cod[100];
	char cant[1000];
	char price[1000];
	char pes[1000];
	char nombre[50];
	char descripcion[100];
	int codigo;
	int cantidad;
	float precio;
	float peso;
	
	ifstream file; //declarar variable de archivo
	file.open("C:/Users/HP INTEL/Documents/1. UMG/algoritmos/Tareas/proyecto/datos/productos.txt",ios::in); // leer fichero
	
	if(file.fail()){ // en caso falle algo al crear el archivo
		cout<<"Error al cargar archivo...";
		exit(1);
	}
	
	while(!file.eof()){
		file.getline(cod,100,'\t');
		file.getline(nombre,50,'\t');
		file.getline(descripcion,100,'\t');
		file.getline(cant,1000,'\t');
		file.getline(price,1000,'\t');
		file.getline(pes,1000,'\n');
		
		codigo = atoi(cod);
		cantidad = atoi(cant);
		precio = atof(price);
		peso = atof(pes);
		
		cout<<"Codigo: "<<codigo<<endl;
		cout<<"Producto: "<<nombre<<endl;
		cout<<"Descripcion: "<<descripcion<<endl;
		cout<<"Cantidad: "<<cantidad<<endl;
		cout<<"Precio: "<<precio<<endl;
		cout<<"Peso: "<<peso<<endl;
		cout<<"--------------------------"<<endl;
	}
	file.close(); // cerrar el archivo
}

void listaProveedor(){
	char cod[100];
	char nitP[10];
	proveedor.prov.nombre;
	proveedor.prov.direccion;
	char tel[10];

	ifstream file; //declarar variable de archivo
	file.open("C:/Users/HP INTEL/Documents/1. UMG/algoritmos/Tareas/proyecto/datos/proveedores.txt",ios::in); // leer fichero
	
	if(file.fail()){ // en caso falle algo al crear el archivo
		cout<<"Error al cargar archivo...";
		exit(1);
	}
	
	while(!file.eof()){
		file.getline(cod,100,'\t');
		file.getline(nitP,10,'\t');
		file.getline(proveedor.prov.nombre,50,'\t');
		file.getline(proveedor.prov.direccion,100,'\t');
		file.getline(tel,10,'\n');
		
		proveedor.prov.codigo = atoi(cod);
		proveedor.prov.nit = atoi(nitP);
		proveedor.prov.telefono = atoi(tel);
		
		cout<<"Codigo: "<<proveedor.prov.codigo<<endl;
		cout<<"NIT: "<<proveedor.prov.nit<<endl;
		cout<<"Proveedor: "<<proveedor.prov.nombre<<endl;
		cout<<"Direccion: "<<proveedor.prov.direccion<<endl;
		cout<<"Telefono: "<<proveedor.prov.telefono<<endl;
		cout<<"------------------------------"<<endl;
	}
	file.close(); // cerrar el archivo
}

void registroProveedor(){
	cout<<"CODIGO: ";
	cin>>proveedor.prov.codigo;
	fflush(stdin);
	cout<<"NOMBRE PROVEEDOR: ";
	cin.getline(proveedor.prov.nombre,50,'\n');
	fflush(stdin);
	cout<<"NIT: ";
	cin>>proveedor.prov.nit;
	fflush(stdin);
	cout<<"DIRECCION: ";
	cin.getline(proveedor.prov.direccion,100,'\n');
	fflush(stdin);
	cout<<"TELEFONO: ";
	cin>>proveedor.prov.telefono;
	fflush(stdin);
	strlwr(proveedor.prov.nombre);
	insertProvider();
}

void insertArticle(){
	ofstream file; //declarar variable de archivo
	file.open("C:/Users/HP INTEL/Documents/1. UMG/algoritmos/Tareas/proyecto/datos/productos.txt", ios::app);
	
	if(file.fail()){ // en caso falle algo al crear el archivo
		cout<<"Error al cargar archivo...";
		exit(1);
	}
	
	file<<producto.info.codigo<<"\t";
	file<<producto.info.nombre<<"\t";
	file<<producto.description<<"\t";;
	file<<producto.quantity<<"\t";;
	file<<producto.price<<"\t";;
	file<<producto.peso<<endl;
	file.close(); // cerrar el archivo
}

void insertProvider(){
	ofstream file; //declarar variable de archivo
	file.open("C:/Users/HP INTEL/Documents/1. UMG/algoritmos/Tareas/proyecto/datos/proveedores.txt",ios::app); //agregar informacion al fichero
	
	if(file.fail()){ // en caso falle algo al crear el archivo
		cout<<"Error al cargar archivo...";
		exit(1);
	}
	
	file<<proveedor.prov.codigo<<"\t";
	file<<proveedor.prov.nit<<"\t";
	file<<proveedor.prov.nombre<<"\t";
	file<<proveedor.prov.direccion<<"\t";
	file<<proveedor.prov.telefono<<endl;
	file.close(); // cerrar el archivo
}

bool verificaProducto(int cod){
	ifstream file;
	file.open("C:/Users/HP INTEL/Documents/1. UMG/algoritmos/Tareas/proyecto/datos/productos.txt");
	
	if(file.fail()){
		cout<<"Error al leer archivo...";
		exit(1);
	}
	
	while(!file.eof()){
//		hacer validacion para poder mostrar que el codigo ya existe
	}
	
	file.close();
	return true;
}
