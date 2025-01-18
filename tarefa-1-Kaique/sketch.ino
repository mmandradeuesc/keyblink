#include "pico/stdlib.h"
#include <stdio.h>

// Definição dos pinos dos LEDs e do buzzer
#define LED_R 10  // Pino do LED vermelho
#define LED_G 11  // Pino do LED verde
#define LED_B 12  // Pino do LED azul
#define BUZZER_PIN 13 // Pino do Buzzer

// Definição do teclado matricial 4x4
#define ROW_NUM    4  // Número de linhas
#define COLUMN_NUM 4  // Número de colunas

// Mapeamento das teclas
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Definição dos pinos das linhas e colunas do teclado
int row_pins[ROW_NUM] = {6, 7, 8, 9};  // Pinos das linhas
int col_pins[COLUMN_NUM] = {2, 3, 4, 5};  // Pinos das colunas

// Função para inicializar os pinos dos LEDs e buzzer
void setup_pins() {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    
    // Inicializa os LEDs e o buzzer como apagados
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);
    gpio_put(BUZZER_PIN, 0);
    
    // Configura as linhas como saída (HIGH)
    for (int i = 0; i < ROW_NUM; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 1);  // Pinos das linhas em HIGH inicialmente
    }

    // Configura as colunas como entrada (com pull-up)
    for (int i = 0; i < COLUMN_NUM; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);
    }
}

// Função para ler a tecla pressionada no teclado matricial
char read_keypad() {
    for (int row = 0; row < ROW_NUM; row++) {
        // Configura a linha atual como LOW
        gpio_put(row_pins[row], 0);
        
        // Verifica se alguma coluna está em LOW (tecla pressionada)
        for (int col = 0; col < COLUMN_NUM; col++) {
            if (gpio_get(col_pins[col]) == 0) {  // Se a coluna estiver em LOW, tecla foi pressionada
                // Aguarda a tecla ser solta
                while (gpio_get(col_pins[col]) == 0) {
                    // Espera a tecla ser liberada
                }
                return keys[row][col];  // Retorna o valor da tecla pressionada
            }
        }
        
        // Restaura a linha atual para HIGH
        gpio_put(row_pins[row], 1);
    }
    return 0;  // Se nenhuma tecla foi pressionada, retorna 0
}

int main() {
    // Inicializa a comunicação serial
    Serial.begin(115200);  // Inicializa a comunicação serial com a velocidade de 115200 baud
    
    // Inicializa os pinos
    setup_pins();
    
    while (true) {
        char key = read_keypad();  // Lê a tecla pressionada

        if (key) {  // Se uma tecla foi pressionada
            Serial.printf("Tecla pressionada: %c\n", key);  // Exibe no terminal

            // Ação para a tecla 1 (Acende o LED vermelho)
            if (key == '1') {
                gpio_put(LED_R, 1);  // Liga o LED vermelho
                gpio_put(LED_G, 0);  // Desliga o LED verde
                gpio_put(LED_B, 0);  // Desliga o LED azul
            }
            // Ação para a tecla 2 (Acende o LED verde)
            else if (key == '2') {
                gpio_put(LED_R, 0);  // Desliga o LED vermelho
                gpio_put(LED_G, 1);  // Liga o LED verde
                gpio_put(LED_B, 0);  // Desliga o LED azul
            }
            // Ação para a tecla 3 (Acende o LED azul)
            else if (key == '3') {
                gpio_put(LED_R, 0);  // Desliga o LED vermelho
                gpio_put(LED_G, 0);  // Desliga o LED verde
                gpio_put(LED_B, 1);  // Liga o LED azul
            }
            // Ação para a tecla 4 (Acende todos os LEDs)
            else if (key == '4') {
                gpio_put(LED_R, 1);  // Liga o LED vermelho
                gpio_put(LED_G, 1);  // Liga o LED verde
                gpio_put(LED_B, 1);  // Liga o LED azul
            }
            // Ação para a tecla # (Liga/desliga o buzzer)
            else if (key == '#') {
                gpio_put(BUZZER_PIN, 1);  // Liga o buzzer
                sleep_ms(500);  // Buzzer ligado por 500ms
                gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
            }
        }
    }

    return 0;
}
