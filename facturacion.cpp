#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int op, opProv, contCliente, contProveedor, contProducto, contEmpleado;

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
	int unidades;
}producto[20], filtrado[20];

struct Proveedor{
	struct Datos prov;
}proveedor[20];

struct Employee{
	struct Datos info;
	char apellido[50];
	int edad;
	int caja;
}empleado[20], filtraEmpleado[20];

struct Cliente{
	struct Datos info;
}cliente[20];

using namespace std;

void gotoxy(int x, int y);
//-------------- INICIO ------------------
void formato();
void home();

//-------------- PRODUCTOS ------------------
bool validaProducto(int cod);
void plantillaProducto();
void busquedaProducto();
void getModificarProducto(Productos p, int posicion);
void submenuModificarProducto(int opcion,Productos p,int posicion);
void menuProductos();
void registroProducto();
void listaProductos();
void modificarProducto();
void eliminarProducto(); //pedro
 int buscarProdCod(char busquedaProductoNom[50]); //pedro
 void eliminarProductoCodigo(); //pedro



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
void registroEmpleado();
void listaEmpleado();
void buscarEmpleadoNombre(); //pedro 
void eliminarEmpleado(); //pedro


//-------------- FACTURACION ------------------
void formatoFactura();
void productosTienda();
void facturacion();


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
	gotoxy(63,14); cout<<"SISTEMA DE FACTURACION \"EL DUENDE\"";
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
//			system("cls");
//			menuClient(); PENDIENTEEEEEEE
		break;
		case 5:
			system("cls");
			facturacion();
			getch();
			system("cls");
		break;
		case 6:
//			system("cls");
//			menuReport(); PENDIENTEEEEEE
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
			eliminarProductoCodigo();
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
			eliminarProveedor();
			getch();
			menuProveedor();
		break;
		case 3:
			system("cls");
			menuProveedor();
			getch();
		break;
		case 4:
			system("cls");
			buscarProveedorNom();
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
			eliminarEmpleado();
			getch;
			menuEmployee();
		break;
		case 3:
			getch();
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
	
	cout<<"NOMBRE: ";
	cin.getline(empleado[contEmpleado].info.nombre,50,'\n');
	fflush(stdin);
	cout<<"APELLIDO: ";
	cin.getline(empleado[contEmpleado].apellido,50,'\n');
	fflush(stdin);
	
	// revisar que no exista el empleado
	if(validaNombres(empleado[contEmpleado])){
		cout<<"Este empleado ya existe...";
		memset(empleado[contEmpleado].info.nombre,0,50); // vaciar memoria de variables
		memset(empleado[contEmpleado].apellido,0,50); // vaciar memoria de variables
		getch();
	}else{
		cout<<"DIRECCION: ";
		cin.getline(empleado[contEmpleado].info.direccion,100,'\n');
		fflush(stdin);
		cout<<"Edad: ";
		cin>>empleado[contEmpleado].edad;
		cout<<"No. de caja: ";
		cin>>num;
		
		while(validaCaja(num)){
			cout<<"Ese numero de caja ya esta ocupado..."<<endl;
			cout<<"No de caja: ";
			cin>>num;
			fflush(stdin);
		}
		empleado[contEmpleado].caja = num;
		//Pasar nombre y apellido de empleados a minusculas
		strlwr(empleado[contEmpleado].info.nombre);
		strlwr(empleado[contEmpleado].apellido);
		
		empleado[contEmpleado].info.codigo = contEmpleado;
		contEmpleado++; //contador de empleados
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
		
		cout<<"Almacenar en:";
		cout<<"1. Bodega";
		cout<<"2. Tienda";
	
		//Pasar nombre y descripcion de producto a minusculas
		strlwr(producto[contProducto].info.nombre);
		strlwr(producto[contProducto].description);
		
		contProducto++; //contador de productos
	}
}

// validar el codigo del producto
bool validaProducto(int cod){
	for(int i = 0 ; i < contProducto; i++){
		if(cod == producto[i].info.codigo) return true;
	}
	return false;
}

void modificarProducto(){
	int update, posicion;
	int opcion = 0;

	cout<<"EDITAR PRODUCTO"<<endl;
	cout<<"Ingrese el codigo del producto: ";
	cin>>update;

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
	}else cout<<"Ninguna coincidencia...";
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

