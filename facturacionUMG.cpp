#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctime> // para obtener fecha actual

int op, opProv,codigoCliente, contCliente, contProveedor, contProducto, contEmpleado, contBodega, contTienda, contFac;
int codigoEmpleado,codigoProveedor;
char nombreCompleto[50];
int codFac = 1;


struct Datos{
	int codigo;
	int nit;
	char nombre[50];
	char direccion[100];
	int telefono;
};

struct Almacenamiento{
	int unidades;
}bodega[20], tienda[20];

struct Productos{
	struct Datos info;
	struct Almacenamiento almacenado;
	char description[60];
	int quantity;
	float price;
	float peso;
	float subtotal;
	float total;
}producto[100], prodBodega[50], prodTienda[50],filtrado[50], compra[100];

struct Proveedor{
	struct Datos prov;
}proveedor[20];

struct Credenciales{
	char user[30];
	char password[30];
};

struct Employee{
	struct Datos info;
	struct Credenciales cuenta;
	char apellido[50];
	int edad;
	int caja;
}empleado[20], filtraEmpleado[20];

struct Cliente{
	struct Datos info;
	char apellido[50];
}cliente[20];

struct Fecha{
	int day, month, year, second, minutes, hour;
}obtener, actual;

struct Factura{
	int codigo;
	long int nit;
	char cliente[100];
	char empleado[100];
	int caja;
//	string fecha;
	float subtotal;
	float total;
	float iva;
	int vendido;
} detalle[50];


Fecha hoy(){
	time_t t;
	t = time(NULL);
	struct tm *f;
	f = localtime(&t);
	obtener.year = f->tm_year + 1900;
	obtener.month = f->tm_mon + 1;
	obtener.day = f->tm_mday;
	obtener.hour =  f->tm_hour;
	obtener.minutes = f->tm_min;
	obtener.second = f->tm_sec;
	
	return obtener;
}



using namespace std;

void gotoxy(int x, int y);
//-------------- INICIO ------------------
void formato();
void home();

//-------------- PRODUCTOS ------------------
void menuProductos();
void submenuListaProducto();
void submenuModificarProducto(int opcion,Productos p,int posicion);
bool validaProducto(int cod);
void plantillaProducto();
void buscaActualiza(int posicion);
void busquedaProducto();
void getModificarProducto(Productos p, int posicion);
void datosAlmacenar();
void almacenarProducto();
void registroProducto();
bool validaProducto2(int cod);
//void listaProductos();
void listaBodega();
void listaTienda();
void modificarProducto();
void eliminarProducto(); //pedro
int buscarProdCod(char busquedaProductoNom[50]); //pedro
void eliminarProductoCodigo(); //pedro
void elimiarProductosOp();
void menuEliminaccion ();
void comprar(int posicion);

//-------------- PROVEEDOR ------------------
void menuProveedor();
void plantillaProveedor();
bool validaNit(int nit,int modulo);
void sinProveedor(); // se llama en caso registren un producto y no existan proveedores
void listaProveedor();
bool validaProveedor(Proveedor p);
void registroProveedor();
void eliminarProveedor(); //pedro
void buscarProveedorNom(); //pedro
void modificarprovNom();//pedro
void eliminarProveedoresOp();
void eliminarProveedoresCod();
void modificarProveedoresOp();
void modidificarProvCod();
void buscarProveedorCod();
void buscarProveedoresOp();



//-------------- EMPLEADO ------------------
void menuEmployee();
void plantillaEmpleado();
void submenuBusquedaEmpleado(int opcion);
void buscarEmpleadoNombre();
void buscarEmpleadoApellido();
void buscarEmpleadoCodigo();
void busquedaEmpleado();
bool validaCaja(int x);
bool validaNombres(Employee);
void ocultarPassword(char user[], char password[], int modulo);
void guardarPassword(char password[]);
void loguear(char user[], char password[]);
bool validaUsuario(char user[],int tam);
void registroEmpleado();
void listaEmpleado();
void buscarEmpleadoNombre(); //pedro 
void eliminarEmpleado(); //pedro
void eliminarEmpleadosCod();
void modificarEmpleadoNom(); //pedro
void modificarEmpleadoCod();
void modificarEmpleadosOp();
void eliminarEmpleadosOp();


//-------------- CLIENTE ------------------
int mostrarDatosCliente(int nit);
void registroCliente(int nit);
void listaClientes();
int buscarCliente(char busquedaCliente[50]);
void buscarClienteNom();
void buscarClienteOp();
void eliminarClienteNom();
void eliminarClienteCodigo();
void eliminarClienteOp();
void modificarClienteNom();
void modificarClienteCod();
void modificarClienteOp();
void plantillaClientes();
void menuClientes();
void registroCliente2();

//--------------- REPORTES FACTURAS -------------------
void menuReport();

//-------------- FACTURACION ------------------
void formatoLogin();
void login();
void fecha(Fecha d);
void guardarFactura(int codFac, float total, int cantCompra, Cliente client, int posicion, int contCompra);
void formatoFactura();
void productosTienda();
void comprarTienda(int posicion, int cantidad);
int buscarCompra(int codigo);
void restarTienda(int cantidad, int posicion);
void comprarTienda(int posicion, int cantidad, int contCompra, float total,int x, int y);
void comprar(int posicion);
void facturacion(int posicion);



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
	gotoxy(63,14); cout<<"SISTEMA DE FACTURACION \"SUPER TIENDA MAS\"";
	gotoxy(57,16); cout<<"1. Articulos";
	gotoxy(57,17); cout<<"2. Proveedores";
	gotoxy(57,18); cout<<"3. Empleados";
	gotoxy(57,19); cout<<"4. Clientes";
	gotoxy(57,20); cout<<"5. Facturacion";
	gotoxy(57,21); cout<<"6. Reportes";
	gotoxy(57,22); cout<<"7. Salir";
	gotoxy(57,23); cout<<"Digite la opcion deseada: ";
	gotoxy(83,23); cin>>op;
	fflush(stdin);

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
			system("cls");
			menuEmployee();
		break;
		case 4:
			system("cls");
			menuClientes(); 
		break;
		case 5:
			system("cls");
			login();
			getch();
			system("cls");
			home();
		break;
		case 6:
			system("cls");
			menuReport();
			getch();
			system("cls");
			home();
		break;	
		case 7:
			gotoxy(57,25); cout<<"Saliendo del sistema...";
			exit(1);
		break;
		default:
			gotoxy(57,25); cout<<"Opcion invalida, vuelve a intantarlo...";
			getch();
			system("cls");
	}
}


void menuReport(){

	gotoxy(30,2); cout<<"NO FAC";
	gotoxy(45,2); cout<<"NIT";
	gotoxy(70,2); cout<<"CLIENTE";
	gotoxy(90,2); cout<<"EMPLEADO";
	gotoxy(120,2); cout<<"NO. CAJA";
	gotoxy(145,2); cout<<"CANT.COMPRA";
	gotoxy(160,2); cout<<"IVA";
	gotoxy(175,2); cout<<"SUBTOTAL";
	gotoxy(185,2); cout<<"TOTAL";


	for(int i = 0; i < contFac; i++){
		
		gotoxy(30,i+4);cout<<detalle[i].codigo<<endl;
		gotoxy(45,i+4);cout<<detalle[i].nit<<endl;
		gotoxy(70,i+4);cout<<detalle[i].cliente<<endl;
		gotoxy(90,i+4);cout<<detalle[i].empleado<<endl;
		gotoxy(120,i+4);cout<<detalle[i].caja<<endl;
		gotoxy(145,i+4);cout<<detalle[i].vendido<<endl;
		gotoxy(160,i+4);cout<<detalle[i].iva<<endl;
		gotoxy(175,i+4);cout<<detalle[i].subtotal<<endl;
		gotoxy(185,i+4);cout<<detalle[i].total<<endl;
	
		}
}

//menu de clientes
void menuClientes(){
	system("cls");
	formato();
	gotoxy(57,16); cout<<"1. NUEVO CLIENTE";
	gotoxy(57,17); cout<<"2. ELIMINAR CLIENTE";
	gotoxy(57,18); cout<<"3. MODIFICAR CLIENTE";
	gotoxy(57,19); cout<<"4. BUSCAR CLIENTE";
	gotoxy(57,20); cout<<"5. LISTADO DE CLIENTES";
	gotoxy(57,21); cout<<"6. ATRAS";
	gotoxy(57,23); cout<<"Digite una opcion: ";
	gotoxy(76,23); cin>>opProv;
	fflush(stdin);
	
	switch(opProv){
		case 1:
			system("cls");
			registroCliente2();
			getch();
			menuClientes();
		break;
		case 2:
			system("cls");
			eliminarClienteOp();
			getch();
			menuClientes();
		break;
		case 3:
			system("cls");
		    modificarClienteOp();
			getch();
			menuClientes();
			
		break;
		case 4:
			system("cls");
			buscarClienteOp();
			getch();
			menuClientes();
		break;
		case 5:
			system("cls");
			listaClientes();
			getch();
			menuClientes();
		break;
		case 6:
			system("cls");
			home();
		break;
		default:
			gotoxy(57,25); cout<<"Opcion invalida vuelve a intentarlo...";
			getch();
			system("cls");
			menuClientes();
	}
	
}

