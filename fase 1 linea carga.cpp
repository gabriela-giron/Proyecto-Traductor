#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

//teclas direccionales
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13


void gotoxy(int x,int y){                          ///Inicio funcion (x,y)
      HANDLE hcon;                                  ///
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);       ///
      COORD dwPos;                                  ///
      dwPos.X = x;                                  ///
      dwPos.Y= y;                                   ///
      SetConsoleCursorPosition(hcon,dwPos);         ///
 }  

//ocultar cursor
void OcultarCursor(){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize= 50;
	cci.bVisible=FALSE;
	
	SetConsoleCursorInfo(hcon,&cci);
}

 
using namespace std;
const char *nombre_archivo = "palabras.dat";

struct Palabras{
    char palabra[100];
    char traduccion[100];
    char funcionalidad[100];
};

int menu(const char* titulo, const char *subtitulo, const char *opciones[], int n);
void salir();
void agregar_palabra();
void abrir_registro();
void ver_palabras();
void eliminar_palabra();
void modificar_palabra();
bool buscar_palabra(string);

int menu(const char* titulo, const char *subtitulo, const char *opciones[], int n){
	int opcionSeleccionada = 1;
	int tecla;
	bool repite = true;
	
	do{
		system("cls");
		gotoxy(75,23 + opcionSeleccionada);
		cout<<">";
		
		gotoxy(73,19);
		cout<<titulo;
		gotoxy(80,20);
		cout<<subtitulo;
		for(int i=0; i<n; i++){
			gotoxy(76, 24 + i);
			cout<<i + 1<<". "<<opciones[i];
		}
		do{
			tecla = getch();
		}while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=ENTER);
		
		switch(tecla){
			case TECLA_ARRIBA:
				opcionSeleccionada--;
				
				if(opcionSeleccionada == 0){
					opcionSeleccionada = n;
				}
				break;
			case TECLA_ABAJO:
				opcionSeleccionada++;
				
				if(opcionSeleccionada > n){
					opcionSeleccionada = 1;
				}
				break;
			case ENTER:
				repite = false;
				break;	
		}

	}while(repite);
	return opcionSeleccionada;
}

//funcion principal
int main(){
	system ("COLOR 5E");
    OcultarCursor();
	bool repite = true;
	int opcion;
	const char *titulo = "TRADUCTOR INGLES - ESPANIOL";
	const char *subtitulo = "BIENVENIDO";
	const char *opciones[]= {"AGREGAR PALABRA", "VER PALABRAS REGISTRADAS","MODIFICAR PALABRA", "TRADUCIR CODIGO","ELIMINAR PALABRA", "SALIR"};
	int n = 6;
    int op;
    do{
    	system("cls");
    	op = menu(titulo,subtitulo,opciones,n);
    	
    	switch(op){
    		case 1:
    			system ("COLOR F2");
    			agregar_palabra();
    		break;
    		case 2:
    			system ("COLOR F1");
    			abrir_registro();
    			getch();
    			
    		break;
    		case 3:
    			system ("COLOR F5");
    			modificar_palabra();
    			getch();
    		break;
    		case 4:
    			system ("COLOR F3");
    			system("cls");
                system("fase2.exe");
                getch();
    			
    		break;
    		case 5:
    			system ("COLOR F4");
    			eliminar_palabra();
    		break;
    		case 6:
    			salir();
    			
    		break;
    		
		}
	}while(op!=6);
	
	
	return 0;
}

void salir(){
	system("cls");
	system ("COLOR 5E");
    OcultarCursor();
	bool repite = true;
	int opcion;
	const char *titulo = "SEGURO DESEAS FINALIZAR?";
	const char *subtitulo = ":(";
	const char *opciones[]= {"Si", "No"};
	int n = 2;
    int op;
    do{
    	system("cls");
    	op = menu(titulo,subtitulo,opciones,n);
    	switch(op){
    		case 1:
    			system("cls");
    			gotoxy(48,12);
    			cout<<"PROGRAMA FINALIZADO :D"<<endl<<endl;
    			gotoxy(48,30);
    			system ("pause");
    			repite = false;
    		break;
    		case 2:
    			main();
		}
	}while(repite);
}

