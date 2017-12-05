#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>


using namespace std;

enum dir { ARRIBA, ABAJO, DERECHA, IZQUIERDA , NADA};

// CLASE SNAKE
class Snake {
private:
	int xCuerpo[100], yCuerpo[100];
	int longitud;
	char caracter, caracterCabeza;
public:
	Snake() {
		longitud = 1;
		caracter = 'o';
		caracterCabeza = 'O';
	}
	void avanzar(dir direccionTecla);
	void crecer();
	void posicionarAlCentro(int anchura, int altura);
	int getXCuerpo(int index) {
		return xCuerpo[index];
	}
	int getYCuerpo(int index) {
		return yCuerpo[index];
	}
	int getLongitud() { return longitud; }
	void setLongitud(int longitud) { this->longitud = longitud;  }
	char getCaracter() { return caracter; }
	char getCaracterCabeza() { return caracterCabeza; }
};
	// Métodos offline de Snake
void Snake::avanzar(dir direccionTecla) {
	if (direccionTecla == ARRIBA) {
		for (int i = longitud - 1; i >= 0; i--) {
			if (i == 0) yCuerpo[0]--;
			else {
				yCuerpo[i] = yCuerpo[i - 1];
				xCuerpo[i] = xCuerpo[i - 1];
			}
		}
	}
	if (direccionTecla == ABAJO) {
		for (int i = longitud - 1; i >= 0; i--) {
			if (i == 0) yCuerpo[0]++;
			else {
				yCuerpo[i] = yCuerpo[i - 1];
				xCuerpo[i] = xCuerpo[i - 1];
			}
		}
	}
	if (direccionTecla == IZQUIERDA) {
		for (int i = longitud - 1; i >= 0; i--) {
			if (i == 0) xCuerpo[0]--;
			else {
				xCuerpo[i] = xCuerpo[i - 1];
				yCuerpo[i] = yCuerpo[i - 1];
			}
		}
	}
	if (direccionTecla == DERECHA) {
		for (int i = longitud - 1; i >= 0; i--) {
			if (i == 0) xCuerpo[0]++;
			else {
				xCuerpo[i] = xCuerpo[i - 1];
				yCuerpo[i] = yCuerpo[i - 1];
			}
		}
	}
}
void Snake::crecer() { longitud++; }

void Snake::posicionarAlCentro(int anchura, int altura) {
	xCuerpo[0] = anchura / 2;
	yCuerpo[0] = altura / 2;
}

// CLASE TABLERO
class Tablero {
private:
	int anchura, altura;
	char caracterBorde;
public:
	Tablero() {
		anchura = 50;
		altura = 25;
		caracterBorde = '#';
	}
	int getAnchura() { return anchura; }
	int getAltura() { return altura; }
	char getCaracterBorde() { return caracterBorde; }
};

// CLASE COMIDA
class Comida {
private:
	int x, y;
	char caracter;
public:
	Comida() {
		caracter = '@';
	}
	void posicionarAleatoriamente(int anchura, int altura);
	int getX() { return x; }
	int getY() { return y; }
	char getCaracter() { return caracter; }
};

	// Métodos offline de Comida
void Comida::posicionarAleatoriamente(int anchura, int altura) {
	x = rand() % (anchura-2 - 1 + 1) + 1;
	y = rand() % (altura-2 - 1 + 1) + 1;
	
}

//CLASE JUEGO
class Juego {
private:
	Snake culebrin;
	Tablero tablero;
	Comida manzana;
	bool gameOver;
	dir direccionTecla;
	string nombreUsuario;
	int decisionJugar;
public:
	void setup();
	void mostrarPantallaInicio();
	void mostrarPantallaGameOver();
	void guardarPuntajeEnBD();
	void recibirInputTeclado();
	void cambiarEstado();
	void dibujar();
	Juego() : decisionJugar(1) {}
	bool getGameOver() { return gameOver; }
	int getDecisionJugar() { return decisionJugar; }
};

	// Métodos offline de Juego
void Juego::setup() {
	gameOver = false;
	direccionTecla = NADA;
	culebrin.setLongitud(1);
	manzana.posicionarAleatoriamente(tablero.getAnchura(), tablero.getAltura());
	culebrin.posicionarAlCentro(tablero.getAnchura(), tablero.getAltura());
}

void Juego::mostrarPantallaInicio() {
	system("cls");
	string renglon;
	ifstream asciiInicio("asciiArtInicio.txt");

	if (asciiInicio.is_open()){
		while (!asciiInicio.eof()) {
			getline(asciiInicio, renglon);
			cout << renglon << endl;
		}
		asciiInicio.close();
	}else {
		cout << "\t\t\t\tERROR: Archivo no existente." << endl << endl;
	}
	

	cout << "\t\t\t\t Nombre: ";
	cin >> nombreUsuario;
	cout << "\t\t\t\t Inserta una moneda." << endl;
	cin.get();
	cin.get();
}

