#include <stdio.h>
#include "pico/stdlib.h"

#define VECTORSIZE 4
#define BUZZERPIN 21
#define GREEN 11
#define BLUE 12
#define RED 13

// Funções auxiliares
void PicoInit(const uint8_t*, const uint8_t*);
void PicoLoop(const uint8_t*, const uint8_t*, const char (*)[4]);

void SetInput(uint8_t);
void SetOutput(uint8_t);

void MapKeyboard(const uint8_t*, const uint8_t*);
void MapRGB();

char TestKeys(const uint8_t*, const uint8_t*, const char(*)[4]);

int main() {
    const uint8_t ROWS[VECTORSIZE] = {9, 8, 7, 6}; //Pinos das linhas do teclado matricial
    const uint8_t COLUMNS[VECTORSIZE] = {5, 4, 3, 2}; //Pinos das colunas do teclado matricial

    const char MAPPING[4][4] = {
// colunas ->                      linhas \/        
    //    5    4    3    2    
        {'1', '2', '3', 'A'}, // 9
        {'4', '5', '8', 'B'}, // 8
        {'7', '8', '9', 'C'}, // 7
        {'*', 'B', '#', 'D'}  // 6
    };

    PicoInit(ROWS, COLUMNS);
    PicoLoop(ROWS, COLUMNS, MAPPING);

    return 0;
}

void PicoInit(const uint8_t* ROWS, const uint8_t* COLUMNS){
    stdio_init_all();
    MapKeyboard(ROWS, COLUMNS); 
    MapRGB();
}

void PicoLoop(const uint8_t* ROWS, const uint8_t* COLUMNS, const char (*MAPPING)[4]){
    while (true) {
        char key = TestKeys(ROWS, COLUMNS, MAPPING);
        if (key == MAPPING[0][0]) // Quando 1 for pressionado
            gpio_put(GREEN, true);
        else
            gpio_put(GREEN, false);
        //printf("Key: %c\n", key); // Debug
        //sleep_ms(500); // Para conseguir ver o print, kkk
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
    for (int i = 0; i < VECTORSIZE; i++) {
        SetInput(ROWS[i]);  
        SetOutput(COLUMNS[i]); 
    }
}

void MapRGB(){
    for (int i = 11; i < 13; i++) //Pinos dos leds RGB
        SetOutput(i);
}

char TestKeys(const uint8_t* ROWS, const uint8_t* COLUMNS, const char (*MAPPING)[4]) {
    for (int col = 0; col < VECTORSIZE; col++) {
        gpio_put(COLUMNS[col], 1); 

        for (int row = 0; row < VECTORSIZE; row++) {
            if (gpio_get(ROWS[row])) { 
                gpio_put(COLUMNS[col], 0); 
                return MAPPING[row][col]; 
            }
        }

        gpio_put(COLUMNS[col], 0); 
    }

    return '$'; 
}