void agregar_palabra(){
	char continuar;
    system("cls");
	FILE* archivo = fopen(nombre_archivo, "a");
    Palabras palab;
    string aux;
    do{
        fflush(stdin);
        cout<<"\t\t\tAgregar Palabra\n";
        cout<<"\t\t-------------------\n";
        cout<<"\tINGRESE PALABRA: ";
        getline(cin,aux);
        if(buscar_palabra(aux)){
            cout<<endl<<"PALABRA YA INGRESADA";
            fclose(archivo);
            cin.ignore();
            return;
        }
        strcpy(palab.palabra, aux.c_str());
        cout<<"INGRESE TRADUCCION: ";
        getline(cin,aux);
        strcpy(palab.traduccion, aux.c_str());
        fflush(stdin);
        cout<<"INGRESE FUNCIONALIDAD: ";
        getline(cin,aux);
        strcpy(palab.funcionalidad, aux.c_str());
        fwrite( &palab, sizeof(Palabras), 1, archivo );
        cout<<"\nDESEA AGREGAR OTRA PALABRA s/n: ";
        cin>>continuar;
        
        int x,y,i;
        system ("cls");
 gotoxy(100,10);
 printf("AGREGANDO");
   
 
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
 
    } while((continuar=='s') || (continuar=='S') );
    system ("cls");
	gotoxy(85,10);   
    cout<<"REGISTROS AGREGADOS EXITOSAMENTE";
    Sleep(1500);
    fclose(archivo);
    cin.ignore();
    
}

void abrir_registro(){
    system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	Palabras palab;
	fread ( &palab, sizeof(Palabras), 1, archivo );
	

	while (feof( archivo ) == 0){
		cout<<"-------------------------------------------------------"<<endl;
		cout<<"  "<<endl;
		cout << "PALABRA "<< palab.palabra<<endl;
		cout << "TRADUCCION "<<palab.traduccion<<endl;
		cout << "FUNCIONALIDAD "<<palab.funcionalidad<<endl;
		fread ( &palab, sizeof(Palabras), 1, archivo );
	}
    cout<<"_____________________________________________________"<<endl;
    cout<<endl;
	fclose(archivo);
}

void mostrar_solo_palabra(){
    system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	Palabras palab;
	fread ( &palab, sizeof(Palabras), 1, archivo );
	
	cout <<" PALABRAS REGISTRADAS "<<endl;
	while (feof( archivo ) == 0){
		cout<<"____________________"<<endl;
		cout << palab.palabra <<endl;
		fread ( &palab, sizeof(Palabras), 1, archivo );
	}
    cout<<endl;
	fclose(archivo);
}

void eliminar_palabra(){
    mostrar_solo_palabra();
    bool enco;
    string palabra_elimina;
    cout<<"\t\t\tEliminar Palabra\n";
    cout<<"\t\t-------------------\n";
    cout<<"\nINGRESA LA PALABRA A ELIMINAR:"<<endl;
    fflush(stdin);
    getline(cin,palabra_elimina);
    if(!buscar_palabra(palabra_elimina)){
        cout<<"PALABRA NO ENCONTRADA";
        cin.ignore();
        return;
    }
    FILE* archivo = fopen(nombre_archivo, "rb");
	FILE* archivo2 = fopen("auxi.dat", "a+b");
    Palabras palab;
	
	fread ( &palab, sizeof(Palabras), 1, archivo );
	
    
	while (feof( archivo ) == 0){
    if (palabra_elimina==palab.palabra){
    	
    	int x,y,i;
        system ("cls");
 gotoxy(100,10);
 printf("ELIMINANDO");
   
 
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
 		gotoxy(100,10);
        cout<<"REGISTRO ELIMINADO"<<endl;
        cout<<endl;
        Sleep(1500);
    } else
        fwrite( &palab, sizeof(Palabras), 1, archivo2 );
    fread ( &palab, sizeof(Palabras), 1, archivo );
    }
    fclose(archivo);
    fclose(archivo2);
    remove("palabras.dat");
    rename("auxi.dat","palabras.dat");
    getch();
}

