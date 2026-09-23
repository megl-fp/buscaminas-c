
// Prototipos de funciones
void inicializarTablero(int filas, int columnas, char tablero[][columnas]);
void colocarMinas(int filas, int columnas, int minas, int tablero[][columnas]);
void imprimirTablero(int filas, int columnas, char tablero[][columnas]);
int minasAdyacentes(int filas, int columnas, int tablero[][columnas], int x, int y);
void revelarCeldas(int filas, int columnas, int tableroOculto[][columnas], char tableroUsuario[][columnas], int x, int y);
int verificarGanador(int filas, int columnas, int tableroOculto[][columnas], char tableroUsuario[][columnas], int minas);
void jugarPartida(int filas, int columnas, int minas);
/*
int main() {
    int filas = 8;
    int columnas = 8;
    int minas = MINAS;

    srand(time(NULL));

    jugarPartida(filas, columnas, minas);

    return 0;
}
*/

void esperarEnter() {
    printf("Presione Enter para continuar...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Consumir cualquier entrada previa
    getchar();  // Esperar a que el usuario presione "Enter"
}
// Función para inicializar el tablero del jugador
void inicializarTablero(int filas, int columnas, char tablero[][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = '_';  // Celdas ocultas
        }
    }
}
// variable glogal para su facil acceso
int ubiMinas[10][2]={{-5}};
// Función para colocar las minas aleatoriamente en el tablero
void colocarMinas(int filas, int columnas, int minas, int tablero[][columnas]) {
    int minasColocadas = 0;
    while (minasColocadas < minas) {
        int x = rand() % filas;
        int y = rand() % columnas;
        if (tablero[x][y] != -1) {
            tablero[x][y] = -1;  // Coloca una mina
            ubiMinas[minasColocadas][0]=x;
            ubiMinas[minasColocadas][1]=y;        
            minasColocadas++;
        }
    }
}

// Función para imprimir el tablero del jugador
void imprimirTablero(int filas, int columnas, char tablero[][columnas]) {
    printf("   ");
    for (int j = 0; j < columnas; j++) {
        printf(" %d ", j + 1);
    }
    printf("\n");

    printf("  +");
    for (int j = 0; j < columnas; j++) {
        printf("---");
    }
    printf("+\n");

    for (int i = 0; i < filas; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < columnas; j++) {
            printf(" %c ", tablero[i][j]);
        }
        printf("|\n");
    }

    printf("  +");
    for (int j = 0; j < columnas; j++) {
        printf("---");
    }
    printf("+\n");
}

// Función para calcular el número de minas adyacentes a una celda
int minasAdyacentes(int filas, int columnas, int tablero[][columnas], int x, int y) {
    int cont = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < filas && j >= 0 && j < columnas && tablero[i][j] == -1) {
                cont++;
            }
        }
    }
    return cont;
}

// Función para revelar celdas en el tablero del jugador
// funcion recursiva para revelar ceros
void revelarCeldas(int filas, int columnas, int tableroOculto[][columnas], char tableroUsuario[][columnas], int x, int y) {
    if (x < 0 || x >= filas || y < 0 || y >= columnas || tableroUsuario[x][y] != '_') {
        return;
    }

    if (tableroOculto[x][y] == -1) {
        tableroUsuario[x][y] = 'M';  // Revela una mina
        return;
    }

    int minas = minasAdyacentes(filas, columnas, tableroOculto, x, y);
    tableroUsuario[x][y] = minas + '0';  // Muestra el número de minas adyacentes

    if (minas == 0) {
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i >= 0 && i < filas && j >= 0 && j < columnas) {
                    revelarCeldas(filas, columnas, tableroOculto, tableroUsuario, i, j);
                }
            }
        }
    }
}

// Función para verificar si el jugador ha ganado
int verificarGanador(int filas, int columnas, int tableroOculto[][columnas], char tableroUsuario[][columnas], int minas) {
    int celdasNoReveladas = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tableroUsuario[i][j] == '_') {
                celdasNoReveladas++;
            }
        }
    }
    return celdasNoReveladas == minas;
}


//#########################################################################################################
//int GlobalEstadoGame=0;
// a=1 save , a=0 random , a=-1 pum
int probabilidad(){
    int a=rand()%101;
    if (0<=a && a<=80 ){
        return 1;
    }else if(81<=a && 95<=a){
        return 0;
    }else{
        return -1;
    }
}

