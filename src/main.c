#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "./ui.h"



void print_bytes(const uint8_t *bytes, size_t size) {
    printf("[ ");
    for (size_t i=0; i < size-1; ++i) {
        printf("%x, ", bytes[i]);
    }
    printf("%x ]\n", bytes[size-1]);
}



// Returns NULL on failure
static uint8_t* read_file(const char *filename, size_t *out_size) {

    struct stat statbuf = { 0 };
    stat(filename, &statbuf);
    size_t size = statbuf.st_size;

    uint8_t *bytes = calloc(size, sizeof(uint8_t));

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    size_t bytes_read = fread(bytes, sizeof(uint8_t), size, file);
    if (bytes_read != size) {
        return NULL;
    }

    fclose(file);

    *out_size = size;
    return bytes;
}


uint8_t** copy_bytes_to_rows(const uint8_t *bytes, size_t size, size_t columns) {

    size_t rows = size / columns;
    uint8_t **newbytes = calloc(rows, sizeof(uint8_t*));

    for (size_t i=0; i < rows; ++i) {
        newbytes[i] = calloc(columns, sizeof(uint8_t));
        size_t offset = i * columns;
        memcpy(newbytes[i], bytes+offset, columns);
    }

    return newbytes;

}



int main(void) {

    const char *filename = "file.txt";
    const size_t columns = 16;

    size_t size = 0;
    uint8_t *bytes = read_file(filename, &size);
    if (bytes == NULL) {
        fprintf(stderr, "Failed to read file\n");
        exit(1);
    }

    // print_bytes(bytes, size);

    uint8_t **newbytes = copy_bytes_to_rows(bytes, size, columns);
    free(bytes);


    newbytes[0][0] = 0x0;
    newbytes[1][0] = 0xff;
    newbytes[2][0] = 0xf;


    ui_loop(newbytes, size/columns, columns);


    for (size_t i=0; i < size/columns; ++i) {
        free(newbytes[i]);
    }
    free(newbytes);




    return EXIT_SUCCESS;
}
