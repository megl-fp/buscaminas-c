#include "BuscaMinash.h"

// struct para gestionar datos de los jugadores
typedef struct {
    char nombre[30];
    char contrasena[30];
    int ganadas;
    int perdidas;
    int totalPartidas;
} Usuario;

void crearUsuario(const char *archivo);
int autenticarUsuario(const char *archivo, const char *nombre, const char *contrasena);
void actualizarEstadisticas(const char *archivo, const char *nombre, int estado);W
void mostrarEstadisticas(const char *archivo, const char *nombre);
void mostrarTodasLasEstadisticas(const char *archivo) ;
void agregarUsuario(FILE *file, Usuario *usuario);
Usuario* leerUsuario(FILE *file, Usuario *usuario);


void EsperarEnter() {
    printf("Presione Enter para continuar...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Consumir cualquier entrada previa
    getchar();  // Esperar a que el usuario presione "Enter"
}
//######################################################
int cargarEntero() {
    char numero[20];
    int bandera;
    while (1) {
        bandera = 1;
        scanf("%s", numero);
        
        for (int i = 0; i < strlen(numero); i++) {
            if (!isdigit(numero[i])) {
                bandera = 0;
                printf("Error, ingrese un número entero.\n");
                break;
            }
        }
        
        if (bandera) {
            return atoi(numero);
        }
    }
}

int cargarEnteroEntreAB(int a,int b){
    int c=0;
    while (1)
    {
        c=cargarEntero();
        if (a<=c && c<=b){
            return c;
        }else{
            printf("Valor fuera de rango, intente nuevamente: ");
        }
    }
}

//######################################################
// funcion para verificar si un usuario esta en el archivo.
int UsuarioExiste(const char *archivo, const char *nombre) {
    Usuario usuario;
    FILE *file = fopen(archivo, "r");
    
    if (!file) {
        perror("No se pudo abrir el archivo");
        return 0;
    }
    
    while (leerUsuario(file, &usuario)) {
        if (strcmp(usuario.nombre, nombre) == 0) {
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return 0;
}


void crearUsuario(const char *archivo) {
    int intentos=3;
    Usuario usuario; 
    while(intentos>0)
    {   
        printf("Tiene %d intenteos.\n",intentos);
        printf("Ingrese nombre de usuario: ");
        scanf("%s", usuario.nombre);
        printf("Ingrese contraseña: ");
        scanf("%s", usuario.contrasena);
        usuario.ganadas = 0;
        usuario.perdidas = 0;
        usuario.totalPartidas = 0;
        if(!(UsuarioExiste(archivo , usuario.nombre))){
            printf("Usuario creado exitosamente :). \n");
            EsperarEnter();
            system("cls");
            intentos=0;
            
            FILE *file = fopen(archivo, "a");
            if (!file) {
                perror("No se pudo abrir el archivo");
            return;
            }
            agregarUsuario(file, &usuario);
            fclose(file);
            
        }else{
            intentos--;
            printf("Ese usuario ya existe. Intente nuevamente.\n");
        }
    }
    
    
}

int autenticarUsuario(const char *archivo, const char *nombre, const char *contrasena) {
    Usuario usuario;
    FILE *file = fopen(archivo, "r");
    
    if (!file) {
        perror("No se pudo abrir el archivo");
        return 0;
    }
    
    while (leerUsuario(file, &usuario)) {
        if (strcmp(usuario.nombre, nombre) == 0 && strcmp(usuario.contrasena, contrasena) == 0) {
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return 0;
}


// estado=1 --> ganó ; estado=0 --> perdió
void actualizarEstadisticas(const char *archivo, const char *nombre, int estado) {
    Usuario usuario;
    FILE *file = fopen(archivo, "r+");
    FILE *tempFile = fopen("temp.txt", "w");
    
    if (!file || !tempFile) {
        perror("No se pudo abrir el archivo");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }
    
    while (leerUsuario(file, &usuario)) {
        if (strcmp(usuario.nombre, nombre) == 0) {
            if (estado == 1) {
                usuario.ganadas += 1;  // Incrementar ganadas
            } else {
                usuario.perdidas += 1; // Incrementar perdidas
            }
            usuario.totalPartidas += 1; // Incrementar total de partidas
        }
        agregarUsuario(tempFile, &usuario); // Escribir en el archivo temporal
    }
    
    fclose(file);
    fclose(tempFile);
    remove(archivo);       // Eliminar archivo original
    rename("temp.txt", archivo); // Renombrar archivo temporal
}

void mostrarEstadisticas(const char *archivo, const char *nombre) {
    Usuario usuario;
    FILE *file = fopen(archivo, "r");
    
    if (!file) {
        perror("No se pudo abrir el archivo");
        return;
    }
    
    while (leerUsuario(file, &usuario)) {
        if (strcmp(usuario.nombre, nombre) == 0) {
            printf("Estadísticas de %s:\n", usuario.nombre);
            printf("Partidas ganadas: %d\n", usuario.ganadas);
            printf("Partidas perdidas: %d\n", usuario.perdidas);
            printf("Total de partidas: %d\n", usuario.totalPartidas);
            break;
        }
    }
    
    fclose(file);   
}


void mostrarTodasLasEstadisticas(const char *archivo) {
    Usuario usuario;
    FILE *file = fopen(archivo, "r");

    if (!file) {
        perror("No se pudo abrir el archivo");
        return;
    }

    printf("Estadísticas de todos los jugadores:\n");
    printf("-----------------------------------\n");

    while (fscanf(file, "%49s\n%49s\n%d\n%d\n%d\n", usuario.nombre, usuario.contrasena, &usuario.ganadas, &usuario.perdidas, &usuario.totalPartidas) == 5) {
        printf("Nombre: %s\n", usuario.nombre);
        printf("Ganadas: %d\n", usuario.ganadas);
        printf("Perdidas: %d\n", usuario.perdidas);
        printf("Total de Partidas: %d\n", usuario.totalPartidas);
        printf("--------------------------\n");
    }

    fclose(file);
}

void agregarUsuario(FILE *file, Usuario *usuario) {
    fprintf(file, "%s\n", usuario->nombre);
    fprintf(file, "%s\n", usuario->contrasena);
    fprintf(file, "%d\n", usuario->ganadas);
    fprintf(file, "%d\n", usuario->perdidas);
    fprintf(file, "%d\n", usuario->totalPartidas);
}
Usuario* leerUsuario(FILE *file, Usuario *usuario) {
    return fscanf(file, "%49s\n%49s\n%d\n%d\n%d\n", usuario->nombre, usuario->contrasena, &usuario->ganadas, &usuario->perdidas, &usuario->totalPartidas) == 5 ? usuario : NULL;
}