void menuProductos(){
	int opcion = 0;
	system("cls");
	formato();
	gotoxy(57,16); cout<<"1. NUEVO ARTICULO";
	gotoxy(57,17); cout<<"2. ELIMINAR ARTICULO";
	gotoxy(57,18); cout<<"3. MODIFICAR ARTICULO";
	gotoxy(57,19); cout<<"4. BUSCAR ARTICULO";
	gotoxy(57,20); cout<<"5. LISTADO DE ARTICULOS";
	gotoxy(57,21); cout<<"6. ATRAS";
	gotoxy(57,23); cout<<"Digite una opcion: ";
	gotoxy(76,23); cin>>opcion;
	fflush(stdin);
	
	switch(opcion){
		case 1:
			system("cls");
			registroProducto();
			menuProductos();
		break;
		case 2:
			system("cls");
			elimiarProductosOp();
			menuProductos();
		break;
		case 3:
			system("cls");
			modificarProducto();
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
			submenuListaProducto();
//			listaProductos();
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

void submenuListaProducto(){
	formato();
	int opLista;
	gotoxy(57,14); cout<<"VER LISTA DE PRODUCTOS ALMACENADOS";
	gotoxy(57,16); cout<<"1. Bodega";
	gotoxy(57,17); cout<<"2. Tienda";
	gotoxy(57,19); cout<<"Digite una opcion: ";
	gotoxy(76,19); cin>>opLista;
	switch(opLista){
		case 1:
			system("cls");
			listaBodega();
			getch();
		break;
		case 2:
			system("cls");
			listaTienda();
			getch();
		break;
		default:
			cout<<"Opcion invalida, intente de nuevo...";
			getch();
			system("cls");
	}
}

void listaBodega(){
	gotoxy(80,2); cout<<"LISTADO EN BODEGA";
	plantillaProducto();

	for(int i = 0; i < contBodega; i++){
		gotoxy(3,i+4); cout<<prodBodega[i].info.codigo;
		gotoxy(18,i+4); cout<<prodBodega[i].info.nombre;
		gotoxy(70,i+4); cout<<prodBodega[i].description;
		gotoxy(130,i+4); cout<<prodBodega[i].quantity;
		gotoxy(145,i+4); cout<<prodBodega[i].price;
		gotoxy(160,i+4); cout<<prodBodega[i].peso;
	}
}

void listaTienda(){
	gotoxy(80,2); cout<<"LISTADO EN TIENDA";
	plantillaProducto();

	for(int i = 0; i < contTienda; i++){
		gotoxy(3,i+4); cout<<prodTienda[i].info.codigo;
		gotoxy(18,i+4); cout<<prodTienda[i].info.nombre;
		gotoxy(70,i+4); cout<<prodTienda[i].description;
		gotoxy(130,i+4); cout<<prodTienda[i].quantity;
		gotoxy(145,i+4); cout<<prodTienda[i].price;
		gotoxy(160,i+4); cout<<prodTienda[i].peso;
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
	gotoxy(76,23); cin>>opProv;
	fflush(stdin);
	
		switch(opProv){
		case 1:
			system("cls");
			registroProveedor();
			menuProveedor();
		break;
		case 2:
			system("cls");
			eliminarProveedoresOp();
			getch();
			menuProveedor();
		break;
		case 3:
			system("cls");
			modificarProveedoresOp();
			getch();
			menuProveedor();
			
		break;
		case 4:
			system("cls");
			buscarProveedoresOp();
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
			menuProveedor();
	}
	
}

void menuEmployee(){
	int opcion = 0;
	system("cls");
	formato();
	gotoxy(57,16); cout<<"1. NUEVO EMPLEADO";
	gotoxy(57,17); cout<<"2. ELIMINAR EMPLEADO";
	gotoxy(57,18); cout<<"3. MODIFICAR EMPLEADO";
	gotoxy(57,19); cout<<"4. BUSCAR EMPLEADO";
	gotoxy(57,20); cout<<"5. LISTA DE EMPLEADOS";
	gotoxy(57,21); cout<<"6. ATRAS";
	gotoxy(57,23); cout<<"Digite una opcion: ";
	gotoxy(76,23); cin>>opcion;
	fflush(stdin);
	switch(opcion){
		case 1:
			system("cls");
			registroEmpleado();
			menuEmployee();
		break;
		case 2:
			system("cls");
			eliminarEmpleadosOp();
			getch;
			menuEmployee();
		break;
		case 3:
			getch();
			modificarEmpleadosOp();
			menuEmployee();
		break;
		case 4:
			system("cls");
			busquedaEmpleado();
			getch();
			menuEmployee();
		break;
		case 5:
			system("cls");
			listaEmpleado();
			getch();
			menuEmployee();
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

void registroEmpleado(){
	int num;
	char user[30];
	char password[20];
	
	formato();
	gotoxy(68,13); cout<<"REGISTRO DE NUEVO EMPLEADO";
	gotoxy(57,14); cout<<"NOMBRE:";
	gotoxy(64,14); cin.getline(empleado[contEmpleado].info.nombre,50,'\n');
	fflush(stdin);
	gotoxy(57,15); cout<<"APELLIDO:";
	gotoxy(66,15); cin.getline(empleado[contEmpleado].apellido,50,'\n');
	fflush(stdin);
	
	// revisar que no exista el empleado
	if(validaNombres(empleado[contEmpleado])){
		gotoxy(57,20); cout<<"Este empleado ya existe...";
		memset(empleado[contEmpleado].info.nombre,0,50); // vaciar memoria de variables
		memset(empleado[contEmpleado].apellido,0,50); // vaciar memoria de variables
		getch();
		system("cls");
	}else{
		gotoxy(57,16); cout<<"DIRECCION:";
		gotoxy(68,16); cin.getline(empleado[contEmpleado].info.direccion,100,'\n');
		fflush(stdin);
		gotoxy(57,17); cout<<"EDAD:";
		gotoxy(63,17); cin>>empleado[contEmpleado].edad;
		gotoxy(57,18); cout<<"NO. DE CAJA:";
		gotoxy(70,18); cin>>num;
		fflush(stdin);
		
		while(validaCaja(num)){
			gotoxy(57,20); cout<<"Ese numero de caja ya esta ocupado..."; getch();
			gotoxy(57,20); cout<<"                                     ";
			gotoxy(57,18); cout<<"NO. DE CAJA:";
			gotoxy(70,18); cin>>num;
			fflush(stdin);
		}
		
		gotoxy(57,19); cout<<"Usuario:";
		gotoxy(65,19); cin.getline(user,30,'\n');
		fflush(stdin);

		while(validaUsuario(user,30)){
			memset(user,0,30);
			gotoxy(57,21); cout<<"El usuario ya existe...";
			gotoxy(57,22); cout<<"Intente de nuevo"; getch();
			gotoxy(57,21); cout<<"                       ";
			gotoxy(57,22); cout<<"                ";
			gotoxy(65,19); cout<<"                   ";
			gotoxy(57,19); cout<<"Usuario:";
			gotoxy(65,19); cin.getline(user,30,'\n');
		}
		
		ocultarPassword(user, password,1);
		strcpy(empleado[contEmpleado].cuenta.user, user);

		empleado[contEmpleado].caja = num;
		//Pasar nombre y apellido de empleados a minusculas
		strlwr(empleado[contEmpleado].info.nombre);
		strlwr(empleado[contEmpleado].apellido);
		
		empleado[contEmpleado].info.codigo = codigoEmpleado;
		contEmpleado++; //contador de empleados
		codigoEmpleado++;
	}
}

bool validaCaja(int x){
	for(int i = 0 ; i < contEmpleado; i++){
		if(x == empleado[i].caja) return true;
	}
	return false;
}

bool validaNombres(Employee e){
	for(int i = 0; i < contEmpleado; i++){
		if(strcmp(e.info.nombre, empleado[i].info.nombre) == 0 && strcmp(e.apellido, empleado[i].apellido) == 0){
			return true;
		}
	}
	return false;
}

bool validaUsuario(char user[], int tam){
	user[tam];
	for(int i = 0; i < contEmpleado; i++){
		if(strcmp(user, empleado[i].cuenta.user) == 0) return true;
	}
	return false;
}

void ocultarPassword(char user[], char password[], int modulo){
    int i=0;
    int ingresar;
    fflush(stdin);
    gotoxy(57,20); cout<<"Password: ";
    do{
// 		capturar datos infinitos y hacer una pausa despues de presionae una tecl
        password[i] = (unsigned char)getch();
        if(password[i]!=8){  // Diferente de retroceso
            cout<<"*";
            i++;
        }else if(i > 0){    // presionan retroceso y existe texto
            cout<<(char)8<<(char)32<<(char)8;
            i--;  //borra el espacio en blanco
        }
		fflush(stdin);
    }while(password[i-1]!=13);  // finaliza hasta que presione Enter
    password[i-1] = NULL;
    
    if(modulo == 1) guardarPassword(password);
    if(modulo == 2) loguear(user, password);
   
//  strcpy(empleado[contEmpleado].cuenta.password, password);
//  cout<<empleado[contEmpleado].cuenta.password;
//  getch();
}

void guardarPassword(char password[]){
	strcpy(empleado[contEmpleado].cuenta.password, password);
}

void loguear(char user[], char password[]){
	int posicion = -1;
	for(int i = 0; i < contEmpleado; i++){
		if(strcmp(user, empleado[i].cuenta.user) == 0 && strcmp(password, empleado[i].cuenta.password) == 0) posicion = i;
	}
	
	
	
	if(posicion != -1){
		system("cls");
		gotoxy(76,16); cout<<"Bienvenido "<<empleado[posicion].cuenta.user<<"!";
		gotoxy(78,18); cout<<"Espere...";
		Sleep(1000);
		system("cls");
		facturacion(posicion);
	}else{
		system("cls");
		gotoxy(76,16); cout<<"Credenciales invalidas";
	}
}


//MODULO DE PRODUCTOS//

// ingreso producto
void registroProducto(){
	int newCodigo = 0;
	
	if(contProveedor < 1){
		opProv = 0;
		while(opProv < 1 || opProv > 2){
			system("cls");
			sinProveedor();
		}
	}else{
		cout<<"CODIGO: ";
		cin>>newCodigo;
		fflush(stdin);

		while(validaProducto2(newCodigo)){
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
		
		almacenarProducto();
	
		//Pasar nombre y descripcion de producto a minusculas
		strlwr(producto[contProducto].info.nombre);
		strlwr(producto[contProducto].description);
	}
}

// validar el codigo del producto por eliminacio 
bool validaProducto2(int cod){
	for(int i = 0 ; i < contProducto; i++){
		if(cod == prodBodega[i].info.codigo || cod==prodTienda[i].info.codigo ) return true;
	}
	return false;
}


// validar el codigo del producto
bool validaProducto(int cod){
	for(int i = 0 ; i < contProducto; i++){
		if(cod == producto[i].info.codigo) return true;
	}
	return false;
}

void almacenarProducto(){
	int almacen = 0;
	cout<<"Almacenar en:"<<endl;
	cout<<"1. Bodega"<<endl;
	cout<<"2. Tienda"<<endl;
	cin>>almacen;
	switch(almacen){
		case 1:
			cout<<"BODEGA"<<endl;
			datosAlmacenar();
			prodBodega[contBodega].info.codigo = producto[contProducto].info.codigo;
			strcpy(prodBodega[contBodega].info.nombre, producto[contProducto].info.nombre);
			strcpy(prodBodega[contBodega].description, producto[contProducto].description);
			prodBodega[contBodega].quantity = producto[contProducto].quantity;
			prodBodega[contBodega].price = producto[contProducto].price;
			prodBodega[contBodega].peso = producto[contProducto].peso;
			contBodega++;
			contProducto++; //contador de productos
		break;
		case 2:
			cout<<"TIENDA"<<endl;
			datosAlmacenar();
			prodTienda[contTienda].info.codigo = producto[contProducto].info.codigo;
			strcpy(prodTienda[contTienda].info.nombre, producto[contProducto].info.nombre);
			strcpy(prodTienda[contTienda].description, producto[contProducto].description);
			prodTienda[contTienda].quantity = producto[contProducto].quantity;
			prodTienda[contTienda].price = producto[contProducto].price;
			prodTienda[contTienda].peso = producto[contProducto].peso;
			contTienda++;
			contProducto++; //contador de productos
		break;
		default:
			cout<<"Opcion invalida";
			memset(producto[contProducto].info.nombre,0,50);
			memset(producto[contProducto].description,0,60);
			getch();
	}
}

void datosAlmacenar(){
	cout<<"CANTIDAD: ";
	cin>>producto[contProducto].quantity;
	fflush(stdin);
	cout<<"PRECIO (UNIDAD): Q ";
	cin>>producto[contProducto].price;
	fflush(stdin);
	cout<<"PESO EN GRAMOS: ";
	cin>>producto[contProducto].peso;
	fflush(stdin);
}

void modificarProducto(){
	int update, posicion;
	int opcion = 0;
	formato();
	
	gotoxy(70,14);cout<<"EDITAR PRODUCTO"<<endl;
	gotoxy(57,16);cout<<"Ingrese el codigo : ";
	gotoxy(77,16);cin>>update;
	
	
	if(validaProducto(update)){
		while(opcion != 2){
			cout<<"Los datos guardados son: ";
			gotoxy(3,5); cout<<"CODIGO";
			gotoxy(18,5); cout<<"PRODUCTO";
			gotoxy(70,5); cout<<"DESCRIPCION";
			gotoxy(120,5); cout<<"CANTIDAD";
			gotoxy(145,5); cout<<"PRECIO";
			gotoxy(160,5); cout<<"PESO";
			
			for(int i = 0; i < contProducto; i++){
				if(producto[i].info.codigo == update){
					gotoxy(3,7); cout<<producto[i].info.codigo;
					gotoxy(18,7); cout<<producto[i].info.nombre;
					gotoxy(70,7); cout<<producto[i].description;
					gotoxy(120,7); cout<<producto[i].quantity;
					gotoxy(145,7); cout<<producto[i].price;
					gotoxy(160,7); cout<<producto[i].peso;
					posicion = i;
				}
			}
			gotoxy(1,9); cout<<"Esta seguro de editar estos datos?";
			gotoxy(1,10); cout<<"1. Si";
			gotoxy(1,11); cout<<"2. No";
			gotoxy(1,13); cout<<"Digite una opcion: ";
			gotoxy(20,13); cin>>opcion;
			fflush(stdin);
			submenuModificarProducto(opcion, producto[posicion], posicion);
			opcion = 2;
		}
	}else gotoxy(68,20);cout<<"Ninguna coincidencia...";
	getch();
}
void getModificarProducto(Productos p, int posicion){
	int almacen ;
	memset(p.info.nombre, 0, 50); // liberar memoria
	memset(p.description, 0, 100); // liberar memoria
	p.price = 0;
	p.quantity = 0;
	p.peso = 0;
	
	
	cout<<"NUEVO NOMBRE DEL PRODUCTO: ";
	cin.getline(producto[posicion].info.nombre,50,'\n');
	cout<<"NUEVA DESCRIPCION DEL PRODUCTO: ";
	cin.getline(producto[posicion].description,100,'\n');
	cout<<"NUEVA CANTIDAD: ";
	cin>>producto[posicion].quantity;
	cout<<"NUEVO PRECIO: Q ";
	cin>>producto[posicion].price;
	cout<<"NUEVO PESO: ";
	cin>>producto[posicion].peso;
	
	buscaActualiza(posicion);
	Sleep(500);
	cout<<"Espere..."<<endl;
	Sleep(1000);
	cout<<"Actulizando datos..."<<endl;
	cout<<"Se han actualizado los datos correctamente!";
}


void submenuModificarProducto(int opcion,Productos p,int posicion){
	switch(opcion){
		case 1:
			system("cls");
			getModificarProducto(p, posicion);
			getch();
		break;
		case 2:
			// regresa a menu anterior (menuProductos)
		break;
		default:
			cout<<"Opcion no valida, intente de nuevo...";
			getch();
			system("cls");
	}
}



void buscaActualiza(int posicion){
	int localizar;
	for(int i = 0; i < contTienda; i++){
		if(producto[posicion].info.codigo == prodTienda[i].info.codigo){
			localizar = i;
			strcpy(prodTienda[localizar].info.nombre, producto[posicion].info.nombre);
			strcpy(prodTienda[localizar].description, producto[posicion].description);
			prodTienda[localizar].quantity = producto[posicion].quantity;
			prodTienda[localizar].price = producto[posicion].price;
			prodTienda[localizar].peso = producto[posicion].peso;
		}
	}
	
	for(int i = 0; i < contBodega; i++){
		if(producto[posicion].info.codigo == prodBodega[i].info.codigo){
			localizar = i;
			strcpy(prodBodega[localizar].info.nombre, producto[posicion].info.nombre);
			strcpy(prodBodega[localizar].description, producto[posicion].description);
			prodBodega[localizar].quantity = producto[posicion].quantity;
			prodBodega[localizar].price = producto[posicion].price;
			prodBodega[localizar].peso = producto[posicion].peso;
		}
	}
}




void sinProveedor(){
	formato();
	gotoxy(57,14); cout<<"Primero se debe ingresar el proveedor";
	gotoxy(57,15); cout<<"para poder ingresar un producto...";
	gotoxy(57,17); cout<<"Desea ingresar un proveedor ahora?";
	gotoxy(57,18); cout<<"1. Si";
	gotoxy(57,19); cout<<"2. No";
	gotoxy(57,21); cout<<"Digite una opcion: ";
	gotoxy(76,21); cin>>opProv;
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
	long int nit;
	fflush(stdin);
	cout<<"NOMBRE PROVEEDOR: ";
	cin.getline(proveedor[contProveedor].prov.nombre,50,'\n');
	fflush(stdin);
	if(validaProveedor(proveedor[contProveedor])){
		cout<<"El proveedor ya existe!";
		memset(proveedor[contProveedor].prov.nombre,0,50);
		getch();
	}else{
		cout<<"NIT: ";
		cin>>nit;
//		cin>>proveedor[contProveedor].prov.nit;
		fflush(stdin);
		while(validaNit(nit,2)){
			cout<<"Este nit ya esta en uso";
			cout<<"Digite nuevo nit: ";
			cin>>nit;
			fflush(stdin);
		}
		
		proveedor[contProveedor].prov.nit = nit;
		
		cout<<"DIRECCION: ";
		cin.getline(proveedor[contProveedor].prov.direccion,100,'\n');
		fflush(stdin);
		cout<<"TELEFONO: ";
		cin>>proveedor[contProveedor].prov.telefono;
		fflush(stdin);
		
		
		
		proveedor[contProveedor].prov.codigo = codigoProveedor;
		//Pasar nombre y direccion del proveedor a minusculas
		strlwr(proveedor[contProveedor].prov.nombre);
		strlwr(proveedor[contProveedor].prov.direccion);
		codigoProveedor++;
		contProveedor++; //contador de proveedores		
	}
}

bool validaProveedor(Proveedor p){
	for(int i = 0; i < contProveedor; i++){
		if(strcmp(p.prov.nombre, proveedor[i].prov.nombre) == 0) return true;
	}
	return false;
}

bool validaNit(int nit, int modulo){
	if(modulo == 1){ // para buscar nit en clientes
		for(int i = 0; i < contProveedor; i++){
			if(nit == proveedor[i].prov.nit) return true;
		}
	}

	if(modulo == 2){ //para buscar nit en proveedores
		for(int i = 0; i < contProveedor; i++){
			if(nit == proveedor[i].prov.nit) return true;
		}
	}
	
	if(modulo == 3){ //para buscar nit en clientes
		for(int i = 0; i < contCliente; i++){
			if(nit == cliente[i].info.nit) return true;
		}
	}
	return false;
}

void listaProductos(){
	plantillaProducto();

	for(int i = 0; i < contProducto; i++){
		gotoxy(3,i+4); cout<<producto[i].info.codigo;
		gotoxy(18,i+4); cout<<producto[i].info.nombre;
		gotoxy(70,i+4); cout<<producto[i].description;
		gotoxy(130,i+4); cout<<producto[i].quantity;
		gotoxy(145,i+4); cout<<producto[i].price;
		gotoxy(160,i+4); cout<<producto[i].peso;
	}
}

void listaProveedor(){
	plantillaProveedor();

	for(int i = 0; i < contProveedor; i++){
		gotoxy(40,i+4); cout<<proveedor[i].prov.codigo;
		gotoxy(55,i+4); cout<<proveedor[i].prov.nombre;
		gotoxy(76,i+4); cout<<proveedor[i].prov.nit;
		gotoxy(90,i+4); cout<<proveedor[i].prov.direccion;
		gotoxy(110,i+4); cout<<proveedor[i].prov.telefono;
	}
}

void listaEmpleado(){
	gotoxy(30,2); cout<<"CODIGO";
	gotoxy(45,2); cout<<"NOMBRES";
	gotoxy(70,2); cout<<"APELLIDOS";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(120,2); cout<<"EDAD";
	gotoxy(135,2); cout<<"CAJA";
	gotoxy(140,2); cout<<"USUARIO";
	gotoxy(155,2); cout<<"CLAVE";

	for(int i = 0; i < contEmpleado; i++){
		gotoxy(30,i+4); cout<<empleado[i].info.codigo;
		gotoxy(45,i+4); cout<<empleado[i].info.nombre;
		gotoxy(70,i+4); cout<<empleado[i].apellido;
		gotoxy(90,i+4); cout<<empleado[i].info.direccion;
		gotoxy(120,i+4); cout<<empleado[i].edad;
		gotoxy(135,i+4); cout<<empleado[i].caja;
		gotoxy(140,i+4); cout<<empleado[i].cuenta.user;
		gotoxy(155,i+4); cout<<empleado[i].cuenta.password;
	}
}

void listaClientes(){
	gotoxy(30,2); cout<<"CODIGO";
	gotoxy(45,2); cout<<"NOMBRES";
	gotoxy(70,2); cout<<"APELLIDOS";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(120,2); cout<<"TELEFONO";
	gotoxy(135,2); cout<<"NIT";

	for(int i = 0; i < contCliente; i++){
		gotoxy(30,i+4); cout<<cliente[i].info.codigo;
		gotoxy(45,i+4); cout<<cliente[i].info.nombre;
		gotoxy(70,i+4); cout<<cliente[i].apellido;
		gotoxy(90,i+4); cout<<cliente[i].info.direccion;
		gotoxy(120,i+4); cout<<cliente[i].info.telefono;
		gotoxy(135,i+4); cout<<cliente[i].info.nit;
	
	}
}


void busquedaProducto(){
	int resultados = 0;
	int pos, i;
	char buscar[50];
	memset(buscar,0,50);
	fflush(stdin);
	formato();
	
	gotoxy(70,14); cout<<"BUSQUEDA DE PRODUCTO ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(buscar,50,'\n');
	fflush(stdin);

	for(int i = 0; i < contProducto; i++){
		if(strcmp(buscar,producto[i].info.nombre) == 0){
			pos = i;
			resultados++;
		}
	}
	
	if(resultados > 0){
		system("cls");
		plantillaProducto();
		gotoxy(3,i+4); cout<<producto[pos].info.codigo;
		gotoxy(18,i+4); cout<<producto[pos].info.nombre;
		gotoxy(70,i+4); cout<<producto[pos].description;
		gotoxy(130,i+4); cout<<producto[pos].quantity;
		gotoxy(145,i+4); cout<<producto[pos].price;
		gotoxy(160,i+4); cout<<producto[pos].peso;
	}else{
		gotoxy(57,25);cout<<"No se encontraron resultados...";
	}
	memset(buscar,0,50);
}

void busquedaEmpleado(){
	int opcion = 0;
	int resultados = 0;
	int i = 0;
	char buscar[50];
	fflush(stdin);
	while(opcion != 4){
		formato();
		gotoxy(57,16); cout<<"1. BUSCAR POR NOMBRE";
		gotoxy(57,17); cout<<"2. BUSCAR POR APELLIDO";
		gotoxy(57,18); cout<<"3. BUSCAR POR CODIGO";
		gotoxy(57,19); cout<<"4. ATRAS";
		gotoxy(57,23); cout<<"Digite una opcion: ";
		gotoxy(76,23); cin>>opcion;

		fflush(stdin);
		submenuBusquedaEmpleado(opcion);
	}
}

void submenuBusquedaEmpleado(int opcion){
	switch(opcion){
			case 1:
				system("cls");
				buscarEmpleadoNombre();
				getch();
				system("cls");
			break;
			case 2:
				system("cls");
				buscarEmpleadoApellido();
				getch();
				system("cls");
			break;
			case 3:
				system("cls");
				buscarEmpleadoCodigo();
				getch();
				system("cls");
			break;
			case 4:
				system("cls");
				menuEmployee();
			break;
			default:
				gotoxy(57,25); cout<<"Opcion invalida vuelve a intentarlo...";
				getch();
				system("cls");
		}
}

void buscarEmpleadoNombre(){
	char nombres[50];
	int pos = 0 ;
	formato();
	gotoxy(57,16); cout<<"Ingrese nombres: ";
	gotoxy(77,16); cin.getline(nombres,50,'\n');
	fflush(stdin);

	system("cls");
	cout<<"Buscando..."<<endl;
	Sleep(600);
	cout<<"Espere...";
	Sleep(1000);
	system("cls");
	
	gotoxy(30,2); cout<<"CODIGO";
	gotoxy(45,2); cout<<"NOMBRES";
	gotoxy(70,2); cout<<"APELLIDOS";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(120,2); cout<<"EDAD";
	gotoxy(135,2); cout<<"CAJA";
	gotoxy(140,2); cout<<"USUARIO";
	gotoxy(155,2); cout<<"CLAVE";

	
	for(int i = 0; i < contEmpleado; i++){
		if(strcmp(nombres, empleado[i].info.nombre) == 0){
			filtraEmpleado[pos].info.codigo = empleado[i].info.codigo;
			strcpy(filtraEmpleado[pos].info.nombre, empleado[i].info.nombre);
			strcpy(filtraEmpleado[pos].apellido, empleado[i].apellido);
			strcpy(filtraEmpleado[pos].info.direccion, empleado[i].info.direccion);
			strcpy(filtraEmpleado[pos].cuenta.password,empleado[i].cuenta.password);
			strcpy(filtraEmpleado[pos].cuenta.user,empleado[i].cuenta.user);
			filtraEmpleado[pos].edad = empleado[i].edad;
			filtraEmpleado[pos].caja = empleado[i].caja;
			
			pos++;
			
			for(int i = 0; i < pos; i++){
				gotoxy(30,i+4); cout<<filtraEmpleado[i].info.codigo;
				gotoxy(45,i+4); cout<<filtraEmpleado[i].info.nombre;
				gotoxy(70,i+4); cout<<filtraEmpleado[i].apellido;
				gotoxy(90,i+4); cout<<filtraEmpleado[i].info.direccion;
				gotoxy(120,i+4); cout<<filtraEmpleado[i].edad;
				gotoxy(135,i+4); cout<<filtraEmpleado[i].caja;
				gotoxy(140,i+4); cout<<empleado[i].cuenta.user;
				gotoxy(155,i+4); cout<<empleado[i].cuenta.password;
				
				
			}
		}
	}
}

void buscarEmpleadoApellido(){
	char apellidos[50];
	int pos = 0;
	formato();
	gotoxy(57,16); cout<<"Ingrese apellidos: ";
	gotoxy(88,16); cin.getline(apellidos,50,'\n');
	fflush(stdin);
	
	system("cls");
	cout<<"Buscando..."<<endl;
	Sleep(600);
	cout<<"Espere...";
	Sleep(1000);
	system("cls");
	
	plantillaEmpleado();
	
	for(int i = 0; i < contEmpleado; i++){
		if(strcmp(apellidos, empleado[i].apellido) == 0){
			filtraEmpleado[pos].info.codigo = empleado[i].info.codigo;
			strcpy(filtraEmpleado[pos].info.nombre, empleado[i].info.nombre);
			strcpy(filtraEmpleado[pos].apellido, empleado[i].apellido);
			strcpy(filtraEmpleado[pos].info.direccion, empleado[i].info.direccion);
			strcpy(filtraEmpleado[pos].cuenta.password,empleado[i].cuenta.password);
			strcpy(filtraEmpleado[pos].cuenta.user,empleado[i].cuenta.user);
			filtraEmpleado[pos].edad = empleado[i].edad;
			filtraEmpleado[pos].caja = empleado[i].caja;
			
			pos++;
			
			for(int i = 0; i < pos; i++){
				gotoxy(30,i+4); cout<<filtraEmpleado[i].info.codigo;
				gotoxy(45,i+4); cout<<filtraEmpleado[i].info.nombre;
				gotoxy(70,i+4); cout<<filtraEmpleado[i].apellido;
				gotoxy(90,i+4); cout<<filtraEmpleado[i].info.direccion;
				gotoxy(120,i+4); cout<<filtraEmpleado[i].edad;
				gotoxy(135,i+4); cout<<filtraEmpleado[i].caja;
				gotoxy(140,i+4); cout<<empleado[i].cuenta.user;
				gotoxy(155,i+4); cout<<empleado[i].cuenta.password;
			}
		}
	}
}

void buscarEmpleadoCodigo(){
	int cod;
	formato();
	gotoxy(57,16); cout<<"Ingrese codigo de empleado: ";
	gotoxy(88,16); cin>>cod;
	
	system("cls");
	cout<<"Buscando..."<<endl;
	Sleep(600);
	cout<<"Espere...";
	Sleep(1000);
	system("cls");
	
	plantillaEmpleado();
	
	for(int i = 0; i < contEmpleado; i++){
		if(cod == empleado[i].info.codigo){
			gotoxy(30,i+4); cout<<empleado[i].info.codigo;
			gotoxy(45,i+4); cout<<empleado[i].info.nombre;
			gotoxy(70,i+4); cout<<empleado[i].apellido;
			gotoxy(90,i+4); cout<<empleado[i].info.direccion;
			gotoxy(120,i+4); cout<<empleado[i].edad;
			gotoxy(135,i+4); cout<<empleado[i].caja;
			gotoxy(140,i+4); cout<<empleado[i].cuenta.user;
			gotoxy(155,i+4); cout<<empleado[i].cuenta.password;
		}
	}
}

void plantillaEmpleado(){
	gotoxy(30,2); cout<<"CODIGO";
	gotoxy(45,2); cout<<"NOMBRES";
	gotoxy(70,2); cout<<"APELLIDOS";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(120,2); cout<<"EDAD";
	gotoxy(135,2); cout<<"CAJA";
	gotoxy(140,2); cout<<"USUARIO";
	gotoxy(155,2); cout<<"CLAVE";
}

void plantillaProveedor(){
	gotoxy(40,2); cout<<"CODIGO";
	gotoxy(55,2); cout<<"PROVEEDOR";
	gotoxy(76,2); cout<<"NIT";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(110,2); cout<<"CONTACTO";
}

void plantillaProducto(){
	gotoxy(3,2); cout<<"CODIGO";
	gotoxy(18,2); cout<<"PRODUCTO";
	gotoxy(70,2); cout<<"DESCRIPCION";
	gotoxy(130,2); cout<<"CANTIDAD";
	gotoxy(145,2); cout<<"PRECIO";
	gotoxy(160,2); cout<<"PESO";
}

void insertarFecha(Fecha f){
	gotoxy(125,3); cout<<"Fecha:"<<f.day<<"/"<<f.month<<"/"<<f.year;
	gotoxy(145,3); cout<<"Hora:"<<f.hour<<":"<<f.minutes<<":"<<f.second;
}

void formatoFactura(){
	// formato mostrar productos (izquierda superior)
	for(int x = 2; x < 50; x++){
		gotoxy(x,1); cout<<"*";
		gotoxy(x,3); cout<<"*";
		gotoxy(x,30); cout<<"*";
	}
	for(int y = 2; y < 30; y++){
		gotoxy(2,y); cout<<"*";
		gotoxy(49,y); cout<<"*";
	}
	
	// formato comprar producto (izquierda inferios)
	for(int x = 2; x < 50; x++){
		gotoxy(x,33); cout<<"*";
		gotoxy(x,35); cout<<"*";
		gotoxy(x,40); cout<<"*";
	}
	for(int y = 33; y < 40; y++){
		gotoxy(2,y); cout<<"*";
		gotoxy(49,y); cout<<"*";
	}
	
	//formato factura (derecha)
	for(int x = 60; x < 160; x++){
		gotoxy(x,1); cout<<"*";
		gotoxy(x,7); cout<<"*";
		gotoxy(x,38); cout<<"*";
		gotoxy(x,40); cout<<"*";
	}
	for(int y = 2; y < 40; y++){
		gotoxy(60,y); cout<<"*";
		gotoxy(159,y); cout<<"*";
	}
	
	gotoxy(2,31); cout<<"-2. Guardar Compra";
	gotoxy(2,32); cout<<"-3. Cancelar Compra";
	gotoxy(62,8); cout<<"PRODUCTO";
	gotoxy(90,8); cout<<"PRECIO U";
	gotoxy(110,8); cout<<"CANTIDAD";
	gotoxy(125,8); cout<<"SUBTOTAL";
}

void login(){
	char user[30], password[50];
	formato();
	gotoxy(76,15); cout<<"LOGIN";
	gotoxy(57,17); cout<<"USUARIO:";
	gotoxy(66,17); cin.getline(user,30,'\n');
	ocultarPassword(user, password, 2);
}


void facturacion(int posicion){
	formatoFactura();
	gotoxy(14,2); cout<<"PRODUCTOS DISPONIBLES EN TIENDA";
	gotoxy(8,34); cout<<"COMPRA DE SUS PRODUCTOS EN LA TIENDA";
	gotoxy(3,36); cout<<"Codigo del producto: ";
	gotoxy(3,37); cout<<"Cantidad de articulos:";
	gotoxy(99,2); cout<<"\"SUPER TIENDA MAS\"";
	gotoxy(62,3); cout<<"NIT:";
	gotoxy(62,4); cout<<"NOMBRE:";
	gotoxy(62,6); cout<<"DIRECCION:";
	
	actual = hoy();
	insertarFecha(actual);
	productosTienda();
	comprar(posicion);
}
void productosTienda(){
	int x = 4;
	int y = 5;
	gotoxy(4,4); cout<<"COD";
	gotoxy(10,4); cout<<"PRODUCTO";
	gotoxy(38,4); cout<<"EXISTENCIA";
	for(int i = 0; i < contTienda; i++){
		gotoxy(x,y); cout<<prodTienda[i].info.codigo;
		gotoxy(x+6,y); cout<<prodTienda[i].info.nombre;
		gotoxy(x+38,y); cout<<prodTienda[i].quantity;
		y++;
	}
}

void comprar(int posicion){
	int x = 62;
	int y = 10;
	float total, iva;
	int cod, cantidad, resultado, contCompra, capturar, pos;
	int acumuladorProd = 0;
	long int nit;
	
	gotoxy(66,3); cin>>nit;
	capturar = validaNit(nit, 3);
	if(capturar){
		pos = mostrarDatosCliente(nit);
		strcpy(nombreCompleto, cliente[pos].info.nombre);
		strcpy(nombreCompleto, " ");
		strcpy(nombreCompleto, cliente[pos].apellido);
		gotoxy(69,4); cout<<nombreCompleto;
		gotoxy(72,6); cout<<cliente[pos].info.direccion;
	}else registroCliente(nit);
	
	while(cod != -2){
		gotoxy(24,36); cin>>cod;
		resultado = buscarCompra(cod);
		if(resultado != -1){
			gotoxy(25,37); cin>>cantidad;
			comprarTienda(resultado, cantidad, contCompra, total, x, y);
			y++;
			acumuladorProd += compra[contCompra].quantity;
			total += compra[contCompra].subtotal;
			iva = total *0.12;
			
			gotoxy(81,39); cout<<"    "; //borrar cantidad articulo comprados
			gotoxy(62,39); cout<<"ARTICULOS COMPRADOS: "<<acumuladorProd;
			gotoxy(136,4); cout<<"    "; //borrar total actual y actualizar
			gotoxy(145,39); cout<<"TOTAL: "<<total+iva;
			gotoxy(119,39); cout<<"     ";
			gotoxy(115,39); cout<<"IVA:"<<iva;
		}else if(cod == -2){
			system("cls");
			gotoxy(59,20); cout<<"Guardando factura..";
			pos = mostrarDatosCliente(nit);
			guardarFactura(codFac, total, acumuladorProd, cliente[pos], posicion, contCompra);
		}else if(cod == -3){
			getch();
			system("cls");
			home();
		}
		else {
			gotoxy(3,39); cout<<"El producto no existe...";	
		}
		gotoxy(24,36); cout<<"      ";
		gotoxy(25,37); cout<<"      ";
	}
}


void guardarFactura(int codFac, float total, int cantCompra, Cliente client, int posicion, int contCompra){
	int subtotal;
	char nombreCompleto[70];
	for(int i = 0; i <= contCompra; i++){
		subtotal += compra[i].subtotal;
	}
	detalle[contFac].codigo = contFac;
	detalle[contFac].iva = total *0.12;
	detalle[contFac].subtotal = total;
	detalle[contFac].total = detalle[contFac].iva + total;
	detalle[contFac].vendido = cantCompra;
	detalle[contFac].nit = client.info.nit;
	strcpy(detalle[contFac].cliente, client.info.nombre);
	strcpy(detalle[contFac].cliente, " ");
	strcpy(detalle[contFac].cliente, client.apellido);
	strcpy(nombreCompleto, empleado[posicion].info.nombre);
	strcpy(nombreCompleto, " ");
	strcpy(nombreCompleto, empleado[posicion].apellido);
	strcpy(detalle[contFac].empleado, nombreCompleto);
	detalle[contFac].caja = empleado[posicion].caja;
	codFac++;
	contFac++;
}

int mostrarDatosCliente(int nit){
	int posicion;
	for(int i = 0; i < contCliente; i++){
		if(nit == cliente[i].info.nit) posicion = i;
	}
	return posicion;
}

void registroCliente(int nit){	 
	fflush(stdin);

	gotoxy(62,4); cout<<"NOMBRE:";
	gotoxy(62,5); cout<<"APELLIDO:";
	gotoxy(62,6); cout<<"DIRECCION:";
	gotoxy(125,4); cout<<"TELEFONO:";
	gotoxy(70,4); cin.getline(cliente[contCliente].info.nombre,50,'\n');
	fflush(stdin);
	gotoxy(72,5); cin.getline(cliente[contCliente].apellido,50,'\n');
	fflush(stdin);
	gotoxy(73,6); cin.getline(cliente[contCliente].info.direccion,100,'\n');
	fflush(stdin);
	gotoxy(135,4); cin>>cliente[contCliente].info.telefono;
	fflush(stdin);
		
	//conversion de datos a minusculas
	strlwr(cliente[contCliente].info.nombre);
	strlwr(cliente[contCliente].apellido);
	strlwr(cliente[contCliente].info.direccion);
	cliente[contCliente].info.nit = nit;
	cliente[contCliente].info.codigo = codigoCliente;
	gotoxy(62,5); cout<<"                                               "; //borrar en pantalla apellido
	gotoxy(72,6); cout<<"                                               ";// borrar en pantalla direccion
	gotoxy(125,4); cout<<"                             "; // borrar en pantalla telefono
	
	strcpy(nombreCompleto, cliente[contCliente].info.nombre);        //cambio
	strcpy(nombreCompleto, " ");
	strcpy(nombreCompleto, cliente[contCliente].apellido);

	gotoxy(69,4); cout<<nombreCompleto;
	gotoxy(73,6); cout<<cliente[contCliente].info.direccion;
	contCliente++; //contador de clientes	
	codigoCliente++; //contador de codigo del cliente
}

int buscarCompra(int codigo){
	int posicion;
	for(int i = 0; i < contTienda; i++){
		if(codigo == prodTienda[i].info.codigo){
			posicion = i;
			return posicion;
		}
	}
	return -1;
}

void comprarTienda(int posicion, int cantidad, int contCompra, float total,int x, int y){
	strcpy(compra[contCompra].info.nombre, prodTienda[posicion].info.nombre);
	compra[contCompra].quantity = cantidad;
	compra[contCompra].subtotal = prodTienda[posicion].price * cantidad;
	prodTienda[posicion].quantity -= cantidad;
	
	for(int i = 0; i <= contCompra; i++){
		gotoxy(x,y); cout<<compra[i].info.nombre;
		gotoxy(x+30,y); cout<<prodTienda[posicion].price;
		gotoxy(x+45,y); cout<<compra[i].quantity;
		gotoxy(x+65,y); cout<<compra[i].subtotal;
	}
	contCompra++;
}


            // validacion de codigo
int validaCodigo(int codigo, int modulo){
	
	if(modulo == 1){ // para buscar codigo  clientes
		for(int i = 0; i <contCliente; i++){
			if(codigo == cliente[i].info.codigo) return i;
		}
	}
	if(modulo == 2){ // para buscar codigo  clientes
		for(int i = 0; i <contEmpleado; i++){
			if(codigo == empleado[i].info.codigo) return i;
		}
	}
	if(modulo == 3){ // para buscar codigo  proveedores
		for(int i = 0; i <contProveedor; i++){
			if(codigo == proveedor[i].prov.codigo) return i;
		}
	}
	
	
	if(modulo == 4){ // para buscar codigo  producto Bodega
		for(int i = 0; i <contProducto; i++){
			if(codigo == prodBodega[i].info.codigo) return i;
		}
	}
	if(modulo == 5){ // para buscar codigo  producto tienda
		for(int i = 0; i <contProducto; i++){
			if(codigo == prodTienda[i].info.codigo) return i;
		}
	}
	
	
	return -1;
}


//funcion buscar empleado eliminacion
int buscarEmp(char busquedaEmpleado[50]){
	int i=0;
	bool encontrado=false;
	while (encontrado==false && i<contEmpleado){
		if(strcmp(busquedaEmpleado,empleado[i].info.nombre)==0) encontrado=true;
		else i++;
	}
	if(encontrado==true) return i;
	else return -1;
} 
	
//funcion buscar proveedor para eliminacion
int buscarProv(char busquedaProveedorNom[50]){
	int i=0;
	bool encontrado=false;
	while(encontrado==false && i<contProveedor){
		if(strcmp(busquedaProveedorNom,proveedor[i].prov.nombre)==0) encontrado=true;
		else i++;
	}
	if(encontrado==true) return i;
	else return -1;
} 
 
 // funcion  buscar por nombre para eliminacion de articulos 
 int buscarProd(char busquedaProductoNom[50]){
	int i=0;
	bool encontrado=false;
	while (encontrado==false && i<contProducto){
		if(strcmp(busquedaProductoNom,producto[i].info.nombre)==0) encontrado=true;
		else i++;
	}
	if(encontrado==true) return i;
	else return -1;
}

//funcion buscar cliente

int buscarCliente(char busquedaCliente[50]){
	int i=0;
	bool encontrado=false;
	while (encontrado==false && i<contCliente){
		if(strcmp(busquedaCliente,cliente[i].info.nombre)==0){
			encontrado=true;
		}
		else{
			i++;
		}
	}
		if(encontrado==true){
			return i;
		}
		else{
			return -1;
		}
} 




// MODULO DE CLIENTES//

// PLANTILLAS

void plantillaClientes(){
	gotoxy(30,2); cout<<"CODIGO";
	gotoxy(45,2); cout<<"NOMBRES";
	gotoxy(70,2); cout<<"APELLIDOS";
	gotoxy(90,2); cout<<"DIRECCION";
	gotoxy(120,2); cout<<"TELEFONO";
	gotoxy(135,2); cout<<" NIT ";
}

void registroCliente2(){
	 
	long int nit;
	fflush(stdin);
		
		cout<<" REGISTRO DE CLIENTES "<<endl;	
		cout<<"NIT: ";
		cin>>nit;
		fflush(stdin);
		
		while(validaNit(nit,3)){
			cout<<"Este nit ya esta en uso"<<endl;;
			cout<<"Digite nuevo nit: ";
			cin>>nit;
			fflush(stdin);
		}
		
		cliente[contCliente].info.nit = nit;
		cout<<"NOMBRE : ";
		cin.getline(cliente[contCliente].info.nombre,50,'\n');
		cout<<"APELLIDO : ";
		cin.getline(cliente[contCliente].apellido,50,'\n');
		cout<<"DIRECCION: ";
		cin.getline(cliente[contCliente].info.direccion,100,'\n');
		fflush(stdin);
		cout<<"TELEFONO: ";
		cin>>cliente[contCliente].info.telefono;
		fflush(stdin);
		
		//conversion de datos a minusculas
		strlwr(cliente[contCliente].info.nombre);
		strlwr(cliente[contCliente].apellido);
		strlwr(cliente[contCliente].info.direccion);
		contCliente++; //contador de clientes	
		codigoCliente++; //contador de codigo del cliente
		cliente[contCliente].info.codigo = codigoCliente;
		
		
		cout<<"\n EL REGISTRO SE INGRESO CON EXITO!!";		
}	

//buscar Cliente 

void buscarClienteNom(){
 	
	system("cls");
	char nomCliente[50];

	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE EMPLEADOS ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(nomCliente,50,'\n');
	int pos=buscarCliente(nomCliente);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL CLIENTE NO EXISTE!! ";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		plantillaClientes();
	 	gotoxy(30,4); cout<<cliente[pos].info.codigo;
		gotoxy(45,4); cout<<cliente[pos].info.nombre;
		gotoxy(70,4); cout<<cliente[pos].apellido;
		gotoxy(90,4); cout<<cliente[pos].info.direccion;
		gotoxy(120,4); cout<<cliente[pos].info.telefono;
		gotoxy(135,4); cout<<cliente[pos].info.nit;
				
	}
}


void buscarClienteCodigo(){
 	
	system("cls");
	int codigoCliente;

	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE EMPLEADOS ";
	gotoxy(57,16); cout<<"Ingrese el codigo: ";
	gotoxy(77,16); cin>>codigoCliente;
	
	int pos=validaCodigo(codigoCliente,1);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL CODIGO NO EXISTE!!";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		plantillaClientes();
	 	gotoxy(30,4); cout<<cliente[pos].info.codigo;
		gotoxy(45,4); cout<<cliente[pos].info.nombre;
		gotoxy(70,4); cout<<cliente[pos].apellido;
		gotoxy(90,4); cout<<cliente[pos].info.direccion;
		gotoxy(120,4); cout<<cliente[pos].info.telefono;	
		gotoxy(135,4); cout<<cliente[pos].info.nit;	
	}
}

void buscarClienteOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE CLIENTES "<<endl;  
	gotoxy(60,16); cout<<"1. BUSQUEDA POR NOMBRE";
	gotoxy(60,18); cout<<"2. BUSQUEDA POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			buscarClienteNom();
			getch();
			buscarClienteOp();
			break;
		case 2:
			system("cls");
			buscarClienteCodigo();
			getch();
			buscarClienteOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuClientes();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 buscarClienteOp();		
	}
	
	}while(op!=3);

}

// Eliminar Cliente
void eliminarClienteNom(){
 	
	system("cls");
	char nomCliente[50];

	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE EMPLEADOS ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(nomCliente,50,'\n');
	
	int pos=buscarCliente(nomCliente);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL CLIENTE NO EXISTE!!";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		for( int i=pos; i<contCliente;i++ ){
	 	
		strcpy(cliente[i].info.nombre, cliente[i+1].info.nombre);
		strcpy(cliente[i].apellido, cliente[i+1].apellido);
		strcpy(cliente[i].info.direccion,cliente[i+1].info.direccion);
		cliente[i].info.telefono = cliente[i+1].info.telefono;
		cliente[i].info.nit = cliente[i+1].info.nit;
		cliente[i].info.codigo = cliente[i+1].info.codigo ;
		}
		contCliente--;
		formato();
		gotoxy(68,20); cout<<"EL REGISTRO SE ELIMINO CON EXITO !!";
		getch();		
	}
}