typedef struct Puntoxy
{
    int x;
    int y;
} PuntoXY ;
// estado=-1 --> pum , estado=0 --> random , estado=1 --> save
PuntoXY func_radial(int filas, int columnas,int tableroOculto[][columnas], char tableroUsuario[][columnas], int a,int b,int estado){
    PuntoXY punto; punto.x=0 ; punto.y=0;  
    int mat_Aro[45][2]={ {-1,-1} , {-1,0} , {-1,1} , {0,-1} , {0,+1} , {1,-1} , {1,0} , {1,1} 
    ,{-2,-2},{-2,-1},{-2,0},{-2,1},{-2,2},{-1,-2},{-1,2},{0,-2},{0,2},{1,-2},{1,2},{2,-2},{2,2}, {-3,-3}, {-3,-2}, {-3,-1}, {-3,0}, 
    {-3, 1}, {-3,2}, {-3,3}, {-2,3}, {-1,3}, {0,3}, {1,3}, {2,3}, {3,3}, {3,2}, {3,1}, {3,0}, {3,-1}, {3,-2}, {3,-3}, {2,-3}, {1,-3}, {0,-3},
    {-1,-3}, {-2,-3}};

    if (estado==1){ 
        int aux=0 , contador=0;
        while (1) //busqueda radial alrededor de donde el jugador revelo para encontrar una posicion segura sí o sí sin revelar
        {
            aux=rand()%21;
            if(a+mat_Aro[aux][0]<filas && a+mat_Aro[aux][0]>=0){
                if(b+mat_Aro[aux][1]<columnas && b+mat_Aro[aux][1]>=0){
                    punto.x=a+mat_Aro[aux][0];
                    punto.y=b+mat_Aro[aux][1];
                    if(tableroUsuario[punto.x][punto.y]=='_' && tableroOculto[punto.x][punto.y]!=-1){
                        return punto;
                    }
                        
                }
            }
            contador++;
            if(contador==5){
                while(1){
                    punto.x=rand()%filas;
                    punto.y=rand()%columnas;
                    if(tableroUsuario[punto.x][punto.y]=='_' && tableroOculto[punto.x][punto.y]!=-1){
                        return punto;
                    }
                }
            }

        }
            
    }else if(estado==0)
    {
        int aux=0 , contador=0;
        while (1)//busqueda radial alrededor de donde el jugador revelo para encontrar una posicion cualquiera, sin revelar
        {
            aux=rand()%21;
            if(a+mat_Aro[aux][0]<filas && a+mat_Aro[aux][0]>0){
                if(b+mat_Aro[aux][1]<columnas && b+mat_Aro[aux][1]>0){
                    punto.x=a+mat_Aro[aux][0];
                    punto.y=b+mat_Aro[aux][1];
                    if(tableroUsuario[punto.x][punto.y]=='_'){
                        return punto;
                    }
                        
                }
            }
            contador++;
            if(contador==40){//busqueda iterativa en el caso de que no haya una posicion alrededor de la última pos que revelo el jugador
                while(1){
                    punto.x=rand()%filas;
                    punto.y=rand()%columnas;
                    if(tableroUsuario[punto.x][punto.y]=='_'){
                        return punto;
                    }
                }
               
            }
        }
    }else{ //devolver posicion de mina directamente :o
        punto.x=ubiMinas[0][0]; //ubi de la 1era mina ite
        punto.y=ubiMinas[0][1];
        return punto;
    }

}
int juegoActivo = 1;
void computadoraJuega(int filas, int columnas, int tableroOculto[][columnas], char tableroUsuario[][columnas],int usu_X,int usu_Y) {
    PuntoXY point;
    // Selección aleatoria de movimiento

    int opcion=probabilidad();
    if(opcion==1){
        point=func_radial(filas,columnas,tableroOculto,tableroUsuario,usu_X,usu_Y,1);
    
    }else if(opcion==0){
        point=func_radial(filas,columnas,tableroOculto,tableroUsuario,usu_X,usu_Y,0);
    
    }else if(opcion==-1)
    {
        point=func_radial(filas,columnas,tableroOculto,tableroUsuario,usu_X,usu_Y,-1);
    }
    // Mostrar en pantalla la celda seleccionada por la computadora
    printf("El jugador 2 selecciono: \n");
    printf("\tFila: %d \n\tColumna: %d \n\n",point.x+1 , point.y+1);
    

    // Revelar la celda seleccionada por la computadora
    if (tableroOculto[point.x][point.y] == -1) {
        tableroUsuario[point.x][point.y]='M';
        imprimirTablero(filas, columnas, tableroUsuario);
        printf("El jugador 2 ha tocado una bomba en (%d, %d).\n", point.x+1, point.y+1);
        printf("¡VICTORIA MAGISTRAL!\n");
        //GlobalEstadoGame=1; //se pone en 1 y al llegar el turno del jugador ya le marca como ganador al usu
        juegoActivo=0;
    } else {
        revelarCeldas(filas,columnas,tableroOculto,tableroUsuario,point.x,point.y);
        imprimirTablero(filas, columnas, tableroUsuario);
        juegoActivo=1;
        
    }
    esperarEnter();
}
//#########################################################################################################



