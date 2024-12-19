#ifndef _UI_H
#define _UI_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "./hexedit.h"


typedef struct {
    size_t columns;
    size_t visual_cursor_row;
    size_t visual_cursor_column;
    HexEditor *hexedit;
} UiState;


extern UiState ui_new(HexEditor *he);
extern void ui_loop(UiState *ui);




#endif // _UI_H
