#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <fstream>
#include <windows.h>
#include <conio.h>

void gotoxy(int x,int y){                          ///Inicio funcion (x,y)
      HANDLE hcon;                                  ///
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);       ///
      COORD dwPos;                                  ///
      dwPos.X = x;                                  ///
      dwPos.Y= y;                                   ///
      SetConsoleCursorPosition(hcon,dwPos);         ///
 }  
 
using namespace std;

struct Palabras {
	char palabra[100];
	char traduccion[100];
	char funcionalidad[100];
};
struct Nodo {
	char valor[15];
	Nodo *siguiente;
};

void Push(Nodo*&, char*);
void Pop(Nodo *&);
void traduccion(char *);
void write(char[]);

int main() {
    system("color F1");
	ofstream archivo;
	archivo.open("auxi.txt", ios::out);
	if (archivo.fail()) {
		cout << "Error al abrir el archivo";
	}
	else {
		archivo.close();
		string txt;
		int x = 0;
		char *frase, *token, *aux, *auxi, inicio[] = "inicio", fin[] = "fin";
		Nodo *pila = NULL;
		cout << "\tINGRESE EL CODIGO A TRADUCIR Y ESCRIBA 'TRADUCIR' AL FINALIZAR EL CODIGO:\n";
		do {
            fflush(stdin);
			getline(cin, txt);
			if (strcmp(txt.c_str(), "TRADUCIR") == 0)
				break;
			frase = &txt[0];
			token = strtok(frase, " ");
			auxi = token;
			while (token != NULL) {
				aux = token;
				token = strtok(NULL, " ");
				if (token != NULL) {
					traduccion(aux);
				}
				else {
					int tam;
					tam = (txt.size() - 1);
					if (txt[tam] == '{') {
						if (x == 0) {
							traduccion(aux);
						}
						else {
							write(inicio);
							traduccion(auxi);
							Push(pila, auxi);
						}
						x += 1;
					}
					else if (txt[tam] == '}') {
						x -= 1;
						if (x == 0) {
							traduccion(aux);
						}
						else {
							write(fin);
							txt = pila->valor;
							auxi = &txt[0];
							traduccion(auxi);
							Pop(pila);
						}
					}
					else {
						traduccion(aux);
					}
				}
			}
			archivo.open("auxi.txt", ios::app);
			if (archivo.fail())
				cout << "Error al abrir el archivo";
			else {
				archivo << endl;
				archivo.close();
			}
		} while (txt != "0");
		cout << "\n\n";
	}
	ifstream archivo1;
	archivo1.open("auxi.txt", ios::in);
	if (archivo1.fail()) {
		cout << "Error al abrir el archivo";
	}
	else {
		int x,y,i;
        system ("cls");
 gotoxy(100,10);
 printf("HACIENDO LA TRADUCCION");
   
 
 for(i=1; i<215; i++) //largo linea carga
 {
 	
  gotoxy(i,13);//columna 13 ubi linea carga
  
  printf("%c",219);//codigo ascii
  
  for(x=62;x<65;x++){  //rapidez lineas carga
   
   for(y=1;y<215;y++){  //donde llegan lineas de abajo

	gotoxy(y,18);
   }
  }
 }
		system ("cls");
		cout << "\n\n\t\t\tTRADUCCION: \n\n";
		string txt;

		while (!archivo1.eof()) {
			getline(archivo1, txt);
			cout << txt << endl;
		}
		archivo1.close();
	}
	remove("auxi.txt");
	cin.ignore();
}

void traduccion(char *token) {
	ofstream archivo2;
	archivo2.open("auxi.txt", ios::app);
	if (archivo2.fail()) {
		cout << "Error al abrir el archivo";
	}
	else {
		FILE* archivo = fopen("palabras.dat", "rb");
		Palabras pal;
		fread(&pal, sizeof(Palabras), 1, archivo);
		while (feof(archivo) == 0) {
			if (strcmp(pal.palabra, token) == 0) {
				archivo2 << pal.traduccion << " ";
				fclose(archivo);
				archivo2.close();
				return;
			}
			fread(&pal, sizeof(Palabras), 1, archivo);
		}
		fclose(archivo);
	}
	archivo2 << token << " ";
	archivo2.close();
}

void write(char token[]) {
	ofstream archivo2;
	archivo2.open("auxi.txt", ios::app);
	if (archivo2.fail()) {
		cout << "Error al abrir el archivo";
	}
	else {
		archivo2 << token << " ";
		archivo2.close();
		return;
	}
}

void Push(Nodo *&pila, char *va) {
	string v(va);
	Nodo *push = new Nodo();
	strcpy(push->valor, v.c_str());
	push->siguiente = pila;
	pila = push;
}

void Pop(Nodo *&pila) {
	if (pila != NULL) {
		char *v;
		Nodo *pop = pila;
		v = &pop->valor[0];
		pila = pop->siguiente;
		delete[] pop;
	}
	return;
}
