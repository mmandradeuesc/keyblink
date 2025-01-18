#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos GPIO
#define GPIO_GREEN_LED 11
#define GPIO_BLUE_LED 12
#define GPIO_RED_LED 13
#define GPIO_BUZZER 27

// Definições de tempo e teclado
const unsigned int ACTIVATION_DURATION_MS = 300;
const uint8_t ROWS[] = {0, 1, 2, 3};  // Linhas do teclado
const uint8_t COLS[] = {4, 5, 6, 7};  // Colunas do teclado
const char KEYPAD[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Estrutura para mapear teclas a funções
typedef void (*KeyAction)();

struct KeyMapping {
    char key;
    KeyAction action;
};

// Protótipos das funções
void InitializeGPIOs();
void InitializeKeypad();
void ActivateGreenLed();
void ActivateBlueLed();
void ActivateRedLed();
void ActivateGreenBlueLeds();
void ActivateGreenRedLeds();
void ActivateBlueRedLeds();
void ActivateBuzzer();
void ActivateAll();
char ReadKeypad();
void HandleKey(char key);
void ProcessKey(char key);

// Mapeamento de teclas e ações
const struct KeyMapping keyMappings[] = {
    {'1', ActivateGreenLed},
    {'2', ActivateBlueLed},
    {'3', ActivateRedLed},
    {'4', ActivateGreenBlueLeds},
    {'5', ActivateGreenRedLeds},
    {'6', ActivateBlueRedLeds},
    {'A', ActivateBuzzer},
    {'B', ActivateAll}
};

int main() {
    stdio_init_all();
    InitializeGPIOs();
    InitializeKeypad();

    while (true) {
        char key = ReadKeypad();
        ProcessKey(key);
    }

    return 0;
}

void InitializeGPIOs() {
    gpio_init(GPIO_GREEN_LED);
    gpio_set_dir(GPIO_GREEN_LED, GPIO_OUT);
    gpio_init(GPIO_BLUE_LED);
    gpio_set_dir(GPIO_BLUE_LED, GPIO_OUT);
    gpio_init(GPIO_RED_LED);
    gpio_set_dir(GPIO_RED_LED, GPIO_OUT);
    gpio_init(GPIO_BUZZER);
    gpio_set_dir(GPIO_BUZZER, GPIO_OUT);
}

void InitializeKeypad() {
    for (int i = 0; i < 4; i++) {
        gpio_init(ROWS[i]);
        gpio_set_dir(ROWS[i], GPIO_IN);
        gpio_pull_down(ROWS[i]);
        gpio_init(COLS[i]);
        gpio_set_dir(COLS[i], GPIO_OUT);
    }
}

// Funções de ação para cada tecla
void ActivateGreenLed() { 
    gpio_put(GPIO_GREEN_LED, 1); 
    sleep_ms(ACTIVATION_DURATION_MS); 
    gpio_put(GPIO_GREEN_LED, 0);
}
void ActivateBlueLed() {
    gpio_put(GPIO_BLUE_LED, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_BLUE_LED, 0);
}

void ActivateRedLed() {
    gpio_put(GPIO_RED_LED, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_RED_LED, 0);
}

void ActivateGreenBlueLeds() {
    gpio_put(GPIO_GREEN_LED, 1);
    gpio_put(GPIO_BLUE_LED, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_GREEN_LED, 0);
    gpio_put(GPIO_BLUE_LED, 0);
}

void ActivateGreenRedLeds() {
    gpio_put(GPIO_GREEN_LED, 1);
    gpio_put(GPIO_RED_LED, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_GREEN_LED, 0);
    gpio_put(GPIO_RED_LED, 0);
}

void ActivateBlueRedLeds() {
    gpio_put(GPIO_BLUE_LED, 1);
    gpio_put(GPIO_RED_LED, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_BLUE_LED, 0);
    gpio_put(GPIO_RED_LED, 0);
}

void ActivateBuzzer() {
    gpio_put(GPIO_BUZZER, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_BUZZER, 0);
}

void ActivateAll() {
    gpio_put(GPIO_GREEN_LED, 1);
    gpio_put(GPIO_BLUE_LED, 1);
    gpio_put(GPIO_RED_LED, 1);
    gpio_put(GPIO_BUZZER, 1);
    sleep_ms(ACTIVATION_DURATION_MS);
    gpio_put(GPIO_GREEN_LED, 0);
    gpio_put(GPIO_BLUE_LED, 0);
    gpio_put(GPIO_RED_LED, 0);
    gpio_put(GPIO_BUZZER, 0);
}
char ReadKeypad() {
    for (int j = 0; j < 4; j++) {
        gpio_put(COLS[j], 1);
        for (int i = 0; i < 4; i++) {
            if (gpio_get(ROWS[i])) {
                char key = KEYPAD[i][j];
                sleep_ms(200);  // Debounce
                while (gpio_get(ROWS[i]));
                gpio_put(COLS[j], 0);
                return key;
            }
        }
        gpio_put(COLS[j], 0);
    }
    return '\0';
}

void HandleKey(char key) {
    for (int i = 0; i < sizeof(keyMappings) / sizeof(keyMappings[0]); i++) {
        if (keyMappings[i].key == key) {
            keyMappings[i].action();
            return;
        }
    }
    printf("Key not mapped: %c\n", key);
}

void ProcessKey(char key) {
    if (key != '\0') {
        printf("Key pressed: %c\n", key);
        HandleKey(key);
    }
}
