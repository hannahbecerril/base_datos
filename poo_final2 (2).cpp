#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string.h>
using namespace std;

class Archivo {
public:
    char matricula[10], nom[16], app[16], apm[16];
    int calif;

    Archivo(char p_matricula[9], char p_nom[16], char p_app[16], char p_apm[16], int p_calif) {
        strcpy(matricula, p_matricula);
        strcpy(nom, p_nom);
        strcpy(app, p_app);
        strcpy(apm, p_apm);
        calif = p_calif;
    }

    Archivo() {
        strcpy(matricula,"NA"); 
		strcpy(nom,"NA");  
		strcpy(app,"NA");
		strcpy(apm,"NA");
		calif=0;
    }

    void despliega() {
        printf("Matrícula     : %s\n", matricula);
        printf("Nombre      : %s\n", nom);
        printf("Apellido Paterno      : %s\n", app);
        printf("Apellido Materno      : %s\n", apm);
        printf("Calificacion      : %d\n", calif);
    }

    void graba() {
        ofstream arch;
        arch.open("alumnos.csv", ios::app);
        arch << matricula << "," << nom << "," << app << "," << apm << ","  << calif << "\n";
        arch.close();
    }

    void busca_rec(char* buf, char matricula[9]) {
        bool existe;
        
        ifstream arch;
        arch.open("alumnos.csv", ios::in);
        existe=false;
        while (!arch.eof()) {
            arch >> buf;
            if (strnicmp(buf, matricula, 9) == 0) {
                existe = true;
                break;
            }
        }
        if (!existe) strcpy(buf, "XXX");
    }

    void listado(){ 
		char cad[80], *token, matricula[10], nom[16], app[16], apm[16], calif[4];
		for (int i=0;i<=40;i++) printf("\n"); 
		printf("\n");
		printf("Matricula   Nombre            APP            APM                Calificacion \n");
		printf("-------------------------------------------------------------------------\n");

		ifstream arch;
		arch.open("alumnos.csv",ios::in); //
		while(!arch.eof()){ 
			arch>>cad; 
			if(!arch.eof()){
				token=strtok(cad,","); strcpy(matricula,token);
				token=strtok(NULL,","); strcpy(nom,token);
				token=strtok(NULL,","); strcpy(app,token);
				token=strtok(NULL,","); strcpy(apm,token);
				token=strtok(NULL,","); strcpy(calif,token);
				printf("%s  ", matricula);
				for (int i=0;i<strlen(nom);i++) if (nom[i]=='_') nom[i]=' '; 
				printf("%s  ",nom); for(int i=strlen(nom);i<=15;i++) printf(" ");
				for (int i=0;i<strlen(app);i++) if (app[i]=='_') app[i]=' ';
				printf("%s  ",app); for(int i=strlen(app);i<=15;i++) printf(" ");
				for (int i=0;i<strlen(apm);i++) if (apm[i]=='_') apm[i]=' '; 
				printf("%s  ",apm); for(int i=strlen(apm);i<=15;i++) printf(" ");
				printf("%s\n",calif); 
			} 
		} 
		arch.close();
		getche();
		
	}
		
}; 
void altas() {
    char matricula[10], nom[16], app[16], apm[16], cad[80];
    int calif;
    for (int i = 0; i < 40; i++)printf("\n");
    while (true) {
        printf("Indica la matricula del estudiante  :");
        gets(matricula);
        strupr(matricula);
        if ((strlen(matricula) != 9) || (matricula[0] != 'A') || (matricula[1] != '0')) {
            printf("Error, la matricula debe de estar en formato 'A01769561'\n");
            getche();
        } else
            break;
    }
    while (true) {
        printf("Indica el nombre del estudiante   : ");
        gets(nom);
        if ((strlen(nom) < 1) || (strlen(nom) > 15)) {
            printf("Error, el nombre debe tener entre 1 y 15 caracteres \n");
            getche();
        } else
            break;
    }
    while (true) {
        printf("Indica el apellido paterno del estudiante   : ");
        gets(app);
        if ((strlen(app) < 1) || (strlen(app) > 15)) {
            printf("Error, el apellido paterno debe tener entre 1 y 15 caracteres \n");
            getche();
        } else
            break;
    }
    while (true) {
        printf("Indica el apellido materno del estudiante   : ");
        gets(apm);
        if ((strlen(apm) < 1) || (strlen(apm) > 15)) {
            printf("Error, el apellido materno debe tener entre 1 y 15 caracteres \n");
            getche();
        } else
            break;
    }

    
    while (true) {
        printf("Indica la calificacion del estudiante   : ");
        scanf("%d", &calif);
        if ((calif < 1) || (calif > 100)) {
            printf("Error, la calificación debe estar entre 1 y 100  \n");
            getche();
        } else
            break;
    }
    for (int i = 0; i < strlen(nom); i++)if (nom[i] == ' ')nom[i] = '_';
    for (int i=0;i<strlen(app);i++) if (app[i]==' ') app[i]='_';
	for (int i=0;i<strlen(apm);i++) if (apm[i]==' ') apm[i]='_';
    Archivo obj; 
    Archivo obj1;
    obj.busca_rec(cad,matricula);
    if(strcmp(cad,"XXX")!=0){
    	printf("Error, matricula duplicada \n");
    	getche;
	}
	else{
		obj1=Archivo(matricula,nom,app,apm,calif);
		obj1.graba();
		getche();
	}
}

void consultas() {
    char cad[100], matricula[9];
    char* token, nom[16], app[16], apm[16], calif[4];
    printf("Indica la clave a consultar : ");gets(matricula);
    Archivo obj;
    obj.busca_rec(cad, matricula);
    if (strcmp(cad, "XXX") == 0) {
        printf("Error, la matricula no se encontró \n");
        getche();
    } else {
        token = strtok(cad, ",");
        token = strtok(NULL, ",");strcpy(nom, token);
        token = strtok(NULL, ",");strcpy(app, token);
        token = strtok(NULL, ",");strcpy(apm, token);
        token = strtok(NULL, ",");strcpy(calif, token);
      
		
        printf("Matricula     : %s\n", matricula);
        for (int i=0;i<strlen(nom);i++) if (nom[i]=='_') nom[i]=' '; 
        printf("Nombre      : %s\n", nom);
        for (int i=0;i<strlen(app);i++) if (app[i]=='_') app[i]=' '; 
        printf("Apellido Paterno      : %s\n", app);
        for (int i=0;i<strlen(apm);i++) if (apm[i]=='_') apm[i]=' '; 
        printf("Apellido Materno      : %s\n", apm);
        printf("Calificacion      : %s\n", calif);
        getche();
    }
}

void menu() {
    int op;
    char falso[2];
    while (op != 4) {
        printf("1) Alta de alumnos\n");
        printf("2) Consulta de alumnos\n");
        printf("3) Lista de alumnos\n");
        printf("4) Terminar\n");
        printf("Indica la opcion indicada   :", 162);
        scanf("%d", &op);
        gets(falso);
        if (op == 1)
            altas();
        if (op == 2)
            consultas();
        if (op == 3) {
            Archivo obj;
            obj.listado();
        }
    }
}

main() {
    menu();
}
