#include "Controlador.h"
Controlador* ctrl = new Controlador();

void menu_Principal();
void menu_Iniciar_Sesion();
void menu_Crear_Cuenta();
void menu_Cuenta(int& pos);
void menu_Operaciones_Cuenta(int& posUsuario, int& posCuenta);

int main() {
	Console::SetWindowSize(101, 30); 
	menu_Principal();
	return 0;
}

void menu_Principal()
{
	Cls;
	int opMenuPrincipal = 0;
	do {
		cout << "\n========================================[ CAJERO AUTOMATICO ]========================================\n\n";
		cout << "\n\20\t1. Iniciar Sesion";
		cout << "\n\20\t2. Crear Cuenta";
		cout << "\n\20\t3. Ver lista de cuentas registradas\b";
		cout << "\n\20\t4. Salir del Programa\n";
		Print; Print;
		cout << "\20\tSeleccione una opcion: "; cin >> opMenuPrincipal; 
		Console::Clear();
	} while (opMenuPrincipal < 1 || opMenuPrincipal > 4);

	switch (opMenuPrincipal)
	{
	case 1:
		menu_Iniciar_Sesion();
		break;
	case 2:
		menu_Crear_Cuenta();
		break;
	case 3:
		ctrl->Mostrar_Listas_Usuarios();
		menu_Principal();
		break;
	case 4:
		cout << "\n\20\tEXIT ";
		for (int i = 1; i < 5; i++) { cout << ". "; Sleep(500); }
		exit(0);
	}
}

void menu_Iniciar_Sesion()
{
	Cls;
	int posUsuario = 0;
	int opMenuIniciarSesion = 0;
	int dniParaIngresar;
	bool dniEncontrado = false;
	do {
		Cls;
		Console::SetCursorPosition(87, 0); cout << "<== VOLVER(0)|\n";
		cout << "\n===============================[ CAJERO AUTOMATICO -- INICIAR SESION ]===============================\n";
		cout << "\n\20\tIngrese su numero de DNI: "; cin >> dniParaIngresar;

		if (dniParaIngresar == 0) menu_Principal();
		dniEncontrado = ctrl->comprobar_Dni(dniParaIngresar, posUsuario);

		if (dniEncontrado) 
		{
			int contraParaIngresar;
			bool contraValidada = false;
			Pos; cout << "...Dni Encontrado..."; Sleep(500);
			Console::SetCursorPosition(0, 5);
			cout << "\n\20\tIngrese su numero de contrasena: "; cin >> contraParaIngresar;
			
			contraValidada = ctrl->comprobar_Contra(contraParaIngresar, posUsuario);
			if (contraValidada) 
			{
				Pos; cout << "...Cuenta validada..."; Sleep(500);
				menu_Cuenta(posUsuario);
			}
			else { Pos; cout << "...Contrasena Incorrecta..."; Sleep(500); }
		}
		else { Pos; cout << "...Dni no existente..."; Sleep(500); }
	} while (true);
}

void menu_Crear_Cuenta()
{
	Cls;
	int dniParaIngresar;
	do {
		Console::SetCursorPosition(87, 0); cout << "<== VOLVER(0)|\n";
		cout << "\n================================[ CAJERO AUTOMATICO -- CREAR CUENTA ]================================\n\n";
		cout << "\n\20\tIngrese su numero de DNI: "; cin >> dniParaIngresar;
	} while (dniParaIngresar < 0);

	if (dniParaIngresar == 0) menu_Principal();
	int contraParaIngresar;

	do {
		cout << "\n\20\tIngrese su numero de contrasena: "; cin >> contraParaIngresar;
	} while (contraParaIngresar < 0);

	string nombreParaIngresar;
	cout << "\n\20\tIngrese su nombre: "; cin >> nombreParaIngresar;
	ctrl->anadir_Usuario(nombreParaIngresar, dniParaIngresar, contraParaIngresar);
	Pos; cout << "...CUENTA REGISTRADA..."; _getch();
	menu_Principal();
}

void menu_Cuenta(int& pos)
{
	Cls;
	int opMenuUsuario;
	do {
		cout << "\n======================[ MENU USUARIO -- BIENVENIDO " << ctrl->get_Usuario(pos)->get_Nombre() << " ELIJA UNA OPCION ]======================\n\n";
		cout << "\20\t1.- Visualizar estado Cuentas" << endl;
		cout << "\20\t2.- Ingresar a una cuenta" << endl;
		cout << "\20\t3.- Crear nueva cuenta" << endl;
		cout << "\20\t4.- Ver dinero total depositado" << endl;
		cout << "\20\t5.- Volver" << endl;
		Print; Print; 
		cout << "\20\tElija una opcion: "; cin >> opMenuUsuario;
	} while (opMenuUsuario < 1 || opMenuUsuario > 5);

	switch (opMenuUsuario)
	{
	case 1:
		ctrl->get_Usuario(pos)->visualizar_Cuentas();
		menu_Cuenta(pos); 
		break;

	case 2:
		int posCuenta;
		ctrl->get_Usuario(pos)->visualizar_Cuentas();
		if (ctrl->get_Usuario(pos)->get_CantDeCuentas() == 0) menu_Cuenta(pos);
		do {
			cout << "\n\20\tElija la posicion de la cuenta a la que desea ingresar: "; cin >> posCuenta;
		} while (posCuenta < 0 || posCuenta > ctrl->get_Usuario(pos)->get_CantDeCuentas() - 1);
		menu_Operaciones_Cuenta(pos, posCuenta);
		menu_Cuenta(pos);
		break;

	case 3:
		ctrl->get_Usuario(pos)->anadir_Cuentas();
		menu_Cuenta(pos);
		break;
	case 4:
		cout << "\n\n\20\tEL DINERO TOTAL REGISTRADO ENTRE LAS CUENTAS ES DE: S/ " << ctrl->recursividad_Dinero_Total(pos, 0) << " soles.";
		cout << "\n\n\20\t"; system("pause");
		menu_Cuenta(pos);
		break;
	case 5: menu_Principal(); break;
	}
}

