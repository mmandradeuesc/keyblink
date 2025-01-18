#include <stdio.h>
#include "pico/stdlib.h"

#define VectorSize 4
#define BuzzerPIN 21

// Funções auxiliares
void PicoInit(const uint8_t*, const uint8_t*);
void PicoLoop(const uint8_t*, const uint8_t*, const char (*)[4]);

void SetInput(uint8_t);
void SetOutput(uint8_t);
void MapKeyboard(const uint8_t*, const uint8_t*);
char TestKeys(const uint8_t*, const uint8_t*, const char(*)[4]);

int main() {
    const uint8_t ROWS[VectorSize] = {9, 8, 7, 6}; 
    const uint8_t COLUMNS[VectorSize] = {5, 4, 3, 2}; 

    const char mapping[4][4] = {
// colunas ->                      linhas \/        
    //    5    4    3    2    
        {'1', '4', '7', '*'}, // 9
        {'2', '5', '8', '0'}, // 8
        {'3', '6', '9', '#'}, // 7
        {'A', 'B', 'C', 'D'}  // 6
    };

    PicoInit(ROWS, COLUMNS);
    PicoLoop(ROWS, COLUMNS, mapping);

    return 0;
}

void PicoInit(const uint8_t* ROWS, const uint8_t* COLUMNS){
    stdio_init_all();
    MapKeyboard(ROWS, COLUMNS); 
}

void PicoLoop(const uint8_t* ROWS, const uint8_t* COLUMNS, const char (*mapping)[4]){
    while (true) {
        char key = TestKeys(ROWS, COLUMNS, mapping);
        printf("Key: %c\n", key);
    }
}

void SetInput(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);   
    gpio_pull_down(pin);          
}

void SetOutput(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);  
    gpio_put(pin, 0);             
}

void MapKeyboard(const uint8_t* ROWS, const uint8_t* COLUMNS) {
    for (int i = 0; i < VectorSize; i++) {
        SetInput(ROWS[i]);  
        SetOutput(COLUMNS[i]); 
    }
}

char TestKeys(const uint8_t* ROWS, const uint8_t* COLUMNS, const char (*mapping)[4]) {
    for (int col = 0; col < VectorSize; col++) {
        gpio_put(COLUMNS[col], 1); 

        
        for (int row = 0; row < VectorSize; row++) {
            if (gpio_get(ROWS[row])) { 
                gpio_put(COLUMNS[col], 0); 
                return mapping[row][col]; 
            }
        }

        gpio_put(COLUMNS[col], 0); 
    }

    return '$'; 
}