void eliminarClienteCodigo(){
 	
	system("cls");
	int codigoCliente;

	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE CLIENTES ";
	gotoxy(57,16); cout<<"Ingrese el codigo : ";
	gotoxy(77,16); cin>>codigoCliente;
	
	int pos=validaCodigo(codigoCliente,1);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL CLIENTE NO EXISTE!!";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		for( int i=pos; i<contCliente;i++ ){

		strcpy(cliente[i].info.nombre, cliente[i+1].info.nombre);
		strcpy(cliente[i].apellido, cliente[i+1].apellido);
		strcpy(cliente[i].info.direccion,cliente[i+1].info.direccion);
		cliente[i].info.telefono = cliente[i+1].info.telefono;
		cliente[i].info.codigo = cliente[i+1].info.codigo ;
		cliente[i].info.nit = cliente[i+1].info.nit; 
		}
		contCliente--;
		formato();
		gotoxy(68,20); cout<<"EL REGISTRO SE ELIMINO CON EXITO !!";
		getch();		
	}
}
void eliminarClienteOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE CLIENTES "<<endl;  
	gotoxy(60,16); cout<<"1. ELIMINACION POR NOMBRE";
	gotoxy(60,18); cout<<"2. ELIMINACION POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			eliminarClienteNom();
			getch();
			eliminarClienteOp();
			break;
		case 2:
			system("cls");
			eliminarClienteCodigo();
			getch();
			eliminarClienteOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuClientes();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 eliminarClienteOp();		
	}
	
	}while(op!=3);

}

