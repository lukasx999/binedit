#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "./ui.h"

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


static void render_bytes(uint8_t **bytes, size_t rows, size_t columns, size_t gap) {

    for (size_t row=0; row < rows; ++row) {
        for (size_t col=0; col < columns; ++col) {

            uint8_t byte = bytes[row][col];

            char buf[3] = { 0 };
            byte_to_string(buf, byte);

            mvprintw(row, col*gap, "%s", buf);

        }
    }

}





void ui_loop(uint8_t **bytes, size_t rows, size_t columns) {


    size_t cursor_x = 0;
    size_t cursor_y = 0;





    initscr();

    bool quit = false;
    while (!quit) {

        size_t gap = 3;

        render_bytes(bytes, rows, columns, gap);

        int screen_width  = getmaxx(stdscr);
        int screen_height = getmaxy(stdscr);




        move(cursor_y, cursor_x);


        int c = getch();
        switch (c) {
            case 'j': {
                cursor_y++;
            } break;
            case 'k': {
                cursor_y--;
            } break;
            case 'h': {
                cursor_x -= gap;
            } break;
            case 'l': {
                cursor_x += gap;
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