void menu_Operaciones_Cuenta(int& posUsuario, int& posCuenta)
{
	float monto;
	int opMenuOperacionesEnCuenta = 0;
	char tipo_cuenta;
	bool pagar_cuenta;
	int deudas = NULL;
	char decision = ' ';
	bool op_realizada = false;
	do {
		Cls;
		cout << "\n========================[ MENU DE OPERACIONES EN CUENTA -- ELIJA UNA OPCION ]========================\n";
		cout << "\n\20\tSe encuentra en la cuenta Nro. [ " << posCuenta << " ] " << endl;
		cout << "\n\20\tEsta cuenta contiene " << ctrl->get_Usuario(posUsuario)->get_Stack_Cuentas()->obtener_Position(posCuenta)->get_Cant_Dinero();
		tipo_cuenta = ctrl->get_Usuario(posUsuario)->get_Stack_Cuentas()->obtener_Position(posCuenta)->get_Tipo();
		if (tipo_cuenta == 'S') cout << " soles." << endl << endl;
		else cout << " dolares." << endl << endl;
		cout << "\n\20\tOPCIONES DISPONIBLES: " << endl;
		cout << "\n\20\t1.- Depositar en cuenta" << endl;
		cout << "\20\t2.- Retirar en Cuenta" << endl;
		cout << "\20\t3.- Ver deudas pendientes" << endl;
		cout << "\20\t4.- Ver historial de operaciones" << endl;
		cout << "\20\t5.- Volver" << endl;
		Console::SetCursorPosition(0, 16);
		cout << "\n\20\tElija una opcion: "; cin >> opMenuOperacionesEnCuenta;
	} while (opMenuOperacionesEnCuenta < 1 || opMenuOperacionesEnCuenta > 5);
	cout << "\n-----------------------------------------------------------------------------------------------------" << endl;
	switch (opMenuOperacionesEnCuenta)
	{
	case 1:
		cout << "\n\20\tIngrese el monto que desea depositar: "; cin >> monto;
		ctrl->get_Usuario(posUsuario)->get_Stack_Cuentas()->obtener_Position(posCuenta)->depositar_Dinero(monto, op_realizada);
		if (op_realizada) ctrl->Operaciones_Cuenta(opMenuOperacionesEnCuenta, monto, tipo_cuenta);
		menu_Operaciones_Cuenta(posUsuario, posCuenta);
		break;
	case 2:
		cout << "\n\20\tIngrese el monto que desea retirar: "; cin >> monto;
		ctrl->get_Usuario(posUsuario)->get_Stack_Cuentas()->obtener_Position(posCuenta)->retirar_Dinero(monto, op_realizada);
		if (op_realizada) ctrl->Operaciones_Cuenta(opMenuOperacionesEnCuenta, monto, tipo_cuenta);
		menu_Operaciones_Cuenta(posUsuario, posCuenta);
		break;
	case 3:
		ctrl->Mostrar_Deuda_Pendiente(pagar_cuenta, tipo_cuenta);
		if (pagar_cuenta == true) {
			float cantidad;
			cout << "\n\20\tDigite la cantidad exacta para cancelar la deuda: "; cin >> cantidad;
			float cash = ctrl->get_Usuario(posUsuario)->get_Stack_Cuentas()->obtener_Position(posCuenta)->get_Cant_Dinero();
			if (cantidad == ctrl->get_Deuda() && cantidad <= cash) { 
				cout << "\n\20\t...Deuda cancelada correctamente..."; Sleep(750); 
				ctrl->Operaciones_Cuenta(opMenuOperacionesEnCuenta, cantidad, tipo_cuenta);
			}
			else if(cantidad > cash){ cout << "\n\20\t...ERROR. Usted no cuenta con el dinero suficiente!..."; _getch(); }
			else if (cantidad < ctrl->get_Deuda()) { cout << "\n\20\t...ERROR. Digite el monto exacto!..."; _getch(); }
		}
		menu_Operaciones_Cuenta(posUsuario, posCuenta);
		break;
	case 4:
		ctrl->Mostrar_Historial_Operaciones();
		menu_Operaciones_Cuenta(posUsuario, posCuenta);
		break;
	case 5:
		cout << "\n\n\20\tEsta regresando al menu usuario..."; Sleep(750);
		menu_Cuenta(posUsuario);
		break;
	}
}