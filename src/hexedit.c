#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "./hexedit.h"


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



void hexeditor_delete(HexEditor *he) {


}



HexEditor hexeditor_new(const char *filename) {

    HexEditor hexeditor = {
        .bytes          = NULL,
        .bytes_capacity = 5,
        .bytes_size     = 0,
        .cursor_column  = 0,
        .cursor_row     = 0,
    };

    hexeditor.bytes = read_file(filename, &hexeditor.bytes_capacity);
    hexeditor.bytes_size = hexeditor.bytes_capacity;
    if (hexeditor.bytes == NULL) {
        fprintf(stderr, "Failed to read file\n");
        exit(1);
    }

    return hexeditor;

}

void hexeditor_destroy(HexEditor *he) {
    free(he->bytes);
    he->bytes = NULL;
}