// MODIFICACION DE CLIENTES
void modificarClienteOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE CLIENTES "<<endl;  
	gotoxy(60,16); cout<<"1. MODIFICACION POR NOMBRE";
	gotoxy(60,18); cout<<"2. MODIFICACION POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			modificarClienteNom();
			getch();
			modificarClienteOp();
			break;
		case 2:
			system("cls");
			modificarClienteCod();
			getch();
			modificarClienteOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuClientes();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 modificarClienteOp();		
	}
	
	}while(op!=3);

}

void modificarClienteNom(){
 	
	system("cls");
	char nomCliente[50];
	int nit;
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE CLIENTES ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(nomCliente,50,'\n');
	
	int pos=buscarCliente(nomCliente);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL CLIENTE NO EXISTE!!";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		
		cout<<"INGRESE NUEVOS DATOS DEL CLIENTE"<<endl;
		cout<<"NIT ";
		cin>>nit;
		fflush(stdin);
		
		while(validaNit(nit,3)){
			cout<<"Este nit ya esta en uso"<<endl;;
			cout<<"Digite un nuevo nit: ";
			cin>>nit;
			fflush(stdin);
		}
		
		cliente[pos].info.nit = nit;
		cout<<"NOMBRE : ";
		cin.getline(cliente[pos].info.nombre,50,'\n');
		cout<<"APELLIDO : ";
		cin.getline(cliente[pos].apellido,50,'\n');
		cout<<"DIRECCION: ";
		cin.getline(cliente[pos].info.direccion,100,'\n');
		fflush(stdin);
		cout<<"TELEFONO: ";
		cin>>cliente[pos].info.telefono;
		fflush(stdin);
		
		//conversion de datos a minusculas
		strlwr(cliente[pos].info.nombre);
		strlwr(cliente[pos].apellido);
		strlwr(cliente[pos].info.direccion);
		
		cout<<"\n EL REGISTRO SE MODIFICO CON EXITO!!";
				
		}			
	}

