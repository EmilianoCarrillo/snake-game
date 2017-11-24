#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;

enum dir { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

class Tablero {
	int anchura, altura;
	char caracterBorde;
public:
	Tablero() {
		anchura = 50;
		altura = 25;
		caracterBorde = '#';
	}
	int getAltura() {return altura;}
	int getAnchura() {return anchura;}
	char getCaracterBorde() {return caracterBorde;}
};

class Snake {
	int xCuerpo[100], yCuerpo[100];
	int xCabeza = xCuerpo[0], yCabeza = yCuerpo[0];
	int longitud;
	char caracter;
	bool cuerpoImpresoTotalmente = false;
public:
	Snake() {
		longitud = 1;
		caracter = 'O';
	}
	void posicionarEnELCentro(int anchura, int altura) {
		xCuerpo[0] = anchura / 2;
		yCuerpo[0] = altura / 2;
	}
	int getXCuerpo(int index) { return xCuerpo[index]; }
	int getYCuerpo(int index) { return yCuerpo[index]; }
	/*Añadí estas dos*/
	/*EDITARLAS Y CREAR UNAS DE MOVIMIENTO (RECORRIDO EN EL ARRAY)*/
	void setXCuerpo(int val) { xCuerpo[0] = val; }
	void setYCuerpo(int val) { yCuerpo[0] = val; }
	/*---------------*/
	int getLongitud() { return longitud; }
	char getCaracter() { return caracter; }
	bool impresoTotalmente() { return cuerpoImpresoTotalmente; }
	void setCuerpoImpresoTotalmente(bool val) { cuerpoImpresoTotalmente = val; }
};

class Comida {
	int x, y;
	char caracter;
public:
	Comida() {
		caracter = '@';
	}
	void posicionarAleatoriamente(int anchura, int altura) {
		int xAleatorio = rand() % (anchura - 2) + 1; //Número aleatorio entre 1 y anchuraTablero-2
		int yAleatorio = rand() % (altura - 2) + 1; //Número aleatorio entre 1 y anchuraTablero-2
		this->x = xAleatorio;
		this->y = yAleatorio;
	}
	int getX() { return x; }
	int getY() { return y; }
	char getCaracter() { return caracter; }
};

class Juego {
	Tablero tablero;
	Snake culebrin;
	Comida manzana;
	dir direccionTecla;
public:
	void setup() {
		manzana.posicionarAleatoriamente(tablero.getAnchura(), tablero.getAltura());
		culebrin.posicionarEnELCentro(tablero.getAnchura(), tablero.getAltura());
	}
	void dibujar() {
		system("cls");
		int cantidadBolasImpresas = 0;
		culebrin.setCuerpoImpresoTotalmente(false);
		for (int y = 0; y < tablero.getAltura(); y++){
			for (int x = 0; x < tablero.getAnchura(); x++){
				//Imprimir bordes
				if (x == 0 || y == 0 || x == tablero.getAnchura() - 1 || y == tablero.getAltura() - 1) cout << tablero.getCaracterBorde();
				//Imprimir Comida
				else if (x == manzana.getX() && y == manzana.getY()) cout << manzana.getCaracter();
				//Imprimir Snake
				else {
					bool bolaImpresa = false;
					for (int i = 0; (i < culebrin.getLongitud() && !culebrin.impresoTotalmente()); i++){
						if (x == culebrin.getXCuerpo(i) && y == culebrin.getYCuerpo(i)) {
							cout << culebrin.getCaracter();
							bolaImpresa = true;
							cantidadBolasImpresas++;
							if (cantidadBolasImpresas == culebrin.getLongitud()) culebrin.setCuerpoImpresoTotalmente(true);
						}
					}
					//Imprimir espacios vacíos
					if (!bolaImpresa) cout << ' ';
				}
			}
			cout << endl;
		}
	}
	void recibirInputTeclado(){
		if (_kbhit()) {
			switch (_getch()) {
				case 'w':
					direccionTecla = ARRIBA;
					culebrin.setYCuerpo(2);
					cout << "w" << culebrin.getYCuerpo(0) << endl;
					break;
				case 'a':
					direccionTecla = IZQUIERDA;
					cout << "a" << endl;
					break;
				case 's':
					direccionTecla = ABAJO;
					cout << "s" << endl;
					break;
				case 'd':
					direccionTecla = DERECHA;
					cout << "d" << endl;
					break;
			}
		}
	}

	void cambiarEstado() {
		manzana.posicionarAleatoriamente(tablero.getAnchura(), tablero.getAltura());
		if (direccionTecla == ARRIBA) culebrin.setYCuerpo(5); //PRUEBA
		if (direccionTecla == ABAJO) culebrin.setYCuerpo(10); //PRUEBA
		if (direccionTecla == IZQUIERDA) culebrin.setXCuerpo(5); //PRUEBA
		if (direccionTecla == DERECHA) culebrin.setXCuerpo(10); //PRUEBA


	}

};






int main() {
	srand(time(0));
	Juego juego;
	juego.setup();
	while (true) {
		juego.dibujar();
		juego.recibirInputTeclado();
		juego.cambiarEstado(); 
	}
}