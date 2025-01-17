#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define ROWS 4
#define COLS 4

const uint row_pins[ROWS] = {2, 3, 4, 5};
const uint col_pins[COLS] = {6, 7, 8, 9};

const uint led_pins[3] = {10, 11, 12};
const uint buzzer_pin = 13;

char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void setup_gpio() {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 0);
    }

    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);
    }

    for (int i = 0; i < 3; i++) {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
        gpio_put(led_pins[i], 0);
    }

    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
    gpio_put(buzzer_pin, 0);
}

char scan_keypad() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(row_pins[row], 1);

        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col]) == 0) {
                sleep_ms(50);
                gpio_put(row_pins[row], 0);
                return key_map[row][col];
            }
        }

        gpio_put(row_pins[row], 0);
    }

    return '\0';
}

void handle_key(char key) {
    switch (key) {
        case '1':
            gpio_put(led_pins[0], 1); // Acende o LED 1
            break;
        case '2':
            gpio_put(led_pins[1], 1); // Acende o LED 2
            break;
        case '3':
            gpio_put(led_pins[2], 1); // Acende o LED 3
            break;
        case 'A':
            gpio_put(buzzer_pin, 1); // Ativa o buzzer
            break;
        case 'B':
            gpio_put(led_pins[0], 0); // Apaga o LED 1
            break;
        case 'C':
            gpio_put(led_pins[1], 0); // Apaga o LED 2
            break;
        case 'D':
            gpio_put(led_pins[2], 0); // Apaga o LED 3
            break;
        case '#':
            gpio_put(buzzer_pin, 0); // Desativa o buzzer
            break;
        default:
            break;
    }
}

int main() {
    setup_gpio();

    while (true) {
        char key = scan_keypad();
        if (key != '\0') {
            handle_key(key);
        }
        sleep_ms(100);
    }
}