void modificarClienteCod(){
 	
	system("cls");
	int codigoCliente;
	int nit;
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE CLIENTES ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin>>codigoCliente;
	
	int pos=validaCodigo(codigoCliente,1);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL CLIENTE NO EXISTE!!";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		
		cout<<"INGRESE NUEVOS DATOS DEL CLIENTE"<<endl;
		cout<<"NIT ";
		cin>>nit;
		fflush(stdin);
		
		while(validaNit(nit,3)){
			cout<<"Este nit ya esta en uso"<<endl;;
			cout<<"Digite un nuevo nit: ";
			cin>>nit;
			fflush(stdin);
		}
		
		cliente[pos].info.nit = nit;
		cout<<"NOMBRE : ";
		cin.getline(cliente[pos].info.nombre,50,'\n');
		cout<<"APELLIDO : ";
		cin.getline(cliente[pos].apellido,50,'\n');
		cout<<"DIRECCION: ";
		cin.getline(cliente[pos].info.direccion,100,'\n');
		fflush(stdin);
		cout<<"TELEFONO: ";
		cin>>cliente[pos].info.telefono;
		fflush(stdin);
		
		//conversion de datos a minusculas
		strlwr(cliente[pos].info.nombre);
		strlwr(cliente[pos].apellido);
		strlwr(cliente[pos].info.direccion);
		
		cout<<"\n EL REGISTRO SE MODIFICO CON EXITO!!";
				
		}			
	}

 //MODULO DE EMPLEADOS//
 
 //MODIFICACION DE EMPLEADOS
 
 