// Función principal para jugar una partida
void jugarPartida(int filas, int columnas, int minas) {
    int tableroOculto[filas][columnas];
    char tableroUsuario[filas][columnas];

    inicializarTablero(filas, columnas, tableroUsuario);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tableroOculto[i][j] = 0;  // Inicializa el tablero oculto con 0 (sin minas)
        }
    }

    colocarMinas(filas, columnas, minas, tableroOculto);

    juegoActivo = 1;
    while (juegoActivo==1) {
        system("cls");
        imprimirTablero(filas, columnas, tableroUsuario);
        printf("¡Es tu turno!\n");
        printf("Para colocar una banderita ingrese (0,0): \n");
        printf("Ingrese fila (1-%d): ", filas);
        int x=cargarEnteroEntreAB(0,filas);
        //scanf("%d", &x);
        x--;

        printf("Ingrese columna (1-%d): ", columnas);
        int y=cargarEnteroEntreAB(0,columnas);
        printf("\n");
        //scanf("%d", &y);
        y--;
        if(x==-1 || y==-1 ){
            printf("Ingrese fila (1-%d) de la banderita: ",filas);
            x=cargarEnteroEntreAB(1,filas);
            x--;
            printf("Ingrese la columna (1-%d) de la banderita: ",columnas);
            y=cargarEnteroEntreAB(1,columnas);
            y--;
            tableroUsuario[x][y]='B';

            system("cls");
            imprimirTablero(filas, columnas, tableroUsuario);
            printf("Ingrese fila (1-%d) de la banderita: %d \n", columnas,1+x);
            printf("Ingrese columna (1-%d) de la banderita: %d \n", columnas,1+y);
            esperarEnter();

        }else if (tableroOculto[x][y] == -1) 
        {
            system("cls");
            tableroUsuario[x][y] = 'M';  // Revelar la mina
            imprimirTablero(filas, columnas, tableroUsuario);
            printf("¡Boom! La celda (%d,%d) ah explotado.\n",x+1,y+1);
            printf("Haz perdido.\n");
            //GlobalEstadoGame=-1;
            juegoActivo = -1;
        } else {
            revelarCeldas(filas, columnas, tableroOculto, tableroUsuario, x, y);
            if (verificarGanador(filas, columnas, tableroOculto, tableroUsuario, minas)) {
                imprimirTablero(filas, columnas, tableroUsuario);
                printf("¡Felicidades! Has ganado el juego.\n");
                //GlobalEstadoGame=1;
                juegoActivo = 0;
            }else{
                system("cls");
                imprimirTablero(filas, columnas, tableroUsuario);
                printf("Ingrese fila (1-%d): %d \n", columnas,1+x);
                printf("Ingrese columna (1-%d): %d \n", columnas,1+y);
                esperarEnter();
            }
        }
        // parte IA .
        if (juegoActivo==1){
            system("cls");
            printf("\nTurno del Jugador 2: \n");
            computadoraJuega(filas, columnas, tableroOculto, tableroUsuario,x,y);
            if(juegoActivo==-1){
                printf("\nHa ganado el jugador 2 :(\n");
            }
        }
        if(juegoActivo==0 || juegoActivo==-1){
            printf("\n\nTablero con las minas descubiertas. \n\n");
            for(int i=0;i<minas;i++){
                tableroUsuario[ubiMinas[i][0]][ubiMinas[i][1]] = 'M' ;
            }
            imprimirTablero(filas,columnas,tableroUsuario);
            esperarEnter();
        }
    }
}
