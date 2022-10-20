#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int op,opProv,contCliente,contProveedor,contProducto;

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
}producto[20], filtrado[20];

struct Proveedor{
	struct Datos prov;
}proveedor[20];

struct Employee{
	struct Datos info;
	int edad;
	int caja;
	int identificacion;
}empleado[20];

struct Cliente{
	struct Datos info;
}cliente[20];

using namespace std;

void gotoxy(int x, int y);
void formato();
void home();
bool validaProducto(int cod);
void busquedaProducto();
void menuProductos();
void menuProveedor();
void sinProveedor();
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
	contCliente = 0;
	contProducto = 0;
	contProveedor = 0;
	
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
			menuProductos();
		break;
		case 2:
			system("cls");
//			eliminarProducto();
			menuProductos();
		break;
		case 3:
			getch();
			menuProductos();
		break;
		case 4:
			system("cls");
			busquedaProducto();
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
	int newCodigo = 0;
	
	if(contProveedor < 1){
		opProv = 0;
		while(opProv < 1 || opProv > 2){
			sinProveedor();
		}
	}else{
		cout<<"CODIGO: ";
		cin>>newCodigo;
		fflush(stdin);

		while(validaProducto(newCodigo)){
			system("cls");
			cout<<"El codigo que ingreso ya esta en uso por otro producto..."<<endl;
			cout<<"NUEVO CODIGO: ";
			cin>>newCodigo;
			fflush(stdin);
		}
		
		producto[contProducto].info.codigo = newCodigo;

		cout<<"NOMBRE PRODUCTO: ";
		cin.getline(producto[contProducto].info.nombre,50,'\n');
		fflush(stdin);
		cout<<"DESCRIPCION: ";
		cin.getline(producto[contProducto].description,60,'\n');
		fflush(stdin);
		cout<<"CANTIDAD: ";
		cin>>producto[contProducto].quantity;
		fflush(stdin);
		cout<<"PRECIO (UNIDAD): Q ";
		cin>>producto[contProducto].price;
		fflush(stdin);
		cout<<"PESO: ";
		cin>>producto[contProducto].peso;
		fflush(stdin);
	
		//Pasar nombre y descripcion de producto a minusculas
		strlwr(producto[contProducto].info.nombre);
		strlwr(producto[contProducto].description);
		
		contProducto++; //contador de productos
	}
}

bool validaProducto(int cod){
	for(int i = 0 ; i < contProducto; i++){
		if(cod == producto[i].info.codigo) return true;
	}
	return false;
}

void sinProveedor(){
	cout<<"Primero se debe ingresar el proveedor para poder ingresar un producto..."<<endl;
	cout<<"Desea ingresar un proveedor ahora?"<<endl;
	cout<<"1. Si"<<endl;
	cout<<"2. No"<<endl;
	cout<<"Digite una opcion: ";
	cin>>opProv;
	switch(opProv){
		case 1:
			system("cls");
			registroProveedor();
		break;
		case 2:
			system("cls");
			menuProductos();
		break;
		default:
			cout<<"Opcion invalida...";
			getch();
			system("cls");
	}
}

void registroProveedor(){
	cout<<"CODIGO: ";
	cin>>proveedor[contProveedor].prov.codigo;
	fflush(stdin);
	cout<<"NOMBRE PROVEEDOR: ";
	cin.getline(proveedor[contProveedor].prov.nombre,50,'\n');
	fflush(stdin);
	cout<<"NIT: ";
	cin>>proveedor[contProveedor].prov.nit;
	fflush(stdin);
	cout<<"DIRECCION: ";
	cin.getline(proveedor[contProveedor].prov.direccion,100,'\n');
	fflush(stdin);
	cout<<"TELEFONO: ";
	cin>>proveedor[contProveedor].prov.telefono;
	fflush(stdin);
	
	//Pasar nombre y direccion del proveedor a minusculas
	strlwr(proveedor[contProveedor].prov.nombre);
	strlwr(proveedor[contProveedor].prov.direccion);
	
	contProveedor++; //contador de proveedores
}

void listaProductos(){
	gotoxy(3,2); cout<<"CODIGO";
	gotoxy(18,2); cout<<"PRODUCTO";
	gotoxy(70,2); cout<<"DESCRIPCION";
	gotoxy(120,2); cout<<"CANTIDAD";
	gotoxy(145,2); cout<<"PRECIO";
	gotoxy(160,2); cout<<"PESO";

	for(int i = 0; i < contProducto; i++){
		gotoxy(3,i+4); cout<<producto[i].info.codigo;
		gotoxy(18,i+4); cout<<producto[i].info.nombre;
		gotoxy(70,i+4); cout<<producto[i].description;
		gotoxy(120,i+4); cout<<producto[i].quantity;
		gotoxy(145,i+4); cout<<producto[i].price;
		gotoxy(160,i+4); cout<<producto[i].peso;
	}
}

void listaProveedor(){
	gotoxy(40,2); cout<<"CODIGO";
	gotoxy(55,2); cout<<"PROVEEDOR";
	gotoxy(76,2); cout<<"NIT";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(110,2); cout<<"CONTACTO";

	for(int i = 0; i < contProveedor; i++){
		gotoxy(40,i+4); cout<<proveedor[i].prov.codigo;
		gotoxy(55,i+4); cout<<proveedor[i].prov.nombre;
		gotoxy(76,i+4); cout<<proveedor[i].prov.nit;
		gotoxy(90,i+4); cout<<proveedor[i].prov.direccion;
		gotoxy(110,i+4); cout<<proveedor[i].prov.telefono;
	}
}

void busquedaProducto(){
	
	int resultados = 0;
	int i = 0;
	char buscar[50];
	fflush(stdin);
	cout<<"Ingrese el nombre del producto a buscar: ";
	cin.getline(buscar,50,'\n');
	fflush(stdin);

	for(int i = 0; i < contProducto; i++){
		if(strcmp(buscar,producto[i].info.nombre) == 0){
			filtrado[i].info.codigo = producto[i].info.codigo;
			strcpy(filtrado[i].info.nombre, producto[i].info.nombre);
			strcpy(filtrado[i].description, producto[i].description);
			filtrado[i].price = producto[i].price;
			filtrado[i].quantity = producto[i].quantity;
			resultados++;
		}
	}
	
	if(resultados > 0){
		for(int res = 0; res < resultados; res++){
			cout<<"\n Codigo: "<<filtrado[res].info.codigo<<"\nProducto: "<<filtrado[res].info.nombre<<"\n Descripcion: "<<filtrado[res].description<<"\n Cantidad: "<<filtrado[res].quantity<<"\n Precio: "<<filtrado[res].price<<endl;
		}
	}else{
		cout<<"no se encontraron resultados...";
	}
}
