#include <stdio.h>
#include "pico/stdlib.h"

#define VECTORSIZE 4

#define BUZZER 21
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
void MapBuzzer();

char TestKeys(const uint8_t*, const uint8_t*, const char(*)[4]);
void UnsetPins();

int main() {
    const uint8_t ROWS[VECTORSIZE] = {9, 8, 7, 6}; //Pinos das linhas do teclado matricial
    const uint8_t COLUMNS[VECTORSIZE] = {5, 4, 3, 2}; //Pinos das colunas do teclado matricial

    const char MAPPING[4][4] = {
    // colunas →               linhas ↓   
    //    5    4    3    2           
        {'1', '2', '3', 'A'}, // 9
        {'4', '5', '8', 'B'}, // 8
        {'7', '8', '9', 'C'}, // 7
        {'*', '0', '#', 'D'}  // 6
    };

    PicoInit(ROWS, COLUMNS);
    PicoLoop(ROWS, COLUMNS, MAPPING);

    return 0;
}

//Inicializa os componentes e o monitor serial
void PicoInit(const uint8_t* ROWS, const uint8_t* COLUMNS){
    stdio_init_all();
    MapKeyboard(ROWS, COLUMNS); 
    MapRGB();
    MapBuzzer();
}

//Realiza a lógica do programa
void PicoLoop(const uint8_t* ROWS, const uint8_t* COLUMNS, const char (*MAPPING)[4]){
    while (true) {
        char key = TestKeys(ROWS, COLUMNS, MAPPING);
        if (key != '$'){ // A lógica só é executada quando uma tecla for pressionada
            if (key == '1') 
                gpio_put(GREEN, true); // Liga o LED verde
            else if (key == '2') 
                gpio_put(BLUE, true); // Liga o LED azul
            else if (key == '3')
                gpio_put(RED, true); // Liga o LED vermelho
            else if (key == 'D')
                gpio_put(BUZZER, true); // Liga o buzzer
            else { // Quando qualquer outra coisa for pressionada, desliga tudo
                UnsetPins();
            }
            //printf("Key: %c\n", key); // Debug
        }
        //printf("Key: %c\n", key); // Debug
        sleep_ms(100); // Para conseguir ver o print, kkk
    }
}

//Configura os pinos de entrada
void SetInput(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);   
    gpio_pull_down(pin);          
}

//Configura os pinos de saída
void SetOutput(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);  
    gpio_put(pin, 0);             
}

//Mapeia o teclado
void MapKeyboard(const uint8_t* ROWS, const uint8_t* COLUMNS) {
    for (int i = 0; i < VECTORSIZE; i++) {
        SetInput(ROWS[i]);  
        SetOutput(COLUMNS[i]); 
    }
}

//Mapeia os LEDs RGB
void MapRGB(){
    for (int i = 11; i <= 13; i++) {//Pinos dos leds RGB
        //printf("pin %d \n", i);
        SetOutput(i);
    }
}

//Mapeia o Buzzer
void MapBuzzer(){
    SetOutput(BUZZER);
}

//Executa a captura dos botões pressionados no teclado
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

//Desliga os pinos (põe todos em estados LOW)
void UnsetPins(){
    gpio_put(GREEN, false);
    gpio_put(RED, false);
    gpio_put(BLUE, false);
    gpio_put(BUZZER, false);
}