void modificar_palabra(){
    mostrar_solo_palabra();
    fflush(stdin);
    string modif;
            cout<<"\t\t\tModificar Palabra\n";
        cout<<"\t\t-------------------\n";
    cout<<"\n\nINGRESE PALABRA A MODIFICAR ";
    fflush(stdin);
    getline(cin,modif);
    
	if(!buscar_palabra(modif)){
        cout<<"PALABRA NO ENCONTRADA";
        cin.ignore();
        return modificar_palabra();
    }
    
    bool res=0;
    FILE* archivo = fopen(nombre_archivo,"rb");
    int pos=0;
    Palabras palab;
	fread ( &palab, sizeof(Palabras), 1, archivo );
	while (!feof( archivo )){
	    if(!strcmp(palab.palabra,modif.c_str())){
            res=1;
            break;
        }
        pos+=1;
        fread ( &palab, sizeof(Palabras), 1, archivo );
	}
    fclose(archivo);
	if(res=0){
        cout<<"PALABRA NO ENCONTRADA";
        cin.ignore();
        return;
	}
    Palabras palabramodif;
	archivo = fopen(nombre_archivo,"rb");
    fseek ( archivo,pos * sizeof(Palabras), SEEK_SET );
    fread ( &palabramodif, sizeof( Palabras ), 1, archivo );
    int op;
	fclose(archivo);
    cout<<"\n1. PALABRA: "<<palabramodif.palabra<<endl;
    cout<<"2. TRADUCCION: "<<palabramodif.traduccion<<endl;
    cout<<"3. FUNCIONALIDAD: "<<palabramodif.funcionalidad<<endl;
	cout<<"\nQUE DESEA MODIFICAR?: ";
	cin>>op;
	cin.ignore();
	string aux;
	switch(op){
		case 1:{
			cout<<"\nINGRESE LA PALABRA MODIFICADA: ";
			getline(cin,aux);
            if(!buscar_palabra(aux)){
                cout<<"PALABRA YA INGRESADA";
                cin.ignore();
                return;
            }
        	strcpy(palabramodif.palabra,aux.c_str());
			break;
		}
		case 2:{
			cout<<"\nINGRESE LA TRADUCCION MODIFICADA: ";
			getline(cin,aux);
        	strcpy(palabramodif.traduccion,aux.c_str());
			break;
		}
		case 3:{
			cout<<"\nINGRESE LA FUNCIONALIDAD MODIFICADA: ";
			getline(cin,aux);
        	strcpy(palabramodif.funcionalidad,aux.c_str());
			break;
		}
		default:{
			cout<<"\n OPCION NO VALIDA\n\n   ";
			cin.ignore();
			return modificar_palabra();
		break;
		}
	}
	archivo = fopen(nombre_archivo, "rb");
	FILE* archivo2 = fopen("auxi.dat", "a+b");
	int registro=0;
	fread ( &palab, sizeof(Palabras), 1, archivo );
	while (feof( archivo ) == 0){
		if(registro==pos){
       		fwrite( &palabramodif, sizeof(Palabras), 1, archivo2 );
       		
       		int x,y,i;
        system ("cls");
 gotoxy(100,10);
 printf("MODIFICANDO");
   
 
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
 		gotoxy(100,10);
       		
            cout<<"REGISTRO MODIFICADO"<<endl;
			Sleep(1500);
		}
       	else
            fwrite( &palab, sizeof(Palabras), 1, archivo2 );
		fread ( &palab, sizeof(Palabras), 1, archivo );
		registro += 1;
	}
	fclose(archivo2);
	fclose(archivo);
	remove("palabras.dat");
	rename("auxi.dat","palabras.dat");
	getch();
}

bool buscar_palabra(string aux){
    bool res=0;
    FILE* archivo = fopen(nombre_archivo,"rb");
    Palabras palab;
	fread ( &palab, sizeof(Palabras), 1, archivo );
	while (!feof( archivo )){
	    if(!strcmp(palab.palabra,aux.c_str())){
            res=1;
            break;
        }
        fread ( &palab, sizeof(Palabras), 1, archivo );
	}
    fclose(archivo);
	return res;
}
