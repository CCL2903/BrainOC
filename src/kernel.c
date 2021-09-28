#include <stddef.h>
#include <stdint.h>

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int t_col = 0;
int t_row = 0;

uint8_t t_color = 31;

void t_init(){
    for (int col = 0; col < VGA_COLS; col++){
        for (int row = 0; row < VGA_ROWS; row++){
            size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = ((uint16_t)t_color << 8) | ' ';
        }
    }
}

void t_putch(char c){
    switch(c){
        case '\n': {
            t_col = 0;
            t_row++;
            break;
        }

        default: {
            size_t index = (VGA_COLS * t_row) + t_col;
            vga_buffer[index] = ((uint16_t)t_color << 8) | c;
            t_col++;
            break;
        }

        if (t_col >= VGA_COLS){
            t_col = 0;
            t_row++;
        }
        
        if (t_row >= VGA_ROWS){
            t_col = 0;
            t_row = 0;
        }
    }
}

void t_print(const char* str){
    for (size_t i = 0; str[i] != '\0'; i++){
        t_putch(str[i]);
    }
}

void kernel_main(){

    t_init();
    t_print("#####   #####   ####   ###### ##   ##    ####    ##### \n");
    t_print("##  ##  ##  ##  ##  ##   ##   ###  ##  ##    ##  ##\n");
    t_print("#####   #####   ######   ##   ## # ##  ##    ##  ##\n");
    t_print("##  ##  ##  ##  ##  ##   ##   ##  ###  ##    ##  ##\n");
    t_print("#####   ##  ##  ##  ## ###### ##   ##    ####    #####\n");

    t_print("Author: TimurCoderov \nVersion: 1.0.0 (build 56)\nRelease: 28.09.2021");
    while(1){

    }
}