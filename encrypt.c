#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void encrypt_then_write(char c){
    char temp[7]; // los 7 caracteres aleatorios

    for(int i = 0; i < 7; i++){
        temp[i] = rand() % 256;
    }

    if(write(1, temp, 7) == -1){
        perror("Error al escribir bytes aleatorios");
        exit(EXIT_FAILURE);
    }
    
    if (write(1, &c, 1) == -1) {
        perror("Error al escribir caracter");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    if(argc > 1){
        // Encriptar desde los argumentos (argv[1])
        for (int i = 0; argv[1][i] != '\0'; i++) {
            encrypt_then_write(argv[1][i]);
        }
    } else {
        // Encriptar desde la entrada estándar
        char buffer;
        int bytes_leidos;
        
        while ((bytes_leidos = read(0, &buffer, 1)) > 0) {
            encrypt_then_write(buffer);
        }
        
        if (bytes_leidos == -1) {
            perror("Error al leer de la entrada estándar");
            exit(EXIT_FAILURE);
        }
    }
    
    // Termina la ejecución del programa.   
    exit(EXIT_SUCCESS);
}