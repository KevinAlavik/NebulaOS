#include "utils.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Function to clear the screen
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}
