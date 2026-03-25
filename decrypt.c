#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    unsigned char buffer[256];

    ssize_t bytesRead = read(0, buffer, sizeof(buffer));

    if (bytesRead < 0) {
        perror("read");
        return EXIT_FAILURE;
    }
    
    if (bytesRead % 8 != 0) {
        fprintf(stderr, "Longitud invalida: %zd\n", bytesRead);
        return EXIT_FAILURE;
    }
    
    ssize_t msgLen = bytesRead / 8;

    if (msgLen == 0) {
        // Nada que mostrar
        return EXIT_SUCCESS;
    }

    for (ssize_t i = 0; i < msgLen; i++) {
        unsigned char c = buffer[i * 8 + 7];
        if (write(1, &c, 1) < 0) {
            perror("write");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}