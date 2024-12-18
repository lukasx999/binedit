#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <raylib.h>

#include "./lib.h"



#define WIDTH 1920
#define HEIGHT 1080


int main(void) {


    InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);


        }
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