void modificarEmpleadoCod(){
 	
	system("cls");
	int codigo,cajaEmp,nit;
	char validaNom[50];
	char modificarEmp[50];
	char validaApe[50];
	int num;
	char user[30];
	char password[20];

	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE EMPLEAEDOS ";
	gotoxy(57,16); cout<<"Ingrese el codigo: ";
	gotoxy(77,16); cin>>codigo;
	fflush(stdin);
	
	int pos=validaCodigo(codigo,2);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL EMPLEADO NO EXISTE!!";
		getch();
	
		
	}else{
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		
		cout<<"MODIFICACION DE EMPLEADOS "<<endl;
		cout<<"NOMBRE: ";
		cin.getline(validaNom,50,'\n');
		
		int nom=buscarEmp(validaNom);
		
		if(nom==-1){
		strcpy(empleado[pos].info.nombre, validaNom);
		cout<<"APELLIDO: ";
		cin.getline(empleado[pos].apellido,50,'\n');
		cout<<"DIRECCION: ";
		cin.getline(empleado[pos].info.direccion,50,'\n');
		cout<<"EDAD: ";
		cin>>empleado[pos].edad;
		cout<<"NO. DE CAJA: ";
		cin>>cajaEmp;
		
		while(validaCaja(cajaEmp)){
			
			cout<<"EL NO. DE CAJA YA ESTA EN USO "<<endl;;
			cout<<"ingrese nuevamente "<<endl;
			cin>>cajaEmp;
			
		}
		empleado[pos].caja=cajaEmp;
		fflush(stdin);

		cout<<"Usuario:";
		cin.getline(user,30,'\n');
		

		while(validaUsuario(user,30)){
		memset(user,0,30);
		cout<<"El usuario ya existe..."<<endl;
		 cout<<"Intente de nuevo"<<endl;
		 cout<<"Usuario: ";
		 cin.getline(user,30,'\n');
		}
		
		ocultarPassword(user,password,1);
		strcpy(empleado[pos].cuenta.user, user);

		empleado[pos].caja = num;
		//Pasar nombre y apellido de empleados a minusculas
		strlwr(empleado[pos].info.nombre);
		strlwr(empleado[pos].apellido);
		cout<<"\n EL REGISTRO SE MODIFICO CON EXITO!!";
			
		}
		else{
			
			cout<<"EL NOMBRE YA EXISTE ";
			getch();
		}		
	}	
}
 
 void modificarEmpleadoNom(){
 	
	system("cls");
	char modificarEmp[50];
	char validaNom[50];
	char validaApe[50];
	int cajaEmp;
	int num;
	char user[30];
	char password[20];
	
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE EMPLEADOS ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(modificarEmp,50,'\n');
	int pos=buscarEmp(modificarEmp);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL EMPLEADO NO EXISTE ";
		getch();
	
		
	}else{
		
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		
		cout<<"MODIFICACION DE EMPLEADOS "<<endl;
		cout<<"NOMBRE: ";
		cin.getline(validaNom,50,'\n');
		
		int nom=buscarEmp(validaNom);
		
		if(nom==-1){
		strcpy(empleado[pos].info.nombre, validaNom);
		cout<<"APELLIDO: ";
		cin.getline(empleado[pos].apellido,50,'\n');
		cout<<"DIRECCION: ";
		cin.getline(empleado[pos].info.direccion,50,'\n');
		cout<<"EDAD: ";
		cin>>empleado[pos].edad;
		cout<<"NO. DE CAJA: ";
		cin>>cajaEmp;
		
		while(validaCaja(cajaEmp)){
			
			cout<<"EL NO. DE CAJA YA ESTA EN USO "<<endl;;
			cout<<"ingrese nuevamente "<<endl;
			cin>>cajaEmp;
			
		}
		
		empleado[pos].caja = num;
		//Pasar nombre y apellido de empleados a minusculas
		strlwr(empleado[pos].info.nombre);
		strlwr(empleado[pos].apellido);
		cout<<"\n EL REGISTRO SE MODIFICO CON EXITO!!";
			
		}
		else{
			
			cout<<"EL NOMBRE YA EXISTE ";
			getch();
		}
	
	}	
}

void modificarEmpleadosOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE EMPLEADOS "<<endl;  
	gotoxy(60,16); cout<<"1. MODIFICACION POR NOMBRE";
	gotoxy(60,18); cout<<"2. MODIFICACION POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			modificarEmpleadoNom();
			getch();
		    modificarEmpleadosOp();
			break;
		case 2:
			system("cls");
			modificarEmpleadoCod();
			getch();
			modificarEmpleadosOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuEmployee();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 modificarEmpleadosOp();		
	}
	
	}while(op!=3);

}

// ELIMINACION DE EMPLEADOS


void eliminarEmpleado(){
	
	char nombre[50];
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE EMPLEADOS ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(nombre,50,'\n');
	fflush(stdin);

	
	int pos=buscarEmp(nombre);
	if(pos==-1){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL EMPLEADO NO EXISTE ";
		getch();
	}
	else{
		
		for (int i=pos; i<contEmpleado; i++){
			
			empleado[i]=empleado[i+1];
			strcpy(empleado[i].cuenta.password,empleado[i+1].cuenta.password);
			strcpy(empleado[i].cuenta.user,empleado[i+1].cuenta.user);			
			strcpy(empleado[i].info.nombre,empleado[i+1].info.nombre);
			strcpy(empleado[i].apellido,empleado[i+1].apellido);
			strcpy(empleado[i].info.direccion,empleado[i+1].info.direccion);
			empleado[i].edad = empleado[i+1].edad;
			empleado[i].caja = empleado[i+1].caja;
			
		}
		contEmpleado--;
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1300);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EMPLEADO ELIMINADO CON EXITO ";
		getch();
			
		}
	}

void eliminarEmpleadoCod(){
	
	int codigo;
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE EMPLEADOS ";
	gotoxy(57,16); cout<<"Ingrese el coidgo : ";
	gotoxy(77,16); cin>>codigo;
	fflush(stdin);

	
	int pos=validaCodigo(codigo,2);
	if(pos==-1){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL EMPLEADO NO EXISTE ";
		getch();
	}
	else{
		
		for (int i=pos; i<contEmpleado; i++){
			
			empleado[i]=empleado[i+1];
			strcpy(empleado[i].cuenta.password,empleado[i+1].cuenta.password);
			strcpy(empleado[i].cuenta.user,empleado[i+1].cuenta.user);			
			strcpy(empleado[i].info.nombre,empleado[i+1].info.nombre);
			strcpy(empleado[i].apellido,empleado[i+1].apellido);
			strcpy(empleado[i].info.direccion,empleado[i+1].info.direccion);
			empleado[i].edad = empleado[i+1].edad;
			empleado[i].caja = empleado[i+1].caja;
			
		}
		contEmpleado--;
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EMPLEADO ELIMINADO CON EXITO ";
		getch();
			
		}
	}
		
void eliminarEmpleadosOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"ELIMINACION  DE EMPLEADOS "<<endl;  
	gotoxy(60,16); cout<<"1. ELIMINACION POR NOMBRE";
	gotoxy(60,18); cout<<"2. ELIMINACION POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			eliminarEmpleado();
			getch();
		    eliminarEmpleadosOp();
			break;
		case 2:
			system("cls");
			eliminarEmpleadoCod();
			getch();
	    	eliminarEmpleadosOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuEmployee();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 eliminarEmpleadosOp();	
	}
	
	}while(op!=3);

}

/// MODULO DE PROVEEDORES ///

//MOODIFICACION

 void modificarprovNom(){
 	
	system("cls");
	char modificarProv[50];
	char validaNom[50];
	int nitProv;
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE PROVEEDOR ";
	gotoxy(57,16); cout<<"Ingrese el nombre: ";
	gotoxy(77,16); cin.getline(modificarProv,50,'\n');
	fflush(stdin);
	int pos=buscarProv(modificarProv);
	
	if(pos==-1 ){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL PROVEEDOR NO EXISTE ";
		getch();
	
		
	}else{
		system("cls");
		
	 	cout<<"MODIFICACION DE PROVEEDOR "<<endl;
		cout<<"NOMBRE: ";
		cin.getline(validaNom,50,'\n');
		
		int nom=buscarProv(validaNom);
		if(nom==-1){
		strcpy(proveedor[pos].prov.nombre, validaNom);
		cout<<"DIRECION: ";
		cin.getline(proveedor[pos].prov.direccion,50,'\n');
		cout<<"NIT: ";
		cin>>nitProv;
		while(validaNit(nitProv,2)){
			
			cout<<"el nit ya esta en uso ";
			cout<<"ingrese nuevamente "<<endl;
			cin>>nitProv;
			
		}
		proveedor[pos].prov.nit=nitProv;
		cout<<"TELEFONO: ";
		cin>>proveedor[pos].prov.telefono;
			
		}
		else{
			
			cout<<"EL NOMBRE YA EXISTE ";
			getch;
		}	
		
		
		
		
	} 
}

 void modificarprovCod(){
 	
	system("cls");
	char validaNom[50];
	int codigo,nitProv;
	
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE PROVEEDOR ";
	gotoxy(57,16); cout<<"Ingrese el codigo: ";
	gotoxy(77,16); cin>>codigo;
	int pos=validaCodigo(codigo,3);
	
	fflush(stdin);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL PROVEEDOR NO EXISTE ";
		getch();
	
		
	}else{
		system("cls");
		
	 	cout<<"MODIFICACION DE PROVEEDOR "<<endl;
		cout<<"NOMBRE: ";
		cin.getline(validaNom,50,'\n');
		
		int nom=buscarProv(validaNom);
		if(nom==-1){
		strcpy(proveedor[pos].prov.nombre, validaNom);
		cout<<"DIRECION: ";
		cin.getline(proveedor[pos].prov.direccion,50,'\n');
		cout<<"NIT: ";
		cin>>nitProv;
		while(validaNit(nitProv,2)){
			
			cout<<"el nit ya esta en uso ";
			cout<<"ingrese nuevamente "<<endl;
			cin>>nitProv;
			
		}
		proveedor[pos].prov.nit=nitProv;
		cout<<"TELEFONO: ";
		cin>>proveedor[pos].prov.telefono;
			
		}
		else{
			
			cout<<"EL NOMBRE YA EXISTE ";
			getch;
		}	
	
	}
} 

void modificarProveedoresOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"MODIFICACION DE PROVEEDORES "<<endl;  
	gotoxy(60,16); cout<<"1. MODIFICACION POR NOMBRE";
	gotoxy(60,18); cout<<"2. MODIFICACION POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			modificarprovNom();
			getch();
		    modificarProveedoresOp();
			break;
		case 2:
			system("cls");
			modificarprovCod();
			getch();
	    	modificarProveedoresOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuProveedor();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 modificarProveedoresOp();
	}
	
	}while(op!=3);

}


