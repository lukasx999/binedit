#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "./hexedit.h"
#include "./ui.h"



void print_bytes(const uint8_t *bytes, size_t size) {
    printf("[ ");
    for (size_t i=0; i < size-1; ++i) {
        printf("%x, ", bytes[i]);
    }
    printf("%x ]\n", bytes[size-1]);
}




int main(void) {

    const char *filename = "file.txt";

    HexEditor hexeditor = hexeditor_new(filename);

    UiState ui = ui_new(&hexeditor);
    ui_loop(&ui);


    return EXIT_SUCCESS;
}