void getModificarProducto(Productos p, int posicion){
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
	Sleep(500);
	cout<<"Espere..."<<endl;
	Sleep(1000);
	cout<<"Actulizando datos..."<<endl;
	cout<<"Se han actualizado los datos correctamente!";
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
		
		proveedor[contProveedor].prov.codigo = contProveedor;
		//Pasar nombre y direccion del proveedor a minusculas
		strlwr(proveedor[contProveedor].prov.nombre);
		strlwr(proveedor[contProveedor].prov.direccion);
		
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

	for(int i = 0; i < contEmpleado; i++){
		gotoxy(30,i+4); cout<<empleado[i].info.codigo;
		gotoxy(45,i+4); cout<<empleado[i].info.nombre;
		gotoxy(70,i+4); cout<<empleado[i].apellido;
		gotoxy(90,i+4); cout<<empleado[i].info.direccion;
		gotoxy(120,i+4); cout<<empleado[i].edad;
		gotoxy(135,i+4); cout<<empleado[i].caja;
	}
}

void busquedaProducto(){
	int resultados = 0;
	int i = 0;
	char buscar[50];
	memset(buscar,0,50);
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
		cout<<"No se encontraron resultados...";
	}
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
	
	for(int i = 0; i < contEmpleado; i++){
		if(strcmp(nombres, empleado[i].info.nombre) == 0){
			filtraEmpleado[pos].info.codigo = empleado[i].info.codigo;
			strcpy(filtraEmpleado[pos].info.nombre, empleado[i].info.nombre);
			strcpy(filtraEmpleado[pos].apellido, empleado[i].apellido);
			strcpy(filtraEmpleado[pos].info.direccion, empleado[i].info.direccion);
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
			filtraEmpleado[pos].edad = empleado[i].edad;
			filtraEmpleado[pos].caja = empleado[i].caja;
			
			pos++;
			
			for(int i = 0; i < contEmpleado; i++){
				gotoxy(30,i+4); cout<<filtraEmpleado[i].info.codigo;
				gotoxy(45,i+4); cout<<filtraEmpleado[i].info.nombre;
				gotoxy(70,i+4); cout<<filtraEmpleado[i].apellido;
				gotoxy(90,i+4); cout<<filtraEmpleado[i].info.direccion;
				gotoxy(120,i+4); cout<<filtraEmpleado[i].edad;
				gotoxy(135,i+4); cout<<filtraEmpleado[i].caja;
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
		gotoxy(x,3); cout<<"*";
		gotoxy(x,40); cout<<"*";
	}
	for(int y = 2; y < 40; y++){
		gotoxy(60,y); cout<<"*";
		gotoxy(159,y); cout<<"*";
	}
}

void facturacion(){
	formatoFactura();
	gotoxy(14,2); cout<<"PRODUCTOS EN DISPONIBLES";
	gotoxy(8,34); cout<<"COMPRA DE SUS PRODUCTOS EN LA TIENDA";
	gotoxy(3,36); cout<<"Codigo del producto: ";
	gotoxy(3,37); cout<<"Cantidad de articulos: ";
	gotoxy(95,2); cout<<"SISTEMA DE FACTURACION \"EL DUENDE\"";
	productosTienda();
}

void productosTienda(){
	int x = 4;
	int y = 5;
	for(int i = 0; i < contProducto; i++){
		gotoxy(x,y); cout<<i+1<<".";
		gotoxy(x+3,y); cout<<producto[i].info.nombre;
		y++;
	}
}

              //codigo pedro 
                          
//funcion buscar empleado eliminacion

int buscarEmp(char busquedaEmpleado[50]){
	int i=0;
	bool encontrado=false;
	while (encontrado==false && i<contEmpleado){
		if(strcmp(busquedaEmpleado,empleado[i].info.nombre)==0){
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
	
//funcion buscar proveedor para eliminacion

int buscarProv(char busquedaProveedorNom[50]){
	int i=0;
	bool encontrado=false;
	while (encontrado==false && i<contProveedor){
		if(strcmp(busquedaProveedorNom,proveedor[i].prov.nombre)==0){
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
 // funcion  buscar por nombre para eliminacion de articulos 
 
 int buscarProd(char busquedaProductoNom[50]){
	int i=0;
	bool encontrado=false;
	while (encontrado==false && i<contProducto){
		if(strcmp(busquedaProductoNom,producto[i].info.nombre)==0){
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

                          
   //buscar proveedor

void buscarProveedorNom(){
	
	char eliminarProveedor[50];
	
	formato();
	gotoxy(70,14); cout<<"BUSQUEDA DE PROVEEDOR ";
	gotoxy(57,16); cout<<"Ingrese el nombre a buscar: ";
	gotoxy(84,16); cin.getline(eliminarProveedor,50,'\n');
	int pos=buscarProv(eliminarProveedor);
	
	if(pos==-1 ){
		system("cls");
		formato();
		gotoxy(68,20); cout<<"EL PROVEEDOR NO EXISTE ";
		getch;
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



//eliminar registros empleado

void eliminarEmpleado(){
	
	char nombre[50];
	cout<<" Ingrese los datos solicitados para la eliminacion del empleado  "<<endl;
	cout<<"Nombre: ";
	cin.getline(nombre,50,'\n');
	int pos=buscarEmp(nombre);
	if(pos==-1){
		cout<<" EL EMPLEADO NO EXISTE ";
	}
	else{
		
		for (int i=pos; i<contEmpleado; i++){
			
			empleado[i]=empleado[i+1];
			
			/*strcpy(empleado[i].info.nombre,empleado[i+1].info.nombre);
			strcpy(empleado[i].apellido,empleado[i+1].apellido);
			strcpy(empleado[i].info.direccion,empleado[i+1].info.direccion);
			empleado[i].edad = empleado[i+1].edad;
			empleado[i].caja = empleado[i+1].caja;
			*/
		}
			contEmpleado--;	
			cout<<"EMPLEADO ELIMINADO";
			getch;
		
		}
	}
	
//eliminar proveedor
void eliminarProveedor(){
	
	char nombre[50];
	cout<<" INGRESE LOS DATOS SOLICITADOS PARA LA ELIMINACION DEL PROVEEDOR  "<<endl;
	cout<<"NOMBRE: ";
	cin.getline(nombre,50,'\n');
	int pos=buscarProv(nombre);
	if(pos==-1){
		cout<<" EL EMPLEADO NO EXISTE ";
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
			cout<<"EMPLEADO ELIMINADO";
			getch();
			
		
		}
	}
	
//eliminar producto  por nombre
void eliminarProducto(){
	
	char nombre[50];
	cout<<" INGRESE LOS DATOS SOLICITADOS PARA LA ELIMINACION DEL PRODUCTO  "<<endl;
	cout<<"NOMBRE: ";
	cin.getline(nombre,50,'\n');
	int pos=buscarProd(nombre);
	if(pos==-1){
		cout<<" EL PRODUCTO NO EXISTE ";
	}
	else{
		
		for (int i=pos; i<contProducto; i++){
		
			strcpy(producto[i].info.nombre,producto[i+1].info.nombre );
			strcpy(producto[i].description,producto[i+1].description);
			producto[i].info.codigo = producto[i+1].info.codigo;
			producto[i].price =producto[i+1].price;
			producto[i].quantity =producto[i+1].quantity;
			producto[i].peso =producto[i+1].peso;
			

		}
			contProducto--;	
			cout<<"EL PRODUCTO SE ELIMINO CON EXITO ";
			getch();
			
		
		}
	}
	
	
//eliminar producto  por codigo
void eliminarProductoCodigo(){
	
	bool cambio=false;
	int num;

	cout<<" INGRESE LOS DATOS SOLICITADOS PARA LA ELIMINACION DEL PRODUCTO  "<<endl;
	cout<<"codigo: ";
	cin>>num;

		for(int i=0; i<contProducto; i++ ){
	
		
		if(num==producto[i].info.codigo){
			cambio=true;
			strcpy(producto[i].info.nombre,producto[i+1].info.nombre );
			strcpy(producto[i].description,producto[i+1].description);
			producto[i].info.codigo = producto[i+1].info.codigo;
			producto[i].price =producto[i+1].price;
			producto[i].quantity =producto[i+1].quantity;
			producto[i].peso =producto[i+1].peso;
			
			contProducto--;		
		}
		
		}
		if(cambio==true){
		   	cout<<"EL PRODUCTO SE ELIMINO CON EXITO ";
			getch();
		
		}
		else{
			cout<<"EL CODIGO NO EXISTE";
			getch();	
	}
}
