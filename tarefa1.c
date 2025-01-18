#include "pico/stdlib.h"
#include <stdio.h>

// Define os pinos do teclado
const uint8_t COL_PINS[] = {1, 2, 3, 4};
const uint8_t ROW_PINS[] = {5, 6, 7, 8};
// Mapa de teclas
const char KEY_MAP[4][4] = {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};
const uint led_pin_green = 11; // Especifica o led verde
const uint led_pin_blue = 12;  // led azul
const uint led_pin_red = 13;   // led vermelho
const uint buzzer_pin = 21;    // pino do buzzer

void init_gpio() {
  gpio_init(led_pin_green);
  gpio_set_dir(led_pin_green, GPIO_OUT);
  gpio_init(led_pin_blue);
  gpio_set_dir(led_pin_blue, GPIO_OUT);
  gpio_init(led_pin_red);
  gpio_set_dir(led_pin_red, GPIO_OUT);
  gpio_init(buzzer_pin);
  gpio_set_dir(buzzer_pin, GPIO_OUT);

  for (int i = 0; i < 4; i++) {
    gpio_init(COL_PINS[i]);
    gpio_set_dir(COL_PINS[i], GPIO_OUT);
    gpio_put(COL_PINS[i], 1);
    gpio_init(ROW_PINS[i]);
    gpio_set_dir(ROW_PINS[i], GPIO_IN);
    gpio_pull_up(ROW_PINS[i]);
  }
}

char read_keypad() {
  for (int col = 0; col < 4; col++) {
    gpio_put(COL_PINS[col], 0);
    for (int row = 0; row < 4; row++) {
      if (gpio_get(ROW_PINS[row]) == 0) {
        gpio_put(COL_PINS[col], 1);
        return KEY_MAP[row][col];
      }
    }
    gpio_put(COL_PINS[col], 1);
  }
  return '\0'; // Nenhuma tecla pressionada
}

void handle_keypress(char key) { 
  switch (key) {    // Conjunto de caracteres para acionar o lede verde
    case '1':
      gpio_put(led_pin_green, 1);
      gpio_put(led_pin_blue, 0);
      gpio_put(led_pin_red, 0);
      break;
    case '4':        // Conjunto de caracteres para acionar o lede azul
      gpio_put(led_pin_green, 0);
      gpio_put(led_pin_blue, 1);
      gpio_put(led_pin_red, 0);
      break;
    case '7':        // Conjunto de caracteres para acionar o lede vermelho
      gpio_put(led_pin_green, 0);
      gpio_put(led_pin_blue, 0);
      gpio_put(led_pin_red, 1);
      break;
    case '#': // Conjunto de caracteres para acionar o buzzer
      gpio_put(buzzer_pin, 1);
      sleep_ms(500); // Toca o buzzer por 500ms
      gpio_put(buzzer_pin, 0);
      break;
    default: //0
      gpio_put(led_pin_green, 0);
      gpio_put(led_pin_blue, 0);
      gpio_put(led_pin_red, 0);
      gpio_put(buzzer_pin, 0);
      break;
  }
}

int main() {
  stdio_init_all();
  init_gpio();

  while (true) {
    char key = read_keypad();
    if (key != '\0') {
      handle_keypress(key);
    }
    sleep_ms(100); // Pequeno atraso para evitar múltiplas leituras da mesma tecla
  }
}