void Juego::mostrarPantallaGameOver() {
	string renglon;
	int contador = 1;
	int index = 1;
	int puntajes[50];
	string nombres[50];

	ifstream scoreboard;
	scoreboard.open("scoreboard.txt");

	if (scoreboard.is_open()) {
		while (!scoreboard.eof()) {
			getline(scoreboard, renglon);
			if (contador % 2 != 0) {
				istringstream (renglon) >> puntajes[index];
				index++;
			}
			else {
				nombres[index - 1] = renglon;
			}
			contador++;
		}

		int i, key, j;
		string key2;
		for (i = 1; i < contador/2; i++){
			key = puntajes[i];
			key2 = nombres[i];
			j = i - 1;
			while (j >= 0 && puntajes[j] > key){
				puntajes[j + 1] = puntajes[j];
				nombres[j + 1] = nombres[j];
				j = j - 1;
			}
			puntajes[j + 1] = key;
			nombres[j + 1] = key2;
		}
	}else {
		cout << "\t\t\t\tERROR: Archivo no existente." << endl << endl;
	}


	// MOSTRAR ASCII ART GAME OVER
	system("cls");
	ifstream asciiGameOver("asciiArtGameOver.txt");

	if (asciiGameOver.is_open()){
		while (!asciiGameOver.eof()) {
			getline(asciiGameOver, renglon);
			cout << "\t\t\t" << renglon << endl;
		}
	} else {
		cout << "\t\t\t\tERROR: Archivo no existente." << endl << endl;
	}
	
	cout << "\n\n\t\t\t\t\t\tTU PUNTAJE: " << culebrin.getLongitud() - 1;

	cout << "\n\n\t\t\t\t\t**********SCOREBOARD**********" << endl;
	cout << "\t\t\t\t\t*                            *" << endl;
	int posicion = 1;
	for (int i = contador/2-1; i >= (contador/2)-3 ; i--) {
		cout << "\t\t\t\t\t*\t  "  << posicion << ". " << puntajes[i] << " " << nombres[i] << "\t     *" << endl;
		posicion++;
	}
	cout << "\t\t\t\t\t*                            *" << endl;
	cout << "\t\t\t\t\t******************************" << endl;

	cout << endl << endl << "\t\t\t\t\t    Deseas volver a jugar?" << endl;
	cout << "\t\t\t\t\t\t1. SI\n\t\t\t\t\t\t2. NO, SALIR" << endl;
	cout << "\t\t\t\t\t\t:: ";
	cin >> decisionJugar;

	cin.get();
}

void Juego::guardarPuntajeEnBD() {
	//GUARDAR EN "BASE DE DATOS"
	ofstream scoreboard;
	scoreboard.open("scoreboard.txt", ios_base::app);

	scoreboard << culebrin.getLongitud() - 1 << endl << nombreUsuario << endl;

	scoreboard.close();
}

void Juego::recibirInputTeclado() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (direccionTecla == ABAJO) direccionTecla = ABAJO;
			else direccionTecla = ARRIBA;
			break;
		case 'a':
			if (direccionTecla == DERECHA) direccionTecla = DERECHA;
			else direccionTecla = IZQUIERDA;
			break;
		case 's':
			if (direccionTecla == ARRIBA) direccionTecla = ARRIBA;
			else direccionTecla = ABAJO;
			break;
		case 'd':
			if (direccionTecla == IZQUIERDA) direccionTecla = IZQUIERDA;
			else direccionTecla = DERECHA;
			break;
		}
	}
}

void Juego::cambiarEstado() {
	culebrin.avanzar(direccionTecla);
	//Si las coordenadas de la cabeza de culebrin son iguales a la de la comida
	//Culebrin crecerá y la manzana deberá posicionarse en otro lugar aleatorio.
	if (culebrin.getXCuerpo(0) == manzana.getX() && culebrin.getYCuerpo(0) == manzana.getY()) {
		culebrin.crecer();
		manzana.posicionarAleatoriamente(tablero.getAnchura(), tablero.getAltura());
	}
	//Morir si toca bordes
	if ( culebrin.getXCuerpo(0) == tablero.getAnchura()-1 || culebrin.getYCuerpo(0) == tablero.getAltura() - 1 || culebrin.getXCuerpo(0) == 0 || culebrin.getYCuerpo(0) == 0)	{
		gameOver = true;
	}
	// Morir si toca su cuerpo
	for (int i = 4; i < culebrin.getLongitud(); i++){
		if (culebrin.getXCuerpo(0) == culebrin.getXCuerpo(i) && culebrin.getYCuerpo(0) == culebrin.getYCuerpo(i)) 
			gameOver = true;
	}
}

void Juego::dibujar() {
	bool bandera = false;
	system("cls");
	// Dibujar Tablero
	for (int y = 0; y < tablero.getAltura(); y++) {
		for (int x = 0; x < tablero.getAnchura(); x++) {
			//Checar y dibujar el borde del tablero
			if (y == 0 || x == 0 || y == tablero.getAltura() - 1 || x == tablero.getAnchura() - 1) {
				cout << tablero.getCaracterBorde();
			// Checar y dibujar manzana
			} else if (x == manzana.getX() && y == manzana.getY()) {
				cout << manzana.getCaracter();
			} else {
			// Checar y dibujar culebra entera
				for (int i = 0; i < culebrin.getLongitud(); i++) {
					if (x == culebrin.getXCuerpo(i) && y == culebrin.getYCuerpo(i)){
						bandera = true;
						if (i == 0) cout << culebrin.getCaracterCabeza();
						else cout << culebrin.getCaracter();
					}
				}
				// De lo contrario, imprimir espacio
				if (bandera == false) cout << " "; 
				bandera = false;
			}
		}
		cout << endl ;
	}
	cout << "PUNTAJE: " << culebrin.getLongitud() - 1;
}



int main() {
	srand(time(NULL));
	Juego juego;

	while (juego.getDecisionJugar() == 1) {
		juego.setup();
		juego.mostrarPantallaInicio();
		while (!juego.getGameOver()) {
			juego.recibirInputTeclado();
			juego.cambiarEstado();
			juego.dibujar();
			Sleep(15);
		}
		juego.guardarPuntajeEnBD();
		juego.mostrarPantallaGameOver();
	}
}
