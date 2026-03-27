#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    unsigned char byte;
    int contador = 0;

    // Leemos de a 1 byte hasta que se cierre la entrada (EOF / read devuelva 0)
    while (read(0, &byte, 1) > 0) {
        contador++;
        
        // Si llegamos al 8vo byte (el original)
        if (contador == 8) {
            if (write(1, &byte, 1) < 0) {
                perror("write");
                return EXIT_FAILURE;
            }
            contador = 0; // Reiniciamos para el próximo bloque de 8
        }
    }

    // Opcional: imprimir un salto de línea al final para que tu terminal no se superponga
    char newline = '\n';
    write(1, &newline, 1);

    return EXIT_SUCCESS;
}