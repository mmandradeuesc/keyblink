// #include <stdio.h>
// #include "pico/stdlib.h"

// // Definição dos pinos GPIO
// #define GPIO_GREEN_LED 11
// #define GPIO_BLUE_LED 12
// #define GPIO_RED_LED 13
// #define GPIO_BUZZER 27
// #define time 300 // Tempo de acionamento em milissegundos

// // Definição das linhas e colunas do teclado
// const uint rows[] = {0, 1, 2, 3};
// const uint cols[] = {4, 5, 6, 7};

// // Mapeamento do teclado
// const char keypad[4][4] = {
//     {'1', '2', '3', 'A'},
//     {'4', '5', '6', 'B'},
//     {'7', '8', '9', 'C'},
//     {'*', '0', '#', 'D'}
// };

// // Protótipos das funções
// void InitGPIOs();
// void InitKeypad();
// void ActionKey1();
// void ActionKey2();
// void ActionKey3();
// void ActionKey4();
// void ActionKey5();
// void ActionKey6();
// void ActionKeyA();
// void ActionKeyB();
// char ReadKeypad();
// void HandleKey(char key);
// void ProcessKey(char key);

// int main() {
//     // Inicialização da biblioteca stdio
//     stdio_init_all();
//     InitGPIOs();
//     InitKeypad();

//     while (true) {
//         char key = ReadKeypad();
//         ProcessKey(key);  
//     }

//     return 0;
// }

// // Função para inicialização dos GPIOs
// void InitGPIOs() {
//     // Configuração dos LEDs
//     gpio_init(GPIO_GREEN_LED);
//     gpio_set_dir(GPIO_GREEN_LED, GPIO_OUT);
//     gpio_init(GPIO_BLUE_LED);
//     gpio_set_dir(GPIO_BLUE_LED, GPIO_OUT);
//     gpio_init(GPIO_RED_LED);
//     gpio_set_dir(GPIO_RED_LED, GPIO_OUT);

//     // Configuração do buzzer
//     gpio_init(GPIO_BUZZER);
//     gpio_set_dir(GPIO_BUZZER, GPIO_OUT);
// }

// // Função para inicialização do teclado
// void InitKeypad() {
//     for (int i = 0; i < 4; i++) {
//         // Configuração das linhas como saída
//         gpio_init(rows[i]);
//         gpio_set_dir(rows[i], GPIO_OUT);
//         // Configuração das colunas como entrada com pull-up
//         gpio_init(cols[i]);
//         gpio_set_dir(cols[i], GPIO_IN);
//         gpio_pull_up(cols[i]);
//     }
// }

// // Ações para cada tecla

// // Ação da tecla 1: LED verde
// void ActionKey1() {
//     gpio_put(GPIO_GREEN_LED, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_GREEN_LED, 0);
// }

// // Ação da tecla 2: LED azul
// void ActionKey2() {
//     gpio_put(GPIO_BLUE_LED, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_BLUE_LED, 0);
// }

// // Ação da tecla 3: LED vermelho
// void ActionKey3() {
//     gpio_put(GPIO_RED_LED, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_RED_LED, 0);
// }

// // Ação da tecla 4: LEDs verde e azul
// void ActionKey4() {
//     gpio_put(GPIO_GREEN_LED, 1);
//     gpio_put(GPIO_BLUE_LED, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_GREEN_LED, 0);
//     gpio_put(GPIO_BLUE_LED, 0);
// }

// // Ação da tecla 5: LEDs verde e vermelho
// void ActionKey5() {
//     gpio_put(GPIO_GREEN_LED, 1);
//     gpio_put(GPIO_RED_LED, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_GREEN_LED, 0);
//     gpio_put(GPIO_RED_LED, 0);
// }

// // Ação da tecla 6: LEDs azul e vermelho
// void ActionKey6() {
//     gpio_put(GPIO_BLUE_LED, 1);
//     gpio_put(GPIO_RED_LED, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_BLUE_LED, 0);
//     gpio_put(GPIO_RED_LED, 0);
// }

// // Ação da tecla A: Buzzer
// void ActionKeyA() {
//     gpio_put(GPIO_BUZZER, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_BUZZER, 0);
// }

// // Ação da tecla B: Todos os LEDs e buzzer
// void ActionKeyB() {
//     gpio_put(GPIO_GREEN_LED, 1);
//     gpio_put(GPIO_BLUE_LED, 1);
//     gpio_put(GPIO_RED_LED, 1);
//     gpio_put(GPIO_BUZZER, 1);
//     sleep_ms(time);
//     gpio_put(GPIO_GREEN_LED, 0);
//     gpio_put(GPIO_BLUE_LED, 0);
//     gpio_put(GPIO_RED_LED, 0);
//     gpio_put(GPIO_BUZZER, 0);
// }


// // Função para leitura do teclado
// char ReadKeypad() {
//     for (int i = 0; i < 4; i++) {
//         // Ativa a linha 'i'
//         gpio_put(rows[i], 0);
//         for (int j = 0; j < 4; j++) {
//             // Verifica se a coluna 'j' está ativa
//             if (gpio_get(cols[j]) == 0) {
//                 char key = keypad[i][j];
//                 sleep_ms(200);
//                 // Aguarda a tecla ser solta
//                 while (gpio_get(cols[j]) == 0);
//                 return key;
//             }
//         }
//         // Desativa a linha i
//         gpio_put(rows[i], 1);
//     }
//     return '\0';
// }

// // Função para tratamento da tecla pressionada
// void HandleKey(char key) {
//     switch (key) {
//         case '1':
//             ActionKey1();
//             break;
//         case '2':
//             ActionKey2();
//             break;
//         case '3':
//             ActionKey3();
//             break;
//         case '4':
//             ActionKey4();
//             break;
//         case '5':
//             ActionKey5();
//             break;
//         case '6':
//             ActionKey6();
//             break;
//         case 'A':
//             ActionKeyA();
//             break;            
//         case 'B':
//             ActionKeyB();
//             break;
//         default:
//             printf("Key not mapped.\n");
//     }
// }

// // Função para processamento da tecla pressionada
// void ProcessKey(char key) {
//     if (key != '\0') {
//         printf("Pressed key: %c\n", key);
//         HandleKey(key);
//     }
// }

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