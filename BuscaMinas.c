#include "BuscaMinash.h"
#include "BuscaminasFunc.c"
#include "FuncionesJuego.c"

int main(){
    system("cls");
    // 1era parte, AUTENTICACIONES, gestor de contrasenas:
    int opcion=0; const char *archivo="usuarios.txt";
    char usuario[30],contrasena[30]; int intentos=3;
    while(1)
    {   
        printf("\n\t\tBienvenido a Buscaminas :)\n\n");
        printf("Para jugar debe iniciar seción o crear una cuenta nueva: \n");
        printf("\t1-)Crear cuenta Nueva: \n");
        printf("\t2-)Iniciar secion en cuenta existente\n");
        printf("Ingrese su opcion: ");
        opcion=cargarEnteroEntreAB(1,2);

        if (opcion==1){
            crearUsuario(archivo);
            esperarEnter();
            system("cls");
            break;
        }else{
            while(intentos>0)
            {
                printf("Tiene %d intentos.\n",intentos);    
                printf("Ingrese el nombre de usuario: ");
                scanf("%s", usuario);
                printf("Ingrese la contrasena: ");
                scanf("%s", contrasena);

                if (autenticarUsuario(archivo,usuario, contrasena)) {
                    printf("Autenticación exitosa.\n");
                    esperarEnter();
                    system("cls");
                    break;
                } else {
                    printf("Nombre de usuario o contrasena incorrecta, intente nuevamente.\n\n");
                    intentos--;
                }
            }
            if (intentos==0){
                system("cls");
            }else{break;}
        }
    }
    // FIN PRIMERA PARTE -----> AUTENTICACIONES


    srand(time(NULL));
    // 2nda parte INICIO ------> MENU PRINCIAL
    opcion=0; int filas=8,columnas=8,minas=10,terminar=1 ;
    while(terminar)
    {   
        printf("\n\n\t\tBienvenido al Menu Principal :]\n\n");
        printf("1-) Iniciar partida \n");
        printf("2-) Ajustar tablero: \n");
        printf("\tEl tablero tiene:\n \tfilas: %d , columnas: %d , minas: %d \n",filas,columnas,minas);
        printf("3-) Ver Estadisticas: \n"); // todos los jugadores
        printf("4-) Mostrar Puntaje: \n"); // puntaje usuario y maquina
        printf("5-) Salir y cerrar juego. \n\n");
        printf("\nIngrese su opcion: ");
        opcion=cargarEnteroEntreAB(1,5);

        switch (opcion)
        {
        // Iniciar partida
        case 1:
            {
                system("cls");
                jugarPartida(filas,columnas,minas);
                if (juegoActivo==0){
                    //gano
                    actualizarEstadisticas(archivo,usuario,1);
                }else if(juegoActivo==-1){
                    //perdio
                    actualizarEstadisticas(archivo,usuario,0);
                }
            }
            break;
        
        // Ajustar tablero
        case 2:
            {
                system("cls");
                printf("\t\tAjustes del Tablero:\n\n");
                printf("Debe haber entre 5 y 10 columnas y entre 1 y 10 minas: \n");
                printf("Ingrese filas: ");
                filas=cargarEnteroEntreAB(5,10);
                printf("Ingrese columnas: ");
                columnas=cargarEnteroEntreAB(5,10);
                printf("Ingrese minas: ");
                minas=cargarEnteroEntreAB(1,10);
                printf("Tablero ajustado con exito.\n\n");
                EsperarEnter();
                system("cls");
            }
            break;
        // Ver Estadisticas
        case 3:
            {
                system("cls");
                mostrarTodasLasEstadisticas(archivo);
                printf("\n");
                EsperarEnter();
                system("cls");
                break;
            }   

        // mostrar puntaje
        case 4:
            {
                system("cls");
                mostrarEstadisticas(archivo,usuario);
                printf("\n");
                EsperarEnter();
                system("cls");
                break;
            }
        
        // salir
        default:
            terminar=0;
            break;
        }
    }

    printf("\nFin del juego. Gracias por jugar :)\n");
    return 0;
}