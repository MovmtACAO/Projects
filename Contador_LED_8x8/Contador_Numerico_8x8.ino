#include <Adafruit_NeoPixel.h>

#define PIN 6        // Pino de dados conectado ao DIN do painel
#define NUM_LEDS 64  // O seu painel é 8x8, então são 64 LEDs no total

// Inicializa a biblioteca para controlar o painel
Adafruit_NeoPixel painel = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// --- FONTE DE NÚMEROS FINAL E OTIMIZADA ---
// Desenhado para máxima clareza em um painel 8x8.
const uint8_t numeros[10][8] = {
  {0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00111100}, // 0
  {0b00011000, 0b00111000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00111100}, // 1
  {0b00111100, 0b01000010, 0b00000010, 0b00000100, 0b00011000, 0b00100000, 0b01111110, 0b00000000}, // 2
  {0b00111100, 0b01000010, 0b00000100, 0b00011100, 0b00000100, 0b01000010, 0b00111100, 0b00000000}, // 3
  {0b00001100, 0b00010100, 0b00100100, 0b01000100, 0b01111110, 0b00000100, 0b00000100, 0b00000000}, // 4
  {0b01111110, 0b01000000, 0b01111100, 0b00000010, 0b00000010, 0b01000010, 0b00111100, 0b00000000}, // 5
  {0b00111100, 0b01000000, 0b01000000, 0b01111100, 0b01000010, 0b01000010, 0b00111100, 0b00000000}, // 6
  {0b01111110, 0b01000010, 0b00000100, 0b00001000, 0b00010000, 0b00010000, 0b00010000, 0b00000000}, // 7
  {0b00111100, 0b01000010, 0b01000010, 0b00111100, 0b01000010, 0b01000010, 0b00111100, 0b00000000}, // 8
  {0b00111100, 0b01000010, 0b01000010, 0b00111110, 0b00000010, 0b00000100, 0b00111100, 0b00000000}  // 9
};

void setup() {
  painel.begin();
  painel.setBrightness(40); // Lembre-se: Mantenha um brilho baixo (de 0 a 255) para não forçar o Arduino!
  painel.show();
}

void loop() {
  // Mostra os números de 0 a 9 em um loop contínuo
  for (int i = 0; i <= 9; i++) {
    desenhaNumero(numeros[i]); // Chama a função para desenhar o número atual
    delay(3000);               // Espera 1 segundo
  }
}

// Função que desenha o bitmap de um número no painel
void desenhaNumero(const uint8_t bitmap[8]) {
  painel.clear(); // Apaga a imagem anterior

  // Percorre cada linha (y) e cada coluna (x) do desenho
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      // Verifica se o pixel (x,y) no desenho deve ser aceso
      if ( (bitmap[y] >> (7 - x)) & 1 ) {
        // Se sim, converte a coordenada (x,y) para o índice do LED e o acende
        int ledIndex = converteXYparaIndice(x, y);
        painel.setPixelColor(ledIndex, painel.Color(50, 100, 200)); // Cor Ciano/Azul claro
      }
    }
  }
  painel.show(); // Envia a nova imagem para o painel de uma vez
}

// Esta função converte a coordenada (x,y) para o índice do LED (0 a 63)
// A maioria dos painéis 8x8 tem uma ligação em "zigue-zague" (serpentina)
int converteXYparaIndice(int x, int y) {
  int index;
  // Se a linha (y) é par (0, 2, 4, 6), a contagem de LEDs é da esquerda para a direita
  if (y % 2 == 0) {
    index = y * 8 + x;
  }
  // Se a linha (y) é ímpar (1, 3, 5, 7), a contagem é invertida, da direita para a esquerda
  else {
    index = y * 8 + (7 - x);
  }
  return index;
}