#ifndef _HEXEDIT_H
#define _HEXEDIT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct {
    uint8_t *bytes;
    size_t bytes_size;
    size_t bytes_capacity;

    size_t cursor_row;
    size_t cursor_column;
} HexEditor;


extern HexEditor hexeditor_new(const char *filename);
extern void hexeditor_destroy(HexEditor *he);




#endif // _HEXEDIT_H
