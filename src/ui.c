#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "./ui.h"
#include "hexedit.h"

#include <ncurses.h>




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



static void render_bytes(HexEditor *he, size_t gap, size_t columns) {

    int row = 0;
    size_t indent = 0;

    for (size_t i=1; i < he->bytes_count; ++i) {

        size_t index = i - 1;

        char buf[3] = { 0 };
        uint8_t byte = he->bytes[index];
        byte_to_string(buf, byte);

        mvprintw(row, (index-indent) * gap, "%s", buf);

        if (i % columns == 0) {
            row++;
            indent += columns;
        }

    }

}







void ui_loop(HexEditor *hexedit) {

    initscr();
    curs_set(0);


    size_t columns = 16;

    bool quit = false;
    while (!quit) {

        size_t gap = 3;

        int screen_width  = getmaxx(stdscr);
        int screen_height = getmaxy(stdscr);

        if (columns < 1) {
            columns = 1;
        }

        // if (columns*2 > screen_height) {
        //     columns = screen_height;
        // }

        render_bytes(hexedit, gap, columns);



        int c = getch();
        switch (c) {
            case '+': {
                columns++;
            } break;
            case '-': {
                columns--;
            } break;
            case 'j': {
            } break;
            case 'k': {
            } break;
            case 'h': {
            } break;
            case 'l': {
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