// ELIMINACION DE PROVEEDORES
	
void eliminarProveedor(){
	
	char nombre[50];
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE PROVEEDORES ";
	gotoxy(57,16); cout<<"Ingrese el nombre : ";
	gotoxy(77,16); cin.getline(nombre,50,'\n');
	fflush(stdin);
	int pos=buscarProv(nombre);
	if(pos==-1){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL PROVEEDOR NO EXISTE ";
		getch();
	}
	else{
		
		for (int i=pos; i<contProveedor; i++){
			strcpy(proveedor[i].prov.nombre,proveedor[i+1].prov.nombre);
			strcpy(proveedor[i].prov.direccion,proveedor[i+1].prov.direccion);
			proveedor[i].prov.codigo = proveedor[i+1].prov.codigo;
			proveedor[i].prov.nit = proveedor[i+1].prov.nit;
			proveedor[i].prov.telefono = proveedor[i+1].prov.telefono;

		}
		contProveedor--;	
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"PROVEEDOR ELIMINADO CON EXITO ";
		getch();
			
		
		}
	}
	
	
void eliminarProveedorCod(){
	
	int codigo;
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE PROVEEDORES ";
	gotoxy(57,16); cout<<"Ingrese el codigo : ";
	gotoxy(77,16); cin>>codigo;
	fflush(stdin);
	int pos=validaCodigo(codigo,3);
	if(pos==-1){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL PROVEEDOR NO EXISTE ";
		getch();
	}
	else{
		
		for (int i=pos; i<contProveedor; i++){
			
			
			
			strcpy(proveedor[i].prov.nombre,proveedor[i+1].prov.nombre);
			strcpy(proveedor[i].prov.direccion,proveedor[i+1].prov.direccion);
			proveedor[i].prov.codigo = proveedor[i+1].prov.codigo;
			proveedor[i].prov.nit = proveedor[i+1].prov.nit;
			proveedor[i].prov.telefono = proveedor[i+1].prov.telefono;

		}
		contProveedor--;	
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"PROVEEDOR ELIMINADO CON EXITO!!";
		getch();
			
		}
	}

void eliminarProveedoresOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE PROVEEDORES "<<endl;  
	gotoxy(60,16); cout<<"1. ELIMINACION POR NOMBRE";
	gotoxy(60,18); cout<<"2. ELIMINACION POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			eliminarProveedor();
			getch();
		    eliminarProveedoresOp();
			break;
		case 2:
			system("cls");
			eliminarProveedorCod();
			getch();
	    	eliminarProveedoresOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuProveedor();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 eliminarProveedoresOp();
	}
	
	}while(op!=3);
}

//BUSCAR PROVEEDOR

void buscarProveedorNom(){
	
	char eliminarProveedor[50];
	
	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE PROVEEDOR ";
	gotoxy(57,16); cout<<"Ingrese el nombre : ";
	gotoxy(77,16); cin.getline(eliminarProveedor,50,'\n');
	int pos=buscarProv(eliminarProveedor);
	
	if(pos==-1 ){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL PROVEEDOR NO EXISTE !!!";
		getch();
	}else{
		system("cls");
		plantillaProveedor();
		
		gotoxy(40,4); cout<<proveedor[pos].prov.codigo;
		gotoxy(55,4); cout<<proveedor[pos].prov.nombre;
		gotoxy(76,4); cout<<proveedor[pos].prov.nit;
		gotoxy(90,4); cout<<proveedor[pos].prov.direccion;
		gotoxy(110,4); cout<<proveedor[pos].prov.telefono;
	}
} 

void buscarProveedorCod(){
	
	int codigo;
	
	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE PROVEEDOR ";
	gotoxy(57,16); cout<<"Ingrese el codigo : ";
    gotoxy(77,16);; cin>>codigo;
	int pos=validaCodigo(codigo,3);
	
	if(pos==-1 ){
			formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL PROVEEDOR NO EXISTE!! ";
		getch();
	}else{
		system("cls");
		plantillaProveedor();
		
		gotoxy(40,4); cout<<proveedor[pos].prov.codigo;
		gotoxy(55,4); cout<<proveedor[pos].prov.nombre;
		gotoxy(76,4); cout<<proveedor[pos].prov.nit;
		gotoxy(90,4); cout<<proveedor[pos].prov.direccion;
		gotoxy(110,4); cout<<proveedor[pos].prov.telefono;
	}
}
void buscarProveedoresOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE PROVEEDORES "<<endl;  
	gotoxy(60,16); cout<<"1. BUSQUEDA POR NOMBRE";
	gotoxy(60,18); cout<<"2. BUSQUEDA POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			buscarProveedorNom();
			getch();
		    buscarProveedoresOp();
			break;
		case 2:
			system("cls");
			buscarProveedorCod();
			getch();
	    	buscarProveedoresOp();
			break;
		case 3:
			
		 	gotoxy(60,24);	cout<<" Saliendo.....";
	        Sleep(1300);	
	        menuProveedor();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1300);
		 buscarProveedoresOp();	
	}
	
	}while(op!=3);

}

//ELIMINACION DE PRODUCTO



void eliminarProductoCodigo(){
	
	int codigo;
	formato();
	gotoxy(70,14); cout<<"ELIMINACION DE PRODUCTO ";
	gotoxy(57,16); cout<<"Ingrese el codigo : ";
	gotoxy(77,16); cin>>codigo;
	fflush(stdin);
	int bod=validaCodigo(codigo,4);
	int tienda=validaCodigo(codigo,5); 
	
	if(bod==-1){
		
	}
	else{
		for(int i=0; i<contProducto; i++ ){
		
			if(codigo==prodBodega[i].info.codigo){
				
			
			prodBodega[i]=prodBodega [i+1];
			strcpy(prodBodega[i].info.nombre, prodBodega[i+1].info.nombre);
			strcpy(prodBodega[i].description,prodBodega[i+1].description);
			prodBodega[i].quantity = prodBodega[i+1].quantity;
			prodBodega[i].price = prodBodega[i+1].price;
			prodBodega[i].peso =prodBodega[i+1].peso;
			prodBodega[i].info.codigo = prodBodega[i+1].info.codigo;
			
			}
		}
		contProducto--;	
		contBodega--;
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"PRODUCTO ELIMINADO CON EXITO!!";
		getch();
		
	}

	if(tienda==-1){
		
	}
	else{
		for(int i=0; i<contProducto; i++ ){
		
			if(codigo==prodTienda[i].info.codigo){
				
			prodTienda[i]=prodTienda[i+1];
			strcpy(prodTienda[i].info.nombre, prodTienda[i+1].info.nombre);
			strcpy(prodTienda[i].description, prodTienda[i+1].description);
			prodTienda[i].quantity = prodTienda[i+1].quantity;
			prodTienda[i].price = prodTienda[i+1].price;
			prodTienda[i].peso = prodTienda[i+1].peso;
			prodTienda[i].info.codigo = prodTienda[i+1].info.codigo;	
			}
			
		}
		contProducto--;	
		contTienda--;
		system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"PRODUCTO ELIMINADO CON EXITO!!";
		getch();
		
	}	
		
		if(bod==-1 && tienda==-1){
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20);cout<<" EL CODIGO NO EXISTE ";
		getch();
		}
}
	

void eliminarProducto(){
	
	bool cambio=false;
	char nombre[50];
	formato();
	gotoxy(70,14);cout<<" INGRESE EL NOMBRE "<<endl;
	gotoxy(57,16);cout<<"nombre: ";
	gotoxy(77,16);cin.getline(nombre,50,'\n');

		for(int i=0; i<contProducto; i++ ){
		
			if(strcmp(nombre,prodBodega[i].info.nombre)==0  ){
				
			cambio=true;
			
			strcpy(prodBodega[i].info.nombre, prodBodega[i+1].info.nombre);
			strcpy(prodBodega[i].description,prodBodega[i+1].description);
			prodBodega[i].quantity = prodBodega[i+1].quantity;
			prodBodega[i].price = prodBodega[i+1].price;
			prodBodega[i].peso =prodBodega[i+1].peso;
			prodBodega[i].info.codigo = prodBodega[i+1].info.codigo;
			
			contProducto--;	
			contBodega--;
			}
			if(strcmp(nombre,prodTienda[i].info.nombre)==0){
			cambio=true;
			strcpy(prodTienda[i].info.nombre, prodTienda[i+1].info.nombre);
			strcpy(prodTienda[i].description, prodTienda[i+1].description);
			prodTienda[i].quantity = prodTienda[i+1].quantity;
			prodTienda[i].price = prodTienda[i+1].price;
			prodTienda[i].peso = prodTienda[i+1].peso;
			prodTienda[i].info.codigo = prodTienda[i+1].info.codigo;	
			
			contProducto--;	
			contTienda--;
					
			}
		}
		
		if(cambio==true){
		   	system("cls");
		formato();
		gotoxy(68,20); cout<<"Buscando registro.....";
		Sleep(1000);
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL PRODUCTO SE ELIMINO CON EXITO !! ";
		getch();
		
		}else{
			system("cls");
			formato();
			gotoxy(68,20); cout<<"Buscando registro.....";
			Sleep(1000);
			system("cls");
			formato();
			gotoxy(68,20); cout<<"EL PRODUCTO NO EXISTE!! ";
			getch();	
		}
}



void elimiarProductosOp(){
		
	system("cls");
	int op;
	formato();
	gotoxy(60,14); cout<<"ELIMINACION DE ARTICULOS  "<<endl;  
	gotoxy(60,16); cout<<"1. ELIMINAR POR NOMBRE";
	gotoxy(60,18); cout<<"2. ELIMINAR POR CODIGO ";
	gotoxy(60,20); cout<<"3. SALIR. ";
	gotoxy(60,22); cout<<"DIGITE UN OPCION: "; cin>>op;
	
	fflush(stdin);

	do{
	switch(op){
		case 1:
			system("cls");
			eliminarProducto();
			elimiarProductosOp();
			break;
		case 2:
			system("cls");
			eliminarProductoCodigo();
			elimiarProductosOp();
			break;
		case 3:
			
		 gotoxy(60,24);	cout<<" saliendo...";
	
	      Sleep(1000);	
	      menuProductos();
			break;
			
		default:
		 gotoxy(60,24);	cout<<"opcion invalida !! ";
		 Sleep(1000);
		 elimiarProductosOp();		
	}
	
	}while(op!=3);

}
