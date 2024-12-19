#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "./ui.h"
#include "./hexedit.h"

#include <ncurses.h>



#define GAP 3
#define HIGHLIGHT 1





// buf should be of size 3
static void byte_to_string(char *buf, uint8_t byte) {

    memset(buf, 0, 3);
    snprintf(buf, 3, "%x", byte);

    // "f" -> "0f"
    if (strlen(buf) == 1) {
        buf[1] = buf[0];
        buf[0] = '0';
    }

}



static void render_bytes(UiState *ui) {

    int row = 0;
    size_t indent = 0;

    HexEditor *he = ui->hexedit;

    for (size_t i=1; i < he->bytes_size; ++i) {

        size_t index = i - 1;

        char buf[3] = { 0 };
        uint8_t byte = he->bytes[index];
        byte_to_string(buf, byte);

        if ((size_t) row == ui->visual_cursor_row &&
            ui->visual_cursor_column == index-indent
        ) {
            color_set(HIGHLIGHT, 0);
        } else {
            color_set(0, 0);
        }

        mvprintw(row, (index-indent) * GAP, "%s", buf);

        if (i % ui->columns == 0) {
            row++;
            indent += ui->columns;
        }

    }

}



static void columns_bounds_check(UiState *ui) {
    int screen_width  = getmaxx(stdscr);
    if (ui->columns < 1) {
        ui->columns = 1;
    }
    if (ui->columns * 3 > (size_t) screen_width) {
        ui->columns = screen_width/3;
    }
}


UiState ui_new(HexEditor *he) {
    UiState ui = {
        .columns = 16,
        .hexedit = he,
        .visual_cursor_column = 0,
        .visual_cursor_row    = 0,
    };
    return ui;
}



void ui_loop(UiState *ui) {

    initscr();
    curs_set(0);
    start_color();

    init_pair(HIGHLIGHT, COLOR_BLACK, COLOR_WHITE);


    bool quit = false;
    while (!quit) {

        columns_bounds_check(ui);

        render_bytes(ui);



        int c = getch();
        switch (c) {
            case '+': {
                ui->columns++;
            } break;
            case '-': {
                ui->columns--;
            } break;
            case 'j': {
                ui->visual_cursor_row++;
            } break;
            case 'k': {
                ui->visual_cursor_row--;
            } break;
            case 'h': {
                ui->visual_cursor_column--;
            } break;
            case 'l': {
                ui->visual_cursor_column++;
            } break;
            case 'q': {
                quit = true;
            } break;
        }

        clear();
        refresh();


    }

    endwin();

}
